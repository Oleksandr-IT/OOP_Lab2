#include <iostream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

// Функція для обчислення біта парності (парність по 15 бітах)
int calculateParity(uint16_t value) {
    int count = 0;
    for (int i = 0; i < 15; i++) {
        if (value & (1 << i)) count++;
    }
    return count % 2; // 0 - парна кількість, 1 - непарна
}

int main() {
    string text;
    cout << "Введіть текст (до 128 символів): ";
    getline(cin, text);

    // Доповнення пробілами до 128 символів
    if (text.size() < 128) {
        text.append(128 - text.size(), ' ');
    } else if (text.size() > 128) {
        text = text.substr(0, 128);
    }

    vector<uint16_t> encoded;

    for (size_t i = 0; i < text.size(); i++) {
        unsigned char ch = text[i];
        uint16_t value = 0;

        // Записуємо ASCII-код у біти 1-8
        value |= (static_cast<uint16_t>(ch) << 1);

        // Записуємо позицію у біти 9-15
        value |= (static_cast<uint16_t>(i) << 9);

        // Обчислюємо біт парності
        int parity = calculateParity(value);
        value |= parity; // встановлюємо 0-й біт

        encoded.push_back(value);
    }

    // Вивід результату у двійковому вигляді
    cout << "\nЗакодовані дані (по 16 біт):\n";
    for (size_t i = 0; i < encoded.size(); i++) {
        cout << bitset<16>(encoded[i]) << " ";
        if ((i + 1) % 8 == 0) cout << "\n";
    }

    return 0;
}