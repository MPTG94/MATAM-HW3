#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include <vector>
#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"


namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;
    using std::vector;

    class ParkingLot {
    private:
        UniqueArray<Vehicle, std::equal_to<Vehicle>> motorbikeArray;
        UniqueArray<Vehicle, std::equal_to<Vehicle>> handicapArray;
        UniqueArray<Vehicle, std::equal_to<Vehicle>> carArray;

        /**
         * Insert a handicap car to the parking lot
         * @param vehicleType The type of vehicle to enter
         * @param licensePlate The plate of the vehicle
         * @param entranceTime The time the vehicle entered the lot
         * @return SUCCESS if the vehicle entered successfully
         * ALREADY_PARKED if the vehicle is already in the lot
         * NO_EMPTY_SPOT if the lot is full
         */
        ParkingResult insertHandicap(VehicleType vehicleType,
                                     LicensePlate licensePlate,
                                     Time entranceTime);

        /**
         * Insert a non handicap car to the parking lot
         * @param vehicleType The type of vehicle to enter
         * @param licensePlate The plate of the vehicle
         * @param entranceTime The time the vehicle entered the lot
         * @return SUCCESS if the vehicle entered successfully
         * ALREADY_PARKED if the vehicle is already in the lot
         * NO_EMPTY_SPOT if the lot is full
         */
        ParkingResult insertNonHandicap(VehicleType vehicleType, LicensePlate
        licensePlate, Time entranceTime);

        /**
         * Returns the parking spot of an input vehicle
         * @param array The array to get the parking spot from
         * @param licensePlate The plate of the vehicle to get a spot for
         * @param parkingSpot The parking spot variable to insert spot data into
         * @return SUCCESS if the parking spot was returned
         */
        static ParkingResult genericGetSpot(const UniqueArray<Vehicle,
                std::equal_to<Vehicle>> &array,
                                            const LicensePlate &licensePlate,
                                            ParkingSpot &parkingSpot);

        /**
         * Inspects an input parking lot and returns the number of vehicles
         * that were fined in the inspection
         * @param currentTime The time of the inspection
         * @param array The array of the lot begin inspected
         * @return The number of cars fined during the inspection
         */
        static int
        genericInspectParkingLot(Time currentTime, const UniqueArray<Vehicle,
                std::equal_to<Vehicle>> &array);

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
        ~ParkingLot() = delete;

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
        ParkingResult
        enterParking(VehicleType vehicleType, LicensePlate &licensePlate,
                     Time entranceTime);

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

        /**
         * Receives a license plate of a vehicle and returns it's parking spot
         * @param licensePlate The license plate of the vehicle to get it's
         * parking spot
         * @param parkingSpot A ParkingSpot object to insert details into
         * @return Fills the ParkingSpot object with details of the parking
         * spot of the input vehicle, returns SUCCESS if the vehicle was found
         * and VEHICLE_NOT_FOUND otherwise
         */
        ParkingResult getParkingSpot(LicensePlate licensePlate,
                                     ParkingSpot &parkingSpot) const;

        /**
         * Checks all of the vehicles in the parking lot and gives them a fine
         * based on the input inspection time if necessary
         * The function will print the results of the inspection
         * @param inspectionTime The time at which the inspector visits the lot
         */
        void inspectParkingLot(Time inspectionTime);

        /**
         * Fills the vector of vehicles in the parking lot from a vehicle array
         * @param vehicleVector The vector to fill with vehicles
         * @param type The type of vehicles to insert into the array
         * @return THe vector after filling with vehicles
         */
        vector<Vehicle>
        fillVectorFromArray(vector<Vehicle> &vehicleVector,
                            VehicleType type) const;

        /**
         * A print function of the parking lot
         * @param os An ostream reference to write to stdout
         * @param parkingLot The parking lot object to print
         * @return An ostream to continue printing
         */
        friend ostream &operator<<(ostream &os, const ParkingLot &parkingLot);

        /**
         * Prints the information of a vehicle leaving the lot
         * @param vehicle The vehicle leaving the lot
         * @param exitTime The time the vehicle left
         * @param bill The price the vehicle needs to pay
         */
        static void
        printVehicleExitByVehicle(Vehicle *vehicle, Time exitTime,
                                  unsigned int bill);

        /**
         * Prints the information of a vehicle entering the lot
         * @param vehicle The vehicle entering the lot
         * @param spot The parking spot of the new vehicle
         */
        static void
        printVehicleEntryByVehicle(Vehicle vehicle, ParkingSpot spot);

        /**
         * Prints the information of a vehicle that is already parked in the lot
         * @param vehicle The vehicle that is already parked
         */
        static void printVehicleParkedByVehicle(Vehicle *vehicle);

        /**
         * Prints a message saying there is no more room for the vehicle in the
         * parking lot
         * @param vehicle The vehicle attempting to enter the lot
         */
        static void printNoRoomForVehicleByVehicle(Vehicle vehicle);

        /**
         * Removes a non handicap vehicle from the parking lot
         * @param type The type of vehicle to remove
         * @param licensePlate The plate of the vehicle to remove
         * @param exitTime The time the vehicle was removed
         * @return SUCCESS if the vehicle was removed
         * VEHICLE_NOT_FOUND if the vehicle wasn't parked
         */
        ParkingResult removeNonHandicap(VehicleType type,
                                        const LicensePlate &licensePlate,
                                        Time exitTime);

        /**
         * Removes a handicap vehicle from the parking lot
         * @param type The type of vehicle to remove
         * @param licensePlate The plate of the vehicle to remove
         * @param exitTime The time the vehicle was removed
         * @return SUCCESS if the vehicle was removed
         * VEHICLE_NOT_FOUND if the vehicle wasn't parked
         */
        ParkingResult
        removeHandicap(const LicensePlate &licensePlate,
                       Time exitTime);

        /**
         * Inserts a motorbike to the lot
         * @param vehicleType The type of vehicle
         * @param licensePlate THe plate of the vehicle
         * @param entranceTime The time the vehicle entered the lot
         * @return SUCCESS if the vehicle entered the lot
         * VEHICLE_ALREADY_PARKED if the vehicle is already in the lot
         * NO_EMPTY_SPOT if the lot is full
         */
        ParkingResult
        insertMotorbike(VehicleType vehicleType, LicensePlate licensePlate,
                        Time entranceTime);

        /**
         * Inserts a car to the lot
         * @param vehicleType The type of vehicle
         * @param licensePlate THe plate of the vehicle
         * @param entranceTime The time the vehicle entered the lot
         * @return SUCCESS if the vehicle entered the lot
         * VEHICLE_ALREADY_PARKED if the vehicle is already in the lot
         * NO_EMPTY_SPOT if the lot is full
         */
        ParkingResult
        insertCar(VehicleType vehicleType, LicensePlate licensePlate,
                  Time entranceTime);

        /**
         * Inserts a handicap car to the handicap lot
         * @param vehicle The vehicle to insert to the lot
         * @return SUCCESS if the vehicle entered the lot
         */
        ParkingResult
        insertHandicapToHandicapBlock(const Vehicle &vehicle);

        /**
         * Inserts a handicap car to the car lot
         * @param vehicle The vehicle to insert to the lot
         * @return SUCCESS if the vehicle entered the lot
         */
        ParkingResult
        insertHandicapToCarBlock(const Vehicle &vehicle);
    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
