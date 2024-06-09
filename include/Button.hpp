/*
  Player.hpp - Library for creating and handling a player.
  Created by GridGurus, April to July, 2024.
  Developed for Physical Computing Lab at Leibniz University Hanover.
*/

#ifndef Button_hpp
#define Button_hpp

#include <Stopwatch.h>
#include <RgbMatrix.h>
#include <Arduino.h>
#include <Globals.hpp>

class Button {
  public:
        Button(int index, int player, double time) : index(index), player(player), time(time) {
            // start watch on creation
            watch.start();
        }

        inline int getIndex() {return index;}
        inline int getPlayer() {return player;}
        
        double getRemainingTime() {
            double elapsed = time - watch.elapsedMilliseconds();
            if (elapsed <= 0) {
                watch.stop();
                return 0;
            }
            return elapsed;
        }

  private:
        int index;
        int player;
        double time;
        Stopwatch watch = Stopwatch();
};

#endif