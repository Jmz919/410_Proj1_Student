/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

std::vector<process_stats> process;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	string file(filename);
	ifstream inputFile(file);

	if (inputFile.is_open()) {
//		string myText;
//		while(getline(inputFile, myText)) {
//			process_stats stats;
//			std::vector<int> row;
//			stringstream line(myText);
//			string ele;
//			getline(line, ele, ',');
//			row.push_back(stringToInt(ele.c_str()));
//
//			if (row.size() == 4) {
//				stats = {row[0], row[1], row[2], row[3]};
//			}
//			else {
//				return FAIL;
//			}
//			process.push_back(stats);
//		}

		inputFile.close();
		return SUCCESS;
	}
	else {
		return COULD_NOT_OPEN_FILE;
	}
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return 0;
}


