/*
 * LuaFunc.c
 *
 *  Created on: 2015年5月2日
 *      Author: Cxz_Label
 */

/**
 * @file		LuaFunc.c
 * @date		2015-05-02 18:00
 * @author		Cxz_Label
 * @brief
 * the lua script function impl
 * lua脚本功能的实现
 *
 */

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <LuaFunc.h>

Lua_result* call(Lua_parameter *par) {
	Lua_result *result;
	int resultIndex=0;
	if (par && par->L) {
		lua_State *L = par->L;
		lua_getglobal(L, par->methodName);
			if (par->numPar) {
				int var;
				for (var = 0; var < par->numParNum; var++) {
					lua_pushinteger(L, par->numPar[var]);
				}
			}
			if (par->existString && (par->existString) == 1) {
				int var;
				for (var = 0; var < par->stringParNum; var++) {
					lua_pushstring(L, par->stringPar[var]);
				}
			}
			if (!par->stringParNum) {
				lua_pcall(L, par->numParNum, par->resultNum, 0);
			} else {
				lua_pcall(L, (par->stringParNum + par->numParNum), par->resultNum,0);
			}
		if (par->resultNum > 0) {
			result->existString=lua_tointeger(L,resultIndex-1);
			if (result->existString==1) {
				result->numParNum=lua_tointeger(L,resultIndex-1);
				result->stringParNum=lua_tointeger(L,resultIndex-1);
				int var;
				for (var = 0; var < result->numParNum; var++) {
					result->numPar[var]=lua_tointeger(L,resultIndex-1);
				}
				int var1;
				for (var1 = 0; var1 < result->stringParNum; var1++) {
					result->stringPar[var]=lua_tostring(L,resultIndex-1);
				}
			}else if (result->existString==0) {
				result->numParNum=lua_tointeger(L,resultIndex-1);
				int var;
				for (var = 0; var < result->numParNum; var++) {
					result->numPar[var]=lua_tointeger(L,resultIndex-1);
				}
			}
		}
		resultIndex = 0;
		return result;
	}
	result->code=-1;
	return result;
}

