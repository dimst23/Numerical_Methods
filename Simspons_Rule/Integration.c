#include "Integration.h"

double simp13(double lower_lim, unsigned long long n, double h)
{
    double sum = 0.0; //Initialize the sum variable

    //Iterate to sum, according to the provided steps
    for(unsigned long long i = 0; i <= n; i++)
    {
        if (i == (n - 1))
            i = n;
        if((i == 0) || (i == n))
            sum += f(((double)(i))*h);     //The first and the last values in the sum are not multiplied with anything
        else if(!(i%2))             //If it is even
            sum += 2.0*f(lower_lim + ((double)(i))*h); //Multiply the function evaluation with 2
        else                     //If i is even
            sum += 4.0*f(lower_lim + ((double)(i))*h); //Multiply the function evaluation with 4
    }

    return (h/3.0)*sum; //Return the result
}
