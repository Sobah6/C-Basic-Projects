#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool done = false;
};

void showMenu() {
    cout << "\n==== TO-DO LIST ====\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Done\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

void listTasks(const vector<Task>& tasks) {
    cout << "\nYour Tasks:\n";
    if (tasks.empty()) {
        cout << "No tasks yet!\n";
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].done ? 'x' : ' ') << "] " << tasks[i].description << "\n";
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();  // To clear newline after number input

        if (choice == 1) {
            cout << "Enter task description: ";
            string desc;
            getline(cin, desc);
            tasks.push_back({desc});
            cout << "Task added!\n";
        } else if (choice == 2) {
            listTasks(tasks);
        } else if (choice == 3) {
            listTasks(tasks);
            cout << "Enter task number to mark as done: ";
            int idx;
            cin >> idx;
            if (idx >= 1 && idx <= static_cast<int>(tasks.size())) {
                tasks[idx - 1].done = true;
                cout << "Task marked as done!\n";
            } else {
                cout << "Invalid task number.\n";
            }
        } else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
