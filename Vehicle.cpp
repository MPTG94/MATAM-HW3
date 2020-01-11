//
// Created by Mor on 09/01/2020.
//
#include "Vehicle.h"

#include <utility>

using std::move;
const int PRICE_FOR_HANDICAPPED = 15;
const int PRICE_FOR_FIRST_HOUR_MOTORBIKE = 10;
const int PRICE_FOR_EXTRA_HOURS_MOTORBIKE = 5;
const int MAX_PRICE_FOR_MOTORBIKE = 35;
const int PRICE_FOR_FIRST_HOUR_CAR = 20;
const int PRICE_FOR_EXTRA_HOURS_CAR = 10;
const int MAX_PRICE_FOR_CAR = 70;
const int FINE = 250;

Vehicle::Vehicle(string plate, Time entranceTime, VehicleType type) :
        plate(move(plate)), entranceTime(entranceTime), type(type) {}

bool Vehicle::isFined() {
    return this->fined;
}

VehicleType Vehicle::getVehicleType() {
    return this->type;
}

string Vehicle::getLicensePlate() {
    return this->plate;
}

Time Vehicle::getEntranceTime() {
    return this->entranceTime;
}

void Vehicle::markAsFined() {
    this->fined = true;
}

unsigned int Vehicle::calculateParkingPrice(Time exitTime) {
    int price = 0;
    VehicleType CurrentType = this->getVehicleType();
    unsigned int oneHour = 1;
    Time totalTime = exitTime - this->entranceTime;
    unsigned int totalTimeInHours = totalTime.toHours();
    if (totalTimeInHours == 0) {
        return price;
    }
    if (CurrentType == HANDICAPPED) {
        price = PRICE_FOR_HANDICAPPED;
    } else if (CurrentType == MOTORBIKE) {
        price = calculateMotorbikeParkingPrice(totalTimeInHours, oneHour,
                                               price);
    } else {
        price = calculatingCarParkingPrice(totalTimeInHours, oneHour, price);
    }
    if (this->isFined()) {
        price += FINE;
    }
    return price;
}

int Vehicle::calculatingCarParkingPrice(unsigned int totalTimeInHours,
                                                 unsigned int oneHour,
                                                 int price) {
    if (totalTimeInHours <= oneHour) {
        price = PRICE_FOR_FIRST_HOUR_CAR;
    } else if (totalTimeInHours > oneHour && totalTimeInHours <= 6 * oneHour) {
        price = PRICE_FOR_FIRST_HOUR_CAR +
                PRICE_FOR_EXTRA_HOURS_CAR * (totalTimeInHours - 1);
    } else {
        price = MAX_PRICE_FOR_CAR;
    }
    return price;
}

unsigned int
Vehicle::calculateMotorbikeParkingPrice(unsigned int totalTimeInHours,
                                        unsigned int oneHour,
                                        unsigned int price) {
    if (totalTimeInHours <= oneHour) {
        price = PRICE_FOR_FIRST_HOUR_MOTORBIKE;
    } else if ((totalTimeInHours > oneHour) &&
               (totalTimeInHours <= 6 * oneHour)) {
        price = PRICE_FOR_FIRST_HOUR_MOTORBIKE +
                PRICE_FOR_EXTRA_HOURS_MOTORBIKE * (totalTimeInHours - 1);
    } else {
        price = MAX_PRICE_FOR_MOTORBIKE;
    }

    return price;
}

bool Vehicle::operator==(const Vehicle &vehicle) const {
    return vehicle.plate == this->plate;
}
