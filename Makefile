all: rfio

rfio: RCSwitch.o rfio.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o rfio
