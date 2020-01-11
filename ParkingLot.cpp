//
// Created by Mor on 09/01/2020.
//

#include "provided_files/ParkingLot.h"

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
        ParkingLotUtils::LicensePlate& licensePlate,
        ParkingLotUtils::Time entranceTime) {
    if (vehicleType==MOTORBIKE) {
        return insertNewVehicle(motorbikeArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    }
    else if (vehicleType==CAR) {
        return insertNewVehicle(carArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    }
    else {
        return insertNewVehicle(handicapArray, vehicleType,
                                licensePlate, entranceTime, carArray);
    }
}

ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::getParkingSpot(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::ParkingSpot &parkingSpot) const {
    if (genericGetSpot(carArray, CAR, licensePlate,
                       parkingSpot) == SUCCESS ||
        genericGetSpot(motorbikeArray, MOTORBIKE,licensePlate,
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
    if (getParkingSpot(licensePlate, spot) == VEHICLE_NOT_FOUND){
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }
    VehicleType type = spot.getParkingBlock();
    if (genericExitParking(carArray, CAR, licensePlate,
            exitTime) == SUCCESS ||
        genericExitParking(motorbikeArray, MOTORBIKE,
                licensePlate,exitTime) == SUCCESS ||
         genericExitParking(handicapArray, HANDICAPPED,
                 licensePlate ,exitTime) == SUCCESS) {
        return SUCCESS;
    }
    ParkingLotPrinter::printExitFailure(cout, licensePlate);
    return VEHICLE_NOT_FOUND;
}

void MtmParkingLot::ParkingLot::inspectParkingLot(
        ParkingLotUtils::Time inspectionTime) {
    int fineCounter = 0;
    fineCounter+=genericInspectParkingLot(inspectionTime, carArray);
    fineCounter+=genericInspectParkingLot(inspectionTime, motorbikeArray);
    fineCounter+=genericInspectParkingLot(inspectionTime, handicapArray);
    ParkingLotPrinter::printInspectionResult(cout,inspectionTime,
            fineCounter);
}

std::ostream
&MtmParkingLot::operator<<(std::ostream &os,
                           const MtmParkingLot::ParkingLot &parkingLot) {
    ParkingLotPrinter::printParkingLotTitle(os);
    VehicleType typeMotorbike = VehicleType::MOTORBIKE;
    VehicleType typeHandicapped = VehicleType::HANDICAPPED;
    VehicleType typeCar = VehicleType::CAR;
    parkingLot.printVehiclesOfType(os, typeMotorbike);
    parkingLot.printVehiclesOfType(os, typeHandicapped);
    parkingLot.printVehiclesOfType(os, typeCar);
    return os;
}

ostream &ParkingLot::printVehiclesOfType(ostream &os, VehicleType type) const {
    switch (type) {
        case VehicleType::MOTORBIKE:
            this->printMotorbikes(os);
            break;
        case VehicleType::HANDICAPPED:
            this->printHandicapped(os);
            break;
        case VehicleType::CAR:
            this->printCars(os);
            break;
    }
    return os;
}

ostream &ParkingLot::printMotorbikes(ostream &os) const {
    for (int i = 0; i < motorbikeArray.getSize(); i++) {
        Vehicle *vehicle = motorbikeArray.getElementByIndex(i);
        if (vehicle != nullptr) {
            ParkingLotPrinter::printVehicle(os, vehicle->getVehicleType(),
                                            vehicle->getLicensePlate(),
                                            vehicle->getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os, ParkingSpot(
                    vehicle->getVehicleType(), i));
        } else {
            continue;
        }
    }
    return os;
}

ostream &ParkingLot::printHandicapped(ostream &os) const {
    for (int i = 0; i < handicapArray.getSize(); i++) {
        Vehicle *vehicle = handicapArray.getElementByIndex(i);
        if (vehicle != nullptr) {
            ParkingLotPrinter::printVehicle(os, vehicle->getVehicleType(),
                                            vehicle->getLicensePlate(),
                                            vehicle->getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os, ParkingSpot(
                    vehicle->getVehicleType(), i));
        } else {
            continue;
        }
    }
    return os;
}

ostream &ParkingLot::printCars(ostream &os) const {
    for (int i = 0; i < carArray.getSize(); i++) {
        Vehicle *vehicle = carArray.getElementByIndex(i);
        if (vehicle != nullptr) {
            ParkingLotPrinter::printVehicle(os, vehicle->getVehicleType(),
                                            vehicle->getLicensePlate(),
                                            vehicle->getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os, ParkingSpot(
                    vehicle->getVehicleType(), i));
        } else {
            continue;
        }
    }
    return os;
}

ParkingResult ParkingLot::insertNewVehicle(UniqueArray
                                        <Vehicle,std::equal_to<Vehicle>> array,
                                           VehicleType vehicleType,LicensePlate
                                           licensePlate, Time entranceTime,
                                           const UniqueArray<Vehicle,
                                            std::equal_to<Vehicle>>& carArray){

    Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                                 vehicleType);
    int isExistInArray = array.contains(newVehicle);
    if (vehicleType==HANDICAPPED){
        int isExistInCar = carArray.contains(newVehicle);
        if (isExistInCar != -1) {
            ParkingSpot spot = ParkingSpot(vehicleType, isExistInCar);
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout, spot);
            return VEHICLE_ALREADY_PARKED;
        }
    }
    if (isExistInArray != -1) {
        ParkingSpot spot = ParkingSpot(vehicleType, isExistInArray);
        ParkingLotPrinter::printEntryFailureAlreadyParked(cout, spot);
        return VEHICLE_ALREADY_PARKED;
    } else {
        if (array.getSize() - array.getCount() > 0) {
            unsigned int newIndex = array.insert(newVehicle);
            ParkingLotPrinter::printVehicle(cout, vehicleType,
                                            newVehicle.getLicensePlate(),
                                            entranceTime);
            ParkingSpot spot = ParkingSpot(vehicleType, newIndex);
            ParkingLotPrinter::printEntrySuccess(cout, spot);
            return SUCCESS;
        } else {
            ParkingLotPrinter::printEntryFailureNoSpot(cout);
            return NO_EMPTY_SPOT;
        }
    }
}

ParkingResult ParkingLot::genericGetSpot(UniqueArray<Vehicle,
        std::equal_to<Vehicle>> array, VehicleType vehicleType,
        LicensePlate licensePlate, ParkingSpot &parkingSpot) {
    for (int i = 0 ; i <array.getSize(); i++) {
        Vehicle* currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            if (currentVehicle->getLicensePlate() == licensePlate) {
                ParkingSpot newSpot = ParkingSpot(CAR, i);
                parkingSpot = newSpot;
                return SUCCESS;
            }
        }
    }
    return VEHICLE_ALREADY_PARKED;
}

ParkingResult ParkingLot::genericExitParking(UniqueArray<Vehicle,
        std::equal_to<Vehicle>> array, VehicleType vehicleType, LicensePlate
                            licensePlate, Time exitTime) {
    for (int i = 0; i < array.getSize(); i++) {
        Vehicle *currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            if (currentVehicle->getLicensePlate() == licensePlate) {
                int bill = currentVehicle->calculateParkingPrice(exitTime);
                ParkingSpot spot = ParkingSpot(vehicleType, i);
                ParkingLotPrinter::printExitSuccess(cout, spot,
                        exitTime, bill);
                array.remove(*currentVehicle);
                return SUCCESS;
            }
        }
    }
}

int ParkingLot::genericInspectParkingLot(Time currentTime, UniqueArray<Vehicle,
        std::equal_to<Vehicle>> array) {
    int count = 0;
    unsigned int oneHour = 1;
    for (int i = 0 ; i < array.getSize() ; i++) {
        Vehicle* currentVehicle = array.getElementByIndex(i);
        if (currentVehicle != nullptr) {
            unsigned int totalTime =
                    (currentTime - currentVehicle->getEntranceTime()).toHours();
            if (totalTime >= 24*oneHour) {
                count++;
                currentVehicle->markAsFined();
            }
        }
    }
    return count;
}
