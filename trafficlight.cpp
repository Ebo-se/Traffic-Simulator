//
// Created by Ebose on 2025-07-23.
//

#include "trafficlight.h"
#include <chrono>
#include <thread>
//whenever we make the light we're gonna make a thread
const int red_stoptime = 50;
const int green_stoptime = 45;
const int yellow_stoptime = 5;
trafficlight::trafficlight(int dir, int start_state) {
    this->direction = dir;
    this->stopSignal = false;
    if (start_state == 2) {this->current = Green;}
    else {this->current = Red;}
}
void trafficlight::changecolour() {
    while (!stopSignal) {
        {
            std::lock_guard<std::mutex> lock(mt);
            if (current == Red) {current = Green;}
            else if (current == Green) {current = Yellow;}
            else {current = Red;}
        }
        std::this_thread::sleep_for(
    current == Red ? std::chrono::seconds(red_stoptime) :
    current == Green ? std::chrono::seconds(green_stoptime) :
    std::chrono::seconds(yellow_stoptime)
);
    }
}

void trafficlight::stop() {this->stopSignal = true;}
int trafficlight::getstate() {
    std::lock_guard<std::mutex> lock(mt);
    switch (this->current) {
        case Red:return 0;
        case Green:return 2;
        case Yellow:return 1;
        default: return -1;
    }
}