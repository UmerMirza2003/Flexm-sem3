#include<iostream>
#include <vector>
#include<fstream>
#include<string>
#include<sstream>
#include <variant>
using namespace std;

int StudentS = 0;
int CourseS = 0;
int TotalCreditHours = 17;



class Courses;      // Forward declaration
class FileHandler;  // Forward declaration
class Student;      // Forward declaration
class System;       // Forward declaration


class Courses
{
public:
    string code;
    string name;
    string instructor;
    int credits;
    int capacity;
    int numofstudents;
    Student* RegisteredStudents;



    Courses() : code(""), name(""), instructor(""), credits(0), capacity(10), numofstudents(0), RegisteredStudents(0) {}
    Courses(string c, string n, string i, int cr, int cap = 10) : code(c), name(n), instructor(i), credits(cr), capacity(cap), numofstudents(0), RegisteredStudents(0) {}
};



class Student
{
public:
    string RollNo;
    string Name;
    string Contact;
    int Age;
    Courses* RegisteredCourses;
    int TotalCredits;
    int TotalCourses;

    int* attendance;
    int* marks;




public:
    Student() : RollNo(""), Name(""), Contact(""), Age(0), RegisteredCourses(0), TotalCredits(0), TotalCourses(0), marks(0), attendance(0) {}
    Student(string r, string n, string c, int a) : RollNo(r), Name(n), Contact(c), Age(a), RegisteredCourses(0), TotalCredits(0), TotalCourses(0), marks(0), attendance(0) {}

    bool AddCourse(string c, string n, string i, int cr)
    {
        if (TotalCredits + cr > TotalCreditHours)
        {
            cout << "Cannot register Course Credit Hour Limit exceeds." << endl;
            return 0;
        }


        if (TotalCourses > 0)
        {
            bool found = 0;
            for (int i = 0; i < TotalCourses; i++)
            {
                if (RegisteredCourses[i].code == c)
                {
                    found = 1;
                    cout << " Already Registered" << endl;
                }
            }
            if (found == 1)
            {
                return 0;
            }
        }

        TotalCourses++;
        TotalCredits = TotalCredits + cr;

        Courses* newRegisteredCourses = new Courses[TotalCourses];
        int* newAttendance = new int[TotalCourses];
        int* newMarks = new int[TotalCourses];
        for (int i = 0; i < (TotalCourses - 1); i++)
        {
            newRegisteredCourses[i] = RegisteredCourses[i];
            newAttendance[i] = attendance[i];
            newMarks[i] = marks[i];
        }
        Courses* newCourses = new Courses(c, n, i, cr);
        newRegisteredCourses[TotalCourses - 1] = *newCourses;
        cout << "Enter attendance: ";
        int att;
        cin >> att;
        cout << "Enter marks: ";
        int mar;
        cin >> mar;
        newAttendance[TotalCourses - 1] = att;
        newMarks[TotalCourses - 1] = mar;

        RegisteredCourses = newRegisteredCourses;
        attendance = newAttendance;
        marks = newMarks;


        return 1;
    }
};



class FileHandler
{
public:
    static void WriteSizeintoFile(int s)
    {
        ofstream file("SizeStudent.txt", ios::out);  //out means entire file is cleared 
        if (file.is_open())
        {
            file << s;      // now new data is inputed
            file.close();
        }
        else
            cout << "File \"SizeStudent.txt\" NOT opened" << endl;
    }

    static void WriteStudentToFile(string r, string n, string c, int a, int sizeC, Courses* courses, int cr, int* att, int* mar)
    {
        ofstream file("Student.txt", ios::app);
        if (file.is_open())
        {
            // file << "\n";
            file << r;
            file << "|";
            file << n;
            file << "|";
            file << c;
            file << "|";
            file << a;
            file << " ";
            file << cr;
            file << " ";
            file << sizeC;
            file << " ";
            for (int i = 0; i < sizeC; i++)
            {
                file << courses[i].code << " " << att[i] << " " << mar[i] << " ";
            }
            file << "\n";

            file.close();
        }
        else
            cout << "File \"Student.txt\" NOT opened" << endl;
    }

    // fills the students s array reading data from file and putting it into the array 
    static void ReadStudentFromFile(Student*& Students)
    {
        ifstream file1("SizeStudent.txt");
        if (file1.is_open())
        {
            file1 >> StudentS;  // putting value from file into StudentS 
            file1.close();
        }
        else
            cout << "File \"SizeStudent.txt\" NOT opened" << endl;

        ifstream file2("Student.txt");
        if (file2.is_open())
        {
            Students = new Student[StudentS];
            for (int i = 0; i < StudentS; i++)
            {
                string line;
                getline(file2, line);
                stringstream ss(line);
                string r;
                string n;
                string c;
                int a = 0;
                int sizeC = 0;
                int TotalC = 0;
                getline(ss, r, '|');
                getline(ss, n, '|');
                getline(ss, c, '|');
                ss >> a;
                ss >> TotalC;
                ss >> sizeC;
                Students[i].RegisteredCourses = new Courses[sizeC];

                string* tempcode = new string[sizeC];
                string* tempname = new string[sizeC];
                string* tempinst = new string[sizeC];
                string* tempatt = new string[sizeC];
                string* tempmar = new string[sizeC];

                for (int j = 0; j < sizeC; j++)
                {
                    string code;
                    string att;
                    string mar;
                    ss >> code;
                    ss >> att;
                    ss >> mar;
                    tempcode[j] = code;
                    tempatt[j] = att;
                    tempmar[j] = mar;
                }


                Student* newStudent = new Student(r, n, c, a);
                Students[i] = *newStudent;
                Students[i].RegisteredCourses = new Courses[sizeC];
                Students[i].attendance = new int[sizeC];
                Students[i].marks = new int[sizeC];
                for (int j = 0; j < sizeC; j++)
                {
                    Students[i].RegisteredCourses[j].code = tempcode[j];
                    Students[i].attendance[j] = stoi(tempatt[j]);
                    Students[i].marks[j] = stoi(tempmar[j]);
                }

                Students[i].TotalCourses = sizeC;
                Students[i].TotalCredits = TotalC;
            }
            file2.close();
        }
        else
            cout << "File \"SizeStudent.txt\" NOT opened" << endl;
    }

    ////////////////////////////////////////////////////////////////////
    static void WriteStudentToCourse(string r, string course)
    {
        string txt = ".txt";
        string temp = course + txt;
        ofstream file(temp, ios::app);
        if (file.is_open())
        {
            // file << "\n";
            file << r << endl;
            //file << "\n";
            file.close();
        }
        else
            cout << "File \" " << course << "\" NOT opened" << endl;
    }
    /////////////////////////////////////////////////////////////////////
    static void ReadCourseFromFile(Courses*& Course)
    {
        ifstream file("Course.txt");
        if (file.is_open())
        {
            file >> CourseS;
            Course = new Courses[CourseS];
            for (int i = 0; i < CourseS; i++)
            {
                string line;
                getline(file, line);
                stringstream ss(line);
                string code;
                string name;
                string instructor;
                int credits = 0;

                getline(ss, code, '|');
                getline(ss, name, '|');
                getline(ss, instructor, '|');
                ss >> credits;

                Courses* newCourse = new Courses(code, name, instructor, credits);
                Course[i] = *newCourse;
                string temp = Course[i].name;
                temp = temp + "_s.txt";
                int size = 0;
                ifstream file1(temp);
                if (file1.is_open())
                {
                    file1 >> size;

                    file1.close();
                }
                else
                    cout << "File \"Course.txt\" NOT opened" << endl;
                Course[i].numofstudents = size;
            }
            file.close();
        }
        else
            cout << "File \"Course.txt\" NOT opened" << endl;
    }

    static void incrementsize(string coursename)
    {
        string temp = coursename;
        temp = temp + "_s.txt";
        int size = 0;

        ifstream file(temp);
        if (file.is_open())
        {
            file >> size;

            file.close();
        }
        else
            cout << "File \"Course.txt\" NOT opened" << endl;
        size = size + 1;

        ofstream file1(temp, ios::out);
        if (file1.is_open())
        {
            // file << "\n";
            file1 << size;
            //file << "\n";
            file1.close();
        }
        else
            cout << "File \" " << coursename << "\" NOT opened" << endl;

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void decrementsize(string coursename)
    {
        string temp = coursename;
        temp = temp + "_s.txt";
        int size = 0;

        ifstream file(temp);
        if (file.is_open())
        {
            file >> size;

            file.close();
        }
        else
            cout << "File \"Course.txt\" NOT opened" << endl;
        size = size - 1;

        ofstream file1(temp, ios::out);
        if (file1.is_open())
        {
            // file << "\n";
            file1 << size;
            //file << "\n";
            file1.close();
        }
        else
            cout << "File \" " << coursename << "\" NOT opened" << endl;

    }

    static void decrementcourse(string coursename, string roll) {
        string temp = coursename;
        temp = temp + "_s.txt";

        ifstream file(temp);
        int size = 0;
        if (file.is_open()) {
            file >> size;
        }
        file.close();

        string temp2 = coursename;
        temp2 = temp2 + ".txt";
        string* rollno = new string[size - 1];
        ifstream file2(temp2);
        string r;
        if (file2.is_open()) 
        {
            int j = 0;
            for (int i = 0; i < size; i++) 
            {
      
                file2 >> r;
                if (r != roll) 
                {
                    rollno[j] = r;
                    j++;
                }
            }
        }
        file2.close();

        ofstream file3(temp2, ios::out);
        if (file3.is_open()) {
            for (int i = 0; i < size - 1; i++) 
            {
                file3 << rollno[i];
                file3 << "\n";
            }
        }
    }


};





class System
{
public:
    Student* Students;
    Courses* Course;
    static int sizeS;
    static int sizeC;

    System()
    {
        Course = nullptr;
        Students = nullptr;
        FileHandler h;
        h.ReadCourseFromFile(Course);
        h.ReadStudentFromFile(Students);
        sizeS = StudentS;
        sizeC = CourseS;
    }

    void AddStudents(string r, string n, string c, int a = 0)
    {

        bool found = 0;
        for (int i = 0; i < sizeS; i++)
        {
            if (Students[i].RollNo == r)
                found = 1;
        }
        if (found)
        {
            cout << "Student Already Exists" << endl;
            return;
        }



        Student* newStudent = new Student(r, n, c, a);
        sizeS++;

        // Allocate a new dynamic array and copy existing elements
        Student* newStudentsArray = new Student[sizeS];
        for (int i = 0; i < sizeS - 1; ++i)
        {
            newStudentsArray[i] = Students[i];
        }

        // Add the new student
        newStudentsArray[sizeS - 1] = *newStudent;

        // Delete the old array and update the pointer
        delete[] Students;
        Students = newStudentsArray;

        FileHandler obj;
        obj.WriteSizeintoFile(sizeS);
        obj.WriteStudentToFile(r, n, c, a, Students->TotalCourses, Students->RegisteredCourses, Students->TotalCredits, Students->attendance, Students->marks);
        cout << "Student Successfully Added" << endl;
    }

    void RemoveStudents(string _r)
    {
        bool found = 0;
        for (int i = 0; i < sizeS; i++)
        {
            if (Students[i].RollNo == _r)
                found = 1;
        }
        if (found == 0)
        {
            cout << "Student Doesnot Exists" << endl;
            return;
        }

        sizeS--;
        // Allocate a new dynamic array and copy existing elements
        Student* newStudentsArray = new Student[sizeS];
        int z = 0;
        for (int i = 0; i < sizeS + 1; ++i)
        {
            if (Students[i].RollNo != _r)
            {
                newStudentsArray[z] = Students[i];
                z++;
            }
        }

        // Delete the old array and update the pointer
        delete[] Students;
        Students = newStudentsArray;
        FileHandler obj3;
        obj3.WriteSizeintoFile(sizeS);
        string r;  //roll no 
        string n;  // name 
        string c;  /// contact 
        int a = 0; //age
        ofstream file("Student.txt", ios::out);
        if (file.is_open())
        {
            for (int i = 0; i < sizeS; i++)
            {
                r = Students[i].RollNo;
                n = Students[i].Name;
                c = Students[i].Contact;
                a = Students[i].Age;

                obj3.WriteStudentToFile(r, n, c, a, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
            }
            file.close();
        }
        else
            cout << "File \"Student.txt\" NOT opened" << endl;

        cout << " Student Removed " << endl;
    }

    //editting student details and storing details in file 
    void EditStudentDetails()
    {
        string find;
        cout << "Student to Edit" << endl;
        cout << "Enter Roll no : ";
        cin >> find;
        int index = -1;
        for (int i = 0; i < sizeS + 1; ++i)
        {
            if (Students[i].RollNo == find)
            {
                index = i;
            }
        }
        if (index != -1)
        {
            string ro;  //roll no 
            string na;  // name 
            string co;  /// contact 
            int ag = 0; //age

            cout << "Enter NEW Roll No : ";
            cin >> ro;
            cout << "Enter NEW Name : ";
            cin >> na;
            cout << "Enter NEW Contact : ";
            cin >> co;
            cout << "Enter NEW Age : ";
            cin >> ag;

            Students[index].RollNo = ro;
            Students[index].Name = na;
            Students[index].Contact = co;
            Students[index].Age = ag;

            string check;
            cout << "Do you want to Remove Student?" << endl;
            cout << " Enter y for yes and n for no" << endl;
            cin >> check;
            while (check != "y" && check != "n")
            {
                cout << " Enter y for yes and n for no" << endl;
                cin >> check;
            }
            if (check == "y")
            {
                ofstream file("Student.txt", ios::out);
                if (file.is_open())
                {
                    for (int i = 0; i < sizeS; i++)
                    {
                        ro = Students[i].RollNo;
                        na = Students[i].Name;
                        co = Students[i].Contact;
                        ag = Students[i].Age;

                        FileHandler obj4;
                        obj4.WriteStudentToFile(ro, na, co, ag, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
                    }
                    file.close();
                }
                else
                    cout << "File \"Student.txt\" NOT opened" << endl;

                cout << "Student Details Edited." << endl;
            }
            else
            {
                cout << "Student details not  eited." << endl;
            }
           
        }
        else
        {
            cout << "Roll no Does not exists!!!" << endl;
        }

    }

    void AvailableCourses()
    {

        for (int i = 0; i < sizeC; i++)
        {
            cout << Course[i].code << " ";
            cout << Course[i].name << " " << endl;
            cout << "Credits : ";
            cout << Course[i].credits << " " << endl;
            cout << "Instructor : ";
            cout << Course[i].instructor << " " << endl;
            cout << "------------------------------------" << endl;

        }

    }

    void RegisterCourse()   //check if already present // if capacity is full  //credit hour limit
    {
        bool found = 0;
        int index = -1;
        string x;
        cout << " Enter Roll No of Student : ";
        cin >> x;

        for (int i = 0; i < sizeS; i++)
        {
            if (Students[i].RollNo == x)
            {
                found = 1;
                index = i;
            }

        }
        if (found == 0)
        {
            cout << "Student Not Found" << endl;
            return;
        }

        if (Students[index].TotalCredits == TotalCreditHours)
        {
            cout << "No courses Available Credit limit Reached." << endl;
            return;
        }

        int n = 0;
        for (int i = 0; i < sizeC; i++)
        {
            cout << i << " ";
            cout << Course[i].code << " ";
            cout << Course[i].name << " " << endl;
        }
        while (n != -1)
        {
            cout << "Enter course number  to Register : ";
            cin >> n;
            if (Course[n].numofstudents == Course[n].capacity)
            {
                cout << "Cannot register Course is Full." << endl;
            }
            else
            {
                bool t = 0;
                t = Students[index].AddCourse(Course[n].code, Course[n].name, Course[n].instructor, Course[n].credits);
                if (t == 1)
                {

                    FileHandler obj1;
                    obj1.WriteStudentToCourse(Students[index].RollNo, Course[n].name);
                    obj1.incrementsize(Course[n].name);
                    string r;
                    string name;
                    string c;
                    int a;
                    ofstream file("Student.txt", ios::out);
                    if (file.is_open())
                    {


                        for (int i = 0; i < sizeS; i++)
                        {
                            r = Students[i].RollNo;
                            name = Students[i].Name;
                            c = Students[i].Contact;
                            a = Students[i].Age;

                            FileHandler obj5;
                            obj5.WriteStudentToFile(r, name, c, a, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
                        }
                        file.close();
                    }
                    else
                        cout << "File \"Student.txt\" NOT opened" << endl;

                    cout << "Student added." << endl;
                }

            }

            cout << "Enter -1 to exist." << endl;
            cin >> n;
        }
        return;
    }


    //function for displaying all enrolled  students
    void DisplayAllStudents()
    {
        for (int i = 0; i < System::sizeS; ++i)
        {
            cout << "Student " << i + 1 << ":" << endl;
            cout << "Roll No: " << Students[i].RollNo << endl;
            cout << "Name: " << Students[i].Name << endl;
            cout << "Contact: " << Students[i].Contact << endl;
            cout << "Age: " << Students[i].Age << endl;
            cout << "Registered Courses: " << endl;
            for (int j = 0; j < Students[i].TotalCourses; j++)
            {
                cout << Students[i].RegisteredCourses[j].code << " ";
            }
            cout << endl;
            cout << "--------------------------" << endl;
        }
    }

    void DisplayAttendance() {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout << Students[index].RegisteredCourses[i].code << " Attendance: " << Students[index].attendance[i] << endl;
            }
        }
    }
    void MarkAttendance()
    {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout<< i <<") " << Students[index].RegisteredCourses[i].code << " Attendance: " << Students[index].attendance[i] << endl;
            }
        }

        cout << "Enter Course index to Mark Attendance : ";
        int corc;
        cin >> corc;
        cout << "Enter Attendance : ";
        int newatt;
        cin >> newatt;
        Students[index].attendance[corc] = newatt;

        ofstream file("Student.txt", ios::out);
        if (file.is_open())
        {
            for (int i = 0; i < sizeS; i++)
            {
                FileHandler::WriteStudentToFile(Students[i].RollNo, Students[i].Name, Students[i].Contact, Students[i].Age, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
            }

            file.close();
        }
        else
        {
            cout << "File \"Student.txt\" NOT opened" << endl;
        }
    }


    void AssignMarks()
    {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout << i << ") " << Students[index].RegisteredCourses[i].code << " Marks: " << Students[index].marks[i] << endl;
            }
        }

        cout << "Enter Course index to Assign Marks : ";
        int corc;
        cin >> corc;
        cout << "Enter Marks : ";
        int newatt;
        cin >> newatt;
        Students[index].marks[corc] = newatt;

        ofstream file("Student.txt", ios::out);
        if (file.is_open())
        {
            for (int i = 0; i < sizeS; i++)
            {
                FileHandler::WriteStudentToFile(Students[i].RollNo, Students[i].Name, Students[i].Contact, Students[i].Age, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
            }

            file.close();
        }
        else
        {
            cout << "File \"Student.txt\" NOT opened" << endl;
        }
    }

    void DisplayMarks() {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout << Students[index].RegisteredCourses[i].code << " Marks: " << Students[index].marks[i] << endl;
            }
        }
    }

    void DisplayCourses() {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout << Students[index].RegisteredCourses[i].code << endl;
            }
        }
    }

    void WithdrawCourse() {
        cout << "Enter Student Roll No: ";
        string roll;
        cin >> roll;
        int index = 0;
        bool found = false;
        for (int i = 0; i < sizeS; i++) {
            if (Students[i].RollNo == roll) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) {
            cout << "Student does not exist\n";
        }
        else {
            for (int i = 0; i < Students[index].TotalCourses; i++) {
                cout << Students[index].RegisteredCourses[i].code << endl;
            }
            cout << "Enter course code to withdraw: ";
            string code;
            cin >> code;

            Courses* newCourses = new Courses[Students[index].TotalCourses - 1];
            int* newAtt = new int[Students[index].TotalCourses - 1];
            int* newMar = new int[Students[index].TotalCourses - 1];
            int cr = 0;
            int courseIndex;
            int j = 0;
            for (int i = 0; i < Students[index].TotalCourses; i++) 
            {
                if (Students[index].RegisteredCourses[i].code != code) 
                {
                    newCourses[j] = Students[index].RegisteredCourses[i];
                    newAtt[j] = Students[index].attendance[i];
                    newMar[j] = Students[index].marks[i];
                    j++;
                }
                else 
                {
                    if (code == "CS1004")
                    {
                        cr = 4;
                    }
                    else if (code == "CS1005")
                    {
                        cr = 3;
                    }
                    else if (code == "EE2003")
                    {
                        cr = 4;
                    }
                    else if (code == "MT1004")
                    {
                        cr = 3;
                    }
                    else if (code == "SS2040")
                    {
                        cr = 3;
                    }
                    else if (code == "SS0410")
                    {
                        cr = 3;
                    }

                    //cr = Students[index].RegisteredCourses[i].credits;
                    courseIndex = i;
                }
            }
            //delete[] Students[index].RegisteredCourses;
            //delete[] Students[index].attendance;
            //delete[] Students[index].marks;

            Students[index].RegisteredCourses = newCourses;
            Students[index].attendance = newAtt;
            Students[index].marks = newMar;
            Students[index].TotalCourses--;
            Students[index].TotalCredits = Students[index].TotalCredits - cr;


            ofstream file("Student.txt", ios::out);
            if (file.is_open())
            {
                for (int i = 0; i < sizeS; i++)
                {
                    FileHandler::WriteStudentToFile(Students[i].RollNo, Students[i].Name, Students[i].Contact, Students[i].Age, Students[i].TotalCourses, Students[i].RegisteredCourses, Students[i].TotalCredits, Students[i].attendance, Students[i].marks);
                }

                file.close();
            }
            else
            {
                cout << "File \"Student.txt\" NOT opened" << endl;
            }
                
            


            if (code == "CS1004") {
                FileHandler::decrementcourse("OOP", roll);
                FileHandler::decrementsize("OOP");
            }
            else if (code == "CS1005") {
                FileHandler::decrementcourse("DS", roll);
                FileHandler::decrementsize("DS");
            }
            else if (code == "EE2003") {
                FileHandler::decrementcourse("COAL", roll);
                FileHandler::decrementsize("COAL");
            }
            else if (code == "MT1004") {
                FileHandler::decrementcourse("LA", roll);
                FileHandler::decrementsize("LA");
            }
            else if (code == "SS2040") {
                FileHandler::decrementcourse("Mass_Com", roll);
                FileHandler::decrementsize("Mass_Com");
            }
            else if (code == "SS0410") {
                FileHandler::decrementcourse("IR", roll);
                FileHandler::decrementsize("IR");
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    void printmenu()
    {
        int x = 0;
        while (x != 6)
        {
            cout << "----------FLEX----------" << endl << endl;
            cout << "1 - Enroll a student" << endl;
            cout << "2 - Course Registration" << endl;
            cout << "3 - Attendance " << endl;
            cout << "4 - Marks " << endl;
            cout << "5 - Course Withdraw " << endl;
            cout << "6 - Exit " << endl;
            cin >> x;
            cout << endl << endl;

            if (x == 1)
            {
                int c = 0;
                while (c != 5)
                {
                    cout << "----------Enroll A Student----------" << endl << endl;
                    cout << "1 - Display already enrolled students" << endl;
                    cout << "2 - Add a student" << endl;
                    cout << "3 - Remove a student " << endl;
                    cout << "4 - Edit student detail " << endl;
                    cout << "5 - Back " << endl;
                    cin >> c;

                    if (c == 1)
                    {
                        DisplayAllStudents();
                    }
                    else if (c == 2)
                    {
                        string r;
                        string n;
                        string c;
                        int a;
                        cout << "Enter roll number e.g(22L-6793) :";
                        cin >> r;
                        cout << "Enter name e.g(Umer Mirza) :";
                        cin >> n;
                        cout << "Enter contact number e.g(03xx-1234567) :";
                        cin >> c;
                        cout << "Enter age e.g(18) :";
                        cin >> a;
                        string check;
                        cout << "Do you want to Add Student?" << endl;
                        cout << " Enter y for yes and n for no" << endl;
                        cin >> check;
                        while (check != "y" && check != "n")
                        {
                            cout << " Enter y for yes and n for no" << endl;
                            cin >> check;
                        }
                        if (check == "y")
                        {
                            AddStudents(r, n, c, a);
                        }
                        else
                        {
                            cout << "Student not Added." << endl;
                        } 
                    }
                    else if (c == 3)
                    {
                        string r;
                        cout << "Enter roll-no of student to remove : ";
                        cin >> r;
                        string check;
                        cout << "Do you want to Remove Student?" << endl;
                        cout << " Enter y for yes and n for no" << endl;
                        cin >> check;
                        while (check != "y" && check != "n")
                        {
                            cout << " Enter y for yes and n for no" << endl;
                            cin >> check;
                        }
                        if (check == "y")
                        {
                            RemoveStudents(r);
                        }
                        else
                        {
                            cout << "Student not Removed." << endl;
                        }

                        
                    }
                    else if (c == 4)
                    {
                        string r;
                        cout << "Enter roll-no of student to edit : ";
                        cin >> r;

                        EditStudentDetails();

                    }
              
                }
  
            }
            else if (x == 2)
            {
                int a = 0;
                while (a != 3)
                {
                    cout << "----------Course Registration----------" << endl << endl;
                    cout << "1 - Available Courses" << endl;
                    cout << "2 - Register course" << endl;
                    cout << "3 - Back " << endl;

                    cin >> a;

                    if (a == 1)
                    {
                        AvailableCourses();
                    }
                    else if(a == 2)
                    {
                        RegisterCourse();
                    }
                }

            }
            else if (x == 3)
            {
                int b = 0;
                while (b != 3)
                {
                    cout << "----------Attendance----------" << endl << endl;
                    cout << "1 - Display Attendance" << endl;
                    cout << "2 - Mark Attendance." << endl;
                    cout << "3 - Back " << endl;
                    cin >> b;

                    if (b == 1)
                    {
                        DisplayAttendance();
                    }
                    else if (b == 2)
                    {
                        MarkAttendance();
                    }

                }

            }
            else if (x == 4)
            {
                int d = 0;
                while (d != 3)
                {
                    cout << "----------Marks----------" << endl << endl;
                    cout << "1 - Display Marks" << endl;
                    cout << "2 - Assign Marks." << endl;
                    cout << "3 - Back " << endl;
                    cin >> d;

                    if (d == 1)
                    {
                        DisplayMarks();
                    }
                    else if (d == 2)
                    {
                        AssignMarks();
                    }

                }
            }
            else if (x == 5)
            {
                int e = 0;
                while (e != 3)
                {
                    cout << "----------Course Withdraw----------" << endl << endl;
                    cout << "1 - Enrolled courses" << endl;
                    cout << "2 - Drop a course" << endl;
                    cout << "3 - Back " << endl;
                    cin >> e;

                    if (e == 1)
                    {
                        DisplayCourses();
                    }
                    else if (e == 2)
                    {
                        WithdrawCourse();
                    }

                }
            }
            else if(x!=6)
            {
                cout << "ENTER A VALID SELECTION" << endl;
            }

        }
      
    }
};

int System::sizeS = 0;
int System::sizeC = 0;


int main()
{
    // Example usage
    System _system;
    _system.printmenu();

    /*_system.AddStudents("123", "John Doe", "123-456-7890", 20);
    _system.AddStudents("456", "Jane Doe", "987-654-3210", 22);*/

 //   _system.DisplayAllStudents();
 //   _system.MarkAttendance();
  //  _system.AssignMarks();


    //_system.RegisterCourse();

    //_system.DisplayAttendance();


    //_system.DisplayMarks();


   // _system.DisplayCourses();

   // _system.WithdrawCourse();


    system("pause");
    return 0;
}