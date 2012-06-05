## Yay for make!
.PHONY:clean all
CC=gcc -I.
CXX=g++ -I.
AR=ar
RM=rm -f
CMAKE=cmake

default:
	@echo "look through this file for manual build targets (use all), otherwise, building using cmake now"
	mkdir -p build
	cd build; \
	$(CMAKE) ..; \
	$(MAKE);

all:
	@echo "THIS PROJECT IS LICENSED UNDER THE WTFPL \
	YOU CAN FIND IT IN LICENSE.TXT"

libscrummy-static.a: scrumcomps.o drupalauth.o scrummer2.o
	$(AR) qs $(@) $(^)

libscrummy-shared.so: scrumcomps.o drupalauth.o scrummer2.o
	$(CXX) -shared -fPIC -o $(@) $(^)

clean:
	$(RM) *.o *.a *.so

%.o: %.cc
	$(CXX) -c $(^)
