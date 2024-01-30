#include <parse.h>
enum colors{
    PR_BLACK,PR_RED,PR_GREEN,
    PR_YELLOW,PR_BLUE,PR_PURPLE,
    PR_CYAN,PR_WHITE,
    PR_BRIGHT_BLACK,PR_BRIGHT_RED,PR_BRIGHT_GREEN,
    PR_BRIGHT_YELLOW,PR_BRIGHT_BLUE,PR_BRIGHT_PURPLE,
    PR_BRIGHT_CYAN,PR_BRIGHT_WHITE,
    BG_BLACK,BG_RED,BG_GREEN,
    BG_YELLOW,BG_BLUE,BG_PURPLE,
    BG_CYAN,BG_WHITE,
    BG_BRIGHT_BLACK,BG_BRIGHT_RED,BG_BRIGHT_GREEN,
    BG_BRIGHT_YELLOW,BG_BRIGHT_BLUE,BG_BRIGHT_PURPLE,
    BG_BRIGHT_CYAN,BG_BRIGHT_WHITE,
};

int set_color(int color);

int token_print(Token *tokens,const int left,const int right);

int Unit_print(AST_tree* minic_tree);

const char *colors_set[] = {
    "\033[1;30m","\033[1;31m","\033[1;32m",
    "\033[1;33m","\033[1;34m","\033[1;35m",
    "\033[1;36m","\033[1;37m",
    "\033[1;90m","\033[1;91m","\033[1;92m",
    "\033[1;93m","\033[1;94m","\033[1;95m",
    "\033[1;96m","\033[1;97m",
    "\033[1;40m","\033[1;41m","\033[1;42m",
    "\033[1;43m","\033[1;44m","\033[1;45m",
    "\033[1;46m","\033[1;47m",
    "\033[1;100m","\033[1;101m","\033[1;102m",
    "\033[1;103m","\033[1;104m","\033[1;105m",
    "\033[1;106m","\033[1;107m",
};