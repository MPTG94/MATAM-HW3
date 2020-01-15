cmake_minimum_required(VERSION 3.15)
project(hw3)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -pedantic-errors")
set(CMAKE_CXX_STANDARD 11)
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(uniqueArr-Local tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yuval tests/OurUATests.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yonatan tests/YonatanTests.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-ms tests/msTests.cpp UniqueArray.h UniqueArrayImp.h)


add_executable(parkingLot-local ParkingLot.h MtmParkingLot.cpp
        ParkingLotTypes.h ParkingSpot.h ParkingSpot.cpp
        Time.h Time.cpp ParkingLotPrinter.h
        ParkingLotPrinter.cpp UniqueArray.h UniqueArrayImp.h ParkingLot.cpp Vehicle.h Vehicle.cpp)