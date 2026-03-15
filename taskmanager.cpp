#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Task {
public:
    int id;
    string title;
    int reminderTime;

    void reminder(string taskName, int seconds) {
        this_thread::sleep_for(chrono::seconds(seconds));
        cout << "\n⏰ Reminder: Task \"" << taskName << "\" needs attention!\n";
    }

    void addTask() {
        ofstream file("tasks.txt", ios::app);

        cout << "Enter Task ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Task Title: ";
        getline(cin, title);

        cout << "Enter Reminder Time (seconds): ";
        cin >> reminderTime;

        file << id << "|" << title << "|" << reminderTime << endl;
        file.close();

        thread t(&Task::reminder, this, title, reminderTime);
        t.detach();  

        cout << "Task added with reminder!\n";
    }

    void viewTasks() {
        ifstream file("tasks.txt");
        string line;

        cout << "\n----- Task List -----\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    void deleteTask() {
        int deleteId;
        cout << "Enter Task ID to delete: ";
        cin >> deleteId;

        ifstream file("tasks.txt");
        ofstream temp("temp.txt");

        string line;

        while (getline(file, line)) {
            int tid = stoi(line.substr(0, line.find("|")));

            if (tid != deleteId) {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove("tasks.txt");
        rename("temp.txt", "tasks.txt");

        cout << "Task deleted successfully!\n";
    }
};

int main() {
    Task t;
    int choice;

    do {
        cout << "\n===== TASK MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            t.addTask();
            break;

        case 2:
            t.viewTasks();
            break;

        case 3:
            t.deleteTask();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while(choice != 4);

    return 0;
}