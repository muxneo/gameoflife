# gameoflife
Conway's Game of Life in C

Stand-Alone GOL implementation
1) Install cmake if it is not on your system ( on ubuntu "sudo apt install cmake" )
2) go to build directory
3) Run "cmake .."
4) Run make
5) cd ../bin
6) ./gol

Client-Server GOL implementation
7) In one terminal run ./gol-server (run the server first)
8) Start another terminal and run ./gol-client


Limitations:
- Some features are missing
- server needs to be started first
- After client is quit using 'q' server needs to be restarted.

