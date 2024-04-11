#include "array_double.hpp"
#include <sstream>

void parseFile(ifstream& input, string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter){
    // TODO
    CovidCase temp;
    int index = 0;
    string data;
    string line;
    while(getline(input, line)){
        stringstream str(line);
        while(getline(str, data, ',')){
                if(index == 0){
                    temp.name = data;
                }
                if(index == 1){
                    temp.variant = data;
                }
                if(index == 2){
                    temp.location = data;
                }
                if(index == 3){
                    temp.age = stoi(data);
                }
                index = index + 1;
        }
    if(isCaseQueried(temp, queryParams[0], queryParams[1],stoi(queryParams[2]), stoi(queryParams[3]))){
        addCase(cases, temp, arrCapacity, recordIdx, doublingCounter);
    }
    index = 0;
    }
}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge) {
    if(covidCase.location == queryLocation){
        if(covidCase.variant == queryVariant){
            if(covidCase.age >= startAge){
                if(covidCase.age <= endAge){
                    return true;
                }
            }
        }
    }
    return false;
}

void resizeArr(CovidCase *&cases, int *arraySize) {
    // TODO
     CovidCase *dbl = new CovidCase[*arraySize*2];
    for (int i = 0; i < *arraySize; i++) {
        dbl[i] = cases[i];
    }
    delete[] cases;
    cases = dbl;
}

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter) {
        if(recordIdx >= arrCapacity){
            resizeArr(cases, &arrCapacity);
            arrCapacity = arrCapacity * 2;
            doublingCounter = doublingCounter + 1;
        }
        cases[recordIdx] = covidCase;
        recordIdx = recordIdx + 1;
}

void sortCases(CovidCase* cases, int length) {
    CovidCase temp;
    for(int i = 0; i< length; i++){
        for(int j = i + 1; j < length; j++){
            if(cases[j].age<cases[i].age){
                temp = cases[i];
                cases[i] = cases[j];
                cases[j] = temp;
            }
            if(cases[j].age == cases[i].age){
                if(cases[j].name < cases[i].name){
                    temp = cases[i];
                    cases[i] = cases[j];
                    cases[j] = temp;
                }
            }
        }
    }
}

void printQueriedCases(CovidCase* cases, int numOfRecords) {
    for(int i = 0; i < numOfRecords; i++){
        cout << cases[i].name << " " << cases[i].age << endl;
    }
}