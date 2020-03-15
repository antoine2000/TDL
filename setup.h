/* Includes */

#include <iostream>
#include<vector>
#include <ctime>
#include<fstream>
#include<string>
#include <algorithm>
#include "functions.h"

using namespace std;



Task_manager extract_from_line(string line) {

	/* This function takes a line of the file as argument and extract the information of the Task ciphred into this line */

	vector<string> parse_line = parse(line, "/");
	int ID = stoi(parse_line[0]);
	string progress;
	switch(stoi(parse_line[5])) { // Identifies the progress value of the Tasks thanks to the number put in this field in the file
		case 0 : 
			progress = "Open";
			break;
		case 1 : 
			progress = "In_Progress";
			break;
		case 2 : 
			progress = "Closed";
			break;
	};
	int avancement = stoi(parse_line[6]);
	string priority;
	switch(stoi(parse_line[7])) { // Identifies the priority value of the Tasks thanks to the number put in this field in the file
		case 0: 
			priority = "Low";
			break;
		case 1:
			priority = "Normal";
			break;
		case 2 :
			priority = "High";
			break;
		case 3 :
			priority = "Super_High";
			break;
	};
	vector<string> comments = parse(parse_line[8], ";");
	vector<string> under_string = parse(parse_line[9], ";");
	vector<int> under;
	vector<string>::iterator it;
	int sub_ID;
	for (it = under_string.begin(); it != under_string.end(); it++){
 		sub_ID = stoi(*it);
		if (sub_ID == -1) {
			break;
		}
		under.push_back(sub_ID);
	} 
	return Task_manager(ID,parse_line[1],parse_line[2],
		                parse_line[3], parse_line[4], progress,
		                avancement, priority, comments, under);
}

vector<Task_manager> setup() {

	/* This function return an image of the file in terms of Tasks */

	fstream file;
	file.open("Tasks.txt");
	vector<Task_manager> Tasks;
	string line;
	while (getline(file, line)){
		Tasks.push_back(extract_from_line(line));
	}
	file.close();
	return Tasks;
}



struct understood{

	/* This struct allows us to have an easier understanding the input of the user*/

	string main_function;
	vector<string> args;
	vector<vector<string>> values;
};

understood to_understood(vector<string> instructs){

	/* This function takes the parsed input line in the prompt as argument and return instructions for the API. It means that the input instructs are parsed 
	with the '--' keyword. */

	string _main_function;
	vector<string> _args;
	vector<string> current_values;
	vector<vector<string>> _values;
	bool boolean = false;
	vector<string>::iterator it;

	for(it = instructs.begin(); it < instructs.end(); it++){	// For each command in the input line
		if (it == instructs.begin()) { // The first argument must be a function
			_main_function = *it;
		} else { 						// The next arguments are args or values. an arg can hold multiple values, that are stored in its associated vector of values
			string current = *it;
			string::iterator ig;
			string token = "";
			string arg_name = "";
			bool arg_token = false;		// check if the name of the argument has already been taken
			for (ig = current.begin(); ig < current.end(); ig++) {
				if (*ig == ' '  and token != "" and arg_token and arg_name != "-comments") {
					current_values.push_back(token);
					token = "";
				} else if (*ig == ' ' and arg_name != "-comments" and token != "") {
					_args.push_back(token);
					arg_name = token;
					token = "";
					arg_token = true;
				} else if (*ig == '^' and arg_name == "-comments"){
					current_values.push_back(token);
					token = "";
					ig++;
				} else {
					token += *ig;
				}
			}
			if (token != ""){
				current_values.push_back(token);
			}
			_values.push_back(current_values);
			current_values = {};
		}
	}
	_values.push_back(current_values);
	understood u;
	u.main_function = _main_function;
	u.args = _args;
	u.values = _values;
	return u;
}

void execute(vector<string> instructs, vector<Task_manager> Tasks) {

	/* This function analyses the input of the user and compute the response of the API*/

	understood u = to_understood(instructs);
	string main_function = u.main_function;
	vector<string> args = u.args;
	vector<vector<string>> values = u.values;
	if (main_function == "list ") {
		vector<Task_manager> list_task = list(Tasks, args, values);
		vector<Task_manager>::iterator it;
		for (it = list_task.begin(); it < list_task.end(); it++){
			it->print();
		}
	} else if (main_function == "create ") {
		create(Tasks, args, values);
	} else if (main_function == "modify ") {
		modify(Tasks, args, values);
	} else if (main_function == "remove ") {
		vector<Task_manager> list_remove = list(Tasks,args,values);
		remove_tasks(list_remove);
	}
}