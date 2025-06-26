// This file is auto-generated, don't edit it. Thanks.
#ifndef ALIBABACLOUD_UTILS_HPP_
#define ALIBABACLOUD_UTILS_HPP_
#include <darabonba/Core.hpp>
#include <darabonba/encode/Encoder.hpp>
#include <alibabacloud/UtilsModel.hpp>
#include <map>
using namespace std;
using json = nlohmann::json;
namespace AlibabaCloud
{
namespace OpenApi
{
namespace Utils
{
  class Utils {
    public:
      Utils() {}
      /**
       * Convert all params of body other than type of readable into content 
       * @param body source Model
       * @param content target Model
       * @return void
       */
      static void convert(const Darabonba::Model &body, Darabonba::Model &content);

      /**
       * Get throttling param
       * @param the response headers
       * @return time left
       */
      static int64_t getThrottlingTimeLeft(const map<string, string> &headers);

      /**
       * Hash the raw data with signatureAlgorithm
       * @param raw hashing data
       * @param signatureAlgorithm the autograph method
       * @return hashed bytes
       */
      static Darabonba::Bytes hash(const Darabonba::Bytes &raw,
                                   const string &signatureAlgorithm) {
        if (signatureAlgorithm.empty())
          return {};
        if (signatureAlgorithm == "ACS3-HMAC-SHA256" ||
            signatureAlgorithm == "ACS3-RSA-SHA256") {
          return Darabonba::Encode::SHA256::hash(raw);
        } else if (signatureAlgorithm == "ACS3-HMAC-SM3") {
          return Darabonba::Encode::SM3::hash(raw);
        }
        return {};
      };

      /**
       * Generate a nonce string
       * @return the nonce string
       */
      inline static string getNonce() { return Darabonba::Core::uuid(); };

      /**
       * Get the string to be signed according to request
       * @param req  which contains signed messages
       * @return the signed string
       */
      static string getStringToSign(const Darabonba::Http::Request &req);

      /**
       * Get signature according to stringToSign, secret
       * @param stringToSign  the signed string
       * @param secret accesskey secret
       * @return the signature
       */
      static string getROASignature(string &stringToSign, string &secret);

      /**
       * Parse filter into a form string
       * @param filter object
       * @return the string
       */
      static string toForm(const Darabonba::Json &filter);

      /**
       * Get timestamp
       * @return the timestamp string
       */
      static string getTimestamp() {
        char buf[80];
        time_t t = time(nullptr);
        strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%SZ", gmtime(&t));
        return buf;
      }

      /**
       * Get UTC string
       * @return the UTC string
       */
      static string getDateUTCString();

      /**
       * Parse filter into a object which's type is map[string]string
       * @param filter query param
       * @return the object
       */
      static map<string, string> query(const Darabonba::Json &filter);

      /**
       * Get signature according to signedParams, method and secret
       * @param signedParams params which need to be signed
       * @param method http method e.g. GET
       * @param secret AccessKeySecret
       * @return the signature
       */
      static string getRPCSignature(const map<string, string> &signedParams, const string &method, const string &secret);

      /**
       * Parse array into a string with specified style
       * @param array the array
       * @param prefix the prefix string
       * @style specified style e.g. repeatList
       * @return the string
       */
      static string arrayToStringWithSpecifiedStyle(const Darabonba::Json &array, const string &prefix, const string &style);

      /**
       * Stringify the value of map
       * @return the new stringified map
       */
      static map<string, string> stringifyMapValue(json &m);

      /**
       * Transform input as array.
       */
      static vector<map<string, Darabonba::Json>> toArray(const Darabonba::Json &input);

      /**
       * Parse map with flat style
       *
       * @param any the input
       * @return any
       */
      static Darabonba::Json mapToFlatStyle(Darabonba::Json &input);

      /**
       * Transform input as map.
       */
      static Darabonba::Json parseToMap(Darabonba::Json &input) {
        return input;
      };

      static std::string hexEncode(const Darabonba::Bytes &raw) {
        return Darabonba::Encode::Encoder::hexEncode(raw);
      }

      static string getEncodePath(const string &path) {
        return Darabonba::Encode::Encoder::pathEncode(path);
      }

      static string getEncodeParam(const string &param) {
        return Darabonba::Encode::Encoder::percentEncode(param);
      }

      /**
       * Get the authorization 
       * @param req request params
       * @param signatureAlgorithm the autograph method
       * @param payload the hashed request
       * @param accesskey the accesskey string
       * @param accessKeySecret the accessKeySecret string
       * @return authorization string
       */
      static string getAuthorization(const Darabonba::Http::Request &request,
                                     const string &signatureAlgorithm,
                                     const string &payload,
                                     const string &accessKey,
                                     const string &accessKeySecret);

      static string getUserAgent(const string &userAgent);

      static std::string getEndpointRules(const std::string &product,
                                          const std::string &regionId,
                                          const std::string &endpointType,
                                          const std::string &network,
                                          const std::string &suffix);

      static Darabonba::Bytes signatureMethod(const std::string &stringToSign,
                                              const std::string &secret,
                                              const std::string &signAlgorithm);

      /**
       * If endpointType is internal, use internal endpoint
       * If serverUse is true and endpointType is accelerate, use accelerate endpoint
       * Default return endpoint
       * @param endpoint endpoint
       * @param useAccelerate whether use accelerate endpoint
       * @param endpointType value must be internal or accelerate
       * @return the final endpoint
       */
      static string getEndpoint(const string &endpoint,
        bool useAccelerate,
        const string &endpointType) {
        if (useAccelerate && endpointType == "accelerate")
          return "oss-accelerate.aliyuncs.com";
        auto ret = endpoint;
        if (endpointType == "internal") {
          auto pos = endpoint.find('.');
          if (pos != string::npos) {
            ret.replace(pos, 1, "-internal.");
          }
        }
        return ret;
      };
  protected:
    static pair<string, string>
    getCanonicalHeadersPair(const Darabonba::Http::Header &headers);

    static string
    getCanonicalHeaders(const Darabonba::Http::Header &headers);

    static string
    getCanonicalResource(const string &path,
                         const map<string, string> &query);

    static void processObject(const Darabonba::Json &obj, string key,
                              map<string, string> &out);

    static int64_t getTimeLeft(const map<string, string>& headers, const string& key);

    static void exceptStream(json &data);

    template <typename T>
    static bool isStreamPtr(uintptr_t ptr_value) {
      auto ptr = reinterpret_cast<std::shared_ptr<T>*>(ptr_value);
      return ptr && dynamic_cast<T*>(ptr->get());
    }
  };

} // namespace Alibabacloud
} // namespace OpenApi
} // namespace Utils
#endif
