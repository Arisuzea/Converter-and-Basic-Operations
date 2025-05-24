#include <iostream>
#include <conio.h>
using namespace std;

void clearScreen() { system("cls"); }
void pause()    { cout<<"\nPress any key to continue..."; getch(); }

// Validators
bool isValid(const char* s, int base) {
    int i = 0;
    if (s[0]=='-' && s[1]) i = 1;
    for (; s[i]; ++i) {
        char c = s[i];
        if (base <= 10) {
            if (c<'0' || c>char('0'+base-1)) return false;
        } else {
            if (!((c>='0'&&c<='9') ||
                  (c>='A'&&c<char('A'+base-10)) ||
                  (c>='a'&&c<char('a'+base-10)))) return false;
        }
    }
    return i > (s[0]=='-'?1:0);
}

// String→decimal
int toDec(const char* s, int base) {
    int val=0, i=0, digit;
    bool neg=false;
    if (s[0]=='-') { neg=true; i=1; }
    for (; s[i]; ++i) {
        char c=s[i];
        if (c>='0'&&c<='9') digit=c-'0';
        else if (c>='A'&&c<='F') digit=c-'A'+10;
        else digit=c-'a'+10;
        val = val*base + digit;
    }
    return neg ? -val : val;
}

// Decimal→any base (2,8,10,16)
void fromDec(int v, int base) {
    char out[100];
    int idx=98;
    out[99]=0;
    unsigned u = v<0 ? -v : v;
    if (u==0) out[idx--]='0';
    while (u && idx>0) {
        int d = u % base;
        if (base==16 && d>=10) out[idx--]= 'A'+(d-10);
        else out[idx--]= '0'+d;
        u/=base;
    }
    if (v<0) out[idx--]='-';
    cout << &out[idx+1];
}

// Universal converter
void universalConvert() {
    clearScreen();
    cout<<"Select source base:\n"
          "1) Binary\n"
          "2) Octal\n"
          "3) Decimal\n"
          "4) Hexadecimal\n"
          "5) Back\n"
          "Choice: ";
    int src; cin>>src;
    if (src<1||src>4) return;

    int bases[5] = {0,2,8,10,16};
    const char* names[5] = {"","Binary","Octal","Decimal","Hex"};
    int srcBase = bases[src];

    char s[100];
    cout<<"Enter "<<names[src]<<" value: ";
    cin>>s;
    if (!isValid(s, srcBase)) {
        cout<<"Error: invalid "<<names[src]<<'\n';
        return;
    }
    int dec = toDec(s, srcBase);

    clearScreen();
    cout<<"Convert "<<names[src]<<" to\n";
    for (int t=1; t<=4; ++t) {
        if (t==src) continue;
        cout<<t<<") "<<names[t]<<'\n';
    }
    cout<<"Choice: ";
    int tgt; cin>>tgt;
    if (tgt<1||tgt>4||tgt==src) return;

    cout<<names[tgt]<<": ";
    fromDec(dec, bases[tgt]);
    cout<<endl;
}

void basicOperations() {
    clearScreen();
    cout << "Basic Operations Mode:\n";
    cout << "1) Binary\n2) Octal\nChoice: ";
    int bmode;
    cin >> bmode;
    int base = (bmode == 1 ? 2 : 8);
    const char* name = (bmode == 1 ? "binary" : "octal");

    char s1[100], s2[100];
    cout << "Enter first " << name << ": ";
    cin >> s1;
    if (!isValid(s1, base)) {
        cout << "Error: invalid " << name << "\n";
        return;
    }

    cout << "Operator (+ - * / %): ";
    char op;
    cin >> op;

    cout << "Enter second " << name << ": ";
    cin >> s2;
    if (!isValid(s2, base)) {
        cout << "Error: invalid " << name << "\n";
        return;
    }

    int v1 = toDec(s1, base);
    int v2 = toDec(s2, base);
    int res = 0;
    bool ok = true;

    switch (op) {
        case '+': res = v1 + v2; break;
        case '-': res = v1 - v2; break;
        case '*': res = v1 * v2; break;
        case '/':
            if (v2 == 0) { cout << "Division by zero\n"; ok = false; }
            else res = v1 / v2;
            break;
        case '%':
            if (v2 == 0) { cout << "Modulo by zero\n"; ok = false; }
            else res = v1 % v2;
            break;
        default:
            cout << "Invalid operator\n";
            ok = false;
    }
    if (!ok) return;

    // convert result back
    if (res == 0) {
        cout << "Result: 0\n";
        return;
    }
    bool neg = res < 0;
    unsigned u = neg ? -res : res;
    char out[100];
    int idx = 99;
    out[idx--] = '\0';
    while (u > 0 && idx > 0) {
        out[idx--] = (u % base) + '0';
        u /= base;
    }
    if (neg) out[idx--] = '-';
    cout << "Result: " << &out[idx + 1] << endl;
}


int main() {
    int choice;
    do {
        clearScreen();
        cout<<"MAIN MENU\n"
              "1) Convert between bases\n"
              "2) Basic Operations (bin/octal)\n"
              "3) Exit\n"
              "Choice: ";
        cin>>choice;
        clearScreen();
        if (choice==1) {
            universalConvert();
            pause();
        }
        else if (choice==2) {
            basicOperations();
            pause();
        }
    } while(choice!=3);
    return 0;
}
