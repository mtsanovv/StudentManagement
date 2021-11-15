#include <iostream>
#include <sstream>
#include <cmath>
#include "StudentWithGradesCollection.h"
#include "StudentManagementIO.h"
#include "StudentWithGrades.h"
#include "Constants.h"

using namespace std;

StudentWithGradesCollection::StudentWithGradesCollection() {
	// constructor implementation
	// read the data from the file that is used as persistent storage
	string serializedStudents = StudentManagementIO::readFromFile();
	// deserialize the data from the file and push the students to the studentsCollection vector
	deserializeStudentsCollection(serializedStudents);
}

void StudentWithGradesCollection::deserializeStudentsCollection(string serializedStudentsCollection) {
	if(serializedStudentsCollection.empty()) {
		// if serializedStudentsCollection is empty, nothing to deserialize
		return;
	}
	// time to iterate over the serialized data - first split it by Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER
	size_t pos = 0; // a variable that will hold the current position when iterating over the data
	string token; // a variable that will hold the data for each iteration
	while(serializedStudentsCollection.find(Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER) != string::npos) { // iterating until the delimiter is no longer available
		pos = serializedStudentsCollection.find(Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER); // assign pos to the current first occurence of the delimiter
		// string::npos, per the documentation: "As a return value, it is usually used to indicate no matches."
	    token = serializedStudentsCollection.substr(0, pos); // get the substring from 0 to the first occurence of the delimiter
	    deserializeStudentData(token); // a method that deserializes the data for each student
	    serializedStudentsCollection.erase(0, pos + Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER.length()); // delete from the data from 0 to the first occurence of the delimiter + the delimiter
	}	
}

void StudentWithGradesCollection::deserializeStudentData(string studentData) {
	string studentName; // a variable that will hold the student name
	int studentFacultyNumber; // a variable that will hold the student faculty number
	unsigned short studentGroupId; // a variable that will hold the student group ID
	unsigned short studentCourseYear; // a variable that will hold the student course year
	int *studentGrades; // a dynamic array of all student grades
	// this array does not have to be deleted as it will be passed to the respective StudentWithGrades later (and when that StudentWithGrades is supposed to be destroyed, it will delete the array)
	int studentGradesCount; // a variable that will hold the grades count in order to make use of the grades dynamic array
	
	stringstream strStream(studentData); // put the studentData into a string stream
	string token; // a token which will hold each of the student's details
	int dataIndex = 0;
	while(getline(strStream, token, '\n')) { // iterate over each line
		stringstream strCaster;
		strCaster << token;
		// push the current line data to a stringstream which we'll use as a 'caster' - to type cast the string to the required type
		switch(dataIndex) {
			case 0:
				studentName = token; // name does not have to be casted, it's a string already
				break;
			case 1:
				strCaster >> studentFacultyNumber;
				break;
			case 2:
				strCaster >> studentGroupId;
				break;
			case 3:
				strCaster >> studentCourseYear;
				break;
			case 4:
				studentGradesCount = studentCourseYear * Constants::SEMESTERS_PER_YEAR * Constants::GRADES_PER_SEMESTER; // at this point we should be able to calculate the grades count, the row with the grades should be after the one with the course year
				studentGrades = new int[studentGradesCount]; // allocate memory for the grades array
				deserializeStudentGrades(token, studentGrades); // since the grades string is complex, it has to be further deserialized and put into the array
				break;
		}
		dataIndex++;
    }
    
    StudentWithGrades *deserializedStudent = new StudentWithGrades(studentName, studentFacultyNumber, studentGroupId, studentCourseYear, studentGrades, studentGradesCount); // create a pointer to the StudentWithGrades object with the deserialized data
    // we cannot have directly a variable holding a StudentWithGrades object because it contains a dynamic array and C++ cannot know the size of dynamic arrays, thus when having a vector of StudentWithGrades objects instead of pointers to StudentWithGrades objects, it will exit with 3221226356 because it has no clue on how much memory it needs to allocate for each object
	studentsCollection.push_back(deserializedStudent);
}

void StudentWithGradesCollection::deserializeStudentGrades(string grades, int *studentGrades) {
	// time to iterate over the serialized data - first split it by Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER
	size_t pos = 0; // a variable that will hold the current position when iterating over the data
	string token; // a variable that will hold the data for each iteration
	int gradeIndex = 0; // iterator in order to be able to access the studentGrades array
	while(grades.find(Constants::STUDENT_MANAGEMENT_GRADES_DELIMITER) != string::npos) { // iterating until the delimiter is no longer available
		pos = grades.find(Constants::STUDENT_MANAGEMENT_GRADES_DELIMITER);
		// string::npos, per the documentation: "As a return value, it is usually used to indicate no matches."
	    token = grades.substr(0, pos); // get the substring from 0 to the first occurence of the delimiter
	    stringstream strCaster; // a string stream that we'll use as a 'caster' - to type cast the string to a int
	    strCaster << token; // fill the strCaster with the content of the string - that is, a grade
	    strCaster >> *(studentGrades + gradeIndex); // put the int into the array
	    grades.erase(0, pos + 1); // delete from the data from 0 to the first occurence of the delimiter + 1, which is the length of the delimiter since it's a simple char in this case
		gradeIndex++;
	}
}

string StudentWithGradesCollection::serializeStudentsCollection() {
	stringstream serializedStudentCollectionStream; // create a stream that will hold all the serialized studentsCollection data
	for(size_t i = 0; i < studentsCollection.size(); i++) { // iterate through the studentsCollection vector
		serializedStudentCollectionStream << serializeStudentData(studentsCollection[i]); // push the data for each student to the stream
	}
	return serializedStudentCollectionStream.str(); // return the contents in the stream as a string
}

string StudentWithGradesCollection::serializeStudentData(StudentWithGrades *student) {
	stringstream serializedStudentDataStream; // create a stream that will hold the serialized StudentWithGrades data
	// push each field's value on a new line in the string
	serializedStudentDataStream << student->getName() << '\n';
	serializedStudentDataStream << student->getFacultyNumber() << '\n';
	serializedStudentDataStream << student->getGroupId() << '\n';
	serializedStudentDataStream << student->getCourseYear() << '\n';
	
	// grades need a special treatment
	int *studentGrades = student->getGrades();
	int studentGradesCount = student->getGradesCount();
	
	// iterate over each grade in the array, push it to the stream and add a comma after it
	for(int i = 0; i < studentGradesCount; i++) {
		serializedStudentDataStream << *(studentGrades + i) << ',';
	}
	
	// finish off the serialized data with the delimiter
	serializedStudentDataStream << Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER;
	
	return serializedStudentDataStream.str(); // return the contents in the stream as a string
}

void StudentWithGradesCollection::persistStudentsCollection() {
	StudentManagementIO::writeToFile(serializeStudentsCollection()); // gets the serialized students collection and writes it to the file, simple as that
}

bool StudentWithGradesCollection::studentWithFacultyNumberExists(int facultyNumber) {
	// iterate through the studentsCollection vector
	for(size_t i = 0; i < studentsCollection.size(); i++) {
		if(studentsCollection[i]->getFacultyNumber() == facultyNumber) {
			// we have a match - the given faculty number is found
			return true;
		}
	}
	return false;
}

void StudentWithGradesCollection::addNewStudentToCollection() {
	StudentWithGrades *student = new StudentWithGrades(); // create a pointer to a new StudentWithGrades object
	studentsCollection.push_back(student); // push the newly created student to the studentsCollection vector
	persistStudentsCollection(); // when a new student is added, it has to be added to the persistence file as well
}

void StudentWithGradesCollection::printAverageGradesInGroup(int groupId) {
	double groupOverallAverageGrade = 0.0; // a variable that holds the overall average grade for the group
	double groupLastSemestersAverageGrade = 0.0; // a variable that holds the last 2 semesters average grade for the group
	int totalStudentsInGroup = 0; // a counter that will be incremented when students from the requested group are found
	for(size_t i = 0; i < studentsCollection.size(); i++) { // iterate over studentsCollection
		if(studentsCollection[i]->getGroupId() == groupId) {
			// we have found a student from the requested group
			// add their average grades to the respective variables and increment the totalStudentsInGroup variable
			groupOverallAverageGrade += studentsCollection[i]->calculateOverallAverageGrade();
			groupLastSemestersAverageGrade += studentsCollection[i]->calculateLastSemestersAverageGrade();
			totalStudentsInGroup++;
		}
	}
	
	if(totalStudentsInGroup == 0) {
		// we have no students from this group, so we just can let the user know there are none
		cout << "No students in group " << groupId << " found." << endl;
		return;
	}
	
	// to find the group averages, divide the sum of each type of average grades by the number of students in the group
	groupOverallAverageGrade /= totalStudentsInGroup;
	groupLastSemestersAverageGrade /= totalStudentsInGroup;
	
	// round to 2 decimal places each of the two doubles
	groupOverallAverageGrade = ceil(groupOverallAverageGrade * 100.0) / 100.0;
	groupLastSemestersAverageGrade = ceil(groupLastSemestersAverageGrade * 100.0) / 100.0;
	
	cout << "Overall average grade for group " << groupId << ": " << groupOverallAverageGrade << endl;
	cout << "Last " << Constants::SEMESTERS_PER_YEAR << " semesters average grade for group " << groupId << ": " << groupLastSemestersAverageGrade << endl;
}

void StudentWithGradesCollection::printStudentsData() {
	if(!studentsCollection.size()) {
		// if there are no students, let the user know about that fact
		cout << "There are no users currently available in StudentsManagement." << endl;
		return; // no need to continue the method execution
	}
	
	for(size_t i = 0; i < studentsCollection.size(); i++) { // iterate over studentsCollection
		StudentWithGrades *student = studentsCollection[i];
		// print out the data for each StudentWithGrades using the predefined << operator in StudentWithGrades
		cout << *student << endl;
		// print out also the average grades for each StudentWithGrades
		student->printAverageGrades();
		// print out the students delimiter for the persistence file for prettier output
		cout << Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER;
	}
}

void StudentWithGradesCollection::printStudentData(int facultyNumber) {
	for(size_t i = 0; i < studentsCollection.size(); i++) { // iterate over studentsCollection
		if(studentsCollection[i]->getFacultyNumber() == facultyNumber) {
			StudentWithGrades *student = studentsCollection[i];
			// we have found a StudentWithGrades with the requested faculty number, print their data out
			cout << *student;
			// print out also the average grades for the StudentWithGrades
			student->printAverageGrades();
			// print out the students delimiter for the persistence file for prettier output
			cout << Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER;
			return; // no need to iterate further or to continue the method execution
		}
	}
	
	// the for loop has iterated over all StudentWithGrades in studentsCollection and the method has not yet returned... this means the student with the specified faculty number has not been found
	cout << "No student with faculty number " << facultyNumber << " found." << endl;
}
