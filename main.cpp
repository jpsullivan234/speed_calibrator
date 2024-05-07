#include "Calibrator.hpp"
#include "Calibrator.cpp"
#include <iostream>
using namespace std;

Calibrator gpsData("RTK_GPS.txt");
Calibrator watchData("SmartWatch.txt");
Calibrator &source = gpsData;


int main(){
    bool bflag = 0;
    bool exit = 0;
    char option;
    double input;

    while (!exit){       // Main loop; runs continuously until exit
        bflag = 0;
        cout<<"\n========== SPEED CALIBRATOR MENU =========="<<endl;
        cout<<"\nselect a data source:"<<endl;
        cout<<"\t1. 'RTK_GPS.txt'"<<endl;
        cout<<"\t2. 'SmartWatch.txt'"<<endl;
        cout<<"\ttype 1, 2 or 'x' to exit: ";

        cin>>option;
        cout<<endl;

        if (option == 'x') break;
        if (option == '1') source = gpsData;
        if (option == '2') source = watchData;

        cout<<source.name<<" Menu: "<<endl;
        cout<<"\te - find errors in the data"<<endl;
        cout<<"\tg - get the speed at a certain time"<<endl;
        cout<<"\ta - show all accurate data"<<endl;
        cout<<"\ts - search for the index of a certain speed"<<endl;
        cout<<"\tb - go back"<<endl;
        cout<<"\tx - exit"<<endl;

        while (!exit && !bflag){
            cout<<"\nChoose an option from the menu: ";
            cin>>option;
            cout<<endl;

            switch (option){
                case 'e': source.findErrors(); 
                    break;

                case 'g': 
                    cout<<"\t enter time value as an int: ";
                    cin>>input; cout<<endl;
                    gpsData.getSpeed(input);
                    break;

                case 'a': gpsData.showAllData();
                    break;

                case 's': 
                    cout<<"\t enter speed: ";
                    cin>>input; cout<<endl;
                    gpsData.search(input);
                    break;

                case 'b': bflag = 1;
                break;

                case 'x': exit = 1;
                break;

                default: cout<<"Error: please select a viable option"<<endl;
                break;
            }
        }
    }
    cout<<"========== Thank you for using Calibrator =========="<<endl;

    return 0;
}