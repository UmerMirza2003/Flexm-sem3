//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//using namespace std;
//
//class Student {
//public:
//    string name;
//    string roll_num;
//    int age;
//    string contact;
//    vector<string> courses;
//    vector<bool> attendance;
//    vector<int> marks;
//
//    // Add methods here
//    void enroll(string course) {
//        courses.push_back(course);
//    }
//
//    // Method to register a course
//    void registerCourse(string course) {
//        courses.push_back(course);
//    }
//
//    // Method to withdraw a course
//    void withdraw(string course) {
//        // Find the course and remove it from the vector
//        for (int i = 0; i < courses.size(); i++) {
//            if (courses[i] == course) {
//                courses.erase(courses.begin() + i);
//                break;
//            }
//        }
//    }
//
//    // Method to mark attendance
//    void markAttendance(bool attend) {
//        attendance.push_back(attend);
//    }
//
//    // Method to assign marks
//    void assignMarks(int mark) {
//        marks.push_back(mark);
//    }
//
//
//    // Method to save student data to a file
//    void saveToFile(string filename) {
//        ofstream file(filename, ios::app); // Open file in append mode
//        if (file.is_open()) {
//            file << name << "," << roll_num << "," << age << "," << contact << "\n";
//            file.close();
//        }
//        else {
//            cout << "Unable to open file";
//        }
//    }
//
//
//
//};
//
//class Course {
//public:
//    string code;
//    string name;
//    string instructor;
//    int credits;
//    int capacity;
//    vector<Student> students;
//
//    // Add methods here
//       // Method to add a student to the course
//    void addStudent(Student student) {
//        if (students.size() < capacity) {
//            students.push_back(student);
//        }
//        else {
//            cout << "Course is full." << endl;
//        }
//    }
//
//    // Method to remove a student from the course
//    void removeStudent(string roll_num) {
//        // Find the student and remove them from the vector
//        for (int i = 0; i < students.size(); i++) {
//            if (students[i].roll_num == roll_num) {
//                students.erase(students.begin() + i);
//                break;
//            }
//        }
//    }
//
//    // Method to display students enrolled in the course
//    void displayStudents() 
//    {
//        for (const Student& student : students) 
//        {
//            cout << student.name << " (" << student.roll_num << ")" << endl;
//        }
//    }
//};
//
//class System {
//public:
//    vector<Student> students;
//    vector<Course> courses;
//    vector<string> menus;
//
//    // Add methods here
//
//    void displayMainMenu() {
//        cout << "Main Menu\n";
//        cout << "1- Enroll a student\n";
//        cout << "2- Course Registration\n";
//        cout << "3- Attendance\n";
//        cout << "4- Marks\n";
//        cout << "5- Course Withdraw\n";
//        cout << "6- Exit\n";
//        cout << "Press 1 to 6 to select an option:\n";
//    }
//
//    // Method to get the user input
//    int getUserInput() {
//        int input;
//        cin >> input;
//        return input;
//    }
//
//    // Method to validate the input
//    bool validateInput(int input) {
//        if (input < 1 || input > 6) {
//            cout << "Invalid input. Please enter a number between 1 and 6.\n";
//            return false;
//        }
//        return true;
//    }
//
//    // Method to perform the corresponding actions
//    void performAction(int input) {
//        switch (input) {
//        case 1:
//            // Enroll a student
//            break;
//        case 2:
//            // Course Registration
//            break;
//        case 3:
//            // Attendance
//            break;
//        case 4:
//            // Marks
//            break;
//        case 5:
//            // Course Withdraw
//            break;
//        case 6:
//            // Exit
//            exit(0);
//        }
//    }
//
//    // Method to save the data to file
//    void saveToFile(string filename) {
//        ofstream file(filename);
//        if (file.is_open()) {
//            // Write data to file
//            file.close();
//        }
//        else {
//            cout << "Unable to open file";
//        }
//    }
//};
//
//class FileHandler {
//public:
//    string filename;
//    string mode;
//    vector<string> data;
//
//    // Add methods here
//
//     // Method to open the file
//    fstream openFile() {
//        fstream file;
//        if (mode == "read") {
//            file.open(filename, ios::in);
//        }
//        else if (mode == "write") {
//            file.open(filename, ios::out);
//        }
//        if (!file) {
//            cout << "Unable to open file";
//        }
//        return file;
//    }
//
//    // Method to close the file
//    void closeFile(fstream& file) {
//        file.close();
//    }
//
//    // Method to read the file
//    void readFile(fstream& file) {
//        string line;
//        while (getline(file, line)) {
//            data.push_back(line);
//        }
//    }
//
//    // Method to write the file
//    void writeFile(fstream& file, vector<string>& data) {
//        for (const string& line : data) {
//            file << line << "\n";
//        }
//    }
//};
//
//class Validator {
//public:
//    string input;
//    string type;
//    vector<string> constraints;
//
//    // Add methods here
//
//    // Method to validate the input according to the type
//    bool validateType() {
//        if (type == "integer") {
//            for (char c : input) {
//                if (!isdigit(c)) {
//                    return false;
//                }
//            }
//        }
//        else if (type == "string") {
//            for (char c : input) {
//                if (!isalpha(c) && c != ' ') {
//                    return false;
//                }
//            }
//        }
//        // Add more types as needed
//        return true;
//    }
//
//    // Method to validate the input according to the constraints
//    bool validateConstraints() {
//        // Implement this based on your constraints
//        return true;
//    }
//
//    // Method to validate the input
//    bool validate() {
//        return validateType() && validateConstraints();
//    }
//};
////void printmenu()
////{
////    int x = 0;
////    while (x != 6)
////    {
////        cout << "----------FLEX----------" << endl << endl;
////        cout << "1 - Enroll a student" << endl;
////        cout << "2 - Course Registration" << endl;
////        cout << "3 - Attendance " << endl;
////        cout << "4 - Marks " << endl;
////        cout << "5 - Course Withdraw " << endl;
////        cout << "6 - Exit " << endl;
////        cin >> x;
////        cout << endl << endl;
////
////        if (x == 1)
////        {
////            int c = 0;
////            while (c != 5)
////            {
////                cout << "----------Enroll A Student----------" << endl << endl;
////                cout << "1 - Display already enrolled students" << endl;
////                cout << "2 - Add a student" << endl;
////                cout << "3 - Remove a student " << endl;
////                cout << "4 - Edit student detail " << endl;
////                cout << "5 - Back " << endl;
////                cin >> c;
////
////                if (c == 1)
////                {
////                    Displayenrolledstudents();
////                }
////                else if (c == 2)
////                {
////                    Add a student"
////                }
////                else if (c == 3)
////                {
////                    Remove a student
////                }
////                else if (c == 4)
////                {
////                    Edit student detail
////                }
////              
////            }
////   
////        }
////        else if (x == 2)
////        {
////            int a = 0;
////            while (a != 3)
////            {
////                cout << "----------Course Registration----------" << endl << endl;
////                cout << "1 - Available Courses" << endl;
////                cout << "2 - Register course" << endl;
////                cout << "3 - Back " << endl;
////
////                cin >> a;
////
////                if (a == 1)
////                {
////                    Available Courses
////                }
////                else if(a == 2)
////                {
////                    Register course
////                }
////            }
////
////        }
////        else if (x == 3)
////        {
////            int b = 0;
////            while (b != 3)
////            {
////                cout << "----------Attendance----------" << endl << endl;
////                cout << "1 - Display Attendance" << endl;
////                cout << "2 - Mark Attendance." << endl;
////                cout << "3 - Back " << endl;
////                cin >> b;
////
////                if (b == 1)
////                {
////                    Display Attendance
////                }
////                else if (b == 2)
////                {
////                    Mark Attendance.
////                }
////
////            }
////
////        }
////        else if (x == 4)
////        {
////            int d = 0;
////            while (d != 3)
////            {
////                cout << "----------Marks----------" << endl << endl;
////                cout << "1 - Display Marks" << endl;
////                cout << "2 - Assign Marks." << endl;
////                cout << "3 - Back " << endl;
////                cin >> d;
////
////                if (d == 1)
////                {
////                    Display Marks
////                }
////                else if (d == 2)
////                {
////                    Assign Marks
////                }
////
////            }
////        }
////        else if (x == 5)
////        {
////            int e = 0;
////            while (e != 3)
////            {
////                cout << "----------Course Withdraw----------" << endl << endl;
////                cout << "1 - Enrolled courses" << endl;
////                cout << "2 - Drop a course" << endl;
////                cout << "3 - Back " << endl;
////                cin >> e;
////
////                if (e == 1)
////                {
////                    Enrolled courses
////                }
////                else if (e == 2)
////                {
////                    Drop a course
////                }
////
////            }
////        }
////        else if(x!=6)
////        {
////            cout << "ENTER A VALID SELECTION" << endl;
////        }
////
////    }
////      
////}
//
//int main() {
//    // Create a Student
//    Student student;
//    student.name = "John Doe";
//    student.roll_num = "12345";
//    student.age = 20;
//    student.contact = "123-456-7890";
//
//    // Enroll the student in a course
//    student.enroll("CS101");
//
//    // Create a Course
//    Course course;
//    course.code = "CS101";
//    course.name = "Introduction to Computer Science";
//    course.instructor = "Jane Smith";
//    course.credits = 3;
//    course.capacity = 30;
//
//    // Add the student to the course
//    course.addStudent(student);
//
//    // Create a System
//    System system;
//    system.students.push_back(student);
//    system.courses.push_back(course);
//
//    // Display the main menu
//    system.displayMainMenu();
//
//    // Get user input
//    int input = system.getUserInput();
//
//    // Validate the input
//    if (system.validateInput(input)) {
//        // Perform the corresponding action
//        system.performAction(input);
//    }
//
//    // Create a FileHandler
//    FileHandler fileHandler;
//    fileHandler.filename = "data.txt";
//    fileHandler.mode = "write";
//
//    // Open the file
//    fstream file = fileHandler.openFile();
//
//    // Write data to the file
//    vector<string> data = { "John Doe,12345,20,123-456-7890" };
//    fileHandler.writeFile(file, data);
//
//    // Close the file
//    fileHandler.closeFile(file);
//
//    // Create a Validator
//    Validator validator;
//    validator.input = "12345";
//    validator.type = "integer";
//
//    // Validate the input
//    if (validator.validate()) {
//        cout << "Input is valid." << endl;
//    }
//    else {
//        cout << "Input is invalid." << endl;
//    }
//
//    return 0;
//}
//
////int main() {
////    
////    return 0;
////}
