/*
 * Info.cpp
 *
 *  Created on: 06/02/2017
 *      Author: Lucas Teske
 */

#include <SatHelper/info.h>


#define Q(x) #x
#define QUOTE(x) Q(x)

#ifndef MAJOR_VERSION
#define MAJOR_VERSION unk
#endif
#ifndef MINOR_VERSION
#define MINOR_VERSION unk
#endif
#ifndef MAINT_VERSION
#define MAINT_VERSION unk
#endif
#ifndef GIT_SHA1
#define GIT_SHA1 unk
#endif

namespace SatHelper {

    const std::string version("v" QUOTE(MAJOR_VERSION) "." QUOTE(MINOR_VERSION) "." QUOTE(MAINT_VERSION));
    const std::string compDate(__DATE__);
    const std::string compTime(__TIME__);
    const std::string gitsha(QUOTE(GIT_SHA1));

    const std::string &Info::GetVersion() {
        return version;
    }

    const std::string &Info::GetCompilationDate() {
        return compDate;
    }

    const std::string &Info::GetCompilationTime() {
        return compTime;
    }

    const std::string &Info::GetGitSHA1() {
        return gitsha;
    }

} /* namespace SatHelper */
