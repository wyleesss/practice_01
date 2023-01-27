#ifndef MONSTERS_H
#define MONSTERS_H

#include "template_pointer.h"
#include <iostream>
#include <queue>

#if _WIN32
#define clear system("CLS")
#define pause system("pause"); system("CLS")

#elif __linux
#define clear system("clear")
#define pause 0

#endif

const enum class MonsterType
{
	nullMT = -1,
	Orc = 1, Troll, Zombie, Goblin
};

const enum class Feature
{
	nullF = -1,
	strong = 1, fast, clever, tricky
};

class Monster
{
	MonsterType type;
	Feature     feature;
	std::string name;
	int         health;
	int         damage;

public:

	Monster()
		:type(MonsterType::nullMT), name(""), health(0), damage(0), feature(Feature::nullF)
	{
	}

	explicit Monster(MonsterType type, std::string name)
		:type(type), name(name)
	{
		switch (type)
		{
		case MonsterType::Orc:

			health = 60;
			damage = 40;
			feature = Feature::clever;
			break;

		case MonsterType::Troll:

			health = 80;
			damage = 50;
			feature = Feature::tricky;
			break;

		case MonsterType::Zombie:

			health = 100;
			damage = 20;
			feature = Feature::fast;
			break;

		case MonsterType::Goblin:

			health = 150;
			damage = 70;
			feature = Feature::strong;
			break;

		default:

			health = 0;
			damage = 0;
			feature = Feature::nullF;
			break;
		}
	}

	friend std::ostream& operator << (std::ostream& os, const Monster& monster_object);
};

class MonsterGame
{
	std::queue<Pointer<Monster>> fight_line;
	std::queue<Pointer<Monster>> recovery_line;
	int crystals_count;
	int imrovement_level;
	int max_size;
	int defeat_count = 0, win_count = 0, monsters_added_count = 0, crystals_earned_count = 0, max_size_updated_count = 0;

public:

	MonsterGame(int max_size)
		:max_size(max_size), crystals_count(5), imrovement_level(1)
	{
	}

	int get_crystal_count()
	{
		return crystals_count;
	}

	int get_max_size()
	{
		return max_size;
	}

	int get_game_leve()
	{
		return imrovement_level;
	}

	void update_max_size(int new_max_size)
	{
		max_size = new_max_size;
		max_size_updated_count++;
	}

	void add(Monster mstr)
	{
		clear;

		if (fight_line.size() >= max_size)
		{
			std::cout << "неможливо додати монстра. досягнута максимальна кількість.\n";
			pause;
			return;
		}

		fight_line.push(Pointer<Monster>(new Monster(mstr)));
		monsters_added_count++;
	}

	void fight()
	{
		clear;

		if (fight_line.empty())
		{
			std::cout << "неможливо відправити 'пустоту'\n";
			pause;
			return;
		}

		int random_score = (rand() % 9 + 1) * (10 + imrovement_level);

		if (random_score < 50)
		{
			recovery_line.push(std::move(fight_line.front()));
			fight_line.pop();
			std::cout << "монстр потерпів поразку.\n";
			defeat_count++;
			pause;
		}

		else
		{
			std::cout << "монстр переміг!\n";
			crystals_count += 2;
			win_count++;
			crystals_earned_count += 2;
			pause;
		}
	}

	void recover_monster()
	{
		clear;

		if (recovery_line.empty())
		{
			std::cout << "неможливо відновити 'пустоту'\n";
			pause;
			return;
		}

		if (crystals_count < 2)
		{
			std::cout << "не вистачає кристалів.\n";
			pause;
			return;
		}

		crystals_count -= 2;
		fight_line.push(std::move(recovery_line.front()));
		recovery_line.pop();
		std::cout << "монстра було відновлено!\n";
		pause;
	}

	void buy_imrovement()
	{
		clear;
		switch (imrovement_level)
		{
		case 1:

			if (crystals_count >= 5)
			{
				crystals_count -= 5;
				imrovement_level++;
				std::cout << "рівень оновлено!\n";
				pause;
			}
			else
			{
				std::cout << "кристалів не вистачає.\n";
				pause;
			}
			break;

		case 2:

			if (crystals_count >= 10)
			{
				crystals_count -= 10;
				imrovement_level++;
				std::cout << "рівень оновлено!\n";
				pause;
			}
			else
			{
				std::cout << "кристалів не вистачає.\n";
				pause;
			}
			break;

		case 3:

			if (crystals_count >= 10)
			{
				crystals_count -= 10;
				imrovement_level++;
				std::cout << "рівень оновлено!\n";
				pause;
			}
			else
			{
				std::cout << "кристалів не вистачає.\n";
				pause;
			}
			break;

		case 4:

			if (crystals_count >= 15)
			{
				crystals_count -= 15;
				imrovement_level++;
				std::cout << "рівень оновлено!\n";
				pause;
			}
			else
			{
				std::cout << "кристалів не вистачає.\n";
				pause;
			}
			break;

		default: 

			std::cout << "рівень вже максимальний.\n";
			break;
		}
	}

	void print_first_monster_info()
	{
		std::cout << "\nмонстр #1 у активній черзі:\n";

		if (!fight_line.empty())
		{
			std::cout << *fight_line.front() << std::endl;
			return;
		}

		std::cout << "\nнаразі немає монстрів у черзі. додайте їх!\n";
	}

	void print_all_monsters_info()
	{
		clear;
		std::queue<Pointer<Monster>> temp_queue;
		Pointer<Monster>* temp_array = new Pointer<Monster>();
		int choice = 0;
		int current_monster_id = 0;
		int max_id;
		bool run = true;

		do
		{
			std::cout << "введіть:"
			   << "\n<1> - для перегляду активних монстрів"
			   << "\n<2> - для перегляду монстрів на відновленні"
			   << "\n-> ";
			std::cin >> choice;
		} while (choice != 1 && choice != 2);

		if ((choice == 1 && fight_line.empty()) || (choice == 2 && recovery_line.empty()))
		{
			clear;
			std::cout << "наразі немає монстрів у поточній черзі\n";
			pause;
			return;
		}

		if (choice == 1 && fight_line.size() == 1)
		{
			clear;
			std::cout << *fight_line.front() << std::endl;
			pause;
			return;
		}

		if (choice == 2 && recovery_line.size() == 1)
		{
			clear;
			std::cout << *recovery_line.front() << std::endl;
			pause;
			return;
		}

		if (choice == 1)
		{
			temp_queue = fight_line;
			max_id = static_cast<int>(fight_line.size() - 1);
		}
		else
		{
			temp_queue = recovery_line;
			max_id = static_cast<int>(recovery_line.size() - 1);
		}

		for (int i = max_id; !temp_queue.empty(); i--)
		{
			temp_array[i] = std::move(temp_queue.front());
			temp_queue.pop();
		}

		while (run)
		{
			if (current_monster_id == 0)
			{
				do
				{
					clear;
					std::cout << "монстр #" << current_monster_id + 1 << " з поточної черги:\n";
					std::cout << *temp_array[current_monster_id];
					std::cout << "\n\nвведіть:"
						"\n<1> - для перегляду наступного монстру"
						"\n<0> - для виходу"
						"\n-> ";
					std::cin >> choice;
				} while (choice != 1 && choice != 0);
			}

			else if (current_monster_id == max_id)
			{
				do
				{
					clear;
					std::cout << "монстр #" << current_monster_id + 1 << " з поточної черги:\n";
					std::cout << *temp_array[current_monster_id];
					std::cout << "\n\nвведіть:"
						"\n<2> - для перегляду попереднього монстру"
						"\n<0> - для виходу"
						"\n-> ";
					std::cin >> choice;
				} while (choice != 2 && choice != 0);
			}

			else
			{
				do
				{
					clear;
					std::cout << "монстр #" << current_monster_id + 1 << " з поточної черги:\n";
					std::cout << *temp_array[current_monster_id];
					std::cout << "\n\nвведіть:"
						"\n<1> - для перегляду наступного монстру"
						"\n<2> - для перегляду попереднього монстру"
						"\n<0> - для виходу"
						"\n-> ";
					std::cin >> choice;
				} while (choice != 1 && choice != 2 && choice != 0);
			}

			choice == 1 ? current_monster_id++ : choice == 2 ? current_monster_id-- : run = false;
		}

		clear;
	}

	void print_info()
	{
		std::cout << "інформація щодо гри"
			<< "\n\nрівень гри -> " << imrovement_level
			<< "\nактивних монстрів -> " << fight_line.size()
			<< "\nмонстрів на відновлення -> " << recovery_line.size()
			<< "\nкристалів -> " << crystals_count
			<< "\nвсього зароблено кристалів -> " << crystals_earned_count
			<< "\nперемог -> " << win_count
			<< "\nпоразок -> " << defeat_count
			<< "\nвсього монстрів додано -> " << monsters_added_count
			<< "\nкількість змін максимальної довжини черги -> " << max_size_updated_count;
	}

};

std::ostream& operator << (std::ostream& os, const MonsterType& monster_type)
{
	switch (monster_type)
	{
	case MonsterType::Orc: return os << "Орк";

	case MonsterType::Troll: return os << "Троль";

	case MonsterType::Zombie: return os << "Зомбі";

	case MonsterType::Goblin: return os << "Гоблін";

	default: return os << '\0';
	}
}

std::ostream& operator << (std::ostream& os, const Feature& feature)
{
	switch (feature)
	{
	case Feature::strong: return os << "сильний";

	case Feature::fast: return os << "швидкий";

	case Feature::clever: return os << "розумний";

	case Feature::tricky: return os << "хитрий";

	default: return os << '\0';
	}
}

std::ostream& operator << (std::ostream& os, const Monster& monster_object)
{
	return os << "Ім'я - " << monster_object.name
		    << "\nТип: " << monster_object.type
		    << "\nРиса: " << monster_object.feature
		    << "\nЗдоров'я -> " << monster_object.health
		    << "\nСила -> " << monster_object.damage;
}

#endif