/*! @file modAlphaCipher.h
* @author Чечерин Артём
* @version 1.0
* @date 04.06.2021
* @brief Заголовочный файл модуля main.cpp
* @details Осуществляет шифрование алгоритмом Гронсвельда на русском языке.
* @details Lab 2-1
*/
#pragma once
#include <vector>
#include <string>
#include <codecvt>
#include <locale>
#include <map>
#include <stdexcept>
using namespace std;
/*! @brief Шифрование методом Гронсфельда
* @details Ключ устанавливается в конструкторе.Для зашифровывания и
расшифровывания предназначены методы encrypt и decrypt.
* @warning Реализация только для русского языка
*/
class modAlphaCipher
{
private:
	wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";///<Русский алфавит по порядку
	map <wchar_t,int> alphaNum;///<Ассоциативный массив "номер по символу"
	vector <int> key;///< Ключ
	/**
	* @brief Преобразование строка-вектор
	* @param [in] ws Строка в кодировке UTF-32
	* @return Целочисленный вектор
	*/
	vector<int> convert(const wstring& ws);
	/**
	* @brief Преобразование вектор-строка
	* @param [in] v Целочисленный вектор
	* @return Строка в кодировке UTF-8
	*/
	string convert(const vector<int>& v);
	/**
	* @brief Валидация ключа
	* @param [in] ws Ключ в кодировке UTF-32. Не
	должен быть пустой строкой.
	* Строчные символы автоматически преобразуются к
	прописным.
	* @return Валидный ключ в кодировке UTF-32
	* @throw Error - ключ пустой или содержит
	недопустимые
	символы
	*/
	wstring towstr(const string& s);
	/**
	* @brief Валидация открытого текста
	4
	* @param [in] ws Открытый текст в кодировке UTF32. Не должен быть пустой
	строкой.
	* Строчные символы автоматически преобразуются к
	прописным.
	* @return Валидный открытый текст в кодировке
	UTF-32
	* @throw Error - текст пустой или содержит
	недопустимые символы
	*/
	string fromwstr(const wstring& ws);
	/**
	* @brief Валидация зашифрованного текста
	* @param [in] ws Зашифрованный текст в кодировке
	UTF-32. Не должен быть пустой строкой.
	* Не должен содержать строчные символы и небуквы.
	* @return Валидный зашифрованный текст в
	кодировке UTF-32
	* @throw Error - текст пустой или содержит
	недопустимые символы
	*/
public:
	/**
	* @brief Конструктор без параметров
	* @details Запрещен
	*/
	modAlphaCipher()=delete;
	/**
	* @brief Конструктор для установки ключа
	* @details Ключ проверяется на валидность.
	Переводится в кодировку UTF-32.
	* Формируется вектор-ключ.
	* @param [in] skey Ключ в кодировке UTF-8
	* @throw Error ключ вырожденный
	*/
	modAlphaCipher(const string& skey);
	/**
	* @brief Зашифровывание
	* @param [in] open_text Открытый текст в
	кодировке UTF-8. Не должен быть пустой строкой.
	* Строчные символы автоматически преобразуются к
	* прописным.Все не-буквы удаляются.
	* @return Зашифрованная строка в кодировке UTF-8
	* @throw Error - текст пустой
	*/
	string encrypt(const string& open_text);
	/**
	* @brief Расшифровывание
	* @param [in] cipher_text Зашифрованный текст в
	* кодировке UTF-8. Не должен быть пустой строкой.
	* Не должен содержать строчные символы и не буквы.
	* @return Руссифрованная строка в кодировке UTF-8
	* @throw Error - текст пустой
	*/
	string decrypt(const string& cipher_text);
};
/**
	* @brief Класс-исключение Error
	* @param производный от класса std::invalid_argument
	* @return Сообщение об ошибке (возбужденное)
	*/
class Error: public invalid_argument
{
public:
	explicit Error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit Error (const char* what_arg):
		invalid_argument(what_arg) {}
};