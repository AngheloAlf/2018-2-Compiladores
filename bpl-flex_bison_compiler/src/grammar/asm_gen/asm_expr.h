#ifndef ASM_EXPR_H
#define ASM_EXPR_H

#include <stdio.h>

#include "expr_type.h"

#include "var_vector.h"
#include "func_vector.h"
#include "scope_vector.h"
#include "expr_vector.h"

/*
 * Register usage:
 * 
 * By ABI:
 * %rax: return value of function.
 * %rdi: first parameter.
 * %rsi: second parameter.
 * %rdx​: third parameter.
 * %rcx​: fourth parameter.
 * %r8: fifth parameter.
 * %r9: sixth parameter
 * %rsp: stack pointer
 * %rbp: base pointer (stack pointer)
 * 
 * By Compiler:
 * %r15: Arrays operations
 * 
 * Safe to use:
 * %r12
 * %r13
 * %r14
 * 
 * TODOs:
 * %r10
 * %r11
 * %rbx​
*/


typedef struct{
    FILE *out_file;
    FuncData *function;
    ScopeData *scope;
    ExprVector *exprs_stack;
} ExprContainer;


ExprType get_ExprType_const(TypesEnum type);

ExprType load_var_into_register(ExprContainer *container, ExprData *expression, const char *register_name);
ExprType load_func_call_into_register(ExprContainer *container, ExprData *func_call_expr, const char *register_name);

ExprType load_expression_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

void store_register_in_var(ExprContainer *container, ExprData *expression, const char *register_name);
void store_register_in_expression(ExprContainer *container, ExprData *expression, const char *register_name);

ExprType load_fake_var_into_register(ExprContainer *container, ExprData *src_fake, const char *register_name);
ExprType store_expression_in_fake_var(ExprContainer *container, ExprData *expression, ExprData *dest_fake, const char *register_name);
ExprType store_stackpop_in_fake_var(ExprContainer *container, ExprData *dest_fake, const char *register_name);
TypesEnum store_arithmetic_in_fake_var(ExprContainer *container, const ExprData *arithmetic_expression, const char *register_name);
TypesEnum store_comparation_in_fake_var(ExprContainer *container, const ExprData *comp_expression, const char *register_name);

#endif /* ASM_EXPR_H */
