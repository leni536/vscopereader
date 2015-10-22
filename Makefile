all: posix win32
	
posix: vscopereader
	
win32: vscopereader.exe
	
vscopereader: vscopereader.cpp
	g++ -g -o vscopereader -std=c++11 vscopereader.cpp

vscopereader.exe: vscopereader.cpp
	i686-w64-mingw32-g++-win32 -g -o vscopereader.exe -static-libstdc++ -static-libgcc -std=c++11 vscopereader.cpp

clean:
	rm -f vscopereader vscopereader.exe

.PHONY: all posix win32 clean
