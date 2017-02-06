/*
 * Info.h
 *
 *  Created on: 06/02/2017
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_INFO_H_
#define INCLUDES_INFO_H_

#include <string>

namespace SatHelper {

    class Info {
    public:
        const static std::string &GetVersion();
        const static std::string &GetCompilationDate();
        const static std::string &GetCompilationTime();
        const static std::string &GetGitSHA1();
    };

} /* namespace SatHelper */

#endif /* INCLUDES_INFO_H_ */
