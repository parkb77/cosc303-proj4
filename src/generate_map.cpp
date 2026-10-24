#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std; 

int main (int argc, char *argv[]) { 
	int n = atoi(argv[1]);

	const char symbols[6] = {'f', 'g', 'G', 'h', 'm', 'r'}; 
	const int cost[6] = {3, 1, 2, 4, 7, 5}; 

	//Got this line from Claude while debugging as I had no why I was getting repeated outputs each 'randomized' run
	srand(time(NULL)); //Bases generated seed on the time so each map is unique

	//Each cell randomized symbol
	vector<vector<char> > cell(n, vector<char>(n));
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) {
			int random = rand() % 6; //Keeps range 0-6
			cell[i][j] = symbols[random]; 
		}
	}

	cout << 6 << endl;
	for (int i = 0; i < 6; i++) { 
		cout << symbols[i] << " " << cost[i] << endl;
	}

	//Generate map
	cout << n << endl << n << endl; 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) {
			if (j > 0) {
				cout << " ";
			}
			cout << cell[i][j];
		}
		cout << endl;
	}

	//Start top left end bottom right
	cout << "0 0" << endl << n - 1 << " " << n - 1 << endl;
	return 0;
}


