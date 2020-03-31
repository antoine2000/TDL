#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include "setup.h"
#include <unistd.h>

struct Info {
    // The widgets
    Fl_Int_Input* ID;
    Fl_Input* title;
    Fl_Input* description;
    Fl_Input* begin;
    Fl_Input* end;
    Fl_Input_Choice* progress;
    Fl_Int_Input* avancement;
    Fl_Input_Choice* priority;
    Fl_Multiline_Input* comments;
    Fl_Input* sub_tasks;
    Task_manager* Task;
    vector<Task_manager> Tasks;
};

struct list_done {
  Fl_Choice *choice;
  vector<Task_manager>* found;
};

understood get_values(Info* input){
  vector<string> args;
  vector<vector<string>> values;
  static char s[1000];
        // ID
  if (input -> ID != nullptr){
    if (input -> ID -> size() != 0){
      strcpy(s, (input -> ID -> value()));
      args.push_back("-ID");
      values.push_back(vector<string> {s});
    }    
  }

        // title
  if (input -> title -> size() != 0){
    strcpy(s, input -> title -> value());
    args.push_back("-title");
    values.push_back(vector<string> {s});
  }

        // description
  if (input -> description -> size() != 0){
    strcpy(s, input -> description -> value());
    args.push_back("-description");
    values.push_back(vector<string> {s});
  }
        // begin
  if (input -> begin -> size() != 0){
    strcpy(s, input -> begin -> value());
    args.push_back("-begin");
    values.push_back(vector<string> {s});
  }
        // end
  if (input -> end -> size() != 0){
    strcpy(s, input -> end -> value());
    args.push_back("-end");
    values.push_back(vector<string> {s});
  }
            // progress
  strcpy(s, input -> progress -> value());
  if ((string) s ==  (string) "Open" | (string) s == (string) "In-Progress" | (string) s == (string) "Closed"){
    args.push_back("-progress");
    values.push_back(vector<string> {s});
  }

        // avancement
  if (input -> avancement -> size() != 0){
    args.push_back("-avancement");
    values.push_back(vector<string> {to_string(atoi(input->avancement->value()))});
  }

        // priority
  strcpy(s, input -> priority -> value());
  if ((string) s == (string) "Low" | s == (string) "Normal" | (string) s == (string) "High" | (string) s == (string) "Super-High"){
    args.push_back("-priority");
    values.push_back(vector<string> {s});    
  }
        // comments
  if (input -> comments -> size() != 0){
    strcpy(s, input -> comments -> value());
    args.push_back("-comments");
    values.push_back(parse(s,"\n"));
  }  
        // under
  if (input -> sub_tasks -> size() != 0){
    strcpy(s, input -> sub_tasks -> value());
    args.push_back("-Under");
    values.push_back(parse(s,";"));
    vector<string>::iterator it;
  }
  understood param;
  param.args = args;
  param.values = values;
  return param;
}

void execute_modif(Fl_Widget* win, void* new_values){
  Info* input = reinterpret_cast<Info*>(new_values);
  // values to give as argument to the "modify" function
  understood param = get_values(input);
  param.args.push_back("-IDm");
  param.values.push_back(vector<string> {to_string(input -> Task -> ID)});
  vector<Task_manager> Tasks = setup();
  modify(Tasks, param.args, param.values);
  if (win -> parent() -> parent() -> parent() != nullptr){
    win -> parent() -> parent() -> parent() -> hide(); 
  } 
}

void modify_task(Fl_Widget *window, void* transmission){
  Info *input = reinterpret_cast<Info*>(transmission);
  Fl_Window* win = new Fl_Window(1000,1000, "modify");
  window -> parent() -> add(win);
  Info new_values;
  new_values.Tasks = input -> Tasks;
  new_values.Task = input -> Task;
  // old values
  int x = 50, y = 40, w = 100, h = 30;
  // title
  static char old_title[1000];
  strcpy(old_title, (" old title : " + input -> Task -> title).c_str());
  Fl_Box *title = new Fl_Box(x - 10, y, w, h, old_title);
  // description
  y += 35;
  static char old_description[1000];
  strcpy(old_description, ("old description : " + input -> Task -> description).c_str());
  Fl_Box *description = new Fl_Box(x + 77, y, w, h, old_description);
  //begin 
  y += 35;
  static char old_begin[1000];
  strcpy(old_begin, ("old begin : " + input -> Task -> begin).c_str());
  Fl_Box *begin = new Fl_Box(x + 13, y, w, h, old_begin);
  // end 
  y += 35;
  static char old_end[1000];
  strcpy(old_end, ("old end : " + input -> Task -> end).c_str());
  Fl_Box *end = new Fl_Box(x + 10, y, w, h, old_end);
  // Progress
  y += 35;
  static char old_progress[1000];
  strcpy(old_progress, ("old progress : " + input -> Task -> progress).c_str());
  Fl_Box *progress = new Fl_Box(x + 23, y, w, h, old_progress);
  // Avancement
  y += 35;
  static char old_avancement[1000];
  strcpy(old_avancement, ("old avancement : " + to_string(input -> Task -> avancement)).c_str());
  Fl_Box *avancement = new Fl_Box(x + 5, y, w, h, old_avancement);
  // Priority
  y += 35;
  static char old_priority[1000];
  strcpy(old_priority, ("old priority : " + input -> Task -> priority).c_str());
  Fl_Box *priority = new Fl_Box(x + 15, y, w, h, old_priority);
  // Comments
  y += 35;
  static char old_comments[10000];
  vector<string>::iterator it;
  h = 30 * (input -> Task -> comments).size();
  string text;
  for (it = (input -> Task -> comments).begin(); it != (input -> Task -> comments).end(); it++) {
    text += *it;
    if (it != (input -> Task -> comments).end()){
      text += "\n";
    }
  }
  strcpy(old_comments, ("old comments : " + text).c_str());
  Fl_Box *comments = new Fl_Box(x + 65, y, w, h, old_comments);
  // Under
  y += h + 15;
  static char old_Under[10000];
  vector<int>::iterator it2;
  h = 30 * (input -> Task -> Under).size();
  string text2;
  for (it2 = (input -> Task -> Under).begin(); it2 != (input -> Task -> Under).end(); it2++) {
    text2 += to_string(*it2);
     text2 += " ";
  }
  strcpy(old_Under, ("old sub-tasks : " + text2).c_str());
  Fl_Box *Under = new Fl_Box(x - 15, y, w, h, old_Under);
  // New values
  x = 600, y = 40, w = 100, h = 30;
  // title
  new_values.title = new Fl_Input(x - 55, y, w, h, "new title");
  new_values.title -> tooltip("new title");
  // description
  y += 35;
  new_values.description = new Fl_Input(x, y, w, h, "new description");
  new_values.description -> tooltip("new description");
  // begin
  y += 35;
  new_values.begin = new Fl_Input(x - 30, y, w, h, "new begin");
  new_values.begin -> tooltip("new begin");
  // end
  y += 35;
  new_values.end = new Fl_Input(x - 27, y, w, h, "new end");
  new_values.end -> tooltip("new end");
  // progress
  y += 35;
  new_values.progress = new Fl_Input_Choice(x, y, w, h, "new progress");
  new_values.progress -> tooltip("new progress");
  new_values.progress -> add("Open");
  new_values.progress -> add("In-Progress");
  new_values.progress -> add("Closed");
  // avancement
  y += 35;
  new_values.avancement = new Fl_Int_Input(x, y, w, h, "new avancement");
  new_values.avancement -> tooltip("new avancement");
  // priority
  y += 35;
  new_values.priority = new Fl_Input_Choice(x, y, w, h, "new priority");
  new_values.priority -> tooltip("new priority");
  new_values.priority -> add("Low");
  new_values.priority -> add("Normal");
  new_values.priority -> add("High");
  new_values.priority -> add("Super-High");

  y += 35;
  new_values.comments = new Fl_Multiline_Input(x + 35, y, w, h + 50,"comments");
  new_values.comments -> tooltip("comments");

  y += 85;
  new_values.sub_tasks = new Fl_Input(x + 30, y, w - 30, h,"sub_tasks");
  new_values.sub_tasks -> tooltip("sub_tasks");


  Fl_Button *done = new Fl_Button(350,470,100,30,"done");
  done -> callback(execute_modif, &new_values);
  win -> end();
  win -> show();
  int i = Fl::run();
}

void affiche_task(Task_manager Task){

    // ID
  static char string_ID[1000];
  strcpy(string_ID, ("ID : " + to_string(Task.ID)).c_str());
  Fl_Box *ID = new Fl_Box(30, 70, 20, 30,string_ID);
    // title
  static char string_title[1000];
  strcpy(string_title, Task.title.c_str());
  Fl_Box *title = new Fl_Box(275,70, 250, 30, string_title);
    // description
  static char string_description[1000];
  strcpy(string_description, Task.description.c_str());
  Fl_Box *description = new Fl_Box(275 ,110, 250, 30, string_description);
    // date begin
  static char string_begin[1000];
  strcpy(string_begin, Task.begin.c_str());
  Fl_Box *begin = new Fl_Box(550,70, 90, 30, string_begin);
  Fl_Box *between_begin_and_end = new Fl_Box(650, 70, 10, 30, " -> ");
    // date end
  static char string_end[1000];
  strcpy(string_end, Task.end.c_str());
  Fl_Box *end = new Fl_Box(680,70, 90, 30, string_end);
    // progress
  static char string_progress[1000];
  strcpy(string_progress, ("progress : " + Task.progress).c_str());
  Fl_Box *progress = new Fl_Box(100,150, 300, 30, string_progress);
    // avancement
  static char string_avancement[1000];
  strcpy(string_avancement, ("avancement : " + to_string(Task.avancement)).c_str());
  Fl_Box *avancement = new Fl_Box(450,150, 150, 30, string_avancement);
    // priority
  static char string_priority[1000];
  strcpy(string_priority, ("priority : " + Task.priority).c_str());
  Fl_Box *priority = new Fl_Box(325,190, 475, 30, string_priority);
}


void get_item(Fl_Widget *w, void *menu){

  /* This function displays a Task */

  list_done *input = reinterpret_cast<list_done*>(menu);
  const char* name = input-> choice -> mvalue() -> label();
  vector<Task_manager>::iterator it;
  Info transmission;
  vector<Task_manager> Tasks = *(input -> found);
  transmission.Tasks = Tasks;
  for (it = Tasks.begin(); it != Tasks.end(); it++) {
    if (("ID = " + to_string((*it).ID) + "  title = : " + ((*it).title)) == name) {
      w -> parent() -> size(800,500);
      Fl_Window *win = new Fl_Window(800,500,name);
      w -> parent() -> add(win);
      Task_manager Task = *it;
      transmission.Task = &Task;
      static char string_ID[1000];
      strcpy(string_ID, ("ID : " + to_string(Task.ID)).c_str());
      Fl_Box *ID = new Fl_Box(50, 10, 20, 30,string_ID);
      ID -> labelsize(30);
        // title
      static char string_title[1000];
      strcpy(string_title, Task.title.c_str());
      Fl_Box *title = new Fl_Box(275,10, 280, 30, string_title);
      title -> labelsize(30);
        // description
      static char string_description[1000];
      strcpy(string_description, Task.description.c_str());
      Fl_Box *description = new Fl_Box(275 ,70, 250, 30, string_description);
      description -> labelsize(30);
        // date begin
      static char string_begin[1000];
      strcpy(string_begin, Task.begin.c_str());
      Fl_Box *begin = new Fl_Box(600,10, 90, 30, string_begin);
      Fl_Box *between_begin_and_end = new Fl_Box(695, 10, 10, 30, " -> ");
        // date end
      static char string_end[1000];
      strcpy(string_end, Task.end.c_str());
      Fl_Box *end = new Fl_Box(710,10, 90, 30, string_end);
        // progress
      static char string_progress[1000];
      strcpy(string_progress, ("progress : \n" + Task.progress).c_str());
      Fl_Box *progress = new Fl_Box(100,200, 75, 30, string_progress);
      progress -> labelsize(30);
        // avancement
      static char string_avancement[1000];
      strcpy(string_avancement, ("avancement : \n" + to_string(Task.avancement)).c_str());
      Fl_Box *avancement = new Fl_Box(350,200, 75, 30, string_avancement);
      avancement -> labelsize(30);
        // priority
      static char string_priority[1000];
      strcpy(string_priority, ("priority : \n" + Task.priority).c_str());
      Fl_Box *priority = new Fl_Box(600,200, 75, 30, string_priority);
      priority -> labelsize(30);
      Fl_Button *modify = new Fl_Button(330, 300, 140, 30, "modify");
      modify -> labelsize(30);
      modify -> callback(modify_task,&transmission);
      win -> end();
      win -> show();
      int i = Fl::run();
    }
  }
}

int affiche_list(vector<Task_manager> found) {
  Fl_Window *window = new Fl_Window(800,300, "result");
  Fl_Choice *choice = new Fl_Choice(200, 30, 400, 30, "list of results");
  window -> add(choice);
  Fl_Button *done = new Fl_Button(630, 30, 30 , 30, "search");
  vector<Task_manager>::iterator it;
  char s[1000];
  for (it = found.begin(); it < found.end(); it++){
    strcpy(s, ("ID = " + to_string((*it).ID) + "  title = : " + ((*it).title)).c_str());
    choice -> add(s);
  }
  list_done menu;
  menu.choice = choice;
  menu.found = &found;
  done -> callback(get_item, &menu);
  window -> end();
  window -> show();
  return Fl::run();
}

void done_list(Fl_Widget *wh, void* parameter) {
  Info* input = reinterpret_cast<Info*>(parameter);
  understood param = get_values(input);
  vector<Task_manager> found = list(setup(), param.args, param.values);
  int i = affiche_list(found);
    
}

void list_graphic(Fl_Widget *wh){
  Fl_Window *window = new Fl_Window(800,800,"List");
  Fl_Box *head = new Fl_Box(10,10,780,100,"Veuillez lister les caractéristiques des tâches à trouver");
  head -> labelsize(20);
  Info input;
  int x = 80, y = 110, w = 660, h = 30;
  input.ID = new Fl_Int_Input(x - 10, y, w + 10, h, "ID");
  input.ID -> tooltip("ID");

  y += 35;
  input.title = new Fl_Input(x, y, w, h,"title");
  input.title -> tooltip("title");

  y += 35;
  input.description = new Fl_Input(x + 50, y, w - 50, h,"description");
  input.description -> tooltip("description");

  y += 35;
  input.begin = new Fl_Input(x + 10 , y, w - 10 , h,"begin");
  input.begin -> tooltip("begin");

  y += 35;
  input.end = new Fl_Input(x - 5, y + 5, w, h,"end");
  input.end -> tooltip("end");

  y += 40;
  input.progress = new Fl_Input_Choice(x + 30, y, w - 30, h, "progress");
  input.progress -> tooltip("progress");
  input.progress -> add("Open");
  input.progress -> add("In-Progress");
  input.progress -> add("Closed");

  y += 35;
  input.avancement = new Fl_Int_Input(x + 53, y, w - 53, h, "avancement");

  y += 35;
  input.priority = new Fl_Input_Choice(x + 20, y, w - 20, h, "priority");
  input.priority -> tooltip("priority");
  input.priority -> add("Low");
  input.priority -> add("Normal");
  input.priority -> add("High");
  input.priority -> add("Super-High");

  y += 35;
  input.comments = new Fl_Multiline_Input(x + 35, y, w - 35, h + 50,"comments");
  input.comments -> tooltip("comments");

  y += 85;
  input.sub_tasks = new Fl_Input(x + 30, y, w - 30, h,"sub_tasks");
  input.sub_tasks -> tooltip("sub_tasks");

  y += 35;
  Fl_Button *done = new Fl_Button(x + 150,y,w- 250,h,"done");
  done -> callback(done_list, &input);
  window -> show();
  int i = Fl::run();
}

void modify_graphic(Fl_Widget *w){
  vector<Task_manager> Tasks = setup();
  int i = affiche_list(Tasks);
}

void process_delete(Fl_Widget *w, void* parameter){
  Info* Input = reinterpret_cast<Info*>(parameter);

  understood param = get_values(Input);
  vector<Task_manager> Tasks = setup();
  vector<Task_manager> list_task = list(Tasks, param.args, param.values);
  remove_tasks(list_task);
}

void delete_task_by_elements(Fl_Widget *wh){
  Fl_Window *win = new Fl_Window(800,800,"Delete some tasks giving some elements");
  Fl_Box *head = new Fl_Box(10,10,780,100,"Veuillez lister les caractéristiques des tâches à supprimer");
  head -> labelsize(20);
  Info input;
  int x = 80, y = 110, w = 660, h = 30;
  input.title = new Fl_Input(x, y, w, h,"title");
  input.title -> tooltip("title");

  y += 35;
  input.description = new Fl_Input(x + 50, y, w - 50, h,"description");
  input.description -> tooltip("description");

  y += 35;
  input.begin = new Fl_Input(x + 10 , y, w - 10 , h,"begin");
  input.begin -> tooltip("begin");

  y += 35;
  input.end = new Fl_Input(x - 5, y + 5, w, h,"end");
  input.end -> tooltip("end");

  y += 40;
  input.progress = new Fl_Input_Choice(x + 30, y, w - 30, h, "progress");
  input.progress -> tooltip("progress");
  input.progress -> add("Open");
  input.progress -> add("In-Progress");
  input.progress -> add("Closed");

  y += 35;
  input.avancement = new Fl_Int_Input(x + 53, y, w - 53, h, "avancement");

  y += 35;
  input.priority = new Fl_Input_Choice(x + 20, y, w - 20, h, "priority");
  input.priority -> tooltip("priority");
  input.priority -> add("Low");
  input.priority -> add("Normal");
  input.priority -> add("High");
  input.priority -> add("Super-High");

  y += 35;
  input.comments = new Fl_Multiline_Input(x + 35, y, w - 35, h + 50,"comments");
  input.comments -> tooltip("comments");

  y += 85;
  input.sub_tasks = new Fl_Input(x + 30, y, w - 30, h,"sub_tasks");
  input.sub_tasks -> tooltip("sub_tasks");

  y += 35;
  Fl_Button *done = new Fl_Button(x + 150,y,w- 250,h,"done");

  done -> callback(process_delete,&input);

  win -> end();
  win -> show();

  int i = Fl::run();
}

void delete_task_by_id(Fl_Widget *w){
  Fl_Window *win = new Fl_Window(200,100,"Delete a task giving its ID");
  Fl_Button *done = new Fl_Button(50,50,100,30,"done");
  Info Input;
  Input.ID = new Fl_Int_Input(30,10,160,30,"ID");
  done -> callback(process_delete,&Input);
  win -> end();
  win -> show();
  int i = Fl::run();
}

void Delete_graphic(Fl_Widget *w){
  Fl_Window *win = new Fl_Window(800,800,"Deleting Tasks");
  Fl_Button *by_id = new Fl_Button(10,10,780,100,"Delete by ID");
  Fl_Button *by_elements = new Fl_Button(10,110,780,100,"Delete by other elements");
  by_id -> tooltip("Delete a task giving its ID");
  by_elements -> tooltip("Possibility to delete more than one task in a single time.");
  by_id -> callback(delete_task_by_id);
  by_elements -> callback(delete_task_by_elements);
  win -> end();
  win -> show();
}

void done_create(Fl_Widget *wh, void* parameter){
    Info* input = reinterpret_cast<Info*>(parameter);

    understood param = get_values(input);
    vector<Task_manager> Tasks = setup();
    create(Tasks, param.args, param.values);
}

void create_graphic(Fl_Widget *wh){
  Fl_Window *window = new Fl_Window(800,800,"create a Task");
  Info input;
  int x = 80, y = 50, w = 660, h = 30;

  input.title = new Fl_Input(x, y, w, h,"title");
  input.title -> tooltip("title");

  y += 35;
  input.description = new Fl_Input(x + 50, y, w - 50, h,"description");
  input.description -> tooltip("description");

  y += 35;
  input.begin = new Fl_Input(x + 10 , y, w - 10 , h,"begin");
  input.begin -> tooltip("begin");

  y += 35;
  input.end = new Fl_Input(x - 5, y + 5, w, h,"end");
  input.end -> tooltip("end");

  y += 40;
  input.progress = new Fl_Input_Choice(x + 30, y, w - 30, h, "progress");
  input.progress -> tooltip("progress");
  input.progress -> add("Open");
  input.progress -> add("In-Progress");
  input.progress -> add("Closed");

  y += 35;
  input.avancement = new Fl_Int_Input(x + 53, y, w - 53, h, "avancement");

  y += 35;
  input.priority = new Fl_Input_Choice(x + 20, y, w - 20, h, "priority");
  input.priority -> tooltip("priority");
  input.priority -> add("Low");
  input.priority -> add("Normal");
  input.priority -> add("High");
  input.priority -> add("Super-High");

  y += 35;
  input.comments = new Fl_Multiline_Input(x + 35, y, w - 35, h + 50,"comments");
  input.comments -> tooltip("comments");

  y += 85;
  input.sub_tasks = new Fl_Input(x + 30, y, w - 30, h,"sub_tasks");
  input.sub_tasks -> tooltip("sub_tasks");

  y += 35;
  Fl_Button *done = new Fl_Button(x + 150,y,w- 250,h,"done");
  done -> callback(done_create, &input);
  window -> show();
  int i = Fl::run();
}

int run_graphic() {
  Fl_Window *window = new Fl_Window(800,800,"To Do List");
  Fl_Button *create = new Fl_Button(10,10,780,100,"Create Task");
  Fl_Button *list = new Fl_Button(10,110,780,100,"List Tasks");
  Fl_Button *modify = new Fl_Button(10,210,780,100,"Modify Existing Task");
  Fl_Button *Delete = new Fl_Button(10,310,780,100,"Delete Existing Task");
  list->callback(list_graphic);
  modify->callback(modify_graphic);
  Delete->callback(Delete_graphic);
  create->callback(create_graphic);
	window -> show();
	return Fl::run();
}