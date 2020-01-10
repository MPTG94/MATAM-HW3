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

    public:
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
