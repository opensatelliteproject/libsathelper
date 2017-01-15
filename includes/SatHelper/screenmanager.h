/*
 * screenmanager.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_SCREENMANAGER_H_
#define INCLUDES_SCREENMANAGER_H_


namespace SatHelper {
    class ScreenManager {
    public:
        static void GotoXY(int x, int y);
        static void Clear();
    };
}


#endif /* INCLUDES_SCREENMANAGER_H_ */
