#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //Used for the tolower() function
#include "Integration.h"


int main()
{
    int choice = 0; //Variable to hold user choice
    char restart = 'n'; //Keep the restart answer
    double h = 0.0, result = 0.0; //Keep the interval and the result

    //Welcome message with the user prompts
    printf("******Integral calculation using the Simpson's rule******\n");

start: //Initial section of the program, used for the goto statement
    printf("\nChoose on of the following options, write the corresponding number.\n");
    printf("1. Provide the number of points, n, to calculate the result\n");
    printf("2. Ask for a specific decimal precision and have n calculated, along with the result\n");

    printf("What is your preference? (Enter either 1 or 2): ");
    scanf(" %d", &choice); //Get the user choice
    while((choice != 1) && (choice != 2))
    {
        fprintf(stderr, "You entered an option that does not exist!!\n");
        fprintf(stderr, "Please enter a correct number 1 or 2: ");
        scanf(" %d", &choice); //Get the user choice
    }

    if(choice == 1)
    {
        unsigned long n_points = 0; //Keep the number of points

        printf("Please now enter an odd number of points: ");
        scanf(" %lu", &n_points); //Get the number of points
        while( !(n_points%2) )
        {
            fprintf(stderr, "As asked, please enter an ODD number of points: ");
            scanf(" %lu", &n_points); //Get the number of points
        }

        h = LIM_DIFF/n_points; //Calculate the interval for integration
        result = simp13(LOWER_LIM, n_points, h); //Find the area of the function

        printf("\nThe result of the calculation for a total of %lu points is: %f", n_points, result);
    }
    else
    {
        unsigned long long n_points = 1; //Keep the number of points and initialize to one. There is no meaning for zero points
        int dec_prec = 0; //Keep the desired decimal precision

        printf("Please enter the desired decimal precision: "); //Prompt for user input
        scanf(" %d", &dec_prec); //Get the decimal precision
        while((dec_prec < 0))
        {
            fprintf(stderr, "I don't think there is a negative decimal precision!!");
            fprintf(stderr, "Please enter a positive number: ");
            scanf(" %d", &dec_prec); //Get the decimal precision
        }

        double calc_1 = 0, calc_2 = 0; //Save the calculated relative error
        unsigned long long i = 1; //Counter variable
        do
        {
            calc_1 = calc_2; //Save the previous result of the calculation to a variable for further use
            n_points = 2*(i++) + 1; //Give an increasing number of points in each iteration
            h = LIM_DIFF/n_points; //Calculate the interval for integration
            calc_2 = simp13(LOWER_LIM, n_points, h); //Find the area of the function

        } while( ( (unsigned long long)(fabs(calc_1 - calc_2)*pow(10, dec_prec + 1)) ) != 0 );
        result = calc_2; //If the loop exited, the variable calc_2 has the result of the calculations

        //Output the calculated result to the user
        printf("\nFor a decimal precision of %d digits, a total of %lu points is required.\n", dec_prec, n_points);
        printf("And the final result is: %.*f", dec_prec, result);
    }

    //Ask the user if another calculation is needed
    printf("\n\nDo you want another calculation?\nIf yes enter 'y', otherwise enter anything: ");
    scanf(" %c", &restart);

    //If user decides for another calculation
    if(tolower(restart) == 'y')
        goto start; //Restart the program

    system("pause"); //Used for Windows to prevent the terminal from closing after program execution

    return 0; //Indicate successful execution of the program
}
