/*
  Stopwatch.h - Library for handling the time.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Stopwatch_h
#define Stopwatch_h

#include <Arduino.h>

class Stopwatch {
  private:
    long startTime;
    long endTime;
    bool started = false;

  public:
      void start();
      void stop();
      double elapsedMilliseconds();

      void start() {
        startTime = millis();
        started = true;
      }

      void Stopwatch::stop() {
        endTime = millis();
        started = false;
      }

      double Stopwatch::elapsedMilliseconds() {
        if(started) {
            endTime = millis();
        }
        
        return endTime - startTime;
      }
};

#endif