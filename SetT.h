//
//  SetT.h
//  Sets
//
//  Created by Justin Reian Balite Mercado on 11/19/19.
//  Copyright © 2019 Justin Reian Balite Mercado. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include<forward_list>
#include<unordered_map>
#include <vector>
using namespace std;

#ifndef SetT_h
#define SetT_h

template<class T>
class SetT
{
public:
    SetT();
    SetT(int numBucks);
    void add(T addNumber);
    bool contains(T containNumber);
    void remove(T removeNumber);
    void unionSets(SetT otherSet);
    void differenceSets(SetT otherSet);
    void intersectionSets(SetT otherSet);
    vector<T> traverse(void visit(T& elem));
    vector<T> traverse(bool visit(T& elem));
    void filter(bool fnc(T elem));
    int size(){ return numElems; };
    SetT operator=(SetT & otherSet); //Reassignment
    SetT operator+(SetT & otherSet); //Union
    SetT operator-(SetT & otherSet); //Difference
    SetT operator*(SetT & otherSet); //Intersection
    SetT operator+(T num); //Addition
    SetT operator-(T num); //Subtraction
private:
    forward_list<T>** buckets;    // An array of forward_list's (ie, each index is a forward_list pointer)
    int numBuckets;
    int getHashIndex(const T& elem);
    int numElems;
};

template<class T>
SetT<T>::SetT(){
    // Create an array of forward_lists and initially set each bucket to an empty forward list
    buckets = new forward_list<T>*[100];
    for (int i = 0; i < 100; i++) {
        buckets[i] = nullptr;
    }
    numBuckets = 100;
    numElems = 0;
//    cout << "Successfully SetT() with 100 buckets \n";
}

template<class T>
SetT<T>::SetT(int numBucks){
    // Create an array of forward_lists and initially set each bucket to null
    buckets = new forward_list<T>*[numBucks];
    for (int i = 0; i < numBucks; i++) {
        buckets[i] = nullptr;
    }
    numBuckets = numBucks;
    numElems=0;
//    cout << "Successfully SetT(int numBucks) with " << numBucks << " buckets \n";
}

template<class T>
int SetT<T>::getHashIndex(const T& key)
{
    unordered_map<int,T> mapper;
    typename unordered_map<int,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}

template<class T>
bool SetT<T>::contains(T containNumber){
    //Checks to see if the number is in the set
    
    //Get the hash
    int hashIndex = getHashIndex(containNumber);
    
    //Debug force hashIndex to be 0
//    int hashIndex = 0;
    
//    cout << "The hash index is: " << hashIndex << endl;
    
    if(buckets[hashIndex]==nullptr){ //there is no current forwardList at this hashIndex
        return false; //Did not find the number in the set Go ahead and add it to Set.
    }
    else{ //there is a current forwardList at this hashIndex, check it to make sure the number isnt there
        for(auto it = buckets[hashIndex]->begin(); it != buckets[hashIndex]->end(); ++it){
            if(*it == containNumber){
//                cout << "Found the number " << containNumber << " in the bucket's forward list" << endl;
                return true; //Found the number in the set, DO NOT add the number
            }
        }
//        cout << "Did not find the number in the bucket's forward list" << endl;
        return false; //Did not find the number in the set, even after checking forward list at correct bucket index. Go ahead and add it to Set.
    }
}

template<class T>
vector<T> SetT<T>::traverse(void visit(T& elem)){
    vector<T> myVector;
    for(int i = 0; i<numBuckets; i++){
        if(buckets[i]!=nullptr){
            for (auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it){
                visit(*it);
                myVector.push_back(*it);
            }
        }
    }
    cout << endl;
    return myVector;
}

template<class T>
vector<T> SetT<T>::traverse(bool visit(T& elem)){
    vector<T> myVector;
    for(int i = 0; i<numBuckets; i++){
        if(buckets[i]!=nullptr){
            for (auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it){
                bool isEvenRes= visit(*it);
                if(isEvenRes){
                    myVector.push_back(*it);
                }
            }
        }
    }
    cout << endl;
    return myVector;
}

template<class T>
void SetT<T>::add(T addNumber){
    
    // First check if it already exists in the set
    bool containedInSet;
    containedInSet = contains(addNumber);
    
    //Get the hash
    int hashIndex = getHashIndex(addNumber);
    
    //Debug force hashIndex to be 0
//    int hashIndex = 0;
    
//    cout << "The hash index for " << addNumber << " is: " << hashIndex << endl;
    
    if(containedInSet){ //Number already exsists in set
//        cout << "The number " << addNumber << " already exists in the set. Did not add. \n";
    }
    else{ //Does not exsist in set
        if(buckets[hashIndex]==nullptr){ //there is no forward list at this bucket yet, initialize a forwardlist
//            cout << "At this hashIndex, the pointer is pointing to null. Going to create a forwardList \n";
            // Initialize a forwardlist
            buckets[hashIndex]= new forward_list<T>;
        }
        //Push the number into the forwardList
        buckets[hashIndex]->push_front(addNumber);
//        cout << "Successfully pushed number to forwardList at bucketIndex" << endl;
        numElems+=1;
    }
}

template<class T>
void SetT<T>::remove(T removeNumber){
    // Does the number exist in the set?
    bool containedInSet = contains(removeNumber);
    
    //Get the hash
    int hashIndex = getHashIndex(removeNumber);
    
    //Debugging force hashIndex = 0
//    int hashIndex = 0;
    
//    cout << "The hash index for " << removeNumber << " is: " << hashIndex << endl;

    if(containedInSet){
//        cout << "Found " << removeNumber << " in set. Removing." << endl;
        buckets[hashIndex]->remove(removeNumber);
        numElems-=1;
//        cout << "forwardList at hashIndex " << hashIndex << " contains: ";
//        for (auto it = buckets[hashIndex]->begin(); it != buckets[hashIndex]->end(); ++it){
//            cout << " " << *it;
//        }
//        cout << "\n";
    }
    else{
//        cout << "Number is not in set. Did not remove " << removeNumber << endl;
    }
}

template<class T>
void SetT<T>::unionSets(SetT otherSet){
    for(int i = 0; i<otherSet.numBuckets; i++){
        if(otherSet.buckets[i]!=nullptr){ //if there is some forwardList at this hashIndex
            for (auto it = otherSet.buckets[i]->begin(); it != otherSet.buckets[i]->end(); ++it){
                add(*it);
            }
        }
    }
}

template<class T>
void SetT<T>::differenceSets(SetT otherSet){
    for(int i = 0; i<otherSet.numBuckets; i++){
        if(otherSet.buckets[i]!=nullptr){ //if there is some forwardList at this hashIndex
            for (auto it = otherSet.buckets[i]->begin(); it != otherSet.buckets[i]->end(); ++it){
                remove(*it);
            }
        }
    }
}

template<class T>
void SetT<T>::intersectionSets(SetT otherSet){
    SetT<int> intersectionSetResult(numBuckets);
    for(int i = 0; i<numBuckets; i++){
        if(buckets[i]!=nullptr){ //if there is some forwardList at this hashIndex
            for (auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it){
                if(otherSet.contains(*it)){
//                    cout << "Yes it does contain " << *it << ". Adding number to intersectionSetResult" << endl;
                    intersectionSetResult.add(*it);
                }
                else{
//                    cout << "Not it does not contain " << *it << "." << endl;
                }
            }
        }
    }
    
    *this = intersectionSetResult;
    
    
//    for(int i = 0; i<intersectionSetResult.numBuckets; i++){
//        if(intersectionSetResult.buckets[i]!=nullptr){
//            for (auto it = intersectionSetResult.buckets[i]->begin(); it != intersectionSetResult.buckets[i]->end(); ++it){
//                cout << " " << *it;
//            }
//        }
//        cout << "\n";
//    }

}

template<class T>
inline SetT<T> SetT<T>::operator=(SetT & otherSet){
//    cout << "In overloaded = " << endl;
    for(int i = 0; i<numBuckets; i++){ //Clear all elements in this Set
        if(buckets[i]!=nullptr){
            for(auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it){
//                cout << "Popping " << *it << endl;
                buckets[i]->pop_front();
            }
        }
    }
    
    SetT<T> result = *this;
    
    for(int i = 0; i<otherSet.numBuckets; i++){
        if(otherSet.buckets[i]!=nullptr){
            for(auto it = otherSet.buckets[i]->begin(); it != otherSet.buckets[i]->end(); ++it){
                result.add(*it);
//                cout << "Adding " << *it << endl;
            }
        }
    }
    
    return result;
}

template<class T>
inline SetT<T> SetT<T>::operator+(SetT & otherSet)
{
    SetT<T> result = *this;
    result.unionSets(otherSet);
    return result;
}

template<class T>
inline SetT<T> SetT<T>::operator-(SetT & otherSet){
    SetT<T> result = *this;
    result.differenceSets(otherSet);
    return result;
}

template<class T>
inline SetT<T> SetT<T>::operator*(SetT & otherSet){
    SetT<T> result = *this;
    result.intersectionSets(otherSet);
    return result;
}

#endif /* SetT_h */

template<class T>
inline SetT<T> SetT<T>::operator+(T num){
    SetT<T> result = *this;
    result.add(num);
    return result;
}

template<class T>
inline SetT<T> SetT<T>::operator-(T num){
    SetT<T> result = *this;
    result.remove(num);
    return result;
}

template<class T>
void SetT<T>::filter(bool fnc(T elem)){
    for(int i = 0; i < numBuckets; i++){
        if(buckets[i]!=nullptr){
            for(auto it = buckets[i]->begin(); it != buckets[i]->end(); ++it){
                if(fnc(*it)){
                    cout << *it << " ";
                }
            }
        }
    }
}
