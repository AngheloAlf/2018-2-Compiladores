#include "ast_handler.h"

#include "error_handler.h"

extern int lineCounter;
extern int in_line_character_counter;

/// exprs

void set_if_id(ExprData *expr){
    assert(expr->type == expr_if || expr->type == expr_else || expr->type == expr_if_end);
    ExprData *old_if;
    static int if_id = 0;

    expr->is_flow_control = true;
    switch(expr->type){
        case expr_if:
            expr->flow_control_id = ++if_id;
            ExprVector_endadd(if_else_stack, expr);
            break;
        case expr_else:
            assert(ExprVector_len(if_else_stack) > 0);
            old_if = ExprVector_endtop(if_else_stack);
            assert(!old_if->has_else);
            old_if->has_else = true;
            expr->flow_control_id = old_if->flow_control_id;
            break;
        case expr_if_end:
            assert(ExprVector_len(if_else_stack) > 0);
            old_if = ExprVector_endpop(if_else_stack);
            expr->flow_control_id = old_if->flow_control_id;
            break;
        default:
            break;
    }
}

void set_while_id(ExprData *expr){
    assert(expr->type == expr_while || expr->type == expr_while_condition || expr->type == expr_while_end);
    ExprData *old_while;
    static int while_id = 0;

    expr->is_flow_control = true;
    switch(expr->type){
        case expr_while:
            expr->flow_control_id = ++while_id;
            ExprVector_endadd(while_stack, expr);
            break;
        case expr_while_condition:
            assert(ExprVector_len(while_stack) > 0);
            old_while = ExprVector_endtop(while_stack);
            expr->flow_control_id = old_while->flow_control_id;
            break;
        case expr_while_end:
            assert(ExprVector_len(while_stack) > 0);
            old_while = ExprVector_endpop(while_stack);
            expr->flow_control_id = old_while->flow_control_id;
            break;
        default:
            break;
    }
}

void add_expr(const char *expr, ExprTypeEnum expr_type){
    ScopeData *actual_scope = ScopeData_get_last_not_ended_scope(local_scope);
    ExprData *actual_expression = ExprData_init(expr, expr_type, lineCounter, in_line_character_counter);

    switch(expr_type){
        case expr_if:
        case expr_else:
        case expr_if_end:
            set_if_id(actual_expression);
            break;

        case expr_while:
        case expr_while_condition:
        case expr_while_end:
            set_while_id(actual_expression);
            break;

        case expr_comparation_leq:
        case expr_comparation_lss:
        case expr_comparation_equ:
        case expr_comparation_neq:
        case expr_comparation_gtr:
        case expr_comparation_geq:

        case expr_arithmetic_add:
        case expr_arithmetic_sub:
        case expr_arithmetic_mul:
        case expr_arithmetic_div:
        case expr_arithmetic_mod:
        case expr_arithmetic_neg:
            // generate_fake_var_for_expr(actual_scope, last_expression);

        case expr_func_call:
        case expr_array:
        case expr_array_ampersand:
        case expr_assignation_var:
            // generate_fake_var_for_expr(actual_scope, actual_expression);
            break;

        default:
            // TODO: show error.
            break;
    }
    ExprVector_endadd(actual_scope->exprs, actual_expression);
    last_expression = actual_expression;
}

void set_last_expr_as_func_arg(){
    if(last_expression != NULL){
        assert(last_expression->is_func_argument == false);
        last_expression->is_func_argument = true;
    }
}
