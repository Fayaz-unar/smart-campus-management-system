#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>
#include <limits>
using namespace std;
class Attendance {
public:
    static void markAttendance(const string& studentFile="students.txt",
                               const string& attendanceFile="attendance.txt") {
        ifstream fin(studentFile.c_str());
        if (!fin) { cout << "No students registered yet.\n"; return; }
        ofstream fout(attendanceFile.c_str(), ios::app);
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, dept, contact;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, contact, ',');

            char status;
            cout << "Mark attendance for " << name << " (P/A): ";
            cin >> status;
            status = toupper(status);
            if (status != 'P' && status != 'A') status = 'A';
            fout << id << "," << status << "\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Attendance recorded.\n";
    }
    static void getAttendanceStats(const string& studentId,
                                   const string& attendanceFile,
                                   int& presents, int& absents) {
        presents = absents = 0;
        ifstream fin(attendanceFile.c_str());
        if (!fin) return;
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, status;
            getline(ss, id, ',');
            getline(ss, status, ',');
            if (id == studentId) {
                if (status == "P") presents++;
                else if (status == "A") absents++;
                }   }   }   };

class Person {
protected:
    string id, name, department, contact;
public:
    Person(string i="", string n="", string d="", string c="")
        : id(i), name(n), department(d), contact(c) {}

    virtual void showDetails() const {
        cout << "ID: " << id << " | Name: " << name
             << " | Dept: " << department << " | Contact: " << contact;
    }

    string getId()   const { return id; }
    string getName() const { return name; }
};

class Student : public Person {
public:
    Student(string i="", string n="", string d="", string c="")
        : Person(i,n,d,c) {}

    void saveToFile(const string& filename="students.txt") const {
        ofstream fout(filename.c_str(), ios::app);
        fout << id << "," << name << "," << department << "," << contact << "\n";
    }

    static void showAll(const string& filename="students.txt") {
        ifstream fin(filename.c_str());
        if (!fin) { cout << "No students found.\n"; return; }
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, dept, contact;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, contact, ',');

            int p=0, a=0;
            Attendance::getAttendanceStats(id, "attendance.txt", p, a);
            int total = p + a;
            double percent = total ? (p * 100.0 / total) : 0.0;

            cout << "ID: " << id << " | Name: " << name
                 << " | Dept: " << dept << " | Contact: " << contact
                 << " | Presents: " << p
                 << " | Absents: " << a
                 << " | Attendance %: " << fixed << setprecision(2) << percent << "%\n";
        }
    }

    static void searchStudent(const string& searchId,
                              const string& filename="students.txt") {
        ifstream fin(filename.c_str());
        if (!fin) { cout << "No students found.\n"; return; }
        string line; bool found = false;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, dept, contact;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, contact, ',');

            if (id == searchId) {
                int p=0, a=0; Attendance::getAttendanceStats(id, "attendance.txt", p, a);
                int total = p + a;
                double percent = total ? (p * 100.0 / total) : 0.0;

                cout << "\nStudent Found:\n";
                cout << "ID: " << id << " | Name: " << name
                     << " | Dept: " << dept << " | Contact: " << contact
                     << " | Presents: " << p
                     << " | Absents: " << a
                     << " | Attendance %: " << fixed << setprecision(2) << percent << "%\n";
                found = true; break;
            }
        }
        if (!found) cout << "Student not found.\n";
    }

    static void updateStudent(const string& searchId,
                              const string& filename="students.txt") {
        ifstream fin(filename.c_str());
        if (!fin) { cout << "No students found.\n"; return; }
        ofstream fout("temp.txt");
        string line; bool found = false;

        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, dept, contact;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, contact, ',');

            if (id == searchId) {
                found = true;
                cout << "Enter new name: "; getline(cin, name);
                cout << "Enter new dept: "; getline(cin, dept);
                cout << "Enter new contact: "; getline(cin, contact);
                fout << id << "," << name << "," << dept << "," << contact << "\n";
            } else {
                fout << line << "\n";
            }
        }
        fin.close(); fout.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << (found ? "Record updated!\n" : "Student not found!\n");
    }

    static void deleteStudent(const string& searchId,
                              const string& filename="students.txt") {
        ifstream fin(filename.c_str());
        if (!fin) { cout << "No students found.\n"; return; }
        ofstream fout("temp.txt");
        string line; bool found = false;

        while (getline(fin, line)) {
            stringstream ss(line);
            string id; getline(ss, id, ',');
            if (id == searchId) { found = true; continue; }
            fout << line << "\n";
        }
        fin.close(); fout.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << (found ? "Record deleted!\n" : "Student not found!\n");
    }
};

class Faculty : public Person {
public:
    Faculty(string i="", string n="", string d="", string c="")
        : Person(i,n,d,c) {}

    void saveToFile(const string& filename="faculty.txt") const {
        ofstream fout(filename.c_str(), ios::app);
        fout << id << "," << name << "," << department << "," << contact << "\n";
    }

    static void showAll(const string& filename="faculty.txt") {
        ifstream fin(filename.c_str());
        if (!fin) { cout << "No faculty found.\n"; return; }
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, dept, contact;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dept, ',');
            getline(ss, contact, ',');
            cout << "ID: " << id << " | Name: " << name
                 << " | Dept: " << dept << " | Contact: " << contact << "\n";
        }
    }
};

class LibraryItem {
protected:
    string ISBN, title, author; int copies;
public:
    LibraryItem(string isbn="", string t="", string a="", int c=0)
        : ISBN(isbn), title(t), author(a), copies(c) {}
    virtual ~LibraryItem() {}
    virtual void showDetails() const {
        cout << "ISBN: " << ISBN << " | Title: " << title
             << " | Author: " << author << " | Copies: " << copies;
    }
    virtual void issueItem() = 0;
    virtual void returnItem() = 0;
};

class Book : public LibraryItem {
public:
    using LibraryItem::LibraryItem;
    void issueItem() override {
        if (copies > 0) { copies--; cout << "Book issued. Remaining: " << copies << "\n"; }
        else cout << "Book not available!\n";
    }
    void returnItem() override {
        int days; cout << "Enter days kept: "; cin >> days;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        copies++;
        if (days > 14) cout << "Fine: Rs." << (days-14)*10 << "\n";
        else cout << "Returned successfully.\n";
    }
};

class Magazine : public LibraryItem {
public:
    using LibraryItem::LibraryItem;
    void issueItem() override {
        if (copies > 0) { copies--; cout << "Magazine issued. Remaining: " << copies << "\n"; }
        else cout << "Magazine not available!\n";
    }
    void returnItem() override {
        int days; cout << "Enter days kept: "; cin >> days;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        copies++;
        if (days > 7) cout << "Fine: Rs." << (days-7)*5 << "\n";
        else cout << "Returned successfully.\n";
    }
};

class CD : public LibraryItem {
public:
    using LibraryItem::LibraryItem;
    void issueItem() override {
        if (copies > 0) { copies--; cout << "CD issued. Remaining: " << copies << "\n"; }
        else cout << "CD not available!\n";
    }
    void returnItem() override {
        int days; cout << "Enter days kept: "; cin >> days;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        copies++;
        if (days > 5) cout << "Fine: Rs." << (days-5)*20 << "\n";
        else cout << "Returned successfully.\n";
    }
};

int main() {
    int choice;
    vector<LibraryItem*> items;

    do {
        cout << "\n=== Smart Campus Management System BY [24CSE40]===\n";
        cout << "1. Add Student\n2. Show All Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Mark Attendance \n";
        cout << "7. Add Faculty\n8. Show All Faculty\n";
        cout << "9. Library (Add/Issue/Return/List)\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string id, name, dept, contact;
            cout << "Enter ID: "; getline(cin, id);
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Dept: "; getline(cin, dept);
            cout << "Enter Contact: "; getline(cin, contact);
            Student(id,name,dept,contact).saveToFile();
        }
        else if (choice == 2) {
            Student::showAll();
        }
        else if (choice == 3) {
            string id; cout << "Enter ID: "; getline(cin, id);
            Student::searchStudent(id);
        }
        else if (choice == 4) {
            string id; cout << "Enter ID to update: "; getline(cin, id);
            Student::updateStudent(id);
        }
        else if (choice == 5) {
            string id; cout << "Enter ID to delete: "; getline(cin, id);
            Student::deleteStudent(id);
        }
        else if (choice == 6) {
            Attendance::markAttendance("students.txt","attendance.txt");
        }
        else if (choice == 7) {
            string id, name, dept, contact;
            cout << "Enter ID: "; getline(cin, id);
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Dept: "; getline(cin, dept);
            cout << "Enter Contact: "; getline(cin, contact);
            Faculty(id,name,dept,contact).saveToFile();
        }
        else if (choice == 8) {
            Faculty::showAll();
        }
        else if (choice == 9) {
            int lc;
            cout << "\n--- Library Menu ---\n"
                 << "1. Add Book\n2. Add Magazine\n3. Add CD\n"
                 << "4. List Items\n5. Issue by Index\n6. Return by Index\n0. Back\n"
                 << "Choice: ";
            cin >> lc;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (lc == 1 || lc == 2 || lc == 3) {
                string isbn, title, author; int copies;
                cout << "ISBN: ";   getline(cin, isbn);
                cout << "Title: ";  getline(cin, title);
                cout << "Author: "; getline(cin, author);
                cout << "Copies: "; cin >> copies;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (lc == 1) items.push_back(new Book(isbn,title,author,copies));
                else if (lc == 2) items.push_back(new Magazine(isbn,title,author,copies));
                else items.push_back(new CD(isbn,title,author,copies));
                cout << "Item added.\n";
            }
            else if (lc == 4) {
                if (items.empty()) cout << "No items.\n";
                else {
                    for (size_t i=0;i<items.size();++i) {
                        cout << i << ") "; items[i]->showDetails(); cout << "\n";
                    }
                }
            }
            else if (lc == 5) {
                if (items.empty()) { cout << "No items.\n"; continue; }
                size_t idx; cout << "Enter index to issue: "; cin >> idx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (idx < items.size()) items[idx]->issueItem();
                else cout << "Invalid index.\n";
            }
            else if (lc == 6) {
                if (items.empty()) { cout << "No items.\n"; continue; }
                size_t idx; cout << "Enter index to return: "; cin >> idx;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (idx < items.size()) items[idx]->returnItem();
                else cout << "Invalid index.\n";
            }
        }

    } while (choice != 0);

    for (auto* p : items) delete p;

    cout << "Goodbye!\n";
    return 0;
}
