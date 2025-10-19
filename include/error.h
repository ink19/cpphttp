#ifndef BOOST_HTTP_ERROR_H
#define BOOST_HTTP_ERROR_H

#include <string>
#include <boost/system/error_code.hpp>

namespace cpphttp {

enum class ErrCode {
  Resolve_Fail = 1,
  SSL_ERROR = 2,
  CONNECT_FAIL = 3,
  REQUEST_FAIL = 4,
  RESPONSE_FAIL = 5,
  Invalid_Param = 6,
};

class RequestErrorCategory : public boost::system::error_category {
 public:
  const char *name() const noexcept override { return "boost_http"; }

  std::string message(int ev) const override {
    switch (static_cast<ErrCode>(ev)) {
      case ErrCode::Resolve_Fail:
        return "Resolve Fail";
      case ErrCode::SSL_ERROR:
        return "SSL Error";
      case ErrCode::CONNECT_FAIL:
        return "Connect Fail";
      case ErrCode::REQUEST_FAIL:
        return "Request Fail";
      case ErrCode::RESPONSE_FAIL:
        return "Response Fail";
      case ErrCode::Invalid_Param:
        return "Invalid Param";
      default:
        return "Unknown Error";
    }
  }
};

}  // namespace boost::http

#endif  // BOOST_HTTP_ERROR_H
