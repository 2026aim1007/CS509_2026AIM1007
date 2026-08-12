#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Automatically handles the specific assignment logic and compilation
void handleAssignment(const string& folderName, const string& menuTitle, const string& options, int maxChoice) {
    int algoChoice;
    do {
        clearScreen();
        cout << "-------------------------------------------------\n";
        cout << "              " << menuTitle << "                  \n";
        cout << "-------------------------------------------------\n";
        cout << options;
        cout << "9. Compile this Assignment\n";
        cout << "0. Go Back\n";
        cout << "Enter choice: ";
        cin >> algoChoice;

        if (algoChoice > 0 && algoChoice <= maxChoice) {
            int modeChoice;
            cout << "\nSelect Execution Mode:\n";
            cout << "0 - Run Once (Standard execution)\n";
            cout << "1 - Test Mode (Average of 5 runs)\n";
            cout << "Enter choice (0 or 1): ";
            cin >> modeChoice;

            string command = "cd ../" + folderName + " && .\\driver_app.exe " + to_string(algoChoice) + " ALL";
            if (modeChoice == 1) {
                command += " --test";
            }

            cout << "\n[System] Executing: " << command << "\n\n";
            system(command.c_str());
            pauseScreen();
        } 
        else if (algoChoice == 9) {
            cout << "\n[System] Compiling " << folderName << "...\n";
            string compileCmd = "cd ../" + folderName + " && mingw32-make";
            system(compileCmd.c_str());
            pauseScreen();
        }
        else if (algoChoice != 0) {
            cout << "\n[!] Invalid choice.\n";
            pauseScreen();
        }
    } while (algoChoice != 0);
}

int main() {
    int mainChoice;
    do {
        clearScreen();
        cout << "=================================================\n";
        cout << "      CS509 Solo Repository Common Wrapper       \n";
        cout << "=================================================\n";
        cout << "1. Assignment 01 (GEMM Simple, GEMM Blocking)\n";
        cout << "2. Assignment 02 (Bellman-Ford, Floyd-Warshall)\n";
        cout << "3. Compile All Assignments (Global Makefile)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                handleAssignment("assignment_01", "Assignment 01 Menu", 
                                 "1. GEMM Simple\n2. GEMM Blocking\n", 2);
                break;
            case 2:
                handleAssignment("assignment_02", "Assignment 02 Menu", 
                                 "1. Bellman-Ford (BF)\n2. Floyd-Warshall (FW)\n", 2);
                break;
            case 3:
                cout << "\n[System] Compiling all assignments from root directory...\n";
                // Moves to the main root folder and triggers the global Makefile
                system("cd .. && mingw32-make");
                pauseScreen();
                break;
            case 0:
                cout << "\nExiting wrapper. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please try again.\n";
                pauseScreen();
                break;
        }
    } while (mainChoice != 0);

    return 0;
}