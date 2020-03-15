#include <vector>

using namespace std;

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
    	cout << "ID : " << ID << endl;
    	cout << "title : " << title << endl;
    	cout << "description : " << description << endl;
    	cout << "begin : " << begin << endl;
    	cout << "end : " << end << endl;
    	cout << "avancement : " << avancement <<  "%" << endl;
    	cout << "comments : ";
    	vector<string>::iterator it1;
    	for(it1 = comments.begin(); it1 != comments.end(); it1++){
    		cout << *it1 << " ,";
    	}
    	cout << endl;
    	cout << "Under : ";
    	vector<int>::iterator it2;
    	for(it2 = Under.begin(); it2 != Under.end(); it2++){
    		cout << *it2 << " ," << endl;
    	}
    	cout << endl;
    }

    void add_to_file();
    //~Task_manager();
};

Task_manager::Task_manager(int top):
	ID(top),
	title("Pas de titre"),
	description("Pas de description"),
	begin(""),
	end(""),
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

void Task_manager::add_to_file() {
	fstream file;
	file.open("Tasks.txt", ios::app);
	file << ID << "/";
	file << title << "/";
	file << description << "/ ";
	file << begin << "/ ";
	file << end << "/";
	if (progress == "Open") {
			file << 0 << "/";
	} else if (progress == "In_Progress") {
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
	} else if (priority == "Super_High") {
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