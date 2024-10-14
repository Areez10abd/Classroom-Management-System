//Areez Abdullah 22i-1090 Summer Project MENU OOP-B
#include <iostream>
#include <string>
#include <fstream>
#include "Project.h"
using namespace std;

//This functioon is for loging in to the system
bool login(User& user)
{
    string username, password;
    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, username);

    cout << "Enter your password: ";
    getline(cin, password);

    if (user.loginUser(username, password))
    {
        cout << "Login successful!" << endl;
        return true;
    }

    else
    {
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}
//This function is for signup
void signup()
{
    ifstream inFile("user.txt");
    int highestID = 0;

    if (inFile)
    {
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            int ID;
            ss >> ID;
            if (ID > highestID) {
                highestID = ID;
            }
        }
        inFile.close();
    }
    int userTypeChoice;
    cout << "Choose user type: " << endl;
    cout << "1. Student" << endl;
    cout << "2. Teacher" << endl;
    cout << "Enter user type choice: ";
    cin >> userTypeChoice;
    string name, email, password, phone;
    highestID++;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter email: ";
    getline(cin, email);

    cout << "uniqueID: " << highestID << endl;


    cout << "Enter password: ";
    cin >> password;

    cout << "Enter phone: ";
    cin.ignore();
    getline(cin, phone);

    if (userTypeChoice == 1)
    {
        Student student;
        student.setName(name);
        student.setEmail(email);
        student.setUniqueID(highestID);
        student.setPassword(password);
        student.setPhone(phone);
        student.saveProfileToFile();
        student.registerUser();
    }
    else if (userTypeChoice == 2)
    {
        Teacher teacher;
        teacher.setName(name);
        teacher.setEmail(email);
        teacher.setUniqueID(highestID);
        teacher.setPassword(password);
        teacher.setPhone(phone);
        teacher.saveProfileToFile();
        teacher.registerUser();
    }
    else
        cout << "Invalid choice" << endl;



}

int main()
{

    const int MAX_CLASSES = 10;
    const int MAX_ASSIGNMENTS = 10;
    User user;
    User::loadProfilesFromFile();
    Class classes[MAX_CLASSES];
    Assignment assignments[MAX_ASSIGNMENTS];
    int numClasses = 0;
    int numAssignments = 0;
    ifstream file;
    bool isLoggedIn = false;
    
    
    while (!isLoggedIn)
    {
        //Switch for login/sign-up
        int loginChoice;
        cout << "####################################################" << endl;
        cout << "<O><O><O><O> Welcome to Areez Classroom <O><O><O><O>" << endl;
        cout << "####################################################" << endl;
        cout << "<<Press 1 for Log-in>>" << endl;
        cout << "<<Press 2 for Sign-up>>" << endl;
        cin >> loginChoice;

        switch (loginChoice)
        {
        case 1:
            if (login(user))
            {
                isLoggedIn = true;
            }
            break;

        case 2:
            signup();
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

//*************************************(MENU)*************************************//        
    int choice;
    do
    {
        cout << "*********************************************" << endl;
        cout << "!!!!!!!! Classroom Management System !!!!!!!!" << endl;
        cout << "*********************************************" << endl;
        cout << "1. Class Management" << endl;
        cout << "2. Assignment Management" << endl;
        cout << "3. Submission and Grading" << endl;
        cout << "4. Notification" << endl;
        cout << "5. Log out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

//*************************************(Choice 1)*************************************//
        case 1:
        {


            int classOption;
            cout << "-------------------------------------------" << endl;
            cout << "|           Class Management              |" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "1. Create Class" << endl;
            cout << "2. Update Class" << endl;
            cout << "3. Delete Class" << endl;
            cout << "4. View Class Details" << endl;
            cout << "5. List of users" << endl;
            cout << "6. Add a user" << endl;
            cout << "7. Remove a user" << endl;
            cout << "8. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> classOption;

            switch (classOption)
            {

            case 1:
            {
                //Checking if classes created are more than maximum classes (5)
                if (numClasses >= MAX_Class)
                {
                    cout << "Maximum number of classes reached. Cannot create more classes." << endl;
                }
                else
                {
                    string className, subject, description, teacherName;
                    cout << "Enter class name: ";
                    cin.ignore();
                    getline(cin, className);
                    cout << "Enter subject: ";
                    getline(cin, subject);
                    cout << "Enter description: ";
                    getline(cin, description);
                    cout << "Enter teacher's name: ";
                    getline(cin, teacherName);
                    Teacher teacher(teacherName);

                    File attachedFiles[MAX_Class];
                    int numFiles = 0;
                    int p = 0;

                    classes[numClasses].createClass(className, description, subject, teacher, attachedFiles, numFiles);
                    numClasses++;
                    cout << "Class created successfully!" << endl;
                }
                break;
            }
            case 2:
            {
                string className, newClassName, newSubject, newDescription, newTeacherName;
                cout << "Enter the name of the class to update: ";
                cin.ignore();
                getline(cin, className);

                int index = -1;
                for (int i = 0; i < numClasses; i++)
                {
                    if (classes[i].getClassName() == className)
                    {
                        index = i;
                        break;
                    }
                }

                if (index == -1)
                {
                    cout << "Class not found." << endl;
                }
                else
                {
                    cout << "Enter new class name: ";
                    getline(cin, newClassName);


                    cout << "Enter new description: ";
                    getline(cin, newDescription);

                    cout << "Enter new teacher's name: ";
                    getline(cin, newTeacherName);

                    Teacher newTeacher(newTeacherName);

                    File attachedFiles[MAX_Class];
                    int numFiles = 0;
                    int p = 0;

                    classes[index].updateClass(newClassName, newDescription, newSubject, newTeacher, attachedFiles, numFiles);
                    cout << "Class updated successfully!" << endl;
                }
                break;
            }
            case 3:
            {
                string className;
                cout << "Enter the name of the class to delete: ";
                cin.ignore();
                getline(cin, className);

                int index = -1;
                for (int i = 0; i < numClasses; i++)
                {
                    if (classes[i].getClassName() == className)
                    {
                        index = i;
                        break;
                    }
                }

                if (index == -1)
                {
                    cout << "Class not found." << endl;
                }
                else
                {
                    classes[index] = classes[numClasses - 1];
                    numClasses--;
                    cout << "Class deleted successfully!" << endl;
                }
                break;
            }

            case 4:
            {
                if (numClasses == 0)
                {
                    cout << "No classes found. Please create a class first." << endl;
                }
                else
                {
                    cout << "Class Details for All Classes:" << endl;
                    cout << "*******************************" << endl;
                    for (int i = 0; i < numClasses; i++)
                    {
                        classes[i].viewClassDetails();
                        cout << "*******************************" << endl;
                    }
                }
                break;
            }

            case 5:
            {
                ifstream inFile("user.txt");
                if (!inFile)
                {
                    cout << "Can't open the file" << endl;
                    break;
                }

                cout << "List of all students:" << endl;
                cout << "-____________________________" << endl;
                string line;
                while (getline(inFile, line))
                {
                    stringstream ss(line);
                    string name, email, password, phone;
                    int uniqueID;

                    getline(ss, name, ',');
                    getline(ss, email, ',');
                    ss >> uniqueID;
                    ss.ignore();
                    getline(ss, password, ',');
                    getline(ss, phone, ',');

                    cout << "Name: " << name << endl;
                    cout << "Email: " << email << endl;
                    cout << "Password: " << password << endl;
                    cout << "Phone: " << phone << endl;
                    cout << "_______________________________" << endl;
                }

                inFile.close();
                break;
            }

            case 6:
                signup();
                break;

            case 7:
            {
                cout << "Enter the name of the student you want to remove: ";
                string studentNameToRemove;
                cin.ignore();
                getline(cin, studentNameToRemove);

                ifstream inFile2("user.txt");
                ofstream outFile("temp_user.txt");

                if (inFile2 && outFile)
                {
                    string line2;
                    while (getline(inFile2, line2))
                    {
                        stringstream ss(line2);
                        string name, email, password, phone;
                        int uniqueID;

                        getline(ss, name, ',');
                        getline(ss, email, ',');
                        ss >> uniqueID;
                        ss.ignore();
                        getline(ss, password, ',');
                        getline(ss, phone, ',');

                        if (name != studentNameToRemove)
                        {
                            outFile << line2 << endl;
                        }
                    }
                    inFile2.close();
                    outFile.close();

                    remove("user.txt");
                    rename("temp_user.txt", "user.txt");

                    cout << "Student removed successfully!" << endl;
                }
                else
                {
                    cout << "Can't open the file" << endl;
                }

                break;
            }

            case 8:
                cout << "Returning to the main menu." << endl;
                break;

            default:
                cout << "Invalid choice for Class Management." << endl;
                break;
            }

            break;
        }


//*************************************(Choice 2)*************************************//
        case 2:
        {
            const int MAX_ASSIGNMENTS = 100;
            Assignment assignments[MAX_ASSIGNMENTS];
            int numAssignments = 0;
            ifstream assignmentFile("assignments.txt");
            if (assignmentFile)
            {
                while (numAssignments < MAX_ASSIGNMENTS && assignments[numAssignments].loadFromFile(assignmentFile))
                {
                    numAssignments++;
                }
                assignmentFile.close();
            }
            int choice;
            do
            {
                cout << "-------------------------------------------" << endl;
                cout << "|          Assignment Management           |" << endl;
                cout << "-------------------------------------------" << endl;
                cout << "1. Create Assignment" << endl;
                cout << "2. Update Assignment" << endl;
                cout << "3. Delete Assignment" << endl;
                cout << "4. View Assignments" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice)
                {

                case 1:
                {
                    if (numAssignments == MAX_ASSIGNMENTS)
                    {
                        cout << "Maximum number of assignments reached. Cannot create more." << endl;
                        break;
                    }

                    string title, description, deadlineString;
                    int pointValue;
                    File attachedFiles[MAX_Assignment];
                    int numFiles = 0;

                    cout << "Enter the title of the assignment: ";
                    getline(cin, title);

                    cout << "Enter the description of the assignment: ";
                    getline(cin, description);

                    cout << "Enter the deadline (format: YYYY-MM-DD HH:mm): ";
                    getline(cin, deadlineString);
                    Datetime deadline(deadlineString);

                    cout << "Enter the point value of the assignment: ";
                    cin >> pointValue;
                    cin.ignore();

                    Assignment newAssignment;
                    newAssignment.createAssignment(title, description, deadline, attachedFiles, numFiles, pointValue);

                    if (newAssignment.saveToFile())
                    {
                        assignments[numAssignments++] = newAssignment;
                        cout << "Assignment created successfully!" << endl;
                    }
                    else
                    {
                        cout << "Error: Could not save assignment to file." << endl;
                    }

                    break;
                }

                case 2:
                {
                    if (numAssignments == 0)
                    {
                        cout << "No assignments available. Please create an assignment first." << endl;

                        break;
                    }

                    string title;
                    cout << "Enter the title of the assignment to update: ";
                    getline(cin, title);

                    int index = -1;
                    for (int i = 0; i < numAssignments; i++)
                    {
                        if (assignments[i].getTitle() == title)
                        {
                            index = i;
                            break;
                        }
                    }

                    if (index != -1)
                    {
                        string description, deadlineString;
                        int pointValue;
                        File attachedFiles[MAX_Assignment];
                        int numFiles = 0;

                        cout << "Enter the updated description of the assignment: ";
                        getline(cin, description);

                        cout << "Enter the updated deadline (format: YYYY-MM-DD HH:mm): ";
                        getline(cin, deadlineString);
                        Datetime deadline(deadlineString);

                        cout << "Enter the updated point value of the assignment: ";
                        cin >> pointValue;
                        cin.ignore();

                        assignments[index].updateAssignment(title, description, deadline, attachedFiles, numFiles, pointValue);
                        assignments[index].saveToFile();
                        cout << "Assignment updated successfully!" << endl;
                    }
                    else
                        cout << "Assignment with title '" << title << "' not found." << endl;

                    break;
                }

                case 3:
                {

                    if (numAssignments == 0)
                    {
                        cout << "No assignments available. Please create an assignment first." << endl;
                        break;
                    }

                    string deleteTitle;
                    cout << "Enter the title of the assignment to delete: ";
                    getline(cin, deleteTitle);

                    int index = -1;
                    for (int i = 0; i < numAssignments; i++)
                    {
                        if (assignments[i].getTitle() == deleteTitle)
                        {
                            index = i;
                            break;
                        }
                    }

                    if (index != -1)
                    {
                        assignments[index].deleteAssignment();
                        for (int i = index + 1; i < numAssignments; i++)
                            assignments[i - 1] = assignments[i];

                        numAssignments--;
                        cout << "Assignment deleted successfully!" << endl;

                        ofstream assignmentFile("assignments.txt");
                        if (assignmentFile)
                        {
                            for (int i = 0; i < numAssignments; i++)
                            {
                                assignments[i].saveToFile();
                            }
                            assignmentFile.close();
                        }
                        else
                        {
                            cout << "Error: Could not open the file." << endl;
                        }
                    }
                    else
                        cout << "Assignment with title '" << deleteTitle << "' not found." << endl;
                    break;
                }

                case 4:
                {
                    if (numAssignments == 0)
                    {
                        cout << "No assignments available. Please create an assignment first." << endl;
                        break;
                    }

                    cout << "-------------------------------------------" << endl;
                    cout << "|           Available Assignments         |" << endl;
                    cout << "-------------------------------------------" << endl;
                    for (int i = 0; i < numAssignments; i++)
                    {
                        cout << "Title: " << assignments[i].getTitle() << endl;
                        cout << "Description: " << assignments[i].getDescription() << endl;
                        cout << "Deadline: " << assignments[i].getDeadline().getDatetimeString() << endl;
                        cout << "Point Value: " << assignments[i].getPointValue() << endl;
                        cout << "-------------------------------------------" << endl;
                    }
                    break;
                }

                case 5:
                {
                    cout << "Returning to the main menu." << endl;
                    break;
                }

                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }

            } while (choice != 5);
            break;

        }


//*************************************(Choice 3)*************************************//                
        case 3:
        {
            const int MAX_SUBMISSIONS = 100;
            Submission submissions[MAX_SUBMISSIONS];
            int numSubmissions = 4;
            Class Obj;
            Gradebook obj;
            ifstream assignmentFile("assignments.txt");
            
            if (!assignmentFile)
            {
                cout << "Error: Could not open assignments.txt" << endl;

            }

            Assignment assignments[MAX_Assignment];
            int numAssignments = 0;

            while (numAssignments < MAX_Assignment)
            {
                Assignment newAssignment;
                if (!newAssignment.loadFromFile(assignmentFile))
                    break;
                assignments[numAssignments++] = newAssignment;
            }

            assignmentFile.close();

            int choice;
            do
            {
                cout << "-------------------------------------------" << endl;
                cout << "|        Submission and Grading          |" << endl;
                cout << "-------------------------------------------" << endl;
                cout << "1. Submit Assignment" << endl;
                cout << "2. Grade Submission" << endl;
                cout << "3. View Submissions" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                int studentId,marks;
                string status, feedback,title,timestamp,name,teachername;
                Teacher* teacher = obj.getTeacherByName(teachername); 
                        
                switch (choice)
                {
                case 1:
                {
                    if (numSubmissions == MAX_SUBMISSIONS)
                    {
                        cout << "Maximum number of submissions reached. Cannot accept more submissions." << endl;
                        break;
                    }

                    if (numAssignments == 0)
                    {
                        cout << "No assignments available. Please create an assignment first." << endl;
                        break;
                    }

                    cout << "Enter the title of the assignment to submit: ";
                    getline(cin, title);

                    int assignmentIndex = -1;
                    for (int i = 0; i < numAssignments; i++)
                    {
                        if (assignments[i].getTitle() == title)
                        {
                            assignmentIndex = i;
                            break;
                        }
                    }

                    if (assignmentIndex != -1)
                    {
                        cout << "Enter your name: ";
                        cin.ignore();
                        getline(cin,name);

                        
                        cout << "Enter the submission timestamp (format: YYYY-MM-DD HH:mm): ";
                        getline(cin, timestamp);

                        ofstream submissionFile("submission.txt", ios::app);
                        if (!submissionFile)
                        {
                            cout << "Error: Could not open the file for writing." << endl;
                            break;
                        }

                        cout << "Assignment Title: " << title << endl;
                        cout << "Submitted by: " << name << endl;
                        cout << "Submission Time: " <<timestamp<< endl;
                        cout << "-------------------------------------------" << endl;

                        submissionFile.close();

                        cout << "Assignment submitted successfully!" << endl;
                    }
                    else
                    {
                        cout << "Assignment with title '" << title << "' not found." << endl;
                    }
                    break;
                }

                case 2:
                {
                    if (numSubmissions == 0)
                    {
                        cout << "No submissions available for grading." << endl;
                        break;
                    }

                    cout << "Enter the title of the assignment to grade: ";
                    getline(cin, title);


                        cout << "Enter your name (Should be a teacher): ";
                        getline(cin, teachername);

                         
                            
                            cout << "Enter the evaluation status (e.g., 'Pending', 'Pass', 'Fail'): ";
                            getline(cin, status);
                            cout << "Enter the feedback: ";
                            getline(cin, feedback);
                            cout<<"Enter the marks: ";
                            cin>>marks;
                            cout << "Submission graded successfully!" << endl;

                    break;
                }


                case 3:
                {
                    if (numSubmissions == 0)
                    {
                        cout << "No submissions available." << endl;
                        break;
                    }


                cout << "-------------------------------------------" << endl;
                cout << "|           Available Submissions         |" << endl;
                cout << "-------------------------------------------" << endl;

                    cout << "Assignment Title: " << title << endl;
                    cout << "Submitted by: " << name << endl;
                    cout << "Checked by:   " << teachername << endl;
                    cout << "Submission Time: " << timestamp << endl;
                    cout << "Marks: " << marks << endl;
                    cout << "Feedback: " << feedback << endl;
                    cout << "Status: " << status << endl;

                    cout << "-------------------------------------------" << endl;
            }
                    break;
                
                    case 4:
                        cout << "Returning to the main menu." << endl;
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                
                }
                }
                while (choice != 4);
                break;
        }
        //*************************************(Choice 4)*************************************//                
        case 4:
        {
            cout << "-------------------------------------------" << endl;
            cout << "|              Notifications               |" << endl;
            cout << "-------------------------------------------" << endl;
            int choice;
            cout<<"1. Student"<<endl;
            cout<<"2. Teacher"<<endl;
            cin>>choice;
            if(choice==1)
            {
                cout<<"Class of OOP-B cancelld on Monday"<<endl;
                cout<<"Demos for PF-D tomorrow at 3:00pm"<<endl;
                cout<<"Please submit the feedback on the portal"<<endl;
                cout<<"Marks uploaded for OOP-Project"<<endl;
            }
            else if(choice==2)
            {
                cout<<"Make-up class in A-302"<<endl;
                cout<<"Duty in Marghala Lab "<<endl;
                cout<<"Meeting on Friday for All CS teacher in C-201"<<endl;
                cout<<"Please check the Finals for OOP-B before Thursday. ~HOD-CS"<<endl;
            }
            else 
                cout<<"Invalid choice"<<endl;
            break;
        }
        
        //*************************************(Choice 6)*************************************//                
        case 5:
            cout << "Exiting the Classroom Management System. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    user.saveProfileToFile();

    return 0;
}
