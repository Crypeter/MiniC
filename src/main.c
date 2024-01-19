#include <common.h>
#include <token.h>
#include <lexer.h>
#include <color.h>
Token tokens[65536] __attribute__((used)) = {};
int nr_token __attribute__((used))  = 0;
int main(int argc,const char *argv[]){
    assert(argc >= 1);
    assert(argv[1] != NULL);
    printf("%s\n",argv[1]);
    init_regex();
    FILE *fp = fopen(argv[1],"r");
    char buf[10240];
    fread(buf,sizeof(char),10240,fp);
    set_color(PR_BLUE);
    make_token(buf,tokens,&nr_token);
    token_print(tokens,nr_token);
}