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
		// also, we do not need an accessor for this field, as all operations with studentsCollection should be done in this class
	public:
		StudentWithGradesCollection(); // a constructor method that initializes the studentsCollection
		std::string serializeStudentsCollection(); // a method that returns a serialized studentsCollection
		std::string serializeStudentData(StudentWithGrades *student); // a method that returns a serialized StudentWithGrades
		void persistStudentsCollection(); // a method that persists the serialized studentsCollection
		void deserializeStudentsCollection(std::string serializedStudentsCollection); // a method that deserializes a serialized studentsCollection and adds the StudentWithGrades eleements to the studentsCollection
		void deserializeStudentData(std::string studentData); // a method that deserializes a serialized Student
		void deserializeStudentGrades(std::string grades, int *studentGrades); // a method that deserializes a student's grades
		bool studentWithFacultyNumberExists(int facultyNumber); // a method that is used when creating a new student to check if a student with the same faculty number exists
		void addNewStudentToCollection(); // a method that creates a new StudentWithGrades object and then pushes it to the studentsCollection vector
};

#endif
