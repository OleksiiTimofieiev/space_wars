//
// Created by Denys Burtnjak on 6/23/18.
//

#include "Window.hpp"
#include "constants.hpp"

Window::Window() {

}

Window::~Window() {
    delwin(this->_window);
    delwin(this->_background);
}

Window::Window(Window const &obj) {
    *this = obj;
}

Window::Window(int w, int h, int w_start, int h_start) {
    this->_bgH = h;
    this->_bgW = w;
    this->_h = h - 2;
    this->_w = w - 4;
    this->_background = newwin(this->_bgH, this->_bgW, h_start, w_start);
    this->_window = newwin(this->_h, this->_w, h_start + 1, w_start + 2);
    init_pair(BG_COLOR, COLOR_RED, COLOR_GREEN | COLOR_RED);
    wbkgd(this->_background, COLOR_PAIR(BG_COLOR));
    refresh();
    wrefresh(this->_background);
}

void Window::refreshAll() {
    wrefresh(this->_window);
}

WINDOW *Window::getWindow() {
    return this->_window;
}

Window &Window::operator=(Window const &obj) {
    if (this == &obj)
        return *this;
    _background = obj._background;
    _window = obj._window;
    _bgW = obj._bgW;
    _bgH = obj._bgH;
    _w = obj._w;
    _h = obj._h;
    return *this;
}
