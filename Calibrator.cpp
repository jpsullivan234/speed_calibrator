#include "Calibrator.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Calibrator::Calibrator(const char* filename){
    _data[0].val = 0;
    _data[0].error = 0;

    double stdev_x = 0.316227766;       // Variance is known to be 0.1; sqrt(0.1) = stdev
    double stdev_y = 28.72281323;       // Y is simply ints 1-99, so stdev was found using calculator
    
    double sum_y = 4950;                // These 4 variables are used to find the linear regression of the data
    double sum_x = 0;
    double sum_x2 = 0;
    double sum_xy = 0;

    double val = 0;                     // Temporarily store each data value
    double correct_val = 0;

    int n = 1;
    ifstream dataFile(filename);        // Create a file obj to get data
    while (n < 100 && dataFile>>val){   // Iterate through each data element
            _data[n].val = val;         // Store the raw data into 'val' of the array. The 'error' part of the struct is still 0.
            _data[n].error = 0;         // Error is initially set to 0 for all
            sum_x += val;               // update sums
            sum_x2 += val*val;
            sum_xy += val*n;
        n++;
    }
    dataFile.close();


    // Calculate the linear regression of the data
    _m = (99 * sum_xy - (sum_x * sum_y) ) / (99 * sum_x2 - (sum_x*sum_x));    // calculate the slope of the regression
    _b = (sum_y - _m * sum_x)/99;              // calculate the intercept of the regression


    cout<<"eqn = "<<_m<<"x + "<<_b<<endl;

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