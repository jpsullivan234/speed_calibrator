#include "Calibrator.hpp"
#include "Calibrator.cpp"
#include <iostream>
using namespace std;

// Read from text file
// store in dictionary
// create a data structure to store the data



Calibrator gpsData("RTK_GPS.txt");
Calibrator watchData("SmartWatch.txt");
int main(){
    //gpsData.findErrors();
    //watchData.findErrors();

    //gpsData.getSpeed(23);
    //watchData.getSpeed(47);

    watchData.showAllData();
    return 0;
}

// To run:
// 1. 'g++ main.cpp'
// 2. './a.out'

// To push changes to git:
// 'git add .'
// 'git commit -m "(explain the commit here)" '
// git push