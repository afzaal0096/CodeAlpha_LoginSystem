#include <iostream>
#include <fstream>  
#include <string>   
#include <limits> // Input errors handle karne ke liye zaroori

using namespace std;

// --- Function to Check if Username Already Exists ---
bool isUsernameTaken(string username) {
    ifstream readFile("users.txt");
    string u, p, label1, label2;

    // Agar file nahi mili, to koi masla nahi, return false
    if (!readFile.is_open()) {
        return false;
    }

    // File parhtay waqt check karna ke format sahi hai ya nahi
    while (readFile >> label1 >> u >> label2 >> p) {
        if (u == username) {
            return true; // Username mil gaya!
        }
    }
    readFile.close();
    return false;
}

// --- Function 1: Registration ---
void registerUser() {
    string username, password;

    cout << "\n--- REGISTRATION ---" << endl;
    cout << "Enter a Username: ";
    cin >> username;

    // Pehle check karo duplicate to nahi
    if (isUsernameTaken(username)) {
        cout << "\n[ERROR] Username '" << username << "' already exists! Try another one." << endl;
        return; // Wapis bhej do
    }

    cout << "Enter a Password: ";
    cin >> password;

    ofstream myFile("users.txt", ios::app);

    if (myFile.is_open()) {
        myFile << "Username: " << username << " Password: " << password << endl;
        myFile.close();
        cout << "\n[SUCCESS] Registration Successful!" << endl;
    }
    else {
        cout << "[ERROR] System error: Could not create file." << endl;
    }
}

// --- Function 2: Login ---
void loginUser() {
    string username, password, u, p, label1, label2;

    cout << "\n--- LOGIN ---" << endl;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ifstream readFile("users.txt");
    bool loginSuccess = false;

    if (readFile.is_open()) {
        while (readFile >> label1 >> u >> label2 >> p) {
            if (u == username && p == password) {
                loginSuccess = true;
                break;
            }
        }
        readFile.close();
    }

    if (loginSuccess) {
        cout << "\n**********************************" << endl;
        cout << "    WELCOME! LOGIN SUCCESSFUL!    " << endl;
        cout << "**********************************" << endl;
    }
    else {
        cout << "\n[ERROR] Invalid Username or Password." << endl;
    }
}

// --- Main Function ---
int main() {
    int choice;

    while (true) {
        cout << "\n=================================" << endl;
        cout << "   LOGIN & REGISTRATION SYSTEM   " << endl;
        cout << "=================================" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose an option (1-3): ";

        // --- CRASH PREVENTION CODE ---
        // Agar user number ki jagah 'Ali' likh de, to ye handle karega
        if (!(cin >> choice)) {
            cout << "\n[OOPS!] Please enter a NUMBER (1, 2, or 3), not text." << endl;
            cin.clear(); // Error saaf karo
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ghalat input delete karo
            continue; // Dobara poocho
        }

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
        }
        else if (choice == 3) {
            cout << "Exiting program..." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}