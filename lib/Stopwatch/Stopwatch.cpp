#include <Stopwatch.h>

void Stopwatch::start() {
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