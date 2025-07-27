//
// Created by Ebose on 2025-07-23.
//

#ifndef VEHICLE_H
#define VEHICLE_H

class vehicle {
private:
    int wait_time;
    int direction; //1=N,-1=E
    double speed = 35.7;
    bool isRunning;
    bool vehicleTextureLoaded = false;
public:
    vehicle(int dir); //constructor
    int getdirection();
    void loadTexture();
};

#endif //VEHICLE_H
