#include "Calibrator.hpp"
#include <iostream>
using namespace std;

void showMenu(Calibrator *obj){
    cout<<obj->name<<" Menu: "<<endl;
    cout<<"\te - find errors in the data"<<endl;
    cout<<"\tg - get the speed at a certain time"<<endl;
    cout<<"\ta - show all accurate data"<<endl;
    cout<<"\ts - search for the index of a certain speed"<<endl;
    cout<<"\ty - show the average accelaration"<<endl;
    cout<<"\tn - show the average noise in the dataset\n"<<endl;
    cout<<"\tb - go back"<<endl;
    cout<<"\tx - exit"<<endl;
}

Calibrator gpsData("RTK_GPS.txt");          // create a Calibrator obj for each dataset
Calibrator watchData("SmartWatch.txt");
Calibrator *source;                         // pointer to allow for easy access to the dataset; will be assigned later

int main(){
    bool bflag = 0;      // 'back' flag to signal when to go back
    bool exit = 0;       // 'exit' flag to signal when to exit
    char option;         // stores the input option selected
    double input;        // stores the number inputted

    while (!exit){       // Main loop; runs continuously until exit
        do{              // Loop for main menu; 'do' statement allows it to run at least once to check for wrong inputs
            bflag = 0;   // reset the back flag to 0
            cout<<"\n========== SPEED CALIBRATOR MENU =========="<<endl;
            cout<<"\nselect a data source:"<<endl;
            cout<<"\t1. 'RTK_GPS.txt'"<<endl;
            cout<<"\t2. 'SmartWatch.txt'"<<endl;
            cout<<"\ttype 1, 2 or 'x' to exit: ";

            cin>>option;
            cout<<endl;

            if (option == 'x') exit = 1;
            else if (option == '1') source = &gpsData;
            else if (option == '2') source = &watchData;
            else{
                cout<<"Error: please select a viable option"<<endl;
                option = 'Z';
            }
        } while (option == 'Z');

        showMenu(source);

        while (!exit && !bflag){        // Second loop: allows the user to select what to do w the dataset chosen
            cout<<"\nChoose an option or press 'm' to see menu: ";
            cin>>option;

            switch (option){            // switch between options selected by the user
                case 'e': source->findErrors(); 
                    break;

                case 'g': 
                    cout<<"--> enter time value as an int: ";
                    cin>>input;
                    source->getSpeed(input);
                    break;

                case 'a': source->showAllData();
                    break;

                case 's': 
                    cout<<"--> enter speed: ";
                    cin>>input;
                    source->search(input);
                    break;
                case 'y': source->getAccel();
                break;

                case 'n': source->getNoise();
                break;
                
                case 'm': showMenu(source);
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
    cout<<"========== Thank you for using Calibrator ==========\n"<<endl;

    return 0;
}