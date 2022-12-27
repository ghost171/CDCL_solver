#include <iostream>
#include<z3++.h>
#include<z3_api.h>

using namespace z3;

int main() {
    context ctx;    
    //z3_string fname = ;
    Z3_ast_vector a = Z3_parse_smtlib2_file(ctx, "smt_z3.smt2", 0, 0, 0, 0, 0, 0);
    //expr e(ctx, a);
    Z3_ast_vector_inc_ref(get_ctx(), v);
    unsigned sz = Z3_ast_vector_size(get_ctx(), v);
    Z3_ast* vv = malloc(sz);
    for (unsigned I = 0; I < sz; ++I) vv[I] = Z3_ast_vector_get(get_ctx(), v, I);
    Z3_ast* result = Z3_mk_and(get_ctx(), sz, vv);
    Z3_inc_ref(get_ctx(), result);
    free(vv);
    Z3_ast_vector_dec_ref(get_ctx(), v);
    cout << result << endl;
}