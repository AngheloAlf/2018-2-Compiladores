#include "ast_handler.h"



// set-up

void prepare_vars(){
    FuncData *lib_func;

    lib_func = FuncData_init(int_type, "read");
    lib_func->paramList = VarVector_init(0);
    FuncVector_endadd(func_vector, lib_func);

    lib_func = FuncData_init(void_type, "writeln");
    lib_func->paramList = VarVector_init(0);
    FuncVector_endadd(func_vector, lib_func);
}

void vars_init_and_prepare(){
    global_vars = VarVector_init(8);
    local_scope = ScopeData_init();
    is_local_var = false;

    func_vector = FuncVector_init(8);
    param_list = VarVector_init(8);

    strings_constants = StringVector_init(8);

    last_expression = NULL;

    if_else_stack = ExprVector_init(8);
    while_stack = ExprVector_init(8);

    prepare_vars();
}

void vars_free(){
    assert(ExprVector_len(while_stack) == 0);
    ExprVector_free(while_stack);
    assert(ExprVector_len(if_else_stack) == 0);
    ExprVector_free(if_else_stack);

    StringVector_clean(strings_constants);
    StringVector_free(strings_constants);

    VarVector_clean(param_list);
    VarVector_free(param_list);
    FuncVector_clean(func_vector);
    FuncVector_free(func_vector);

    ScopeData_clean(local_scope);
    ScopeData_free(local_scope);
    VarVector_clean(global_vars);
    VarVector_free(global_vars);
}