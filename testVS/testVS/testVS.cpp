#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main()
{
	srand(time(NULL));
	cout << "Find my number!\n";
	cout << "1. You choose a number\n";
	cout << "2. I will tell you if that number is my number or not\n";
	cout << "3. If you're right, you win\n";
	cout << "4. Otherwise, you have to choose another number until you win\n";
	cout << "Ready? (y/Y): ";
	char inp;
	cin >> inp;
lap:
	system("cls");
	int myNumber = rand() % 13;
	int userNumber;
	while (1)
	{
		cout << "Your number is: ";
		cin >> userNumber;
		if (userNumber == myNumber)
		{
			cout << "You win!\n";
			cout << "Wanna try again? (y/n): ";
			cin >> inp;
			if (inp == 'y' || inp == 'Y') goto lap;
			else break;
		}
		else
		{
			cout << "WRONG!!\n";
		}
	}
	system("cls");
	cout << "Bye";
}
