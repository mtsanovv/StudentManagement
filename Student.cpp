#include <iostream>
#include "Student.h" // include Student class header file with class declarations in order to implement them in this file
#include "StudentWithGradesCollection.h"  // include the StudentWithGradesCollection in order to be able to verify if a Student with a given faculty number already exists

using namespace std;

Student::Student() {
	// constructor implementation
	// the aim is to initialize all class fields using STDIN values, so call the methods that initialize the fields
	initName();
	initFacultyNumber();
	initGroupId();
	initCourseYear();
}

Student::Student(string studentName, int studentFacultyNumber, unsigned short studentGroupId, unsigned short studentCourseYear) {
	// constructor that sets the class fields with the data that has been deserialized from the StudentManagement persistent storage file
	name = studentName;
	facultyNumber = studentFacultyNumber;
	groupId = studentGroupId;
	courseYear = studentCourseYear;
}

string Student::getName() 
{
	// accessor implementation for the name field
	return name;
}

int Student::getFacultyNumber() {
	// accessor implementation for the facultyNumber field
	return facultyNumber;
}

unsigned short Student::getGroupId() {
	// accessor implementation for the groupId field
	return groupId;
}

unsigned short Student::getCourseYear() {
	// accessor implementation for the courseYear field
	return courseYear;
}

void Student::initName() {
	// implementation for initialization of the name field
	cout << "Enter student's name: ";
	// initialize the name field's value with STDIN input
	getline(cin, name); // cin >> name would fail if there are whitespaces in the name, so use getline
}

void Student::initFacultyNumber() {
	// implementation for initialization of the facultyNumber field
	// request first STDIN input for facultyNumber and then validate it
	requestFacultyNumber();
	
	StudentWithGradesCollection allStudents;
	while(allStudents.studentWithFacultyNumberExists(facultyNumber)) {
		// a student with this faculty number exists, re-request from the user to enter the faculty number
		cout << "The student with faculty number " << facultyNumber << " already exists." << endl;
		requestFacultyNumber();
	}
}

void Student::requestFacultyNumber() {
	// this method is required because initFacultyNumber needs to validate the user's input
	cout << "Enter student's faculty number: ";
	// initialize the facultyNumber field's value with STDIN input
	cin >> facultyNumber;
}

void Student::initGroupId() {
	// implementation for initialization of the groupId field
	cout << "Enter student's group: ";
	// initialize the groupId field's value with STDIN input
	cin >> groupId;
}

void Student::initCourseYear() {
	// implementation for initialization of the courseYear field
	// request first STDIN input and then validate it
	requestCourseYear();
	
	while(courseYear < 1 || courseYear > 6) {
		// validation failed, re-request course year value
		cout << "The course year has to be between 1 and 6." << endl;
		requestCourseYear();
	}
}

void Student::requestCourseYear() {
	// this method is required because initCourseYear needs to validate the user's input
	cout << "Enter student's course year: ";
	// initialize the courseYear field's value with STDIN input
	cin >> courseYear;
}
