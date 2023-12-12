#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <limits>
#include <thread>

using namespace std;

/* Class Prototype */
class Student;
class User;

/* Function Prototype */
int command();
void Line(char ch);
void login(Student *student);
bool isValidAge(const int &age);
bool isValidID(const string &id);
void takeCourse(Student *student);
void exitProgram(Student *student);
void displayLoggedInStudentPortal();
bool isValidName(const string &name);
void loading(string message, int frameDelay = 100);
void Error(string errorMessage = "Invalid Command");
void createStudent(string &name, int &age, string &id);
void displayPortal(string name, string id, Student *student);

/*
 !User Class Start
*/
class User
{
protected: // Access specifier used "protected" for inheritance
    string name;
    int age;

public:
    /**
     * @brief Construct a new User:: User object
     * Constructor can be declared outside the class like this.It can also be declared inside the class.
     */
    User()
    {
        Line('+');
        cout << "User Constructor Called" << endl;
        Line('+');
    };

    /**
     * @brief Construct a new User object
     * Parameterized Constructor with member initializer list
     *
     * @param name name of the user
     * @param age  age of the user
     */
    User(string name, int age) : name(name), age(age) {}

    /**
     * @brief Destroy the User object
     */
    ~User()
    {
        Line('+');
        cout << "User Destructor Called" << endl;
        Line('+');
    }
};
/*
!User Class End
*/

/*
! Student Class Start
*/
class Student : public User // Student class inheriting User class
{
private:
    string id;
    vector<string> courses;

public:
    Student()
    {
        Line('+');
        cout << "Student Constructor Called" << endl;
        Line('+');
    };

    /**
     * @brief Construct a new Student object
     * Parameterized Constructor with member initializer list
     *
     * @param name name of the student
     * @param age  age of the student
     * @param id   id of the student
     */
    Student(const string name, int age, const string id) : User(name, age), id(id) {}

    void getStudentInfo()
    {
        cout << endl;
        Line('-');
        cout << "Student Name: " << name << endl;
        cout << "Student Age: " << age << endl;
        cout << "Student ID: " << id << endl;
        Line('-');
        cout << endl;
    }

    // Getters for private variables
    string getStudentID() { return id; }

    string getStudentName() { return name; }

    int getStudentAge() { return age; }

    /**
     * @brief           Adds a course to the student
     *
     * @param course    Course name to add to the student courses list
     */
    void addCourse(string course)
    {
        if (courses.size() < 5)
        {
            courses.push_back(course);
            Line('+');
            cout << "Success: Course Has Been Added" << endl;
            Line('+');
        }
        else
        {
            Error("Cannot Add Any More Courses (maximum 5 course can be added)");
        }
    }

    /**
     * @brief   Displays the courses of the student
     */
    void showCourses()
    {
        Line('-');

        if (courses.size() == 0)
        {
            Error("Student Doesn't Have Any Courses Yet");
        }
        else
        {
            cout << "Courses: " << endl;
            for (int i = 1; i <= courses.size(); i++)
            {
                cout << i << ". " << courses[i - 1] << endl;
            }
        }
        Line('-');
    }

    /**
     * @brief Destroy the Student object
     */
    ~Student()
    {
        Line('+');
        cout << "Student Destructor Called" << endl;
        Line('+');
    }
};
/*
! Student Class End
*/

/**
 * @brief       Main function
 */
int main()
{
    string name;
    int age;
    string id;

    createStudent(name, age, id);

    /*
     *Student Object is dynamically allocated with new
     *because i want to delete this object from memory when i exit the program
     */
    Student *student = new Student(name, age, id);
    student->getStudentInfo();

    /**
     * @brief Its not possible to print "Student info" before creating object
     *        thats why i created another object to show the constructor called message
     *        ? its because of the sample program of the assignment
     *
     */
    Student student1;

    // Running the program
    bool running = true;
    while (running)
    {
        // Displaying Student Portal
        displayPortal(name, id, student);

        // Taking command input from the user
        int commandInput = command();

        // Switching between commands
        switch (commandInput)
        {
        case 1:
            login(student);
            break;

        case 2:
            system("clear");
            break;

        case 3:
            exitProgram(student); // Passing student object address to delete this student object
            running = false;
            break;

        default:
            Error();
            break;
        }
    }

    return 0;
}

/**
 * @brief       Prints a line of the given character
 *
 * @param ch    Character to print
 */
void Line(char ch)
{
    // this string constructor creates a string of 60 characters of the given character
    string line(60, ch);
    cout << line << endl;
}

/**
 * @brief       Takes a command Input from the user
 *
 * @return      Command entered by the user
 */
int command()
{

    Line('-');
    cout << "Command: ";
    int command;
    cin >> command;
    Line('-');
    cout << endl;
    return command;
}

/**
 * @brief           Exits the program
 *
 * @param student   Student object to delete
 */
void exitProgram(Student *student)
{
    Line('#');
    cout << "Are you sure you want to exit?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    int exitCommand = command();

    if (exitCommand == 1)
    {
        Line('+');
        loading("System Shutting down in 3 Seconds... ");
        cout << endl;
        delete student;
        student = nullptr; // Deleting student object from memory
        cout << "Object Destroyed Successfully" << endl;
        Line('+');
        this_thread::sleep_for(std::chrono::seconds(4));
        exit(0);
    }
    else
    {
        Line('+');
        cout << "ShutDown Prevented" << endl;
        Line('+');
    }
}

/**
 * @brief       Checks if the name is valid
 *
 * @param name  Name to check
 * @return      True if the name is valid, false otherwise
 */
bool isValidName(const string &name)
{

    if (name.empty())
    {
        Error("Name can't be empty!");
        return false;
    }

    if (!all_of(name.begin(), name.end(), ::isalpha))
    {
        Error("Name can't contain numbers or any special characters!");
        return false;
    }

    if (name.length() > 20)
    {
        Error("Name can't be more than 20 characters!");
        return false;
    }

    if (name.length() < 3)
    {
        Error("Name can't be less than 3 characters!");
        return false;
    }

    return true;
}

/**
 * @brief       Checks if the age is valid
 *
 * @param age   Age to check
 * @return      True if the age is valid, false otherwise
 */
bool isValidAge(const int &age)
{
    if (age <= 0 || age > 150)
    {
        Error("Age must be between 1 and 150!");
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief       Checks if the ID is valid
 *
 * @param id    ID to check
 * @return      True if the ID is valid, false otherwise
 */
bool isValidID(const string &id)
{
    // regex for ID format 00-00000-0
    regex idRegex("\\d{2}-\\d{5}-\\d{1}");

    // Check if the ID matches the expected format
    if (!regex_match(id, idRegex))
    {
        Error("ID must be in the format 00-00000-0");
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief        Function to log a student in.
 *               The student is asked to enter their name and ID.
 *               If the entered credentials match the student's credentials, the student is logged in.
 *               Once logged in, the student can execute various commands until they choose to log out.
 *
 * @param student   Student object to log in to the system
 */
void login(Student *student)
{
    Line('-');
    cout << "Enter Login Info: " << endl;
    Line('-');

    string LoginName;
    string LoginId;

    cout << "Enter Student Name: ";
    if (!(cin >> LoginName))
    {
        Error("Something wrong with reading student name. Please try again.");
        return;
    }
    cout << endl;

    cout << "Enter Student ID: ";
    if (!(cin >> LoginId))
    {
        Error("Something wrong with reading student ID. Please try again.");
        return;
    }
    cout << endl;

    if (LoginName == student->getStudentName() && LoginId == student->getStudentID())
    {
        loading("Logging in... ");
        system("clear");
        Line('+');
        cout << "Login Successful" << endl;
        Line('+');
        cout << endl;

        bool loggedIn = true;

        while (loggedIn)
        {
            displayLoggedInStudentPortal();

            int loggedInCommand = command();

            switch (loggedInCommand)
            {
            case 1:
                student->getStudentInfo();
                break;
            case 2:
                student->showCourses();
                break;
            case 3:
                takeCourse(student);
                break;
            case 4:
                system("clear");
                break;
            case 5:
                loggedIn = false;
                system("clear");
                break;
            default:
                Error();
                break;
            }
        }
    }
    else
    {
        Error("Invalid Login Info");
    }
}

/**
 * @brief       Takes a valid name from the user
 *
 * @return      Valid name entered by the user
 */
string takeStudentName()
{
    string name;
    do
    {
        cout << "Enter Student Name: ";
        getline(cin, name); // getline used for take input with space in string
    } while (!isValidName(name));

    return name;
}

/**
 * @brief       Takes a valid age from the user
 *
 * @return      Valid age entered by the user
 */
int takeStudentAge()
{
    int age;
    do
    {
        cout << "Enter Student Age: ";
        cin >> age;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValidAge(age));

    return age;
}

/**
 * @brief       Takes a valid ID from the user
 *
 * @return      Valid ID entered by the user
 */
string takeStudentID()
{
    string id;
    do
    {
        cout << "Enter Student ID: ";
        cin >> id;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!isValidID(id));

    return id;
}

/**
 * @brief       Creates a new student account
 *
 * @param name  Name of the student
 * @param age   Age of the student
 * @param id    ID of the student
 */
void createStudent(string &name, int &age, string &id)
{
    Line('=');
    cout << "Create Student Account: " << endl;
    Line('=');

    name = takeStudentName();
    age = takeStudentAge();
    id = takeStudentID();

    cout << endl;
    Line('-');
    cout << "New Student Account Created Successfully" << endl;
    Line('-');
}

/**
 * @brief           Displays the student portal
 *
 * @param name      Name of the student
 * @param id        ID of the student
 * @param student   Student object
 */
void displayPortal(string name, string id, Student *student)
{
    cout << endl;
    Line('-');
    cout << "Student Portal" << endl;
    Line('-');

    cout << "1. Login" << endl;
    cout << "2. Clear Screen" << endl;
    cout << "3. Exit" << endl;
}

/**
 * @brief   Displays the logged in student portal
 */
void displayLoggedInStudentPortal()
{
    Line('-');
    cout << "Student Portal (Logged In)" << endl;
    cout << endl;
    Line('-');

    cout << "1. Display Student Info" << endl;
    cout << "2. Display Courses" << endl;
    cout << "3. Add Courses" << endl;
    cout << "4. Clear Screen" << endl;
    cout << "5. Logout" << endl;
}

/**
 * @brief       Takes a course name from the user
 *
 * @return      Course name entered by the user
 */

void takeCourse(Student *student)
{
    Line('-');

    cout << "Enter Course Name: ";

    string course;

    cin.ignore(); // Ignore the newline character left in the input buffer
    getline(cin, course);

    Line('-');

    student->addCourse(course);

    cout << endl;
}

/**
 * @brief   Prints invalid command message
 */
void Error(string errorMessage)
{
    Line('#');
    cout << "Error : " << errorMessage << endl;
    Line('#');
}

/**
 * @brief               Prints loading animation
 *
 * @param totalFrames   Total frames to print
 * @param frameDelay    Delay between each frame
 */
void loading(string message, int frameDelay)
{
    const char frames[] = {'-', '\\', '|', '/'};

    for (int i = 0; i < 20; ++i)
    {
        cout << "\r" << message << " " << frames[i % sizeof(frames)] << " " << flush;
        this_thread::sleep_for(chrono::milliseconds(frameDelay));
    }
}
