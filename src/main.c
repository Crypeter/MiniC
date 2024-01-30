#include <common.h>
#include <token.h>
#include <lexer.h>
#include <color.h>
#include <parse.h>
Token tokens[65536] __attribute__((used)) = {};
int nr_token __attribute__((used))  = 0;
Line lines[65536] __attribute__((used)) = {};
int nr_line __attribute__((used))  = 0;
int main(int argc,const char *argv[]){
    //assert(argc >= 1);
    //assert(argv[1] != NULL);
    //printf("%s\n",argv[1]);
    init_regex();
    FILE *fp = fopen("/home/kkoapbd/Desktop/MiniC/test/test1.c","r");
    char buf[10240];
    fread(buf,sizeof(char),10240,fp);
    set_color(PR_BLUE);
    AST_tree minic_tree;
    make_lines(buf,lines,&nr_line);
    make_token(lines,&nr_line,minic_tree.tokens,&minic_tree.nr_token);
    Init_tree(&minic_tree);
    Make_Unit(minic_tree.root,minic_tree.tokens);
    Unit_print(&minic_tree);
    //token_print(minic_tree.tokens,minic_tree.nr_token);
}