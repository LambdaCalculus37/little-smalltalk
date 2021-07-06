#ifndef _CD_LUAIUP_
#define _CD_LUAIUP_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
void cdluaiup_open(void);
#endif

#ifdef LUA_TNONE  /* Lua 5 */
int cdluaiup_open(lua_State *L);
#endif

#ifdef __cplusplus
}
#endif

#endif

