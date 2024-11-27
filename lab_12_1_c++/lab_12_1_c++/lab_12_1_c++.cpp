// lab_12_1_c++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <Windows.h>
using namespace std;

// Функція для генерації файлу з дійсними числами у бінарному режимі
void generateDataFile(const string& filename, int n) {
    ofstream file(filename, ios::binary);
    
    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            double number = -10.0 + (rand() / (RAND_MAX + 1.0)) * 20.0;    // Генерація випадкового числа від -10 до 10
            file.write((char*)&number, sizeof(number));  // Запис числа у бінарному форматі
        }
        file.close();
    }
    else {
        cout << "Не вдалося створити файл!" << endl;
    }
}

// Функція для перевірки, чи може число бути значенням функції exp(x)
bool canBeExp(double number) {
    return number > 0;  // exp(x) завжди більше за 0 для всіх x
}

// Функція для переписування в новий файл значень, які можуть бути значеннями exp(x) у бінарному режимі
void writeExpValuesToFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (inputFile.is_open() && outputFile.is_open()) {
        double number;
        while (inputFile.read((char*)&number, sizeof(number))) {
            if (canBeExp(number)) {
                outputFile.write((char*)&number, sizeof(number));
            }
        }
        inputFile.close();
        outputFile.close();
    }
    else {
        cout << "Не вдалося відкрити файли!" << endl;
    }
}

// Функція для виведення вмісту файлу в бінарному режимі
void printFileContent(const string& filename) {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        double number;
        cout << fixed << setprecision(2);
        while (file.read((char*)&number, sizeof(number))) {
            cout << number << endl;
        }
        file.close();
    }
    else {
        cout << "Не вдалося відкрити файл для виведення!" << endl;
    }
}

// Основна функція
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned)time(NULL));
    string inputFilename = "data.bin";  // Вхідний файл
    string outputFilename = "exp_values.bin";  // Вихідний файл

    generateDataFile(inputFilename, 10);  // Генерація 10 дійсних чисел у файл data.bin
    cout << "Вміст вхідного файлу (data.bin):\n";
    printFileContent(inputFilename);  // Виведення вмісту вхідного файлу

    writeExpValuesToFile(inputFilename, outputFilename);  // Переписуємо числа, які можуть бути значеннями exp(x)

    cout << "\nВміст вихідного файлу (exp_values.bin):\n";
    printFileContent(outputFilename);  // Виведення вмісту вихідного файлу

    return 0;
}