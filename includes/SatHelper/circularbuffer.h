/*
 * CircularBuffer.h
 *
 *  Created on: 01/02/2017
 *      Author: Lucas Teske
 */

#ifndef SRC_CIRCULARBUFFER_H_
#define SRC_CIRCULARBUFFER_H_

#include <atomic>
#include <mutex>

namespace SatHelper {

    template<class T> class CircularBuffer {
    private:
        T *baseBuffer;
        int curSample;

        std::mutex fifoMutex;
        unsigned int maxLength;
        std::atomic_bool overflow;
        unsigned int numItems;

        inline T *getPositionPointer(int pos) {
            return &baseBuffer[pos % maxLength];
        }
    public:
        CircularBuffer<T>(const unsigned int maxLength) :
             curSample(0), maxLength(maxLength), overflow(false), numItems(0) {
            baseBuffer = new T[maxLength];
        }
        inline ~CircularBuffer<T>() {
            delete[] baseBuffer;
        }

        // Safe operations
        void addSamples(const T *data, unsigned int length);
        void addSample(T data);
        T takeSample();
        unsigned int size();
        bool containsSamples();

        inline bool isOverflow() { return overflow; }

        // Unsafe operations
        inline void unsafe_lockMutex() {
            fifoMutex.lock();
        }

        inline void unsafe_unlockMutex() {
            fifoMutex.unlock();
        }

        inline T unsafe_takeSample() {
            T v = *getPositionPointer(curSample);
            curSample++;
            curSample %= maxLength;
            numItems-=1;
            overflow = false;
            return v;
        }
    };

} /* namespace SatHelper */

#endif /* SRC_CIRCULARBUFFER_H_ */
