// Edward Burke 
// ID: 001602259 
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;
// Class representing a person 
class Person {
	// Person's name 
	string fullname;
	// Person's address 
	string address;
	// Person's age 
	int age;
public:
	// Requests input for Person attributes 
	void readPersonInfo(ifstream* pf);
	// Displays Person attributes 
	void printPersonInfo();
	// Returns Person age 
	int personAge();
	// Returns Person name 
	string personName();
};
// Gets Person attributes from file 
void Person::readPersonInfo(ifstream* pf) {
	string temp;
	getline(*pf, fullname);
	getline(*pf, address);
	getline(*pf, temp);
	age = stoi(temp);
}
// Displays Person attributes 
void Person::printPersonInfo() {
	cout << "Name: " << fullname << "\nAddress: " << address << "\nAge: " << age << "\n";
}
// Returns Person age 
int Person::personAge() {
	return age;
}
// Returns Person name 
string Person::personName() {
	return fullname;
}
// Class for a Students, dereived from Person 
class Student : public Person {
	// Student ID 
	string ID;
	// Student major 
	string major;
	// Student GPA 
	float gpa;
public:
	// Requests input for Student attributes 
	void readStudentInfo(ifstream* sf);
	// Displays Student attributes 
	void printStudentInfo();
	// Returns Student GPA 
	float studentGPA();
};

// Requests input for Student attributes 
void Student::readStudentInfo(ifstream* sf) {
	readPersonInfo(sf);
	string temp;
	getline(*sf, ID);
	getline(*sf, major);
	getline(*sf, temp);
	gpa = stof(temp);
}
// Displays Student attributes 
void Student::printStudentInfo() {
	printPersonInfo();
	cout << "Student ID: " << ID << "\nMajor: " << major << "\nGPA: " << gpa << "\n";
}
// Returns Student GPA 
float Student::studentGPA() {
	return gpa;
}
// Class for Courses 
class Course {
	// Course ID 
	string ID;
	// Course title 
	string title;
	// Course credits 
	int credits;
public:
	Course() {
		cout << "Course Constructor:\nID? ";
		cin >> ID;
		cout << "Title? ";
		cin >> title;
		cout << "Credits? ";
		cin >> credits;
	};
	// Displays Course attributes 
	void printCourseInfo();
};
// Displays Course attributes 
void Course::printCourseInfo() {
	cout << "Course ID: " << ID << "\nTitle: " << title << "\nCredits: " << credits;
}
// Class for Course Sections, derived from Course 
class CourseSection : public Course {
	// Section size (used for roster size) 
	int sectionSize;
	// List of Students in the Course Section 
	Student* roster;
	// List of pointers to Students by name 
	Student** sortedNames;
	// List of pointers to Students by age 
	Student** sortedAges;
	// List of pointers to Students by GPA 
	Student** sortedGPAs;
public:
	// Constructor TODO MAYBE ADJUST FOR NEW LISTS?
	CourseSection(string ID, string title, int credits, int sectionSize) {
		CourseSection::sectionSize = sectionSize;
		CourseSection::roster = new Student[sectionSize];
		CourseSection::sortedNames = new Student * [sectionSize];
		CourseSection::sortedAges = new Student * [sectionSize];
		CourseSection::sortedGPAs = new Student * [sectionSize];
		// Creating an list of dummy Students to be filled in later 
		Student dummy;
		for (int i = 0; i < sectionSize; i++) {
			roster[i] = dummy;
		}
	}
	// Destructor 
	~CourseSection() {
		delete roster;
		delete sortedNames;
		delete sortedAges;
		delete sortedGPAs;
	};
	// Fill roster from file 
	void fillRosterInfo(ifstream* rf);
	// Displays attributes by name 
	void printSectionInfoByName();
	// Displays attributes by age 
	void printSectionInfoByAge();
	// Displays attributes by GPA 
	void printSectionInfoByGPA();
};
// Request input for all the Students in roster 
void CourseSection::fillRosterInfo(ifstream* infile) {
	int min = 0;
	Student* temp;
	for (int i = 0; i < sectionSize; i++) {
		roster[i].readStudentInfo(infile);
		// Adding to lists, will be sorted later 
		sortedNames[i] = &roster[i];
		sortedAges[i] = &roster[i];
		sortedGPAs[i] = &roster[i];
	}
	// Sorts by name 
	for (int i = 0; i < sectionSize - 1; i++) {
		min = i;
		for (int j = i + 1; j < sectionSize; j++) {
			if (sortedNames[j]->personName() < sortedNames[min]->personName()) {
				min = j;
			}
		}
		temp = sortedNames[i];
		sortedNames[i] = sortedNames[min];
		sortedNames[min] = temp;
	}
	// Sorts by age
	for (int i = 0; i < sectionSize - 1; i++) {
		min = i;
		for (int j = i + 1; j < sectionSize; j++) {
			if (sortedAges[j]->personAge() < sortedAges[min]->personAge()) {
				min = j;
			}
		}
		temp = sortedAges[i];
		sortedAges[i] = sortedAges[min];
		sortedAges[min] = temp;
	}
	// Sorts by GPA
	for (int i = 0; i < sectionSize - 1; i++) {
		min = i;
		for (int j = i + 1; j < sectionSize; j++) {
			if (sortedGPAs[j]->studentGPA() < sortedGPAs[min]->studentGPA()) {
				min = j;
			}
		}
		temp = sortedGPAs[i];
		sortedGPAs[i] = sortedGPAs[min];
		sortedGPAs[min] = temp;
	}
}
// Displays course attributes by name 
void CourseSection::printSectionInfoByName() {
	cout << "\nStudents by name:\n";
	for (int i = 0; i < sectionSize; i++) {
		cout << "\nStudent " << i + 1 << ":\n";
		sortedNames[i]->printStudentInfo();
	}
}
// Displays course attributes by age 
void CourseSection::printSectionInfoByAge() {
	cout << "\nStudents by age:\n";
	for (int i = 0; i < sectionSize; i++) {
		cout << "\nStudent " << i + 1 << ":\n";
		sortedAges[i]->printStudentInfo();
	}
}
// Displays course attributes by GPA 
void CourseSection::printSectionInfoByGPA() {
	cout << "\nStudents by GPA:\n";
	for (int i = 0; i < sectionSize; i++) {
		cout << "\nStudent " << i + 1 << ":\n";
		sortedGPAs[i]->printStudentInfo();
	}
}
// Test code 
int main() {
	CourseSection* example = new CourseSection("1234", "Example", 4, 10);
	ifstream inf;
	Person testPerson1;

	cout << "Read in file\n";

	// Adjust this line if text file is in a different place 
	inf.open("section01.txt");
	if (inf.fail()) {
		cerr << "Error: Could not open input file\n";
		exit(1);
	}
	inf.exceptions(ifstream::failbit | ifstream::badbit);

	cout << "\nFilling into CourseSection\n";
	example->fillRosterInfo(&inf);
	cout << "\nCalling list by names\n";
	example->printSectionInfoByName();
	cout << "\nCalling list by age\n";
	example->printSectionInfoByAge();
	cout << "\nCalling list by GPA\n";
	example->printSectionInfoByGPA();
}