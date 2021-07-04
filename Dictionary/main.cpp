#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
using namespace std;

static inline void left_trim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
}

static inline string left_trim_copy(string s) {
	left_trim(s);
	return s;
}

int main()
{
    ifstream dictionary("dictionary.txt");
    ofstream log("log.txt");

	string s, words_db[30], meaning_db[30];
	string option, word, input;
	
	
	int words_counter = 0;
	if (dictionary.is_open()) {
		
		while (!dictionary.eof()) {
			string line;
			getline(dictionary, line);
			vector<string> temp_v;
			stringstream ss(line);
			while (ss.good()) {
				string temp;
				getline(ss, temp, ';');
				temp_v.push_back(temp);
			}
			words_db[words_counter] = temp_v.at(0);
			meaning_db[words_counter] = left_trim_copy(temp_v.at(1));
			words_counter++;
		}
		dictionary.close();
		log << "dictionary.txt was succesfuly loaded" << endl;
	}
	else {
		cout << "dictionary.txt is not open" << endl;
		log << "dictionary.txt is not open" << endl;
		return 1;

	}
	cout << "To find a word in dictionary use one of the following options + word:" << endl
		<< "<starting> word" << endl
		<< "<containing> word" << endl
		<< "<ending> word" << endl
		<< "<stop>" << endl << endl;
	do
	{
		getline(cin, input);
		log << input << endl;
		istringstream iss(input);
		iss >> option >> word;
		string temp_d[30];
		int match = 0;
		bool flag1 = false, flag2 = false;
		int matches = 0;
		if (option == "<starting>") {
			for (int i = 0; i < words_counter; i++) {
				if (word.size() == 1) {
					if (words_db[i][0] == word[0]) {
						if (flag1 == false) {
							flag1 = true;
						}
						else {
							flag2 = true;
						}
						temp_d[matches] = words_db[i];
						match = i;
						matches++;
					}
				}
				else {
					if (words_db[i].rfind(word) == 0) {
						if (flag1 == false) {
							flag1 = true;
						}
						else {
							flag2 = true;
						}
						temp_d[matches] = words_db[i];
						match = i;
						matches++;
					}
				}
			}
		}
		else if (option == "<containing>") {
			for (int i = 0; i < words_counter; i++) {
				if (words_db[i].find(word) != string::npos) {
					if (flag1 == false) {
						flag1 = true;
					}
					else {
						flag2 = true;
					}
					temp_d[matches] = words_db[i];
						match = i;
						matches++;
				}
			}

		}
		else if (option == "<ending>") {
			for (int i = 0; i < words_counter; i++) {
				if (words_db[i].rfind(word) == words_db[i].size()-word.size()) {
					if (flag1 == false) {
						flag1 = true;
					}
					else {
						flag2 = true;
					}
					temp_d[matches] = words_db[i];
					match = i;
					matches++;
				}
			}
		}
		else {
			continue;
		}
		if (flag1 == false) {
			cout << "No word in dictionary contains: " << word << endl;
			log << "No word in dictionary contains: " << word << endl;
		}
		else {
			if (flag2 == false) {
				cout << words_db[match] << "; "<< meaning_db[match] << endl;
				log << words_db[match] << "; " << meaning_db[match] << endl;
			}
			else {
				for (int i = 0; i < matches; i++) {
					cout << temp_d[i] << endl;
					log << temp_d[i] << endl;
				}
			}
		}
	} while (option !="<stop>");
	log << "Programm was terminated by user" << endl;
	log.close();
	return 0;
}