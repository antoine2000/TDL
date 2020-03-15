#include <iostream>
#include<vector>
#include <ctime>
#include<fstream>
#include<string>
#include "Tasks.h"
using namespace std;

string sum(vector<string> vec) {

	/* This function computes the sum of the elements of a vector of strings */

	string output = "";
	vector<string>::iterator it;
	for (it = vec.begin(); it < vec.end(); it++) {
		output += *it;
		if (it +1 != vec.end()) {
			output += " ";
		}
	}
	return output;
}

vector<string> parse(string line, string delimiter) {

	/* This functions divides the given string into an vector of string, cutting when it finds the given delimiter */

	int n = delimiter.size();
    vector<string> tokens;
    string token = "";
    for (int pos = 0; pos < line.size(); pos++){
    	if (line.substr(pos,n) == delimiter and token != ""){ // This is a new sub-string
    		tokens.push_back(token);
    		token = "";
    	} else if (line.substr(pos,n) == delimiter) { // We have the delimiter two times in a row
    		tokens.push_back(" ");
    		pos += n - 1;
    	} else {
    		token += line[pos]; // we add the current caracter to the current sub-string
    	}
    }
    if (token != "") { // to catch the last sub-string
    	tokens.push_back(token);
    }
    return tokens;
}

vector<Task_manager> list(vector<Task_manager> Tasks, vector<string> args, vector<vector<string>> values) {

	/* This function lists the task that verify the given values in the given fields. For example, 
	an argument of args can be 'title' and the associated value can be 'the TITLE', the function will return
	a vector with the Tasks with 'the TITLE' as title */

	vector<Task_manager> List_task;
	bool boolean;
	for(int i = 0; i < Tasks.capacity(); i++) { // for each Task
		boolean = true; 						// The boolean that will check whereas the fields of the tested Task have the same value as the values passed as arguments
		Task_manager Task = Tasks[i];
		for(int j = 0; j < args.capacity(); j++) {
			string field;
			string arg = args[j];
			if (arg == "-ID" || arg == "ID") {
	    		field = to_string(Task.ID);
	    	} else if (arg == "-title" || arg == "title") {
	    		field = Task.title;
	    	} else if (arg == "-description" || arg == "description") {
	    		field = Task.description;
	    	} else if (arg == "-begin" || arg == "begin") {
	    		field = Task.begin;
	    	} else if (arg == "-end" || arg == "end") {
	    		field = Task.end;
	    	} else if (arg == "-progress" || arg == "progress") {
	    		field = Task.progress;
	    	} else if (arg == "-avancement" || arg == "avancement") {
	    		field = to_string(Task.avancement);
	    	} else if (arg == "-priority" || arg == "priority") {
	    		field = Task.priority;
	    	}
	    	if (field != sum(values[j])) {
	    		boolean = false;
	    	}
	    	if (arg == "-comments" || arg == "comments") {
	    		vector<string> coms = Task.comments;
    			vector<string>::iterator it1;
    			for (it1 = values[j].begin(); it1 < values[j].end(); it1++ ){	    		
    				bool sub_bool = false;
	    			vector<string>::iterator it2;
    				for (it2 = coms.begin(); it2 < coms.end(); it2++) {
						if (*it2 == *it1) {
	    					sub_bool = true;
	    				}
	    			}
		    		if (not sub_bool) {
		    			boolean = false;
		    		}
	    		}
	    	} else if (arg == "-under" || arg == "under") {
	    		vector<int> unders = Task.Under;
   				vector<string>::iterator it1;
    			for (it1 = values[j].begin(); it1 < values[j].end(); it1++ ){	    		
    				bool sub_bool = false;
	    			vector<int>::iterator it2;
    				for (it2 = unders.begin(); it2 < unders.end(); it2++) {
						if (*it2 == stoi(*it1)) {
	    					sub_bool = true;
	    				}
	    			}
		    		if (not sub_bool) {
		    			boolean = false;
		    		}	    			
	    		}
	    	}
	   		}
	   	if (boolean){
	   		List_task.push_back(Task);
	   	}
	}
	return List_task;
}

int get_top(vector<Task_manager> Tasks) {

	/* This function catches the biggest ID in the vector of Tasks, taken from the file */

	int top = 1;
	vector<Task_manager>::iterator it;
	for(it = Tasks.begin(); it < Tasks.end(); it++){
		int n = (*it).ID;
		if (n >= top) {
			top = n + 1 ;
		}
	}
	return top;
}

void create(vector<Task_manager> Tasks, vector<string> args, vector<vector<string>> values) {

	/* This function aims to prepare the arguments passed to the generator of the Task struct. It detects the fields given by the user, and the associated values*/

	int top = get_top(Tasks);
	Task_manager New_task = Task_manager(top);
	for (int i = 0; i < args.capacity(); i++) {
		string arg = args[i];
		if (arg == "-title") {
			New_task.title = sum(values[i]);
		} else if (arg == "-description") {
			New_task.description = sum(values[i]);
		} else if (arg == "-begin") {
			New_task.begin = sum(values[i]);
		} else if (arg == "-end") {
			New_task.end = sum(values[i]);
		} else if (arg == "-progress") {
			New_task.progress = sum(values[i]);
		} else if (arg == "-avancement") {	
			New_task.avancement = stoi(sum(values[i]));
		} else if (arg == "-priority") {
			New_task.priority = sum(values[i]);
		} else if (arg == "-comments") {
			New_task.comments = values[i];
		} else if (arg == "-under") {
			vector<string>::iterator it;
			for (it = values[i].begin(); it < values[i].end(); it++){
				New_task.Under.push_back(stoi(*it));	
			}
		}
	}
	New_task.add_to_file(); // add to the file
}

bool is_not_in(string test, vector<int> list){

	/* Test whearas the given number in the string is in the given list, the string must contained an integer */

	int i = stoi(test);
	vector<int>::iterator it;
	for (it = list.begin(); it < list.end(); it++) {
		if (*it == i) {
			return false;
		}
	}
	return true;
}

void remove_tasks(vector<Task_manager> list_rm) {

	/* This function removes Tasks from the file. To do that, it suppress the file and re-write it without the Tasks that are passed as argument in the function*/

	vector<int> ID_s;
	vector<Task_manager>::iterator it;
	for (it = list_rm.begin(); it < list_rm.end(); it++) {
		ID_s.push_back((*it).ID);                           // Get the ID's of the Tasks passed as arguments
	}
	fstream file;
	fstream file2;
	file2.open("temp.txt", ios::app);
	file.open("Tasks.txt");
	string line;
	while (getline(file,line)) {
		if (is_not_in(parse(line, "/")[0],ID_s)) {     // Get the ID of each Task and check whereas the Task must be removed
			file2 << line << "\n";
		}
	}
	remove("Tasks.txt");
	rename("temp.txt", "Tasks.txt");
}

void modify(vector<Task_manager> Tasks, vector<string> args, vector<vector<string>> values) {

	/* This function modifies some fields of the given Tasks. It finds the fields to modify by checking the key word entered by the user.
	To modify a field, you must add a 'm' at the end of the argument : for example '--titlem' in spite of '--title'. The function can then make the difference
	between the former and the new values.
	Example of use : --modify --title THE FORMER TITLE --titlem THE NEW TITLE. It will replace all Tasks whose name is THE FORMER TITLE and replace it with
	THE NEW TITLE */

	vector<string> former_args;
	vector<vector<string>> former_values;
	vector<string> new_args;
	vector<vector<string>> new_values;
	vector<string>::iterator it;

	// Catch the differents fields and values associated

	int incr = 0;
	for (it = args.begin(); it < args.end(); it++) {
		if ((*it)[it->size() -1] == 'm') {
			former_args.push_back((*it).substr(0, it->size() - 2));
			former_values.push_back(values[incr++]);
		} else {
			new_args.push_back(*it);
			new_values.push_back(values[incr++]);
		}
	}

	// Find the Tasks that are compatible with the former args

	vector<Task_manager> list_task = list(Tasks, former_args, former_values);

	// Remove that Tasks

	remove_tasks(list_task);

	// Then add the updated Task with the updated values in its fields

	vector<Task_manager>::iterator iter;
	vector<string>::iterator iter_args;
	int i = 0;
	for (iter = list_task.begin(); iter < list_task.end(); iter++) {
		Task_manager Task = *iter;

		// Replace the values in the fields given by the user (by adding a 'm' : --titlem THE TITLE will put THE TITLE as new title in the Task)

		for (iter_args = new_args.begin(); iter_args < new_args.end(); iter_args++) {
			if (*iter_args == "-title") {
				Task.title = sum(new_values[i]);
			} else if (*iter_args == "-description") {
				Task.description = sum(new_values[i]);
			} else if (*iter_args == "-begin") {
				Task.begin = sum(new_values[i]);
			} else if (*iter_args == "-end") {
				Task.end = sum(new_values[i]);
			} else if (*iter_args == "-progress") {
				Task.progress = sum(new_values[i]);
			} else if (*iter_args == "-avancement") {
				Task.avancement = stoi(sum(new_values[i]));
			} else if (*iter_args == "-priority") {
				Task.priority = sum(new_values[i]);
			} else if (*iter_args == "-comments") {
				Task.comments = new_values[i];
			} else if (*iter_args == "-under") {
				vector<string>::iterator it;
				for (it = new_values[i].begin(); it < new_values[i].end(); it++){
					Task.Under.push_back(stoi(*it));	
				}
			}
		}

		// Finaly add the updated Task to the file

		Task.add_to_file();
	}
}