#include <string>

#ifndef STUDENTMANAGEMENTIO_H
#define STUDENTMANAGEMENTIO_H

// StudentManagementIO namespace
namespace StudentManagementIO {
	// namespace contains only static methods for reading and writing to the file that is used as persistent storage
	void writeToFile(std::string content); // the only argument content is what is written to the file
	std::string readFromFile(); // a method that reads the serialized data from the file
}

#endif
