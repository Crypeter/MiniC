#ifndef ___minic_parse___
#define ___minic_parse___
#include <token.h>
enum{
    Program,Unit,
};

typedef struct ast_node{
    int left,right;
    int type;
    int Grammer_rule;
    struct ast_node *son,*brother;
}AST_Node;

typedef struct ast_tree{
    Token tokens[65536];
    int nr_token;
    AST_Node *root;
}AST_tree;

void Init_tree(AST_tree *);

void Make_Unit(AST_Node *progarm,Token *tokens);

#endif