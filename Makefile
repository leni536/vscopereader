all: posix win32
	
posix: kiolvaso
	
win32: kiolvaso.exe
	
kiolvaso: kiolvaso.cpp
	g++ -g -o kiolvaso -std=c++11 kiolvaso.cpp

kiolvaso.exe: kiolvaso.cpp
	i686-w64-mingw32-g++-win32 -g -o kiolvaso.exe -static-libstdc++ -static-libgcc -std=c++11 kiolvaso.cpp
