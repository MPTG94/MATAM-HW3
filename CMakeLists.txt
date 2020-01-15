cmake_minimum_required(VERSION 3.15)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(uniqueArr-Local ./provided_files/tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yuval ./provided_files/tests/OurUATests.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yonatan ./provided_files/tests/YonatanTests.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-ms ./provided_files/tests/msTests.cpp UniqueArray.h UniqueArrayImp.h)


add_executable(parkingLot-local ParkingLot.h MtmParkingLot.cpp
        ParkingLotTypes.h ParkingSpot.h ParkingSpot.cpp
        Time.h Time.cpp ParkingLotPrinter.h
        ParkingLotPrinter.cpp UniqueArray.h UniqueArrayImp.h ParkingLot.cpp Vehicle.h Vehicle.cpp)