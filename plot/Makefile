CC = g++
CFLAGS = -DDEBUG -ggdb -Wall -std=c++11

all: plot 

plot: plot.cpp
	$(CC) $(CFLAGS) plot.cpp -o plot \
                        -I./ \
                        -I/usr/include/root/ \
                        `root-config --ldflags` \
                        `${ROOTSYS}/bin/root-config --glibs` \
                        -Wl,--no-as-needed \
                        -fdiagnostics-color \
                        -Wno-error

clean:
	rm -f plot




