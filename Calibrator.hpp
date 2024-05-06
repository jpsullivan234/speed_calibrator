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
        const char * name;
        double data[99];            // Stores corrected data
        double slope;               // Stores the slope of the data
        double offset;              // Stores the y-intercept of the data (will be close to 0)

    public:
        vector<Pair> errors;

        Calibrator(const char* fileName);    // Constructor
        ~Calibrator();                       // Destructor

        void findErrors();             // Prints all possible erroneous data values
        void getSpeed(int time);       // Prints a speed at specified time
        void showAllData();            // Prints entire dataset
        void search(double speed);     // Search for a specified speed, print corresponding time if found
};

#endif /* Calibrator_hpp*/