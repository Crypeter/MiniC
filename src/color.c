#include <parse.h>
#include <token.h>
#include <color.h>
#include <common.h>

int set_color(int color){
    if(color >= 32)return -1;
    else{
        printf("%s",colors_set[color]);
    }
    return color;
}

int token_print(Token *tokens,const int left,const int right){
    for(int i = left;i<=right;i++){
        switch (tokens[i].type)
        {
        case TK_LP:
        case TK_RP:
        case TK_LC:
        case TK_RC:set_color(PR_PURPLE);break;
        case TK_LB:
        case TK_RB:set_color(PR_GREEN);break;
        case TK_CHAR:
        case TK_VOID:
        case TK_FLOAT:
        case TK_INT:set_color(PR_BLUE);break;
        case TK_ID:set_color(PR_YELLOW);break;
        case TK_10_NUMBER:
        case TK_8_NUMBER:
        case TK_16_NUMBER:
        case TK_FLOAT_NUMBER:set_color(PR_BRIGHT_BLACK);break;
        case TK_STRING:set_color(PR_BRIGHT_YELLOW);break;
        default:
            set_color(PR_WHITE);
            break;
        }
        printf("%s",tokens[i].str);
    }
    return right - left;
}

int Unit_print(AST_tree* minic_tree){
    assert(minic_tree->root->type == Program);
    AST_Node *now_Unit = minic_tree->root->son;
    int count = 0;
    while(now_Unit != NULL){
        if(count%2 == 1)set_color(BG_RED);
        else set_color(BG_BLACK);
        token_print(minic_tree->tokens,now_Unit->left,now_Unit->right);
        now_Unit = now_Unit->brother;
        count++;
    }
    return count;
}