#include <parse.h>
#include <common.h>
void Init_tree(AST_tree *tree)
{
    tree->root = (AST_Node *)malloc(sizeof(AST_Node));
    AST_Node *root = tree->root;
    root->type = Program;
    root->left = 0;
    root->son = (AST_Node *)malloc(sizeof(AST_Node));
    root->right = tree->nr_token - 1;
    root->brother = NULL;
}
int find_parentheses(int left, int right, Token *tokens, int find_type)
{
    int to_find_type, depth = 1, to_find_place = -1;
    if (find_type == TK_SEMI)
        return left;
    switch (find_type)
    {
    case TK_LC:
        to_find_type = TK_RC;
        break;
    case TK_LB:
        to_find_type = TK_RB;
        break;
    case TK_LP:
        to_find_type = TK_RP;
        break;
    default:
        assert(0);
        break;
    }
    for (int i = left + 1; i <= right; i++)
    {
        if (tokens[i].type == find_type)
            depth++;
        else if (tokens[i].type == to_find_type)
            depth--;
        if (depth == 0)
        {
            to_find_place = i;
            break;
        }
    }
    assert(to_find_place > left);
    assert(to_find_place > 0);
    return to_find_place;
}
void Make_Unit(AST_Node *progarm, Token *tokens)
{
    int left = progarm->left, right = progarm->right;
    if (left > right)
    {
        printf("left = %d,right = %d\n",left,right);
        printf("Bad Program\n");
        exit(-1);
    }
    else
    {
        int last_end_place = -1;
        AST_Node *now = progarm->son;
        for (int i = left; i <= right; i++)
        {
            //int last_end_place = -1;
            //AST_Node *now = progarm->son;
            if (tokens[i].type == TK_SEMI || tokens[i].type == TK_LC)
            {
                now->type = Unit;
                now->left = last_end_place + 1;
                i = find_parentheses(i, right, tokens, tokens[i].type);
                now->right = i;
                last_end_place = i;
                if (i < right)
                {
                    now->brother = (AST_Node *)malloc(sizeof(AST_Node));
                    now = now->brother;
                }
                else{
                    now->brother = NULL;
                }
            }
        }
    }
}
