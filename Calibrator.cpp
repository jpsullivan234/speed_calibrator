#include "Calibrator.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Calibrator::Calibrator(const char* filename){
    _data[0].val = 0;
    _data[0].error = 0;   // Assuming speed at 0 seconds is 0 m/s

    double stdev_x = 0.316227766;       // Variance is known to be 0.1; sqrt(0.1) = stdev
    double stdev_y = 28.72281323;       // Y is simply ints 1-99, so stdev was found using calculator
    
    double sum_y = 4950;                // These 3 variables
    double sum_dx = 0;
    double sum_b = 0;
    double n_slope = 0;

    double val = 0;                         // Temporarily store each data value
    double correct_val = 0;


    int n = 1;
    ifstream dataFile(filename);            // Create a file obj to get data
    while (n < 100 && dataFile>>val){       // Iterate through each data element

        n_slope = (_data[n].val - _data[n-1].val)/(n - (n-1));
        if (n_slope < 1 + 2*stdev_x || n_slope > 1 - 2*stdev_x){    // If the slope is outside of 2 standard deviations from 1, it is error
            _data[n].val = n;
            _data[n].error = val - n;
            
            // dont need to update sum_b
            sum_dx++;

        } else {
            _data[n].val = val;             // Store the raw data into 'val' of the array. The 'error' part of the struct is still 0.
            _data[n].error = 0;             // Error is initially set to 0 for all

            sum_b += n - (n_slope * val);   // Keep track of the y-intercepts 
            sum_dx += n_slope;
        }
        n++;
    }
    dataFile.close();


    // Calculate the average slope and average offset (noise)
    _m = sum_dx/99;
    _b = sum_b / 99;

    cout<<"Eqn is: y = "<<_m<<"x + "<<_b<<endl;
    // Remove the error from the raw data & update 'error' part of each struct
    for (int i = 0; i < 100; i++){
        correct_val = _m * i + _b;                              // calculate the correct value using the regression line
        
        if ( abs( correct_val - _data[i].val ) > stdev_x){      // If the data is outside of the standard deviation, find the error
            _data[i].error = abs( correct_val - _data[i].val ); // Add the error to this 'pair' in the array
            _data[i].val = correct_val;
            cout<<"Error at: "<<i<<" Speed is: " <<_data[i].val<<" Correct speed is: "<<correct_val<<endl;
        }
    }
};