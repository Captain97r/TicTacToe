// TicTacToe.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

enum Turn { user, comp};																				// Нумератор, содержащий инофрмацию об очереди хода
char field[3][3];																						// Поле для игры

void go(Turn turn, char userMarker, char compMarker);													// Метод самого процееса игры :)
void display();																							// Отображение текущего состояния поля
bool check();																							// Проверка, нет ли победителя на данный момент
bool fieldIsFull();																						// Проверка, есть ли свободные места на поле



int main()
{
	system("cls");
	char userMarker = '-';																				// Маркер компьютера
	char compMarker = '-';																				// Маркер игрока
	Turn turn;																							// Активный игрок

	cout << "Choose your marker (X / O): ";
	cin >> userMarker;																					// Назначение маркеров

	userMarker = toupper(userMarker);

	switch (userMarker)
	{
	case 'X':
		compMarker = 'O';
		turn = user;
		break;
	case 'O':
		compMarker = 'X';
		turn = comp;
		break;
	default:																							// Обработка неверного ввода
		cout << "Undefined input!\n";
		system("pause");
		exit(1);
		break;
	}

	go(turn, userMarker, compMarker);																	// Если ошибки ввода нет, начинаем игру

	cin.get();

	cout << "Do you wanna play one more time? (Y/N): ";													// Do you wanna play one more time?
	switch (toupper(getchar()))
	{
	case 'Y':
		main();																							// Если да, то все сначала
		break;
	case 'N':
		return 0;																						// Нет - завершение программы
	default:
		cout << "Undefined input!\n";																	// Что-то другое - сообщение об ошибке и завершение программы
		system("pause");
		exit(1);
		break;
	}
    return 0;
}


void go(Turn turn, char userMarker, char compMarker)
{
	system("cls");
	int x = 0;																							// Коорината x постановки маркера
	int y = 0;																							// Коорината y постановки маркера
	bool repeat = false;																				// Определяет, не нужно ли игроку ввести позицию заново после ошибки

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			field[i][j] = '-';																			// Создание пустого поля перед началом игры


	do {

		display();																						// Перед кадым ходом отображаем поле

		if (fieldIsFull())																				// Если поле заполнено и победитель не определен - ничья, возвращение из метода
		{
			cout << "Draw\n";
			system("pause");
			return;
		}

		if (turn == user)
		{
			repeat ? cout << "Incorrect input! Try again: " : cout << "Input index: ";					// Если была совершена ошибка при вводе, позволяем игроку ввести позицию повторно
			cin >> x >> y;																				// Ввод позиции

			if ((x <= 3) && (y <= 3) && (field[--x][--y] == '-'))										// Проверка на ошибку ввода и занятость поля по текущим коодинатам
			{ 
				field[x][y] = userMarker;																// Если все хорошо, ставим маркер
				repeat = false;																			// Сбрасываем флаг ошибки
				turn = comp;																			// Передаем очередь хода
			}
			else 
			{ 
				repeat = true;																			// Если что-то полшло не так - выводим сообщение, повторяем
				system("cls"); 
				continue; 
			}
		}
		else
		{
			srand(time(NULL));																			// Если ход компьютера, определяем случайное незанятое поле
			do {
				x = rand() % 3;
				y = rand() % 3;
			} while (field[x][y] != '-');

			field[x][y] = compMarker;																	// И ставим туда метку
			turn = user;																				// Передача очереди хода
		}

		system("cls");

	} while (check());																					// Играем, пока кто-либо не выиграл или не проиграл

	display();																							// Показываем финальное состояние поля
	(turn == user) ? cout << "The CPU has just owned you\n": cout << "You win!\n";						// Определяем победителя

	return;
}


bool check()
{
	for (int i = 0; i < 3; i++)
	{
		if ((field[i][0] == field[i][1] && field[i][0] == field[i][2]) && field[i][0] != '-') return false;							// Проверка горизонталей
		else if ((field[0][i] == field[1][i] && field[0][i] == field[2][i]) && field[0][i] != '-') return false;					// Проверка вертикалей
	}
	if ((field[0][0] == field[1][1] && field[0][0] == field[2][2]) && field[0][0] != '-') return false;								
	else if ((field[2][0] == field[1][1] && field[2][0] == field[0][2]) && field[2][0] != '-') return false;						// И обоих диагоналей
	else return true;
}

void display()
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << field[i][j] << ' ';																								// Отборажение поля
		cout << endl;
	}
	return;
}

bool fieldIsFull()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (field[i][j] == '-') return false;																					// Если есть хоть одно незанятое поле, можно играть дальше
	return true;
}