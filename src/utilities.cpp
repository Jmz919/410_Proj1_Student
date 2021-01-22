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

vector<process_stats> data;

// Private sort functions for process_stats struct
bool sortCPU(process_stats i, process_stats j) {
	return i.cpu_time < j.cpu_time;
}

bool sortProcess(process_stats i, process_stats j) {
	return i.process_number < j.process_number;
}

bool sortStart(process_stats i, process_stats j) {
	return i.start_time < j.start_time;
}

bool sortIO(process_stats i, process_stats j) {
	return i.io_time < j.io_time;
}

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	// Make sure to clear the vector upon a new file being uploaded
	data.clear();
	string file(filename);
	ifstream inputFile(file);

	// Ensure the file is open before proceeding
	if (!inputFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	
	string myText;
	bool first = ignoreFirstRow;
	while(!inputFile.eof()) {
		getline(inputFile, myText);

		// If ignoreFirstRow is true ignore the first row and set first to false
		// If ignoreFirstRow is false proceed normally
		if (!first) {
			process_stats stats;
			vector<int> row;
			
			// Remove whitespace from the string to help with parsing
			myText.erase(remove(myText.begin(), myText.end(), ' '), myText.end());
			stringstream line(myText);

			// Parse line from file by searching for CHAR_TO_SEARCH_FOR
			while(line.good()) {
				string ele;
				getline(line, ele, CHAR_TO_SEARCH_FOR);
				
				// Ensure each part of the string is a digit before converting to int
				if (isdigit(ele[0])) {
					row.push_back(stringToInt(ele.c_str()));
				}
			}

			// Make sure the row has all for process stats before adding to global vector
			if (row.size() == 4) {
				stats = {row[0], row[1], row[2], row[3]};
				data.push_back(stats);
			}
		}
		else {
			first = !first;
		}
	}

	inputFile.close();
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder) {
		case (CPU_TIME):
			sort(data.begin(), data.end(), sortCPU);
			break;
		case (PROCESS_NUMBER):
			sort(data.begin(), data.end(), sortProcess);
			break;
		case (START_TIME):
			sort(data.begin(), data.end(), sortStart);
			break;
		case (IO_TIME):
			sort(data.begin(), data.end(), sortIO);
			break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	if (data.size() > 0) {
		myFirst = data[0];
		data.erase(data.begin());
	}

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return data.size();
}


