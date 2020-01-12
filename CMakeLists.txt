cmake_minimum_required(VERSION 3.15)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(uniqueArr-Local ./provided_files/tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yuval ./provided_files/tests/OurUATests.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-ms ./provided_files/tests/msTests.cpp UniqueArray.h UniqueArrayImp.h)


add_executable(parkingLot-local ./provided_files/ParkingLot.h ./provided_files/MtmParkingLot.cpp
        ./provided_files/ParkingLotTypes.h ./provided_files/ParkingSpot.h ./provided_files/ParkingSpot.cpp
        ./provided_files/Time.h ./provided_files/Time.cpp ./provided_files/ParkingLotPrinter.h
        ./provided_files/ParkingLotPrinter.cpp UniqueArray.h UniqueArrayImp.h ParkingLot.cpp Vehicle.h Vehicle.cpp)