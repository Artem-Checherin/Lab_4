/*! @file main.cpp
* @author Чечерин Артём
* @version 1.0
* @date 04.06.2021
* @brief Головной модуль программы для шифрования.
* @details Осуществляет шифрование алгоритмом Гронсвельда на русском языке.
* @details Lab 2-1
*/
#include <iostream>
#include <cctype>
#include <codecvt>
#include <locale>
#include <stdbool.h>
#include "modAlphaCipher.h"

using namespace std;
bool isValid(const string& s)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring ws = codec.from_bytes(s);
	for (auto wc: ws)
		if (!((wc>= 1040) && (wc <= 1071)) || (wc == 1025))
			return false;
	return true;
}
/*! @brief Интерфейс программы
* @details Осуществление выбора операции 0, 1 или 2. В зависимости
 от выбора выполняются следующие действия: выход, зашифровка,
расшифровка.Задание ключа и проверка его синтаксис.
*/
int main(int argc, char **argv)
{
	string key;
	string text;
	unsigned op;
	do {
		locale loc("ru_RU.UTF-8");
		locale::global(loc);
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
		try {
			cout<<"<Cipher ready> Введите операцию (0-выход, 1-зашифровка, 2-расшифровка):";
			cin>>op;/// ввод номера операции
			if (op > 2) {
				cout<<"Номер операции ошибочен"<<endl;
			} else if (op >0) {
				cout<<"<Cipher ready> Введите ключ(русские заглавные буквы)--> ";
				cin>>key;/// ввод ключа
				if (!isValid(key)) {
					cout << key << endl;
					throw Error(string("Ключ не принят"));
				}
				cout<<"Ключ принят"<< endl;
				modAlphaCipher cipher(key);
				cout<<"<Cipher ready> Введите текст--> ";
				cin>>text;
				cout << text << endl;
				if (isValid(text)) {
					if (op==1) {
						cout<<"Зашифрованный текст: "<<cipher.encrypt(text)<<endl;
					} else {
						cout<<"Расшифрованный текст: "<<cipher.decrypt(text)<<endl;
					}
				} else {
					throw Error(string("Операция не выполнена: неверный формат текста(не руссие заглавные буквы)"));
				}
			}
		} catch (const Error & e) {
			cerr << "<Error> Ошибка : " << e.what() << endl;
		}
	} while (op!=0);
	return 0;
}