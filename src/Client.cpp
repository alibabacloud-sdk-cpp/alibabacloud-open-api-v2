#include <darabonba/Core.hpp>
#include <alibabacloud/Openapi.hpp>
#include <alibabacloud/Utils.hpp>
#include <alibabacloud/credential/Credential.hpp>
#include <darabonba/Runtime.hpp>
#include <darabonba/policy/Retry.hpp>
#include <darabonba/Exception.hpp>
#include <darabonba/Convert.hpp>
#include <map>
#include <darabonba/Stream.hpp>
#include <darabonba/http/Form.hpp>
#include <darabonba/Bytes.hpp>
#include <darabonba/XML.hpp>
#include <alibabacloud/gateway/SPI.hpp>
using namespace std;
using json = nlohmann::json;
using namespace AlibabaCloud::OpenApi;
using namespace AlibabaCloud::Gateway;
using namespace AlibabaCloud::Gateway::Models;
using namespace AlibabaCloud::Credential::Models;
using namespace AlibabaCloud::OpenApi::Exceptions;
using namespace AlibabaCloud::OpenApi::Utils::Models;
using CredentialClient = AlibabaCloud::Credential::Client;
namespace AlibabaCloud
{
namespace OpenApi
{

/**
* Init client with Config
* @param config config contains the necessary information to create a client
*/
AlibabaCloud::OpenApi::Client::Client(AlibabaCloud::OpenApi::Utils::Models::Config &config){
  if (config.empty()) {
    throw ClientException(json({
                                   {"code" , "ParameterMissing"},
                                   {"message" , "'config' can not be unset"}
                               }));
  }

  if ((!!config.hasAccessKeyId() && config.accessKeyId() != "") && (!!config.hasAccessKeySecret() && config.accessKeySecret() != "")) {
    if (!!config.hasSecurityToken() && config.securityToken() != "") {
      config.setType("sts");
    } else {
      config.setType("access_key");
    }

    AlibabaCloud::Credential::Models::Config credentialConfig = AlibabaCloud::Credential::Models::Config(json({
                                                                                                                  {"accessKeyId" , config.accessKeyId()},
                                                                                                                  {"type" , config.type()},
                                                                                                                  {"accessKeySecret" , config.accessKeySecret()}
                                                                                                              }));
    credentialConfig.setSecurityToken(config.securityToken());
    this->_credential = make_shared<CredentialClient>(credentialConfig);
  } else if (!!config.hasBearerToken() && config.bearerToken() != "") {
    AlibabaCloud::Credential::Models::Config cc = AlibabaCloud::Credential::Models::Config(json({
                                                                                                    {"type" , "bearer"},
                                                                                                    {"bearerToken" , config.bearerToken()}
                                                                                                }));
    this->_credential = make_shared<CredentialClient>(cc);
  } else if (!!config.hasCredential()) {
    this->_credential = config.credential();
  }

  this->_endpoint = config.endpoint();
  this->_endpointType = config.endpointType();
  this->_network = config.network();
  this->_suffix = config.suffix();
  this->_protocol = config.protocol();
  this->_method = config.method();
  this->_regionId = config.regionId();
  this->_userAgent = config.userAgent();
  this->_readTimeout = config.readTimeout();
  this->_connectTimeout = config.connectTimeout();
  this->_httpProxy = config.httpProxy();
  this->_httpsProxy = config.httpsProxy();
  this->_noProxy = config.noProxy();
  this->_socks5Proxy = config.socks5Proxy();
  this->_socks5NetWork = config.socks5NetWork();
  this->_maxIdleConns = config.maxIdleConns();
  this->_signatureVersion = config.signatureVersion();
  this->_signatureAlgorithm = config.signatureAlgorithm();
  this->_globalParameters = config.globalParameters();
  this->_key = config.key();
  this->_cert = config.cert();
  this->_ca = config.ca();
  this->_disableHttp2 = config.disableHttp2();
  this->_retryOptions = config.retryOptions();
  this->_tlsMinVersion = config.tlsMinVersion();
}


Darabonba::Json Client::doRPCRequest(const string &action, const string &version, const string &protocol, const string &method, const string &authType, const string &bodyType, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  Darabonba::RuntimeOptions runtime_(json({
                                              {"key", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.key(), _key))},
                                              {"cert", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.cert(), _cert))},
                                              {"ca", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.ca(), _ca))},
                                              {"readTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.readTimeout(), _readTimeout))},
                                              {"connectTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.connectTimeout(), _connectTimeout))},
                                              {"httpProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpProxy(), _httpProxy))},
                                              {"httpsProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpsProxy(), _httpsProxy))},
                                              {"noProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.noProxy(), _noProxy))},
                                              {"socks5Proxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5Proxy(), _socks5Proxy))},
                                              {"socks5NetWork", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5NetWork(), _socks5NetWork))},
                                              {"maxIdleConns", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.maxIdleConns(), _maxIdleConns))},
                                              {"retryOptions", _retryOptions},
                                              {"ignoreSSL", runtime.ignoreSSL()},
                                              {"tlsMinVersion", _tlsMinVersion}
                                          }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
                                                            {"retriesAttempted" , _retriesAttempted}
                                                        });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      request_.setProtocol(Darabonba::Convert::stringVal(Darabonba::defaultVal(_protocol, protocol)));
      request_.setMethod(method);
      request_.setPathname("/");
      map<string, string> globalQueries = {};
      map<string, string> globalHeaders = {};
      if (!Darabonba::isNull(_globalParameters)) {
        GlobalParameters globalParams = _globalParameters;
        if (!!globalParams.hasQueries()) {
          globalQueries = globalParams.queries();
        }

        if (!!globalParams.hasHeaders()) {
          globalHeaders = globalParams.headers();
        }

      }

      map<string, string> extendsHeaders = {};
      map<string, string> extendsQueries = {};
      if (!!runtime.hasExtendsParameters()) {
        Darabonba::ExtendsParameters extendsParameters = runtime.extendsParameters();
        if (!!extendsParameters.hasHeaders()) {
          extendsHeaders = extendsParameters.headers();
        }

        if (!!extendsParameters.hasQueries()) {
          extendsQueries = extendsParameters.queries();
        }

      }

      request_.setQuery(Darabonba::Core::merge(json({
                                                        {"Action" , action},
                                                        {"Format" , "json"},
                                                        {"Version" , version},
                                                        {"Timestamp" , Utils::Utils::getTimestamp()},
                                                        {"SignatureNonce" , Utils::Utils::getNonce()}
                                                    }),
                                               globalQueries,
                                               extendsQueries,
                                               request.query()
      ));
      map<string, string> headers = getRpcHeaders();
      if (Darabonba::isNull(headers)) {
        // endpoint is setted in product client
        request_.setHeaders(Darabonba::Core::merge(json({
                                                            {"host" , _endpoint},
                                                            {"x-acs-version" , version},
                                                            {"x-acs-action" , action},
                                                            {"user-agent" , Utils::Utils::getUserAgent(_userAgent)}
                                                        }),
                                                   globalHeaders,
                                                   extendsHeaders,
                                                   request.headers()
        ));
      } else {
        request_.setHeaders(Darabonba::Core::merge(json({
                                                            {"host" , _endpoint},
                                                            {"x-acs-version" , version},
                                                            {"x-acs-action" , action},
                                                            {"user-agent" , Utils::Utils::getUserAgent(_userAgent)}
                                                        }),
                                                   globalHeaders,
                                                   extendsHeaders,
                                                   request.headers(),
                                                   headers
        ));
      }

      if (!!request.hasBody()) {
        json m = json(request.body());
        json tmp = json(Utils::Utils::query(m));
        request_.setBody(Darabonba::Stream::toReadable(Darabonba::Http::Form::toFormString(tmp)));
        request_.addHeader("content-type", "application/x-www-form-urlencoded");
      }

      if (authType != "Anonymous") {
        if (Darabonba::isNull(_credential)) {
          throw ClientException(json({
                                         {"code" , DARA_STRING_TEMPLATE("InvalidCredentials")},
                                         {"message" , DARA_STRING_TEMPLATE("Please set up the credentials correctly. If you are setting them through environment variables, please ensure that ALIBABA_CLOUD_ACCESS_KEY_ID and ALIBABA_CLOUD_ACCESS_KEY_SECRET are set correctly. See https://help.aliyun.com/zh/sdk/developer-reference/configure-the-alibaba-cloud-accesskey-environment-variable-on-linux-macos-and-windows-systems for more details.")}
                                     }));
        }

        CredentialModel credentialModel = _credential->getCredential();
        if (!!credentialModel.hasProviderName()) {
          request_.addHeader("x-acs-credentials-provider", credentialModel.providerName());
        }

        string credentialType = credentialModel.type();
        if (credentialType == "bearer") {
          string bearerToken = credentialModel.bearerToken();
          request_.addQuery("BearerToken", bearerToken);
          request_.addQuery("SignatureType", "BEARERTOKEN");
        } else {
          string accessKeyId = credentialModel.accessKeyId();
          string accessKeySecret = credentialModel.accessKeySecret();
          string securityToken = credentialModel.securityToken();
          if (!Darabonba::isNull(securityToken) && securityToken != "") {
            request_.addQuery("SecurityToken", securityToken);
          }

          request_.addQuery("SignatureMethod", "HMAC-SHA1");
          request_.addQuery("SignatureVersion", "1.0");
          request_.addQuery("AccessKeyId", accessKeyId);
          json t = nullptr;
          if (!!request.hasBody()) {
            t = json(request.body());
          }

          map<string, string> signedParam = Darabonba::Core::merge(request_.query(),
                                                                   Utils::Utils::query(t)
          );
          request_.addQuery("Signature", Utils::Utils::getRPCSignature(signedParam, request_.method(), accessKeySecret));
        }

      }

      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      if ((response_->statusCode() >= 400) && (response_->statusCode() < 600)) {
        Darabonba::Json _res = Darabonba::Stream::readAsJSON(response_->body());
        json err = json(_res);
        Darabonba::Json requestId = Darabonba::defaultVal(err["RequestId"], err["requestId"]);
        Darabonba::Json code = Darabonba::defaultVal(err["Code"], err["code"]);
        if ((DARA_STRING_TEMPLATE("" , code) == "Throttling") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.User") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.Api")) {
          throw ThrottlingException(json({
                                             {"statusCode" , response_->statusCode()},
                                             {"code" , DARA_STRING_TEMPLATE("" , code)},
                                             {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                             {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                             {"retryAfter" , Utils::Utils::getThrottlingTimeLeft(response_->headers())},
                                             {"data" , err},
                                             {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                         }));
        } else if ((response_->statusCode() >= 400) && (response_->statusCode() < 500)) {
          throw ClientException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"accessDeniedDetail" , getAccessDeniedDetail(err)},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        } else {
          throw ServerException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        }

      }

      if (bodyType == "binary") {
        json resp = json({
                             {"body" , response_->body()},
                             {"headers" , response_->headers()},
                             {"statusCode" , response_->statusCode()}
                         });
        return resp;
      } else if (bodyType == "byte") {
        Darabonba::Bytes byt = Darabonba::Stream::readAsBytes(response_->body());
        return json({
                        {"body" , byt},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "string") {
        string _str = Darabonba::Stream::readAsString(response_->body());
        return json({
                        {"body" , _str},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "json") {
        Darabonba::Json obj = Darabonba::Stream::readAsJSON(response_->body());
        json res = json(obj);
        return json({
                        {"body" , res},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "array") {
        Darabonba::Json arr = Darabonba::Stream::readAsJSON(response_->body());
        return json({
                        {"body" , arr},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else {
        return json({
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      }

    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
                                                                {"retriesAttempted" , _retriesAttempted},
                                                                {"lastRequest" , _lastRequest},
                                                                {"lastResponse" , _lastResponse},
                                                                {"exception" , ex},
                                                            }));
      continue;
    }
  }

  throw *_context.exception();
}

Darabonba::Json Client::doROARequest(const string &action, const string &version, const string &protocol, const string &method, const string &authType, const string &pathname, const string &bodyType, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  Darabonba::RuntimeOptions runtime_(json({
                                              {"key", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.key(), _key))},
                                              {"cert", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.cert(), _cert))},
                                              {"ca", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.ca(), _ca))},
                                              {"readTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.readTimeout(), _readTimeout))},
                                              {"connectTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.connectTimeout(), _connectTimeout))},
                                              {"httpProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpProxy(), _httpProxy))},
                                              {"httpsProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpsProxy(), _httpsProxy))},
                                              {"noProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.noProxy(), _noProxy))},
                                              {"socks5Proxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5Proxy(), _socks5Proxy))},
                                              {"socks5NetWork", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5NetWork(), _socks5NetWork))},
                                              {"maxIdleConns", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.maxIdleConns(), _maxIdleConns))},
                                              {"retryOptions", _retryOptions},
                                              {"ignoreSSL", runtime.ignoreSSL()},
                                              {"tlsMinVersion", _tlsMinVersion}
                                          }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
                                                            {"retriesAttempted" , _retriesAttempted}
                                                        });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      request_.setProtocol(Darabonba::Convert::stringVal(Darabonba::defaultVal(_protocol, protocol)));
      request_.setMethod(method);
      request_.setPathname(pathname);
      map<string, string> globalQueries = {};
      map<string, string> globalHeaders = {};
      if (!Darabonba::isNull(_globalParameters)) {
        GlobalParameters globalParams = _globalParameters;
        if (!!globalParams.hasQueries()) {
          globalQueries = globalParams.queries();
        }

        if (!!globalParams.hasHeaders()) {
          globalHeaders = globalParams.headers();
        }

      }

      map<string, string> extendsHeaders = {};
      map<string, string> extendsQueries = {};
      if (!!runtime.hasExtendsParameters()) {
        Darabonba::ExtendsParameters extendsParameters = runtime.extendsParameters();
        if (!!extendsParameters.hasHeaders()) {
          extendsHeaders = extendsParameters.headers();
        }

        if (!!extendsParameters.hasQueries()) {
          extendsQueries = extendsParameters.queries();
        }

      }

      request_.setHeaders(Darabonba::Core::merge(json({
                                                          {"date" , Utils::Utils::getDateUTCString()},
                                                          {"host" , _endpoint},
                                                          {"accept" , "application/json"},
                                                          {"x-acs-signature-nonce" , Utils::Utils::getNonce()},
                                                          {"x-acs-signature-method" , "HMAC-SHA1"},
                                                          {"x-acs-signature-version" , "1.0"},
                                                          {"x-acs-version" , version},
                                                          {"x-acs-action" , action},
                                                          {"user-agent" , Utils::Utils::getUserAgent(_userAgent)}
                                                      }),
                                                 globalHeaders,
                                                 extendsHeaders,
                                                 request.headers()
      ));
      if (!!request.hasBody()) {
        request_.setBody(Darabonba::Stream::toReadable(json(request.body()).dump()));
        request_.addHeader("content-type", "application/json; charset=utf-8");
      }

      request_.setQuery(Darabonba::Core::merge(globalQueries,
                                               extendsQueries
      ));
      if (!!request.hasQuery()) {
        request_.setQuery(Darabonba::Core::merge(request_.query(),
                                                 request.query()
        ));
      }

      if (authType != "Anonymous") {
        if (Darabonba::isNull(_credential)) {
          throw ClientException(json({
                                         {"code" , DARA_STRING_TEMPLATE("InvalidCredentials")},
                                         {"message" , DARA_STRING_TEMPLATE("Please set up the credentials correctly. If you are setting them through environment variables, please ensure that ALIBABA_CLOUD_ACCESS_KEY_ID and ALIBABA_CLOUD_ACCESS_KEY_SECRET are set correctly. See https://help.aliyun.com/zh/sdk/developer-reference/configure-the-alibaba-cloud-accesskey-environment-variable-on-linux-macos-and-windows-systems for more details.")}
                                     }));
        }

        CredentialModel credentialModel = _credential->getCredential();
        if (!!credentialModel.hasProviderName()) {
          request_.addHeader("x-acs-credentials-provider", credentialModel.providerName());
        }

        string credentialType = credentialModel.type();
        if (credentialType == "bearer") {
          string bearerToken = credentialModel.bearerToken();
          request_.addHeader("x-acs-bearer-token", bearerToken);
          request_.addHeader("x-acs-signature-type", "BEARERTOKEN");
        } else {
          string accessKeyId = credentialModel.accessKeyId();
          string accessKeySecret = credentialModel.accessKeySecret();
          string securityToken = credentialModel.securityToken();
          if (!Darabonba::isNull(securityToken) && securityToken != "") {
            request_.addHeader("x-acs-accesskey-id", accessKeyId);
            request_.addHeader("x-acs-security-token", securityToken);
          }

          string stringToSign = Utils::Utils::getStringToSign(request_);
          request_.addHeader("authorization", DARA_STRING_TEMPLATE("acs " , accessKeyId , ":" , Utils::Utils::getROASignature(stringToSign, accessKeySecret)));
        }

      }

      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      if (response_->statusCode() == 204) {
        return json({
                        {"headers" , response_->headers()}
                    });
      }

      if ((response_->statusCode() >= 400) && (response_->statusCode() < 600)) {
        Darabonba::Json _res = Darabonba::Stream::readAsJSON(response_->body());
        json err = json(_res);
        string requestId = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["RequestId"], err["requestId"]));
        requestId = Darabonba::Convert::stringVal(Darabonba::defaultVal(requestId, err["requestid"]));
        string code = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["Code"], err["code"]));
        if ((DARA_STRING_TEMPLATE("" , code) == "Throttling") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.User") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.Api")) {
          throw ThrottlingException(json({
                                             {"statusCode" , response_->statusCode()},
                                             {"code" , DARA_STRING_TEMPLATE("" , code)},
                                             {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                             {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                             {"retryAfter" , Utils::Utils::getThrottlingTimeLeft(response_->headers())},
                                             {"data" , err},
                                             {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                         }));
        } else if ((response_->statusCode() >= 400) && (response_->statusCode() < 500)) {
          throw ClientException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"accessDeniedDetail" , getAccessDeniedDetail(err)},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        } else {
          throw ServerException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        }

      }

      if (bodyType == "binary") {
        json resp = json({
                             {"body" , response_->body()},
                             {"headers" , response_->headers()},
                             {"statusCode" , response_->statusCode()}
                         });
        return resp;
      } else if (bodyType == "byte") {
        Darabonba::Bytes byt = Darabonba::Stream::readAsBytes(response_->body());
        return json({
                        {"body" , byt},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "string") {
        string _str = Darabonba::Stream::readAsString(response_->body());
        return json({
                        {"body" , _str},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "json") {
        Darabonba::Json obj = Darabonba::Stream::readAsJSON(response_->body());
        json res = json(obj);
        return json({
                        {"body" , res},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "array") {
        Darabonba::Json arr = Darabonba::Stream::readAsJSON(response_->body());
        return json({
                        {"body" , arr},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else {
        return json({
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      }

    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
                                                                {"retriesAttempted" , _retriesAttempted},
                                                                {"lastRequest" , _lastRequest},
                                                                {"lastResponse" , _lastResponse},
                                                                {"exception" , ex},
                                                            }));
      continue;
    }
  }

  throw *_context.exception();
}

Darabonba::Json Client::doROARequestWithForm(const string &action, const string &version, const string &protocol, const string &method, const string &authType, const string &pathname, const string &bodyType, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  Darabonba::RuntimeOptions runtime_(json({
                                              {"key", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.key(), _key))},
                                              {"cert", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.cert(), _cert))},
                                              {"ca", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.ca(), _ca))},
                                              {"readTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.readTimeout(), _readTimeout))},
                                              {"connectTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.connectTimeout(), _connectTimeout))},
                                              {"httpProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpProxy(), _httpProxy))},
                                              {"httpsProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpsProxy(), _httpsProxy))},
                                              {"noProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.noProxy(), _noProxy))},
                                              {"socks5Proxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5Proxy(), _socks5Proxy))},
                                              {"socks5NetWork", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5NetWork(), _socks5NetWork))},
                                              {"maxIdleConns", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.maxIdleConns(), _maxIdleConns))},
                                              {"retryOptions", _retryOptions},
                                              {"ignoreSSL", runtime.ignoreSSL()},
                                              {"tlsMinVersion", _tlsMinVersion}
                                          }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
                                                            {"retriesAttempted" , _retriesAttempted}
                                                        });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      request_.setProtocol(Darabonba::Convert::stringVal(Darabonba::defaultVal(_protocol, protocol)));
      request_.setMethod(method);
      request_.setPathname(pathname);
      map<string, string> globalQueries = {};
      map<string, string> globalHeaders = {};
      if (!Darabonba::isNull(_globalParameters)) {
        GlobalParameters globalParams = _globalParameters;
        if (!!globalParams.hasQueries()) {
          globalQueries = globalParams.queries();
        }

        if (!!globalParams.hasHeaders()) {
          globalHeaders = globalParams.headers();
        }

      }

      map<string, string> extendsHeaders = {};
      map<string, string> extendsQueries = {};
      if (!!runtime.hasExtendsParameters()) {
        Darabonba::ExtendsParameters extendsParameters = runtime.extendsParameters();
        if (!!extendsParameters.hasHeaders()) {
          extendsHeaders = extendsParameters.headers();
        }

        if (!!extendsParameters.hasQueries()) {
          extendsQueries = extendsParameters.queries();
        }

      }

      request_.setHeaders(Darabonba::Core::merge(json({
                                                          {"date" , Utils::Utils::getDateUTCString()},
                                                          {"host" , _endpoint},
                                                          {"accept" , "application/json"},
                                                          {"x-acs-signature-nonce" , Utils::Utils::getNonce()},
                                                          {"x-acs-signature-method" , "HMAC-SHA1"},
                                                          {"x-acs-signature-version" , "1.0"},
                                                          {"x-acs-version" , version},
                                                          {"x-acs-action" , action},
                                                          {"user-agent" , Utils::Utils::getUserAgent(_userAgent)}
                                                      }),
                                                 globalHeaders,
                                                 extendsHeaders,
                                                 request.headers()
      ));
      if (!!request.hasBody()) {
        json m = json(request.body());
        request_.setBody(Darabonba::Stream::toReadable(Utils::Utils::toForm(m)));
        request_.addHeader("content-type", "application/x-www-form-urlencoded");
      }

      request_.setQuery(Darabonba::Core::merge(globalQueries,
                                               extendsQueries
      ));
      if (!!request.hasQuery()) {
        request_.setQuery(Darabonba::Core::merge(request_.query(),
                                                 request.query()
        ));
      }

      if (authType != "Anonymous") {
        if (Darabonba::isNull(_credential)) {
          throw ClientException(json({
                                         {"code" , DARA_STRING_TEMPLATE("InvalidCredentials")},
                                         {"message" , DARA_STRING_TEMPLATE("Please set up the credentials correctly. If you are setting them through environment variables, please ensure that ALIBABA_CLOUD_ACCESS_KEY_ID and ALIBABA_CLOUD_ACCESS_KEY_SECRET are set correctly. See https://help.aliyun.com/zh/sdk/developer-reference/configure-the-alibaba-cloud-accesskey-environment-variable-on-linux-macos-and-windows-systems for more details.")}
                                     }));
        }

        CredentialModel credentialModel = _credential->getCredential();
        if (!!credentialModel.hasProviderName()) {
          request_.addHeader("x-acs-credentials-provider", credentialModel.providerName());
        }

        string credentialType = credentialModel.type();
        if (credentialType == "bearer") {
          string bearerToken = credentialModel.bearerToken();
          request_.addHeader("x-acs-bearer-token", bearerToken);
          request_.addHeader("x-acs-signature-type", "BEARERTOKEN");
        } else {
          string accessKeyId = credentialModel.accessKeyId();
          string accessKeySecret = credentialModel.accessKeySecret();
          string securityToken = credentialModel.securityToken();
          if (!Darabonba::isNull(securityToken) && securityToken != "") {
            request_.addHeader("x-acs-accesskey-id", accessKeyId);
            request_.addHeader("x-acs-security-token", securityToken);
          }

          string stringToSign = Utils::Utils::getStringToSign(request_);
          request_.addHeader("authorization", DARA_STRING_TEMPLATE("acs " , accessKeyId , ":" , Utils::Utils::getROASignature(stringToSign, accessKeySecret)));
        }

      }

      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      if (response_->statusCode() == 204) {
        return json({
                        {"headers" , response_->headers()}
                    });
      }

      if ((response_->statusCode() >= 400) && (response_->statusCode() < 600)) {
        Darabonba::Json _res = Darabonba::Stream::readAsJSON(response_->body());
        json err = json(_res);
        string requestId = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["RequestId"], err["requestId"]));
        string code = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["Code"], err["code"]));
        if ((DARA_STRING_TEMPLATE("" , code) == "Throttling") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.User") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.Api")) {
          throw ThrottlingException(json({
                                             {"statusCode" , response_->statusCode()},
                                             {"code" , DARA_STRING_TEMPLATE("" , code)},
                                             {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                             {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                             {"retryAfter" , Utils::Utils::getThrottlingTimeLeft(response_->headers())},
                                             {"data" , err},
                                             {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                         }));
        } else if ((response_->statusCode() >= 400) && (response_->statusCode() < 500)) {
          throw ClientException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"accessDeniedDetail" , getAccessDeniedDetail(err)},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        } else {
          throw ServerException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        }

      }

      if (bodyType == "binary") {
        json resp = json({
                             {"body" , response_->body()},
                             {"headers" , response_->headers()},
                             {"statusCode" , response_->statusCode()}
                         });
        return resp;
      } else if (bodyType == "byte") {
        Darabonba::Bytes byt = Darabonba::Stream::readAsBytes(response_->body());
        return json({
                        {"body" , byt},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "string") {
        string _str = Darabonba::Stream::readAsString(response_->body());
        return json({
                        {"body" , _str},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "json") {
        Darabonba::Json obj = Darabonba::Stream::readAsJSON(response_->body());
        json res = json(obj);
        return json({
                        {"body" , res},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (bodyType == "array") {
        Darabonba::Json arr = Darabonba::Stream::readAsJSON(response_->body());
        return json({
                        {"body" , arr},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else {
        return json({
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      }

    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
                                                                {"retriesAttempted" , _retriesAttempted},
                                                                {"lastRequest" , _lastRequest},
                                                                {"lastResponse" , _lastResponse},
                                                                {"exception" , ex},
                                                            }));
      continue;
    }
  }

  throw *_context.exception();
}

Darabonba::Json Client::doRequest(const Params &params, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  Darabonba::RuntimeOptions runtime_(json({
                                              {"key", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.key(), _key))},
                                              {"cert", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.cert(), _cert))},
                                              {"ca", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.ca(), _ca))},
                                              {"readTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.readTimeout(), _readTimeout))},
                                              {"connectTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.connectTimeout(), _connectTimeout))},
                                              {"httpProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpProxy(), _httpProxy))},
                                              {"httpsProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpsProxy(), _httpsProxy))},
                                              {"noProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.noProxy(), _noProxy))},
                                              {"socks5Proxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5Proxy(), _socks5Proxy))},
                                              {"socks5NetWork", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5NetWork(), _socks5NetWork))},
                                              {"maxIdleConns", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.maxIdleConns(), _maxIdleConns))},
                                              {"retryOptions", _retryOptions},
                                              {"ignoreSSL", runtime.ignoreSSL()},
                                              {"tlsMinVersion", _tlsMinVersion}
                                          }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
                                                            {"retriesAttempted" , _retriesAttempted}
                                                        });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      request_.setProtocol(Darabonba::Convert::stringVal(Darabonba::defaultVal(_protocol, params.protocol())));
      request_.setMethod(params.method());
      request_.setPathname(params.pathname());
      map<string, string> globalQueries = {};
      map<string, string> globalHeaders = {};
      if (!Darabonba::isNull(_globalParameters)) {
        GlobalParameters globalParams = _globalParameters;
        if (!!globalParams.hasQueries()) {
          globalQueries = globalParams.queries();
        }

        if (!!globalParams.hasHeaders()) {
          globalHeaders = globalParams.headers();
        }

      }

      map<string, string> extendsHeaders = {};
      map<string, string> extendsQueries = {};
      if (!!runtime.hasExtendsParameters()) {
        Darabonba::ExtendsParameters extendsParameters = runtime.extendsParameters();
        if (!!extendsParameters.hasHeaders()) {
          extendsHeaders = extendsParameters.headers();
        }

        if (!!extendsParameters.hasQueries()) {
          extendsQueries = extendsParameters.queries();
        }

      }

      request_.setQuery(Darabonba::Core::merge(globalQueries,
                                               extendsQueries,
                                               request.query()
      ));
      // endpoint is setted in product client
      request_.setHeaders(Darabonba::Core::merge(json({
                                                          {"host" , _endpoint},
                                                          {"x-acs-version" , params.version()},
                                                          {"x-acs-action" , params.action()},
                                                          {"user-agent" , Utils::Utils::getUserAgent(_userAgent)},
                                                          {"x-acs-date" , Utils::Utils::getTimestamp()},
                                                          {"x-acs-signature-nonce" , Utils::Utils::getNonce()},
                                                          {"accept" , "application/json"}
                                                      }),
                                                 globalHeaders,
                                                 extendsHeaders,
                                                 request.headers()
      ));
      if (params.style() == "RPC") {
        map<string, string> headers = getRpcHeaders();
        if (!Darabonba::isNull(headers)) {
          request_.setHeaders(Darabonba::Core::merge(request_.headers(),
                                                     headers
          ));
        }

      }

      string signatureAlgorithm = Darabonba::Convert::stringVal(Darabonba::defaultVal(_signatureAlgorithm, "ACS3-HMAC-SHA256"));
      Darabonba::Bytes hashedRequestPayload = Utils::Utils::hash(Darabonba::BytesUtil::from("", "utf-8"), signatureAlgorithm);
      if (!!request.hasStream()) {
        Darabonba::Bytes tmp = Darabonba::Stream::readAsBytes(request.stream());
        hashedRequestPayload = Utils::Utils::hash(tmp, signatureAlgorithm);
        request_.setBody(Darabonba::Stream::toReadable(tmp));
        request_.addHeader("content-type", "application/octet-stream");
      } else {
        if (!!request.hasBody()) {
          if (params.reqBodyType() == "byte") {
            Darabonba::Bytes byteObj = Darabonba::BytesUtil::toBytes(request.body());
            hashedRequestPayload = Utils::Utils::hash(byteObj, signatureAlgorithm);
            request_.setBody(Darabonba::Stream::toReadable(byteObj));
          } else if (params.reqBodyType() == "json") {
            string jsonObj = json(request.body()).dump();
            hashedRequestPayload = Utils::Utils::hash(Darabonba::BytesUtil::toBytes(jsonObj), signatureAlgorithm);
            request_.setBody(Darabonba::Stream::toReadable(jsonObj));
            request_.addHeader("content-type", "application/json; charset=utf-8");
          } else {
            json m = json(request.body());
            string formObj = Utils::Utils::toForm(m);
            hashedRequestPayload = Utils::Utils::hash(Darabonba::BytesUtil::toBytes(formObj), signatureAlgorithm);
            request_.setBody(Darabonba::Stream::toReadable(formObj));
            request_.addHeader("content-type", "application/x-www-form-urlencoded");
          }

        }

      }

      request_.addHeader("x-acs-content-sha256", Darabonba::Encode::Encoder::hexEncode(hashedRequestPayload));
      if (params.authType() != "Anonymous") {
        if (Darabonba::isNull(_credential)) {
          throw ClientException(json({
                                         {"code" , DARA_STRING_TEMPLATE("InvalidCredentials")},
                                         {"message" , DARA_STRING_TEMPLATE("Please set up the credentials correctly. If you are setting them through environment variables, please ensure that ALIBABA_CLOUD_ACCESS_KEY_ID and ALIBABA_CLOUD_ACCESS_KEY_SECRET are set correctly. See https://help.aliyun.com/zh/sdk/developer-reference/configure-the-alibaba-cloud-accesskey-environment-variable-on-linux-macos-and-windows-systems for more details.")}
                                     }));
        }

        CredentialModel credentialModel = _credential->getCredential();
        if (!!credentialModel.hasProviderName()) {
          request_.addHeader("x-acs-credentials-provider", credentialModel.providerName());
        }

        string authType = credentialModel.type();
        if (authType == "bearer") {
          string bearerToken = credentialModel.bearerToken();
          request_.addHeader("x-acs-bearer-token", bearerToken);
          if (params.style() == "RPC") {
            request_.addQuery("SignatureType", "BEARERTOKEN");
          } else {
            request_.addHeader("x-acs-signature-type", "BEARERTOKEN");
          }

        } else {
          string accessKeyId = credentialModel.accessKeyId();
          string accessKeySecret = credentialModel.accessKeySecret();
          string securityToken = credentialModel.securityToken();
          if (!Darabonba::isNull(securityToken) && securityToken != "") {
            request_.addHeader("x-acs-accesskey-id", accessKeyId);
            request_.addHeader("x-acs-security-token", securityToken);
          }

          request_.addHeader("Authorization", Utils::Utils::getAuthorization(request_, signatureAlgorithm, Darabonba::Encode::Encoder::hexEncode(hashedRequestPayload), accessKeyId, accessKeySecret));
        }

      }

      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      if ((response_->statusCode() >= 400) && (response_->statusCode() < 600)) {
        json err = {};
        if (!Darabonba::isNull(response_->headers().at("content-type")) && response_->headers().at("content-type") == "text/xml;charset=utf-8") {
          string _str = Darabonba::Stream::readAsString(response_->body());
          json respMap = Darabonba::XML::parseXml(_str, nullptr);
          err = json(respMap["Error"]);
        } else {
          Darabonba::Json _res = Darabonba::Stream::readAsJSON(response_->body());
          err = json(_res);
        }

        string requestId = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["RequestId"], err["requestId"]));
        string code = Darabonba::Convert::stringVal(Darabonba::defaultVal(err["Code"], err["code"]));
        if ((DARA_STRING_TEMPLATE("" , code) == "Throttling") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.User") || (DARA_STRING_TEMPLATE("" , code) == "Throttling.Api")) {
          throw ThrottlingException(json({
                                             {"statusCode" , response_->statusCode()},
                                             {"code" , DARA_STRING_TEMPLATE("" , code)},
                                             {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                             {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                             {"retryAfter" , Utils::Utils::getThrottlingTimeLeft(response_->headers())},
                                             {"data" , err},
                                             {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                         }));
        } else if ((response_->statusCode() >= 400) && (response_->statusCode() < 500)) {
          throw ClientException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"accessDeniedDetail" , getAccessDeniedDetail(err)},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        } else {
          throw ServerException(json({
                                         {"statusCode" , response_->statusCode()},
                                         {"code" , DARA_STRING_TEMPLATE("" , code)},
                                         {"message" , DARA_STRING_TEMPLATE("code: " , response_->statusCode() , ", " , Darabonba::defaultVal(err["Message"], err["message"]) , " request id: " , requestId)},
                                         {"description" , DARA_STRING_TEMPLATE("" , Darabonba::defaultVal(err["Description"], err["description"]))},
                                         {"data" , err},
                                         {"requestId" , DARA_STRING_TEMPLATE("" , requestId)}
                                     }));
        }

      }

      if (params.bodyType() == "binary") {
        json resp = json({
                             {"body" , response_->body()},
                             {"headers" , response_->headers()},
                             {"statusCode" , response_->statusCode()}
                         });
        return resp;
      } else if (params.bodyType() == "byte") {
        Darabonba::Bytes byt = Darabonba::Stream::readAsBytes(response_->body());
        return json({
                        {"body" , byt},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (params.bodyType() == "string") {
        string respStr = Darabonba::Stream::readAsString(response_->body());
        return json({
                        {"body" , respStr},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (params.bodyType() == "json") {
        Darabonba::Json obj = Darabonba::Stream::readAsJSON(response_->body());
        json res = json(obj);
        return json({
                        {"body" , res},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else if (params.bodyType() == "array") {
        Darabonba::Json arr = Darabonba::Stream::readAsJSON(response_->body());
        return json({
                        {"body" , arr},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      } else {
        string anything = Darabonba::Stream::readAsString(response_->body());
        return json({
                        {"body" , anything},
                        {"headers" , response_->headers()},
                        {"statusCode" , response_->statusCode()}
                    });
      }

    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
                                                                {"retriesAttempted" , _retriesAttempted},
                                                                {"lastRequest" , _lastRequest},
                                                                {"lastResponse" , _lastResponse},
                                                                {"exception" , ex},
                                                            }));
      continue;
    }
  }

  throw *_context.exception();
}

Darabonba::Json Client::execute(const Params &params, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  Darabonba::RuntimeOptions runtime_(json({
                                              {"key", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.key(), _key))},
                                              {"cert", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.cert(), _cert))},
                                              {"ca", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.ca(), _ca))},
                                              {"readTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.readTimeout(), _readTimeout))},
                                              {"connectTimeout", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.connectTimeout(), _connectTimeout))},
                                              {"httpProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpProxy(), _httpProxy))},
                                              {"httpsProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.httpsProxy(), _httpsProxy))},
                                              {"noProxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.noProxy(), _noProxy))},
                                              {"socks5Proxy", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5Proxy(), _socks5Proxy))},
                                              {"socks5NetWork", Darabonba::Convert::stringVal(Darabonba::defaultVal(runtime.socks5NetWork(), _socks5NetWork))},
                                              {"maxIdleConns", Darabonba::Convert::int64Val(Darabonba::defaultVal(runtime.maxIdleConns(), _maxIdleConns))},
                                              {"retryOptions", _retryOptions},
                                              {"ignoreSSL", runtime.ignoreSSL()},
                                              {"tlsMinVersion", _tlsMinVersion},
                                              {"disableHttp2", Darabonba::Convert::boolVal(Darabonba::defaultVal(_disableHttp2, false))}
                                          }));

  shared_ptr<Darabonba::Http::Request> _lastRequest = nullptr;
  shared_ptr<Darabonba::Http::MCurlResponse> _lastResponse = nullptr;
  Darabonba::Exception _lastException;
  int _retriesAttempted = 0;
  Darabonba::Policy::RetryPolicyContext _context = json({
                                                            {"retriesAttempted" , _retriesAttempted}
                                                        });
  while (Darabonba::allowRetry(runtime_.retryOptions(), _context)) {
    if (_retriesAttempted > 0) {
      int _backoffTime = Darabonba::getBackoffTime(runtime_.retryOptions(), _context);
      if (_backoffTime > 0) {
        Darabonba::sleep(_backoffTime);
      }
    }
    _retriesAttempted++;
    try {
      Darabonba::Http::Request request_ = Darabonba::Http::Request();
      // spi = new Gateway();//Gateway implements SPI，这一步在产品 SDK 中实例化
      map<string, string> headers = getRpcHeaders();
      map<string, string> globalQueries = {};
      map<string, string> globalHeaders = {};
      if (!Darabonba::isNull(_globalParameters)) {
        GlobalParameters globalParams = _globalParameters;
        if (!!globalParams.hasQueries()) {
          globalQueries = globalParams.queries();
        }

        if (!!globalParams.hasHeaders()) {
          globalHeaders = globalParams.headers();
        }

      }

      map<string, string> extendsHeaders = {};
      map<string, string> extendsQueries = {};
      if (!!runtime.hasExtendsParameters()) {
        Darabonba::ExtendsParameters extendsParameters = runtime.extendsParameters();
        if (!!extendsParameters.hasHeaders()) {
          extendsHeaders = extendsParameters.headers();
        }

        if (!!extendsParameters.hasQueries()) {
          extendsQueries = extendsParameters.queries();
        }

      }

      InterceptorContextRequest requestContext = InterceptorContextRequest(json({
                                                                                    {"headers" , Darabonba::Core::merge(globalHeaders,
                                                                                                                        extendsHeaders,
                                                                                                                        request.headers(),
                                                                                                                        headers
                                                                                    )},
                                                                                    {"query" , Darabonba::Core::merge(globalQueries,
                                                                                                                      extendsQueries,
                                                                                                                      request.query()
                                                                                    )},
                                                                                    {"body" , request.body()},
                                                                                    {"stream" , request.stream()},
                                                                                    {"hostMap" , request.hostMap()},
                                                                                    {"pathname" , params.pathname()},
                                                                                    {"productId" , _productId},
                                                                                    {"action" , params.action()},
                                                                                    {"version" , params.version()},
                                                                                    {"protocol" , Darabonba::Convert::stringVal(Darabonba::defaultVal(_protocol, params.protocol()))},
                                                                                    {"method" , Darabonba::Convert::stringVal(Darabonba::defaultVal(_method, params.method()))},
                                                                                    {"authType" , params.authType()},
                                                                                    {"bodyType" , params.bodyType()},
                                                                                    {"reqBodyType" , params.reqBodyType()},
                                                                                    {"style" , params.style()},
                                                                                    {"credential" , _credential},
                                                                                    {"signatureVersion" , _signatureVersion},
                                                                                    {"signatureAlgorithm" , _signatureAlgorithm},
                                                                                    {"userAgent" , Utils::Utils::getUserAgent(_userAgent)}
                                                                                }));
      InterceptorContextConfiguration configurationContext = InterceptorContextConfiguration(json({
                                                                                                      {"regionId" , _regionId},
                                                                                                      {"endpoint" , Darabonba::Convert::stringVal(Darabonba::defaultVal(request.endpointOverride(), _endpoint))},
                                                                                                      {"endpointRule" , _endpointRule},
                                                                                                      {"endpointMap" , _endpointMap},
                                                                                                      {"endpointType" , _endpointType},
                                                                                                      {"network" , _network},
                                                                                                      {"suffix" , _suffix}
                                                                                                  }));
      InterceptorContext interceptorContext = InterceptorContext(json({
                                                                          {"request" , requestContext},
                                                                          {"configuration" , configurationContext}
                                                                      }));
      AttributeMap attributeMap = AttributeMap();
      // 1. spi.modifyConfiguration(context: SPI.InterceptorContext, attributeMap: SPI.AttributeMap);
      _spi->modifyConfiguration(interceptorContext, attributeMap);
      // 2. spi.modifyRequest(context: SPI.InterceptorContext, attributeMap: SPI.AttributeMap);
      _spi->modifyRequest(interceptorContext, attributeMap);
      request_.setProtocol(interceptorContext.request().protocol());
      request_.setMethod(interceptorContext.request().method());
      request_.setPathname(interceptorContext.request().pathname());
      request_.setQuery(interceptorContext.request().query());
      request_.setBody(interceptorContext.request().stream());
      request_.setHeaders(interceptorContext.request().headers());
      _lastRequest = make_shared<Darabonba::Http::Request>(request_);
      auto futureResp_ = Darabonba::Core::doAction(request_, runtime_);
      shared_ptr<Darabonba::Http::MCurlResponse> response_ = futureResp_.get();
      _lastResponse  = response_;

      InterceptorContextResponse responseContext = InterceptorContextResponse(json({
                                                                                       {"statusCode" , response_->statusCode()},
                                                                                       {"headers" , response_->headers()},
                                                                                       {"body" , response_->body()}
                                                                                   }));
      interceptorContext.setResponse(responseContext);
      // 3. spi.modifyResponse(context: SPI.InterceptorContext, attributeMap: SPI.AttributeMap);
      _spi->modifyResponse(interceptorContext, attributeMap);
      return json({
                      {"headers" , interceptorContext.response().headers()},
                      {"statusCode" , interceptorContext.response().statusCode()},
                      {"body" , interceptorContext.response().deserializedBody()}
                  });
    } catch (const Darabonba::Exception& ex) {
      _context = Darabonba::Policy::RetryPolicyContext(json({
                                                                {"retriesAttempted" , _retriesAttempted},
                                                                {"lastRequest" , _lastRequest},
                                                                {"lastResponse" , _lastResponse},
                                                                {"exception" , ex},
                                                            }));
      continue;
    }
  }

  throw *_context.exception();
}


Darabonba::Json Client::callApi(const Params &params, const OpenApiRequest &request, const Darabonba::RuntimeOptions &runtime) {
  if (params.empty()) {
    throw ClientException(json({
                                   {"code" , "ParameterMissing"},
                                   {"message" , "'params' can not be unset"}
                               }));
  }

  if (Darabonba::isNull(_signatureVersion) || _signatureVersion != "v4") {
    if (Darabonba::isNull(_signatureAlgorithm) || _signatureAlgorithm != "v2") {
      return doRequest(params, request, runtime);
    } else if ((params.style() == "ROA") && (params.reqBodyType() == "json")) {
      return doROARequest(params.action(), params.version(), params.protocol(), params.method(), params.authType(), params.pathname(), params.bodyType(), request, runtime);
    } else if (params.style() == "ROA") {
      return doROARequestWithForm(params.action(), params.version(), params.protocol(), params.method(), params.authType(), params.pathname(), params.bodyType(), request, runtime);
    } else {
      return doRPCRequest(params.action(), params.version(), params.protocol(), params.method(), params.authType(), params.bodyType(), request, runtime);
    }

  } else {
    return execute(params, request, runtime);
  }

}

/**
* Get accesskey id by using credential
* @return accesskey id
*/
string Client::getAccessKeyId() {
  if (Darabonba::isNull(_credential)) {
    return "";
  }

  string accessKeyId = _credential->getAccessKeyId();
  return accessKeyId;
}

/**
* Get accesskey secret by using credential
* @return accesskey secret
*/
string Client::getAccessKeySecret() {
  if (Darabonba::isNull(_credential)) {
    return "";
  }

  string secret = _credential->getAccessKeySecret();
  return secret;
}

/**
* Get security token by using credential
* @return security token
*/
string Client::getSecurityToken() {
  if (Darabonba::isNull(_credential)) {
    return "";
  }

  string token = _credential->getSecurityToken();
  return token;
}

/**
* Get bearer token by credential
* @return bearer token
*/
string Client::getBearerToken() {
  if (Darabonba::isNull(_credential)) {
    return "";
  }

  string token = _credential->getBearerToken();
  return token;
}

/**
* Get credential type by credential
* @return credential type e.g. access_key
*/
string Client::getType() {
  if (Darabonba::isNull(_credential)) {
    return "";
  }

  string authType = _credential->getType();
  return authType;
}

/**
* If the endpointRule and config.endpoint are empty, throw error
* @param config config contains the necessary information to create a client
*/
void Client::checkConfig(const AlibabaCloud::OpenApi::Utils::Models::Config &config) {
  if (Darabonba::isNull(_endpointRule) && !config.hasEndpoint()) {
    throw ClientException(json({
                                   {"code" , "ParameterMissing"},
                                   {"message" , "'config.endpoint' can not be empty"}
                               }));
  }

}

/**
* set gateway client
* @param spi.
*/
void Client::setGatewayClient(const shared_ptr<SPI> &spi) {
  this->_spi = spi;
}

/**
* set RPC header for debug
* @param headers headers for debug, this header can be used only once.
*/
void Client::setRpcHeaders(const map<string, string> &headers) {
  this->_headers = headers;
}

/**
* get RPC header for debug
*/
map<string, string> Client::getRpcHeaders() {
  map<string, string> headers = _headers;
  this->_headers = map<string, string>();
  return headers;
}

json Client::getAccessDeniedDetail(const json &err) {
  json accessDeniedDetail = nullptr;
  if (!!err.contains("AccessDeniedDetail")) {
    json detail1 = json(err["AccessDeniedDetail"]);
    accessDeniedDetail = detail1;
  } else if (!!err.contains("accessDeniedDetail")) {
    json detail2 = json(err["accessDeniedDetail"]);
    accessDeniedDetail = detail2;
  }

  return accessDeniedDetail;
}
} // namespace AlibabaCloud
} // namespace OpenApi