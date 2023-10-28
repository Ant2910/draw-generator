# General
Author: [Ulrich Eisenecker](https://www.wifa.uni-leipzig.de/personenprofil/mitarbeiter/prof-dr-ulrich-eisenecker), Anton Hempel

The Draw-generator is an implementation for permutation and combinatorics in C++. These are represented by a simplified model based on an urn. 
Three main concepts are used: Urn, Balls, and Draw are used. 
The urns can then be used to generate all possibilities of the respective specification.
The following urn models are possible:

The implementations of the urn models are called: 
 * `UrnOR` – urn where the order is important and which contains repetitions.
 * `UrnO` – urn where the order is important and does not include repetitions.
 * `UrnR` – urn with unimportant order and with repetitions.
 * `Urn` – urn with unimportant order and without repetitions.
 * `GenericUrn` - Template-Wrapper for the urn models/draw-generator.
   
|                         | With repetition                      | Without repetition              | 
| ----------------------- | ------------------------------------ | ------------------------------- |
| Order is important      | $`n^k,¬(n=0∧k=0)∨(n>0)`$             | $`n! \over (n−k)!`$ $`,k≤n`$    |
| Order is not important  | $`(k+n−1)! \over k!(n−1)!`$ $`,n>0`$ | $`n! \over (n−k)!k!`$ $`, k≤n`$ |

For a deeper explanation of the different urn models, [MathisFun](https://www.mathsisfun.com/combinatorics/combinations-permutations.html) (English) and [MassMatics](https://www.massmatics.de/merkzettel/#!879:Urnenmodelle) (German) can be used.

# Usage
To include the urn in the code use the include directive `#include "urn.hpp"`

Please note that the include path must be adjusted depending on the location of the source files.

An urn can be filled with `n` balls (n is a natural number). The balls are numbered strictly sequentially, starting with 0. 
A draw, used here as a general term for combination and permutation, has the size `k` (k is a natural number) of the balls drawn from the urn. 

There are two criteria that can vary for a draw. 
First, a ball may or may not be returned to the urn immediately after being drawn. 
This is called drawing with repetition and drawing without repetition. 
Second, the order in which the balls are drawn may be important or not important, that is, the order is important or order is not important. 
Both criteria for drawing can be combined, resulting in four different drawing strategies.
 * `UrnOR` – urn where the order is important and which contains repetitions.
 * `UrnO` – urn where the order is important and does not include repetitions.
 * `UrnR` – urn with unimportant order and with repetitions.
 * `Urn` – urn with unimportant order and without repetitions.

An urn can then be created with `Urntype {n, k};`.
An example would be `UrnOR {3, 3};` 

Creates an urn where the order is important and which contains repetitions with 3 balls inside the urn and 3 as the size of a draw from the urn.



It is also possible to create an urn in which the elements of the urn have a specific type.

An urn can then be created with `GenericUrn<Type, ORDER, REPETITION> {k, elements};`

An example would be `GenericUrn<std::string, true, true> {3, balls};` where balls is a vector `std::vector<std::string> balls {"Green", "Blue", "Red"};`

Creates an urn where the order is important and which contains repetitions with 3 balls (one red ball, one green ball and one blue ball) inside the urn and 3 as the size of a draw from the urn. `n` has the size of `balls.size()`.

# Compilation
The instructions for the compilation create an executable for the unit tests.
The unit tests were created with [Catch2](https://github.com/catchorg/Catch2).

Therefore [Catch2](https://github.com/catchorg/Catch2) must be installed as well.

Note: `The GNU Compiler Collection (GCC)` for `g++` must be installed! 

For compiling the `makefile` is recommended.
* Generating executable with: `make`
* Delete the files from the obj/ and doc/ subdirectories with : `make clean`
  
Note: `make` must be installed!

Another way to compile is to type the following commands one after another into the console: 
 * `g++ -std=c++20 -o obj/urn.o -c src/urn.cpp`
 * `g++ -std=c++20 -o obj/UrnUnitTests.o -c src/UrnUnitTests.cpp`
 * `g++ -std=c++20 -o obj/UrnUnitTests obj/UrnUnitTests.o obj/urn.o`

   
# Documentation
The documentation is created with [Doxygen](https://github.com/doxygen/doxygen).

The documentation can then be viewed via `doc/html/index.html`

* Generating documentation with: `make doc` or just `doxygen`

  
Note: `doxygen` must be installed!