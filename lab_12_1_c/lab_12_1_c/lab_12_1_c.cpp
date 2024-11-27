// lab_12_1_c.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

using namespace std;

// Функція для генерації файлу з дійсними числами у бінарному режимі
void generateDataFile(const char* filename, int n) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        cout << "Не вдалося створити файл!" << endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        double number = -10.0 + (rand() / (RAND_MAX + 1.0)) * 20.0; // Генерація випадкового числа від -10 до 10
        fwrite(&number, sizeof(double), 1, file);                  // Запис числа у бінарному форматі
    }
    fclose(file);
}

// Функція для перевірки, чи може число бути значенням функції exp(x)
int canBeExp(double number) {
    return number > 0.00; // exp(x) завжди більше за 0 для всіх x
}

// Функція для переписування в новий файл значень, які можуть бути значеннями exp(x) у бінарному режимі
void writeExpValuesToFile(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    if (inputFile == NULL || outputFile == NULL) {
        cout << "Не вдалося відкрити файли!" << endl;
        if (inputFile) fclose(inputFile);
        if (outputFile) fclose(outputFile);
        return;
    }

    double number;
    while (fread(&number, sizeof(double), 1, inputFile) == 1) {
        if (canBeExp(number)) {
            fwrite(&number, sizeof(double), 1, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

// Функція для виведення вмісту файлу в бінарному режимі
void printFileContent(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        cout << "Не вдалося відкрити файл для виведення!" << endl;
        return;
    }

    double number;
    cout << fixed << setprecision(2); // Встановлюємо початковий формат виводу
    while (fread(&number, sizeof(double), 1, file) == 1) {
        cout << number << endl;
    }

    fclose(file);
}

// Основна функція
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand((unsigned int)time(NULL));

    const char* inputFilename = "data.bin";  // Вхідний файл
    const char* outputFilename = "exp_values.bin";  // Вихідний файл

    generateDataFile(inputFilename, 10);  // Генерація 10 дійсних чисел у файл data.bin
    cout << "Вміст вхідного файлу (data.bin):" << endl;
    printFileContent(inputFilename);  // Виведення вмісту вхідного файлу

    writeExpValuesToFile(inputFilename, outputFilename);  // Переписуємо числа, які можуть бути значеннями exp(x)

    cout << "\nВміст вихідного файлу (exp_values.bin):" << endl;
    printFileContent(outputFilename);  // Виведення вмісту вихідного файлу

    return 0;
}
