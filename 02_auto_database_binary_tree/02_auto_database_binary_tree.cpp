/*
Завдання 2.
Реалізувати базу даних ДАІ по штрафним квитанціями за допомогою бінарного дерева(дерева бінарного пошуку).
Кожен елемент дерева  повинен містити
o	ключ(номер автомашини),
o	значення(список правопорушень: vector<violation>, де  violation(назва, дата, сума штрафу) – структура чи клас, що описує одне правопорушення))
o	необхідні вказівники для зв’язування елементів дерева.
Якщо квитанція додається в перший раз, то у дереві з'являється новий вузол, а в списку порушень дані по першому правопорушенню;  якщо інформація про  порушення авто  у дереві наявна, то дані про нове правопорушення  заносяться до знайденого вузла авто(у список правопорушень).
Необхідно також реалізувати такі операції:
o	Повна роздруківка бази даних (номери машин і їх правопорушення)
o	Роздруківка даних по заданому номеру авто
o	Роздруківка даних за діапазоном номерів
o	Очистка бази

*/


#include "stdafx.h"
#include <iostream> 
#include <string>
#include <vector>




using namespace std;


struct Violation
{
	string name;
	string date;
	int price;

	Violation(string name, string date, int price):name(name), date(date), price(price)
	{}

	void print() const
	{
		cout << name << " (" << date << "), money: " << price << endl;
	}
};

struct CarNode
{

	string number;
	vector<Violation> violations;
	CarNode *left, *right, *parent;

	CarNode(string number) :number(number), left(nullptr), right(nullptr), parent(nullptr)
	{}
	

	void print()
	{
		cout << "\nNumber of auto:\t" << number << endl;
		if (violations.size() == 0)
			cout << "Without violation\n";
		else
		{
			int count = 1;
			cout << "Violations:\n";
			for (Violation & v : violations)
			{
				cout << "(" << count++ << ") ";
				v.Violation::print();
			}
		}
	}

	
	void addViolation(string name, string date, int price)
	{
		Violation tmp(name, date, price);
		violations.push_back(tmp);
	}

	void addViolation(Violation v)
	{
		violations.push_back(v);
	}
	

};

class DAI
{
private:

	CarNode * root = nullptr;

public:

	DAI() = default;

	void addViolationOfCar(string number, string violation, string date, int price)
	{
		CarNode * newNode = new CarNode(number);
		if (root == nullptr)
		{
			root = newNode;
			//cout << "nullptr\n";
			newNode->addViolation(violation, date, price);
		}
		else
		{
			CarNode * current = root;
			bool found = false;
			while (!found)
			{
				if (number > current->number)
				{
					if (current->right == nullptr)
					{
						//cout << "rigth\n";
						current->right = newNode;
						newNode->parent = current;
						newNode->addViolation(violation, date, price);
						found = true;
					}
					else
						current = current->right;
				}
				else
					if (number == current->number)
					{
						//cout << "equal\n";
						current->addViolation(violation, date, price);
						found = true;
					}
					else
				{
					if (current->left == nullptr)
					{
						//cout << "left\n";
						current->left = newNode;
						newNode->parent = current;
						newNode->addViolation(violation, date, price);
						found = true;
					}
					else
						current = current->left;
				}
			}
		}
		
	}

	//Роздруківка даних по заданому номеру авто
	void show(string number)
	{
		if (find(number) == NULL)
			cout << endl << number << " - no mismatch!\n";
		else
			find(number)->print();
	}

	//Роздруківка даних за діапазоном номерів
	void showFromTo(string number1, string number2)
	{

		CarNode * current = find(number1);
		while (current != nullptr)
		{
			if (current->number >= number1) 
				show(current->number);
			if (current->number == number2)
				current = current->left;
			else
				current = current->right;
		}
	}

	//Повна роздруківка бази даних (номери машин і їх правопорушення)
	void showAll()const
	{
		ShowHelper(root);
		cout << endl;
	}

	void ShowHelper(CarNode * pNode) const
	{
		if (pNode)
		{
			ShowHelper(pNode->left);
			pNode->print();
			ShowHelper(pNode->right);
		}
	}

	CarNode * find(string number)
	{
		CarNode * current = root;
		while (current != nullptr)
		{
			if (current->number == number)
				return current;
			if (current->number > number)
				current = current->left;
			else
				current = current->right;
		}
		return NULL;
	}
	
	void clear(CarNode * p)
	{
		if (p != nullptr)
		{
			clear(p->left);
			clear(p->right);
			delete p;
		}
	}
	
	//Очистка бази
	void clear()
	{
		clear(root);
		root = nullptr;
		cout << "\nDatabase clear!!!\n";
	}
	
};



int main()
{

	Violation v("Speeding up", "29.06.18", 3000);

	CarNode c("AT3456TB");
	//c.violations.push_back(v);
	//c.violations.push_back(Violation("Red ligth", "28.06.18", 2500));
	c.addViolation(v);
	c.addViolation("Red ligth", "28.06.18", 2500);
	c.print();
	
	DAI dai;
	
	dai.addViolationOfCar("AB0001BK", "Red ligth", "28.06.18", 2500);
	dai.addViolationOfCar("AB0001BK", "Wrong parking", "02.07.18", 500);
	dai.addViolationOfCar("AB0002BK", "Double line", "30.06.18", 2500);
	dai.addViolationOfCar("AB0002BK", "Speeding up", "01.07.18", 3000);
	dai.addViolationOfCar("AB0002BK", "Wrong parking", "02.07.18", 500);
	dai.addViolationOfCar("AB0003BK", "Wrong parking", "03.07.18", 500);
	dai.addViolationOfCar("AB0004BK", "Speeding up", "03.07.18", 3000);
	dai.addViolationOfCar("AB0000BK", "Speeding up", "03.07.18", 3000);
	dai.addViolationOfCar("AB0005BK", "Speeding up", "03.07.18", 3000);

	cout << "\n\tAll auto\n";
	dai.showAll();

	cout << "\n\tSingle auto\n";
	dai.show("AB0001BK");

	cout << "\n\tDiapason autos\n";
	dai.showFromTo("AB0002BK", "AB0004BK");

	dai.clear();
	dai.showAll();
	



	cout << endl;
	system("pause");
	return 0;
}

