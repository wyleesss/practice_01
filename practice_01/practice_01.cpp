#include "monsters.h"
#include <iostream>

#if _WIN32
#include <Windows.h>
#endif

#define SHOW_GAME_RULES 1

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	#if _WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	#endif

	srand(time(NULL));
	std::string game_rules("макисмальна кількість монстрів в черзі визначається гравцем\n"
		                   "кількіть можна змінити в процесі гри\n"
	                       "гравець додає в чергу монстрів наступних 4 категорій:\n"
	                       "* 'Орк' (здоров'я - 60; сила - 40; особливість - розумний;\n"
	                       "* 'Троль' (здоров'я - 80; сила - 50; особливість - хитрий;\n"
	                       "* 'Зомбі' (здоров'я - 100; сила - 20; особливість - швидкий;\n"
		                   "* 'Гоблін' (здоров'я - 150; сила - 70; особливість - сильний;\n"
		                   "монстри можуть йти в бій та принести перемогу або потерпіти поразку\n"
		                   "(результат визначається випадково)\n"
		                   "основна валюта гри - 'кристали'\n"
		                   "за них можна підвищити 'рівень гри', що підвищує шанси на перемогу\n"
				           "(ціна за перше підвищення - 5 кристалів, подальші коштуватимуть на 5 більше кожний)\n"
		                   "також вони корисні, коли монстр потерпів поразку і потрапив у 'чергу відновлення'\n"
		                   "тоді може виникнути потреба його повернути (ціна - 2 кристали)\n");

	bool game_run = true;
	string input_string = "";
	int user_choice = 0;

	#if SHOW_GAME_RULES
	cout << "!правила гри!\n" << game_rules;
	cout << endl;
	pause;
	#endif

	cout << "налаштування гри:"
		    "\nвведіть максимальну довжину черги монстрів"
		    "\n-> ";
	cin >> user_choice;
	clear;

	if (user_choice < 1)
		user_choice = 1;

	MonsterGame Game(user_choice);

	while (game_run)
	{
		#if _WIN32
		clear;
		#endif

		cout << "рівень -> " << Game.get_game_leve() << endl
			 << "кристалів -> " << Game.get_crystal_count() << endl
		     << "максимальна довжина -> " << Game.get_max_size() << endl;
		Game.print_first_monster_info();
		cout << "\nвведіть:"
			    "\n<1> - для відправки монстра в бій"
			    "\n<2> - для перегляду всіх наявних монстрів"
			    "\n<3> - для переходу в магазин"
			    "\n<4> - для зміни довжини черги"
			    "\n<5> - для того щоб додати монтстра"
			    "\n<0> - для завершення гри"
			    "\n-> ";

		cin >> user_choice;
		switch (user_choice)
		{
		case 1:

			Game.fight();
			break;

		case 2:

			Game.print_all_monsters_info();
			break;

		case 3:

			clear;
			cout << "введіть:"
				"\n<1> - придбати покращення"
				"\n<2> - звільнити монстра"
				"\n-> ";

			cin >> user_choice;

			if (user_choice == 1)
				Game.buy_imrovement();

			else
				Game.recover_monster();

			break;

		case 4:

			clear;
			cout << "введіть нову довжину"
				"\n-> ";

			cin >> user_choice;

			if(user_choice < 1)
				user_choice = 1;

			Game.update_max_size(user_choice);
			break;

		case 5:

			clear;

			cout << "введіть ім'я монстра"
				    "\n-> ";
			cin >> input_string;
			
			clear;

			cout << "оберіть тип монстра"
				    "\nвведіть:"
				    "\n<1> - Орк"
				    "\n<2> - Троль"
				    "\n<3> - Зомбі"
				    "\n<4> - Гоблін"
				    "\n-> ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:

				Game.add(Monster(MonsterType::Orc, input_string));
				break;

			case 2:

				Game.add(Monster(MonsterType::Troll, input_string));
				break;

			case 3:

				Game.add(Monster(MonsterType::Zombie, input_string));
				break;

			case 4:

				Game.add(Monster(MonsterType::Goblin, input_string));
				break;

			default: break;
			}
			break;

		default: 

			game_run = false;
			clear;
			cout << "гру завершено!\n\n";
			Game.print_info();
			break;

		}
	}
}