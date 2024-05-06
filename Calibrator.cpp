#include "Calibrator.hpp"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

Calibrator::Calibrator(const char* filename):name(filename){
    data[0] = 0;                        // Assuming speed at 0 seconds is 0 m/s
    data[0] = 0;

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

        cout<<"n = "<<n<<" | Slope = "<<n_slope;

        if (n_slope > 1 + 2*stdev_x || n_slope < 1 - 2*stdev_x){    // If the slope is outside of 2 standard deviations from 1, it is an error

            correct_val = n*sum_dx/(n-1) + sum_offset/(n-1);        // Calculate what the data point should be based on the averages so far
            data[n] = correct_val;                      // Save the correct value

            cout<<"| Error! n_slope = "<<sum_dx/(n-1)<<endl;

            n_error = (Pair){.index = n, .val = val};   // Save the current (index,val) pair of the erroneous point
            errors.emplace_back(n_error);

            sum_offset += n - (sum_dx/(n-1) * val);     // Keep track of the y-intercepts 
            sum_dx += sum_dx/(n-1);                     // Update the sum of slopes

        } else {                                        // This case means the point is accurate
            cout<<endl;

            data[n] = val;                              // Store the raw data
            
            sum_offset += n - (n_slope * val);          // Keep track of the y-intercepts 
            sum_dx += n_slope;                          // Update the sum of slopes
        }
        n++;
    }
    dataFile.close();
    cout<<"Eqn is: y = "<<sum_dx/99<<"x + "<<sum_offset/99<<endl;

    for (int i = 0; i < errors.size(); i++){
        cout<<errors[i].index<<endl;
    }
};

Calibrator::~Calibrator(){
    cout<<"\n===== All data has been deleted for "<<name<<" ====="<<endl;
};