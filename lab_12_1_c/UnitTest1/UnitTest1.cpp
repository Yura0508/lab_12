
#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12_1_c/lab_12_1_c.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestWriteExpValuesToFile)
		{

			// Імена файлів для тесту
			const char* inputTestFile = "test_input.bin";
			const char* outputTestFile = "test_output.bin";

			// Підготовка тестових даних
			FILE* inputFile = fopen(inputTestFile, "wb");
			double testData[] = { -5.0, 0.0, 1.0, 3.5, -10.0, 7.8, 0.0001, 10.0 };
			for (double number : testData) {
				fwrite(&number, sizeof(double), 1, inputFile);
			}
			fclose(inputFile);

			// Викликаємо функцію, що тестується
			writeExpValuesToFile(inputTestFile, outputTestFile);

			// Читаємо результат із вихідного файлу
			FILE* outputFile = fopen(outputTestFile, "rb");
			Assert::IsNotNull(outputFile, L"Не вдалося відкрити вихідний файл!");

			// Очікуваний результат
			double expectedData[] = { 1.0, 3.5, 7.8, 0.0001, 10.0 }; // Числа, що > 0
			size_t expectedSize = sizeof(expectedData) / sizeof(expectedData[0]);

			// Перевіряємо вміст файлу
			double readNumber;
			size_t index = 0;
			while (fread(&readNumber, sizeof(double), 1, outputFile) == 1) {
				Assert::IsTrue(index < expectedSize, L"У вихідному файлі більше елементів, ніж очікувалося!");
				Assert::AreEqual(expectedData[index], readNumber, 0.0001, L"Число у файлі не відповідає очікуваному!");
				index++;
			}

			// Перевіряємо, що кількість записаних чисел збігається
			Assert::AreEqual(expectedSize, index, L"Кількість чисел у файлі не відповідає очікуваній!");

			fclose(outputFile);
		}
	};
}
