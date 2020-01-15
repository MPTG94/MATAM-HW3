//
// Created by Mor on 09/01/2020.
//

#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include <string>
#include "ParkingLotTypes.h"
#include "ParkingSpot.h"
#include "Time.h"

using namespace ParkingLotUtils;

class Vehicle {
private:
    string plate;
    Time entranceTime;
    VehicleType type;
    ParkingSpot spot;
    bool fined = false;

    static int calculatingCarParkingPrice(unsigned int
                                                   totalTimeInHours,
                                                   unsigned int oneHour,
                                                   unsigned  int price);

    static unsigned int calculateMotorbikeParkingPrice(unsigned int
                                                       totalTimeInHours,
                                                       unsigned int oneHour,
                                                       unsigned int price);

public:
    Vehicle(string plate, Time entranceTime, VehicleType type);

    string getLicensePlate();

    VehicleType getVehicleType();

    Time getEntranceTime();

    ParkingSpot getParkingSpot();

    bool setParkingSpot(ParkingSpot parkingSpot);

    bool isFined();

    void markAsFined();

    int calculateParkingPrice(Time exitTime);

    bool operator==(const Vehicle &vehicle) const;

};

#endif //HW3_VEHICLE_H
