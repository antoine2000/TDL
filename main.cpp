#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include "fltk.h"
using namespace std;

int main(int argc, char **argv) {
	vector<Task_manager> Tasks;
	string key = "--graphic";
	if (argc == 2 && argv[1] == key) {
		return run_graphic();
	} 
	while (true) {
		Tasks = setup();
		string instruct;
		cout << "Instruction > ";
		getline(cin, instruct);
		vector<string> instructs = parse(instruct, "--");
		execute(instructs, Tasks);
	}
	return 0;
}
