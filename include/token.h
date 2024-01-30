#ifndef ___minic_token___
#define ___minic_token___
#define NR_REGEX sizeof(rules)/sizeof(rules[0])
enum{
    TK_NOTYPE = 256,TK_NEWLINE,
    TK_LP,TK_RP,TK_LC,TK_RC,TK_LB,TK_RB,
    TK_INT,TK_FLOAT,TK_VOID,TK_CHAR,
    TK_RETURN,TK_STRUCT,
    TK_IF_NO_ELSE,TK_IF_ELSE,TK_ELSE,
    TK_WHILE,TK_BREAK,
    TK_AS,TK_ADD_AS,TK_SUB_AS,TK_MUL_AS,TK_DIV_AS,TK_MOD_AS,
    TK_ADD,TK_SUB,TK_MUL,TK_DIV,TK_MOD,TK_ADD_ADD,TK_SUB_SUB,
    TK_AND,TK_OR,TK_NOT,
    TK_SEMI,TK_COMMA,TK_DOT,
    TK_RELOP,
    TK_10_NUMBER,TK_8_NUMBER,TK_16_NUMBER,
    TK_STRING,TK_FLOAT_NUMBER,TK_ID,
};

struct rule {
    const char *regex;
    int token_type;
} rules[] = {
    {"[ \r\t\n]+",TK_NOTYPE},

    //{"([0-9]*\\.[0-9]+)|([0-9]+\\.)|(0-9)*\\.[0-9]+e(-)?[0-9]+)",TK_FLOAT_NUMBER},
    
    {"[0](0|[1-7][0-7])",TK_8_NUMBER},
    {"(0x|0X)[0-9A-Fa-f]+",TK_16_NUMBER},
    {"0|([1-9][0-9]*)",TK_10_NUMBER},

    //
    {"\'[^'\\]\'",TK_STRING},

    {"int",TK_INT},
    {"void",TK_VOID},
    //{"float",TK_FLOAT},
    {"char",TK_CHAR},
    {"struct",TK_STRUCT},

    {"return",TK_RETURN},
    {"if",TK_IF_NO_ELSE},
    {"else",TK_ELSE},
    {"while",TK_BREAK},

    {"[a-zA-Z_][a-zA-Z0-9_]*",TK_ID},

    {"[{]",TK_LC},
    {"[}]",TK_RC},
    {"[(]",TK_LP},
    {"[)]",TK_RP},
    {"[[]",TK_LB},
    {"[]]",TK_RB},

    {";",TK_SEMI},
    {",",TK_COMMA},
    {"[.]",TK_DOT},
    {">|<|>=|<=|==|!=",TK_RELOP},
    {"=",TK_AS},
    {"[+=]",TK_ADD_AS},
    {"-=",TK_SUB_AS},
    {"[*=]",TK_MUL_AS},
    {"/=",TK_DIV_AS},
    {"%=",TK_MOD_AS},

    {"[++]",TK_ADD_ADD},
    {"[--]",TK_SUB_SUB},

    {"[+]",TK_ADD},
    {"[-]",TK_SUB},
    {"[*]",TK_MUL},
    {"[/]",TK_DIV},
    {"[%]",TK_MOD},
    {"&&",TK_AND},
    {"[|][|]",TK_OR},
    {"!",TK_NOT},
};

typedef struct token {
  int type;
  char str[32];
  int line_number;
} Token;

typedef struct line {
    char str[256];
    int line_number;
} Line;
#endif