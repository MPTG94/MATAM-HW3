CC = g++
DEBUG_FLAGS =
OBJS = MtmParkingLot.o ParkingLot.o Vehicle.o Time.o ParkingSpot.o ParkingLotPrinter.o
EXEC = MtmParkingLot
LIBS =
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors

# build ParkingLot using dependencies
$(EXEC): $(OBJS) UniqueArray.h
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(LIBS) $(OBJS) -o $@

# build MtmParkingLot tests runner library
MtmParkingLot.o: MtmParkingLot.cpp ParkingLot.o ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingLot library file
ParkingLot.o: ParkingLot.cpp ParkingLot.h Vehicle.o Time.o ParkingSpot.o ParkingLotPrinter.o UniqueArray.h UniqueArrayImp.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build Vehicle Class library file
Vehicle.o: Vehicle.h Vehicle.cpp Time.o ParkingSpot.o ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build Time Class library file
Time.o: Time.h Time.cpp
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingSpot Class library file
ParkingSpot.o: ParkingSpot.h ParkingSpot.cpp
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingLotPrinter Class library file
ParkingLotPrinter.o: ParkingLotPrinter.h ParkingLotPrinter.cpp
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# clean working directory
clean:
	rm -f $(OBJS) $(EXEC)
