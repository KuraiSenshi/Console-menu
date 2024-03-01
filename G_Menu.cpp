#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "constants.h"


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setCursorLocation(short x, short y) {
    SetConsoleCursorPosition(hStdOut, {x, y} );
}

void ConsoleCursorVisibe(bool show, short size) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = show;
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
}


void get_menu(std::vector<std::string>& menu, int active_menu) {
    int x = coordinates::X, y = coordinates::Y;
    setCursorLocation(x, y);
    
    for (int i = 0; i < menu.size(); i++) {
        if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

        setCursorLocation(x, y++);
        std::cout << menu[i] << std::endl;
    }

}

//void show_option(std::string& selected) {
//    system("CLS");
//    setCursorLocation(coordinates::X, coordinates::Y);
//    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
//    std::cout << "You chose " << selected << " ";
//    _getch();
//    system("CLS");
//}

void menu_pick_load() {
    int x = 42, y = coordinates::Y;
    system("CLS");
    setCursorLocation(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "No saves were found. Press \"Esc\" to return" << " ";

    while (_getch() != buttons::ESC);
    system("CLS");
}

void menu_pick_newgame() {
    int x = 42, y = coordinates::Y;
    system("CLS");
    setCursorLocation(x, y);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "Startin a new game. Press \"Enter\" to confirm " << " ";
    
    while (_getch() != buttons::ENTER);
    system("CLS");
}

void menu_pick_settings() {
    system("CLS");
    std::vector<std::string> settings = { "difficulty", "brightness", "sensitivity", "controlling" };
    int x = coordinates::X, y = coordinates::Y;
    setCursorLocation(x, y);

    for (auto& s : settings) {
        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        setCursorLocation(x, y++);
        std::cout << s << std::endl;
    }

    _getch();
    system("CLS");
}

void option_selected(int picked, std::string& option) {
    switch (picked) {
        case 0:
            menu_pick_newgame();
            //exit(0);
            break;
        case 1:
            menu_pick_load();
            break;
        case 2:
            menu_pick_settings();
            break;
        case 3:
            exit(0);
    }
}

int main(){
    
    SetConsoleTitle(L"Your residence");
    //setCursorLocation(50, 13);
    ConsoleCursorVisibe(false, 10);

    std::vector<std::string> menu = {"New game", "Load", "Settings", "Escape"};
    int active_menu = 0;
    char ch;
    
    while (true) {
        
        get_menu(menu, active_menu);
        
        ch = _getch();
        if (ch == -32) ch = _getch();

        switch (ch) {
            case buttons::ESC: exit(0);

            case buttons::UP:
                active_menu = max(0, active_menu-1); 
			    break;
		    case buttons::DOWN:
                active_menu = min(menu.size()-1, active_menu + 1);
                break;
            case buttons::ENTER:
                option_selected(active_menu, menu[active_menu]);
                break;
        }

    }
    
    return EXIT_SUCCESS;
}
