#include <iostream>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

char cyclicLeftShift(char ch, int shift) {
    unsigned char byte = static_cast<unsigned char>(ch);
    shift %= 8; // обмеження до 8 бітів
    return static_cast<char>(((byte << shift) | (byte >> (8 - shift))) & 0xFF);
}
char cyclicRightShift(char ch, int shift) {
    unsigned char byte = static_cast<unsigned char>(ch);
    shift %= 8;
    return static_cast<char>(((byte >> shift) | (byte << (8 - shift))) & 0xFF);
}

// Функція шифрування рядка
string encryptString(const string& input, int shift) {
    string result;
    for (char ch : input) {
        result += cyclicLeftShift(ch, shift);
    }
    return result;
}
string decryptString(const string& input, int shift) {
    string result;
    for (char ch : input) {
        result += cyclicRightShift(ch, shift);
    }
    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    string text;
    int shift;

    cout << "Введіть рядок: ";
    getline(cin, text);
    cout << "Введіть величину зсуву (0-7): ";
    while (!(cin >> shift) || shift < 0 || shift > 7) {
        cout << "Некоректний зсув. Введіть число від 0 до 7: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // ШИФРУВАННЯ
    string encrypted = encryptString(text, shift);
    cout << "\nЗашифрований рядок: " << encrypted << endl;

    // ДЕШИФРУВАННЯ
    string decrypted = decryptString(encrypted, shift);
    cout << "Дешифрований рядок: " << decrypted << endl;

    return 0;
}