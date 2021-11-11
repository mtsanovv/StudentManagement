#include <sstream>
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
	while((pos = serializedStudentsCollection.find(Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER)) != string::npos) { // iterating until the delimiter is no longer available
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
    
    StudentWithGrades deserializedStudent(studentName, studentFacultyNumber, studentGroupId, studentCourseYear, studentGrades, studentGradesCount); // create a StudentWithGrades object with the deserialized data
	studentsCollection.push_back(deserializedStudent);
}

void StudentWithGradesCollection::deserializeStudentGrades(string grades, int *studentGrades) {
	// time to iterate over the serialized data - first split it by Constants::STUDENT_MANAGEMENT_FILE_STUDENTS_DELIMITER
	size_t pos = 0; // a variable that will hold the current position when iterating over the data
	string token; // a variable that will hold the data for each iteration
	int gradeIndex = 0; // iterator in order to be able to access the studentGrades array
	while((pos = grades.find(Constants::STUDENT_MANAGEMENT_GRADES_DELIMITER)) != string::npos) { // iterating until the delimiter is no longer available
		// string::npos, per the documentation: "As a return value, it is usually used to indicate no matches."
	    token = grades.substr(0, pos); // get the substring from 0 to the first occurence of the delimiter
	    stringstream strCaster; // a string stream that we'll use as a 'caster' - to type cast the string to a int
	    strCaster << token; // fill the strCaster with the content of the string - that is, a grade
	    strCaster >> *(studentGrades + gradeIndex); // put the int into the array
	    grades.erase(0, pos + 1); // delete from the data from 0 to the first occurence of the delimiter + 1, which is the length of the delimiter since it's a simple char in this case
		gradeIndex++;
	}
}
