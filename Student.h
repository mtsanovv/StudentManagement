#include <string>
#ifndef STUDENT_H
#define STUDENT_H

// Student class declaration
class Student {
	private:
		// fields of the class
		std::string name;
		int facultyNumber;
		unsigned short groupId;
		unsigned short courseYear;
	public:
		Student(); // declaration of the constructor
		// declaration of accessors of all class fields
		std::string getName();
		int getFacultyNumber();
		unsigned short getGroupId();
		unsigned short getCourseYear();
		// declaration of methods that will initialize all class fields with information from STDIN
		void initName();
		void initFacultyNumber();
		void initGroupId();
		void initCourseYear();
		void requestCourseYear(); // method that will read the actual STDIN input for course year, because course year requires validation
};

#endif
