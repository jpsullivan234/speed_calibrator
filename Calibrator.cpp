#include <Calibrator.hpp>
#include <fstream>
#include <iostream>
using namespace std;

Calibrator::Calibrator(char* filename){
    double stdev_x = 0.316227766;       // Variance is known to be 0.1; sqrt(0.1) = stdev
    double stdev_y = 28.72281323;       // Y is simply ints 1-99, so stdev was found using calculator
    
    double sum_y = 4950;                // These three variables are used to find the linear regression of the data
    double sum_x = 0;
    double sum_xy = 0;

    double val = 0;                     // Temporarily stores each data value

    ifstream dataFile(filename);        // Create a file obj to get data
    while (dataFile.good()){
        for (int i = 1; i < 100; i++){  // Iterate through each data element
            dataFile>>val;              // Input data element
            _data[]
            sum_x += val;               // update sums
            sum_xy += val*i;
        }
    }
};


// r = 