/*
 * ConfigParser.cpp
 *
 *  Created on: 31/01/2017
 *      Author: Lucas Teske
 */

#include <SatHelper/configparser.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace SatHelper {

    ConfigParser::ConfigParser(const std::string &filename) :
            filename(filename) {

    }

    ConfigParser::~ConfigParser() {

    }

    void ConfigParser::SaveFile() {
        std::ofstream fs(filename, std::ofstream::trunc);
        std::cout << "Saving config file to " << filename << std::endl;
        for (auto iter = parameters.begin(); iter != parameters.end(); ++iter) {
            auto k = iter->first;
            fs << iter->first << "=" << iter->second << std::endl;
        }
        fs.close();
    }

    bool ConfigParser::LoadFile() {
        std::ifstream fs(filename);
        std::string line, key, value;

        std::cout << "Loading config file from " << filename << std::endl;
        if (fs) {
            while (std::getline(fs, line)) {
                std::istringstream is(line);
                if (std::getline(is, key, '=')) {
                    if (std::getline(is, value)) {
                        parameters[key] = value;
                    }
                } else {
                    std::cerr << "Warning. Invalid line format: " << line << std::endl;
                }
            }
            fs.close();
            return true;
        } else {
            std::cerr << "Cannot open " << filename  << std::endl;
            return false;
        }
    }

} /* namespace SatHelper */
