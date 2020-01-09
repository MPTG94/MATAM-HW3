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

public:
    Vehicle(string  plate, Time entranceTime, VehicleType type);
    string getLicensePlate();
    VehicleType getVehicleType();
    bool isFined();
    void markAsFined();
    unsigned int calculateParkingPrice( Time exitTime);

    static unsigned int calculateMotorbikeParkingPrice(unsigned int
                                                        totalTimeInHours,
                                                        unsigned int oneHour,
                                                       unsigned int price) {
        if (totalTimeInHours <= oneHour) {
            price =PRICE_FOR_FIRST_HOUR_MOTORBIKE;
        }
        else if ((totalTimeInHours > oneHour)&&(totalTimeInHours<=6*oneHour)) {
            price= PRICE_FOR_FIRST_HOUR_MOTORBIKE +
                   PRICE_FOR_EXTRA_HOURS_MOTORBIKE * (totalTimeInHours - 1);
        }
        else{
            price = MAX_PRICE_FOR_MOTORBIKE;
        }

        return price;
        }

        static unsigned int calculatingCarParkingPrice(unsigned int
                                                        totalTimeInHours,
                                                        unsigned int oneHour,
                                                       unsigned int price) {
            if(totalTimeInHours <= oneHour) {
                price =PRICE_FOR_FIRST_HOUR_CAR;
            }
            else if(totalTimeInHours > oneHour&&totalTimeInHours<=6*oneHour) {
                price= PRICE_FOR_FIRST_HOUR_CAR +
                        PRICE_FOR_EXTRA_HOURS_CAR * (totalTimeInHours - 1);
            }
            else{
                price = MAX_PRICE_FOR_CAR;
            }
            return price;
        }

};

#endif //HW3_VEHICLE_H
