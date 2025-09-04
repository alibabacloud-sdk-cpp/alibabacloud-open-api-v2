// This file is auto-generated, don't edit it. Thanks.
#ifndef ALIBABACLOUD_UTILS_MODELS_CONFIG_HPP_
#define ALIBABACLOUD_UTILS_MODELS_CONFIG_HPP_
#include <darabonba/Core.hpp>
#include <alibabacloud/credential/Credential.hpp>
#include <darabonba/policy/Retry.hpp>
using namespace std;
using json = nlohmann::json;
namespace AlibabaCloud
{
  namespace OpenApi
  {
    namespace Utils
    {
      namespace Models
      {
        /**
         * Model for initing client
         */
        class Config : public Darabonba::Model {
        public:
          friend void to_json(Darabonba::Json& j, const Config& obj) {
            DARABONBA_PTR_TO_JSON(accessKeyId, accessKeyId_);
            DARABONBA_PTR_TO_JSON(accessKeySecret, accessKeySecret_);
            DARABONBA_PTR_TO_JSON(securityToken, securityToken_);
            DARABONBA_PTR_TO_JSON(bearerToken, bearerToken_);
            DARABONBA_PTR_TO_JSON(protocol, protocol_);
            DARABONBA_PTR_TO_JSON(method, method_);
            DARABONBA_PTR_TO_JSON(regionId, regionId_);
            DARABONBA_PTR_TO_JSON(readTimeout, readTimeout_);
            DARABONBA_PTR_TO_JSON(connectTimeout, connectTimeout_);
            DARABONBA_PTR_TO_JSON(httpProxy, httpProxy_);
            DARABONBA_PTR_TO_JSON(httpsProxy, httpsProxy_);
            DARABONBA_TO_JSON(credential, credential_);
            DARABONBA_PTR_TO_JSON(endpoint, endpoint_);
            DARABONBA_PTR_TO_JSON(noProxy, noProxy_);
            DARABONBA_PTR_TO_JSON(maxIdleConns, maxIdleConns_);
            DARABONBA_PTR_TO_JSON(network, network_);
            DARABONBA_PTR_TO_JSON(userAgent, userAgent_);
            DARABONBA_PTR_TO_JSON(suffix, suffix_);
            DARABONBA_PTR_TO_JSON(socks5Proxy, socks5Proxy_);
            DARABONBA_PTR_TO_JSON(socks5NetWork, socks5NetWork_);
            DARABONBA_PTR_TO_JSON(endpointType, endpointType_);
            DARABONBA_PTR_TO_JSON(openPlatformEndpoint, openPlatformEndpoint_);
            DARABONBA_PTR_TO_JSON(type, type_);
            DARABONBA_PTR_TO_JSON(signatureVersion, signatureVersion_);
            DARABONBA_PTR_TO_JSON(signatureAlgorithm, signatureAlgorithm_);
            DARABONBA_PTR_TO_JSON(globalParameters, globalParameters_);
            DARABONBA_PTR_TO_JSON(key, key_);
            DARABONBA_PTR_TO_JSON(cert, cert_);
            DARABONBA_PTR_TO_JSON(ca, ca_);
            DARABONBA_PTR_TO_JSON(disableHttp2, disableHttp2_);
            DARABONBA_PTR_TO_JSON(retryOptions, retryOptions_);
            DARABONBA_PTR_TO_JSON(tlsMinVersion, tlsMinVersion_);
          };
          friend void from_json(const Darabonba::Json& j, Config& obj) {
            DARABONBA_PTR_FROM_JSON(accessKeyId, accessKeyId_);
            DARABONBA_PTR_FROM_JSON(accessKeySecret, accessKeySecret_);
            DARABONBA_PTR_FROM_JSON(securityToken, securityToken_);
            DARABONBA_PTR_FROM_JSON(bearerToken, bearerToken_);
            DARABONBA_PTR_FROM_JSON(protocol, protocol_);
            DARABONBA_PTR_FROM_JSON(method, method_);
            DARABONBA_PTR_FROM_JSON(regionId, regionId_);
            DARABONBA_PTR_FROM_JSON(readTimeout, readTimeout_);
            DARABONBA_PTR_FROM_JSON(connectTimeout, connectTimeout_);
            DARABONBA_PTR_FROM_JSON(httpProxy, httpProxy_);
            DARABONBA_PTR_FROM_JSON(httpsProxy, httpsProxy_);
            DARABONBA_FROM_JSON(credential, credential_);
            DARABONBA_PTR_FROM_JSON(endpoint, endpoint_);
            DARABONBA_PTR_FROM_JSON(noProxy, noProxy_);
            DARABONBA_PTR_FROM_JSON(maxIdleConns, maxIdleConns_);
            DARABONBA_PTR_FROM_JSON(network, network_);
            DARABONBA_PTR_FROM_JSON(userAgent, userAgent_);
            DARABONBA_PTR_FROM_JSON(suffix, suffix_);
            DARABONBA_PTR_FROM_JSON(socks5Proxy, socks5Proxy_);
            DARABONBA_PTR_FROM_JSON(socks5NetWork, socks5NetWork_);
            DARABONBA_PTR_FROM_JSON(endpointType, endpointType_);
            DARABONBA_PTR_FROM_JSON(openPlatformEndpoint, openPlatformEndpoint_);
            DARABONBA_PTR_FROM_JSON(type, type_);
            DARABONBA_PTR_FROM_JSON(signatureVersion, signatureVersion_);
            DARABONBA_PTR_FROM_JSON(signatureAlgorithm, signatureAlgorithm_);
            DARABONBA_PTR_FROM_JSON(globalParameters, globalParameters_);
            DARABONBA_PTR_FROM_JSON(key, key_);
            DARABONBA_PTR_FROM_JSON(cert, cert_);
            DARABONBA_PTR_FROM_JSON(ca, ca_);
            DARABONBA_PTR_FROM_JSON(disableHttp2, disableHttp2_);
            DARABONBA_PTR_FROM_JSON(retryOptions, retryOptions_);
            DARABONBA_PTR_FROM_JSON(tlsMinVersion, tlsMinVersion_);
          };
          Config() = default ;
          Config(const Config &) = default ;
          Config(Config &&) = default ;
          Config(const Darabonba::Json & obj) { from_json(obj, *this); };
          virtual ~Config() = default ;
          Config& operator=(const Config &) = default ;
          Config& operator=(Config &&) = default ;
          virtual void validate() const override {
          };
          virtual void fromMap(const Darabonba::Json &obj) override { from_json(obj, *this); validate(); };
          virtual Darabonba::Json toMap() const override { Darabonba::Json obj; to_json(obj, *this); return obj; };
          virtual bool empty() const override { return this->accessKeyId_ == nullptr
                                                && this->accessKeySecret_ == nullptr && this->securityToken_ == nullptr && this->bearerToken_ == nullptr && this->protocol_ == nullptr && this->method_ == nullptr
                                                && this->regionId_ == nullptr && this->readTimeout_ == nullptr && this->connectTimeout_ == nullptr && this->httpProxy_ == nullptr && this->httpsProxy_ == nullptr
                                                && this->credential_ == nullptr && this->endpoint_ == nullptr && this->noProxy_ == nullptr && this->maxIdleConns_ == nullptr && this->network_ == nullptr
                                                && this->userAgent_ == nullptr && this->suffix_ == nullptr && this->socks5Proxy_ == nullptr && this->socks5NetWork_ == nullptr && this->endpointType_ == nullptr
                                                && this->openPlatformEndpoint_ == nullptr && this->type_ == nullptr && this->signatureVersion_ == nullptr && this->signatureAlgorithm_ == nullptr && this->globalParameters_ == nullptr
                                                && this->key_ == nullptr && this->cert_ == nullptr && this->ca_ == nullptr && this->disableHttp2_ == nullptr && this->retryOptions_ == nullptr
                                                && this->tlsMinVersion_ == nullptr;};
          // accessKeyId Field Functions
          bool hasAccessKeyId() const { return this->accessKeyId_ != nullptr;};
          void deleteAccessKeyId() { this->accessKeyId_ = nullptr;};
          inline string accessKeyId() const { DARABONBA_PTR_GET_DEFAULT(accessKeyId_, "") };
          inline Config& setAccessKeyId(string accessKeyId) { DARABONBA_PTR_SET_VALUE(accessKeyId_, accessKeyId) };


          // accessKeySecret Field Functions
          bool hasAccessKeySecret() const { return this->accessKeySecret_ != nullptr;};
          void deleteAccessKeySecret() { this->accessKeySecret_ = nullptr;};
          inline string accessKeySecret() const { DARABONBA_PTR_GET_DEFAULT(accessKeySecret_, "") };
          inline Config& setAccessKeySecret(string accessKeySecret) { DARABONBA_PTR_SET_VALUE(accessKeySecret_, accessKeySecret) };


          // securityToken Field Functions
          bool hasSecurityToken() const { return this->securityToken_ != nullptr;};
          void deleteSecurityToken() { this->securityToken_ = nullptr;};
          inline string securityToken() const { DARABONBA_PTR_GET_DEFAULT(securityToken_, "") };
          inline Config& setSecurityToken(string securityToken) { DARABONBA_PTR_SET_VALUE(securityToken_, securityToken) };


          // bearerToken Field Functions
          bool hasBearerToken() const { return this->bearerToken_ != nullptr;};
          void deleteBearerToken() { this->bearerToken_ = nullptr;};
          inline string bearerToken() const { DARABONBA_PTR_GET_DEFAULT(bearerToken_, "") };
          inline Config& setBearerToken(string bearerToken) { DARABONBA_PTR_SET_VALUE(bearerToken_, bearerToken) };


          // protocol Field Functions
          bool hasProtocol() const { return this->protocol_ != nullptr;};
          void deleteProtocol() { this->protocol_ = nullptr;};
          inline string protocol() const { DARABONBA_PTR_GET_DEFAULT(protocol_, "") };
          inline Config& setProtocol(string protocol) { DARABONBA_PTR_SET_VALUE(protocol_, protocol) };


          // method Field Functions
          bool hasMethod() const { return this->method_ != nullptr;};
          void deleteMethod() { this->method_ = nullptr;};
          inline string method() const { DARABONBA_PTR_GET_DEFAULT(method_, "") };
          inline Config& setMethod(string method) { DARABONBA_PTR_SET_VALUE(method_, method) };


          // regionId Field Functions
          bool hasRegionId() const { return this->regionId_ != nullptr;};
          void deleteRegionId() { this->regionId_ = nullptr;};
          inline string regionId() const { DARABONBA_PTR_GET_DEFAULT(regionId_, "") };
          inline Config& setRegionId(string regionId) { DARABONBA_PTR_SET_VALUE(regionId_, regionId) };


          // readTimeout Field Functions
          bool hasReadTimeout() const { return this->readTimeout_ != nullptr;};
          void deleteReadTimeout() { this->readTimeout_ = nullptr;};
          inline int32_t readTimeout() const { DARABONBA_PTR_GET_DEFAULT(readTimeout_, 0) };
          inline Config& setReadTimeout(int32_t readTimeout) { DARABONBA_PTR_SET_VALUE(readTimeout_, readTimeout) };


          // connectTimeout Field Functions
          bool hasConnectTimeout() const { return this->connectTimeout_ != nullptr;};
          void deleteConnectTimeout() { this->connectTimeout_ = nullptr;};
          inline int32_t connectTimeout() const { DARABONBA_PTR_GET_DEFAULT(connectTimeout_, 0) };
          inline Config& setConnectTimeout(int32_t connectTimeout) { DARABONBA_PTR_SET_VALUE(connectTimeout_, connectTimeout) };


          // httpProxy Field Functions
          bool hasHttpProxy() const { return this->httpProxy_ != nullptr;};
          void deleteHttpProxy() { this->httpProxy_ = nullptr;};
          inline string httpProxy() const { DARABONBA_PTR_GET_DEFAULT(httpProxy_, "") };
          inline Config& setHttpProxy(string httpProxy) { DARABONBA_PTR_SET_VALUE(httpProxy_, httpProxy) };


          // httpsProxy Field Functions
          bool hasHttpsProxy() const { return this->httpsProxy_ != nullptr;};
          void deleteHttpsProxy() { this->httpsProxy_ = nullptr;};
          inline string httpsProxy() const { DARABONBA_PTR_GET_DEFAULT(httpsProxy_, "") };
          inline Config& setHttpsProxy(string httpsProxy) { DARABONBA_PTR_SET_VALUE(httpsProxy_, httpsProxy) };


          // credential Field Functions
          bool hasCredential() const { return this->credential_ != nullptr;};
          void deleteCredential() { this->credential_ = nullptr;};
          inline shared_ptr<AlibabaCloud::Credential::Client> credential() const { DARABONBA_GET(credential_) };
          inline Config& setCredential(shared_ptr<AlibabaCloud::Credential::Client> credential) { DARABONBA_SET_RVALUE(credential_, credential) };


          // endpoint Field Functions
          bool hasEndpoint() const { return this->endpoint_ != nullptr;};
          void deleteEndpoint() { this->endpoint_ = nullptr;};
          inline string endpoint() const { DARABONBA_PTR_GET_DEFAULT(endpoint_, "") };
          inline Config& setEndpoint(string endpoint) { DARABONBA_PTR_SET_VALUE(endpoint_, endpoint) };


          // noProxy Field Functions
          bool hasNoProxy() const { return this->noProxy_ != nullptr;};
          void deleteNoProxy() { this->noProxy_ = nullptr;};
          inline string noProxy() const { DARABONBA_PTR_GET_DEFAULT(noProxy_, "") };
          inline Config& setNoProxy(string noProxy) { DARABONBA_PTR_SET_VALUE(noProxy_, noProxy) };


          // maxIdleConns Field Functions
          bool hasMaxIdleConns() const { return this->maxIdleConns_ != nullptr;};
          void deleteMaxIdleConns() { this->maxIdleConns_ = nullptr;};
          inline int32_t maxIdleConns() const { DARABONBA_PTR_GET_DEFAULT(maxIdleConns_, 0) };
          inline Config& setMaxIdleConns(int32_t maxIdleConns) { DARABONBA_PTR_SET_VALUE(maxIdleConns_, maxIdleConns) };


          // network Field Functions
          bool hasNetwork() const { return this->network_ != nullptr;};
          void deleteNetwork() { this->network_ = nullptr;};
          inline string network() const { DARABONBA_PTR_GET_DEFAULT(network_, "") };
          inline Config& setNetwork(string network) { DARABONBA_PTR_SET_VALUE(network_, network) };


          // userAgent Field Functions
          bool hasUserAgent() const { return this->userAgent_ != nullptr;};
          void deleteUserAgent() { this->userAgent_ = nullptr;};
          inline string userAgent() const { DARABONBA_PTR_GET_DEFAULT(userAgent_, "") };
          inline Config& setUserAgent(string userAgent) { DARABONBA_PTR_SET_VALUE(userAgent_, userAgent) };


          // suffix Field Functions
          bool hasSuffix() const { return this->suffix_ != nullptr;};
          void deleteSuffix() { this->suffix_ = nullptr;};
          inline string suffix() const { DARABONBA_PTR_GET_DEFAULT(suffix_, "") };
          inline Config& setSuffix(string suffix) { DARABONBA_PTR_SET_VALUE(suffix_, suffix) };


          // socks5Proxy Field Functions
          bool hasSocks5Proxy() const { return this->socks5Proxy_ != nullptr;};
          void deleteSocks5Proxy() { this->socks5Proxy_ = nullptr;};
          inline string socks5Proxy() const { DARABONBA_PTR_GET_DEFAULT(socks5Proxy_, "") };
          inline Config& setSocks5Proxy(string socks5Proxy) { DARABONBA_PTR_SET_VALUE(socks5Proxy_, socks5Proxy) };


          // socks5NetWork Field Functions
          bool hasSocks5NetWork() const { return this->socks5NetWork_ != nullptr;};
          void deleteSocks5NetWork() { this->socks5NetWork_ = nullptr;};
          inline string socks5NetWork() const { DARABONBA_PTR_GET_DEFAULT(socks5NetWork_, "") };
          inline Config& setSocks5NetWork(string socks5NetWork) { DARABONBA_PTR_SET_VALUE(socks5NetWork_, socks5NetWork) };


          // endpointType Field Functions
          bool hasEndpointType() const { return this->endpointType_ != nullptr;};
          void deleteEndpointType() { this->endpointType_ = nullptr;};
          inline string endpointType() const { DARABONBA_PTR_GET_DEFAULT(endpointType_, "") };
          inline Config& setEndpointType(string endpointType) { DARABONBA_PTR_SET_VALUE(endpointType_, endpointType) };


          // openPlatformEndpoint Field Functions
          bool hasOpenPlatformEndpoint() const { return this->openPlatformEndpoint_ != nullptr;};
          void deleteOpenPlatformEndpoint() { this->openPlatformEndpoint_ = nullptr;};
          inline string openPlatformEndpoint() const { DARABONBA_PTR_GET_DEFAULT(openPlatformEndpoint_, "") };
          inline Config& setOpenPlatformEndpoint(string openPlatformEndpoint) { DARABONBA_PTR_SET_VALUE(openPlatformEndpoint_, openPlatformEndpoint) };


          // type Field Functions
          bool hasType() const { return this->type_ != nullptr;};
          void deleteType() { this->type_ = nullptr;};
          inline string type() const { DARABONBA_PTR_GET_DEFAULT(type_, "") };
          inline Config& setType(string type) { DARABONBA_PTR_SET_VALUE(type_, type) };


          // signatureVersion Field Functions
          bool hasSignatureVersion() const { return this->signatureVersion_ != nullptr;};
          void deleteSignatureVersion() { this->signatureVersion_ = nullptr;};
          inline string signatureVersion() const { DARABONBA_PTR_GET_DEFAULT(signatureVersion_, "") };
          inline Config& setSignatureVersion(string signatureVersion) { DARABONBA_PTR_SET_VALUE(signatureVersion_, signatureVersion) };


          // signatureAlgorithm Field Functions
          bool hasSignatureAlgorithm() const { return this->signatureAlgorithm_ != nullptr;};
          void deleteSignatureAlgorithm() { this->signatureAlgorithm_ = nullptr;};
          inline string signatureAlgorithm() const { DARABONBA_PTR_GET_DEFAULT(signatureAlgorithm_, "") };
          inline Config& setSignatureAlgorithm(string signatureAlgorithm) { DARABONBA_PTR_SET_VALUE(signatureAlgorithm_, signatureAlgorithm) };


          // globalParameters Field Functions
          bool hasGlobalParameters() const { return this->globalParameters_ != nullptr;};
          void deleteGlobalParameters() { this->globalParameters_ = nullptr;};
          inline const GlobalParameters & globalParameters() const { DARABONBA_PTR_GET_CONST(globalParameters_, GlobalParameters) };
          inline GlobalParameters globalParameters() { DARABONBA_PTR_GET(globalParameters_, GlobalParameters) };
          inline Config& setGlobalParameters(const GlobalParameters & globalParameters) { DARABONBA_PTR_SET_VALUE(globalParameters_, globalParameters) };
          inline Config& setGlobalParameters(GlobalParameters && globalParameters) { DARABONBA_PTR_SET_RVALUE(globalParameters_, globalParameters) };


          // key Field Functions
          bool hasKey() const { return this->key_ != nullptr;};
          void deleteKey() { this->key_ = nullptr;};
          inline string key() const { DARABONBA_PTR_GET_DEFAULT(key_, "") };
          inline Config& setKey(string key) { DARABONBA_PTR_SET_VALUE(key_, key) };


          // cert Field Functions
          bool hasCert() const { return this->cert_ != nullptr;};
          void deleteCert() { this->cert_ = nullptr;};
          inline string cert() const { DARABONBA_PTR_GET_DEFAULT(cert_, "") };
          inline Config& setCert(string cert) { DARABONBA_PTR_SET_VALUE(cert_, cert) };


          // ca Field Functions
          bool hasCa() const { return this->ca_ != nullptr;};
          void deleteCa() { this->ca_ = nullptr;};
          inline string ca() const { DARABONBA_PTR_GET_DEFAULT(ca_, "") };
          inline Config& setCa(string ca) { DARABONBA_PTR_SET_VALUE(ca_, ca) };


          // disableHttp2 Field Functions
          bool hasDisableHttp2() const { return this->disableHttp2_ != nullptr;};
          void deleteDisableHttp2() { this->disableHttp2_ = nullptr;};
          inline bool disableHttp2() const { DARABONBA_PTR_GET_DEFAULT(disableHttp2_, false) };
          inline Config& setDisableHttp2(bool disableHttp2) { DARABONBA_PTR_SET_VALUE(disableHttp2_, disableHttp2) };


          // retryOptions Field Functions
          bool hasRetryOptions() const { return this->retryOptions_ != nullptr;};
          void deleteRetryOptions() { this->retryOptions_ = nullptr;};
          inline const Darabonba::Policy::RetryOptions & retryOptions() const { DARABONBA_PTR_GET_CONST(retryOptions_, Darabonba::Policy::RetryOptions) };
          inline Darabonba::Policy::RetryOptions retryOptions() { DARABONBA_PTR_GET(retryOptions_, Darabonba::Policy::RetryOptions) };
          inline Config& setRetryOptions(const Darabonba::Policy::RetryOptions & retryOptions) { DARABONBA_PTR_SET_VALUE(retryOptions_, retryOptions) };
          inline Config& setRetryOptions(Darabonba::Policy::RetryOptions && retryOptions) { DARABONBA_PTR_SET_RVALUE(retryOptions_, retryOptions) };


          // tlsMinVersion Field Functions
          bool hasTlsMinVersion() const { return this->tlsMinVersion_ != nullptr;};
          void deleteTlsMinVersion() { this->tlsMinVersion_ = nullptr;};
          inline string tlsMinVersion() const { DARABONBA_PTR_GET_DEFAULT(tlsMinVersion_, "") };
          inline Config& setTlsMinVersion(string tlsMinVersion) { DARABONBA_PTR_SET_VALUE(tlsMinVersion_, tlsMinVersion) };


        protected:
          // accesskey id
          std::shared_ptr<string> accessKeyId_ = nullptr;
          // accesskey secret
          std::shared_ptr<string> accessKeySecret_ = nullptr;
          // security token
          std::shared_ptr<string> securityToken_ = nullptr;
          // bearer token
          std::shared_ptr<string> bearerToken_ = nullptr;
          // http protocol
          std::shared_ptr<string> protocol_ = nullptr;
          // http method
          std::shared_ptr<string> method_ = nullptr;
          // region id
          std::shared_ptr<string> regionId_ = nullptr;
          // read timeout
          std::shared_ptr<int32_t> readTimeout_ = nullptr;
          // connect timeout
          std::shared_ptr<int32_t> connectTimeout_ = nullptr;
          // http proxy
          std::shared_ptr<string> httpProxy_ = nullptr;
          // https proxy
          std::shared_ptr<string> httpsProxy_ = nullptr;
          // credential
          std::shared_ptr<AlibabaCloud::Credential::Client> credential_ = nullptr;
          // endpoint
          std::shared_ptr<string> endpoint_ = nullptr;
          // proxy white list
          std::shared_ptr<string> noProxy_ = nullptr;
          // max idle conns
          std::shared_ptr<int32_t> maxIdleConns_ = nullptr;
          // network for endpoint
          std::shared_ptr<string> network_ = nullptr;
          // user agent
          std::shared_ptr<string> userAgent_ = nullptr;
          // suffix for endpoint
          std::shared_ptr<string> suffix_ = nullptr;
          // socks5 proxy
          std::shared_ptr<string> socks5Proxy_ = nullptr;
          // socks5 network
          std::shared_ptr<string> socks5NetWork_ = nullptr;
          // endpoint type
          std::shared_ptr<string> endpointType_ = nullptr;
          // OpenPlatform endpoint
          std::shared_ptr<string> openPlatformEndpoint_ = nullptr;
          // credential type
          std::shared_ptr<string> type_ = nullptr;
          // Signature Version
          std::shared_ptr<string> signatureVersion_ = nullptr;
          // Signature Algorithm
          std::shared_ptr<string> signatureAlgorithm_ = nullptr;
          // Global Parameters
          std::shared_ptr<GlobalParameters> globalParameters_ = nullptr;
          // privite key for client certificate
          std::shared_ptr<string> key_ = nullptr;
          // client certificate
          std::shared_ptr<string> cert_ = nullptr;
          // server certificate
          std::shared_ptr<string> ca_ = nullptr;
          // disable HTTP/2
          std::shared_ptr<bool> disableHttp2_ = nullptr;
          // retry options
          std::shared_ptr<Darabonba::Policy::RetryOptions> retryOptions_ = nullptr;
          // TLS Minimum Version
          std::shared_ptr<string> tlsMinVersion_ = nullptr;
        };

      } // namespace Models
    } // namespace AlibabaCloud
  } // namespace OpenApi
} // namespace Utils
#endif
