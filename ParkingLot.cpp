//
// Created by Mor on 09/01/2020.
//

#include "provided_files/ParkingLot.h"

#include <utility>
#include <ostream>
#include "provided_files/ParkingLotPrinter.h"
using std::ostream;


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
ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::enterParking
                                    (ParkingLotUtils::VehicleType vehicleType,
                                    const ParkingLotUtils::LicensePlate&
                                    licensePlate,
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

ParkingResult ParkingLot::insertNewVehicle(UniqueArray
                                        <Vehicle,std::equal_to<Vehicle>> array,
                                        VehicleType vehicleType,LicensePlate
                                        licensePlate, Time entranceTime,
                                        const UniqueArray<Vehicle,
                                        std::equal_to<Vehicle>>& carArray) {

    Vehicle newVehicle = Vehicle(std::move(licensePlate), entranceTime,
                          vehicleType);
    int isExistInArray = array.contains(newVehicle);
    if (vehicleType==HANDICAPPED){
        int isExistInCar = carArray.contains(newVehicle);
        if (isExistInCar != -1) {
            ParkingSpot spot = ParkingSpot(vehicleType, isExistInCar);
            ParkingLotPrinter::printEntryFailureAlreadyParked(&os, spot);
            return VEHICLE_ALREADY_PARKED;
        }
    }
    if (isExistInArray != -1) {
        ParkingSpot spot = ParkingSpot(vehicleType, isExistInArray);
        ParkingLotPrinter::printEntryFailureAlreadyParked(&os, spot);
        return VEHICLE_ALREADY_PARKED;
    } else {
        if (array.getSize() - array.getCount() > 0) {
            unsigned int newIndex = array.insert(newVehicle);
            ParkingLotPrinter::printVehicle(&os, vehicleType,
                    newVehicle.getLicensePlate(), entranceTime);
            ParkingSpot spot = ParkingSpot(vehicleType, newIndex);
            ParkingLotPrinter::printEntrySuccess(&os, spot);
            return SUCCESS;
        } else {
            ParkingLotPrinter::printEntryFailureNoSpot(&os);
            return NO_EMPTY_SPOT;
        }
    }
}
