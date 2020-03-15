#include <stdio.h>
#include <time.h>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/gl.h>
//
// Simple GL window with dynamic popup menu
// erco 01/25/06
//
class MyGlWindow : public Fl_Gl_Window {
    void draw() {
        if (!valid()) {
            glLoadIdentity();
            glViewport(0,0,w(),h());
            glOrtho(-w(),w(),-h(),h(),-1,1);
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
    static void Menu_CB(Fl_Widget*, void *data) {
        char name[80];
        ((Fl_Menu_Button*)data)->item_pathname(name, sizeof(name)-1);
        fprintf(stderr, "Menu Callback: %s\n", name);
    }
    int handle(int e) {
        int ret = Fl_Gl_Window::handle(e);
        switch ( e ) {
            case FL_PUSH:
                if ( Fl::event_button() == 3 ) {
                    char tmp[80];
                    time_t t = time(NULL);
                    sprintf(tmp, "Time is %s", ctime(&t));
                    // Dynamically create menu, pop it up
                    Fl_Menu_Button menu(Fl::event_x_root(), Fl::event_y_root(), 80, 1);
                    menu.add(tmp);      // dynamic -- changes each time popup opens..
                    menu.add("Edit/Copy",  0, Menu_CB, (void*)&menu);
                    menu.add("Edit/Paste", 0, Menu_CB, (void*)&menu);
                    menu.add("Quit",       0, Menu_CB, (void*)&menu);
                    menu.popup();
                }
        }
        return(ret);
    }
public:
    // CONSTRUCTOR
    MyGlWindow(int X,int Y,int W,int H,const char*L=0) : Fl_Gl_Window(X,Y,W,H,L) {
    }
};

// MAIN
int main() {
     Fl_Window win(500, 300);
     MyGlWindow mygl(10, 10, win.w()-20, win.h()-20);
     win.show();
     return(Fl::run());
}
    