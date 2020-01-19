//
// Created by Mor on 09/01/2020.
//
#include <algorithm>
#include <utility>
#include <vector>
#include "ParkingLot.h"
#include "ParkingLotPrinter.h"


using namespace MtmParkingLot;
using std::ostream;
using std::cout;

namespace MtmParkingLot {

    static const int HOURS_IN_A_DAY = 24;

    struct CompareVehicles {
        bool operator()(Vehicle vehicle1, Vehicle vehicle2) {
            return (vehicle1.getParkingSpot() < vehicle2.getParkingSpot());
        }
    };

    std::ostream
    &operator<<(std::ostream &os,
                const ParkingLot &parkingLot) {
        vector<Vehicle> vehicleVector = vector<Vehicle>();
        vehicleVector = parkingLot.fillVectorFromArray(vehicleVector,
                                                       MOTORBIKE);
        vehicleVector = parkingLot.fillVectorFromArray(vehicleVector,
                                                       HANDICAPPED);
        vehicleVector = parkingLot.fillVectorFromArray(vehicleVector,
                                                       CAR);
        ParkingLotPrinter::printParkingLotTitle(os);
        sort(vehicleVector.begin(), vehicleVector.end(),
             CompareVehicles());
        for (unsigned int i = 0; i < vehicleVector.size(); i++) {
            Vehicle vehicle = vehicleVector[i];
            ParkingLotPrinter::printVehicle(os, vehicle.getVehicleType(),
                                            vehicle.getLicensePlate(),
                                            vehicle.getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os,
                                                vehicle.getParkingSpot());
        }
        return os;
    }


    ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
            : motorbikeArray(parkingBlockSizes[0]),
              handicapArray(parkingBlockSizes[1]),
              carArray(parkingBlockSizes[2]) {
    }

    ParkingLot::~ParkingLot() = default;

    ParkingLotUtils::ParkingResult ParkingLot::enterParking(
            ParkingLotUtils::VehicleType vehicleType,
            ParkingLotUtils::LicensePlate &licensePlate,
            ParkingLotUtils::Time entranceTime) {
        if (vehicleType == MOTORBIKE) {
            return insertNonHandicap(MOTORBIKE,
                                     licensePlate, entranceTime);
        } else if (vehicleType == CAR) {
            return insertNonHandicap(CAR,
                                     licensePlate, entranceTime);
        } else {
            return insertHandicap(HANDICAPPED,
                                  licensePlate, entranceTime);
        }
    }

    ParkingLotUtils::ParkingResult ParkingLot::getParkingSpot(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::ParkingSpot &parkingSpot) const {
        if (genericGetSpot(carArray, licensePlate,
                           parkingSpot) == SUCCESS ||
            genericGetSpot(motorbikeArray,
                           licensePlate, parkingSpot) == SUCCESS ||
            genericGetSpot(handicapArray,
                           licensePlate, parkingSpot) == SUCCESS) {
            return SUCCESS;
        } else {
            return VEHICLE_NOT_FOUND;
        }
    }

    ParkingLotUtils::ParkingResult
    ParkingLot::exitParking(
            ParkingLotUtils::LicensePlate licensePlate,
            ParkingLotUtils::Time exitTime) {
        ParkingSpot spot;
        if (getParkingSpot(licensePlate, spot) == VEHICLE_NOT_FOUND) {
            ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        if (this->removeNonHandicap(MOTORBIKE, licensePlate,
                                    exitTime) == SUCCESS ||
            this->removeNonHandicap(CAR, licensePlate,
                                    exitTime) == SUCCESS ||
            this->removeHandicap(licensePlate, exitTime) == SUCCESS) {
            return SUCCESS;
        }
        ParkingLotPrinter::printExitFailure(cout, licensePlate);
        return VEHICLE_NOT_FOUND;
    }

    void ParkingLot::inspectParkingLot(
            ParkingLotUtils::Time inspectionTime) {
        int fineCounter = 0;
        fineCounter += genericInspectParkingLot(inspectionTime,
                                                carArray);
        fineCounter += genericInspectParkingLot(inspectionTime,
                                                motorbikeArray);
        fineCounter += genericInspectParkingLot(inspectionTime,
                                                handicapArray);
        ParkingLotPrinter::printInspectionResult(cout, inspectionTime,
                                                 fineCounter);
    }

    vector<Vehicle>
    ParkingLot::fillVectorFromArray(vector<Vehicle> &vehicleVector,
                                    VehicleType type) const {
        switch (type) {
            case ParkingLotUtils::MOTORBIKE:
                for (unsigned int i = 0;
                     i < this->motorbikeArray.getSize(); i++) {
                    Vehicle *vehicle = this->motorbikeArray.getElementByIndex(
                            i);
                    if (vehicle != nullptr) {
                        vehicleVector.push_back(*vehicle);
                    }
                }
                return vehicleVector;
            case ParkingLotUtils::HANDICAPPED:
                for (unsigned int i = 0;
                     i < this->handicapArray.getSize(); i++) {
                    Vehicle *vehicle = this->handicapArray.getElementByIndex(i);
                    if (vehicle != nullptr) {
                        vehicleVector.push_back(*vehicle);
                    }
                }
                return vehicleVector;
            case CAR:
                for (unsigned int i = 0; i < this->carArray.getSize(); i++) {
                    Vehicle *vehicle = this->carArray.getElementByIndex(i);
                    if (vehicle != nullptr) {
                        vehicleVector.push_back(*vehicle);
                    }
                }
                return vehicleVector;
        }
        // Shouldn't get here.
        return vehicleVector;
    }

    ParkingResult ParkingLot::insertNonHandicap(VehicleType vehicleType,
                                                LicensePlate licensePlate,
                                                Time entranceTime) {
        if (vehicleType == MOTORBIKE) {
            return insertMotorbike(vehicleType, std::move(licensePlate),
                                   entranceTime);
        } else {
            return insertCar(vehicleType, std::move(licensePlate),
                             entranceTime);
        }
    }

    ParkingResult ParkingLot::insertCar(VehicleType vehicleType,
                                        LicensePlate licensePlate,
                                        Time entranceTime) {
        Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                                     vehicleType);
        int isVehicleInArray = this->carArray.contains(newVehicle);
        if (isVehicleInArray != NOT_FOUND) {
            Vehicle *oldVehicle = this->carArray.getElementByIndex(
                    isVehicleInArray);
            printVehicleParkedByVehicle(oldVehicle);
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (carArray.getSize() - carArray.getCount() > 0) {
                unsigned int newIndex = carArray.insert(newVehicle);
                ParkingSpot spot = ParkingSpot(vehicleType, newIndex);
                printVehicleEntryByVehicle(newVehicle, spot);
                carArray.getElementByIndex(newIndex)->setParkingSpot(spot);
                return SUCCESS;
            } else {
                printNoRoomForVehicleByVehicle(newVehicle);
                return NO_EMPTY_SPOT;
            }
        }
    }

    ParkingResult ParkingLot::insertMotorbike(VehicleType vehicleType,
                                              LicensePlate licensePlate,
                                              Time entranceTime) {
        Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                                     vehicleType);
        int isVehicleInArray = this->motorbikeArray.contains(newVehicle);
        if (isVehicleInArray != NOT_FOUND) {
            Vehicle *oldVehicle = this->motorbikeArray.getElementByIndex(
                    isVehicleInArray);
            printVehicleParkedByVehicle(oldVehicle);
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (motorbikeArray.getSize() - motorbikeArray.getCount() > 0) {
                unsigned int newIndex = motorbikeArray.insert(newVehicle);
                ParkingSpot spot = ParkingSpot(vehicleType, newIndex);
                printVehicleEntryByVehicle(newVehicle, spot);
                motorbikeArray.getElementByIndex(newIndex)->setParkingSpot(
                        spot);
                return SUCCESS;
            } else {
                printNoRoomForVehicleByVehicle(newVehicle);
                return NO_EMPTY_SPOT;
            }
        }
    }

    ParkingResult ParkingLot::insertHandicap(VehicleType vehicleType,
                                             LicensePlate licensePlate,
                                             Time entranceTime) {
        Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                                     vehicleType);
        int isInHandicapArray = this->handicapArray.contains(newVehicle);
        int isInCarArray = this->carArray.contains(newVehicle);
        if (isInHandicapArray != NOT_FOUND) {
            Vehicle *oldVehicle = this->handicapArray.getElementByIndex(
                    isInHandicapArray);
            printVehicleParkedByVehicle(oldVehicle);
            return VEHICLE_ALREADY_PARKED;
        } else if (isInCarArray != NOT_FOUND) {
            Vehicle *oldVehicle = this->carArray.getElementByIndex(
                    isInCarArray);
            printVehicleParkedByVehicle(oldVehicle);
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (this->handicapArray.getSize() - this->handicapArray.getCount() >
                0) {
                return insertHandicapToHandicapBlock(newVehicle);
            } else if (this->carArray.getSize() - this->carArray.getCount() >
                       0) {
                return insertHandicapToCarBlock(newVehicle);
            } else {
                printNoRoomForVehicleByVehicle(newVehicle);
                return NO_EMPTY_SPOT;
            }
        }
    }

    ParkingResult
    ParkingLot::insertHandicapToHandicapBlock(const Vehicle &vehicle) {
        unsigned int newIndex = handicapArray.insert(vehicle);
        ParkingSpot spot = ParkingSpot(HANDICAPPED, newIndex);
        printVehicleEntryByVehicle(vehicle, spot);
        handicapArray.getElementByIndex(newIndex)->setParkingSpot(
                spot);
        return SUCCESS;
    }

    ParkingResult ParkingLot::insertHandicapToCarBlock(const Vehicle &vehicle) {
        unsigned int newIndex = carArray.insert(vehicle);
        ParkingSpot spot = ParkingSpot(CAR, newIndex);
        printVehicleEntryByVehicle(vehicle, spot);
        carArray.getElementByIndex(newIndex)->setParkingSpot(
                spot);
        return SUCCESS;
    }

    ParkingResult ParkingLot::genericGetSpot(const UniqueArray<Vehicle,
            std::equal_to<Vehicle>> &array, const LicensePlate &licensePlate,
                                             ParkingSpot &parkingSpot) {
        for (unsigned int i = 0; i < array.getSize(); i++) {
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

    ParkingResult ParkingLot::removeNonHandicap
            (VehicleType type,
             const LicensePlate &licensePlate,
             Time exitTime) {
        if (type == MOTORBIKE) {
            for (unsigned int i = 0; i < motorbikeArray.getSize(); i++) {
                Vehicle *currentVehicle = motorbikeArray.getElementByIndex(i);
                if (currentVehicle != nullptr) {
                    if (currentVehicle->getLicensePlate() == licensePlate) {
                        int bill = currentVehicle->calculateParkingPrice(
                                exitTime);
                        printVehicleExitByVehicle(currentVehicle, exitTime,
                                                  bill);
                        motorbikeArray.remove(*currentVehicle);
                        return SUCCESS;
                    }
                }
            }
        } else {
            for (unsigned int i = 0; i < carArray.getSize(); i++) {
                Vehicle *currentVehicle = carArray.getElementByIndex(i);
                if (currentVehicle != nullptr) {
                    if (currentVehicle->getLicensePlate() == licensePlate) {
                        int bill = currentVehicle->calculateParkingPrice(
                                exitTime);
                        printVehicleExitByVehicle(currentVehicle, exitTime,
                                                  bill);
                        carArray.remove(*currentVehicle);
                        return SUCCESS;
                    }
                }
            }
        }
        return VEHICLE_NOT_FOUND;
    }

    void
    ParkingLot::printVehicleEntryByVehicle(Vehicle vehicle, ParkingSpot spot) {
        ParkingLotPrinter::printVehicle(cout, vehicle.getVehicleType(),
                                        vehicle.getLicensePlate(),
                                        vehicle.getEntranceTime());
        ParkingLotPrinter::printEntrySuccess(cout, spot);
    }

    void ParkingLot::printNoRoomForVehicleByVehicle(Vehicle vehicle) {
        ParkingLotPrinter::printVehicle(cout, vehicle.getVehicleType(),
                                        vehicle.getLicensePlate(),
                                        vehicle.getEntranceTime());
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
    }

    void ParkingLot::printVehicleParkedByVehicle(Vehicle *vehicle) {
        ParkingLotPrinter::printVehicle(cout, vehicle->getVehicleType(),
                                        vehicle->getLicensePlate(),
                                        vehicle->getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(
                cout,
                vehicle->getParkingSpot());
    }

    void ParkingLot::printVehicleExitByVehicle(Vehicle *vehicle, Time exitTime,
                                               int bill) {
        ParkingLotPrinter::printVehicle(cout,
                                        vehicle->getVehicleType(),
                                        vehicle->getLicensePlate(),
                                        vehicle->getEntranceTime());
        ParkingLotPrinter::printExitSuccess(cout,
                                            vehicle->getParkingSpot(),
                                            exitTime, bill);
    }

    ParkingResult ParkingLot::removeHandicap(const LicensePlate &licensePlate,
                                             Time exitTime) {
        for (unsigned int i = 0; i < handicapArray.getSize(); i++) {
            Vehicle *currentVehicle = handicapArray.getElementByIndex(i);
            if (currentVehicle != nullptr) {
                if (currentVehicle->getLicensePlate() == licensePlate) {
                    int bill = currentVehicle->calculateParkingPrice(
                            exitTime);
                    printVehicleExitByVehicle(currentVehicle, exitTime, bill);
                    handicapArray.remove(*currentVehicle);
                    return SUCCESS;
                }
            }
        }
        for (unsigned int i = 0; i < carArray.getSize(); i++) {
            Vehicle *currentVehicle = carArray.getElementByIndex(i);
            if (currentVehicle != nullptr) {
                if (currentVehicle->getLicensePlate() == licensePlate) {
                    int bill = currentVehicle->calculateParkingPrice(
                            exitTime);
                    printVehicleExitByVehicle(currentVehicle, exitTime, bill);
                    carArray.remove(*currentVehicle);
                    return SUCCESS;
                }
            }
        }
        return SUCCESS;
    }

    int ParkingLot::genericInspectParkingLot
            (Time currentTime,
             const UniqueArray<Vehicle,
                     std::equal_to<Vehicle>> &array) {
        int count = 0;
        unsigned int oneHour = 1;
        for (unsigned int i = 0; i < array.getSize(); i++) {
            Vehicle *currentVehicle = array.getElementByIndex(i);
            if (currentVehicle != nullptr) {
                if (!currentVehicle->isFined()) {
                    unsigned int totalTime =
                            (currentTime -
                             currentVehicle->getEntranceTime()).toHours();
                    if (totalTime > HOURS_IN_A_DAY * oneHour) {
                        count++;
                        currentVehicle->markAsFined();
                    }
                }
            }
        }
        return count;
    }
}