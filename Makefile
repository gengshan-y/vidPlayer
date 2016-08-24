CC=g++
CXXFLAGS=-std=c++0x -gdwarf-3 -Wall `pkg-config opencv --cflags`
# c++0x partially support c++11 features

LDFLAGS=-g  `pkg-config opencv --libs`

all: clean vidPlayer mv

vidPlayer:
	${CC} -o vidPlayer vidPlayer.cpp ${CXXFLAGS} ${LDFLAGS}

clean: 
	rm -f vidPlayer *.o

mv: 
	mv vidPlayer /home/gengshan/bin/
