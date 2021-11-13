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
		StudentWithGrades(std::string studentName, int studentFacultyNumber, unsigned short studentGroupId, unsigned short studentCourseYear, int *studentGrades, int studentGradesCount); // constructor overloading - we need this constructor in order to be able to initialize StudentWithGrades and respectively a Student after its data has been fetched from the file
		~StudentWithGrades(); // declaration of destructor - the destructor is needed here to free the memory of the grades dynamic array
		// accessors of the grades field and its length
		int* getGrades();
		int getGradesCount();
		// initialize the grades field with STDIN input
		void initGrades();
		void requestGrades(); // an auxiliary method that requests grades from the user and adds them to the grades array
		void requestGrade(int courseYear, int semesterId, int gradeId); // an auxiliary method that requests a specific grade from the user
		// the request methods are needed because each grade needs validation
		double calculateOverallAverageGrade(); // calculates the overall average grade
		double calculateLastSemestersAverageGrade(); // calculates the last two semesters' average grade
		void printAverageGrades(); // prints the overall average grade and the last two semesters average grade
};

#endif
