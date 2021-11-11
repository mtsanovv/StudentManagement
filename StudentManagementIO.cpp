#include <iostream>
#include <fstream>
#include <sstream>
#include "StudentManagementIO.h"
#include "Constants.h"

using namespace std;

namespace StudentManagementIO {
	// namespace contains only static methods for reading and writing to the file that is used as persistent storage
	void writeToFile(string content) {
		// implementation of a method that will be writing to the file the only argument that can be passed to it, content
		ofstream persistentStorage(Constants::STUDENT_MANAGEMENT_STORAGE_FILE.c_str()); // open the file for writing
		if(!persistentStorage.is_open()) {
			// if the file is not open, exit - something very messed up has happened
			cout << "Cannot open " << Constants::STUDENT_MANAGEMENT_STORAGE_FILE << " for writing!" << endl;
			exit(1);
		}
		// if the file is open, write to it
		persistentStorage << content;
		// a good practice is to always close the file
		persistentStorage.close();
	}
	
	string readFromFile() {
		ifstream persistentStorage(Constants::STUDENT_MANAGEMENT_STORAGE_FILE.c_str()); // open the file for reading
		if(!persistentStorage.is_open()) {
			// if the file is not open, no need to exit, we can just return an empty string as we really cannot check in C++ if the file exists
			return "";
		}
		
		stringstream strStream; // a stringstream that we will fill with the contents of the file
		strStream << persistentStorage.rdbuf(); // read the file
		// a good practice is to always close the file
		persistentStorage.close();
		return strStream.str(); // stringStream.str() returns the contents of the file as a string
	}
}
