#include <common.h>
#include <token.h>
#include <lexer.h>
static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */

void init_regex() {
  int i;
  char error_msg[128];
  int ret;
  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      printf("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
      exit(-1);
    }
  }
}

bool make_token(char *e,Token *tokens,int *nr_token) {
  int position = 0;
  int i;
  regmatch_t pmatch;
  *nr_token = 0;
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
        if(rules[i].token_type != TK_NOTYPE)
        printf("match rules[%d] = \"%s\" at position %d with len %d: %.*s\n",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */     
        tokens[*nr_token].type = rules[i].token_type;
        strncpy(tokens[*nr_token].str,substr_start,substr_len);
        tokens[*nr_token].str[substr_len] = '\0';
        (*nr_token) ++;
        break;
      }
    }
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  return true;
}
