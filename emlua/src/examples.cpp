#include "../libs/lua-5.4.6/src/lua.hpp"

#include <stdio.h>

void example_1_hello_world_from_file() {

	printf( "--- Example 1: Hello World from file ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Run Lua script file. */

	const char *script = "scripts/1_hello_world.lua";
	
	int script_result = luaL_dofile( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script file '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	lua_close( lua );

	printf( "\n" );
}

void example_2_hello_world_from_string() {

	printf( "--- Example 2: Hello World from string ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Run Lua script string. */

	const char *script = "print(\"[Lua] Hello World from Lua script string!\")";

	int script_result = luaL_dostring( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script string '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	lua_close( lua );

	printf( "\n" );
}

void example_3_accessing_lua_variables() {

	printf( "--- Example 3: Accessing Lua variables ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Run Lua script file. */

	const char *script = "scripts/3_accessing_lua_variables.lua";

	int script_result = luaL_dofile( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script file '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	/* Get Lua script variable value. */

	// Get variable `number` on the stack.
	lua_getglobal( lua, "number" );

	// Get the value of the `number` variable.
	// Since it's on top of the stack, we can get its value by index -1.
	// In this simple example, we know that it's a number type variable,
	// so we can use `lua_tointeger`, or more generic `lua_tonumber`.
	lua_Number number_value = lua_tonumber( lua, -1 );

	printf( "[Emlua] Value of 'number': %.f\n", number_value );

	lua_close( lua );

	printf( "\n" );
}

void example_4_passing_variables_to_lua() {

	printf( "--- Example 4: Passing variables to Lua ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Declare new Lua variable. */

	// Create a new variable containing the value we want to pass to Lua.
	int external_number = 321;

	// Push value to the stack and then assign a variable to it.
	lua_pushnumber( lua, external_number );
	lua_setglobal( lua, "external_number" );

	printf( "[Emlua] Declared new variable 'external_number' with value: %d\n", external_number );

	/* Run Lua script file. */

	const char *script = "scripts/4_passing_variables_to_lua.lua";

	int script_result = luaL_dofile( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script file '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	lua_close( lua );

	printf( "\n" );
}

void example_5_accessing_lua_functions() {

	printf( "--- Example 5: Accessing Lua functions ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Run Lua script file. */

	const char *script = "scripts/5_accessing_lua_functions.lua";

	int script_result = luaL_dofile( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script file '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	/* Get Lua function and call it. */

	// The signutare of the function we are searching:
	//     function add(a, b)
	const char *function = "add";
	lua_getglobal( lua, function );
	if ( lua_isfunction( lua, -1 ) ) {
		// The signutare of the function is:
		//     function add(a, b)
		//
		// Since it expects 2 arguments, we must pass them by the stack.

		// Pass 1-st argument.
		int argument_a = 35;
		lua_pushnumber( lua, argument_a );

		// Pass 2-nd argument.
		int argument_b = 65;
		lua_pushnumber( lua, argument_b );

		const int arguments_count = 2;     // How many arguments function takes.
		const int return_values_count = 1; // How many values function returns.

		// Call Lua function.
		printf( "[Emlua] Calling Lua function '%s' with arguments: %d, %d\n", function, argument_a, argument_b );
		lua_pcall( lua, arguments_count, return_values_count, 0 );

		// Get the function result.
		lua_Number result = lua_tonumber( lua, -1 );

		printf( "[Emlua] Lua function returned: %.f\n", result );

	} else {
		printf( "[Emlua] Couldn't find Lua function '%s'.\n", function );
	}

	lua_close( lua );

	printf( "\n" );
}

extern "C" {

// Expected function signature:
//     external_multiply( a, b )
int external_multiply( lua_State *lua ) {
	// It is 

	// Get 2-nd argument.
	lua_Number argument_b = lua_tonumber( lua, -1 );

	// Get 1-st argument.
	lua_Number argument_a = lua_tonumber( lua, -2 );

	lua_Number result = argument_a * argument_b;

	printf( "[Emlua] Called 'external_multiply' function: %.f * %.f = %.f\n", argument_a, argument_b, result );

	// `Return` the result to Lua by the stack.
	lua_pushnumber( lua, result );

	return 1;
}

}

void example_6_calling_external_functions_from_lua() {

	printf( "--- Example 6: Calling external functions from Lua ---\n" );

	lua_State *lua = luaL_newstate();
	luaL_openlibs( lua );

	/* Declare new external function. */

	// Push function to the stack and then assign a function variable to it.
	lua_pushcfunction( lua, external_multiply );
	lua_setglobal( lua, "external_multiply" );

	printf( "[Emlua] Declared new external function 'external_multiply'\n" );

	/* Run Lua script file. */

	const char *script = "scripts/6_calling_external_functions_from_lua.lua";

	int script_result = luaL_dofile( lua, script );
	if ( script_result != LUA_OK ) {
		printf( "Couldn't execute script file '%s'.\n", script );
		luaL_error( lua, "Error: %s\n", lua_tostring( lua, -1 ) );
	}

	lua_close( lua );

	printf( "\n" );
}