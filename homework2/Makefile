a.exe: bmp_image.o position.o filter.o main.cpp
	g++ main.cpp -g position.o bmp_image.o filter.o 

bmp_image.o: BmpImage.cpp BmpImage.hpp
	g++ -c -g BmpImage.cpp -o bmp_image.o 

position.o: Position.cpp Position.hpp
	g++ -c -g Position.cpp -o position.o 

filter.o: Filter.cpp Filter.hpp
	g++ -c -g Filter.cpp -o filter.o