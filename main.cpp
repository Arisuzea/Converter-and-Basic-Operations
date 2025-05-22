// Imports
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Clears the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

// Pauses until the user presses Enter
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Converts a decimal number to a given base (2 to 16)
string convertDecimalToBase(int dec, int base) {
    if (dec == 0) return "0";
    string digits = "0123456789ABCDEF";
    string result;
    unsigned int num = dec 0<  ? -dec : dec;
    while (num > 0) {
        result.push_back(digits[num % base]);
        num /= base;
    }
    if (dec < 0) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

// Converts a number string from a given base to decimal
int convertBaseToDecimal(const string &s, int base) {
    int result = 0;
    int start = (s[0] == '-') ? 1 : 0;
    for (int i = start; i < (int)s.size(); i++) {
        char c = toupper(s[i]);
        int value = isdigit(c) ? c - '0' : c - 'A' + 10;
        result = result * base + value;
    }
    return (s[0] == '-') ? -result : result;
}

// Handles and validates integer input from user
int getIntInput() {
    int x;
    while (true) {
        if (cin >> x) return x;
        cout << "Invalid input. Please enter a proper number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Handles and validates string input from user
string getStringInput() {
    string s;
    while (true) {
        if (cin >> s) return s;
        cout << "Invalid input. Please enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Maps base names to their corresponding numeric values
int getBaseFromName(const string& name) {
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    if (lowerName == "binary") return 2;
    if (lowerName == "octal") return 8;
    if (lowerName == "decimal") return 10;
    if (lowerName == "hexadecimal") return 16;
    return -1;
}

int main() {
    clearScreen();
    while (true) {
        cout << "Select mode:\n";
        cout << "1) Conversion (show all other bases)\n";
        cout << "2) Basic Operations (binary or octal only)\n";
        cout << "3) Exit\n";
        cout << "Choice: ";
        int mode = getIntInput();

        if (mode == 3) {
            clearScreen();
            cout << "Exiting program.\n";
            break;
        }

        if (mode == 1) {
            clearScreen();
            cout << "Conversion Mode:\n";
            cout << "Enter source base (binary, octal, decimal, hexadecimal): ";
            string srcBaseStr = getStringInput();
            int srcBase = getBaseFromName(srcBaseStr);
            if (srcBase == -1) {
                cout << "Invalid source base.\n";
                pause(); clearScreen();
                continue;
            }

            cout << "Enter number: ";
            string srcNum = getStringInput();

            // Convert to decimal once
            int decimalValue;
            try {
                decimalValue = convertBaseToDecimal(srcNum, srcBase);
            } catch (...) {
                cout << "Error converting number to decimal.\n";
                pause(); clearScreen();
                continue;
            }

            // Display conversion to all other bases
            struct BaseInfo { int base; const char* name; };
            BaseInfo targets[] = {
                {2, "Binary"},
                {8, "Octal"},
                {10, "Decimal"},
                {16, "Hexadecimal"}
            };
            cout << "\nResults:\n";
            for (auto &t : targets) {
                if (t.base == srcBase) continue;
                cout << "  " << t.name << ": "
                     << convertDecimalToBase(decimalValue, t.base)
                     << "\n";
            }
        }
        else if (mode == 2) {
            clearScreen();
            cout << "Basic Operations Mode:\n";
            cout << "Select base:\n";
            cout << " 1) Binary\n";
            cout << " 2) Octal\n";
            cout << "Choice: ";
            int bmode = getIntInput();
            int base;
            const char* baseName;
            if (bmode == 1) { base = 2; baseName = "binary"; }
            else if (bmode == 2) { base = 8; baseName = "octal"; }
            else {
                cout << "Invalid choice.\n";
                pause(); clearScreen();
                continue;
            }

            cout << "Enter first " << baseName << " number: ";
            string num1Str = getStringInput();
            cout << "Enter operator (+ - * / %): ";
            char op; cin >> op;
            cout << "Enter second " << baseName << " number: ";
            string num2Str = getStringInput();

            int n1 = convertBaseToDecimal(num1Str, base);
            int n2 = convertBaseToDecimal(num2Str, base);
            int resultVal;
            bool ok = true;
            switch (op) {
                case '+': resultVal = n1 + n2; break;
                case '-': resultVal = n1 - n2; break;
                case '*': resultVal = n1 * n2; break;
                case '/':
                    if (n2 == 0) {
                        cout << "Cannot divide by zero.\n"; ok = false;
                    } else resultVal = n1 / n2;
                    break;
                case '%':
                    if (n2 == 0) {
                        cout << "Cannot modulo by zero.\n"; ok = false;
                    } else resultVal = n1 % n2;
                    break;
                default:
                    cout << "Invalid operator.\n"; ok = false;
            }

            if (!ok) {
                pause(); clearScreen();
                continue;
            }

            // Display result in same base
            cout << "\nResult in " << baseName << ": "
                 << convertDecimalToBase(resultVal, base)
                 << "\n";
        }
        else {
            cout << "Invalid mode.\n";
        }

        pause();
        clearScreen();
    }
    return 0;
}
