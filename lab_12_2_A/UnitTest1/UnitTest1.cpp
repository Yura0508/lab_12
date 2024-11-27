#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12_2_A/lab_12_2_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestPrintStudentAverage)
        {
            // Створюємо тестовий файл
            string testFilename = "test_students.dat";
            int N = 2; // кількість студентів

            Student students[2] = {
                { "Іваненко", 1, INFORMATIKA, { 5, 4, 3 } },
                { "Петренко", 2, COMPUTER_SCIENCE, { 3, 3, 4 } }
            };

            // Запис даних у файл
            ofstream outFile(testFilename, ios::binary);
            outFile.write(reinterpret_cast<const char*>(&N), sizeof(N));
            for (int i = 0; i < N; i++) {
                size_t length = students[i].prizv.size();
                outFile.write((char*)&length, sizeof(length)); // записуємо довжину прізвища
                outFile.write(students[i].prizv.c_str(), length); // записуємо прізвище
                outFile.write((char*)&students[i].kurs, sizeof(students[i].kurs)); // записуємо курс
                outFile.write((char*)&students[i].spec, sizeof(students[i].spec)); // записуємо спеціальність
                outFile.write((char*)&students[i].subject, sizeof(students[i].subject)); // записуємо оцінки
            }
            outFile.close();

            // Перенаправлення виводу у stringstream для перевірки результату
            streambuf* origCoutStreamBuf = cout.rdbuf();
            stringstream testOutput;
            cout.rdbuf(testOutput.rdbuf());

            // Виклик функції
            PrintStudentAverage(testFilename);

            // Відновлення оригінального потоку
            cout.rdbuf(origCoutStreamBuf);

            // Зчитуємо вивід
            string actualOutput = testOutput.str();

            // Перевірка ключових частин виводу
            Assert::IsTrue(actualOutput.find("Іваненко") != string::npos, L"Вивід не містить прізвище 'Іваненко'");
            Assert::IsTrue(actualOutput.find("4") != string::npos, L"Вивід не містить середній бал 4.00 для 'Іваненко'");
            Assert::IsTrue(actualOutput.find("Петренко") != string::npos, L"Вивід не містить прізвище 'Петренко'");
            Assert::IsTrue(actualOutput.find("3.3") != string::npos, L"Вивід не містить середній бал 3.33 для 'Петренко'");
        }
	};
}
