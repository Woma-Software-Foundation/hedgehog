#include <stdio.h>

#include "ast_node.h"
#include "hedgehog.h"

extern int yyparse(struct parser_state* p);

int main(int argc, char** argv) {
    extern FILE* yyin;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return -1;
    }

    FILE* f;
    if ((f = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "faild to open `%s`\n", argv[1]);
        return -1;
    }

    yyin = f;

    struct parser_state p = {
        .lineno = 1, .tline = 1, .lval = NULL, .fname = argv[1]};

    while (yyparse(&p))
        ;
    return 0;
}
