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

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	data.clear();
	string file(filename);
	ifstream inputFile(file);

	if (!inputFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	string myText;
	while(!inputFile.eof()) {
		getline(inputFile, myText);
		process_stats stats;
		vector<int> row;
		myText.erase(remove(myText.begin(), myText.end(), ' '), myText.end());
		stringstream line(myText);

		while(line.good()) {
			string ele;
			getline(line, ele, CHAR_TO_SEARCH_FOR);
			if (isdigit(ele[0])) {
				row.push_back(stringToInt(ele.c_str()));
			}
		}

		if (row.size() == 4) {
			stats = {row[0], row[1], row[2], row[3]};
			data.push_back(stats);
		}
	}

	inputFile.close();
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	int data_size = data.size();
	switch(mySortOrder) {
		case (CPU_TIME):
			for (int i = 0; i < data_size - 1; i++) {
				for (int j = 0; j < data_size - i - 1; j++) {
					if (data[j].cpu_time > data[j+1].cpu_time) {
						struct process_stats temp;
						temp.process_number = data[j].process_number;
						temp.start_time = data[j].start_time;
						temp.cpu_time = data[j].cpu_time;
						temp.io_time = data[j].io_time;

						data[j] = data[j+1];
						data[j+1] = temp;
					}
				}
			}
			break;
		case (PROCESS_NUMBER):
			for (int i = 0; i < data_size - 1; i++) {
				for (int j = 0; j < data_size - i - 1; j++) {
					if (data[j].process_number > data[j+1].process_number) {
						struct process_stats temp;
						temp.process_number = data[j].process_number;
						temp.start_time = data[j].start_time;
						temp.cpu_time = data[j].cpu_time;
						temp.io_time = data[j].io_time;

						data[j] = data[j+1];
						data[j+1] = temp;
					}
				}
			}
			break;
		case (START_TIME):
			for (int i = 0; i < data_size - 1; i++) {
				for (int j = 0; j < data_size - i - 1; j++) {
					if (data[j].start_time > data[j+1].start_time) {
						struct process_stats temp;
						temp.process_number = data[j].process_number;
						temp.start_time = data[j].start_time;
						temp.cpu_time = data[j].cpu_time;
						temp.io_time = data[j].io_time;

						data[j] = data[j+1];
						data[j+1] = temp;
					}
				}
			}
			break;
		case (IO_TIME):
			for (int i = 0; i < data_size - 1; i++) {
				for (int j = 0; j < data_size - i - 1; j++) {
					if (data[j].io_time > data[j+1].io_time) {
						struct process_stats temp;
						temp.process_number = data[j].process_number;
						temp.start_time = data[j].start_time;
						temp.cpu_time = data[j].cpu_time;
						temp.io_time = data[j].io_time;

						data[j] = data[j+1];
						data[j+1] = temp;
					}
				}
			}
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


