OBJS = ArrayVector.cpp

#Change compiler here if required
CC = g++

OBJ_NAME = ArrayVector

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)