#include <darabonba/Core.hpp>
#include <darabonba/String.hpp>
#include <darabonba/Array.hpp>
#include <darabonba/http/Form.hpp>
#include <darabonba/signature/Signer.hpp>
#include <darabonba/encode/Encoder.hpp>
#include <alibabacloud/Utils.hpp>
#include <map>
#include <set>
using namespace std;
using json = nlohmann::json;
using Form = Darabonba::Http::Form;

static string lowercase(string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](char c) { return std::tolower(c); });
  return str;
}

namespace AlibabaCloud
{
namespace OpenApi
{
namespace Utils
{

/**
 * Convert all params of body other than type of readable into content 
 * @param body source Model
 * @param content target Model
 * @return void
 */
void Utils::convert(const Darabonba::Model &body, Darabonba::Model &content) {
  auto map = body.toMap();
  content.fromMap(map);
  content.validate();
}

int64_t Utils::getTimeLeft(const map<string, string>& headers, const string& key) {
  auto it = headers.find(key);
  if (it != headers.end()) {
      const string rateLimit = it->second;
      istringstream stream(rateLimit);
      string pair;
      while (getline(stream, pair, ',')) {
          istringstream kvStream(pair);
          string k, v;
          if (getline(kvStream, k, ':') && getline(kvStream, v)) {
              k = Darabonba::String::trim(k);
              v = Darabonba::String::trim(v);
              if (k == "TimeLeft") {
                  try {
                      return stoll(v);
                  } catch (const invalid_argument& ia) {
                      return 0;
                  }
              }
          }
      }
  }
  return 0;
}

/**
 * Get throttling param
 * @param the response headers
 * @return time left
 */
int64_t Utils::getThrottlingTimeLeft(const map<string, string> &headers) {
  int64_t timeLeftForUserApi = getTimeLeft(headers, "x-ratelimit-user-api");
  int64_t timeLeftForUser = getTimeLeft(headers, "x-ratelimit-user");

  if (timeLeftForUserApi > timeLeftForUser) {
    return timeLeftForUserApi;
  } else {
    return timeLeftForUser;
  }
}

string Utils::getCanonicalHeaders(const Darabonba::Http::Header &headers) {
  map<string, const string *> canonicalKeys;
  for (const auto &p : headers) {
    if (Darabonba::String::hasPrefix(p.first, "x-acs")) {
      canonicalKeys.emplace(p.first, &p.second);
    }
  }
  string canonicalHeaders = "";
  for (const auto &p : canonicalKeys) {
    canonicalHeaders += p.first + ':' + *p.second + '\n';
  }
  return canonicalHeaders;
}

string Utils::getCanonicalResource(const string &path,
                           const map<string, string> &query) {
  if (query.empty())
    return path;
  string ret = path + '?';
  for (const auto &p : query) {
    if (p.first.empty())
      continue;
    if (p.second.empty()) {
      ret += p.first + '&';
    } else {
      ret += p.first + '=' + p.second + '&';
    }
  }
  ret.pop_back();
  return ret;
}

/**
 * Get the string to be signed according to request
 * @param request  which contains signed messages
 * @return the signed string
 */
string Utils::getStringToSign(const Darabonba::Http::Request &req) {
  auto method = req.method(), path = req.url().pathName();
  const auto &headers = req.header();
  const auto &query = req.query();
  string accept = "";
  auto it = headers.find("accept");
  if (it != headers.end()) {
    accept = it->second;
  }
  string contentMD5 = "";
  it = headers.find("content-md5");
  if (it != headers.end()) {
    contentMD5 = it->second;
  }
  string contentType = "";
  it = headers.find("content-type");
  if (it != headers.end()) {
    contentType = it->second;
  }
  string date = "";
  it = headers.find("date");
  if (it != headers.end()) {
    date = it->second;
  }
  auto header = method + '\n' + accept + '\n' + contentMD5 + '\n' +
                contentType + '\n' + date + '\n';
  auto canonicalHeaders = getCanonicalHeaders(headers);
  auto canonicalResource = getCanonicalResource(path, query);
  return header + canonicalHeaders + canonicalResource;
}

/**
 * Get signature according to stringToSign, secret
 * @param stringToSign  the signed string
 * @param secret accesskey secret
 * @return the signature
 */
string Utils::getROASignature(string &stringToSign, string &secret) {
  if (secret.empty())
    return "";
  auto signData =
      Darabonba::Signature::Signer::HmacSHA1Sign(stringToSign, secret);
  return Darabonba::Encode::Encoder::base64EncodeToString(signData);
}

/**
 * Parse filter into a form string
 * @param filter object
 * @return the string
 */
string Utils::toForm(const Darabonba::Json &filter) {
  string ret;
  for (const auto &p : query(filter)) {
    if (p.second.empty())
      continue;
    ret.append(Form::encode(p.first))
        .append("=")
        .append(Form::encode(p.second))
        .append("&");
  }
  ret.pop_back();
  return ret;
}

/**
 * Get UTC string
 * @return the UTC string
 */
string Utils::getDateUTCString() {
  char buf[80];
  time_t t = time(nullptr);
  strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&t));
  return buf;
}

Darabonba::Bytes Utils::signatureMethod(const string &stringToSign,
                                       const string &secret,
                                       const string &signAlgorithm) {
  if (secret.empty() || signAlgorithm.empty())
    return {};
  if (signAlgorithm == "ACS3-HMAC-SHA256") {
    return Darabonba::Signature::Signer::HmacSHA256Sign(stringToSign, secret);
  } else if (signAlgorithm == "ACS3-HMAC-SM3") {
    return Darabonba::Signature::Signer::HmacSM3Sign(stringToSign, secret);
  } else if (signAlgorithm == "ACS3-RSA-SHA256") {
    return Darabonba::Signature::RSASigner::sign(
        reinterpret_cast<const void *>(stringToSign.c_str()),
        stringToSign.size(), reinterpret_cast<const void *>(secret.c_str()),
        secret.size(),
        unique_ptr<Darabonba::Encode::Hash>(
            new Darabonba::Encode::SHA256()));
  }
  return {};
}

void Utils::processObject(const Darabonba::Json &obj, string key,
                         std ::map<string, string> &out) {
  if (obj.is_null()) {
    return;
  } else if (obj.is_primitive()) {
    if (obj.is_binary()) {
      const auto &objReal = obj.get_ref<const Darabonba::Json::binary_t &>();
      out[key] = string(objReal.begin(), objReal.end());
    } else if (obj.is_string()) {
      out[key] = obj.get<string>();
    } else {
      // bool, number, and others
      out[key] = nlohmann::to_string(obj);
    }
  } else if (obj.is_array()) {
    for (size_t i = 0; i < obj.size(); ++i) {
      processObject(
          obj[i], (key.empty() ? key : key + '.') + to_string(i + 1), out);
    }
  } else if (obj.is_object()) {
    for (auto it = obj.begin(); it != obj.end(); ++it) {
      processObject(it.value(), (key.empty() ? key : key + '.') + it.key(),
                    out);
    }
  }
}

/**
 * Parse filter into a object which's type is map[string]string
 * @param filter query param
 * @return the object
 */
map<string, string> Utils::query(const Darabonba::Json &filter) {
  if (filter.empty() || filter.is_null())
    return {};
  map<string, string> ret;
  processObject(filter, "", ret);
  return ret;
}

/**
 * Get signature according to signedParams, method and secret
 * @param signedParams params which need to be signed
 * @param method http method e.g. GET
 * @param secret AccessKeySecret
 * @return the signature
 */
string Utils::getRPCSignature(const map<string, string> &signedParams, const string &method, const string &secret) {
  string canonicalQueryString = "";
  for (const auto &p : signedParams) {
    if (p.second.empty())
      continue;
    canonicalQueryString +=
        Darabonba::Encode::Encoder::percentEncode(p.first) + '=' +
        Darabonba::Encode::Encoder::percentEncode(p.second) + '&';
  }
  canonicalQueryString.pop_back(); // pop '&'
  // %2F is the encode of '/'
  string stringToSign =
      method + "&%2F&" +
      Darabonba::Encode::Encoder::percentEncode(canonicalQueryString);

  auto signData =
      Darabonba::Signature::Signer::HmacSHA1Sign(stringToSign, secret + '&');
  return Darabonba::Encode::Encoder::base64EncodeToString(signData);
}

/**
 * Parse array into a string with specified style
 * @param array the array
 * @param prefix the prefix string
 * @style specified style e.g. repeatList
 * @return the string
 */
string Utils::arrayToStringWithSpecifiedStyle(const Darabonba::Json &array,
                                                  const string &prefix,
                                                  const string &style) {
  if (array.empty())
    return "";
  if (style == "repeatList") {
    Darabonba::Json obj = {{prefix, array}};
    string ret;
    for (const auto &p : query(obj)) {
      if (p.second.empty())
        continue;
      ret.append(Form::encode(p.first))
          .append("=")
          .append(Form::encode(p.second))
          .append("&&");
    }
    // remove the "&&"
    ret.resize(ret.size() - 2);
    return ret;
  } else if (style == "json") {
    return array.dump();
  } else {
    char flag;
    if (style == "simple") {
      flag = ',';
    } else if (style == "spaceDelimited") {
      flag = ' ';
    } else if (style == "pipeDelimited") {
      flag = '|';
    } else {
      return "";
    }
    ostringstream oss;
    for (const auto &val : array) {
      if(val.is_string()) {
        oss << val.get<string>() << flag;
      } else {
        oss << val << flag;
      }
    }
    auto ret = oss.str();
    ret.pop_back();
    return ret;
  }
  return "";
}

/**
 * Stringify the value of map
 * @return the new stringified map
 */
map<string, string> Utils::stringifyMapValue(json &m) {
  map<string, string> result;
  if (m.is_null()) {
      return result;
  }
  if (!m.is_object()) {
      return result;
  }
  map<string, Darabonba::Json> mr = m.get<map<string, Darabonba::Json>>();
  for (const auto& kv : m) {
      const string& key = kv.first;
      const nlohmann::json& value = kv.second;

      if (!value.is_null()) {
          result[key] = value.dump();
      }
  }

  return result;
}

/**
 * Transform input as array.
 */
vector<map<string, Darabonba::Json>> Utils::toArray(const Darabonba::Json &input) {
  vector<map<string, Darabonba::Json>> tmp;

  try {
      if (input.is_null()) {
          return tmp;
      }
      if (input.is_array()) {
          for (const auto& elem : input) {
              if (elem.is_object()) {
                  map<string, Darabonba::Json> objMap = elem.get<map<string, Darabonba::Json>>();
                  tmp.push_back(objMap);
              }
          }
      }
  } catch (const exception& e) {
      cerr << "Error parsing JSON: " << e.what() << endl;
      return tmp;
  }

  return tmp;
}

/**
 * Parse map with flat style
 *
 * @param any the input
 * @return any
 */
Darabonba::Json Utils::mapToFlatStyle(Darabonba::Json &input) {}

pair<string, string> Utils::getCanonicalHeadersPair(const Darabonba::Http::Header &headers) {
  map<string, set<string>> tmpHeaders;
  set<string> canonicalKeys;

  for (const auto &p : headers) {
    auto lowerKey = Darabonba::String::toLower(p.first);
    if (Darabonba::String::hasPrefix(lowerKey, "x-acs-") ||
        lowerKey == "host" || lowerKey == "content-type") {
      canonicalKeys.insert(lowerKey);
      tmpHeaders[lowerKey].emplace(p.second);
    }
  }

  string canonicalHeaders = "";
  for (const auto &p : tmpHeaders) {
    canonicalHeaders +=
        p.first + ':' +
        Darabonba::Array::join(p.second.begin(), p.second.end(), ",") + '\n';
  }
  return {canonicalHeaders, Darabonba::Array::join(canonicalKeys.begin(),
                                                   canonicalKeys.end(), ";")};
}

/**
 * Get the authorization 
 * @param request request params
 * @param signatureAlgorithm the autograph method
 * @param payload the hashed request
 * @param accesskey the accesskey string
 * @param accessKeySecret the accessKeySecret string
 * @return authorization string
 */
string Utils::getAuthorization(const Darabonba::Http::Request &req,
                               const string &signatureAlgorithm, 
                               const string &payload, 
                               const string &accessKey,
                               const string &accessKeySecret) {
  auto canonicalURI = req.url().pathName();
  if (canonicalURI.empty()) {
    canonicalURI = "/";
  }

  auto canonicalQuery = string(req.query());
  auto p = getCanonicalHeadersPair(req.header());
  const auto &canonicalHeaders = p.first, &signedHeaders = p.second;

  string canonicalRequest = "";
  canonicalRequest.append(req.method())
      .append("\n")
      .append(canonicalURI)
      .append("\n")
      .append(canonicalQuery)
      .append("\n")
      .append(canonicalHeaders)
      .append("\n")
      .append(signedHeaders)
      .append("\n")
      .append(payload);
  Darabonba::Bytes canonicalRequestByte;
  canonicalRequestByte.assign(canonicalRequest.begin(), canonicalRequest.end());
  auto strToSign = signatureAlgorithm + '\n' +
                   hexEncode(hash(canonicalRequestByte, signatureAlgorithm));
  auto signature = hexEncode(
      signatureMethod(strToSign, accessKeySecret, signatureAlgorithm));
  return signatureAlgorithm + " Credential=" + accessKey +
         ",SignedHeaders=" + signedHeaders + ",Signature=" + signature;
}

static string osName() {
  #if defined(_WIN64) || defined(__MINGW64__)
    return "Windows64";
  #elif defined(_WIN32) || defined(__MINGW32__)
    return "Windows32";
  #elif defined(__APPLE__) || defined(__MACH__)
    return "MacOS";
  #elif defined(__linux__)
    return "Linux";
  #elif defined(__FreeBSD__)
    return "FreeBSD";
  #elif defined(__NetBSD__)
    return "NetBSD";
  #elif defined(__unix) || defined(__unix__)
    return "Unix";
  #elif defined(__ANDROID__)
    return "Android";
  #else
    return "Other";
  #endif
  }

string Utils::getUserAgent(const string &userAgent) {
  string defaultUserAgent = "Alibabacloud C++ OS/" + osName() + " Core/1.0 TeaDSL/2";
  if (userAgent.empty()) {
    return defaultUserAgent;
  }
  return defaultUserAgent + userAgent;
}

/**
 * Get endpoint according to productId, regionId, endpointType, network and suffix
 * @return endpoint
 */
string Utils::getEndpointRules(const string &product,
                               const string &regionId,
                               const string &endpointType,
                               const string &network,
                               const string &suffix) {
  string result, networkVal, suffixVal = suffix;
  if (!network.empty() && lowercase(network) != "public") {
    networkVal = "-" + network;
  } else {
    networkVal = "";
  }

  if (!suffix.empty()) {
    suffixVal = "-" + suffix;
  }

  if (endpointType == "regional") {
    if (regionId.empty()) {
      throw Darabonba::Exception(
          "RegionId is empty, please set a valid RegionId");
    }
    result.append(product)
        .append(suffixVal)
        .append(networkVal + ".")
        .append(regionId)
        .append(".aliyuncs.com");
  } else {
    result.append(product).append(suffixVal).append(networkVal).append(
        ".aliyuncs.com");
  }
  return lowercase(result);
}
} // namespace Alibabacloud
} // namespace OpenApi
} // namespace Utils