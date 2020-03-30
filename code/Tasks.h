#include <vector>
#include <time.h>

using namespace std;

struct tm* get_time() {
	time_t rawtime;
	struct tm * ptm;
	time (&rawtime);
	ptm = gmtime (&rawtime);
	return ptm;
}

string time_to_string(struct tm* ptm){
	string output;
	output += to_string(ptm->tm_mday);
	output += "-";
	output += to_string(ptm->tm_mon + 1);
	output += "-";
	output += to_string(ptm->tm_year + 1900);
	return output;
}

bool test_line(string input){

	/* This functions tests the input of the user, we check it doesn't contains a '/' */

	bool check = true;
	for (int i = 0; i < input.size(); i++){
		if (input[i] == '/') {
			check = false;
		}
	}
	return check;
}

bool is_int(string s) {

	/* This functions tests the input of the user, we check it is an int */

	if (s.empty()){
		return false;
	}
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i]) && s[i] != ' ') {
			return false;
		} 
	}
	return true;
}

class Task_manager {
public:
	int ID;
	string title;
	string description;
	string begin;
	string end;
	string progress;
	int avancement;
	string priority;
	vector<string> comments;
	vector<int> Under;

    Task_manager(int top);

    Task_manager(int top,
    			string _title,
				string _description,
				string _begin,
				string _end,
				string _var,
				int _avancement,
				string _priority,
	            vector<string> _comment,
				vector<int> _Under);

    void print() {
    	cout << endl;
    	cout << "ID : " << ID;
    	cout << "                                   title : " << title << endl;
    	cout << "				      description : " << description << endl;
    	cout << "			        begin : " << begin ;
    	cout << "   ->   end : " << end << endl;
    	cout << "			  progress: " << progress;
    	cout << " ||  avancement : " << avancement <<  "%";
    	cout << " ||  priority : " << priority << endl;
    	cout << "			comments : ";
    	vector<string>::iterator it1;
    	for(it1 = comments.begin(); it1 != comments.end(); it1++){
    		cout << *it1 << " ;";
    	}
    	cout << endl;
    	cout << "			Under : ";
    	vector<int>::iterator it2;
    	for(it2 = Under.begin(); it2 != Under.end(); it2++){
    		cout << *it2 << " ,";
    	}
    	cout << endl;
    	cout << "   =====================================================================================================================" << endl;
    }
    bool is_wrong();

    void add_to_file();
    //~Task_manager();
};

Task_manager::Task_manager(int top):
	ID(top),
	title("Pas de titre"),
	description("Pas de description"),
	begin(time_to_string(get_time())),
	end(time_to_string(get_time())),
	progress("Open"),
	avancement(0),
	priority("Normal"),
	comments(vector<string> {"Pas de commentaires"}),
	Under(vector<int> {-1}) {};
 	
Task_manager::Task_manager(int top,
						   string _title,
						   string _description,
						   string _begin,
						   string _end,
						   string _var,
						   int _avancement,
						   string _priority,
						   vector<string> _comment,
						   vector<int> _Under = vector<int> {-1}):
	ID(top),
	title(_title),
	description(_description),
	begin(_begin),
	end(_end),
	progress(_var),
	avancement(_avancement),
	priority(_priority),
	comments(_comment),
	Under(_Under) {};

bool Task_manager::is_wrong() {

	// Under and avancement have already been tested

	bool tested_positive = false;
	if (not test_line(title)){
		tested_positive = true;
	} else if (not test_line(description)){
		tested_positive = true;
	} else if (not test_line(begin)){
		tested_positive = true;
	} else if (not test_line(end)){
		tested_positive = true;
	} else if (not test_line(progress)){
		tested_positive = true;
	} else if (not test_line(priority)){
		tested_positive = true;
	}
	// comments
	vector<string>::iterator it;
	for (it = comments.begin(); it != comments.end(); it++) {
		if (not test_line(*it)){
			tested_positive = false;
			break;
		}
	}
	return tested_positive;
}

void Task_manager::add_to_file() {
	if (not is_wrong()) {
		fstream file;
		file.open("Tasks.txt", ios::app);
		file << ID << "/";
		file << title << "/";
		file << description << "/ ";
		file << begin << "/ ";
		file << end << "/";
		if (progress == "Open") {
				file << 0 << "/";
		} else if (progress == "In-Progress") {
				file << 1 << "/";		
		} else if (progress == "Closed") {
				file << 2 << "/";	
		}
		file << avancement << "/";
		if (priority == "Low"){
				file << 0 << "/";
		} else if (priority == "Normal") {
				file << 1 << "/";
		} else if (priority == "High") {
				file << 2 << "/";
		} else if (priority == "Super-High") {
				file << 3 << "/" ;		
		}
		vector<string>::iterator it1;
		for (it1 = comments.begin(); it1 != comments.end(); it1++) {
			file << *it1 << ";" ;
		}
		file << "/";
		vector<int>::iterator it2;
		for (it2 = Under.begin(); it2 != Under.end(); it2++) {
			file << *it2 << ";";
		} 
		if (Under.begin() == Under.end()) {
			file << "-1;";
		}
		file << "/" << "\n";
		file.close();
	}
}