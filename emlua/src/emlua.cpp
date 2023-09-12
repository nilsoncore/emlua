#include "../libs/lua-5.4.6/src/lua.hpp"

#include "examples.cpp"

int main( int aruments, char *arguments[] ) {

	example_1_hello_world_from_file();
	example_2_hello_world_from_string();
	example_3_accessing_lua_variables();
	example_4_passing_variables_to_lua();
	example_5_accessing_lua_functions();
	example_6_calling_external_functions_from_lua();

	return 0;
}