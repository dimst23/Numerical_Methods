#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> //Needed for strcspn function

double min(double* array, int dimen); //Find the absolute minimum value in an array and return it
double* mem_alloc(size_t dim); //Memory allocation function for pointers to make code less cluttered
double power_method(double** matrix, size_t dimension, int precision); //Calculate the absolute maximum eigen value using the power method

int iter_num = 0; //Iteration number counter variable

int main()
{
    double** matrix = NULL; //Create the necessary pointers
    double lam = 0; //Save the calculated eigen value
    char file_path[100] = " "; //Save the file path provided
    int dimension = 0, prec = 0; //Keep the dimension of the system
    char temp_s[10]; //Array to store the temporary string from the file read
    FILE* pfile = NULL; //Pointer to the provided file

    printf("******Absolute largest eigen value calculator******\n\n"); //Welcome message
    printf("You will need to enter the file path containing the matrix: \n"); //Prompt for file path
    fgets(file_path, 100, stdin); //Get the file path as provided by the user
    file_path[strcspn(file_path, "\n")] = '\0'; //Remove the trailing new line character from the file path string

    printf("\nThe matrix dimension is: "); //Prompt for system dimensions
    scanf(" %d", &dimension); //Get the entered dimension
    while(dimension <= 0) //Keep asking if the dimension entered is wrong
    {
        fprintf(stderr, "Please enter a valid dimension above zero: "); //Prompt for a correct and valid number
        scanf(" %d", &dimension); //Get the entered dimension
    }
    printf("And finally enter the required decimal precision for the calculation: "); //Prompt for the decimal precision input
    scanf(" %d", &prec); //Get the desired decimal precision

    if(!(pfile = fopen(file_path, "r"))) //Check for file input error and open the provided file
    {
        fprintf(stderr, "\nError opening file %s. Program terminates here.\n", file_path); //Send the error message before termination
        exit(1); //Indicate file error
    }

    if(!(matrix = (double**)calloc(dimension, sizeof(double)))) //Allocate memory for the matrix rows
    {
        fprintf(stderr, "An error has occurred. Now exiting."); //Indicate an error message before exiting
        exit(4); //Indicate a pointer problem
    }
    else //If all succeeded allocate memory for the elements in each row
        for(int i = 0; i < dimension; i++)
            matrix[i] = mem_alloc(dimension);

    //Get the contents from the file
    for(int i = 0; i < dimension; i++) //Scan through the text file to get all the values
    {
        for(int j = 0; j < dimension; j++)
        {
            fscanf(pfile, "%[^;]s", temp_s); //Get the value from the file which is in text mode
            matrix[i][j] = atof(temp_s); //Convert the text to a double in order to work with the values
            fseek(pfile, 1, SEEK_CUR); //Increase the file position by one to get rid of the current delimiter
        }
    }

    lam = power_method(matrix, dimension, prec); //Get the eigen value with the desired decimal precision

    free(matrix); //Clear the memory of the pointer
    fclose(pfile); //Close the file, because is no longer needed

    //Output the message for the calculation
    printf("\n\nThe calculated absolute maximum eigen value of the %dx%d matrix provided is: ", dimension, dimension);
    printf("%.*f\n", prec, lam); //Output the result of the eigen value calculation
    printf("And it has taken %d iterations to complete.\n\n", iter_num + 1); //Output the number of iterations taken for completion

    system("pause"); //Prevent the program for exiting immediately on terminal execution

    return 0;
}

double min(double* array, int dimen) //Find the absolute minimum in an array
{
    double min_val = array[0]; //Initialize the minimum value with the first array element

    for(int i = 0; i < dimen; i++) //Iterate over all array elements to find the minimum value
    {
        if(fabs(array[i]) < fabs(min_val)) //Compare the absolute values
            min_val = array[i]; //If a lesser value than the current is found save it
    }
    return min_val; //Return the absolute minimum value found
}

double* mem_alloc(size_t dim)
{
    double* ptr = NULL; //Initialize the pointer to NULL to avoid errors

    if(!(ptr = (double*)calloc(dim, sizeof(double)))) //Allocate memory
    {
        fprintf(stderr, "An error has occurred. Now exiting."); //Show an error message before exiting
        exit(4); //Exit indicating pointer problem
    }
    return ptr; //Return the address of the allocated memory
}

double power_method(double** matrix, size_t dimension, int precision)
{
    double* cur_eigen = mem_alloc(dimension), *prev_eigen = mem_alloc(dimension); //Allocate memory for pointers
    double scale = 0, sum1 = 0, sum2 = 0, lambda_cur = 0, lambda_prev = 0; //Save the scaling factor and the sums

    iter_num = 0; //Rest the iterations count

    for(int i = 0; i < dimension; i++) //Initialize the first eigen vector to be used in the process
        prev_eigen[i] = 1.0; //Set the values to one

    do
    {
        lambda_prev = lambda_cur; //Set the current eigen value to previous, because the current now is past
        iter_num++; //Increase the iteration count to jeep track of the iterations

        for(int i = 0; i < dimension; i++) //Execute matrix multiplication with the NxN matrix provided and the eigen vector
        {
            for(int j = 0; j < dimension; j++)
                cur_eigen[i] += matrix[i][j]*prev_eigen[j];
            sum1 += cur_eigen[i]*prev_eigen[i]; //Sum over the multiplication of the current and the previous eigen vector values
            sum2 += prev_eigen[i]*prev_eigen[i]; //Square the eigen vector values from the previous vector and sum over them
        }

        scale = min(cur_eigen, dimension); //Find the minimum for scaling

        for(int i = 0; i < dimension; i++) //Scale all values based on the minimum value in the array
        {
            prev_eigen[i] = cur_eigen[i] /= scale; //Scale the current eigen vector value before saving it to the previous
            cur_eigen[i] = 0.0; //Reset the current eigen vector
        }

        lambda_cur = sum1/sum2; //Calculate the current eigen value for further comparison
        sum1 = sum2 = 0; //Reset the sum variables, to prepare for an upcoming iteration
    } while( (int)((lambda_cur - lambda_prev)*pow(10, precision)) !=0 ); //If the desired decimal precision is achieved stop looping

    free(prev_eigen); //Free the allocated memory
    free(cur_eigen); //Free the allocated memory

    return lambda_cur; //Return the calculated eigen value
}
