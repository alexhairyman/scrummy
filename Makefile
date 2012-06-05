## Yay for make!
.PHONY:clean all
CC=gcc -I.
CXX=g++ -I.
AR=ar
RM=rm -f
CMAKE=cmake

default:
	@echo "look through this file for manual build targets, otherwise, building using cmake now"
	mkdir -p build
	cd build; \
	$(CMAKE) ..; \
	$(MAKE);

all:
	@echo "Select a target"

libscrummy-static.a: scrumcomps.o drupalauth.o scrummer2.o
	$(AR) qs $(@) $(^)

libscrummy-shared.so: scrumcomps.o drupalauth.o scrummer2.o
	$(CXX) -shared -fPIC -o $(@) $(^)

clean:
	$(RM) *.o *.a *.so

%.o: %.cc
	$(CXX) -c $(^)
