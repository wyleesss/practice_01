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
	std::string game_rules("����������� ������� ������� � ���� ����������� �������\n"
		                   "������ ����� ������ � ������ ���\n"
	                       "������� ���� � ����� ������� ��������� 4 ��������:\n"
	                       "* '���' (������'� - 60; ���� - 40; ���������� - ��������;\n"
	                       "* '�����' (������'� - 80; ���� - 50; ���������� - ������;\n"
	                       "* '����' (������'� - 100; ���� - 20; ���������� - �������;\n"
		                   "* '�����' (������'� - 150; ���� - 70; ���������� - �������;\n"
		                   "������� ������ ��� � �� �� �������� �������� ��� �������� �������\n"
		                   "(��������� ����������� ���������)\n"
		                   "������� ������ ��� - '��������'\n"
		                   "�� ��� ����� �������� '����� ���', �� ������ ����� �� ��������\n"
				           "(���� �� ����� ��������� - 5 ��������, �������� ������������� �� 5 ����� ������)\n"
		                   "����� ���� ������, ���� ������ ������� ������� � �������� � '����� ����������'\n"
		                   "��� ���� ��������� ������� ���� ��������� (���� - 2 ��������)\n");

	bool game_run = true;
	string input_string = "";
	int user_choice = 0;

	#if SHOW_GAME_RULES
	cout << "!������� ���!\n" << game_rules;
	cout << endl;
	pause;
	#endif

	cout << "������������ ���:"
		    "\n������ ����������� ������� ����� �������"
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

		cout << "����� -> " << Game.get_game_leve() << endl
			 << "�������� -> " << Game.get_crystal_count() << endl
		     << "����������� ������� -> " << Game.get_max_size() << endl;
		Game.print_first_monster_info();
		cout << "\n������:"
			    "\n<1> - ��� �������� ������� � ��"
			    "\n<2> - ��� ��������� ��� ������� �������"
			    "\n<3> - ��� �������� � �������"
			    "\n<4> - ��� ���� ������� �����"
			    "\n<5> - ��� ���� ��� ������ ��������"
			    "\n<0> - ��� ���������� ���"
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
			cout << "������:"
				"\n<1> - �������� ����������"
				"\n<2> - �������� �������"
				"\n-> ";

			cin >> user_choice;

			if (user_choice == 1)
				Game.buy_imrovement();

			else
				Game.recover_monster();

			break;

		case 4:

			clear;
			cout << "������ ���� �������"
				"\n-> ";

			cin >> user_choice;

			if(user_choice < 1)
				user_choice = 1;

			Game.update_max_size(user_choice);
			break;

		case 5:

			clear;

			cout << "������ ��'� �������"
				    "\n-> ";
			cin >> input_string;
			
			clear;

			cout << "������ ��� �������"
				    "\n������:"
				    "\n<1> - ���"
				    "\n<2> - �����"
				    "\n<3> - ����"
				    "\n<4> - �����"
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
			cout << "��� ���������!\n\n";
			Game.print_info();
			break;

		}
	}
}