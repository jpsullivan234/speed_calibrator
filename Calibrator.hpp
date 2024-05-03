#ifndef Calibrator_hpp
#define Calibrator_hpp

class Calibrator{

    private:
        struct Pair{            // 'pair' is a data type that holds a corrected data value and the error, if there is any
            double val;
            double error;
        };

        Pair _data[99];         // Stores (corrected data, error) pairs
        double _m;              // Stores the slope of the data
        double _b;              // Stores the y-intercept of the data (will be close to 0)
        
    public:
        Calibrator(const char* fileName);    // Constructor
        ~Calibrator();                 // Destructor

        void findErrors();             // Prints all possible erroneous data values
        void getSpeed(int time);       // Prints a speed at specified time
        void showAllData();            // Prints entire dataset
        void search(double speed);     // Search for a specified speed, print corresponding time if found
};

#endif /* Calibrator_hpp*/