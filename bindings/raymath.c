#define RAYMATH_HEADER_ONLY
#include <raymath.h>

static int l_Lerp(lua_State *L) {
  lua_Number start = luaL_checknumber(L, 1);
  lua_Number end = luaL_checknumber(L, 2);
  lua_Number amount = luaL_checknumber(L, 3);
  lua_Number result = start + amount*(end - start);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Clamp(lua_State *L) {
  lua_Number value = luaL_checknumber(L, 1);
  lua_Number min = luaL_checknumber(L, 2);
  lua_Number max = luaL_checknumber(L, 3);
  lua_Number result = value < min ? min : value;
  lua_pushnumber(L, result > max ? max : min);
  return 1;
}

static int l_Vector3OrthoNormalize(lua_State *L) {
  Vector3 *v1 = luaL_checkudata(L, 1, "Vector3");
  Vector3 *v2 = luaL_checkudata(L, 2, "Vector3");
  Vector3OrthoNormalize(v1, v2);
  return 0;
}

static int l_Vector2Divide(lua_State *L) {
  Vector2 v = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float div = luaL_checknumber(L, 2);
  Vector2 result = Vector2Divide(v, div);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2DivideU(lua_State *L) {
  Vector2 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float div = luaL_checknumber(L, 3);
  Vector2 result = Vector2Divide(v, div);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_MatrixScale(lua_State *L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float z = luaL_checknumber(L, 3);
  Matrix result = MatrixScale(x, y, z);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixScaleU(lua_State *L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float z = luaL_checknumber(L, 3);
  Matrix result = MatrixScale(x, y, z);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3ToFloatV(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float3 result = Vector3ToFloatV(v);
  float3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "float3");
  return 1;
}

static int l_Vector3ToFloatVU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float3 result = Vector3ToFloatV(v);
  float3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "float3");
  return 1;
}

static int l_MatrixFrustum(lua_State *L) {
  double left = luaL_checknumber(L, 1);
  double right = luaL_checknumber(L, 2);
  double bottom = luaL_checknumber(L, 3);
  double top = luaL_checknumber(L, 4);
  double near = luaL_checknumber(L, 5);
  double far = luaL_checknumber(L, 6);
  Matrix result = MatrixFrustum(left, right, bottom, top, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixFrustumU(lua_State *L) {
  double left = luaL_checknumber(L, 1);
  double right = luaL_checknumber(L, 2);
  double bottom = luaL_checknumber(L, 3);
  double top = luaL_checknumber(L, 4);
  double near = luaL_checknumber(L, 5);
  double far = luaL_checknumber(L, 6);
  Matrix result = MatrixFrustum(left, right, bottom, top, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixTranslate(lua_State *L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float z = luaL_checknumber(L, 3);
  Matrix result = MatrixTranslate(x, y, z);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixTranslateU(lua_State *L) {
  float x = luaL_checknumber(L, 1);
  float y = luaL_checknumber(L, 2);
  float z = luaL_checknumber(L, 3);
  Matrix result = MatrixTranslate(x, y, z);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3Barycenter(lua_State *L) {
  Vector3 p = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 a = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 b = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  Vector3 c = (*(Vector3*)luaL_checkudata(L, 4, "Vector3"));
  Vector3 result = Vector3Barycenter(p, a, b, c);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3BarycenterU(lua_State *L) {
  Vector3 p = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 a = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 b = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  Vector3 c = {luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12)};
  Vector3 result = Vector3Barycenter(p, a, b, c);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Normalize(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 result = Vector3Normalize(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3NormalizeU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 result = Vector3Normalize(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector2Lerp(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float amount = luaL_checknumber(L, 3);
  Vector2 result = Vector2Lerp(v1, v2, amount);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2LerpU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float amount = luaL_checknumber(L, 5);
  Vector2 result = Vector2Lerp(v1, v2, amount);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_QuaternionMultiply(lua_State *L) {
  Vector4 q1 = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 q2 = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  Vector4 result = QuaternionMultiply(q1, q2);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_MatrixToFloatV(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  float16 result = MatrixToFloatV(mat);
  float16* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "float16");
  return 1;
}

static int l_MatrixToFloatVU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  float16 result = MatrixToFloatV(mat);
  float16* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "float16");
  return 1;
}

static int l_Vector2Length(lua_State *L) {
  Vector2 v = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float result = Vector2Length(v);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2LengthU(lua_State *L) {
  Vector2 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float result = Vector2Length(v);
  lua_pushnumber(L, result);
  return 1;
}

static int l_MatrixIdentity(lua_State *L) {
  Matrix result = MatrixIdentity();
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixIdentityU(lua_State *L) {
  Matrix result = MatrixIdentity();
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3Lerp(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float amount = luaL_checknumber(L, 3);
  Vector3 result = Vector3Lerp(v1, v2, amount);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3LerpU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float amount = luaL_checknumber(L, 7);
  Vector3 result = Vector3Lerp(v1, v2, amount);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_MatrixTrace(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  float result = MatrixTrace(mat);
  lua_pushnumber(L, result);
  return 1;
}

static int l_MatrixTraceU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  float result = MatrixTrace(mat);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3Scale(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float scale = luaL_checknumber(L, 2);
  Vector3 result = Vector3Scale(v, scale);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3ScaleU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float scale = luaL_checknumber(L, 4);
  Vector3 result = Vector3Scale(v, scale);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_MatrixAdd(lua_State *L) {
  Matrix left = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix right = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  Matrix result = MatrixAdd(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixAddU(lua_State *L) {
  Matrix left = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix right = {luaL_checknumber(L, 17),luaL_checknumber(L, 18),luaL_checknumber(L, 19),luaL_checknumber(L, 20),luaL_checknumber(L, 21),luaL_checknumber(L, 22),luaL_checknumber(L, 23),luaL_checknumber(L, 24),luaL_checknumber(L, 25),luaL_checknumber(L, 26),luaL_checknumber(L, 27),luaL_checknumber(L, 28),luaL_checknumber(L, 29),luaL_checknumber(L, 30),luaL_checknumber(L, 31),luaL_checknumber(L, 32)};
  Matrix result = MatrixAdd(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3Divide(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float div = luaL_checknumber(L, 2);
  Vector3 result = Vector3Divide(v, div);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3DivideU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float div = luaL_checknumber(L, 4);
  Vector3 result = Vector3Divide(v, div);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_MatrixRotateX(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateX(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixRotateXU(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateX(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3MultiplyV(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3MultiplyV(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3MultiplyVU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3MultiplyV(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Add(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3Add(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3AddU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3Add(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_MatrixRotateZ(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateZ(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixRotateZU(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateZ(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixRotate(lua_State *L) {
  Vector3 axis = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float angle = luaL_checknumber(L, 2);
  Matrix result = MatrixRotate(axis, angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixRotateU(lua_State *L) {
  Vector3 axis = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float angle = luaL_checknumber(L, 4);
  Matrix result = MatrixRotate(axis, angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_QuaternionInvert(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 result = QuaternionInvert(q);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_Vector3RotateByQuaternion(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  Vector3 result = Vector3RotateByQuaternion(v, q);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3RotateByQuaternionU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 4, "Vector4"));
  Vector3 result = Vector3RotateByQuaternion(v, q);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_MatrixSubtract(lua_State *L) {
  Matrix left = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix right = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  Matrix result = MatrixSubtract(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixSubtractU(lua_State *L) {
  Matrix left = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix right = {luaL_checknumber(L, 17),luaL_checknumber(L, 18),luaL_checknumber(L, 19),luaL_checknumber(L, 20),luaL_checknumber(L, 21),luaL_checknumber(L, 22),luaL_checknumber(L, 23),luaL_checknumber(L, 24),luaL_checknumber(L, 25),luaL_checknumber(L, 26),luaL_checknumber(L, 27),luaL_checknumber(L, 28),luaL_checknumber(L, 29),luaL_checknumber(L, 30),luaL_checknumber(L, 31),luaL_checknumber(L, 32)};
  Matrix result = MatrixSubtract(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_QuaternionFromMatrix(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Vector4 result = QuaternionFromMatrix(mat);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionFromMatrixU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Vector4 result = QuaternionFromMatrix(mat);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_Vector3DivideV(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3DivideV(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3DivideVU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3DivideV(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Transform(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  Vector3 result = Vector3Transform(v, mat);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3TransformU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Matrix mat = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16),luaL_checknumber(L, 17),luaL_checknumber(L, 18),luaL_checknumber(L, 19)};
  Vector3 result = Vector3Transform(v, mat);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector2Distance(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float result = Vector2Distance(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2DistanceU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float result = Vector2Distance(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_QuaternionToMatrix(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Matrix result = QuaternionToMatrix(q);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_QuaternionToMatrixU(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Matrix result = QuaternionToMatrix(q);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixOrtho(lua_State *L) {
  double left = luaL_checknumber(L, 1);
  double right = luaL_checknumber(L, 2);
  double bottom = luaL_checknumber(L, 3);
  double top = luaL_checknumber(L, 4);
  double near = luaL_checknumber(L, 5);
  double far = luaL_checknumber(L, 6);
  Matrix result = MatrixOrtho(left, right, bottom, top, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixOrthoU(lua_State *L) {
  double left = luaL_checknumber(L, 1);
  double right = luaL_checknumber(L, 2);
  double bottom = luaL_checknumber(L, 3);
  double top = luaL_checknumber(L, 4);
  double near = luaL_checknumber(L, 5);
  double far = luaL_checknumber(L, 6);
  Matrix result = MatrixOrtho(left, right, bottom, top, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_QuaternionFromVector3ToVector3(lua_State *L) {
  Vector3 from = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 to = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector4 result = QuaternionFromVector3ToVector3(from, to);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionFromVector3ToVector3U(lua_State *L) {
  Vector3 from = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 to = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector4 result = QuaternionFromVector3ToVector3(from, to);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_Vector2Negate(lua_State *L) {
  Vector2 v = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 result = Vector2Negate(v);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2NegateU(lua_State *L) {
  Vector2 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 result = Vector2Negate(v);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_MatrixInvert(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix result = MatrixInvert(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixInvertU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix result = MatrixInvert(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3DotProduct(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float result = Vector3DotProduct(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3DotProductU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float result = Vector3DotProduct(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_QuaternionFromAxisAngle(lua_State *L) {
  Vector3 axis = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float angle = luaL_checknumber(L, 2);
  Vector4 result = QuaternionFromAxisAngle(axis, angle);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionFromAxisAngleU(lua_State *L) {
  Vector3 axis = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float angle = luaL_checknumber(L, 4);
  Vector4 result = QuaternionFromAxisAngle(axis, angle);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_Vector2Normalize(lua_State *L) {
  Vector2 v = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 result = Vector2Normalize(v);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2NormalizeU(lua_State *L) {
  Vector2 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 result = Vector2Normalize(v);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_Vector2Add(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 result = Vector2Add(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2AddU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 result = Vector2Add(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_Vector3Negate(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 result = Vector3Negate(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3NegateU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 result = Vector3Negate(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Zero(lua_State *L) {
  Vector3 result = Vector3Zero();
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3ZeroU(lua_State *L) {
  Vector3 result = Vector3Zero();
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_QuaternionIdentity(lua_State *L) {
  Vector4 result = QuaternionIdentity();
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionNormalize(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 result = QuaternionNormalize(q);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionLength(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  float result = QuaternionLength(q);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3Subtract(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3Subtract(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3SubtractU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3Subtract(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Reflect(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 normal = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3Reflect(v, normal);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3ReflectU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 normal = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3Reflect(v, normal);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3One(lua_State *L) {
  Vector3 result = Vector3One();
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3OneU(lua_State *L) {
  Vector3 result = Vector3One();
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Perpendicular(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 result = Vector3Perpendicular(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3PerpendicularU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 result = Vector3Perpendicular(v);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Multiply(lua_State *L) {
  Vector3 v = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float scalar = luaL_checknumber(L, 2);
  Vector3 result = Vector3Multiply(v, scalar);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3MultiplyU(lua_State *L) {
  Vector3 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float scalar = luaL_checknumber(L, 4);
  Vector3 result = Vector3Multiply(v, scalar);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector3Min(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3Min(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3MinU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3Min(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_QuaternionTransform(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  Vector4 result = QuaternionTransform(q, mat);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionTransformU(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Matrix mat = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16),luaL_checknumber(L, 17)};
  Vector4 result = QuaternionTransform(q, mat);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionSlerp(lua_State *L) {
  Vector4 q1 = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 q2 = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  float amount = luaL_checknumber(L, 3);
  Vector4 result = QuaternionSlerp(q1, q2, amount);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_Vector3Length(lua_State *L) {
  const Vector3 v = (*(const Vector3*)luaL_checkudata(L, 1, "const Vector3"));
  float result = Vector3Length(v);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2One(lua_State *L) {
  Vector2 result = Vector2One();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2OneU(lua_State *L) {
  Vector2 result = Vector2One();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_MatrixLookAt(lua_State *L) {
  Vector3 eye = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 target = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 up = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  Matrix result = MatrixLookAt(eye, target, up);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixLookAtU(lua_State *L) {
  Vector3 eye = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 target = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 up = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  Matrix result = MatrixLookAt(eye, target, up);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixNormalize(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix result = MatrixNormalize(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixNormalizeU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix result = MatrixNormalize(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixDeterminant(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  float result = MatrixDeterminant(mat);
  lua_pushnumber(L, result);
  return 1;
}

static int l_MatrixDeterminantU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  float result = MatrixDeterminant(mat);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3Distance(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float result = Vector3Distance(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3DistanceU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float result = Vector3Distance(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector3CrossProduct(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3CrossProduct(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3CrossProductU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3CrossProduct(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_QuaternionToEuler(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector3 result = QuaternionToEuler(q);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_QuaternionToEulerU(lua_State *L) {
  Vector4 q = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector3 result = QuaternionToEuler(q);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_Vector2Subtract(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 result = Vector2Subtract(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2SubtractU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 result = Vector2Subtract(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_MatrixPerspective(lua_State *L) {
  double fovy = luaL_checknumber(L, 1);
  double aspect = luaL_checknumber(L, 2);
  double near = luaL_checknumber(L, 3);
  double far = luaL_checknumber(L, 4);
  Matrix result = MatrixPerspective(fovy, aspect, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixPerspectiveU(lua_State *L) {
  double fovy = luaL_checknumber(L, 1);
  double aspect = luaL_checknumber(L, 2);
  double near = luaL_checknumber(L, 3);
  double far = luaL_checknumber(L, 4);
  Matrix result = MatrixPerspective(fovy, aspect, near, far);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector2Scale(lua_State *L) {
  Vector2 v = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float scale = luaL_checknumber(L, 2);
  Vector2 result = Vector2Scale(v, scale);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2ScaleU(lua_State *L) {
  Vector2 v = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float scale = luaL_checknumber(L, 3);
  Vector2 result = Vector2Scale(v, scale);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_Vector2MultiplyV(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 result = Vector2MultiplyV(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2MultiplyVU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 result = Vector2MultiplyV(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_Vector2Angle(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float result = Vector2Angle(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2AngleU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float result = Vector2Angle(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2DivideV(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 result = Vector2DivideV(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2DivideVU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 result = Vector2DivideV(v1, v2);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_Vector2DotProduct(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float result = Vector2DotProduct(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2DotProductU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float result = Vector2DotProduct(v1, v2);
  lua_pushnumber(L, result);
  return 1;
}

static int l_Vector2Zero(lua_State *L) {
  Vector2 result = Vector2Zero();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_Vector2ZeroU(lua_State *L) {
  Vector2 result = Vector2Zero();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_QuaternionToAxisAngle(lua_State *L) {
  Quaternion q = (*(Quaternion*)luaL_checkudata(L, 1, "Quaternion"));
  Vector3 *outAxis = lua_newuserdata(L, sizeof *outAxis); luaL_setmetatable(L, "Vector3");
  float outAngle;
  QuaternionToAxisAngle(q, outAxis, &outAngle);
  lua_pushnumber(L, outAngle);
  return 2;
}

static int l_MatrixMultiply(lua_State *L) {
  Matrix left = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix right = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  Matrix result = MatrixMultiply(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixMultiplyU(lua_State *L) {
  Matrix left = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix right = {luaL_checknumber(L, 17),luaL_checknumber(L, 18),luaL_checknumber(L, 19),luaL_checknumber(L, 20),luaL_checknumber(L, 21),luaL_checknumber(L, 22),luaL_checknumber(L, 23),luaL_checknumber(L, 24),luaL_checknumber(L, 25),luaL_checknumber(L, 26),luaL_checknumber(L, 27),luaL_checknumber(L, 28),luaL_checknumber(L, 29),luaL_checknumber(L, 30),luaL_checknumber(L, 31),luaL_checknumber(L, 32)};
  Matrix result = MatrixMultiply(left, right);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_Vector3Max(lua_State *L) {
  Vector3 v1 = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 v2 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 result = Vector3Max(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_Vector3MaxU(lua_State *L) {
  Vector3 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 v2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector3 result = Vector3Max(v1, v2);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_QuaternionNlerp(lua_State *L) {
  Vector4 q1 = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 q2 = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  float amount = luaL_checknumber(L, 3);
  Vector4 result = QuaternionNlerp(q1, q2, amount);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionLerp(lua_State *L) {
  Vector4 q1 = (*(Vector4*)luaL_checkudata(L, 1, "Vector4"));
  Vector4 q2 = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  float amount = luaL_checknumber(L, 3);
  Vector4 result = QuaternionLerp(q1, q2, amount);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_QuaternionFromEuler(lua_State *L) {
  float roll = luaL_checknumber(L, 1);
  float pitch = luaL_checknumber(L, 2);
  float yaw = luaL_checknumber(L, 3);
  Vector4 result = QuaternionFromEuler(roll, pitch, yaw);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_MatrixTranspose(lua_State *L) {
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  Matrix result = MatrixTranspose(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixTransposeU(lua_State *L) {
  Matrix mat = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  Matrix result = MatrixTranspose(mat);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_MatrixRotateY(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateY(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_MatrixRotateYU(lua_State *L) {
  float angle = luaL_checknumber(L, 1);
  Matrix result = MatrixRotateY(angle);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static const luaL_Reg l_raymath_functions[] = {
  {"Lerp", l_Lerp},
  {"Clamp", l_Clamp},
  {"Vector3OrthoNormalize", l_Vector3OrthoNormalize},
  {"Vector2Divide", l_Vector2Divide},
  {"MatrixScale", l_MatrixScale},
  {"Vector3ToFloatV", l_Vector3ToFloatV},
  {"MatrixFrustum", l_MatrixFrustum},
  {"MatrixTranslate", l_MatrixTranslate},
  {"Vector3Barycenter", l_Vector3Barycenter},
  {"Vector3Normalize", l_Vector3Normalize},
  {"Vector2Lerp", l_Vector2Lerp},
  {"QuaternionMultiply", l_QuaternionMultiply},
  {"MatrixToFloatV", l_MatrixToFloatV},
  {"Vector2Length", l_Vector2Length},
  {"MatrixIdentity", l_MatrixIdentity},
  {"Vector3Lerp", l_Vector3Lerp},
  {"MatrixTrace", l_MatrixTrace},
  {"Vector3Scale", l_Vector3Scale},
  {"MatrixAdd", l_MatrixAdd},
  {"Vector3Divide", l_Vector3Divide},
  {"MatrixRotateX", l_MatrixRotateX},
  {"Vector3MultiplyV", l_Vector3MultiplyV},
  {"Vector3Add", l_Vector3Add},
  {"MatrixRotateZ", l_MatrixRotateZ},
  {"MatrixRotate", l_MatrixRotate},
  {"QuaternionInvert", l_QuaternionInvert},
  {"Vector3RotateByQuaternion", l_Vector3RotateByQuaternion},
  {"MatrixSubtract", l_MatrixSubtract},
  {"QuaternionFromMatrix", l_QuaternionFromMatrix},
  {"Vector3DivideV", l_Vector3DivideV},
  {"Vector3Transform", l_Vector3Transform},
  {"Vector2Distance", l_Vector2Distance},
  {"QuaternionToMatrix", l_QuaternionToMatrix},
  {"MatrixOrtho", l_MatrixOrtho},
  {"QuaternionFromVector3ToVector3", l_QuaternionFromVector3ToVector3},
  {"Vector2Negate", l_Vector2Negate},
  {"MatrixInvert", l_MatrixInvert},
  {"Vector3DotProduct", l_Vector3DotProduct},
  {"QuaternionFromAxisAngle", l_QuaternionFromAxisAngle},
  {"Vector2Normalize", l_Vector2Normalize},
  {"Vector2Add", l_Vector2Add},
  {"Vector3Negate", l_Vector3Negate},
  {"Vector3Zero", l_Vector3Zero},
  {"QuaternionIdentity", l_QuaternionIdentity},
  {"QuaternionNormalize", l_QuaternionNormalize},
  {"QuaternionLength", l_QuaternionLength},
  {"Vector3Subtract", l_Vector3Subtract},
  {"Vector3Reflect", l_Vector3Reflect},
  {"Vector3One", l_Vector3One},
  {"Vector3Perpendicular", l_Vector3Perpendicular},
  {"Vector3Multiply", l_Vector3Multiply},
  {"Vector3Min", l_Vector3Min},
  {"QuaternionTransform", l_QuaternionTransform},
  {"QuaternionSlerp", l_QuaternionSlerp},
  {"Vector3Length", l_Vector3Length},
  {"Vector2One", l_Vector2One},
  {"MatrixLookAt", l_MatrixLookAt},
  {"MatrixNormalize", l_MatrixNormalize},
  {"MatrixDeterminant", l_MatrixDeterminant},
  {"Vector3Distance", l_Vector3Distance},
  {"Vector3CrossProduct", l_Vector3CrossProduct},
  {"QuaternionToEuler", l_QuaternionToEuler},
  {"Vector2Subtract", l_Vector2Subtract},
  {"MatrixPerspective", l_MatrixPerspective},
  {"Vector2Scale", l_Vector2Scale},
  {"Vector2MultiplyV", l_Vector2MultiplyV},
  {"Vector2Angle", l_Vector2Angle},
  {"Vector2DivideV", l_Vector2DivideV},
  {"Vector2DotProduct", l_Vector2DotProduct},
  {"Vector2Zero", l_Vector2Zero},
  {"QuaternionToAxisAngle", l_QuaternionToAxisAngle},
  {"MatrixMultiply", l_MatrixMultiply},
  {"Vector3Max", l_Vector3Max},
  {"QuaternionNlerp", l_QuaternionNlerp},
  {"QuaternionLerp", l_QuaternionLerp},
  {"QuaternionFromEuler", l_QuaternionFromEuler},
  {"MatrixTranspose", l_MatrixTranspose},
  {"MatrixRotateY", l_MatrixRotateY},
  {"Vector2DivideU", l_Vector2DivideU},
  {"MatrixScaleU", l_MatrixScaleU},
  {"Vector3ToFloatVU", l_Vector3ToFloatVU},
  {"MatrixFrustumU", l_MatrixFrustumU},
  {"MatrixTranslateU", l_MatrixTranslateU},
  {"Vector3BarycenterU", l_Vector3BarycenterU},
  {"Vector3NormalizeU", l_Vector3NormalizeU},
  {"Vector2LerpU", l_Vector2LerpU},
  {"MatrixToFloatVU", l_MatrixToFloatVU},
  {"Vector2LengthU", l_Vector2LengthU},
  {"MatrixIdentityU", l_MatrixIdentityU},
  {"Vector3LerpU", l_Vector3LerpU},
  {"MatrixTraceU", l_MatrixTraceU},
  {"Vector3ScaleU", l_Vector3ScaleU},
  {"MatrixAddU", l_MatrixAddU},
  {"Vector3DivideU", l_Vector3DivideU},
  {"MatrixRotateXU", l_MatrixRotateXU},
  {"Vector3MultiplyVU", l_Vector3MultiplyVU},
  {"Vector3AddU", l_Vector3AddU},
  {"MatrixRotateZU", l_MatrixRotateZU},
  {"MatrixRotateU", l_MatrixRotateU},
  {"Vector3RotateByQuaternionU", l_Vector3RotateByQuaternionU},
  {"MatrixSubtractU", l_MatrixSubtractU},
  {"QuaternionFromMatrixU", l_QuaternionFromMatrixU},
  {"Vector3DivideVU", l_Vector3DivideVU},
  {"Vector3TransformU", l_Vector3TransformU},
  {"Vector2DistanceU", l_Vector2DistanceU},
  {"QuaternionToMatrixU", l_QuaternionToMatrixU},
  {"MatrixOrthoU", l_MatrixOrthoU},
  {"QuaternionFromVector3ToVector3U", l_QuaternionFromVector3ToVector3U},
  {"Vector2NegateU", l_Vector2NegateU},
  {"MatrixInvertU", l_MatrixInvertU},
  {"Vector3DotProductU", l_Vector3DotProductU},
  {"QuaternionFromAxisAngleU", l_QuaternionFromAxisAngleU},
  {"Vector2NormalizeU", l_Vector2NormalizeU},
  {"Vector2AddU", l_Vector2AddU},
  {"Vector3NegateU", l_Vector3NegateU},
  {"Vector3ZeroU", l_Vector3ZeroU},
  {"Vector3SubtractU", l_Vector3SubtractU},
  {"Vector3ReflectU", l_Vector3ReflectU},
  {"Vector3OneU", l_Vector3OneU},
  {"Vector3PerpendicularU", l_Vector3PerpendicularU},
  {"Vector3MultiplyU", l_Vector3MultiplyU},
  {"Vector3MinU", l_Vector3MinU},
  {"QuaternionTransformU", l_QuaternionTransformU},
  {"Vector2OneU", l_Vector2OneU},
  {"MatrixLookAtU", l_MatrixLookAtU},
  {"MatrixNormalizeU", l_MatrixNormalizeU},
  {"MatrixDeterminantU", l_MatrixDeterminantU},
  {"Vector3DistanceU", l_Vector3DistanceU},
  {"Vector3CrossProductU", l_Vector3CrossProductU},
  {"QuaternionToEulerU", l_QuaternionToEulerU},
  {"Vector2SubtractU", l_Vector2SubtractU},
  {"MatrixPerspectiveU", l_MatrixPerspectiveU},
  {"Vector2ScaleU", l_Vector2ScaleU},
  {"Vector2MultiplyVU", l_Vector2MultiplyVU},
  {"Vector2AngleU", l_Vector2AngleU},
  {"Vector2DivideVU", l_Vector2DivideVU},
  {"Vector2DotProductU", l_Vector2DotProductU},
  {"Vector2ZeroU", l_Vector2ZeroU},
  {"MatrixMultiplyU", l_MatrixMultiplyU},
  {"Vector3MaxU", l_Vector3MaxU},
  {"MatrixTransposeU", l_MatrixTransposeU},
  {"MatrixRotateYU", l_MatrixRotateYU},
  {NULL, NULL}
};

LUAMOD_API int luaopen_raymath(lua_State *L) {
  luaL_newlib(L, l_raymath_functions);
  lua_pushnumber(L, PI);
  lua_setfield(L, -2, "PI");
  return 1;
}
