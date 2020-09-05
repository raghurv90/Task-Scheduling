#variables

CXX = g++
CXXFLAGS = -Wall -g

#creating an executable from created objects 

risingCity: risingCity.o RBT.o heap.o Building.o
	$(CXX) $(CXXFLAGS) -o risingCity risingCity.o RBT.o heap.o Building.o

#creating objects from cpp and header files

risingCity.o: risingCity.cpp input_parsing_functions.h Building.h nodeClass.h
	$(CXX) $(CXXFLAGS) -c risingCity.cpp	

RBT.o : RBT.cpp Building.h nodeClass.h
	$(CXX) $(CXXFLAGS) -c RBT.cpp	

heap.o : heap.cpp Building.h nodeClass.h
	$(CXX) $(CXXFLAGS) -c heap.cpp
	
Building.o : Building.cpp Building.h nodeClass.h
	$(CXX) $(CXXFLAGS) -c Building.cpp	