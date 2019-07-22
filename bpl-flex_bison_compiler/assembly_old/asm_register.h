#ifndef ASM_EXPR_H
#define ASM_EXPR_H

#include "assembly_generator.h"

#include "expr_type_enum.h"

#include "variable.h"
#include "function.h"
#include "expression.h"
#include "scope.h"

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

ExprTypeEnum get_ExprType_const(TypesEnum type);

ExprTypeEnum load_var_into_register(ExprContainer *container, ExprData *expression, const char *register_name);
ExprTypeEnum load_func_call_into_register(ExprContainer *container, ExprData *func_call_expr, const char *register_name);

ExprTypeEnum load_expression_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

void store_register_in_var(ExprContainer *container, ExprData *expression, const char *register_name);
void store_register_in_expression(ExprContainer *container, ExprData *expression, const char *register_name);

#endif /* ASM_EXPR_H */
