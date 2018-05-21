#ifndef INTEGRATION_H_INCLUDED
#define INTEGRATION_H_INCLUDED

#include <math.h>

//Modify the f(x) macro to put your function and set the limits of integration
#define f(x) 1.0/(5.0*pow(x, 2.0) + 1.0) //Define a macro for the function you want to calculate
#define LOWER_LIM 0.0 //Set the lower integration limit
#define UPPER_LIM 3.0 //Set the upper integration limit

#define LIM_DIFF (UPPER_LIM - LOWER_LIM) //Limit difference used in the interval calculation

extern double simp13(double lower_lim, unsigned long long n, double h); //Simpson's 1/3 rule
extern double trapezium(double lower_lim, unsigned long long n, double h); //Trapezium rule


#endif // INTEGRATION_H_INCLUDED
