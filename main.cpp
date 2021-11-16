#include <iostream>
#include <unistd.h>
#include "StudentWithGradesCollection.h"

using namespace std;

void printStudentManagementHeader() {
	// implementing a method that prints out on the console the StudentManagement application header
	cout << "***************************************************************" << endl;
	cout << "*                      StudentManagement                      *" << endl;
	cout << "***************************************************************" << endl;
	cout << endl;
}

void printActions() {
	// implementing a method that prints out on the console the StudentManagement the available actions for the app
	cout << "+-------------------------------------------------------------+" << endl;
	cout << "|                      Available Actions                      |" << endl;
	cout << "+-------------------------------------------------------------+" << endl;
	cout << "| Action # |                   Description                    |" << endl;
	cout << "+-------------------------------------------------------------+" << endl;
	cout << "|    0     | Exit                                             |" << endl;
	cout << "|    1     | Add a new student                                |" << endl;
	cout << "|    2     | Show all students' data                          |" << endl;
	cout << "|    3     | Show a student's data by given faculty number    |" << endl;
	cout << "|    4     | Show a given group's average grades              |" << endl;
	cout << "+-------------------------------------------------------------+" << endl;
	cout << endl;
}

void executeAction(int actionId, StudentWithGradesCollection &allStudents) {
	// method implementation that executes a specified action on a specified StudentWithGradesCollection
	// it is important to note that in order to avoid wrongful copying the object, we need an alias to it
	switch(actionId) {
		case 0:
			exit(0); // the user has chosen to quit
		case 1:
			allStudents.addNewStudentToCollection(); // the user has chosen to add a new student
			break;
		case 2:
			allStudents.printStudentsData(); // the user has chosen to print all students'data
			break;
		case 3:
			// the user has chosen to print a student's data by given faculty number
			cout << "Enter a student's faculty number: ";
			int facultyNumber;
			cin >> facultyNumber;
			allStudents.printStudentData(facultyNumber);
			break;
		case 4:
			// the user has chosen to print a group's average grades by a given group ID
			cout << "Enter a group: ";
			int groupId;
			cin >> groupId;
			allStudents.printAverageGradesInGroup(groupId);
			break;
	}
	cout << endl << "---------------        Action complete.         ---------------" << endl << endl; // finish off by letting the user know that the action execution has finished
	sleep (2); // sleep for 2 seconds so that the user can see the result of the action
}

int main(int argc, char *argv[]) {
	StudentWithGradesCollection allStudents; // create a StudentWithGradesCollection object which we'll use later
	// also this object creation will deserialize and load all students from the persistence file into the collection
	printStudentManagementHeader(); // print the app header
	int actionChosen; // a variable that will be used to hold the action chosen by the user
	while(true) { // the application is basically active forever - until the user closes it or picks option 0
		printActions(); // print the list of actions
		cout << "Choose an action (0-4): ";
		cin >> actionChosen;
		if(actionChosen < 0 || actionChosen > 4) {
			// invalid action, print out the error message and continue to the next iteration
			cout << "Invalid action number." << endl << endl;
			continue;
		}
		cout << endl;
		executeAction(actionChosen, allStudents); // pass apart from the chosen action ID, the StudentWithGradesCollection because all actions have to be executed on the collection
	}
	return 0;
}
