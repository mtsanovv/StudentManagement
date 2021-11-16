#include <string>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
	// constants that can be used in all classes
	const unsigned short SEMESTERS_PER_YEAR = 2;
	const unsigned short GRADES_PER_SEMESTER = 5;
	const std::string STUDENT_MANAGEMENT_STORAGE_FILE = "StudentManagement.mgmt"; // file is used for persistent storage of StudentWithGrades collection
	const std::string STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER = "\n---------------------------------------------------------------\n"; // delimiter that separates each serialized StudentWithGrades
	const char STUDENT_MANAGEMENT_GRADES_DELIMITER = ','; // delimiter that separates each grade in the file for a given StudentWithGrades
}

#endif
