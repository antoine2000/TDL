#include "fltk.h"

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

		// Does the user want to quit ?

		if (instruct == "quit") {
			break;
		} 

		// Is the input correct ?

		if (test_line(instruct)) {

			// The input is correct

			vector<string> instructs = parse(instruct, "--");
			execute(instructs, Tasks);			
		} else {

			// The input isn't correct

			cout << "Error : You mustn't put a '/' as argument" << endl;
		}
	}
	return 0;
}
