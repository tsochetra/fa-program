// include useful libraries
#include <iostream>
#include <string>
#include <fstream>
#include "functions.h"
#include "create_fa.h"
#include "load_fa.h"
#include "delete_fa.h"
#include "convert_fa.h"
#include "test_fa.h"

using namespace std;

int loaded = 0; // is FA file loaded to program ?
string fa, file; // store content of FA file
int choice; // user menu option

// clear previous data from console (UNIX)
void clearConsole() {
    system("clear");
}

// display header of the program
void displayHeader() {
    clearConsole();
    cout<<"███████╗ █████╗     ██████╗ ██████╗  ██████╗  ██████╗ ██████╗  █████╗ ███╗   ███╗"<<endl;
    cout<<"██╔════╝██╔══██╗    ██╔══██╗██╔══██╗██╔═══██╗██╔════╝ ██╔══██╗██╔══██╗████╗ ████║"<<endl;
    cout<<"█████╗  ███████║    ██████╔╝██████╔╝██║   ██║██║  ███╗██████╔╝███████║██╔████╔██║"<<endl;
    cout<<"██╔══╝  ██╔══██║    ██╔═══╝ ██╔══██╗██║   ██║██║   ██║██╔══██╗██╔══██║██║╚██╔╝██║"<<endl;
    cout<<"╚═╝     ╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝"<<endl;

}

// display menu to user
void displayMenu() {
    cout<<"Welcome to FA Program, ";
    if(loaded) {
        cout<<"your current FA: "<<file<<endl;
        cout<<"Please choose your options: "<<endl;
    } else {
        cout<<"please choose your options: "<<endl;
    }

    // if FA file is loaded, we display more operations
    cout<<"   1. Load FA from file"<<endl;
    cout<<"   2. Create new FA"<<endl;
    if(loaded) {
        cout<<"   3. Convert NFA to DFA"<<endl;
        cout<<"   4. Minimize DFA (not yet implemented)"<<endl;
        cout<<"   5. Test FA string"<<endl;
        cout<<"   6. Delete current FA file"<<endl;
        cout<<"   7. Exit the program"<<endl;
    } else {
        cout<<"   3. Exit the program"<<endl;
    }
}

// driver code
int main() {

    int loop = 1; // loop the program
    displayHeader();
    displayMenu();

    while(loop) {
        
        cout<<"Your choice: ";
        cin>>choice;

        switch(choice) {
            case 1: // load file operation
                displayHeader();
                file = loadFile();
                if(file != "no") {
                    loaded = 1;
                    fa = readFile(file);
                    displayHeader();
                    cout<<"You have loaded your FA file successfully."<<endl;
                    displayMenu();
                } else {
                    displayHeader();
                    displayMenu();
                }
                continue;
            break;
            case 2: // create FA file operation
                displayHeader();
                if(CreateFA(&file)) {
                    loaded = 1;
                    fa = readFile(file);
                    displayHeader();
                    cout<<"You have created your FA file successfully."<<endl;
                    displayMenu();
                    continue;
                }
            break;
            case 3: // convert general FA to DFA
                if(!loaded) {
                    clearConsole();
                    loop  = 0;
                } else {
                    displayHeader();
                    convertFA(fa);
                    displayHeader();
                    displayMenu();
                    continue;
                }
            break;
            default: // invalid option
                if(!loaded) {
                    cout<<"Please choose a correct one."<<endl;
                }
        }

        if(loaded) {
            switch(choice) {
                case 4: // minimize fa
                    cout<<4;
                break;
                case 5: // test string
                    testFA(fa);
                    displayHeader();
                    displayMenu();
                    continue;
                break;
                case 6: // delete FA
                    displayHeader();
                    if(deleteFA(file)) {
                        loaded = 0;
                        file = "";
                        fa = "";
                        displayHeader();
                        cout<<"You have deleted your FA file successfully."<<endl;
                        displayMenu();
                        continue;
                    } else {
                        displayHeader();
                        displayMenu();
                        continue;
                    }
                break;
                case 7: // exit the program
                    clearConsole();
                    loop = 0;
                break;
                default: // invalid option
                    cout<<"Please choose a correct one."<<endl;
            } 
        }
    
    }
}