#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12_1_c++/lab_12_1_c++.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestWriteExpValuesToFile)
        {
            string inputTestFile = "test_input.bin";
            string outputTestFile = "test_output.bin";

            // Створюємо вхідний файл
            ofstream inputFile(inputTestFile, ios::binary);
            double testData[] = { -5.0, 0.0, 1.0, 3.5, -10.0, 7.8, 0.0001, 10.0 };
            for (double number : testData) {
                inputFile.write((char*)&number, sizeof(number));
            }
            inputFile.close();

            // Викликаємо функцію
            writeExpValuesToFile(inputTestFile, outputTestFile);

            // Перевіряємо вміст вихідного файлу
            ifstream outputFile(outputTestFile, ios::binary);
            Assert::IsTrue(outputFile.is_open(), L"Не вдалося відкрити вихідний файл!");

            // Очікувані дані
            double expectedData[] = { 1.0, 3.5, 7.8, 0.0001, 10.0 };
            size_t expectedCount = sizeof(expectedData) / sizeof(expectedData[0]);

            // Перевіряємо, що дані збігаються
            double number;
            size_t count = 0;
            while (outputFile.read((char*)&number, sizeof(number))) {
                Assert::IsTrue(count < expectedCount, L"У вихідному файлі більше елементів, ніж очікувалося!");
                Assert::AreEqual(expectedData[count], number, 0.0001, L"Число у файлі не відповідає очікуваному!");
                count++;
            }

            Assert::AreEqual(expectedCount, count, L"Кількість чисел у файлі не відповідає очікуваній!");

            outputFile.close();
        }
	};
}
