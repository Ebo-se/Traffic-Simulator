//
// Created by Ebose on 2025-07-23.
//

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <mutex>
class trafficlight {
private:
    int direction; //1 = N, -1 = E
    enum state {Red, Yellow, Green};
    state current;
    bool stopSignal;
    std::mutex mt;//to protect the code from crashing as we need to getstate and change colour at the same time
public:
    trafficlight(int dir, int start_state); //start state is either red or green
    void changecolour();
    int getstate();
    void stop();

};

#endif //TRAFFICLIGHT_H
