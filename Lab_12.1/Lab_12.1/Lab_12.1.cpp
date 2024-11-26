#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

// Функція для створення файлу з дійсними числами
void CreateRealFile(const char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cerr << "Error: cannot create file " << fname << endl;
        return;
    }
    double number;
    char ch;
    do {
        cout << "Enter a real number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number));
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fout.close();
}

// Функція для виведення вмісту файлу на екран
void PrintRealFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cerr << "Error: cannot open file " << fname << endl;
        return;
    }
    double number;
    cout << "File content of " << fname << ":" << endl;
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << endl;
    }
    fin.close();
}

// Функція для перевірки, чи є число значенням exp(x)
bool IsExpValue(double number) {
    if (number <= 0) return false;
    double x = log(number);
    return fabs(exp(x) - number) < 1e-6; // Порівнюємо з точністю
}

// Функція для переписування чисел, які є значеннями exp(x), в інший файл
void ProcessRealFile(const char* fname, const char* gname) {
    ifstream fin(fname, ios::binary);
    ofstream fout(gname, ios::binary);
    if (!fin || !fout) {
        cerr << "Error: cannot process files" << endl;
        return;
    }
    double number;
    while (fin.read((char*)&number, sizeof(number))) {
        if (IsExpValue(number)) {
            fout.write((char*)&number, sizeof(number));
        }
    }
    fin.close();
    fout.close();
}

int main() {
    char fname[100], gname[100];

    cout << "Enter the name of the first file: ";
    cin >> fname;
    CreateRealFile(fname);
    PrintRealFile(fname);

    cout << "Enter the name of the second file: ";
    cin >> gname;
    ProcessRealFile(fname, gname);
    PrintRealFile(gname);

    return 0;
}
