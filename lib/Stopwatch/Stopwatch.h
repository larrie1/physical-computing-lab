/*
  Stopwatch.h - Library for handling the time.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/
#ifndef Stopwatch_h
#define Stopwatch_h

#include <Arduino.h>

// Declarations
class Stopwatch {
  public:
      void start();
      void stop();
      double elapsedMilliseconds();

  private:
    long startTime;
    long endTime;
    bool started = false;
};

#endif