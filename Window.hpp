//
// Created by Denys Burtnjak on 6/23/18.
//

#ifndef RUSH_WINDOW_HPP
#define RUSH_WINDOW_HPP


#include <ncurses.h>

class Window {
private:
    Window();
    WINDOW  *_background;
    WINDOW  *_window;

    int _bgW;
    int _bgH;
    int _w;
    int _h;

public:
    ~Window();
    Window(Window const & obj);
    Window(int w, int h, int w_start, int h_start);

    Window &operator=(Window const &obj);

    void    refreshAll();
    WINDOW  *getWindow();
};


#endif //RUSH_WINDOW_HPP
