#include "Calibrator.hpp"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

Calibrator::Calibrator(const char* filename):name(filename){
    data[0] = 0;                        // Assuming speed at 0 seconds is 0 m/s

    double stdev_x = 0.316227766;       // Variance is known to be 0.1; sqrt(0.1) = stdev
    double sum_dx = 0;                  // Sum of the difference (slope) between each point
    double sum_offset = 0;              // Sum of the offset of each slope (y-intercept)
    double n_slope = 0;                 // Stores individual slope values for each point
    double val = 0;                     // Temporarily store each raw data value
    double correct_val = 0;             // Stores the calculated correct data value for each point
    Pair n_error;                       // Stores (index, error) pairs for each point containing error

    /* Get raw data and separate error points*/
    ifstream dataFile(filename);                        // Create a file obj to get data
    int n = 1;

    while (n < 100 && dataFile>>val){                   // Iterate through each data element
        n_slope = (val - data[n-1]);                    // Calculate the slope between current val and last val
        if (n_slope > 1 + 2*stdev_x || n_slope < 1 - 2*stdev_x){    // If the slope is outside of 2 standard deviations from 1, it is an error

            correct_val = n;                            // Assuming the correct slope is roughly 1, the correct data will be roughly n
            data[n] = correct_val;                      // Save the correct value
            n_error = (Pair){.index = n, .val = val};   // Save the current (index,val) pair of the erroneous point in the vector
            errors.emplace_back(n_error);
            sum_dx ++;                                  // Update the sum of slopes

        } else {                                        // This case means the point is accurate
            data[n] = val;                              // Store the raw data
            sum_offset += n - (n_slope * val);          // Keep track of the y-intercepts 
            sum_dx += n_slope;                          // Update the sum of slopes
        }
        n++;
    }
    dataFile.close();
    slope = sum_dx/99;
    offset = sum_offset/99;
};

Calibrator::~Calibrator(){
    cout<<"\n===== All data has been deleted for "<<name<<" ====="<<endl;
};

void Calibrator::findErrors(){
    cout<<"\nPrinting Errors for "<<name<<":"<<endl;
    for (int i = 0; i < errors.size(); i++){
        cout<<"     Error "<<i+1<<": Index = "<<errors[i].index<<" | Value = "<<errors[i].val<<endl;
    }
}
