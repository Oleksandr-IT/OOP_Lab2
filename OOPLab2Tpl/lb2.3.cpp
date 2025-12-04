#include <iostream>
#include <string>
#include <bitset>
using namespace std;

// Структура з бітовими полями
struct EncodedChar {
    unsigned int parity : 1;    // 0-й біт
    unsigned int ascii  : 8;    // біти 1-8 (ASCII код)
    unsigned int pos    : 7;    // біти 9-15 (позиція символу)
};

// Об’єднання для доступу до 16-бітного значення
union CharUnion {
    EncodedChar fields;
    uint16_t fullValue;
};

// Функція для обчислення біта парності
int calculateParity(uint16_t value) {
    int count = 0;
    for (int i = 1; i < 16; i++) { // рахуємо біти 1-15
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

    CharUnion encoded[128];

    // Шифрування
    for (size_t i = 0; i < text.size(); i++) {
        encoded[i].fields.ascii = static_cast<unsigned char>(text[i]);
        encoded[i].fields.pos = i;
        encoded[i].fields.parity = 0; // тимчасово

        // Обчислюємо парність для 15 бітів (без біта парності)
        encoded[i].fields.parity = calculateParity(encoded[i].fullValue);
    }

    // Вивід закодованих даних
    cout << "\nЗакодовані дані (16 біт):\n";
    for (size_t i = 0; i < text.size(); i++) {
        cout << bitset<16>(encoded[i].fullValue) << " ";
        if ((i + 1) % 8 == 0) cout << "\n";
    }

    return 0;
}
