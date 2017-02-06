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

    template<class T>
    void CircularBuffer<T>::addSamples(const T *data, unsigned int length) {
      fifoMutex.lock();
      bool trimmed = false;
      if (length >= maxLength) {
        overflow = true;
        length = maxLength;
        trimmed = true;
      }

      if (numItems + length == maxLength) {
        curSample += length;
        curSample %= maxLength;
        numItems -= length;
        overflow = true;
      } else if (!trimmed) {
        overflow = false;
      }

      for (unsigned int i = 0; i < length; i++) {
        *getPositionPointer(curSample + numItems) = data[i];
        numItems++;
      }
      fifoMutex.unlock();
    }

    template<class T>
    void CircularBuffer<T>::addSample(T data) {
      fifoMutex.lock();

      if (numItems + 1 == maxLength) {
        curSample++;
        curSample %= maxLength;
        numItems--;
        overflow = true;
      } else {
        overflow = false;
      }

      *getPositionPointer(curSample + numItems) = data;
      numItems++;

      fifoMutex.unlock();
    }

    template<class T>
    T CircularBuffer<T>::takeSample() {
      T v;

      fifoMutex.lock();
      if (numItems > 0) {
        v = unsafe_takeSample();
      }
      fifoMutex.unlock();

      return v;
    }

    template<class T>
    unsigned int CircularBuffer<T>::size() {
      unsigned int size;

      fifoMutex.lock();
      size = numItems;
      fifoMutex.unlock();

      return size;
    }

    template<class T>
    bool CircularBuffer<T>::containsSamples() {
      bool ret;

      fifoMutex.lock();
      ret = numItems > 0;
      fifoMutex.unlock();

      return ret;
    }


} /* namespace SatHelper */

#endif /* SRC_CIRCULARBUFFER_H_ */
