GCC=g++
CPPFLAGS=-lstdc++ -std=c++17
MODEL=element.cpp opz_calculator.cpp converter_to_opz.cpp parser.cpp model.cpp validator.cpp main.cpp
LIBFLAGS=--verbose -dynamiclib

dylib:
	$(GCC) $(CPPFLAGS) $(LIBFLAGS) $(MODEL) -o libSmC.dylib

clean:
	rm -rf *.o *.dylib