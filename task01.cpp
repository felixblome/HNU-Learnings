#include <iostream>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

// Initializing the amount of lecturers and courses as constants
const int TOTAL_COURSES = 3;
const int TOTAL_LECTURERS = 3;
const int MIN_STUDENTS = 3;
const int MAX_STUDENTS = 10;

// Prototypes of functions
void EnrollInCourse();
void ShowStartMenu();
void ShowCoursesToEnroll();
bool emailIsUnique(string, string);

string comparedEmail;

// Variables in class "Person" are public they need to be accessed
class Person
{
    public:

        string firstname;
        string surname;
        string email;

        Person(string surname, string firstname, string email)
        : surname(surname), firstname(firstname), email(email) {}

        string GetFirstName()
        {
            return firstname;
        }

        string GetSurname()
        {
            return surname;
        }

        string GetEmail()
        {
            return email;
        }
};

// Class "Lecturer" inherits from class "Person" and additionally has an academic title which is shown in front of their name
class Lecturer : public Person
{
    private:
        string acadamicTitle;

    public:
        Lecturer(string surname, string firstname, string email, string acadamicTitle)
        : Person(surname, firstname, email), acadamicTitle(acadamicTitle){}

        string GetAcademicTitle()
        {
            return acadamicTitle;
        }

        string GetFullName()
        {
            return firstname + " " + surname;
        }
};

// Class "Student" inherits from class "Person" and has additionally the properties "university" and "matriculationNumber"
class Student : public Person
{
    private:
        string university;
        int matriculationNumber;

    public:
        Student()
        : Person("", "", ""), university(""), matriculationNumber(0)
        {
            cin.ignore();
            cout << "Please enter your first name: ";
            getline(cin, firstname);

            cout << "Please enter your surname: ";
            getline(cin, surname);

            cout << "Please enter your email: ";
            getline(cin, email);

            if(!emailIsUnique(email, comparedEmail))
            {
                system("cls");
                cout << "EMAIL IS NOT UNIQUE!" << endl << endl;
                ShowCoursesToEnroll();
            }

            cout << "Please enter your university: ";
            getline(cin, university);

            cout << "Please enter your matriculation number: ";
            cin >> matriculationNumber;
        }

        string GetUniversity()
        {
            return university;
        }

        string GetFullName()
        {
            return firstname + " " + surname;
        }

        int GetMatriculationNumber()
        {
            return matriculationNumber;
        }
};

// Every course has a name and lecturer, as well as a list of students
// If there is space for a new student, create a new object of type "Student" and prompt the user for according input in "RegisterStudent"
class Course
{
    private:
        string courseName;
        Lecturer lecturer;
        int registeredStudents;

    public:
        Course(string courseName, Lecturer lecturer)
        : courseName(courseName), lecturer(lecturer) {}

        list<Student> students;

        string GetCourseName()
        {
            return courseName;
        }

        int GetRegisteredStudents()
        {
            return registeredStudents;
        }

        Lecturer GetCourseLecturer()
        {
            return lecturer;
        }

        void RegisterStudent()
        {
            if(registeredStudents < MAX_STUDENTS)
            {
                Student newStudent;
                students.push_back(newStudent);
                registeredStudents++;
            }
            else
            {
                cout << "Reached maximum amount of students!";
            }
        }
};

// Initializing the lecturers and courses as array
Lecturer lecturers[TOTAL_LECTURERS] =
{
    Lecturer("Mustermann", "Max", "maxmustermann@cplusplus.com", "Prof. Dr."),
    Lecturer("Yard", "Bill", "billyard@cplusplus.com", "Dr."),
    Lecturer("Bonn", "Lisa", "lisabonn@cplusplus.com", "Prof.")
};

Course courses[TOTAL_COURSES] =
{
    Course("Programming", lecturers[0]),
    Course("Databases", lecturers[1]),
    Course("Software Engineering", lecturers[2])
};

// Show all lecturers and their according courses
// Then call "EnrollInCourse" to handle the registration
void ShowCoursesToEnroll()
{
    cout << "Choose a course to enroll: " << endl << endl;
    for (int i = 0; i < TOTAL_COURSES; i++)
    {
        cout << "[" + to_string(i + 1) + "] " << courses[i].GetCourseName() + " with " + courses[i].GetCourseLecturer().GetFullName() << endl << endl;
    }
    cout << "[0] Return to Main Menu" << endl << endl;
    EnrollInCourse();
}

// Iterate through all courses and check if there are less students than MAX_STUDENTS allows
// If yes, display the according information in the console
void ShowNotFullyBookedCourses()
{
    for(int i = 0; i < TOTAL_COURSES; i++)
    {
        if(courses[i].GetRegisteredStudents() < MAX_STUDENTS)
        {
            cout << courses[i].GetCourseName() + " is not fully booked!" << endl;
            cout << "There are still " + to_string(MAX_STUDENTS - courses[i].GetRegisteredStudents()) + " free places available."<< endl;
            cout << "Lecturer of this course is: " + courses[i].GetCourseLecturer().GetAcademicTitle() + " " + courses[i].GetCourseLecturer().GetFullName() << endl << endl;
        }
    }

    cout << "[0] Return to Main Menu" << endl;

    int userInput;
    cin >> userInput;

    switch(userInput)
    {
        case 0:
            system("cls");
            ShowStartMenu();
            break;

        default:
            break;
    }
}

// take two strings as parameter and compare the entered email with every email registered
// if there is no student or the new email is unique, everything is fine
// if there is a duplicate, the user has to re-enter their data
bool emailIsUnique(string newMail, string comparedEmail)
{
    for(int i = 0; i < TOTAL_COURSES; i++)
    {
        if(!courses[i].students.empty())
        {
            for(Student& student : courses[i].students)
            {
                comparedEmail = student.GetEmail();
                if(comparedEmail != newMail)
                    return true;
                else
                    return false;
            }
        }
        else
            return true;
    }
}

// Iterate through each course and its students, then print their information if at least 1 student is enrolled
// Check if course has more than 3 participants
void ShowCourseParticipants()
{
    cout << "[1] Show Programming Students" << endl << endl;
    cout << "[2] Show Databases Students" << endl << endl;
    cout << "[3] Show Software Engineering Students" << endl << endl;
    cout << "[4] Show Students of All Courses" << endl << endl;
    cout << "[0] Return to Main Menu" << endl << endl;

    int returnInput;
    int userInput;
    cin >> userInput;

    switch(userInput)
    {
        case 1:
            system ("cls");
            cout << "Course: " + courses[0].GetCourseName() << endl << endl;
            if(courses[0].GetRegisteredStudents() > 0)
            {
                for(Student& student : courses[0].students)
                {
                    cout << "Name: " << student.GetFullName() << endl;
                    cout << "Email: " << student.GetEmail() << endl;
                    cout << "University: " << student.GetUniversity() << endl;
                    cout << "Matriculation Number: " << to_string(student.GetMatriculationNumber()) << endl << endl;
                }
            }
            else if(courses[0].GetRegisteredStudents() < MIN_STUDENTS)
            {
                cout << "Course will NOT take place!" << endl;
            }
            cout << endl << "Press [0] to Return" << endl;
            cin >> returnInput;
            if(returnInput == 0)
            {
                system("cls");
                ShowCourseParticipants();
            }
            break;

        case 2:
            system ("cls");
            cout << "Course: " + courses[1].GetCourseName() << endl << endl;
            if(courses[1].GetRegisteredStudents() > 0)
            {
                for(Student& student : courses[1].students)
                {
                    cout << "Name: " << student.GetFullName() << endl;
                    cout << "Email: " << student.GetEmail() << endl;
                    cout << "University: " << student.GetUniversity() << endl;
                    cout << "Matriculation Number: " << to_string(student.GetMatriculationNumber()) << endl << endl;
                }
            }
            else if(courses[1].GetRegisteredStudents() < MIN_STUDENTS)
            {
                cout << "Course will NOT take place!" << endl;
            }
            cout << endl << "Press [0] to Return" << endl;
            cin >> returnInput;
            if(returnInput == 0)
            {
                system("cls");
                ShowCourseParticipants();
            }
            break;

        case 3:
            system ("cls");
            cout << "Course: " + courses[2].GetCourseName() << endl << endl;
            if(courses[2].GetRegisteredStudents() > 0)
            {
                for(Student& student : courses[2].students)
                {
                    cout << "Name: " << student.GetFullName() << endl;
                    cout << "Email: " << student.GetEmail() << endl;
                    cout << "University: " << student.GetUniversity() << endl;
                    cout << "Matriculation Number: " << to_string(student.GetMatriculationNumber()) << endl << endl;
                }
            }
            else if(courses[2].GetRegisteredStudents() < MIN_STUDENTS)
            {
                cout << "Course will NOT take place!" << endl;
            }
            cout << endl << "Press [0] to Return" << endl;
            cin >> returnInput;
            if(returnInput == 0)
            {
                system("cls");
                ShowCourseParticipants();
            }
            break;

        case 4:
            system ("cls");
            cout << "All Courses Combined: " << endl << endl;
            for(int i = 0; i < TOTAL_COURSES; i++)
            {
                if(courses[i].GetRegisteredStudents() > 0)
                {
                    for(Student& student : courses[i].students)
                    {
                        cout << "Name: " << student.GetFullName() << endl;
                        cout << "Email: " << student.GetEmail() << endl;
                        cout << "University: " << student.GetUniversity() << endl;
                        cout << "Matriculation Number: " << to_string(student.GetMatriculationNumber()) << endl << endl;
                    }
                }
                else if(courses[i].GetRegisteredStudents() < MIN_STUDENTS)
                {
                    cout << "Course " + courses[i].GetCourseName() + " will NOT take place!"<< endl;
                }
            }
            cout << endl << "Press [0] to Return" << endl;
            cin >> returnInput;
            if(returnInput == 0)
            {
                system("cls");
                ShowCourseParticipants();
            }
            break;

        case 0:
            system("cls");
            ShowStartMenu();
            break;
    }
}

// Take the user input and register a new student with the according function from the class "Course"
void EnrollInCourse()
{
    int userInput;
    cin >> userInput;

     switch(userInput)
    {
        case 0:
            system("cls");
            ShowStartMenu();
            break;
        case 1:
            courses[0].RegisterStudent();
            break;

        case 2:
            courses[1].RegisterStudent();
            break;

        case 3:
            courses[2].RegisterStudent();
            break;
    }
    system("cls");
    ShowStartMenu();
};

void NotifyStudents()
{
    cout << "These students must be notified because their course does not take place: " << endl << endl;
    for(int i = 0; i < TOTAL_COURSES; i++)
    {
        for(Student& student : courses[i].students)
        {
            if(courses[i].GetRegisteredStudents() < MIN_STUDENTS)
            {
                cout << student.GetFullName() + " " + student.GetEmail() << endl;
            }
        }
    }
}

// Check the user input and display the according option in the console
void ShowStartMenu()
{
    cout << endl << "Please choose an option by entering a number" << endl << endl;
    cout << "[1] Register for a course" << endl << endl;
    cout << "[2] Show course participants" << endl << endl;
    cout << "[3] Show free courses" << endl << endl;
    cout << "[0] Quit Program" << endl << endl;

    int userInput;
    cin >> userInput;

    switch(userInput)
    {
        case 1:
            system("cls");
            ShowCoursesToEnroll();
            break;

        case 2:
            system("cls");
            ShowCourseParticipants();
            break;

        case 3:
            system("cls");
            ShowNotFullyBookedCourses();
            break;

        case 0:
            system("cls");
            NotifyStudents();
            break;
    }
}

int main()
{
    system("pause");
    ShowStartMenu();
    return 0;
}
