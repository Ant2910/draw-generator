# Makefile for draw-generator
# Commands:
# Generating executable with: make
# Delete the files from the obj/ and doc/ subdirectories with : make clean
# Generating documentation with: make doc


#Compiler variable
CXX = g++
#Compiler version variable
CXXFLAGS = -std=c++20
#Source code directory variable
SRCDIR = src
#Object code directory variable
OBJDIR = obj


#Rule1: Generate executable for UrnUnitTests
$(OBJDIR)/UrnUnitTests: $(OBJDIR)/UrnUnitTests.o $(OBJDIR)/urn.o
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/UrnUnitTests $(OBJDIR)/UrnUnitTests.o $(OBJDIR)/urn.o


#Rule2: Generate object code for urn.cpp
$(OBJDIR)/urn.o: $(SRCDIR)/urn.cpp $(SRCDIR)/urn.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/urn.o -c $(SRCDIR)/urn.cpp


#Rule3: Generate object code for UrnUnitTests.cpp
$(OBJDIR)/UrnUnitTests.o: $(SRCDIR)/UrnUnitTests.cpp $(SRCDIR)/urn.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/UrnUnitTests.o -c $(SRCDIR)/UrnUnitTests.cpp


#Rule 4: Delete all files and subdirectories
clean:
#Delete all files from the object code directory
	rm -f $(OBJDIR)/*
#Delete all files and subdirectories from documentation directory
	rm -rf doc/*

#Rule 5: Execute UnitTests.cpp
test:
	$(OBJDIR)/./UrnUnitTests

.PHONY: doc
#Rule 6: Calls Doxygen to generate the documentation
doc:
	doxygen