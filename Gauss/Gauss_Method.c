#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> //Needed for the strcspn function

//Function prototypes
double* gauss(double** eq_array, int system_size); //Method for solving the provided system
void user_prompt(char file_path[], int* dimension); //User prompt function

int main()
{
    char file_path[100] = " "; //Save the file path provided
    int dimension = 0; //Keep the dimension of the system
    double** eq_array = NULL; //Array to store the values read from the file
    double* solution = NULL; //Array to save the solutions
    char temp_s[10]; //Array to store the temporary string from the file read
    FILE* pfile = NULL; //Pointer to the provided file

    user_prompt(file_path, &dimension); //Call user_prompt to start the program and ask for the necessary input

    if(!(pfile = fopen(file_path, "r"))) //Check for file input error
    {
        fprintf(stderr, "Error opening file %s. Program terminates here.", file_path); //Send the error message before termination
        exit(1); //Indicate file error
    }

    eq_array = (double**)calloc(dimension, sizeof(double)); //Get the required memory for the input values if fopen was successful
    if(!eq_array)
    {
        fprintf(stderr, "An error occurred. Program terminates here."); //Show an error message before exiting
        exit(4); //Indicate pointer error
    }
    for(int i = 0; i < dimension; i++) //Occupy the required memory for the input
    {
        if(!(eq_array[i] = (double*)calloc(dimension + 1, sizeof(double)))) //Check for error
        {
            fprintf(stderr, "An error occurred. Program terminates here.");
            exit(4); //Indicate pointer error
        }
    }

    for(int i = 0; i < dimension; i++) //Scan through the text file to get all the values
    {
        for(int j = 0; j < dimension + 1; j++)
        {
            fscanf(pfile, "%[^;]s", temp_s); //Get the value from the file which is in text mode
            eq_array[i][j] = atof(temp_s); //Convert the text to a double in order to work with the values
            fseek(pfile, 1, SEEK_CUR); //Increase the file position by one to get rid of the current delimiter
        }
    }

    if(!(solution = (double*)calloc(dimension, sizeof(double))))
    {
        fprintf(stderr, "An error occurred. Now exiting.");
        exit(4);
    }
    solution = gauss(eq_array, dimension); //Solve the system and save the solutions

    printf("\nThe calculated solutions for the provided %dx%d system, using the Gauss method are:\n", dimension, dimension);
    for(int i = 0; i < dimension; i++)
		printf("x%d: %f\n", (i + 1), solution[i]); //Print out each solution to a line

    free(eq_array); //Free the allocated memory
    free(solution); //Free the allocated memory
    fclose(pfile); //Close the file before exiting

    system("pause"); //Prevent the program for exiting immediately on terminal execution

    return 0;
}

void user_prompt(char file_path[], int* dimension) //User prompt for input and welcome messages
{
    printf("******Linear system of equations solver******\n\n"); //Welcome message
    printf("Enter the file path containing the system coefficients: \n"); //Prompt for file path
    fgets(file_path, 100, stdin); //Get the file path as provided by the user
    file_path[strcspn(file_path, "\n")] = '\0'; //Remove the trailing new line character from the file path string

    printf("\nThe system dimension is: "); //Prompt for system dimensions
    scanf(" %d", dimension); //Get the entered dimension
	
    while(dimension <= 0) //Keep asking if the dimension entered is wrong
    {
        printf("Please enter a valid dimension above zero: "); //Prompt for a correct and valid number
        scanf(" %d", dimension); //Get the entered dimension
    }
}

double* gauss(double** eq_array, int system_size)
{
    double factor = 0; //Variable to hold the multiplying factor
    double* sol_array = NULL; //Array to store the solutions

    if(!(sol_array = (double*)calloc(system_size, sizeof(double)))) //Allocate memory for the solutions
    {
        fprintf(stderr, "\nAn error has occurred. Now exiting."); //Indicate an error if memory allocation fails
        exit(4); //Exit returning 4
    }

    for(int i = 0; i < system_size - 1; i++) //Iterate over all rows, except the first one
    {
        for(int j = i + 1; j < system_size; j++) //Iterate over all columns except the first one
        {
            factor = eq_array[j][i]/eq_array[i][i]; //Calculate the factor to multiply the elements in each row
            for(int k = 0; k < system_size + 1; k++) //Iterate over all elements in a row to do the necessary math
            {
                eq_array[i][k] *= factor; //Multiply each row element by the calculated factor
                eq_array[j][k] = eq_array[i][k] - eq_array[j][k]; //Subtract a standard row form the other n-th row
            }
        }
    }

    for(int i = system_size - 1; i >= 0; i--) //Solution finding loop
    {
        double sum = 0; //Hold the sum
        int count = system_size - 1; //Counter for the summing process

        while(count > i) //Summing process as needed by the Gauss method
        {
            sum += eq_array[i][count]*sol_array[count]; //Sum the components as needed
            count--; //Decrease count
        }
        sol_array[i] = (eq_array[i][system_size] - sum)/eq_array[i][i]; //Save the calculated solution in the corresponding array
    }

    return sol_array; //Return the address of the solution array
}
