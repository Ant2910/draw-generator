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
$(OBJDIR)/unstable_tests: $(OBJDIR)/unstable_tests.o $(OBJDIR)/newurn.o
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/unstable_tests $(OBJDIR)/unstable_tests.o $(OBJDIR)/newurn.o


#Rule2: Generate object code for urn.cpp
$(OBJDIR)/newurn.o: $(SRCDIR)/newurn.cpp $(SRCDIR)/newurn.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/newurn.o -c $(SRCDIR)/newurn.cpp


#Rule3: Generate object code for UrnUnitTests.cpp
$(OBJDIR)/unstable_tests.o: $(SRCDIR)/unstable_tests.cpp $(SRCDIR)/newurn.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/unstable_tests.o -c $(SRCDIR)/unstable_tests.cpp


#Rule 4: Delete all files and subdirectories
clean:
#Delete all files from the object code directory
	rm -f $(OBJDIR)/*
#Delete all files and subdirectories from documentation directory
	rm -rf doc/*

#Rule 5: Execute UnitTests.cpp
test:
	$(OBJDIR)/./unstable_tests

.PHONY: doc
#Rule 6: Calls Doxygen to generate the documentation
doc:
	doxygen