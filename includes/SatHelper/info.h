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
        static const std::string &GetVersion();
        static const std::string &GetCompilationDate();
        static const std::string &GetCompilationTime();
        static const std::string &GetGitSHA1();
    };

} /* namespace SatHelper */

#endif /* INCLUDES_INFO_H_ */
