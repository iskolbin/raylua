#define float lua_Number
#include <easings.h>

static int l_EaseBackOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBackOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseBackInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBackInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCircIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCircIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseQuadIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseQuadIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseExpoOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseExpoOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCircInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCircInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseBounceInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBounceInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCubicIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCubicIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseLinearIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseLinearIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseSineInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseSineInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseSineIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseSineIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseQuadOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseQuadOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseQuadInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseQuadInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseExpoIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseExpoIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseBounceOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBounceOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseLinearOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseLinearOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseLinearInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseLinearInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseLinearNone(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseLinearNone(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseElasticOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseElasticOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseElasticInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseElasticInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseBackIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBackIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseSineOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseSineOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseBounceIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseBounceIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCircOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCircOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCubicOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCubicOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseCubicInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseCubicInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseElasticIn(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseElasticIn(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

static int l_EaseExpoInOut(lua_State *L) {
  float t = luaL_checknumber(L, 1);
  float b = luaL_checknumber(L, 2);
  float c = luaL_checknumber(L, 3);
  float d = luaL_checknumber(L, 4);
  float result = EaseExpoInOut(t, b, c, d);
  lua_pushnumber(L, result);
  return 1;
}

#undef float

static const luaL_Reg l_easings_functions[] = {
  {"EaseBackOut", l_EaseBackOut},
  {"EaseBackInOut", l_EaseBackInOut},
  {"EaseCircIn", l_EaseCircIn},
  {"EaseQuadIn", l_EaseQuadIn},
  {"EaseExpoOut", l_EaseExpoOut},
  {"EaseCircInOut", l_EaseCircInOut},
  {"EaseBounceInOut", l_EaseBounceInOut},
  {"EaseCubicIn", l_EaseCubicIn},
  {"EaseLinearIn", l_EaseLinearIn},
  {"EaseSineInOut", l_EaseSineInOut},
  {"EaseSineIn", l_EaseSineIn},
  {"EaseQuadOut", l_EaseQuadOut},
  {"EaseQuadInOut", l_EaseQuadInOut},
  {"EaseExpoIn", l_EaseExpoIn},
  {"EaseBounceOut", l_EaseBounceOut},
  {"EaseLinearOut", l_EaseLinearOut},
  {"EaseLinearInOut", l_EaseLinearInOut},
  {"EaseLinearNone", l_EaseLinearNone},
  {"EaseElasticOut", l_EaseElasticOut},
  {"EaseElasticInOut", l_EaseElasticInOut},
  {"EaseBackIn", l_EaseBackIn},
  {"EaseSineOut", l_EaseSineOut},
  {"EaseBounceIn", l_EaseBounceIn},
  {"EaseCircOut", l_EaseCircOut},
  {"EaseCubicOut", l_EaseCubicOut},
  {"EaseCubicInOut", l_EaseCubicInOut},
  {"EaseElasticIn", l_EaseElasticIn},
  {"EaseExpoInOut", l_EaseExpoInOut},
  {NULL, NULL}
};

LUAMOD_API int luaopen_easings(lua_State *L) {
  float x = 1;
	luaL_newlib(L, l_easings_functions);
  lua_pushnumber(L, PI);
  lua_setfield(L, -2, "PI");
  return 1;
}
