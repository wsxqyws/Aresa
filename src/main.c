#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "Monster.h"

#ifndef ESC
#define ESC 27
#endif

void play_game();
bool handle_user_input();
void attack(Monster *m);
void prepare_game();
void destory_game();

Monster *g_monster = NULL;

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "en_US.UTF-8");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    prepare_game();
    play_game();
    destory_game();

    endwin();

    return 0;
}

void prepare_game()
{
    g_monster = malloc(sizeof(Monster));
    if (g_monster == NULL) {
        printw("Can not allocate memory");
        exit(1);
    }
    strcpy(g_monster->name, "Slime");
    g_monster->max_hp = 5;
    g_monster->hp = 5;
}

void destory_game()
{
    free(g_monster);
}

void play_game()
{
    int ch;
    bool is_game_end = false;
    while (true) {
        is_game_end = handle_user_input();
        if (is_game_end) {
            break;
        }
    }
}

bool handle_user_input()
{
    int ch = getch();
    if (ch == ESC) {
        return true;
    } else if (ch == 'a') {
        attack(g_monster);
        printw("Attack on %s, (%d/%d)\n", g_monster->name, g_monster->hp, g_monster->max_hp);
    }
    return false;
}

void attack(Monster *m)
{
    int damage = 1;
    m->hp -= damage;
    if (m->hp < 0) {
        m->hp = 0;
    }
}
