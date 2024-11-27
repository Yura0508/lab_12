// lab_12_2_A.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Specialnost {
    INFORMATIKA, COMPUTER_SCIENCE, MATHEMATICS_AND_ECONOMICS,
    PHYSICS_AND_INFORMATICS, TECHNICAL_EDUCATION
};

string specialnostStr[] = { "Інформатика", "Комп’ютерні науки", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    string prizv;
    int kurs;
    Specialnost spec;
    struct subject {
        int fizika;
        int matematika;
        int informatika;
    } subject;
};

void Create(const string& filename, Student* students, int N);
void Print(const string& filename);
void PrintStudentAverage(const string& filename);
double CalcPhysicsHighGrades(const string& filename);

int main() {
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N;
    cout << "Введіть кількість студентів: ";
    cin >> N;
    Student* students = new Student[N];
    string filename;

    cout << "Введіть ім'я файлу для збереження: ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - вивід середнього балу кожного студента" << endl;
        cout << " [4] - обчислення процента студентів, які отримали з фізики оцінки '5' або '4'" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl;
        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(filename, students, N);
            break;
        case 2:
            Print(filename);
            break;
        case 3:
            PrintStudentAverage(filename);
            break;
        case 4:
            double percentHighGrades;
            percentHighGrades = CalcPhysicsHighGrades(filename);
            cout << "Процент студентів, які отримали з фізики оцінки '5' або '4': " << percentHighGrades << "%" << endl;
            break;
        case 0:
            cout << "Завершення програми." << endl;
            break;
        default:
            cout << "Ви ввели помилкове значення! Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}

void Create(const string& filename, Student* students, int N) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&N), sizeof(N)); // записуємо кількість студентів

    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore();
        cout << " Прізвище: "; getline(cin, students[i].prizv);
        cout << " Курс: "; cin >> students[i].kurs;
        int spec;
        cout << " Спеціальність (0-Інформатика,1-Комп’ютерні науки,2-Математика та економіка,3-Фізика та інформатика,4-Трудове навчання): ";
        cin >> spec;
        students[i].spec = static_cast<Specialnost>(spec);
        cout << " Оцінка з фізики: "; cin >> students[i].subject.fizika;
        cout << " Оцінка з математики: "; cin >> students[i].subject.matematika;
        cout << " Оцінка з інформатики: "; cin >> students[i].subject.informatika;

        // записуємо дані студента в файл
        size_t length = students[i].prizv.size();
        outFile.write((char*)&length, sizeof(length)); // записуємо довжину прізвища
        outFile.write(students[i].prizv.c_str(), length); // записуємо прізвище
        outFile.write((char*)&students[i].kurs, sizeof(students[i].kurs)); // записуємо курс
        outFile.write((char*)&students[i].spec, sizeof(students[i].spec)); // записуємо спеціальність
        outFile.write((char*)&students[i].subject, sizeof(students[i].subject)); // записуємо оцінки
    }

    outFile.close();
}

void Print(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    int N;
    inFile.read((char*)&N, sizeof(N)); // зчитуємо кількість студентів
    cout << "=============================================================================================" << endl;
    cout << "| №   | Прізвище      | Курс |        Спеціальність     | Фізика | Математика | Інформатика |" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        size_t length;
        inFile.read((char*)&length, sizeof(length)); // зчитуємо довжину прізвища
        string prizv(length, ' ');
        inFile.read(&prizv[0], length); // зчитуємо прізвище

        int kurs;
        inFile.read((char*)&kurs, sizeof(kurs)); // зчитуємо курс

        Specialnost spec;
        inFile.read((char*)&spec, sizeof(spec)); // зчитуємо спеціальність

        struct subject {
            int fizika;
            int matematika;
            int informatika;
        } subject;
        inFile.read((char*)&subject, sizeof(subject)); // зчитуємо оцінки


        cout << "| " << setw(3) << i + 1 << " | "
            << setw(13) << prizv << " | "
            << setw(4) << kurs << " | "
            << setw(24) << specialnostStr[spec] << " | "
            << setw(6) << subject.fizika << " | "
            << setw(10) << subject.matematika << " | "
            << setw(11) << subject.informatika << " |" << endl;
    }

    cout << "=============================================================================================" << endl;
    inFile.close();
}

void PrintStudentAverage(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    int N;
    inFile.read((char*)&N, sizeof(N)); // зчитуємо кількість студентів
    cout << "=========================================" << endl;
    cout << "| Прізвище      |Середній бал студентів |" << endl;
    cout << "-----------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        size_t length;
        inFile.read((char*)&length, sizeof(length)); // зчитуємо довжину прізвища
        string prizv(length, ' ');
        inFile.read(&prizv[0], length); // зчитуємо прізвище

        int kurs;
        inFile.read((char*)&kurs, sizeof(kurs)); // зчитуємо курс

        Specialnost spec;
        inFile.read((char*)&spec, sizeof(spec)); // зчитуємо спеціальність

        struct subject {
            int fizika;
            int matematika;
            int informatika;
        } subject;
        inFile.read((char*)&subject, sizeof(subject)); // зчитуємо оцінки

        double average = (subject.fizika + subject.matematika + subject.informatika) / 3.0;
        cout << "|  " << setw(13) << prizv << "|" << setw(23) << setprecision(2) << average << "|" << endl;
    }

    cout << "=========================================" << endl;
    inFile.close();
}

double CalcPhysicsHighGrades(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return 0;
    }

    int N;
    inFile.read((char*)&N, sizeof(N)); // зчитуємо кількість студентів
    int highGradesCount = 0;

    for (int i = 0; i < N; i++) {
        size_t length;
        inFile.read((char*)&length, sizeof(length)); // зчитуємо довжину прізвища
        string prizv(length, ' ');
        inFile.read(&prizv[0], length); // зчитуємо прізвище

        int kurs;
        inFile.read((char*)&kurs, sizeof(kurs)); // зчитуємо курс

        Specialnost spec;
        inFile.read((char*)&spec, sizeof(spec)); // зчитуємо спеціальність

        struct subject {
            int fizika;
            int matematika;
            int informatika;
        } subject;
        inFile.read((char*)&subject, sizeof(subject)); // зчитуємо оцінки

        if (subject.fizika == 4 || subject.fizika == 5) {
            highGradesCount++;
        }
    }

    double percent = (highGradesCount / static_cast<double>(N)) * 100;
    inFile.close();
    return percent;
}
