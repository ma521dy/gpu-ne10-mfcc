CC = g++
CCFLAGS= -Wall -pthread -lpulse-simple -lpulse -lNE10
EXEC_NAME= audio_test
LIBS= -L/usr/local/lib/ 
OBJ = main.o circular.o recordmanager.o client.o audio.o mfcc.o

all: $(EXEC_NAME) clean

$(EXEC_NAME) : $(OBJ)
	$(CC) -o $(EXEC_NAME) $(OBJ) $(CCFLAGS) $(LIBS)

main.o : src/main.cpp
	$(CC) $(CCFLAGS) -c -o main.o src/main.cpp 

circular.o : src/circular.cpp include/circular.h
	$(CC) $(CCFLAGS) -c -o circular.o src/circular.cpp 

recordmanager.o : src/recordmanager.cpp include/recordmanager.h
	$(CC) $(CCFLAGS) -c -o recordmanager.o src/recordmanager.cpp 

client.o : src/client.cpp include/client.h
	$(CC) $(CCFLAGS) -c -o client.o src/client.cpp 

audio.o : src/audio.cpp include/audio.h
	$(CC) $(CCFLAGS) -c -o audio.o src/audio.cpp 

mfcc.o : src/mfcc.cpp include/mfcc.h
	$(CC) $(CCFLAGS) -c -o mfcc.o src/mfcc.cpp 
	
clean :
	rm -rf *.o

cleanall :
	rm -rf *.o
	rm $(EXEC_NAME)
