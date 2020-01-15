CC = g++
DEBUG_FLAGS =
OBJS = MtmParkingLot.o ParkingLot.o ParkingLot_print.o ParkingLot_main.o ParkingLot_tests.o amount_set.o
EXEC = MtmParkingLot
LIBS = -L. -lm -lmtm
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors

./provided_files/ParkingLot.h ./provided_files/MtmParkingLot.cpp
        ./provided_files/ParkingLotTypes.h ./provided_files/ParkingSpot.h ./provided_files/ParkingSpot.cpp
        ./provided_files/Time.h ./provided_files/Time.cpp ./provided_files/ParkingLotPrinter.h
        ./provided_files/ParkingLotPrinter.cpp UniqueArray.h UniqueArrayImp.h ParkingLot.cpp Vehicle.h Vehicle.cpp

# build ParkingLot using dependencies
$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(LIBS) $(OBJS) -o $@

# build example amount_set program with tests using dependencies
amount_set: amount_set.o amount_set_main.o amount_set_tests.o
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) amount_set.o amount_set_main.o amount_set_tests.o -o $@

# build ParkingLot tests runner library
ParkingLot_main.o: tests/ParkingLot_tests.h tests/ParkingLot_tests.c ParkingLot_tests.o ParkingLot.o
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) tests/$*.c

# build ParkingLot tests library
ParkingLot_tests.o: tests/ParkingLot_tests.c tests/ParkingLot_tests.h tests/test_utilities.h ParkingLot.o
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) tests/$*.c

# build ParkingLot library file
ParkingLot.o: ParkingLot.c ParkingLot.h amount_set.o ParkingLot_print.o
	$(CC) -c $(DEBUG_FLAGS) $(CFLAGS) $*.c

# build UniqueArray Class library file
uniqueArray.o: UniqueArray.h, UniqueArrayImp.h
    $(CC) -c $(DEBUG_FLAGS) $(CFLAGS) UniqueArray.h UniqueArrayImp.h

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
	rm -f amount_set_main.o amount_set_tests.o $(OBJS) $(EXEC)
