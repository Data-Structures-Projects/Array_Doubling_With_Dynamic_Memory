#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    // TODO
    if(argc != 6){
    cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Variant> <Query_Start_Age> <Query_End_Age>" << endl;
    return -1;
    }

    ifstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        cout << "input file could not be opened"<< endl;
        return -1;
    }
    int arrCapacity = 10;
    int recordIdx = 0;
    int doublingCounter = 0;
    CovidCase* cases = new CovidCase[arrCapacity];
    string queryParams[4] = {argv[2], argv[3], argv[4], argv[5]};
    parseFile(inputFile, queryParams, cases, arrCapacity, recordIdx, doublingCounter);
    inputFile.close();
    sortCases(cases, recordIdx);

    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of cases returned after the query: " << recordIdx << endl;
    cout << "Queried Cases" << endl;
    cout << "---------------------------------------" << endl;
    printQueriedCases(cases, recordIdx);
    return 0;
}