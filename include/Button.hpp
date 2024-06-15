/*
  Player.hpp - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Button_hpp
#define Button_hpp

#include <Stopwatch.h>
#include <Arduino.h>

class Button {
  public:
        // Default constructor
        Button() : index(-1), player(-1), time(0) {}

        Button(int8_t index, int8_t player, double time) : index(index), player(player), time(time) {
          // start watch on creation
          watch.start();
        }

        inline int getIndex() {return index;}
        inline int getPlayer() {return player;}

        void remove() {
            // stop watch before removing button
            watch.stop();
            index = -1;
            player = -1;
        }

        double getRemainingTime() {
            double elapsed = time - watch.elapsedMilliseconds();
            if (elapsed <= 0) {
                watch.stop();
                return 0;
            }
            return elapsed;
        }

  private:
        int8_t index;
        int8_t player;
        double time;
        Stopwatch watch = Stopwatch();
};

#endif