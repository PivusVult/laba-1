/********************************************************************
*                   КУРС КОМПЬЮТЕРНЫЕ ТЕХНОЛОГИИ                    *
*-------------------------------------------------------------------*
* Project Type  : Win32 Console Application                         *
* Project Name  : lab3                                              *
* File Name     : lab1.cpp                                          *
* Programmer(s) : Волошин В.О., Петров Д.Л, М3О-119Б-23             *
* Modified By   :                                                   *
* Created       : 01/03/24                                          *
* Last Revision :                                                   *
* Comment(s)    :  Символьные данные                                *
********************************************************************/

#include <iostream>
#include <fstream>
#include <clocale>
#include <Windows.h>
#include <conio.h>

using namespace std;
void FuncMaxDigit(char** matrix, int m);        //Объявление функции Нахождение предложения с максимальным количеством цифр
void FuncReplaceDigit(char** matrix, int m);    //Объявление функции Замена цифр на слова

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");        //Подключение Русского языка 
    //Объявление переменных
    int line = 0;                   //Номер предложения 
    int symbol = 0;                 //Номер символа в предложении
    int numberOfLines = 0;          //Количество предложений
    int symbolOfFile = 0;           //Количество символов в файле
    char** offer;                   //Исходный текст разбитый на предложения
    char ch;                        //Буферная переменая
    char* fileText=new char[2000];  //Исходный текст
    int b;

    offer = new char* [20];                     //Выделение памяти под Исходный текст разбитый на предложения
    for (int line = 0; line < 20; line++) {
        offer[line] = new char[100];
    }

    //Выбор действия пользователя
    int choice=0;      //Значение выбора пользователя 
    cout << "Выбор действия" << endl << "1. Ввод текста с файла" << endl << "2. Ввод текста с клавиатуры" << endl;
    cin >> choice;


    if (choice == 1) {              //Взятие текста из файла
        //Тесты. Подключение файла
        //const char* FILENAME = "Текст1.txt";        //Несколько предложений с максимальным количеством цифр
        //const char* FILENAME = "Текст2.txt";      //Предложение не оканчивается точкой
        //const char* FILENAME = "Текст3.txt";      //В тексте нет цифр
        const char* FILENAME = "Текст4.txt";      //Текст не имеет ошибок

        ifstream fin(FILENAME); // объявление файловой переменной и открытие файла для чтения
        if (!fin)  // Проврка на существовние исходного файла
        {
            cout << "Файл " << FILENAME << " не найден" << endl;
            return 1; // выход по ошибке
        }

        if (fin.peek() == EOF) // Проверка на пустой файл
        {
            cout << "Файл " << FILENAME << " пуст" << endl;
            fin.close();    // закрыть файл
            return 2;       // выход по ошибке
        }

        //Чтение из файла
        while (fin.get(ch)) {
            fileText[symbolOfFile] = ch;
            symbolOfFile++;
        }
    }
    else if (choice == 2) {         //Взятие текста от пользователя
        cout << "Введите текст" << endl;
        //Ввод текста
        while (true) {
            b = _getch();
            fileText[symbolOfFile] = (char)b;
            cout << fileText[symbolOfFile];
            symbolOfFile++;
            //Если пользователь нажал ENTER- завершение печати
            if(b==13){
                break;
            }
        }
        symbolOfFile--;

        
    }
    else {      //Введено не корректное значение
        cout << "Введено не корректное значение" << endl;
        return 4;
    }


    int xd = 0;         //Переменая отвечающая за номер массива

    //Разбитие исходного текста на предложения
    while (xd < symbolOfFile) {
        offer[line][symbol] = fileText[xd];
        symbol++;
        //Проверка на окончание предложения и начало нового
        if (offer[line][symbol - 1] == '.') {
            offer[line][symbol] = 0;
            line++;
            symbol = 0;
        }
        xd++;
    }

    //Проверка на окончание точкой
    if (symbol != 0) {  
        cout << "Файл не оканчивается точкой";
        return 3;// выход по ошибке
    }



    //Вывод исходного массива
    cout << "Исходные предложения: ";
    symbol = 0;
    numberOfLines = line;
    for (int line = 0; line < numberOfLines; line++) {
        while (offer[line][symbol] != 0) {

            cout << offer[line][symbol];
            symbol++;
        }
        symbol = 0;
    }

    cout << endl;

    //Вызов функции Нахождение предложения с максимальным количеством цифр
    FuncMaxDigit(offer, numberOfLines);

    return 0;
}

void FuncMaxDigit(char** matrix,int numberOfLines) {      //Функция Нахождение предложения с максимальным количеством цифр
    char numbres[10] = { '0','1','2','3','4','5','6','7','8','9' };     //Массив возможных цифр
    int max = 0;        //Максимальное количество цифр в предложениях
    int maxNumber = 0;  //Номер массива с максимальным количеством элементов
    int symbol = 0;          //Номер символа в предложении   
    int maxNow = 0;     //Количество цифр в предложении 
    int maxKolvo = 0;     //Количество предложений с максимальным количеством цифр

    //Выявление предложения с максимальным количеством цифр
    for (int line = 0; line < numberOfLines; line++) {              
        for (int digit = 0; digit < 10; digit++) {
            while (matrix[line][symbol] != 0) {         //Подсчет цифр в предложении
                if (matrix[line][symbol] == numbres[digit]) {
                    maxNow++;
                }
                symbol++;
            }
            symbol = 0;

        }

        //Проверка цифр с максимальным количеством цифр
        if (maxNow > max) {         
            max = maxNow;
            maxNumber = line;
        }
        maxNow = 0;
    }

    //Проверка на существование цифр в файле
    if (max == 0) {                 
        cout << "В файле нет чисел";
        return;
    }

    //Проверка на существование нескольких предложений с максимальным количеством цифр
    for (int line = 0; line < numberOfLines; line++) {       
        for (int digit = 0; digit < 10; digit++) {
            while (matrix[line][symbol] != 0) {
                if (matrix[line][symbol] == numbres[digit]) {
                    maxNow++;
                }
                symbol++;
            }
            symbol = 0;

        }
        if (maxNow == max) {
            maxKolvo++;
        }
        maxNow = 0;
    }

    //Вывод существования нескольких предложений с максимальным количеством цифр
    if (maxKolvo != 1) {        
        cout << "В файле несколько предложений с максимальным количеством чисел";
        return;
    }

    //Вызов функции Замена цифр на слова
    FuncReplaceDigit(matrix, numberOfLines);      
    cout << endl;

    cout << "Предложение с максимальным количеством цифр:";

    symbol = 0;
    //Вывод предложения с максимальным количеством цифр
    while (matrix[maxNumber][symbol] != 0) {     

         cout << matrix[maxNumber][symbol];
         symbol++;
    }
}


void FuncReplaceDigit(char** matrix, int numberOfLines) {       //Функции Нахождение предложения с максимальным количеством цифр
    int numberSymbols[20];       //Количество символов в предложении
    int symbol = 0;              //Номер предложения

    //Подсчет символов в предложении
    for (int line = 0; line < numberOfLines; line++) {       
        while (matrix[line][symbol] != 0) {

            symbol++;
        }
        numberSymbols[line] = symbol - 1;
        symbol = 0;
    }

    char numbres[10] = { '0','1','2','3','4','5','6','7','8','9' };//Массив возможных цифр
    char a;     //Буферная переменная
    symbol = 0;
    int nowSize = 0;  //Актуальный размер предложения

    //Замена цифр на слова
    for (int line = 0; line < numberOfLines; line++) {      
        for (int digit = 0; digit < 10; digit++) {
            while (matrix[line][symbol] != 0) {
                //Проверка является ли символ цифрой
                if (matrix[line][symbol] == numbres[digit]) {
                    a = numbres[digit];
                    switch (a)
                    {
                    case '0':       //Символ равен 0
                        numberSymbols[line] = numberSymbols[line] + 3;          //Увеличение размера предложения
                        nowSize = numberSymbols[line];                          
                        matrix[line][nowSize + 1] = 0;                          //Обозначения нового конца предложения

                        //Перенос всех символов стоящих справа от числа на 3 символа вправо
                        while (nowSize - 3 != symbol) {                        
                            matrix[line][nowSize] = matrix[line][nowSize - 3];
                            nowSize--;
                        }
                        //Замена цифры на буквы
                        matrix[line][symbol] = 'н';
                        matrix[line][symbol + 1] = 'о';
                        matrix[line][symbol + 2] = 'л';
                        matrix[line][symbol + 3] = 'ь';
                        break;
                    case '1':       //Символ равен 1
                        numberSymbols[line] = numberSymbols[line] + 3;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 3 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 3];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'о';
                        matrix[line][symbol + 1] = 'д';
                        matrix[line][symbol + 2] = 'и';
                        matrix[line][symbol + 3] = 'н';
                        break;
                    case '2':       //Символ равен 2
                        numberSymbols[line] = numberSymbols[line] + 2;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 2 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 2];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'д';
                        matrix[line][symbol + 1] = 'в';
                        matrix[line][symbol + 2] = 'а';
                        break;
                    case '3':       //Символ равен 3
                        numberSymbols[line] = numberSymbols[line] + 2;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 2 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 2];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'т';
                        matrix[line][symbol + 1] = 'р';
                        matrix[line][symbol + 2] = 'и';
                        break;
                    case '4':       //Символ равен 4
                        numberSymbols[line] = numberSymbols[line] + 5;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 5 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 5];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'ч';
                        matrix[line][symbol + 1] = 'е';
                        matrix[line][symbol + 2] = 'т';
                        matrix[line][symbol + 3] = 'ы';
                        matrix[line][symbol + 4] = 'р';
                        matrix[line][symbol + 5] = 'е';
                        break;
                    case '5':       //Символ равен 5
                        numberSymbols[line] = numberSymbols[line] + 3;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 3 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 3];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'п';
                        matrix[line][symbol + 1] = 'я';
                        matrix[line][symbol + 2] = 'т';
                        matrix[line][symbol + 3] = 'ь';
                        break;
                    case '6':       //Символ равен 6
                        numberSymbols[line] = numberSymbols[line] + 4;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 4 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 4];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'ш';
                        matrix[line][symbol + 1] = 'е';
                        matrix[line][symbol + 2] = 'с';
                        matrix[line][symbol + 3] = 'т';
                        matrix[line][symbol + 4] = 'ь';
                        break;
                    case '7':       //Символ равен 7
                        numberSymbols[line] = numberSymbols[line] + 3;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 3 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 3];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'с';
                        matrix[line][symbol + 1] = 'е';
                        matrix[line][symbol + 2] = 'м';
                        matrix[line][symbol + 3] = 'ь';
                        break;
                    case '8':       //Символ равен 8
                        numberSymbols[line] = numberSymbols[line] + 5;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 5 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 5];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'в';
                        matrix[line][symbol + 1] = 'о';
                        matrix[line][symbol + 2] = 'с';
                        matrix[line][symbol + 3] = 'е';
                        matrix[line][symbol + 4] = 'м';
                        matrix[line][symbol + 5] = 'ь';
                        break;
                    case '9':       //Символ равен 9
                        numberSymbols[line] = numberSymbols[line] + 5;
                        nowSize = numberSymbols[line];
                        matrix[line][nowSize + 1] = 0;
                        while (nowSize - 5 != symbol) {
                            matrix[line][nowSize] = matrix[line][nowSize - 5];
                            nowSize--;
                        }
                        matrix[line][symbol] = 'д';
                        matrix[line][symbol + 1] = 'е';
                        matrix[line][symbol + 2] = 'в';
                        matrix[line][symbol + 3] = 'я';
                        matrix[line][symbol + 4] = 'т';
                        matrix[line][symbol + 5] = 'ь';
                        break;
                    default:
                        break;
                    }
                }
                symbol++;
            }
            symbol = 0;
        }
    }
    //Вывод измененного текста
    cout << "Предложения с заменной цифр на слова: ";

    for (int line = 0; line < numberOfLines; line++) {
        while (matrix[line][symbol] != 0) {

            cout << matrix[line][symbol];
            symbol++;
        }
        symbol = 0;
    }
}




