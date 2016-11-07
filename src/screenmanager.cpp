/*
 * screenmanager.cpp
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#include "screenmanager.h"

#include <iostream>

using namespace SatHelper;

void ScreenManager::GotoXY(int x, int y) {
    std::cout << "\033[" << x << ";" << y << "H";
}

void ScreenManager::Clear() {
    std::cout << "\033[H\033[J";
}




