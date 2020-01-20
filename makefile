CC = g++
DEBUG_FLAGS =
OBJS = MtmParkingLot.o ParkingLot.o Vehicle.o Time.o ParkingSpot.o ParkingLotPrinter.o
EXEC = MtmParkingLot
LIBS =
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors

# build ParkingLot using dependencies
$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(LIBS) $(OBJS) -o $@

# build MtmParkingLot tests runner library
MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h UniqueArrayImp.h Vehicle.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingLot library file
ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h ParkingSpot.h UniqueArray.h UniqueArrayImp.h Vehicle.h ParkingLotPrinter.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build Vehicle Class library file
Vehicle.o: Vehicle.cpp Vehicle.h ParkingLotTypes.h ParkingSpot.h Time.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build Time Class library file
Time.o: Time.cpp Time.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingSpot Class library file
ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# build ParkingLotPrinter Class library file
ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.cpp

# clean working directory
clean:
	rm -f $(OBJS) $(EXEC)
