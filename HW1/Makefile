LIBS := -lSDL2 -lGLEW -lGL
CXXFLAGS := -std=c++14 -Wall -Wpedantic -g -I/usr/include/SDL2 -I/usr/include/GL

sources := $(wildcard *.cpp)
headers := $(wildcard *.h)

main: $(sources) $(headers)
	$(CXX) -o $@ $(CPPFLAGS) $(CXXFLAGS) $(sources) $(LIBS)

.PHONY: clean
clean:
	$(RM) main
