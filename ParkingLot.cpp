//
// Created by Mor on 09/01/2020.
//

#include "provided_files/ParkingLot.h"

#include <utility>
#include "ostream"
#include "provided_files/ParkingLotPrinter.h"
using std::move;
unsigned std::ostream;


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
    if (vehicleType == HANDICAPPED) {
        Vehicle newHandicapped = Vehicle(licensePlate, entranceTime, vehicleType);
        int isExistInHandicap = handicapArray.contains(newHandicapped);
        if (isExistInHandicap = !-1) {
            ParkingSpot spot = ParkingSpot(vehicleType, isExistInHandicap);
            ParkingLotPrinter::printEntryFailureAlreadyParked(&os, spot);
            return VEHICLE_ALREADY_PARKED;
        }
        int isExistInCar = carArray.contains(newHandicapped);
        if (isExistInCar = !-1) {
            ParkingSpot spot = ParkingSpot(vehicleType[2], isExistInHandicap);
            ParkingLotPrinter::printEntryFailureAlreadyParked(&os, spot);
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (handicapArray.getSize() - handicapArray.getCount() > 0) {
                int newCarIndex = handicapArray.insert(newHandicapped);
                ParkingLotPrinter::printVehicle(&os, vehicleType, newHandicapped.getLicensePlate(), entranceTime);
                ParkingSpot spot = ParkingSpot(vehicleType, newCarIndex);
                ParkingLotPrinter::printEntrySuccess(&os, spot);
                return SUCCESS;
            }
            else {
                ParkingLotPrinter::printEntryFailureNoSpot(&os);
                return NO_EMPTY_SPOT;
            }
        }
    }

    else if (vehicleType == MOTORBIKE) {
        Vehicle newMotorbike = vehicle(licensePlate, entranceTime, vehicleType);
        int isExistInMotorbike = motorbikeArray.contains(newMotorbike);
        if (isExistInMotorbike !=1) {
            ParkingSpot spot = ParkingSpot(vehicleType, isExistInMotorbike);
            ParkingLotPrinter::printEntryFailureAlreadyParked(&os, spot);
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (motorbikeArray.getSize() - motorbikeArray.getCount() > 0) {
                int newCMotorbikeIndex = handicapArray.insert(newHandicapped);
                ParkingLotPrinter::printVehicle(&os, vehicleType, newHandicapped.getLicensePlate(), entranceTime);
                ParkingSpot spot = ParkingSpot(vehicleType, newCarIndex);
                ParkingLotPrinter::printEntrySuccess(&os, spot);
                return SUCCESS;
            }
            else {
                ParkingLotPrinter::printEntryFailureNoSpot(&os);
                return NO_EMPTY_SPOT;
            }

    }
    return ;
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
