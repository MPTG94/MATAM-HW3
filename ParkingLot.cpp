//
// Created by Mor on 09/01/2020.
//

#include "provided_files/ParkingLot.h"

using namespace MtmParkingLot;

/**
 * Construct a parking lot object
 * @param parkingBlockSizes
 */
MtmParkingLot::ParkingLot::ParkingLot(unsigned int *parkingBlockSizes) {

}

/**
 * Destroy parking lot object
 */
MtmParkingLot::ParkingLot::~ParkingLot() {

}

/**
 * Register a vehicle in the parking lot
 * @param vehicleType
 * @param licensePlate
 * @param entranceTime
 * @return
 */
ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::enterParking(ParkingLotUtils::VehicleType vehicleType,
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
ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::getParkingSpot(ParkingLotUtils::LicensePlate licensePlate,
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
MtmParkingLot::ParkingLot::exitParking(ParkingLotUtils::LicensePlate licensePlate, ParkingLotUtils::Time exitTime) {
    return VEHICLE_ALREADY_PARKED;
}

/**
 * Summon an inspector to check vehicles in the parking lot
 * @param inspectionTime
 */
void MtmParkingLot::ParkingLot::inspectParkingLot(ParkingLotUtils::Time inspectionTime) {

}

/**
 * Print the contents of the parking lot object according to specification
 * @param os
 * @param parkingLot
 * @return
 */
std::ostream &MtmParkingLot::operator<<(std::ostream &os, const MtmParkingLot::ParkingLot &parkingLot) {
    return <#initializer#>;
}
