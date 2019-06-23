// include libraries
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>

using namespace std;

// class for loading file from directory
class LoadFile { 
    
    public: 
    string list[100]; // array of FA file name in data folder
    int total;

    // constructor set total FA file in data folder, init to 0
    LoadFile() {
        total = 0;
    }

    // scan folder data
    void getListFile() {
        DIR *pDIR;
        struct dirent *entry;

        pDIR = opendir("./data"); // open directory data

        if(pDIR) { // if exist

            entry = readdir(pDIR); // read first file
            
            while(entry != NULL){

                // check if not a directory, then it is a file
                if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

                    // get file name with extension and length
                    string file = entry->d_name;
                    int length = file.length();

                    // get extension of the file, get last 3 chars
                    string file_ext = file.substr(length - 3);
                    
                    // push file that has .fa extension to list
                    if(file_ext == ".fa") {
                        //list with index of total and increase total by 1
                        LoadFile::list[LoadFile::total++] = file; 
                    }
                    
                }  
                entry = readdir(pDIR); // next file
            }
            closedir(pDIR); // close directory

        } else { // directory data is not existed in root directory
            cout<<"Directory not found."<<endl;
        }
    }

};

// load file
string loadFile () {

    int temp; // user option
    string c;
    LoadFile load_file; // new class LoadFile

    load_file.getListFile(); // get all files from folder

    // if FA files are existed in folder
    if(load_file.total > 0) {
        // print every file to console
        for(int i = 0; i < load_file.total; i++) {
            cout<<i+1<<". "<<load_file.list[i]<<endl;
        }
        cout<<endl;

        // ask user to choose which file
        while(true) {
            cout<<"Please choose your file: ";
            cin>>temp;

            // if valid option from user
            if(temp > 0 && temp <= load_file.total) {
                return load_file.list[temp - 1]; // array start from 0, but console start from 1
            }
        }
    // otherwise
    } else {
        cout<<"There is no FA file in the folder."<<endl;
        cout<<"Enter e to exit: ";
        cin>>c;
        return "no";
    }
}

