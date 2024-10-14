//Areez Abdullah 22i-1090 OOP-B Summer Project 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

    //*************************************Class User*************************************//        
    class User 
    {
        private:
            string name;
            string email;
            int uniqueID;
            string password;
            string phone;
            string role;

        public:
            //Default and Parameterized constructor
            User(string n = "", string e = "", int ID = 0, string P1 = "", string P2 = "", string r = "")
                : name(n), email(e), uniqueID(ID), password(P1), phone(P2), role(r) {}

            //Setters
            void setName(string n) { name = n; }
            void setEmail(string e) { email = e; }
            void setUniqueID(int ID) { uniqueID = ID; }
            void setPassword(string P1) { password = P1; }
            void setPhone(string P2) { phone = P2; }
            void setRole(string r) { role = r; }

            //Getters
            string getName() const { return name; }
            string getEmail() const { return email; }
            int getUniqueID() const { return uniqueID; }
            string getPassword() const { return password; }
            string getPhone() const { return phone; }
            string getRole() const { return role; }


            //This is for Login for user
            bool loginUser(string username, string password) 
            {
                ifstream inFile("user.txt");
                if (!inFile) {
                    cout << "Can't open the file" << endl;
                    return false;
                }

            string line;
            while (getline(inFile, line)) 
            {
                    stringstream ss(line);
                    string name, email, storedPassword, phone, role;
                    int uniqueID;

                getline(ss, name, ',');
                getline(ss, email, ',');
                ss >> uniqueID;
                ss.ignore(); 
                getline(ss, storedPassword, ',');
                getline(ss, phone, ',');
                getline(ss, role, ',');


                if (name == username && storedPassword == password) {
                    name = name;
                    email = email;
                    uniqueID = uniqueID;
                    password = storedPassword;
                    phone = phone;
                    role = role;
                    inFile.close();
                    return true;
                }
            }

                inFile.close();
                return false;
            }


            //saving data to file
            void saveProfileToFile() const 
            {
                ofstream outFile("user.txt", ios::app);
                if (outFile.is_open()) 
                {
                    outFile << name << "," << email << "," << uniqueID << "," << password << "," << phone << "," << role << endl;
                    outFile.close();
                }
                else 
                    cout << "Can't open the file" << endl;
                
            }

            static void loadProfilesFromFile() 
            {
                ifstream inFile("classroom.txt");
                if (inFile.is_open()) 
                {
                    string line;
                    while (getline(inFile, line)) {}
                    inFile.close();
                }
                else 
                    cout << "Can't open the file" << endl;
                
            }

            //Authentication using polymorphism
            virtual bool authenticate(string inputPassword) const 
            {
                return password == inputPassword;
            }

            virtual void registerUser() 
            {
                cout << "User registered: " << name << " (" << role << ")" << endl;
            }
            //operator
            bool operator==(const User& other) const 
            {
                return uniqueID == other.uniqueID;
            }
    };

//*************Class Student inherited by class User******************//
    class Student : public User 
    {
        public:
            //Default and Parameterized constructors
            Student(string n = "", string e = "", int ID = 0, string P1 = "", string P2 = "", string r = "Student"):User(n, e, ID, P1, P2, r) {}

    };

    //*************Class Teacher inherited by class User******************//
    class Teacher : public User 
    {

        public:
            //Default and Parameterized constructors
            Teacher(string n = "", string e = "", int ID = 0, string P1 = "", string P2 = "", string r = "Teacher"):User(n, e, ID, P1, P2, r) {}
    };

    //*************************************Class File*************************************//        
    class File 
    {
        private:
            string fileName;

        public:
            //constructor
            File() : fileName("file.txt") {}
            //setter
            void setFileName(string name) { fileName = name; }
            //getter
            string getFileName() const { return fileName; }
    };



    //*************************************Class Class*************************************//        
    const int MAX_Class = 10;
    const int MAX_ROSTER_SIZE = 50;    
    class Class
    {
    private:
        int numClasses=0;
        string class_name;
        string subject;
        //Composition
        Teacher teacher;
        //Composition
        File attachedFiles[MAX_Class];
        int numAttachedFiles;
        string description;
        //Aggregation
        Student* roster[MAX_ROSTER_SIZE];
        int numStudents;

    public:
        //Parameterized default constructor
        Class(string c = " ", string s = " ", const Teacher& t = Teacher(), string d = " ")
            : class_name(c), subject(s), teacher(t), description(d), numStudents(0), numAttachedFiles(0) {}

        //setters
        void setClassName(string c) { class_name = c; }
        void setSubject(string s) { subject = s; }
        void setTeacher(const Teacher& t) { teacher = t; }
        void setDescription(string d) { description = d; }

        //getters
        string getClassName() const { return class_name; }
        string getSubject() const { return subject; }
        Teacher getTeacher() const { return teacher; }
        string getDescription() const { return description; }
        int getNumStudents() const { return numStudents; }
        int getNumAttachedFiles() const { return numAttachedFiles; }

            //this function is for creating a class
            void createClass(const string& t, const string& d,const string& s, const Teacher& teacher, const File* files, int numFiles)
            {
                if (numClasses >= MAX_Class)
                {
                    cout << "Classes" << endl;
                    return;
                }
                subject=s;
                class_name = t;
                description = d;
                this->teacher = teacher;
                numStudents = 0;
                numAttachedFiles = 0;

                for (int i = 0; i < numFiles && i < MAX_Class; i++)
                {
                    attachedFiles[i] = files[i];
                    numAttachedFiles++;
                }

                saveToFile();
                
            }

            //this function is for updating and already existed class
            void updateClass(const string& t, const string& d,const string& s,const Teacher& teacher, const File* files, int numFiles)
            {
                subject=s;
                class_name = t;
                description = d;
                numAttachedFiles = 0;
                this->teacher = teacher;
                for (int i = 0; i < numFiles && i < MAX_Class; i++)
                {
                    attachedFiles[i] = files[i];
                    numAttachedFiles++;
                }

                saveToFile();
            }

            //this function is for deleting an already existing class
            void deleteClass()
            {
                class_name = " ";
                subject = " ";
                description = " ";
                numStudents = 0;
                numAttachedFiles = 0;

                for (int i = 0; i < MAX_Class; i++)
                    attachedFiles[i].setFileName("file.txt");

            
                saveToFile();
            }

            //viewing the class details
            void viewClassDetails()
            {
                cout << "Class Name: " << class_name << endl;
                cout << "Subject: " << subject << endl;
                cout << "Teacher: " << teacher.getName() << endl;
                cout << "Description: " << description << endl;
            }    

        
        bool saveToFile() const
        {
            ofstream file("Class.txt", ios::app);
            if (file.is_open())
            {
                file << "Class Name: " << class_name << endl;
                file << "Subject: " << subject << endl;
                file << "Teacher: " << teacher.getName() << endl;
                file << "Description: " << description << endl;
            }
            else
            {
                cout << "Can't open the file" << endl;
                return false;
            }
        }

        bool loadFromFile(ifstream& file)
        {
            if (file.is_open())
            {
                string line;
                while (getline(file, line))
                {
                    if (line.find("Class Name: ") != string::npos)
                    {
                        class_name = line.substr(12);
                        getline(file, line);
                        subject = line.substr(9);
                        getline(file, line);
                        string teacherName = line.substr(9);
                        teacher.setName(teacherName);
                        getline(file, line);
                        description = line.substr(13);
                        getline(file, line);

                        numStudents = 0;
                        

                        while (getline(file, line) && line.find("Attached Files:") == string::npos)
                        {
                        }
                        
                        numAttachedFiles = 0;
                        while (getline(file, line) && !line.empty())
                        {
                            if (numAttachedFiles < MAX_Class)
                                attachedFiles[numAttachedFiles++].setFileName(line);
                        }
                    }
                }
                return true;
            }
            else
            {
                cout << "Can't open the file" << endl;
                return false;
            }
        }
    };

    //*************************************Class Datetime*************************************//        
    class Datetime 
    {
        private:
            string datetime;

        public:
            //default constructor
            Datetime() : datetime(" ") {}
            //parameterized constructor
            Datetime(string d) : datetime(d) {}
            //setter
            void setDatetimeString(string d) { datetime = d; }
            //getter
            string getDatetimeString() const { return datetime; }
    };

    //*************************************Class Assignment*************************************//        
    const int MAX_Assignment = 10; 
    class Assignment 
    {
        private:
            string title;
            string description;
            //Composition
            Datetime deadline;
            //Composition
            File attachedFiles[MAX_Assignment];
            int numAttachedFiles; 
            int pointValue;

        public:
            //default constructor
            Assignment() : title(""), description(""), numAttachedFiles(0), pointValue(0) {}

            //parameterized constructor
            Assignment(string t, string d, const Datetime& dl, const File* files, int numFiles, int p):title(t), description(d), deadline(dl), numAttachedFiles(numFiles), pointValue(p) 
            {
                for (int i = 0; i < numFiles; i++) 
                attachedFiles[i] = files[i];
            
            }

            //setters
            void setTitle(string t) { title = t; }
            void setDescription(string d) { description = d; }
            void setDeadline(const Datetime& dl) { deadline = dl; }
            void setPointValue(int p) { pointValue = p; }
            void setAssignmentTitle(const File* files, int numFiles) 
            {
                numAttachedFiles = min(numFiles, MAX_Assignment);
                for (int i = 0; i < numAttachedFiles; i++) 
                attachedFiles[i] = files[i];
            }   
            

            //getters
            string getTitle() const { return title; }
            string getDescription() const { return description; }
            Datetime getDeadline() const { return deadline; }
            const File* getAssignmentTitle() const { return attachedFiles; }
            int getNumAttachedFiles() const { return numAttachedFiles; }
            int getPointValue() const { return pointValue; }
            
            //creating an Assignment
            void createAssignment(string t, string d, const Datetime& dl, const File* files, int numFiles, int p) 
            {
                title = t;
                description = d;
                deadline = dl;
                setAssignmentTitle(files, numFiles);
                pointValue = p;
            }


            //Updating an Assingmwent
            void updateAssignment(string t, string d, const Datetime& dl, const File* files, int numFiles, int p) 
            {
                title = t;
                description = d;
                deadline = dl;
                setAssignmentTitle(files, numFiles);
                pointValue = p;
            }

            //deleting an Assignment
            void deleteAssignment() 
            {
                title.clear();
                description.clear();
                deadline = Datetime();
                numAttachedFiles = 0;
                pointValue = 0;
            }

            //File handling
            
            bool saveToFile() const
            {
                ofstream file("assignments.txt", ios::app);
                if (!file)
                {
                    cout << "Can't open the file" << endl;
                    return false;
                }
                file << getTitle() << endl;
                file << getDescription() << endl;
                file << getDeadline().getDatetimeString() << endl;
                file << getPointValue() << endl;
                file << getNumAttachedFiles() << endl;
                for (int j=0; j<getNumAttachedFiles(); ++j)
                {
                    file << getAssignmentTitle()[j].getFileName() << endl;
                }
                file.close();
                return true;
            }   

            bool loadFromFile(ifstream& file)
            {
                string t, d, dl;
                int p, numFiles;
                getline(file, t);
                if (t.empty()) 
                {
                    file.close(); 
                    return false;
                }

                getline(file, d);
                getline(file, dl);
                file >> p;
                file >> numFiles;
                file.ignore();
                
                File files[MAX_Assignment];
                for (int j=0; j<numFiles; ++j)
                {
                    string fileName;
                    getline(file, fileName);
                    files[j].setFileName(fileName);
                }
                
                if (file.peek() == ifstream::traits_type::eof()) 
                {
                    file.close();
                    return false;
                }

                setTitle(t);
                setDescription(d);
                setDeadline(Datetime(dl));
                setAssignmentTitle(files, numFiles);
                setPointValue(p);

                file.close();
                return true;
            }

    };

    //*************************************Class Submission*************************************//        
    const int MAX_Submission = 10; 
    class Submission 
    {
        private:
            string submissionTimestamp;
            //Composition
            File attachedFiles[MAX_Submission];
            int numAttachedFiles;
            string evaluationStatus;
            //Aggregation
            Assignment* assignment;
            string feedback;
            //Aggregation
            Student* student; 
            //Aggregation
            Teacher* teacher; 

        public:
            //default constructor
            Submission() : submissionTimestamp(""), numAttachedFiles(0), evaluationStatus(""), feedback(""), student(nullptr), teacher(nullptr) {}

            //parameterized constructor
            Submission(string timestamp, const File* files, int numFiles, Student* s):submissionTimestamp(timestamp), numAttachedFiles(numFiles), evaluationStatus(""), feedback(""), student(s), teacher(nullptr) 
            {
                for (int i = 0; i < numFiles; i++) 
                    attachedFiles[i] = files[i];
            }

            //setters
            void setSubmissionTimestamp(string timestamp) { submissionTimestamp = timestamp; }
            void setEvaluationStatus(string status) { evaluationStatus = status; }
            void setFeedback(string fb) { feedback = fb; }
            void setAssignment(Assignment* assignment) 
            {
            this->assignment = assignment;
            }
            void setAssignmentTitle(const File* files, int numFiles) 
            {
                numAttachedFiles = min(numFiles, MAX_Submission);
                for (int i = 0; i < numAttachedFiles; i++) 
                    attachedFiles[i] = files[i];
            }
            
            //getters
            int getNumAttachedFiles() const { return numAttachedFiles; }
            string getEvaluationStatus() const { return evaluationStatus; }
            string getFeedback() const { return feedback; }
            string getSubmissionTimestamp() const { return submissionTimestamp; }
            Student* getStudent() const { return student; }
            Teacher* getTeacher() const { return teacher; }
            string getAssignmentTitle() const 
            {
                if (assignment != nullptr)
                    return assignment->getTitle();
                else 
                    return ""; 
            } 
        
            
            void submitAssignment(const Datetime& deadline, const File* files, int numFiles, const string& timestamp, Student* s) 
            {
                
                submissionTimestamp = timestamp;
                setAssignmentTitle(files, numFiles);
                evaluationStatus = "Pending"; 
                feedback = ""; 
                student = s; 
                teacher = nullptr; 
            }

            void gradeSubmission(const string& status, const string& fb, Teacher* t) 
            {
                evaluationStatus = status;
                feedback = fb;
                teacher = t; 
            }

        
    };

    //*************************************Class Grade*************************************//        
    class Grade 
    {
        public:
            int studentID;
            double grade;

            Grade(int studentID = 0, double grade = 0) : studentID(studentID), grade(grade) {}
    };


    const int MAX_STUDENTS = 50;
    const int MAX_TEACHERS = 10;
    class Gradebook 
    {
        private:
            double cumulativeGrades;
            double classAverage;
            double weightageSettings;
            //Composition
            Grade studentGrades[MAX_STUDENTS];
            int numStudents;
            //Aggregation
            Teacher teachers[MAX_TEACHERS];
            int numTeachers;

        public:
            //Default constructor
            Gradebook() : cumulativeGrades(0.0), classAverage(0.0), weightageSettings(0.0), numStudents(0), numTeachers(0) {}

            //Parameterized constructor
            Gradebook(double cumulativeGrades, double classAverage, double weightageSettings):cumulativeGrades(cumulativeGrades), classAverage(classAverage), weightageSettings(weightageSettings), numStudents(0), numTeachers(0) {}

            //setters
            void setCumulativeGrades(double cumulativeGrades) { this->cumulativeGrades = cumulativeGrades; }
            void setClassAverage(double classAverage) { this->classAverage = classAverage; }
            void setWeightageSettings(double weightageSettings) { this->weightageSettings = weightageSettings; }

            //getters
            double getCumulativeGrades() const { return cumulativeGrades; }
            double getClassAverage() const { return classAverage; }
            double getWeightageSettings() const { return weightageSettings; }
            void addTeacher(const Teacher& teacher) 
            {
                if (numTeachers < MAX_TEACHERS) 
                    teachers[numTeachers++] = teacher;
                
                else 
                    cout << "Maximum number of teachers reached. Cannot add more teachers." << endl;
            
            }
            
            Teacher* getTeacherByName( string& teacherName) 
            {
                for (int i = 0; i < numTeachers; i++)
                {
                    if (teachers[i].getName() == teacherName)
                    {
                        return &teachers[i];
                    }
                }

                return nullptr;
            }

            Teacher* getTeacherById(int teacherId) 
            {
                for (int i = 0; i < numTeachers; i++) 
                {
                    if (teachers[i].getUniqueID() == teacherId) 
                    return &teachers[i];
                }
                return nullptr;
                
            }    

            void addStudentGrade(const Grade& grade) 
            {
                if (numStudents < MAX_STUDENTS) 
                {
                    studentGrades[numStudents++] = grade;
                    updateCumulativeGrades();
                    updateClassAverage();
                } 
                else 
                    cout << "Can't add more grades" << endl;
            }

            void updateStudentGrade(int studentID, double grade) 
            {
                for (int i = 0; i < numStudents; i++) 
                {
                    if (studentGrades[i].studentID == studentID) 
                    {
                    studentGrades[i].grade = grade;
                    updateCumulativeGrades();
                    updateClassAverage();
                    return;
                    }
                }
                cout << "ID not found" << endl;
            }

            void updateCumulativeGrades() 
            {
                cumulativeGrades = 0.0;
                for (int i = 0; i < numStudents; i++) 
                {
                    cumulativeGrades += studentGrades[i].grade;
                }
            }
        
            void updateClassAverage()
            {
                if (numStudents > 0)
                classAverage = cumulativeGrades / numStudents;
                else
                classAverage = 0.0;
            }

            void generateStudentGradeReport(int studentID) const 
            {
                for (int i = 0; i < numStudents; i++) 
                {
                    if (studentGrades[i].studentID == studentID) 
                    {
                    cout << "Grade Report for Student ID: " << studentID << endl;
                    cout << "Cumulative Grade: " << cumulativeGrades << endl;
                    cout << "Individual Grade: " << studentGrades[i].grade << endl;
                    return;
                    }
                }
                cout << "ID not found" << endl;
            }

            void generateClassGradeReport() const 
            {
                cout << "Class Grade Report" << endl;
                cout << "Class Average: " << classAverage << endl;
                cout << "Cumulative Grades: " << cumulativeGrades << endl;
                cout << "Individual Student Grades:" << endl;
                for (int i = 0; i < numStudents; i++) 
                cout << "Student ID: " << studentGrades[i].studentID << " - Grade: " << studentGrades[i].grade << endl;
            }

            void saveToFile() const 
            {   
                ofstream outFile("gradebook.txt");
                if (outFile.is_open()) 
                {
                    outFile << cumulativeGrades << endl;
                    outFile << classAverage << endl;
                    outFile << weightageSettings << endl;
                    for (int i = 0; i < numStudents; i++) 
                        outFile << studentGrades[i].studentID << " " << studentGrades[i].grade << endl;
                    outFile.close();
                }

                else 
                cout << "Can't open the file" << endl;
            }   

            void loadFromFile() 
            {
                ifstream inFile("gradebook.txt");
                if (inFile.is_open()) 
                {
                inFile >> cumulativeGrades;
                inFile >> classAverage;
                inFile >> weightageSettings;
                numStudents = 0;
                int studentID;
                double grade;
                while (inFile >> studentID >> grade) 
                {
                    if (numStudents < MAX_STUDENTS) 
                        studentGrades[numStudents++] = Grade(studentID, grade);
                    else 
                    {
                        cout << "can't load more grades" << endl;
                        break;
                    }
                }

                    inFile.close();
                } 
                else 
                cout << "Can't open the file" << endl;
            
            }
    };