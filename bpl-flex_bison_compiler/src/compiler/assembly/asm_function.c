#include "assembly_generator.h"

#include "types_enum.h"
#include "variable.h"
#include "function.h"

#include "ast_handler.h"

#include "error_handler.h"
#include "util.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void write_global_vars(FILE *output_file){
    const char *asm_str;
    // asm_str = "\t.comm\t%s,%i,%i\n";
    asm_str = "\t.comm\t%s,%i\n";
    int length;
    // int alignment;
    for(int i = 0; i < VarVector_len(global_vars); ++i){
        VarData *global = VarVector_item(global_vars, i);
        if(!global->written){
            if(TypesEnum_is_array(global->type)){
                length = global->array_size * 8;
                /*if(global->array_size <= 1){
                    alignment = 8;
                }
                else if(global->array_size <= 2){
                    alignment = 16;
                }
                else{
                    alignment = 32;
                }*/
            }
            else{
                length = 8;
                // alignment = 8;
            }
            fprintf(output_file, asm_str, global->id, length);
            global->written = true;
        }
    }
}

void write_strings_constants(FILE *output_file, const char *function_name){
    fprintf(output_file, "\n\t.section\t.rodata\n");
    const char *str = ".%s_str_%i:\n\t.string %s\n";
    for(int i = 0; i < StringVector_len(strings_constants); ++i){
        StringData *data = StringVector_item(strings_constants, i);
        if(!data->written){
            fprintf(output_file, str, function_name, data->str_id, data->string);
            data->written = true;
        }
    }
}

void write_function_header(FILE *output_file, const char *function_name){
    const char *asm_str = "\n\t.text\n\t.globl\t%s\n\t.type\t%s, @function\n";
    fprintf(output_file, asm_str, function_name, function_name);
}

void write_arrays_size(FILE *output_file, ScopeData *actual_scope){
    VarVector *vars = actual_scope->declared_vars;
    for(int i = 0; i < VarVector_len(vars); ++i){
        VarData *var = VarVector_item(vars, i);
        if(TypesEnum_is_array(var->type) && var->var_id > 0){
            fprintf(output_file, "\tmovq\t$%i, -%i(%%rbp) # %s %s[%i]\n", var->array_size, var->var_id+8, TypesEnum_get_name(var->type), var->id, var->array_size);
        }
    }
    ScopeVector *scps = actual_scope->scopes;
    for(int i = 0; i < ScopeVector_len(scps); ++i){
        ScopeData *scp = ScopeVector_item(scps, i);
        write_arrays_size(output_file, scp);
    }
}

void write_function_prologue(FILE *output_file, const char *function_name){
    const char *asm_str = "%s:\n\tpushq\t%%rbp\n\tmovq\t%%rsp, %%rbp\n";
    fprintf(output_file, asm_str, function_name);

    fprintf(output_file, "\tpushq\t%%r12\n\tpushq\t%%r13\n\tpushq\t%%r14\n\tpushq\t%%r15\n");

    asm_str = "\tsubq\t$%i, %%rsp\n";
    int variables_size = get_all_declared_variables_size() + get_parameters_size();
    variables_size = get_aligned_stack_size(variables_size);
    fprintf(output_file, asm_str, variables_size);

    write_arrays_size(output_file, local_scope);
}

void write_function_params(FILE *output_file, FuncData *function){
    if(function->paramList != NULL){
        fprintf(output_file, ".%s_params:\n", function->name);

        int local_var_id = get_parameters_size() + get_all_declared_variables_size();

        int params_len = VarVector_len(function->paramList);
        const char *param_registers = "\tmovq\t%%%s, -%i(%%rbp) # %s %s\n";
        const char *registers[6] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
        VarData *variable;
        const char *type;
        char *param_name;
        for(int i = 0; i < MIN(6, params_len); ++i){
            variable = VarVector_item(function->paramList, i);
            type = TypesEnum_get_name(variable->type);
            param_name = variable->id;
            fprintf(output_file, param_registers, registers[i], local_var_id, type, param_name);
            local_var_id -= 8;
        }

        const char *param_stack = "\tmovq\t%i(%%rbp), %%rax\n\tmovq\t%%rax, -%i(%%rbp) # %s %s\n";
        for(int i = 6; i < params_len; ++i){
            int aux = i - 6;
            int first_number = 16 + aux*8;
            variable = VarVector_item(function->paramList, i);
            type = TypesEnum_get_name(variable->type);
            param_name = variable->id;
            fprintf(output_file, param_stack, first_number, local_var_id, type, param_name);
            local_var_id -= 8;
        }
    }
}

void write_function_exprs(FILE *output_file, FuncData *function){
    fprintf(output_file, ".%s_exprs:\n", function->name);
    parse_expressions(output_file, function, local_scope);
}

void write_function_epilogue(FILE *output_file, const char *function_name){
    const char *asm_str = ".%s_epilogue:\n"; 
    fprintf(output_file, asm_str, function_name);
    fprintf(output_file, "\tpopq\t%%r15\n\tpopq\t%%r14\n\tpopq\t%%r13\n\tpopq\t%%r12\n");
    fprintf(output_file, "\tleave\n\tret\n");
}

void write_function_footer(FILE *output_file, const char *function_name){
    const char *asm_str = "\t.size\t%s, .-%s\n";
    fprintf(output_file, asm_str, function_name, function_name);
}

void write_function(FILE *out_file, FuncData *function){
    set_vars_ids();
    set_strings_ids();
    write_global_vars(out_file);
    write_strings_constants(out_file, function->name);
    write_function_header(out_file, function->name);
    write_function_prologue(out_file, function->name);
    write_function_params(out_file, function);
    write_function_exprs(out_file, function);
    write_function_epilogue(out_file, function->name);
    write_function_footer(out_file, function->name);
}
