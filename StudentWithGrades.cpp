#include <iostream>
#include <cmath>
#include "StudentWithGrades.h"
#include "Constants.h"

using namespace std;

StudentWithGrades::StudentWithGrades() {
	// constructor implementation
	// the superclass constructor will be called first and then this one when creating the StudentWithGrades object
	// call the method to initialize the grades field with STDIN input
	initGrades();
}

StudentWithGrades::StudentWithGrades(string studentName, int studentFacultyNumber, unsigned short studentGroupId, unsigned short studentCourseYear, int *studentGrades, int studentGradesCount): Student(studentName, studentFacultyNumber, studentGroupId, studentCourseYear) {
	// implementation of a constructor that receives the deserialized data for a student from the StudentManagement persistent storage file
	// this constructor first calls the base class (Student) constructor and then here we just need to add the pointer to the grades array
	grades = studentGrades;
	gradesCount = studentGradesCount;
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
	grades = new int[gradesCount]; // dynamic array allocation
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

double StudentWithGrades::calculateOverallAverageGrade() {
	// implementation for calculation of the overall average grade for the student
	double overallAverageGrade = 0.0;
	// calculate the overall average grade by adding together all grades and then dividing that sum by all grades count
	for(int i = 0; i < gradesCount; i++) {
		overallAverageGrade += *(grades + i);
	}
	overallAverageGrade /= gradesCount;
	return overallAverageGrade;
}

double StudentWithGrades::calculateLastSemestersAverageGrade() {
	// implementation for calculation of the last two semesters average grade;
	double lastSemestersAverageGrade = 0.0;
	// calculate the last semesters average grade by adding together all grades from those semesters and then dividing that sum by their count
	int lastSemestersGradeCount = Constants::SEMESTERS_PER_YEAR * Constants::GRADES_PER_SEMESTER;
	for(int i = 0; i < lastSemestersGradeCount; i++) {
		lastSemestersAverageGrade += *(grades + gradesCount - 1 - i);
	}
	lastSemestersAverageGrade /= lastSemestersGradeCount;
	return lastSemestersAverageGrade;
}

void StudentWithGrades::printAverageGrades() {	
	// set precision to 3 digits (one before and two after the decimal point) and print out the overall average grade and the last semesters average grade
	double overallAverageGrade = calculateOverallAverageGrade();
	double lastSemestersAverageGrade = calculateLastSemestersAverageGrade();
	overallAverageGrade = ceil(overallAverageGrade * 100.0) / 100.0; // to round up the number to two decimal places
	lastSemestersAverageGrade = ceil(lastSemestersAverageGrade * 100.0) / 100.0;
	cout << "Overall average grade: " << overallAverageGrade << endl;
	cout << "Last " << Constants::SEMESTERS_PER_YEAR << " semesters average grade: " << lastSemestersAverageGrade << endl;
}

ostream& operator << (ostream &stream, StudentWithGrades &studentWithGrades) {
	// implementation for predefining the << operator so that the data stored in StudentWithGrades can be printed out
	// first, print out the values of the fields in Student
	stream << "Name: " << studentWithGrades.getName() << endl;
	stream << "Faculty number: " << studentWithGrades.getFacultyNumber() << endl;
	stream << "Group ID: " << studentWithGrades.getGroupId() << endl;
	stream << "Course year: " << studentWithGrades.getCourseYear() << endl;
	// next, iterate over the grades array and print each grade out
	int *grades = studentWithGrades.getGrades();
	stream << "Grades: ";
	for(int i = 0; i < studentWithGrades.getGradesCount(); i++) {
		stream << *(grades + i) << ' ';
	}
	stream << endl;
}
