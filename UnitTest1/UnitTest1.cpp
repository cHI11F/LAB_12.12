#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.12/LAB_12.12.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // Тест для методу addEmployee
        TEST_METHOD(TestAddEmployee)
        {
            BinaryTree phoneBook;
            Employee emp = { "Smith", "01", "101" };
            phoneBook.addEmployee(emp);

            Employee* result = phoneBook.searchByPhoneNumber("01");
            Assert::IsNotNull(result);
            Assert::AreEqual(string("Smith"), result->lastName);
            Assert::AreEqual(string("101"), result->roomNumber);
        }

        // Тест для методу deleteEmployee
        TEST_METHOD(TestDeleteEmployee)
        {
            BinaryTree phoneBook;
            Employee emp = { "Smith", "01", "101" };
            phoneBook.addEmployee(emp);
            phoneBook.deleteEmployee("01");

            Employee* result = phoneBook.searchByPhoneNumber("01");
            Assert::IsNull(result);
        }

        // Тест для методу searchByPhoneNumber
        TEST_METHOD(TestSearchByPhoneNumber)
        {
            BinaryTree phoneBook;
            Employee emp = { "Smith", "01", "101" };
            phoneBook.addEmployee(emp);

            Employee* result = phoneBook.searchByPhoneNumber("01");
            Assert::IsNotNull(result);
            Assert::AreEqual(string("Smith"), result->lastName);
            Assert::AreEqual(string("101"), result->roomNumber);

            Employee* notFound = phoneBook.searchByPhoneNumber("02");
            Assert::IsNull(notFound);
        }

        // Тест для методу saveToFile та readFromFile
        TEST_METHOD(TestSaveAndReadFromFile)
        {
            BinaryTree phoneBook;
            Employee emp1 = { "Smith", "01", "101" };
            Employee emp2 = { "Johnson", "02", "102" };
            phoneBook.addEmployee(emp1);
            phoneBook.addEmployee(emp2);

            string filename = "testfile.txt";
            phoneBook.saveToFile(filename);

            BinaryTree newPhoneBook;
            newPhoneBook.readFromFile(filename);

            Employee* result1 = newPhoneBook.searchByPhoneNumber("01");
            Assert::IsNotNull(result1);
            Assert::AreEqual(string("Smith"), result1->lastName);
            Assert::AreEqual(string("101"), result1->roomNumber);

            Employee* result2 = newPhoneBook.searchByPhoneNumber("02");
            Assert::IsNotNull(result2);
            Assert::AreEqual(string("Johnson"), result2->lastName);
            Assert::AreEqual(string("102"), result2->roomNumber);
        }
    };
}

