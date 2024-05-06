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

    //watchData.showAllData();
    watchData.search(0.9603606793058179);
    watchData.search(2.05);
    watchData.search(3.9);
    return 0;
}

// To run:
// 1. 'g++ main.cpp'
// 2. './a.out'

// To push changes to git:
// 'git add .'
// 'git commit -m "(explain the commit here)" '
// git push