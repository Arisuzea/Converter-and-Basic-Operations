#include <iostream>
#include <conio.h>
using namespace std;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nPress any key to continue...";
    getch();
}

// Conversion routines:

void decimalToOctal() {
    int d, octal = 0, i = 1, rem;
    cout << "Enter Decimal: ";
    cin >> d;
    while (d > 0) {
        rem = d % 8;
        octal += rem * i;
        d /= 8;
        i *= 10;
    }
    cout << "Octal: " << octal << endl;
}

void octalToDecimal() {
    int o, decimal = 0, i = 1, rem;
    cout << "Enter Octal: ";
    cin >> o;
    while (o > 0) {
        rem = o % 10;
        decimal += rem * i;
        o /= 10;
        i *= 8;
    }
    cout << "Decimal: " << decimal << endl;
}

void decimalToBinary() {
    int d, rem;
    string binary = "";
    cout << "Enter Decimal: ";
    cin >> d;
    while (d != 0) {
        rem = d % 2;
        binary = char(rem + '0') + binary;
        d /= 2;
    }
    cout << "Binary: " << binary << endl;
}

void binaryToDecimal() {
    int b, decimal = 0, i = 1, rem;
    cout << "Enter Binary: ";
    cin >> b;
    while (b > 0) {
        rem = b % 10;
        if (rem > 1) {
            cout << "INVALID" << endl;
            return;
        }
        decimal += rem * i;
        b /= 10;
        i *= 2;
    }
    cout << "Decimal: " << decimal << endl;
}

void decimalToHexadecimal() {
    int d, rem;
    string hex = "";
    cout << "Enter Decimal: ";
    cin >> d;
    while (d != 0) {
        rem = d % 16;
        if (rem < 10)
            hex = char(rem + '0') + hex;
        else {
            switch (rem) {
                case 10: hex = 'A' + hex; break;
                case 11: hex = 'B' + hex; break;
                case 12: hex = 'C' + hex; break;
                case 13: hex = 'D' + hex; break;
                case 14: hex = 'E' + hex; break;
                case 15: hex = 'F' + hex; break;
            }
        }
        d /= 16;
    }
    cout << "Hexadecimal: " << hex << endl;
}

void hexadecimalToDecimal() {
    char h[20];
    int decimal = 0, i = 0, value;
    cout << "Enter Hexadecimal: ";
    cin >> h;
    while (h[i]) {
        if (h[i] >= '0' && h[i] <= '9')
            value = h[i] - '0';
        else {
            switch (h[i]) {
                case 'A': value = 10; break;
                case 'B': value = 11; break;
                case 'C': value = 12; break;
                case 'D': value = 13; break;
                case 'E': value = 14; break;
                case 'F': value = 15; break;
                default:
                    cout << "INVALID DIGIT" << endl;
                    return;
            }
        }
        decimal = decimal * 16 + value;
        i++;
    }
    cout << "Decimal: " << decimal << endl;
}

// Basic operations (binary or octal only):

void basicOperations() {
    clearScreen();
    cout << "Basic Operations Mode:\n";
    cout << "1) Binary\n2) Octal\nChoice: ";
    int bmode; cin >> bmode;
    int base = (bmode == 1 ? 2 : (bmode == 2 ? 8 : -1));
    const char* bname = (bmode == 1 ? "binary" : "octal");
    if (base == -1) {
        cout << "Invalid choice.\n";
        pause();
        return;
    }

    cout << "Enter first " << bname << " number: ";
    string s1; cin >> s1;
    // validate
    for (char c : s1) if ((c < '0' || c >= '0' + base) && c != '-') {
        cout << "Invalid number.\n"; pause(); return;
    }

    cout << "Enter operator (+ - * / %): ";
    char op; cin >> op;
    if (op!='+'&&op!='-'&&op!='*'&&op!='/'&&op!='%') {
        cout << "Invalid operator.\n"; pause(); return;
    }

    cout << "Enter second " << bname << " number: ";
    string s2; cin >> s2;
    for (char c : s2) if ((c < '0' || c >= '0' + base) && c != '-') {
        cout << "Invalid number.\n"; pause(); return;
    }

    // convert to decimal
    auto toDec = [&](const string& s) {
        int val = 0, sign = 1, i = 0;
        if (s[0] == '-') { sign = -1; i = 1; }
        for (; i < (int)s.size(); ++i)
            val = val * base + (s[i] - '0');
        return sign * val;
    };
    int v1 = toDec(s1), v2 = toDec(s2), res = 0;
    bool ok = true;
    switch (op) {
        case '+': res = v1 + v2; break;
        case '-': res = v1 - v2; break;
        case '*': res = v1 * v2; break;
        case '/':
            if (v2 == 0) { cout << "Error: Division by zero.\n"; ok = false; }
            else res = v1 / v2;
            break;
        case '%':
            if (v2 == 0) { cout << "Error: Modulo by zero.\n"; ok = false; }
            else res = v1 % v2;
            break;
    }
    if (!ok) { pause(); return; }

    // convert result back
    if (res == 0) {
        cout << "Result: 0\n";
    } else {
        bool neg = res < 0;
        unsigned int u = neg ? -res : res;
        string out = "";
        while (u > 0) {
            int d = u % base;
            out = char('0' + d) + out;
            u /= base;
        }
        if (neg) out = "-" + out;
        cout << "Result: " << out << endl;
    }
    pause();
}

int main() {
    int choice;
    do {
        clearScreen();
        cout << "MAIN MENU\n";
        cout << "1. Conversion\n";
        cout << "2. Basic Operations\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        clearScreen();

        if (choice == 1) {
            int sub;
            do {
                cout << "CONVERSION MENU\n";
                cout << "1. Decimal to Octal\n";
                cout << "2. Octal to Decimal\n";
                cout << "3. Decimal to Binary\n";
                cout << "4. Binary to Decimal\n";
                cout << "5. Decimal to Hexadecimal\n";
                cout << "6. Hexadecimal to Decimal\n";
                cout << "7. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;
                clearScreen();
                switch (sub) {
                    case 1: decimalToOctal(); break;
                    case 2: octalToDecimal(); break;
                    case 3: decimalToBinary(); break;
                    case 4: binaryToDecimal(); break;
                    case 5: decimalToHexadecimal(); break;
                    case 6: hexadecimalToDecimal(); break;
                    case 7: break;
                    default: cout << "Invalid choice.\n"; break;
                }
                if (sub >= 1 && sub <= 6) pause();
                clearScreen();
            } while (sub != 7);
        }
        else if (choice == 2) {
            basicOperations();
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice.\n";
            pause();
        }
    } while (choice != 3);

    return 0;
}
