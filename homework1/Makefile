a.exe: main.cpp Pixel.hpp position.o gradient.o bmp_image.o processor.o
	g++ main.cpp position.o bmp_image.o gradient.o processor.o

gradient.o: Gradient.cpp
	g++ -c Gradient.cpp -o gradient.o

position.o: Position.cpp
	g++ -c Position.cpp -o position.o

bmp_image.o: BmpImage.cpp
	g++ -c BmpImage.cpp -o bmp_image.o

processor.o: Processor.cpp
	g++ -c Processor.cpp -o processor.o