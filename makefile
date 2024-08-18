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

#Default target
all: $(OBJDIR)/Benchmark

#Rule1: Generate object code for urn.cpp
$(OBJDIR)/urn.o: $(SRCDIR)/urn.cpp $(SRCDIR)/urn.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/urn.o -c $(SRCDIR)/urn.cpp

#Rule7: Generate object code for urn_old.cpp
$(OBJDIR)/urn_old.o: $(SRCDIR)/urn_old.cpp $(SRCDIR)/urn_old.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/urn_old.o -c $(SRCDIR)/urn_old.cpp

#Rule3: Generate object code for Benchmark.cpp
$(OBJDIR)/Benchmark.o: $(SRCDIR)/Benchmark.cpp $(SRCDIR)/urn.hpp $(SRCDIR)/urn_old.hpp $(SRCDIR)/Benchmark_Config.hpp
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/Benchmark.o -c $(SRCDIR)/Benchmark.cpp

#Rule5: Generate executable for Benchmark
$(OBJDIR)/Benchmark: $(OBJDIR)/Benchmark.o $(OBJDIR)/urn.o $(OBJDIR)/urn_old.o
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/Benchmark $(OBJDIR)/Benchmark.o $(OBJDIR)/urn.o $(OBJDIR)/urn_old.o

.PHONY: clean
#Rule 6: Delete all files and subdirectories
clean:
#Delete all files from the object code directory
	rm -f $(OBJDIR)/*
#Delete all files and subdirectories from documentation directory
	rm -rf doc/*

.PHONY: bench
#Rule 7: Execute UnitTests.cpp
bench:
	$(OBJDIR)/./Benchmark

.PHONY: doc
#Rule 9: Calls Doxygen to generate the documentation
doc:
	doxygen