#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include <functional>
#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "../UniqueArray.h"
#include "../Vehicle.h"


namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
    private:
        UniqueArray<Vehicle, std::equal_to<Vehicle>> motorbikeArray;
        UniqueArray<Vehicle, std::equal_to<Vehicle>> handicapArray;
        UniqueArray<Vehicle, std::equal_to<Vehicle>> carArray;

        static ParkingResult insertNewVehicle (UniqueArray<Vehicle,
                std::equal_to<Vehicle>> array, VehicleType vehicleType,
                LicensePlate licensePlate, Time entranceTime, const UniqueArray<Vehicle,
                std::equal_to<Vehicle>>& carArray);

    public:
        /**
         * Creates a new ParkingLot object based on the block sizes specified
         * @param parkingBlockSizes An int array containing the sizes of the
         * different parking blocks
         */
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        /**
         * Deletes an instance of ParkingLot
         */
        ~ParkingLot();
        // TODO: sivan :) :-) =) :D
        /**
         * Registers a new vehicle to the parking lot
         * @param vehicleType The type of the the vehicle based on the
         * VehicleType enum
         * @param licensePlate The license plate of the vehicle
         * @param entranceTime The time the vehicle entered the parking lot
         * @return Prints the details of the vehicle when parked and returns
         * SUCCESS
         * Prints that parking failed if the lot is full and returns
         * NO_EMPTY_SPOT
         * Prints that the vehicle is already parked if the is inside the lot
         * and returns ALREADY_PARKED
         */
        ParkingResult enterParking(VehicleType vehicleType, const LicensePlate& licensePlate, Time entranceTime);
        // TODO: sivan :) :-) =) :D
        /**
         * Removes a vehicle from the parking lot
         * @param licensePlate The license plate of the vehicle to remove
         * @param exitTime The time at which the vehicle was removed from the
         * parking lot
         * @return Prints the details of the vehicle which was removed
         * and returns PARKING_SUCCESS if the vehicle is in the parking lot
         * Prints that the vehicle was failed to remove and returns
         * VEHICLE_NOT_FOUND otherwise
         */
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        // TODO: sivan :) :-) =) :D
        /**
         * Receives a license plate of a vehicle and returns it's parking spot
         * @param licensePlate The license plate of the vehicle to get it's
         * parking spot
         * @param parkingSpot A ParkingSpot object to insert details into
         * @return Fills the ParkingSpot object with details of the parking
         * spot of the input vehicle, returns SUCCESS if the vehicle was found
         * and VEHICLE_NOT_FOUND otherwise
         */
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        // TODO: sivan :) :-) =) :D
        /**
         * Checks all of the vehicles in the parking lot and gives them a fine
         * based on the input inspection time if necessary
         * The function will print the results of the inspection
         * @param inspectionTime The time at which the inspector visits the lot
         */
        void inspectParkingLot(Time inspectionTime);
        /**
         * A print function of the parking lot
         * @param os An ostream reference to write to stdout
         * @param parkingLot The parking lot object to print
         * @return An ostream to continue printing
         */
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
        /**
         * Receives a vehicle types and calls the correct printing function for
         * the input type
         * @param os An ostream reference to write to stdout
         * @param type
         * @return
         */
        ostream & printVehiclesOfType(ostream& os, VehicleType type) const;
        /**
         * Prints all Motorbikes in the parking lot
         * @param os An ostream reference to write to stdout
         * @return An ostream to continue printing
         */
        ostream& printMotorbikes(ostream& os) const;
        /**
         * Prints all Handicapped cars in the parking lot
         * @param os An ostream reference to write to stdout
         * @return An ostream to continue printing
         */
        ostream& printHandicapped(ostream& os) const;
        /**
         * Prints all cars in the parking lot
         * @param os An ostream reference to write to stdout
         * @return An ostream to continue printing
         */
        ostream& printCars(ostream& os) const;

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
