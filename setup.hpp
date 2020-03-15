/* Includes */

#include <iostream>
#include<vector>
#include <ctime>
using namespace std;

//int top_ = 0;

int main() {
	cout << 1<< endl;
	return 0;
}

/*enum Status {Open,Closed,In_Progress};

enum Priority{Low,Normal,High,Super_High};

class Date{
protected:
	int day;
	int month;
	int year;
	int hour;
	int minute;

public:
	Date() {
		const time_t* ptr;
		tm time = *localtime(ptr);
		month = time.tm_mon + 1;
		day = time.tm_mday;
		year = time.tm_year + 1900;
		hour = time.tm_hour;
		minute = time.tm_min;
	}	;
};

class Task_manager {
protected:
	const char* title;
	const char* description;
	Date begin;
	Date end;
	Status progress;
	double avancement;
	Priority priority;
	vector<const char*> comments;
	vector<int> Under;

public:
	int ID;

    Task_manager(const char* _title,
				const char* _description,
				Priority _priority,
				vector<const char*> _comment,
				double _avancement,
				vector<int> _Under);
    //~Task_manager();
};

Task_manager::Task_manager(const char* _title = "Le titre",
						   const char* _description = "No description Yet",
						   Priority _priority = Normal,
						   vector<const char*> _comment = vector<const char*> {"No comment Yet"},
						   double _avancement = 0,
						   vector<int> _Under = vector<int> {})//:
	/*ID(++top_),
	title(_title),
	description(_description),
	begin(Date{}), //voir comment on gère le temps en C++
	end(Date{}),
	progress(Open),
	avancement(_avancement),
	comments(_comment),
	priority(_priority),
	Under(_Under)
{
	cout << top_ << endl;
};*/

