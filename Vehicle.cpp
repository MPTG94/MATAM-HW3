//
// Created by Mor on 09/01/2020.
//

#include "Vehicle.h"

Vehicle::Vehicle(string plate, Time entranceTime, VehicleType type) : plate(
        plate), entranceTime(entranceTime), type(type) {}

bool Vehicle::isFined() {
    return this->fined;
}
VehicleType Vehicle::getVehicleType() {
    return this->type;
}

unsigned int Vehicle::calculateParkingPrice(Time exitTime) {
    unsigned int price = 0;
    VehicleType CurrentType = this->getVehicleType();
    unsigned int oneHour = 1;
    Time totalTime = exitTime - this->entranceTime;
    unsigned int totalTimeInHours = totalTime.toHours();

    if (CurrentType == HANDICAPPED) {
        price = 15;
    } else if (CurrentType == MOTORBIKE) {
        if (totalTimeInHours <= oneHour) {
            price =10;
        }
        else if ((totalTimeInHours > oneHour)&&(totalTimeInHours<=6*oneHour)) {
            price= 10 + 5 * (totalTimeInHours - 1);
        }
        else{
            price = 35;
        }
    }
    else {
        if (totalTimeInHours <= oneHour) {
            price =20;
        }
        else if ((totalTimeInHours > oneHour)&&(totalTimeInHours<=6*oneHour)) {
            price= 20 + 10 * (totalTimeInHours - 1);
        }
        else{
            price = 70;
        }
    }
    return price;
}

string Vehicle::getLicensePlate() {
    return this->plate;
}

void Vehicle::markAsFined() {
    this->fined = true;
}

