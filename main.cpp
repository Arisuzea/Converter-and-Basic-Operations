// This program is a console-based number system converter and simple calculator.
// It supports converting numbers between binary, octal, decimal, and hexadecimal bases,
// and can perform basic arithmetic operations (+, -, *, /, %) on binary or octal numbers.
//
// The logic involves:
// ⋆ Parsing and validating input numbers according to their base.
// ⋆ Converting numbers from any supported base to decimal for calculations or conversions.
// ⋆ Converting results back from decimal to the desired base for display.
// ⋆ Handling edge cases such as negative numbers and invalid inputs.
// ⋆ Providing a user-friendly menu with input validation and error handling.

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdexcept>

using namespace std;

// Clears the console screen depending on the OS.
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

// Waits for the user to press Enter before continuing.
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Converts a decimal (base-10) number to a string representing the number in another base.
// ⋆ Handles zero as a special case.
// ⋆ Handles negative numbers by converting the positive counterpart and adding a minus sign.
// ⋆ Repeatedly divides the absolute number by the target base, collecting remainders as digits.
// ⋆ Digits are mapped to characters '0'–'9' and 'A'–'F'.
// ⋆ Reverses the collected digits to get the final result.
string convertDecimalToBase(int dec, int base) {
    if (dec == 0) return "0";
    string digits = "0123456789ABCDEF";
    string result;
    // Handle INT_MIN safely by converting it to unsigned.
    unsigned int num = dec == numeric_limits<int>::min()
                           ? static_cast<unsigned int>(numeric_limits<int>::max()) + 1u
                           : static_cast<unsigned int>(dec < 0 ? -dec : dec);
    while (num > 0) {
        result.push_back(digits[num % base]);
        num /= base;
    }
    if (dec < 0) result.push_back('-');
    reverse(result.begin(), result.end());
    return result;
}

// Converts a string number in a given base to decimal (int).
// ⋆ Checks for a negative sign at the start.
// ⋆ For each digit, determines its numeric value (0-15) and ensures it's valid for the base.
// ⋆ Accumulates the decimal result by multiplying the running total by the base and adding the digit value.
// ⋆ Returns a negative number if the original string had a minus sign.
int convertBaseToDecimal(const string &s, int base) {
    if (s.empty() || s == "-") throw invalid_argument("Empty or lone minus.");
    int result = 0;
    int start = (s[0] == '-') ? 1 : 0;
    for (int i = start; i < (int)s.size(); i++) {
        char c = toupper(s[i]);
        int value;
        if (c >= '0' && c <= '9')         value = c - '0';
        else if (c >= 'A' && c <= 'F')    value = c - 'A' + 10;
        else                              throw invalid_argument("Invalid character.");
        if (value >= base)                throw invalid_argument("Digit out of range.");
        result = result * base + value;
    }
    return (s[0] == '-') ? -result : result;
}

// Checks if a string is a valid number for the specified base.
// ⋆ Rejects empty strings or just a minus sign.
// ⋆ For each character, checks if it is a digit or letter valid for bases up to 16.
// ⋆ Ensures no digit is outside the allowed range for that base
bool isValidNumber(const string &s, int base) {
    if (s.empty() || s == "-") return false;
    int start = (s[0] == '-') ? 1 : 0;
    for (int i = start; i < (int) s.size(); i++) {
        char c = toupper(s[i]);
        int value;
        if (c >= '0' && c <= '9')         value = c - '0';
        else if (c >= 'A' && c <= 'F')    value = c - 'A' + 10;
        else                              return false;
        if (value >= base)                return false;
    }
    return true;
}

// Reads and validates an integer input from the user.
int getIntInput() {
    int x;
    while (true) {
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "Invalid input. Please enter a proper number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads a string input from the user.
string getStringInput() {
    string s;
    while (true) {
        if (cin >> s) return s;
        cout << "Invalid input. Please enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Converts a base name string to its numeric base value.
int getBaseFromName(const string& name) {
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    if (lowerName == "binary")      return 2;
    if (lowerName == "octal")       return 8;
    if (lowerName == "decimal")     return 10;
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
        // Conversion mode was selected
        // ⋆ Ask the base of conversion
        // ⋆ Display the base converted to the other bases.
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
            if (!isValidNumber(srcNum, srcBase)) {
                cout << "Error: `" << srcNum << "` is not valid for base " << srcBaseStr << ".\n";
                pause(); clearScreen();
                continue;
            }
            int decimalValue;
            try {
                decimalValue = convertBaseToDecimal(srcNum, srcBase);
            } catch (const exception& e) {
                cout << "Conversion error: " << e.what() << "\n";
                pause(); clearScreen();
                continue;
            }
            struct { int base; const char* name; } targets[] = {
                {2, "Binary"}, {8, "Octal"}, {10, "Decimal"}, {16, "Hexadecimal"}
            };
            cout << "\nResults:\n";
            for (auto &t : targets) {
                if (t.base == srcBase) continue;
                cout << "  " << t.name << ": " << convertDecimalToBase(decimalValue, t.base) << "\n";
            }
        }
        // Basic operation was selected
        // ⋆ Ask for the base of the operations
        // ⋆ Input num 1
        // ⋆ Num 1 gets converted to decimal
        // ⋆ Input num 2
        // ⋆ Num2 gets converted to decimal
        // ⋆ Get the sum, difference, product of quotient of the operation based on what was selected.
        // ⋆ Convert the result back to the base selected.
        else if (mode == 2) {
            clearScreen();
            cout << "Basic Operations Mode:\n";
            cout << "Select base:\n 1) Binary\n 2) Octal\nChoice: ";
            int bmode = getIntInput();
            int base = (bmode == 1 ? 2 : (bmode == 2 ? 8 : -1));
            const char* baseName = (bmode == 1 ? "binary" : (bmode == 2 ? "octal" : ""));
            if (base == -1) {
                cout << "Invalid choice.\n";
                pause(); clearScreen();
                continue;
            }

            cout << "Enter first " << baseName << " number: ";
            string num1 = getStringInput();
            if (!isValidNumber(num1, base)) {
                cout << "Error: `" << num1 << "` is not valid for " << baseName << ".\n";
                pause(); clearScreen();
                continue;
            }

            cout << "Enter operator (+ - * / %): ";
            string opStr = getStringInput();
            if (opStr.size() != 1 || string("+-*/%").find(opStr[0]) == string::npos) {
                cout << "Invalid operator.\n";
                pause(); clearScreen();
                continue;
            }
            char op = opStr[0];

            cout << "Enter second " << baseName << " number: ";
            string num2 = getStringInput();
            if (!isValidNumber(num2, base)) {
                cout << "Error: `" << num2 << "` is not valid for " << baseName << ".\n";
                pause(); clearScreen();
                continue;
            }

            int n1, n2, resultVal;
            bool ok = true;
            try {
                n1 = convertBaseToDecimal(num1, base);
                n2 = convertBaseToDecimal(num2, base);
                switch (op) {
                    case '+': resultVal = n1 + n2; break;
                    case '-': resultVal = n1 - n2; break;
                    case '*': resultVal = n1 * n2; break;
                    case '/':
                        if (n2 == 0) { cout << "Cannot divide by zero.\n"; ok = false; }
                        else resultVal = n1 / n2;
                        break;
                    case '%':
                        if (n2 == 0) { cout << "Cannot modulo by zero.\n"; ok = false; }
                        else resultVal = n1 % n2;
                        break;
                }
            } catch (...) {
                cout << "Error during operation.\n";
                ok = false;
            }

            if (!ok) {
                pause(); clearScreen();
                continue;
            }

            cout << "\nResult in " << baseName << ": "
                 << convertDecimalToBase(resultVal, base) << "\n";
        }
        else {
            cout << "Invalid mode.\n";
        }

        pause();
        clearScreen();
    }
    return 0;
}
