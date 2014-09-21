/**************************************************************************
 ** Linear Curve Fitting
 **   This program fits a line to the data points in the text file provided
 **   on the command line (one data point per line)
 **
 ** Revised: Juan C. Cockburn - 9/11/2014
 ** Edited: Vu X. Dinh - 9/19/2014
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Timers.h"

typedef double Point; /* Macro for double type */

/* "header" of dynamic array */
typedef struct
{
    /* Pointer to X data dynamic array */
    Point *Data_X;
    /* Pointer to Y data dynamic array */
    Point *Data_Y;
    /* Current Size of dynamic arrays */
    unsigned int Size;
    /* Index of element next to last used entry in the arrays */
    unsigned int NextElement;
} LinearFit;

/**************************************************************************
 * AddPoint() - Accepts a single point and adds it to the array expanding
 * the size of the arrays if necessary.
 **************************************************************************/
void AddPoint(LinearFit *DataSet, Point X, Point Y)
{
    /* Store the data point (X,Y) into the arrays */
    DataSet->Data_X[DataSet->NextElement] = X;
    DataSet->Data_Y[DataSet->NextElement] = Y;
    
    /* Increment index for the next point and see if that point will be */
    /* beyond the size of the arrays */
    if (++DataSet->NextElement >= DataSet->Size)
    {
        /* Double the size of the arrays to store more data points */
        DataSet->Size = DataSet->Size << 1;
        
        /* Allocate the new arrays with the newly-doubled size */
        DataSet->Data_X = (Point *) realloc(DataSet->Data_X,sizeof(Point) * DataSet->Size);
        DataSet->Data_Y = (Point *) realloc(DataSet->Data_Y,sizeof(Point) * DataSet->Size);
    } /* if() */
} /* AddPoint() */


/**************************************************************************
 *  CalculateConstant() - Calculate 'A' & 'B' in Y = A * X + B
 **************************************************************************/
void CalculateCoefficients(LinearFit *DataSet, Point *A, Point *B)
{
    /* Declare and initialize sum variables */
    Point S_XX = 0.0;
    Point S_XY = 0.0;
    Point S_X  = 0.0;
    Point S_Y  = 0.0;
    unsigned int lcv;
    
    /* Compute the sums */
    for (lcv=0; lcv < DataSet->NextElement; lcv++)
    {
        S_XX += DataSet->Data_X[lcv] * DataSet->Data_X[lcv];
        S_XY += DataSet->Data_X[lcv] * DataSet->Data_Y[lcv];
        S_X  += DataSet->Data_X[lcv];
        S_Y  += DataSet->Data_Y[lcv];
    } /* for() */
    
    /* Compute the parameters of the line Y = A*X + B */
    (*A) = (((DataSet->NextElement * S_XY) - (S_X * S_Y)) / ((DataSet->NextElement * S_XX) - (S_X * S_X)));
    (*B) = (((S_XX * S_Y) - (S_XY * S_X)) / ((DataSet->NextElement * S_XX) - (S_X * S_X)));
} /* CalculateCoefficients() */

/**************************************************************************
 * Main program to fit a line to the data.
 **************************************************************************/
int main(int argc, char *argv[])
{
    unsigned int Iteration;
    
    /* Declare a LinearFit data structure */
    LinearFit DataSet;
    
    /* Declare timers */
    DECLARE_TIMER(InputTimer);
    DECLARE_TIMER(CalculationTimer);
    
    /* Constant defining the number of times to perform calculations */
#define NUM_REPETITIONS (100)
    
    
    /* Variables to hold the coefficients of the least-square linear fit */
    Point A, B;
    
    /* Temporary variables to hold data point read from file */
    Point X, Y;
    
    /* "Boolean" variable to indicate all data has been read. */
    int Done;
    
    /* Declare an input file of type FILE pointer */
    FILE *InputFile;
    
    /* Check that a command line argument was provided */
    if (argc != 1)
    {
        
        /* Start timer */
        START_TIMER(InputTimer);
        
        /* Perform the calculations many times */
        for (Iteration=NUM_REPETITIONS; Iteration != 0 ; Iteration--)
        {
            
            /* Open input file for reading -- it should be a valid filename */
            InputFile = fopen(argv[1], "r");
            
            /* Start with minimally sized arrays */
            DataSet.Size = 100;
            
            /* Allocate the arrays */
            DataSet.Data_X = (Point *)malloc(sizeof(Point) * DataSet.Size);
            DataSet.Data_Y = (Point *)malloc(sizeof(Point) * DataSet.Size);
            
            /* Initialize the index where the next data point will go */
            DataSet.NextElement = 0;
            
            /* Read all of the data from the file */
            do
            {
                /* Read X,Y data point and if read did not go beyond end-of-file,
                 add it to the data set */
                if (fscanf(InputFile, "%lf %lf", &X, &Y) != EOF)
                {
                    /* Add the data point */
                    AddPoint(&DataSet, X, Y);
                    Done = 0;
                } /* if() */
                else
                {
                    /* Set the flag indicating that all the data is gone */
                    Done = 1;
                } /* if...else() */
            } while (!Done);
            
            /* Stop Input Timer */
            STOP_TIMER(InputTimer);
            
            /* Start Calculation Timer */
            START_TIMER(CalculationTimer);
            
            /* Save the constant value and the linear coefficient */
            CalculateCoefficients(&DataSet, &A, &B);
            
            /* Stop Calculation Timer */
            STOP_TIMER(CalculationTimer);
            
            /* Start Input Timer */
            START_TIMER(InputTimer);
            
            /* Return dynamic memory to the heap */
            free(DataSet.Data_X);
            free(DataSet.Data_Y);
            
            /* Disconnect the input file from the stream */
            fclose(InputFile);
        }
        
        /* Stop the timer */
        STOP_TIMER(InputTimer);
        
        /* Print out the line that fits the data set. */
        printf("The line is: Y = %g * X + %g\n", A, B);
        
        /* Print measured times */
        PRINT_TIMER(InputTimer);
        PRINT_TIMER(CalculationTimer);
        
    } /* if() */
    else
    {
        /* Display program usage information */
        printf("Usage: %s Filename\n", argv[0]);
    } /* if...else() */
    
    return 0;
} /* main() */
