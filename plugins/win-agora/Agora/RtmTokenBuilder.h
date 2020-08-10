#pragma once

//#include <zlib.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "AccessToken.h"

namespace agora {
namespace tools {

enum RtmUserRole {
  Rtm_User = 1,
};

class RtmTokenBuilder {
 public:
	 static std::string buildToken(const char* appId,
		 const char* appCertificate,
		 const char* userAccount,
                                RtmUserRole userRole,
                                uint32_t privilegeExpiredTs = 0);
};

 std::string RtmTokenBuilder::buildToken(
	 const char* appId,
	 const char* appCertificate,
	 const char* userAccount,
    RtmUserRole userRole,
    uint32_t privilegeExpiredTs) {
  AccessToken generator(appId, appCertificate, userAccount, "");
  generator.AddPrivilege(AccessToken::Privileges::kRtmLogin, privilegeExpiredTs);
  return generator.Build();
}
}  // namespace tools
}  // namespace agora
