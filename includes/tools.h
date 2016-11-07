/*
 * tools.h
 *
 *  Created on: 07/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_TOOLS_H_
#define INCLUDES_TOOLS_H_

#include <sys/stat.h>

namespace SatHelper {

    class Tools {
    public:
        inline static uint32_t swapEndianess(uint32_t num) {
            return ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
        }
        inline static uint32_t getTimestamp() {
            return (int) time(NULL);
        }
        inline static void makedir(const std::string &folder) {
            mkdir(folder.c_str(), 0777);
        }
    };
}

#endif /* INCLUDES_TOOLS_H_ */
