#ifndef HG_AST_H_
#define HG_AST_H_

#include "common.h"

struct hg_parser_state {
    int nerr;
    void* lval;
    const char* fname;
    int lineno;
    int tline;
    struct hg_ast* ast;
};

enum hg_ast_node_type {
    // statement:
    AST_NODE_BLOCK,
    AST_NODE_ASSIGNMENT,
    AST_NODE_FOR,
    AST_NODE_IF,
    AST_NODE_FUNC,
    AST_NODE_BREAK,
    AST_NODE_CONTINUE,
    AST_NODE_RETURN,
    // exprs:
    AST_NODE_CALL,
    AST_NODE_FIELD,
    AST_NODE_FUNC_DEF,
    AST_NODE_BINARY_EXPR,
    AST_NODE_UNARY_EXPR,
    AST_NODE_TABLE,
    AST_NODE_TABLE_ENTRY,
    // literal:
    AST_NODE_LITERAL_STR,
    AST_NODE_LITERAL_ID,
    AST_NODE_LITERAL_BOOL,
    AST_NODE_LITERAL_INT,
    AST_NODE_LITERAL_FLOAT,
    // inner:
    AST_NODE_ARRAY,
};

enum ast_node_op_type {
    AST_NODE_OP_AND,
    AST_NODE_OP_OR,
    AST_NODE_OP_NOT,
    AST_NODE_OP_NEQ,
    AST_NODE_OP_EQ,
    AST_NODE_OP_GE,
    AST_NODE_OP_LE,
    AST_NODE_OP_GT,
    AST_NODE_OP_LS,
    AST_NODE_OP_NEG,
    AST_NODE_OP_ADD,
    AST_NODE_OP_SUB,
    AST_NODE_OP_MUL,
    AST_NODE_OP_DIV,
    AST_NODE_OP_MOD,
};

struct hg_ast* hg_ast_new();
void hg_ast_free(struct hg_ast*);

struct hg_ast_node {
    enum hg_ast_node_type type;
};
#define _hg_ast_head struct hg_ast_node node

struct hg_ast_node_array {
    _hg_ast_head;
    struct hg_ast_node** arr;
    size_t len, cap;
};
struct hg_ast_node* hg_ast_node_array_new();
struct hg_ast_node* hg_ast_node_array_append();

struct hg_ast_for_stat {
    _hg_ast_head;
    struct hg_ast_node_array* params;
    struct hg_ast_node* iterator;
    struct hg_ast_node_array* block;
};
struct hg_ast_node* hg_ast_for_stat_new(struct hg_ast_node* params,
                                        struct hg_ast_node* iterator,
                                        struct hg_ast_node* block);

struct hg_ast_break_stat {
    _hg_ast_head;
};
struct hg_ast_node* hg_ast_break_stat_new();

struct hg_ast_continue_stat {
    _hg_ast_head;
};
struct hg_ast_node* hg_ast_continue_stat_new();

struct hg_ast_return_stat {
    _hg_ast_head;
    struct hg_ast_node_array* exprs;
};
struct hg_ast_node* hg_ast_return_stat_new(struct hg_ast_node* exprs);

struct hg_ast_if_stat {
    _hg_ast_head;
    struct hg_ast_node* condition;
    struct hg_ast_node_array* block;
    struct hg_ast_node_array* else_block;
};
struct hg_ast_node* hg_ast_if_stat_new(struct hg_ast_node* cond,
                                       struct hg_ast_node* block,
                                       struct hg_ast_node* else_block);

struct hg_ast_assignment_stat {
    _hg_ast_head;
    struct hg_ast_node_array* vars;
    struct hg_ast_node_array* exprs;
};
struct hg_ast_node* hg_ast_assignment_stat_new(struct hg_ast_node* vars,
                                               struct hg_ast_node* exps);

struct hg_ast_func_stat {
    _hg_ast_head;
    struct hg_ast_node* id;
    struct hg_ast_node_array* params;
    struct hg_ast_node_array* block;
};
struct hg_ast_node* hg_ast_func_stat_new(struct hg_ast_node* id,
                                         struct hg_ast_node* params,
                                         struct hg_ast_node* blocks);

struct hg_ast_func_def_expr {
    _hg_ast_head;
    struct hg_ast_node_array* params;
    struct hg_ast_node_array* block;
};
struct hg_ast_node* hg_ast_func_def_new(struct hg_ast_node* params,
                                        struct hg_ast_node* blocks);

struct hg_ast_unary_expr {
    _hg_ast_head;
    enum ast_node_op_type op;
    struct hg_ast_node* expr;
};
struct hg_ast_node* hg_ast_unary_expr_new(enum ast_node_op_type op,
                                          struct hg_ast_node* expr);

struct hg_ast_binary_expr {
    _hg_ast_head;
    enum ast_node_op_type op;
    struct hg_ast_node* left;
    struct hg_ast_node* right;
};
struct hg_ast_node* hg_ast_binary_expr_new(enum ast_node_op_type op,
                                           struct hg_ast_node* left,
                                           struct hg_ast_node* right);

struct hg_ast_call_expr {
    _hg_ast_head;
    struct hg_ast_node* callable;
    struct hg_ast_node_array* args;
};
struct hg_ast_node* hg_ast_call_expr_new(struct hg_ast_node* callable,
                                         struct hg_ast_node* args);

struct hg_ast_field_expr {
    _hg_ast_head;
    struct hg_ast_node* prefix;
    struct hg_ast_node* field;
};
struct hg_ast_node* hg_ast_field_expr_new(struct hg_ast_node* prefix,
                                          struct hg_ast_node* field);

struct hg_ast_index_expr {
    _hg_ast_head;
    struct hg_ast_node* prefix;
    struct hg_ast_node* index;
};
struct hg_ast_node* hg_ast_index_expr_new(struct hg_ast_node* prefix,
                                          struct hg_ast_node* index);

struct hg_ast_table_expr {
    _hg_ast_head;
    struct hg_ast_node_array* entries;
};
struct hg_ast_node* hg_ast_table_expr_new();
struct hg_ast_node* hg_ast_table_expr_append(struct hg_ast_node* table,
                                             struct hg_ast_node* entry);

struct hg_ast_table_entry {
    _hg_ast_head;
    struct hg_ast_node* key;
    struct hg_ast_node* value;
};
struct hg_ast_node* hg_ast_table_entry_new(struct hg_ast_node* key,
                                           struct hg_ast_node* value);

struct hg_ast_literal {
    _hg_ast_head;
    union {
        hg_char as_id;
        hg_char as_str;
        hg_float as_float;
        hg_int as_int;
        hg_bool as_bool;
    };
};
struct hg_ast_node* hg_ast_literal_id_new(hg_char str);
struct hg_ast_node* hg_ast_literal_str_new(hg_char str);
struct hg_ast_node* hg_ast_literal_float_new(hg_float d);
struct hg_ast_node* hg_ast_literal_int_new(hg_float i);
struct hg_ast_node* hg_ast_literal_bool_new(hg_bool b);

#undef _hg_ast_head

#endif // HG_AST_H_
