#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Employee {
    string lastName;
    string phoneNumber;
    string roomNumber;
};

struct TreeNode {
    Employee employee;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Employee& emp) : employee(emp), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void insert(TreeNode*& node, const Employee& emp) {
        if (node == nullptr) {
            node = new TreeNode(emp);
        }
        else if (emp.phoneNumber < node->employee.phoneNumber) {
            insert(node->left, emp);
        }
        else {
            insert(node->right, emp);
        }
    }

    void remove(TreeNode*& node, const string& phoneNumber) {
        if (node == nullptr) return;

        if (phoneNumber < node->employee.phoneNumber) {
            remove(node->left, phoneNumber);
        }
        else if (phoneNumber > node->employee.phoneNumber) {
            remove(node->right, phoneNumber);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                TreeNode* temp = findMin(node->right);
                node->employee = temp->employee;
                remove(node->right, temp->employee.phoneNumber);
            }
        }
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    TreeNode* search(TreeNode* node, const string& phoneNumber) const {
        if (node == nullptr || node->employee.phoneNumber == phoneNumber) {
            return node;
        }
        else if (phoneNumber < node->employee.phoneNumber) {
            return search(node->left, phoneNumber);
        }
        else {
            return search(node->right, phoneNumber);
        }
    }

    void inorderSave(TreeNode* node, ofstream& fout) const {
        if (node != nullptr) {
            inorderSave(node->left, fout);
            fout << node->employee.lastName << " " << node->employee.phoneNumber << " " << node->employee.roomNumber << endl;
            inorderSave(node->right, fout);
        }
    }

    void clear(TreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clear(root);
    }

    void addEmployee(const Employee& emp) {
        insert(root, emp);
    }

    void deleteEmployee(const string& phoneNumber) {
        remove(root, phoneNumber);
    }

    Employee* searchByPhoneNumber(const string& phoneNumber) const {
        TreeNode* node = search(root, phoneNumber);
        if (node == nullptr) return nullptr;
        return &node->employee;
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename);
        if (!fout.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        inorderSave(root, fout);
        fout.close();
    }

    void readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        clear(root);
        root = nullptr;

        Employee employee;
        string phoneNumber;
        while (fin >> employee.lastName >> phoneNumber >> employee.roomNumber) {
            employee.phoneNumber = phoneNumber;
            addEmployee(employee);
        }
        fin.close();
    }
};

string filename;

void addEmployee(BinaryTree& phoneBook) {
    Employee newEmployee;
    cout << "Enter last name: ";
    cin >> newEmployee.lastName;
    cout << "Enter phone number (two digits): ";
    cin >> newEmployee.phoneNumber;
    cout << "Enter room number: ";
    cin >> newEmployee.roomNumber;

    phoneBook.addEmployee(newEmployee);
}

void deleteEmployee(BinaryTree& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number to delete: ";
    cin >> phoneNumber;

    phoneBook.deleteEmployee(phoneNumber);
    cout << "Employee with phone number " << phoneNumber << " deleted successfully." << endl;
}

void printEmployeeByPhoneNumber(const BinaryTree& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    Employee* employee = phoneBook.searchByPhoneNumber(phoneNumber);
    if (employee != nullptr) {
        cout << "Last name: " << employee->lastName << ", Room number: " << employee->roomNumber << endl;
    }
    else {
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }
}

void savePhoneBookToFile(const BinaryTree& phoneBook) {
    phoneBook.saveToFile(filename);
    cout << "Phone book has been saved to file: " << filename << endl;
}

void readPhoneBookFromFile(BinaryTree& phoneBook) {
    phoneBook.readFromFile(filename);
    cout << "Phone book has been read from file: " << filename << endl;
}

int main() {
    BinaryTree phoneBook;

    cout << "Enter filename: ";
    getline(cin, filename);

    readPhoneBookFromFile(phoneBook);

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Delete employee" << endl;
        cout << "3. Print employee by phone number" << endl;
        cout << "4. Save phone book to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            addEmployee(phoneBook);
            break;
        case 2:
            deleteEmployee(phoneBook);
            break;
        case 3:
            printEmployeeByPhoneNumber(phoneBook);
            break;
        case 4:
            savePhoneBookToFile(phoneBook);
            break;
        case 5:
            cout << "Exiting program." << endl;
            savePhoneBookToFile(phoneBook);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    }

    return 0;
}
