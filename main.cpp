//
//  main.cpp
//  Sets
//
//  Created by Justin Reian Balite Mercado on 11/19/19.
//  Copyright © 2019 Justin Reian Balite Mercado. All rights reserved.
//

#include <iostream>
#include "SetT.h"
#include <string>
#include <fstream>
#include <vector>
#include <forward_list>

using namespace std;

void PrintStuff(int& elem){
    cout << elem << " ";
}

int WriteStuff(int &elem){
    return elem;
}

bool isEven(int& elem){
    if(elem%2){
        return false;
    }
    return true;
}

bool isOdd(int& elem){
    if(elem%2){
        return true;
    }
    return false;
}

template<class T>
void resetSets(SetT<T> a, SetT<T> b);

int main() {
    SetT<int> SetA;
    SetT<int> SetB;
    SetT<int> SetD;
    SetT<int> SetE;
    SetT<int> SetF;
    
    ifstream inFile;
    ofstream outFile;
    cout << "What is the name of the input file? ";
    string fileName;
    cin >> fileName;
    inFile.open(fileName);
    outFile.open("outfile.txt");
    
    if(inFile){
        cout << "Found file" << endl;
        string command;
        inFile>>command;
        while(command!="quit"){
            if(command == "add"){
                string nameOfSet;
                int addNum;
                inFile>>nameOfSet;
                inFile>>addNum;
                if(nameOfSet == "A" || nameOfSet == "a"){
                    SetA+addNum;
                    outFile<<"Added " << addNum << " to set " << nameOfSet << endl;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    SetB.add(addNum);
                    outFile<<"Added " << addNum << " to set " << nameOfSet << endl;
                }
                inFile>>command;
            }
            if(command == "remove"){
                string nameOfSet;
                int removeNum;
                inFile>>nameOfSet;
                inFile>>removeNum;
                if(nameOfSet == "A" || nameOfSet == "a"){
                    SetA-removeNum;
                    outFile<<"Removed " << removeNum << " to set " << nameOfSet << endl;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    SetB.remove(removeNum);
                    outFile<<"Removed " << removeNum << " to set " << nameOfSet << endl;
                }
                inFile>>command;
            }
            if(command == "union"){
                
                SetT<int> SetC = SetA+SetB;
                outFile << "The union result is: ";
                vector<int> myVector = SetC.traverse(PrintStuff);
                for(int i= 0; i<myVector.size(); i++){
                    outFile<< myVector[i] << " ";
                }
                outFile<<endl;
                inFile>>command;
            }
            if(command == "difference"){
                
                SetT<int> SetD = SetA-SetB;
                outFile << "The difference result is: ";
                vector<int> myVector = SetD.traverse(PrintStuff);
                for(int i= 0; i<myVector.size(); i++){
                    outFile<< myVector[i] << " ";
                }
                outFile<<endl;
                inFile>>command;
            }
            if(command == "intersection"){
                SetT<int> SetE = SetA*SetB;
                outFile << "The intersection result is: ";
                vector<int> myVector = SetE.traverse(PrintStuff);
                for(int i= 0; i<myVector.size(); i++){
                    outFile<< myVector[i] << " ";
                }
                outFile<<endl;
                inFile>>command;
            }
            if(command == "size"){
                string nameOfSet;
                inFile>>nameOfSet;
                if(nameOfSet == "A" || nameOfSet == "a"){
                    outFile << "The size of " << nameOfSet << " is: " << SetA.size() << endl;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    outFile << "The size of " << nameOfSet << " is: " << SetB.size() << endl;
                }
                inFile >> command;
            }
            if(command == "filterEven"){
                string nameOfSet;
                inFile>>nameOfSet;
                outFile << "The isEven filter result is: ";
                if(nameOfSet == "A" || nameOfSet == "a"){
                    vector<int> myVector = SetA.traverse(isEven);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    vector<int> myVector = SetB.traverse(isEven);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
            }
            if(command == "filterOdd"){
                string nameOfSet;
                inFile>>nameOfSet;
                outFile << "The isOdd filter result is: ";
                if(nameOfSet == "A" || nameOfSet == "a"){
                    vector<int> myVector = SetA.traverse(isOdd);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    vector<int> myVector = SetB.traverse(isOdd);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
            }
            if(command == "print"){
                string nameOfSet;
                inFile>>nameOfSet;
                outFile << "The contents of Set " << nameOfSet << " is: ";
                if(nameOfSet == "A" || nameOfSet == "a"){
                    vector<int> myVector = SetA.traverse(PrintStuff);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
                if(nameOfSet == "B" || nameOfSet == "b"){
                    vector<int> myVector = SetB.traverse(PrintStuff);
                    for(int i= 0; i<myVector.size(); i++){
                        outFile<< myVector[i] << " ";
                    }
                    outFile<<endl;
                    inFile>>command;
                }
            }
        }
    }
    else{
        cout << "Unable to find input file" << endl;
        outFile << "Unable to find input file" << endl;
    }
    cout << "Quitting Program" << endl;
    outFile<< "Quiting Program" << endl;
    inFile.close();
    outFile.close();
    
    return 0;
}

template <class T>
void resetSets(SetT<T> a, SetT<T> b){
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);
    a.add(5);
    b.add(2);
    b.add(1);
    b.add(7);
    b.add(8);
}
