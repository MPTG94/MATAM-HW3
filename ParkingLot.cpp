//
// Created by Mor on 09/01/2020.
//
#include <algorithm>
#include "provided_files/ParkingLot.h"

#include <vector>
#include <utility>
#include "./provided_files/ParkingLotPrinter.h"


using namespace MtmParkingLot;
using namespace std;


MtmParkingLot::ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
        : motorbikeArray(parkingBlockSizes[0]),
          handicapArray(parkingBlockSizes[1]),
          carArray(parkingBlockSizes[2]) {
}

MtmParkingLot::ParkingLot::~ParkingLot() = default;

ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::enterParking(
        ParkingLotUtils::VehicleType vehicleType,
        ParkingLotUtils::LicensePlate &licensePlate,
        ParkingLotUtils::Time entranceTime) {
    if (vehicleType == MOTORBIKE) {
        return insertNewVehicle(motorbikeArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    } else if (vehicleType == CAR) {
        return insertNewVehicle(carArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    } else {
        return insertNewVehicle(handicapArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    }
}

ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::getParkingSpot(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::ParkingSpot &parkingSpot) const {
    if (genericGetSpot(carArray, CAR, licensePlate,
                       parkingSpot) == SUCCESS ||
        genericGetSpot(motorbikeArray, MOTORBIKE, licensePlate,
                       parkingSpot) == SUCCESS ||
        genericGetSpot(handicapArray, HANDICAPPED,
                       licensePlate, parkingSpot) == SUCCESS) {
        return SUCCESS;
    } else {
        return VEHICLE_NOT_FOUND;
    }
}

ParkingLotUtils::ParkingResult
MtmParkingLot::ParkingLot::exitParking(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time exitTime) {
    ParkingSpot spot;
    if (getParkingSpot(licensePlate, spot) == VEHICLE_NOT_FOUND) {
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }
    if (genericExitParking(carArray, CAR, licensePlate,
                           exitTime) == SUCCESS ||
        genericExitParking(motorbikeArray, MOTORBIKE,
                           licensePlate, exitTime) == SUCCESS ||
        genericExitParking(handicapArray, HANDICAPPED,
                           licensePlate, exitTime) == SUCCESS ||
        genericExitParking(carArray, HANDICAPPED,
                           licensePlate, exitTime) == SUCCESS) {
        return SUCCESS;
    }
    ParkingLotPrinter::printExitFailure(cout, licensePlate);
    return VEHICLE_NOT_FOUND;
}

void MtmParkingLot::ParkingLot::inspectParkingLot(
        ParkingLotUtils::Time inspectionTime) {
    int fineCounter = 0;
    fineCounter += genericInspectParkingLot(inspectionTime, carArray);
    fineCounter += genericInspectParkingLot(inspectionTime, motorbikeArray);
    fineCounter += genericInspectParkingLot(inspectionTime, handicapArray);
    ParkingLotPrinter::printInspectionResult(cout, inspectionTime,
                                             fineCounter);
}

struct CompareVehicles {
    bool operator()(Vehicle vehicle1, Vehicle vehicle2) {
        return (vehicle1.getParkingSpot() < vehicle2.getParkingSpot());
    }
};

std::ostream
&MtmParkingLot::operator<<(std::ostream &os,
                           const MtmParkingLot::ParkingLot &parkingLot) {
    vector<Vehicle> vehicleVector = vector<Vehicle>();
    vehicleVector = parkingLot.fillVectorFromArray(vehicleVector, MOTORBIKE);
    vehicleVector = parkingLot.fillVectorFromArray(vehicleVector, HANDICAPPED);
    vehicleVector = parkingLot.fillVectorFromArray(vehicleVector, CAR);
    ParkingLotPrinter::printParkingLotTitle(os);
    sort(vehicleVector.begin(), vehicleVector.end(), CompareVehicles());
    for (int i = 0; i < vehicleVector.size(); i++) {

    }
    return os;
}

vector<Vehicle> ParkingLot::fillVectorFromArray(vector<Vehicle> &vehicleVector,
                                                VehicleType type) const {
    switch (type) {
        case ParkingLotUtils::MOTORBIKE:
            for (int i = 0; i < this->motorbikeArray.getSize(); i++) {
                vehicleVector.push_back(
                        *this->motorbikeArray.getElementByIndex(i));
            }
            return vehicleVector;
        case ParkingLotUtils::HANDICAPPED:
            for (int i = 0; i < this->handicapArray.getSize(); i++) {
                vehicleVector.push_back(
                        *this->handicapArray.getElementByIndex(i));
            }
            return vehicleVector;
        case CAR:
            for (int i = 0; i < this->carArray.getSize(); i++) {
                vehicleVector.push_back(*this->carArray.getElementByIndex(i));
            }
            return vehicleVector;
    }
}

ostream &ParkingLot::printVehiclesOfType(ostream &os, VehicleType type) const {
    switch (type) {
        case MOTORBIKE:
            MtmParkingLot::ParkingLot::genericPrintVehicles(
                    os, motorbikeArray, type);
            break;
        case HANDICAPPED:
            MtmParkingLot::ParkingLot::genericPrintVehicles(
                    os, handicapArray, type);
            break;
        case CAR:
            MtmParkingLot::ParkingLot::genericPrintVehicles(
                    os, carArray, type);
            break;
    }
    return os;
}

ostream &ParkingLot::genericPrintVehicles(ostream &os, Vehicle vehicle,
                                          VehicleType type) {
    ParkingLotPrinter::printVehicle(os, vehicle.getVehicleType(),
                                    vehicle.getLicensePlate(),
                                    vehicle.getEntranceTime());
    ParkingLotPrinter::printParkingSpot(os, vehicle.getParkingSpot());
    return os;
}


ParkingResult ParkingLot::insertNewVehicle(UniqueArray
                                                   <Vehicle, std::equal_to<Vehicle>> array,
                                           VehicleType vehicleType, LicensePlate
                                           licensePlate, Time entranceTime,
                                           const UniqueArray<Vehicle,
                                                   std::equal_to<Vehicle>> &carArray) {
    Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                                 vehicleType);
    int isVehicleInArray = array.contains(newVehicle);
    if (vehicleType == HANDICAPPED) {
        int isVehicleInCarArray = carArray.contains(newVehicle);
        if (isVehicleInCarArray != -1) {
            ParkingSpot spot = carArray.getElementByIndex(
                    isVehicleInCarArray)->getParkingSpot();
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout, spot);
            return VEHICLE_ALREADY_PARKED;
        }
    }
    if (isVehicleInArray != -1) {
        ParkingSpot spot = array.getElementByIndex(
                isVehicleInArray)->getParkingSpot();
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout, spot);
        return VEHICLE_ALREADY_PARKED;
    } else {
        if (array.getSize() - array.getCount() > 0) {
            unsigned int newIndex = array.insert(newVehicle);
            ParkingLotPrinter::printVehicle(cout, vehicleType,
                                            newVehicle.getLicensePlate(),
                                            entranceTime);
            ParkingSpot spot = ParkingSpot(vehicleType, newIndex);
            array.getElementByIndex(newIndex)->setParkingSpot(spot);
            ParkingLotPrinter::printEntrySuccess(cout, spot);
            return SUCCESS;
        } else {
            ParkingLotPrinter::printEntryFailureNoSpot(cout);
            return NO_EMPTY_SPOT;
        }
    }
}

ParkingResult ParkingLot::genericGetSpot(const UniqueArray<Vehicle,
        std::equal_to<Vehicle>> &array, VehicleType vehicleType,
                                         const LicensePlate &licensePlate,
                                         ParkingSpot &parkingSpot) {
    for (int i = 0; i < array.getSize(); i++) {
        Vehicle *currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            if (currentVehicle->getLicensePlate() == licensePlate) {
                parkingSpot = currentVehicle->getParkingSpot();
                return SUCCESS;
            }
        }
    }
    return VEHICLE_ALREADY_PARKED;
}

ParkingResult ParkingLot::genericExitParking(UniqueArray<Vehicle,
        std::equal_to<Vehicle>> array, VehicleType vehicleType,
                                             const LicensePlate &
                                             licensePlate, Time exitTime) {
    for (int i = 0; i < array.getSize(); i++) {
        Vehicle *currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            if (currentVehicle->getLicensePlate() == licensePlate) {
                int bill = currentVehicle->calculateParkingPrice(exitTime);
                ParkingLotPrinter::printExitSuccess(cout,
                                                    currentVehicle->getParkingSpot(),
                                                    exitTime, bill);
                array.remove(*currentVehicle);
                return SUCCESS;
            }
        }
    }
}

int ParkingLot::genericInspectParkingLot(Time currentTime,
                                         const UniqueArray<Vehicle,
                                                 std::equal_to<Vehicle>> &array) {
    int count = 0;
    unsigned int oneHour = 1;
    for (int i = 0; i < array.getSize(); i++) {
        Vehicle *currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            if (!currentVehicle->isFined()) {
                unsigned int totalTime =
                        (currentTime -
                         currentVehicle->getEntranceTime()).toHours();
                if (totalTime >= 24 * oneHour) {
                    count++;
                    currentVehicle->markAsFined();
                }
            }
        }
    }
    return count;
}