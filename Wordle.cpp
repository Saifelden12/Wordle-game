#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

class player {
public:
	string username;
	string email;
	string password;
	player() = default ;

	player(const string& name, const string& mail, const string& pass) :username(name), email(mail), password(pass) {};
};

class word {
public:
	int ID;
	string letters;
};

class authentication {
public:
	vector<player> players;
	authentication() {
		string name;
		string mail;
		string pass;
		ifstream input("players.txt");
		player temp;
		while (input >> name >> mail >> pass) {
			temp.username = name;
			temp.email = mail;
			temp.password = pass;
			players.push_back(temp);
		}
	}
	void signup(string name , const string& mail ,const string& pass) {
		for (int i = 0; i < players.size(); i++) {
			if (name == players[i].username) {
				cout << "\nUsername already exists, chose another username: ";
				cin >> name;
				i = -1;
			}
		}
		player newplayer(name, mail, pass);
		players.push_back(newplayer);
		ofstream file("players.txt", ios::app);
		file <<endl << name << endl<< mail << endl<< pass;
		file.close();
		cout << "new player has been created\n";
	}
	bool login(const string& user,const string& pass) {
		for (int i = 0; i < players.size(); i++) {
			if (user == players[i].username&& pass == players[i].password) {
					return true;
			}
		}
		return false;
	}
};

class listOfWord {
public:
	vector<word>listWord;

	listOfWord() {
		string letters;
		int ID;
		word temp;
		ifstream input("word.txt");
		while (input >> ID >> letters) {
			temp.ID = ID;
			temp.letters = letters;
			listWord.push_back(temp);
		}
	}
	word gettheword(int ID) {
		for (int i = 0; i < listWord.size(); i++) {
			if (listWord[i].ID == ID) {
				return listWord[i];
			}
		}

		return word();
	}

};

class gameSession {
public:
	int sessionID;
	word theWord;
	gameSession() = default;

	void getrandomword(vector<word>listWord) {
		srand(time(0));

		int randomIndex = rand() % listWord.size();

		theWord = listWord[randomIndex];
	};
	string checkLetters(string guess) {

		string target = theWord.letters;
		int n = target.size();

		if (guess == "") {
			return string(n, '-');
		}

		if (guess.size() != n)
			return "Invalid";

		string result(n, '_');
		string tempTarget = target;

		for (int i = 0; i < n; i++) {
			if (guess[i] == tempTarget[i]) {
				result[i] = 'T';
				tempTarget[i] = '*';
			}
		}

		for (int i = 0; i < n; i++) {
			if (result[i] == 'T') continue;

			for (int j = 0; j < n; j++) {
				if (guess[i] == tempTarget[j]) {
					result[i] = 'M';
					tempTarget[j] = '*';
					break;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (result[i] == '_')
				result[i] = '-';
		}

		if (guess == target)
			return "Winner";
		return result;
	}
};

int main()
{
	int chose=0;
	authentication system;
	while (chose != 3) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); 

				cout << "======================================\n";
				cout << "        Welcome To Wordle Game  \n";
				cout << "======================================\n";
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "1.sign-in\n";
	cout << "2.sign-up\n";
		cin >> chose;
		cout << endl;
		if (chose == 1) {
			string name;
			string password;
			cout << "Enter name: ";
			cin >> name;
			cout << "\nEnter password: ";
			cin >> password;

			if (system.login(name, password) == true) {

				int x=1;
				while (x==1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					string guess;
					gameSession thegame;
					listOfWord words;
					thegame.getrandomword(words.listWord);
					cout << string(thegame.theWord.letters.size(), '-') << endl;
					string result;
					for (int i = 0; i < 6; i++) {
						cout << "Enter your guess: ";
						cin >> guess;
						cout <<"The Word-> " << thegame.checkLetters(guess) << endl;
						if (thegame.checkLetters(guess) == "Winner"|| thegame.checkLetters(guess) == "Invalid") {
							break;
						}
					}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "\nYou want to try again?";
					cout << "\n1.Yes";
					cout << "\n2.No\n";
					cin >> x;
				}
				chose = 3;
			}
			else {
				cout << "wrong password or username ";
			}
		}
		else if (chose == 2) {
			string name;
			string pass;
			string mail;
			cout << "Enter your username: ";
			cin >> name;
			cout << "\nEnter your email: ";
			cin >> mail;
			cout << "\nEnter your password: ";
			cin >> pass;
			system.signup(name, mail, pass);
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}