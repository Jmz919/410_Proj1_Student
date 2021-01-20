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

vector<process_stats> process;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	process.clear();
	string file(filename);
	ifstream inputFile(file);

	if (!inputFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	string myText;
	while(getline(inputFile, myText)) {
		process_stats stats;
		vector<int> row;
		myText.erase(remove(myText.begin(), myText.end(), ' '), myText.end());
		stringstream line(myText);

		// bool heading = false;
		while(line.good()) {
			string ele;
			getline(line, ele, CHAR_TO_SEARCH_FOR);
			if (isdigit(ele[0])) {
				row.push_back(stringToInt(ele.c_str()));
			}
			// else {
			// 	heading = true;
			// }
		}

		if (row.size() == 4) {
			stats = {row[0], row[1], row[2], row[3]};
			process.push_back(stats);
		}
		// else {
		// 	if (!heading) {
		// 		return FAIL;
		// 	}
		// }
	}

	inputFile.close();
	return SUCCESS;
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
	return process.size();
}


