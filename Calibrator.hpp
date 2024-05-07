#ifndef Calibrator_hpp
#define Calibrator_hpp
#include <vector>
using namespace std;

class Calibrator{

    private:
        struct Pair{                // 'pair' is a data type that holds a corrected data value and the error, if there is any
            int index;
            double val;

        };
        double data[100];            // Stores corrected data
        double slope;               // Stores the slope of the data
        double offset;              // Stores the y-intercept of the data (will be close to 0)

    public:
        const char * name;
        vector<Pair> errors;

        Calibrator(const char* fileName);    // Constructor
        Calibrator();                        // Second constructor for initializing without file
        ~Calibrator();                       // Destructor

        void findErrors();             // Prints all possible erroneous data values
        void getSpeed(int time);       // Prints a speed at specified time
        void showAllData();            // Prints entire dataset
        void search(double speed);     // Search for a specified speed, print corresponding time if found
        void getAccel();               // returns the average accelaration of the data
        void getNoise();               // returns the amount of noise in the data
};

#endif /* Calibrator_hpp*/