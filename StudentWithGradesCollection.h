#include <string>
#include <vector>
#include "StudentWithGrades.h"

#ifndef STUDENTWITHGRADESCOLLECTION_H
#define STUDENTWITHGRADESCOLLECTION_H

// StudentWithGradesCollection class declaration
class StudentWithGradesCollection {
	private:
		// the only field is a vector with StudentWithGrades objects
		std::vector<StudentWithGrades*> studentsCollection;
	public:
		StudentWithGradesCollection(); // a constructor method that will initialize the studentsCollection
		std::string serializeStudentsCollection(); // a method that will return a serialized studentsCollection
		void deserializeStudentsCollection(std::string serializedStudentsCollection); // a method that deserializes a serialized studentsCollection and adds the StudentWithGrades eleements to the studentsCollection
		void deserializeStudentData(std::string studentData); // a method that deserializes a serialized Student
		void deserializeStudentGrades(std::string grades, int *studentGrades); // a method that deserializes a student's grades
		bool studentWithFacultyNumberExists(int facultyNumber); // a method that will be used when creating a new student to check if a student with the same faculty number exists
};

#endif
