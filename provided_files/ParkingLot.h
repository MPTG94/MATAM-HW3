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
        // TODO: mor
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        // TODO: mor
        ~ParkingLot();
        // TODO: sivan :) :-) =) :D
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        // TODO: sivan :) :-) =) :D
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        // TODO: sivan :) :-) =) :D
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        // TODO: sivan :) :-) =) :D
        void inspectParkingLot(Time inspectionTime);
        // TODO: mor
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
