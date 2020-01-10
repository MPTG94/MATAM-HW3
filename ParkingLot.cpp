//
// Created by Mor on 09/01/2020.
//

#include "provided_files/ParkingLot.h"
#include "./provided_files/ParkingLotPrinter.h"

using namespace MtmParkingLot;

/**
 * Construct a parking lot object
 * @param parkingBlockSizes
 */
MtmParkingLot::ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
        : motorbikeArray(parkingBlockSizes[0]),
          handicapArray(parkingBlockSizes[1]),
          carArray(parkingBlockSizes[2]) {
}

/**
 * Destroy parking lot object
 */
MtmParkingLot::ParkingLot::~ParkingLot() = default;

/**
 * Register a vehicle in the parking lot
 * @param vehicleType
 * @param licensePlate
 * @param entranceTime
 * @return
 */
ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::enterParking(
        ParkingLotUtils::VehicleType vehicleType,
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time entranceTime) {
    return VEHICLE_ALREADY_PARKED;
}

/**
 * Get the place a vehicle is parked at
 * @param licensePlate
 * @param parkingSpot
 * @return
 */
ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::getParkingSpot(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::ParkingSpot &parkingSpot) const {
    return VEHICLE_ALREADY_PARKED;
}

/**
 * Remove a vehicle from the parking lot
 * @param licensePlate
 * @param exitTime
 * @return
 */
ParkingLotUtils::ParkingResult
MtmParkingLot::ParkingLot::exitParking(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time exitTime) {
    return VEHICLE_ALREADY_PARKED;
}

/**
 * Summon an inspector to check vehicles in the parking lot
 * @param inspectionTime
 */
void MtmParkingLot::ParkingLot::inspectParkingLot(
        ParkingLotUtils::Time inspectionTime) {

}

/**
 * Print the contents of the parking lot object according to specification
 * @param os
 * @param parkingLot
 * @return
 */
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
