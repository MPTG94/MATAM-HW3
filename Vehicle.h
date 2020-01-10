//
// Created by Mor on 09/01/2020.
//

#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include <string>
#include "provided_files/ParkingLotTypes.h"
#include "provided_files/ParkingSpot.h"
#include "provided_files/Time.h"

using namespace ParkingLotUtils;

class Vehicle {
private:
    string plate;
    Time entranceTime;
    VehicleType type;
    bool fined = false;

    static unsigned int calculatingCarParkingPrice(unsigned int
                                                   totalTimeInHours,
                                                   unsigned int oneHour,
                                                   unsigned int price);

    static unsigned int calculateMotorbikeParkingPrice(unsigned int
                                                       totalTimeInHours,
                                                       unsigned int oneHour,
                                                       unsigned int price);

public:
    Vehicle(string plate, Time entranceTime, VehicleType type);

    string getLicensePlate();

    VehicleType getVehicleType();

    bool isFined();

    void markAsFined();

    unsigned int calculateParkingPrice(Time exitTime);

    bool operator==(const Vehicle &vehicle) const;

};

#endif //HW3_VEHICLE_H
