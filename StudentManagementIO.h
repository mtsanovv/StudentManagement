#include <string>

#ifndef STUDENTMANAGEMENTIO_H
#define STUDENTMANAGEMENTIO_H

// StudentManagementIO namespace
namespace StudentManagementIO {
	// namespace contains only static methods for reading and writing to the file that is used as persistent storage
	void writeToFile(std::string content); // the only argument content will be what will be written to the file
	std::string readFromFile();
}

#endif
