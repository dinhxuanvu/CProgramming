//////////////////////////////////////////////////////////////////////////////
// Linear Curve Fitting - This program fits a line to the data points in the
// file provided on the command line (one data point per line of text in the
// file).
//////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <list>
#include <iostream>
#include "Timers.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//  Class declaration for determining the "best" line for a given set of X-Y
// data points.
//////////////////////////////////////////////////////////////////////////////
class LinearFit
{
public:
    // Constructor
    LinearFit(void);
    
    // Accepts a single X-Y data point and adds it to the collection of points
    // used to determine the line.
    void AddPoint(double X, double Y);
    
    // Returns the number of data points collected
    int GetNumberOfPoints(void);
    
    // Returns the constant 'B' in Y = A * X + B
    double GetConstant(void);
    
    // Returns the coefficient to the linear term 'A' in Y = A * X + B
    double GetLinearCoefficient(void);
private:
    // Computes the coefficients (when needed)
    void ComputeCoefficients(void);
    
    // X data list
    list<double> Data_X;
    
    // Y data list
    list<double> Data_Y;
    
    // The constant 'B'
    double B;
    
    // The coefficient to the linear term 'A'
    double A;
    
    // Flag indicating that the coefficients have been computed
    int CoefficientsComputed;
}; // LinearFit Class

//////////////////////////////////////////////////////////////////////////////
//  Constructor
//////////////////////////////////////////////////////////////////////////////
LinearFit::LinearFit(void)
{
    // Initialize the flag indicating that the coefficients have not been computed
    CoefficientsComputed = 0;
} // Constructor

//////////////////////////////////////////////////////////////////////////////
//  AddPoint() - Accepts a single point and adds it to the lists
//////////////////////////////////////////////////////////////////////////////
void LinearFit::AddPoint(double X, double Y)
{
    // Store the data point into the lists
    Data_X.push_back(X);
    Data_Y.push_back(Y);
} // AddPoint()

//////////////////////////////////////////////////////////////////////////////
//  GetNumberOfPoints() - Returns the number of points collected
//////////////////////////////////////////////////////////////////////////////
int LinearFit::GetNumberOfPoints(void)
{
    return Data_X.size();
} // GetNumberOfPoints()

//////////////////////////////////////////////////////////////////////////////
//  ComputeCoefficients() - Calculate the value of the linear coefficient
// 'A' and the constant term 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
void LinearFit::ComputeCoefficients(void)
{
    // Declare and initialize sum variables
    double S_XX = 0.0;
    double S_XY = 0.0;
    double S_X  = 0.0;
    double S_Y  = 0.0;
    
    // Iterators
    list<double>::const_iterator lcv_X, lcv_Y;
    
    // Compute the sums
    lcv_X = Data_X.begin();
    lcv_Y = Data_Y.begin();
    while ((lcv_X != Data_X.end()) && (lcv_Y != Data_Y.end()))
    {
        S_XX += (*lcv_X) * (*lcv_X);
        S_XY += (*lcv_X) * (*lcv_Y);
        S_X  += (*lcv_X);
        S_Y  += (*lcv_Y);
        
        // Iterate
        lcv_X++; lcv_Y++;
    } // while()
    
    // Compute the constant
    B = (((S_XX * S_Y) - (S_XY * S_X)) / ((Data_X.size() * S_XX) - (S_X * S_X)));
    // Compute the linear coefficient
    A = (((Data_X.size() * S_XY) - (S_X * S_Y)) / ((Data_X.size() * S_XX) - (S_X * S_X)));
    
    // Indicate that the Coefficients have been computed
    CoefficientsComputed = 1;
} // ComputeCoefficients()

//////////////////////////////////////////////////////////////////////////////
//  GetConstant() - Calculate the value of the constant 'B' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetConstant(void)
{
    if (CoefficientsComputed == 0)
    {
        ComputeCoefficients();
    } // if()
    
    return B;
} // GetConstant()

//////////////////////////////////////////////////////////////////////////////
//  GetLinearCoefficient() - Calculate the value of the linear coefficient
// 'A' in Y = A * X + B
//////////////////////////////////////////////////////////////////////////////
double LinearFit::GetLinearCoefficient(void)
{
    if (CoefficientsComputed == 0)
    {
        ComputeCoefficients();
    } // if()
    
    return A;
} // GetLinearCoefficient()

//////////////////////////////////////////////////////////////////////////////
// Main program to fit a line to the data.
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    // Declare a pointer to the LinearFit object
    LinearFit *DataSet;
    
    // Declare timers
    DECLARE_TIMER(InputTimer);
    DECLARE_TIMER(CalculationTimer);
    
    // Constant defining the number of times to perform calculations
#define NUM_REPETITIONS (100)
    
    // Program phase timing variables
    //clock_t StartTime, StopTime;
    
    
    // Check that a command line argument was provided
    if (argc != 1)
    {
        // Boolean variable to indicate all data has been read.
        bool Done;
        
        // Declare an input stream
        ifstream InputFile;
        
        // Variables to hold the constant and linear coefficients of the line
        double A, B;
        
        // Start the timer
        START_TIMER(InputTimer);
        //StartTime = clock();
        
        // Perform the calculations many times
        for (int Iteration=0; Iteration < NUM_REPETITIONS ; Iteration++)
        {
            // Attach the input stream to the command line argument (it should be a
            // filename).
            InputFile.open(argv[1]);
            
            // Instantiate and object for determining the line
            DataSet = new LinearFit;
            
            // Read all of the data from the file
            do
            {
                // Temporary variables to hold data read from file
                double X, Y;
                
                // Read the X-Y data point
                InputFile >> X >> Y;
                
                // If read did not go beyond end-of-file, add it to the data set
                if (!InputFile.eof())
                {
                    // Add the data point
                    DataSet->AddPoint(X, Y);
                    Done = false;
                } // if()
                else
                {
                    // Set the flag indicating that all the data is gone
                    Done = true;
                } // if...else()
            } while (!Done);
            
            // Stop Input Timer
            STOP_TIMER(InputTimer);
            
            // Start Calculation Timer
            START_TIMER(CalculationTimer);
            
            // Save the constant value and the linear coefficent
            A = DataSet->GetLinearCoefficient();
            B = DataSet->GetConstant();
            
            // Stop Calculation Timer
            STOP_TIMER(CalculationTimer);
            
            // Start Input Timer
            START_TIMER(InputTimer);
            
            // Destroy the data set object
            delete DataSet;
            
            // Disconnect the input file from the stream
            InputFile.close();
            InputFile.clear();
        } // for()
        
        // Stop the timer
        //StopTime = clock();
        STOP_TIMER(InputTimer);
        
        // Print out the line that fits the data set.
        cout << "The line is: Y = " << A << " * X + " << B << endl;
        
        // Print measured times
        PRINT_TIMER(InputTimer);
        PRINT_TIMER(CalculationTimer);
        
        // Print out elapsed time per iteration.
        //cout << "Time per calculation = " << double(StopTime - StartTime) / double(CLOCKS_PER_SEC) / double(NUM_REPETITIONS) * 1000.0 << " msec." << endl;
    } // if()
    else
    {
        // Display program usage information
        cout << "(C++ Version) Usage: " << argv[0] << " Filename" << endl;
    } // if...else()
    
    return 0;
} // main()
