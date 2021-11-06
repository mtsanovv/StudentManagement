#include "Student.h"

#ifndef STUDENTWITHGRADES_H
#define STUDENTWITHGRADES_H


// StudentWithGrades class declaration
// StudentWithGrades is derived from Student
class StudentWithGrades: public Student {
	private:
		// the only fields of StudentWithGrades are a dynamic array of grades - unsigned short int and its length
		int *grades;
		int gradesCount;
	public:
		StudentWithGrades(); // declaration of the constructor
		~StudentWithGrades(); // declaration of destructor - the destructor is needed here to free the memory of the grades dynamic array
		// accessors of the grades field and its length
		int* getGrades();
		int getGradesCount();
		// initialize the grades field with STDIN input
		void initGrades();
		void requestGrades(); // an auxiliary method that will be requesting grades from the user and adding them to the grades array
		void requestGrade(int courseYear, int semesterId, int gradeId); // an auxiliary method that will be requesting a specific grade from the user
		// the request methods are needed because each grade needs validation
};

#endif
