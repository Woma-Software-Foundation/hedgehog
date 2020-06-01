#ifndef _HG_CHUNK_H_
#define _HG_CHUNK_H_
#include "common.h"
#include "value.h"

enum opcode {
    OP_NOP,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_GREATER_EQUAL,
    OP_LESS_EQUAL,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MODULO,
    OP_NOT,
    OP_NEGATE,
    OP_POP,            // pop a byte
    OP_PUSH,           // push a byte from chunk into stack
    OP_CHECK_ARGS_NUM, /* compare the number of vars and args
                          number of vars: the byte after OP_CHECK_ARGS_NUM,
                          number of args: the byte on the top of the stack */
    OP_SET_STATIC,
    OP_GET_STATIC,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_JUMP,
    OP_JUMP_IF_FALSE,
    OP_JUMP_BACK,
    OP_CALL,
};

#define CHUNK_INIT_CAPACITY (256u)
struct chunk {
    size_t len;
    size_t capacity;
    struct value_array statics;
    uint8_t* code;
};

void chunk_init(struct chunk* chk);
void chunk_free(struct chunk* chk);

void chunk_write(struct chunk* chk, uint8_t byte);
static inline void chunk_write_word(struct chunk* chk, uint16_t word) {
    chunk_write(chk, (word >> 8) & 0xff);
    chunk_write(chk, word & 0xff);
}
uint16_t chunk_add_static(struct chunk* chk, struct hg_value value);
int chunk_dump(struct chunk* chk, FILE* fp);
struct chunk* chunk_load(FILE* fp);
void chunk_disassemble(struct chunk* chk);
#endif // _HG_CHUNK_H_
