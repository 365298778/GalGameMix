/*
 * LuaFunc.h
 *
 *  Created on: 2015年5月2日
 *      Author: Administrator
 */

#ifndef LUAIMPL_LUAFUNC_H_
#define LUAIMPL_LUAFUNC_H_

#define PAR_MAX_LENGTH  50

typedef struct{
	lua_State *L;
	char methodName[PAR_MAX_LENGTH];
	int numParNum;
	int stringParNum;
	int resultNum;
	int existString;
	int *numPar[PAR_MAX_LENGTH];
	char *stringPar[PAR_MAX_LENGTH];
}Lua_parameter;

typedef struct{
	int code;
	int existString;
	int numParNum;
	int stringParNum;
	int *numPar[PAR_MAX_LENGTH];
	char *stringPar[PAR_MAX_LENGTH];
}Lua_result;

#endif /* LUAIMPL_LUAFUNC_H_ */
