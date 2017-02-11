/*
 * ConfigParser.h
 *
 *  Created on: 31/01/2017
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_SATHELPER_CONFIGPARSER_H_
#define INCLUDES_SATHELPER_CONFIGPARSER_H_

#include <string>
#include <unordered_map>

namespace SatHelper {

    class ConfigParser {
    private:
        std::unordered_map<std::string, std::string> parameters;
        std::string filename;

    public:
        ConfigParser(const std::string &filename);

        inline void set(const std::string &key, const std::string &value) {
            parameters[key] = value;
        }

        inline bool hasKey(const std::string &key) {
            return parameters.find(key) != parameters.end();
        }

        inline std::string get(const std::string &key) {
            if (parameters.find(key) != parameters.end()) {
                return parameters[key];
            } else {
                return std::string();
            }
        }

        inline std::string &operator[](const std::string &key) {
            return parameters[key];
        }

        inline float getFloat(const std::string &key) {
            return (float)std::atof(parameters[key].c_str());
        }

        inline int getInt(const std::string &key) {
            return std::atoi(parameters[key].c_str());
        }

        inline unsigned int getUInt(const std::string &key) {
            return (unsigned int) (std::strtoul(parameters[key].c_str(), NULL, 10) & 0xFFFFFFFF);
        }

        inline bool getBool(const std::string &key) {
            return parameters[key] == "true";
        }

        void SaveFile();
        bool LoadFile();
        virtual ~ConfigParser();
    };

} /* namespace SatHelper */

#endif /* INCLUDES_SATHELPER_CONFIGPARSER_H_ */
