//
// Created by Ebose on 2025-07-23.
//

#ifndef VEHICLE_H
#define VEHICLE_H

class vehicle {
private:
    int wait_time;
    int id;
    int direction; //1=N,-1=E
    double speed = 35.7;
public:
    vehicle(int id,int dir); //constructor
    int getdirection();
};

#endif //VEHICLE_H
