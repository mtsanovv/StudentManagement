#include <iostream>
#include "StudentWithGrades.h"
#include "Constants.h"

using namespace std;

StudentWithGrades::StudentWithGrades() {
	// constructor implementation
	// the superclass constructor will be called first and then this one when creating the StudentWithGrades object
	// call the method to initialize the grades field with STDIN input
	initGrades();
}

StudentWithGrades::~StudentWithGrades() {
	// destructor implementation
	// destructor is needed in StudentWithGrades to free the memory from the grades dynamic array
	delete[] grades;
}

int* StudentWithGrades::getGrades() {
	// implementation of accessor of grades field
	return grades;
}

int StudentWithGrades::getGradesCount() {
	// implementation of accessor of gradesCount field
	return gradesCount;
}

void StudentWithGrades::initGrades() {
	// implementation of initialization of grades field using the course year's value and some constants
	// calculate the count of grades by the grades per semester and semesters per year
	gradesCount = Student::getCourseYear() * Constants::SEMESTERS_PER_YEAR * Constants::GRADES_PER_SEMESTER;
	grades = new int(gradesCount); // dynamic array allocation
	// request grades from user
	requestGrades();
}

void StudentWithGrades::requestGrades() {
	// we need to request the student's grades from the user and validate each grade they input
	unsigned short studentCourseYear = Student::getCourseYear();
	for(int i = 1; i <= studentCourseYear; i++) {
		// outer loop for the course years - i is the course year
		for(int j = (i - 1) * Constants::SEMESTERS_PER_YEAR + 1; j <= i * Constants::SEMESTERS_PER_YEAR; j++) {
			// j starts from previous year number, times semesters per year plus one
			// inner loop for the semesters - j is the number of the semester - 1, 2, 3 and so on
			for(int k = 1; k <= Constants::GRADES_PER_SEMESTER; k++) {
				// innermost loop for the grades each semester - k is the grade id
				requestGrade(i, j, k); // request from the user to input the specific grade
				
				int *currentGradePointer = grades + (j - 1) * Constants::GRADES_PER_SEMESTER + k - 1;
				// the current grade is the previous semester number, times the grades per semester, plus the current grade number and in the end -1 because array elements start from 0
				while(*currentGradePointer < 2 || *currentGradePointer > 6) {
					// validation for the current grade failed - re-request it from the user
					cout << "The grade has to be between 2 and 6." << endl;
					requestGrade(i, j, k);
				}
			}
		}
	}
}

void StudentWithGrades::requestGrade(int courseYear, int semesterId, int gradeId) {
	// implementation for requesting a grade from STDIN
	cout << "Enter grade " << gradeId << " (year " << courseYear << ", semester " << semesterId << "): ";
	int *currentGradePointer = grades + (semesterId - 1) * Constants::GRADES_PER_SEMESTER + gradeId - 1;
	// the current grade is the previous semester number, times the grades per semester, plus the current grade number and in the end -1 because array elements start from 0
	// write the STDIN value into the correct place of the grades array
	cin >> *currentGradePointer;
}
