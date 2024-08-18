//Benchmark_Config.hpp by Anton Hempel, August 08, 2024
#ifndef BENCHMARK_CONFIG_HPP
#define BENCHMARK_CONFIG_HPP

/*
Welche Benchmarks sollen enthalten sein.
Benchmark soll enthalten sein       => 1
Benchmark soll nicht enthalten sein => 0
*/
#define URN_O_FULL_ITERATION 0
#define URN_O_SPECIFIC_DRAW 0

#define URN_OR_FULL_ITERATION 0
#define URN_OR_SPECIFIC_DRAW 0

#define URN_R_FULL_ITERATION 0
#define URN_R_SPECIFIC_DRAW 1

#define URN_FULL_ITERATION 0
#define URN_SPECIFIC_DRAW 0



//CONFIG AUSWERTUNGEN
#if URN_O_FULL_ITERATION 
    #define URN_O_FULL_ITERATION_ENABLED
#endif //URN_O_FULL_ITERATION 

#if URN_O_SPECIFIC_DRAW 
    #define URN_O_SPECIFIC_DRAW_ENABLED
#endif //URN_O_SPECIFIC_DRAW 


#if URN_OR_FULL_ITERATION 
    #define URN_OR_FULL_ITERATION_ENABLED
#endif //URN_OR_FULL_ITERATION 

#if URN_OR_SPECIFIC_DRAW 
    #define URN_OR_SPECIFIC_DRAW_ENABLED
#endif //URN_OR_SPECIFIC_DRAW


#if URN_R_FULL_ITERATION 
    #define URN_R_FULL_ITERATION_ENABLED
#endif //URN_R_FULL_ITERATION 

#if URN_R_SPECIFIC_DRAW 
    #define URN_R_SPECIFIC_DRAW_ENABLED
#endif //URN_R_SPECIFIC_DRAW


#if URN_FULL_ITERATION 
    #define URN_FULL_ITERATION_ENABLED
#endif //URN_R_FULL_ITERATION 

#if URN_SPECIFIC_DRAW 
    #define URN_SPECIFIC_DRAW_ENABLED
#endif //URN_R_SPECIFIC_DRAW


#endif //BENCHMARK_CONFIG_HPP