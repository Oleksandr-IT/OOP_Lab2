#include <iostream>
#include <string>
#include <bitset>
#include <clocale>
using namespace std;
#include "Examples.h"

void MenuExamples() {
	cout << "\n===== OOP Lab 2: Bitwise Operations =====\n";
	cout << "1.  Task 2.1: Calculate expression using bitwise operations\n";
	cout << "2.  Task 2.2: Encode text with bit-field structure and parity\n";
	cout << "3.  Task 2.3: Encode text with union and parity bits\n";
	cout << "4.  Task 2.4: Encrypt string using cyclic left shift\n";
	cout << "5.  Exit\n";
	cout << "Select option: ";
}

void Examples()
{
	setlocale(LC_ALL, "uk_UA.UTF-8");
	char ch = '0';
	do {
		MenuExamples();
		cin >> ch;
		cin.ignore();

		switch (ch) {
		case '1': Example1(); break;
		case '2': Example2(); break;
		case '3': Example3(); break;
		case '4': Example4(); break;
		case '5': return;
		default: cout << "Invalid option\n";
		}
	} while (ch != '5');
}

// Task 2.1: Calculate expression using bitwise operations
void Example1()
{
	int a, b, c, d, x, y;
	cout << "x = b + (b<<5) + (((d<<4)-d+(a<<3)+(a<<2))>>9) - (c+(c<<6)) + (d<<1) + (d<<3) + (d<<2)\n";
	cout << "Enter a b c d: ";
	cin >> a >> b >> c >> d;
	
	x = b + (b << 5) + (((d << 4) - d + (a << 3) + (a << 2)) >> 9) - (c + (c << 6)) + (d << 1) + (d << 3) + (d << 2);
	y = 33 * b + ((15 * d + 12 * a) / 512) - 65 * c + 14 * d;
	
	cout << "Result (bitwise): x = " << x << "\n";
	cout << "Result (normal):  y = " << y << "\n";
	cin.ignore();
	cout << "Press Enter to continue...\n";
	cin.get();
}

// Task 2.2: Encode text using bit-field structure
struct TextCode {
	unsigned short schkb : 4;
	unsigned short posrow : 7;
	unsigned short mchkb : 4;
	unsigned short bitp : 1;
};

unsigned char pbit(unsigned char c)
{
	unsigned char t = 1, b = 0;
	for (int j = 0; j < 8; j++) {
		if (c & t) {
			b = (b == 0) ? 1 : 0;
		}
		t <<= 1;
	}
	return b;
}

void Example2()
{
	char S[65];
	TextCode Rez[64];
	cout << "Введіть рядок: ";
	cin.getline(S, 64);
	
	int n = strlen(S);
	for (int i = n; i < 64; i++) S[i] = '\0';

	for (int i = 0; i < 64; i++) {
		unsigned char c = S[i];
		Rez[i].schkb = c >> 4;
		Rez[i].mchkb = c & 0x0f;
		Rez[i].posrow = i;
		unsigned char r = pbit(c);
		unsigned char t = pbit(static_cast<unsigned char>(i));
		Rez[i].bitp = r ^ t;
	}

	cout << "Encoded data (hex):\n";
	for (int i = 0; i < 64; i++) {
		cout << hex << *(unsigned short*)&Rez[i] << " ";
		if ((i + 1) % 16 == 0) cout << "\n";
	}
	cout << dec << "\n";
	cout << "Press Enter to continue...\n";
	cin.get();
}

// Task 2.3: Encode text using union and parity
struct EncodedChar {
	unsigned int parity : 1;
	unsigned int ascii : 8;
	unsigned int pos : 7;
};

union CharUnion {
	EncodedChar fields;
	uint16_t fullValue;
};

int calculateParity(uint16_t value)
{
	int count = 0;
	for (int i = 1; i < 16; i++) {
		if (value & (1 << i)) count++;
	}
	return count % 2;
}

void Example3()
{
	string text;
	cout << "Enter string (max 128 characters): ";
	getline(cin, text);

	if (text.size() < 128) {
		text.append(128 - text.size(), ' ');
	} else if (text.size() > 128) {
		text = text.substr(0, 128);
	}

	CharUnion encoded[128];

	for (size_t i = 0; i < text.size(); i++) {
		encoded[i].fields.ascii = static_cast<unsigned char>(text[i]);
		encoded[i].fields.pos = i;
		encoded[i].fields.parity = 0;
		encoded[i].fields.parity = calculateParity(encoded[i].fullValue);
	}

	cout << "Encoded data (16 bits):\n";
	for (size_t i = 0; i < text.size(); i++) {
		cout << bitset<16>(encoded[i].fullValue) << " ";
		if ((i + 1) % 8 == 0) cout << "\n";
	}
	cout << "\nPress Enter to continue...\n";
	cin.get();
}

// Task 2.4: Encrypt string using cyclic left shift
char cyclicLeftShift(char ch, int shift)
{
	unsigned char byte = static_cast<unsigned char>(ch);
	shift %= 8;
	return static_cast<char>(((byte << shift) | (byte >> (8 - shift))) & 0xFF);
}

string encryptString(const string& input, int shift)
{
	string result;
	for (char ch : input) {
		result += cyclicLeftShift(ch, shift);
	}
	return result;
}

void Example4()
{
	string text;
	int shift;
	cout << "Enter string: ";
	getline(cin, text);
	cout << "Enter shift amount (0-7): ";
	cin >> shift;
	cin.ignore();

	string encrypted = encryptString(text, shift);
	cout << "Original:  " << text << "\n";
	cout << "Encrypted: " << encrypted << "\n";
	cout << "Press Enter to continue...\n";
	cin.get();
}
