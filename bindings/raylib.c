#include <raylib.h>
#include <rlgl.h>

typedef struct { void *data; } OpaqueMusic;

typedef struct IVector2{
  int x;
  int y;
} IVector2;

typedef struct IVector3{
  int x;
  int y;
  int z;
} IVector3;

typedef struct IVector4{
  int x;
  int y;
  int z;
  int w;
} IVector4;

// Begin blending mode (alpha, additive, multiplied)
static int l_raylib_BeginBlendMode(lua_State *L) {
  int mode = luaL_checkinteger(L, 1);
  BeginBlendMode(mode);
  return 0;
}

// Setup canvas (framebuffer) to start drawing
static int l_raylib_BeginDrawing(lua_State *L) {
  (void)L; // Suppress unused warning
  BeginDrawing();
  return 0;
}

// Initialize 2D mode with custom camera (2D)
static int l_raylib_BeginMode2D(lua_State *L) {
  Camera2D camera = (*(Camera2D*)luaL_checkudata(L, 1, "Camera2D"));
  BeginMode2D(camera);
  return 0;
}

// Initializes 3D mode with custom camera (3D)
static int l_raylib_BeginMode3D(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  BeginMode3D(camera);
  return 0;
}

// Begin scissor mode (define screen area for following drawing)
static int l_raylib_BeginScissorMode(lua_State *L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  BeginScissorMode(x, y, width, height);
  return 0;
}

// Begin custom shader drawing
static int l_raylib_BeginShaderMode(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  BeginShaderMode(shader);
  return 0;
}

// Initializes render texture for drawing
static int l_raylib_BeginTextureMode(lua_State *L) {
  RenderTexture2D target = (*(RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D"));
  BeginTextureMode(target);
  return 0;
}

// Begin VR simulator stereo rendering
static int l_raylib_BeginVrDrawing(lua_State *L) {
  (void)L; // Suppress unused warning
  BeginVrDrawing();
  return 0;
}

// Change working directory, returns true if success
static int l_raylib_ChangeDirectory(lua_State *L) {
  const char* dir = luaL_checkstring(L, 1);
  bool result = ChangeDirectory(dir);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between box and sphere
static int l_raylib_CheckCollisionBoxSphere(lua_State *L) {
  BoundingBox box = (*(BoundingBox*)luaL_checkudata(L, 1, "BoundingBox"));
  Vector3 centerSphere = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float radiusSphere = luaL_checknumber(L, 3);
  bool result = CheckCollisionBoxSphere(box, centerSphere, radiusSphere);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between box and sphere (unpacked version)
static int l_raylib_CheckCollisionBoxSphereU(lua_State *L) {
  BoundingBox box = (*(BoundingBox*)luaL_checkudata(L, 1, "BoundingBox"));
  Vector3 centerSphere = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float radiusSphere = luaL_checknumber(L, 5);
  bool result = CheckCollisionBoxSphere(box, centerSphere, radiusSphere);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between two bounding boxes
static int l_raylib_CheckCollisionBoxes(lua_State *L) {
  BoundingBox box1 = (*(BoundingBox*)luaL_checkudata(L, 1, "BoundingBox"));
  BoundingBox box2 = (*(BoundingBox*)luaL_checkudata(L, 2, "BoundingBox"));
  bool result = CheckCollisionBoxes(box1, box2);
  lua_pushboolean(L, result);
  return 1;
}

// Check collision between circle and rectangle
static int l_raylib_CheckCollisionCircleRec(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float radius = luaL_checknumber(L, 2);
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  bool result = CheckCollisionCircleRec(center, radius, rec);
  lua_pushboolean(L, result);
  return 1;
}

// Check collision between circle and rectangle (unpacked version)
static int l_raylib_CheckCollisionCircleRecU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float radius = luaL_checknumber(L, 3);
  Rectangle rec = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  bool result = CheckCollisionCircleRec(center, radius, rec);
  lua_pushboolean(L, result);
  return 1;
}

// Check collision between two circles
static int l_raylib_CheckCollisionCircles(lua_State *L) {
  Vector2 center1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float radius1 = luaL_checknumber(L, 2);
  Vector2 center2 = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  float radius2 = luaL_checknumber(L, 4);
  bool result = CheckCollisionCircles(center1, radius1, center2, radius2);
  lua_pushboolean(L, result);
  return 1;
}

// Check collision between two circles (unpacked version)
static int l_raylib_CheckCollisionCirclesU(lua_State *L) {
  Vector2 center1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float radius1 = luaL_checknumber(L, 3);
  Vector2 center2 = {luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  float radius2 = luaL_checknumber(L, 6);
  bool result = CheckCollisionCircles(center1, radius1, center2, radius2);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside circle
static int l_raylib_CheckCollisionPointCircle(lua_State *L) {
  Vector2 point = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float radius = luaL_checknumber(L, 3);
  bool result = CheckCollisionPointCircle(point, center, radius);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside circle (unpacked version)
static int l_raylib_CheckCollisionPointCircleU(lua_State *L) {
  Vector2 point = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 center = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float radius = luaL_checknumber(L, 5);
  bool result = CheckCollisionPointCircle(point, center, radius);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside rectangle
static int l_raylib_CheckCollisionPointRec(lua_State *L) {
  Vector2 point = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  bool result = CheckCollisionPointRec(point, rec);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside rectangle (unpacked version)
static int l_raylib_CheckCollisionPointRecU(lua_State *L) {
  Vector2 point = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Rectangle rec = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  bool result = CheckCollisionPointRec(point, rec);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside a triangle
static int l_raylib_CheckCollisionPointTriangle(lua_State *L) {
  Vector2 point = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 p1 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 p2 = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  Vector2 p3 = (*(Vector2*)luaL_checkudata(L, 4, "Vector2"));
  bool result = CheckCollisionPointTriangle(point, p1, p2, p3);
  lua_pushboolean(L, result);
  return 1;
}

// Check if point is inside a triangle (unpacked version)
static int l_raylib_CheckCollisionPointTriangleU(lua_State *L) {
  Vector2 point = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 p1 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 p2 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Vector2 p3 = {luaL_checknumber(L, 7),luaL_checknumber(L, 8)};
  bool result = CheckCollisionPointTriangle(point, p1, p2, p3);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between ray and box
static int l_raylib_CheckCollisionRayBox(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  BoundingBox box = (*(BoundingBox*)luaL_checkudata(L, 2, "BoundingBox"));
  bool result = CheckCollisionRayBox(ray, box);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between ray and sphere
static int l_raylib_CheckCollisionRaySphere(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Vector3 spherePosition = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float sphereRadius = luaL_checknumber(L, 3);
  bool result = CheckCollisionRaySphere(ray, spherePosition, sphereRadius);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between ray and sphere (unpacked version)
static int l_raylib_CheckCollisionRaySphereU(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Vector3 spherePosition = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float sphereRadius = luaL_checknumber(L, 5);
  bool result = CheckCollisionRaySphere(ray, spherePosition, sphereRadius);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between ray and sphere, returns collision point
static int l_raylib_CheckCollisionRaySphereEx(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Vector3 spherePosition = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float sphereRadius = luaL_checknumber(L, 3);
  Vector3 *collisionPoint = lua_newuserdata(L, sizeof *collisionPoint); luaL_setmetatable(L, "Vector3");
  if (CheckCollisionRaySphereEx(ray, spherePosition, sphereRadius, collisionPoint)) {
    return 1;
  } else {
    lua_pop(L, 1);
    return 0;
  }
}

// Check collision between two rectangles
static int l_raylib_CheckCollisionRecs(lua_State *L) {
  Rectangle rec1 = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Rectangle rec2 = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  bool result = CheckCollisionRecs(rec1, rec2);
  lua_pushboolean(L, result);
  return 1;
}

// Check collision between two rectangles (unpacked version)
static int l_raylib_CheckCollisionRecsU(lua_State *L) {
  Rectangle rec1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Rectangle rec2 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8)};
  bool result = CheckCollisionRecs(rec1, rec2);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between two spheres
static int l_raylib_CheckCollisionSpheres(lua_State *L) {
  Vector3 centerA = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radiusA = luaL_checknumber(L, 2);
  Vector3 centerB = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  float radiusB = luaL_checknumber(L, 4);
  bool result = CheckCollisionSpheres(centerA, radiusA, centerB, radiusB);
  lua_pushboolean(L, result);
  return 1;
}

// Detect collision between two spheres (unpacked version)
static int l_raylib_CheckCollisionSpheresU(lua_State *L) {
  Vector3 centerA = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radiusA = luaL_checknumber(L, 4);
  Vector3 centerB = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  float radiusB = luaL_checknumber(L, 8);
  bool result = CheckCollisionSpheres(centerA, radiusA, centerB, radiusB);
  lua_pushboolean(L, result);
  return 1;
}

// Set background color (framebuffer clear color)
static int l_raylib_ClearBackground(lua_State *L) {
  Color color = (*(Color*)luaL_checkudata(L, 1, "Color"));
  ClearBackground(color);
  return 0;
}

// Set background color (framebuffer clear color) (unpacked version)
static int l_raylib_ClearBackgroundU(lua_State *L) {
  Color color = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  ClearBackground(color);
  return 0;
}

// Clear directory files paths buffers (free memory)
static int l_raylib_ClearDirectoryFiles(lua_State *L) {
  (void)L; // Suppress unused warning
  ClearDirectoryFiles();
  return 0;
}

// Clear dropped files paths buffer (free memory)
static int l_raylib_ClearDroppedFiles(lua_State *L) {
  (void)L; // Suppress unused warning
  ClearDroppedFiles();
  return 0;
}

// Close the audio device and context
static int l_raylib_CloseAudioDevice(lua_State *L) {
  (void)L; // Suppress unused warning
  CloseAudioDevice();
  return 0;
}

// Close audio stream and free memory
static int l_raylib_CloseAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  CloseAudioStream(stream);
  return 0;
}

// Close VR simulator for current device
static int l_raylib_CloseVrSimulator(lua_State *L) {
  (void)L; // Suppress unused warning
  CloseVrSimulator();
  return 0;
}

// Close window and unload OpenGL context
static int l_raylib_CloseWindow(lua_State *L) {
  (void)L; // Suppress unused warning
  CloseWindow();
  return 0;
}

// Returns a Color from HSV values
static int l_raylib_ColorFromHSV(lua_State *L) {
  Vector3 hsv = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Color result = ColorFromHSV(hsv);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

// Returns a Color from HSV values (unpacked version)
static int l_raylib_ColorFromHSVU(lua_State *L) {
  Vector3 hsv = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Color result = ColorFromHSV(hsv);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

// Returns color normalized as float [0..1]
static int l_raylib_ColorNormalize(lua_State *L) {
  Color color = (*(Color*)luaL_checkudata(L, 1, "Color"));
  Vector4 result = ColorNormalize(color);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

// Returns color normalized as float [0..1] (unpacked version)
static int l_raylib_ColorNormalizeU(lua_State *L) {
  Color color = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Vector4 result = ColorNormalize(color);
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);lua_pushnumber(L, result.w);
  return 4;
}

// Returns HSV values for a Color
static int l_raylib_ColorToHSV(lua_State *L) {
  Color color = (*(Color*)luaL_checkudata(L, 1, "Color"));
  Vector3 result = ColorToHSV(color);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

// Returns HSV values for a Color (unpacked version)
static int l_raylib_ColorToHSVU(lua_State *L) {
  Color color = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Vector3 result = ColorToHSV(color);
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

// Returns hexadecimal value for a Color
static int l_raylib_ColorToInt(lua_State *L) {
  Color color = (*(Color*)luaL_checkudata(L, 1, "Color"));
  int result = ColorToInt(color);
  lua_pushinteger(L, result);
  return 1;
}

// Returns hexadecimal value for a Color (unpacked version)
static int l_raylib_ColorToIntU(lua_State *L) {
  Color color = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  int result = ColorToInt(color);
  lua_pushinteger(L, result);
  return 1;
}

// Disables cursor (lock cursor)
static int l_raylib_DisableCursor(lua_State *L) {
  (void)L; // Suppress unused warning
  DisableCursor();
  return 0;
}

// Draw a billboard texture
static int l_raylib_DrawBillboard(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  Vector3 center = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  float size = luaL_checknumber(L, 4);
  Color tint = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawBillboard(camera, texture, center, size, tint);
  return 0;
}

// Draw a billboard texture (unpacked version)
static int l_raylib_DrawBillboardU(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Texture2D texture = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Vector3 center = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  float size = luaL_checknumber(L, 10);
  Color tint = {luaL_checkinteger(L, 11),luaL_checkinteger(L, 12),luaL_checkinteger(L, 13),luaL_checkinteger(L, 14)};
  DrawBillboard(camera, texture, center, size, tint);
  return 0;
}

// Draw a billboard texture defined by sourceRec
static int l_raylib_DrawBillboardRec(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  Rectangle sourceRec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  Vector3 center = (*(Vector3*)luaL_checkudata(L, 4, "Vector3"));
  float size = luaL_checknumber(L, 5);
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawBillboardRec(camera, texture, sourceRec, center, size, tint);
  return 0;
}

// Draw a billboard texture defined by sourceRec (unpacked version)
static int l_raylib_DrawBillboardRecU(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Texture2D texture = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Rectangle sourceRec = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10)};
  Vector3 center = {luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13)};
  float size = luaL_checknumber(L, 14);
  Color tint = {luaL_checkinteger(L, 15),luaL_checkinteger(L, 16),luaL_checkinteger(L, 17),luaL_checkinteger(L, 18)};
  DrawBillboardRec(camera, texture, sourceRec, center, size, tint);
  return 0;
}

// Draw bounding box (wires)
static int l_raylib_DrawBoundingBox(lua_State *L) {
  BoundingBox box = (*(BoundingBox*)luaL_checkudata(L, 1, "BoundingBox"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  DrawBoundingBox(box, color);
  return 0;
}

// Draw bounding box (wires) (unpacked version)
static int l_raylib_DrawBoundingBoxU(lua_State *L) {
  BoundingBox box = (*(BoundingBox*)luaL_checkudata(L, 1, "BoundingBox"));
  Color color = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  DrawBoundingBox(box, color);
  return 0;
}

// Draw a color-filled circle
static int l_raylib_DrawCircle(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawCircle(centerX, centerY, radius, color);
  return 0;
}

// Draw a color-filled circle (unpacked version)
static int l_raylib_DrawCircleU(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color = {luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  DrawCircle(centerX, centerY, radius, color);
  return 0;
}

// Draw a circle in 3D world space
static int l_raylib_DrawCircle3D(lua_State *L) {
  Vector3 center = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radius = luaL_checknumber(L, 2);
  Vector3 rotationAxis = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  float rotationAngle = luaL_checknumber(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
  return 0;
}

// Draw a circle in 3D world space (unpacked version)
static int l_raylib_DrawCircle3DU(lua_State *L) {
  Vector3 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radius = luaL_checknumber(L, 4);
  Vector3 rotationAxis = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  float rotationAngle = luaL_checknumber(L, 8);
  Color color = {luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12)};
  DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
  return 0;
}

// Draw a gradient-filled circle
static int l_raylib_DrawCircleGradient(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color1 = (*(Color*)luaL_checkudata(L, 4, "Color"));
  Color color2 = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawCircleGradient(centerX, centerY, radius, color1, color2);
  return 0;
}

// Draw a gradient-filled circle (unpacked version)
static int l_raylib_DrawCircleGradientU(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color1 = {luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  Color color2 = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawCircleGradient(centerX, centerY, radius, color1, color2);
  return 0;
}

// Draw circle outline
static int l_raylib_DrawCircleLines(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawCircleLines(centerX, centerY, radius, color);
  return 0;
}

// Draw circle outline (unpacked version)
static int l_raylib_DrawCircleLinesU(lua_State *L) {
  int centerX = luaL_checkinteger(L, 1);
  int centerY = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  Color color = {luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  DrawCircleLines(centerX, centerY, radius, color);
  return 0;
}

// Draw a piece of a circle
static int l_raylib_DrawCircleSector(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float radius = luaL_checknumber(L, 2);
  int startAngle = luaL_checkinteger(L, 3);
  int endAngle = luaL_checkinteger(L, 4);
  int segments = luaL_checkinteger(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw a piece of a circle (unpacked version)
static int l_raylib_DrawCircleSectorU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float radius = luaL_checknumber(L, 3);
  int startAngle = luaL_checkinteger(L, 4);
  int endAngle = luaL_checkinteger(L, 5);
  int segments = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw circle sector outline
static int l_raylib_DrawCircleSectorLines(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float radius = luaL_checknumber(L, 2);
  int startAngle = luaL_checkinteger(L, 3);
  int endAngle = luaL_checkinteger(L, 4);
  int segments = luaL_checkinteger(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw circle sector outline (unpacked version)
static int l_raylib_DrawCircleSectorLinesU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float radius = luaL_checknumber(L, 3);
  int startAngle = luaL_checkinteger(L, 4);
  int endAngle = luaL_checkinteger(L, 5);
  int segments = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw a color-filled circle (Vector version)
static int l_raylib_DrawCircleV(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float radius = luaL_checknumber(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawCircleV(center, radius, color);
  return 0;
}

// Draw a color-filled circle (Vector version) (unpacked version)
static int l_raylib_DrawCircleVU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float radius = luaL_checknumber(L, 3);
  Color color = {luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  DrawCircleV(center, radius, color);
  return 0;
}

// Draw cube
static int l_raylib_DrawCube(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float width = luaL_checknumber(L, 2);
  float height = luaL_checknumber(L, 3);
  float length = luaL_checknumber(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawCube(position, width, height, length, color);
  return 0;
}

// Draw cube (unpacked version)
static int l_raylib_DrawCubeU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float width = luaL_checknumber(L, 4);
  float height = luaL_checknumber(L, 5);
  float length = luaL_checknumber(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCube(position, width, height, length, color);
  return 0;
}

// Draw cube textured
static int l_raylib_DrawCubeTexture(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float width = luaL_checknumber(L, 3);
  float height = luaL_checknumber(L, 4);
  float length = luaL_checknumber(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawCubeTexture(texture, position, width, height, length, color);
  return 0;
}

// Draw cube textured (unpacked version)
static int l_raylib_DrawCubeTextureU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Vector3 position = {luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8)};
  float width = luaL_checknumber(L, 9);
  float height = luaL_checknumber(L, 10);
  float length = luaL_checknumber(L, 11);
  Color color = {luaL_checkinteger(L, 12),luaL_checkinteger(L, 13),luaL_checkinteger(L, 14),luaL_checkinteger(L, 15)};
  DrawCubeTexture(texture, position, width, height, length, color);
  return 0;
}

// Draw cube (Vector version)
static int l_raylib_DrawCubeV(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 size = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawCubeV(position, size, color);
  return 0;
}

// Draw cube (Vector version) (unpacked version)
static int l_raylib_DrawCubeVU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 size = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCubeV(position, size, color);
  return 0;
}

// Draw cube wires
static int l_raylib_DrawCubeWires(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float width = luaL_checknumber(L, 2);
  float height = luaL_checknumber(L, 3);
  float length = luaL_checknumber(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawCubeWires(position, width, height, length, color);
  return 0;
}

// Draw cube wires (unpacked version)
static int l_raylib_DrawCubeWiresU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float width = luaL_checknumber(L, 4);
  float height = luaL_checknumber(L, 5);
  float length = luaL_checknumber(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCubeWires(position, width, height, length, color);
  return 0;
}

// Draw cube wires (Vector version)
static int l_raylib_DrawCubeWiresV(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 size = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawCubeWiresV(position, size, color);
  return 0;
}

// Draw cube wires (Vector version) (unpacked version)
static int l_raylib_DrawCubeWiresVU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 size = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawCubeWiresV(position, size, color);
  return 0;
}

// Draw a cylinder/cone
static int l_raylib_DrawCylinder(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radiusTop = luaL_checknumber(L, 2);
  float radiusBottom = luaL_checknumber(L, 3);
  float height = luaL_checknumber(L, 4);
  int slices = luaL_checkinteger(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
  return 0;
}

// Draw a cylinder/cone (unpacked version)
static int l_raylib_DrawCylinderU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radiusTop = luaL_checknumber(L, 4);
  float radiusBottom = luaL_checknumber(L, 5);
  float height = luaL_checknumber(L, 6);
  int slices = luaL_checkinteger(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
  return 0;
}

// Draw a cylinder/cone wires
static int l_raylib_DrawCylinderWires(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radiusTop = luaL_checknumber(L, 2);
  float radiusBottom = luaL_checknumber(L, 3);
  float height = luaL_checknumber(L, 4);
  int slices = luaL_checkinteger(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
  return 0;
}

// Draw a cylinder/cone wires (unpacked version)
static int l_raylib_DrawCylinderWiresU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radiusTop = luaL_checknumber(L, 4);
  float radiusBottom = luaL_checknumber(L, 5);
  float height = luaL_checknumber(L, 6);
  int slices = luaL_checkinteger(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
  return 0;
}

// Shows current FPS
static int l_raylib_DrawFPS(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  DrawFPS(posX, posY);
  return 0;
}

// Draw simple gizmo
static int l_raylib_DrawGizmo(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  DrawGizmo(position);
  return 0;
}

// Draw simple gizmo (unpacked version)
static int l_raylib_DrawGizmoU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  DrawGizmo(position);
  return 0;
}

// Draw a grid (centered at (0, 0, 0))
static int l_raylib_DrawGrid(lua_State *L) {
  int slices = luaL_checkinteger(L, 1);
  float spacing = luaL_checknumber(L, 2);
  DrawGrid(slices, spacing);
  return 0;
}

// Draw a line
static int l_raylib_DrawLine(lua_State *L) {
  int startPosX = luaL_checkinteger(L, 1);
  int startPosY = luaL_checkinteger(L, 2);
  int endPosX = luaL_checkinteger(L, 3);
  int endPosY = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawLine(startPosX, startPosY, endPosX, endPosY, color);
  return 0;
}

// Draw a line (unpacked version)
static int l_raylib_DrawLineU(lua_State *L) {
  int startPosX = luaL_checkinteger(L, 1);
  int startPosY = luaL_checkinteger(L, 2);
  int endPosX = luaL_checkinteger(L, 3);
  int endPosY = luaL_checkinteger(L, 4);
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawLine(startPosX, startPosY, endPosX, endPosY, color);
  return 0;
}

// Draw a line in 3D world space
static int l_raylib_DrawLine3D(lua_State *L) {
  Vector3 startPos = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector3 endPos = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawLine3D(startPos, endPos, color);
  return 0;
}

// Draw a line in 3D world space (unpacked version)
static int l_raylib_DrawLine3DU(lua_State *L) {
  Vector3 startPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector3 endPos = {luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawLine3D(startPos, endPos, color);
  return 0;
}

// Draw a line using cubic-bezier curves in-out
static int l_raylib_DrawLineBezier(lua_State *L) {
  Vector2 startPos = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 endPos = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float thick = luaL_checknumber(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawLineBezier(startPos, endPos, thick, color);
  return 0;
}

// Draw a line using cubic-bezier curves in-out (unpacked version)
static int l_raylib_DrawLineBezierU(lua_State *L) {
  Vector2 startPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 endPos = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float thick = luaL_checknumber(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawLineBezier(startPos, endPos, thick, color);
  return 0;
}

// Draw a line defining thickness
static int l_raylib_DrawLineEx(lua_State *L) {
  Vector2 startPos = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 endPos = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float thick = luaL_checknumber(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawLineEx(startPos, endPos, thick, color);
  return 0;
}

// Draw a line defining thickness (unpacked version)
static int l_raylib_DrawLineExU(lua_State *L) {
  Vector2 startPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 endPos = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float thick = luaL_checknumber(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawLineEx(startPos, endPos, thick, color);
  return 0;
}

// Draw lines sequence
static int l_raylib_DrawLineStrip(lua_State *L) {
  int len = lua_rawlen(L, 1);
  Color *color = luaL_checkudata(L, 2, "Color");
  if (len < 4) return 0;
  if (rlCheckBufferLimit(len/2)) rlglDraw();
  rlBegin(RL_LINES);
  {
    float x0, y0, x1, y1;
    rlColor4ub(color->r, color->g, color->b, color->a);
    lua_rawgeti(L, 1, 1); x0 = luaL_checknumber(L, -1);
    lua_rawgeti(L, 1, 2); y0 = luaL_checknumber(L, -1);
    for (int i = 3; i <= len; i += 2)
    {
      lua_rawgeti(L, 1, i); x1 = luaL_checknumber(L, -1);
      lua_rawgeti(L, 1, i+1); y1 = luaL_checknumber(L, -1);
      rlVertex2f(x0, y0);
      rlVertex2f(x1, y1);
      x0 = x1; y0 = y1;
    }
  }
  rlEnd();
	return 0;
}

// Draw a line (Vector version)
static int l_raylib_DrawLineV(lua_State *L) {
  Vector2 startPos = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 endPos = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawLineV(startPos, endPos, color);
  return 0;
}

// Draw a line (Vector version) (unpacked version)
static int l_raylib_DrawLineVU(lua_State *L) {
  Vector2 startPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 endPos = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawLineV(startPos, endPos, color);
  return 0;
}

// Draw a model (with texture if set)
static int l_raylib_DrawModel(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float scale = luaL_checknumber(L, 3);
  Color tint = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawModel(model, position, scale, tint);
  return 0;
}

// Draw a model (with texture if set) (unpacked version)
static int l_raylib_DrawModelU(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float scale = luaL_checknumber(L, 5);
  Color tint = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawModel(model, position, scale, tint);
  return 0;
}

// Draw a model with extended parameters
static int l_raylib_DrawModelEx(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 rotationAxis = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  float rotationAngle = luaL_checknumber(L, 4);
  Vector3 scale = (*(Vector3*)luaL_checkudata(L, 5, "Vector3"));
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return 0;
}

// Draw a model with extended parameters (unpacked version)
static int l_raylib_DrawModelExU(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector3 rotationAxis = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  float rotationAngle = luaL_checknumber(L, 8);
  Vector3 scale = {luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11)};
  Color tint = {luaL_checkinteger(L, 12),luaL_checkinteger(L, 13),luaL_checkinteger(L, 14),luaL_checkinteger(L, 15)};
  DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return 0;
}

// Draw a model wires (with texture if set)
static int l_raylib_DrawModelWires(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  float scale = luaL_checknumber(L, 3);
  Color tint = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawModelWires(model, position, scale, tint);
  return 0;
}

// Draw a model wires (with texture if set) (unpacked version)
static int l_raylib_DrawModelWiresU(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float scale = luaL_checknumber(L, 5);
  Color tint = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawModelWires(model, position, scale, tint);
  return 0;
}

// Draw a model wires (with texture if set) with extended parameters
static int l_raylib_DrawModelWiresEx(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 rotationAxis = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  float rotationAngle = luaL_checknumber(L, 4);
  Vector3 scale = (*(Vector3*)luaL_checkudata(L, 5, "Vector3"));
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return 0;
}

// Draw a model wires (with texture if set) with extended parameters (unpacked version)
static int l_raylib_DrawModelWiresExU(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  Vector3 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector3 rotationAxis = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  float rotationAngle = luaL_checknumber(L, 8);
  Vector3 scale = {luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11)};
  Color tint = {luaL_checkinteger(L, 12),luaL_checkinteger(L, 13),luaL_checkinteger(L, 14),luaL_checkinteger(L, 15)};
  DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
  return 0;
}

// Draw a pixel
static int l_raylib_DrawPixel(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawPixel(posX, posY, color);
  return 0;
}

// Draw a pixel (unpacked version)
static int l_raylib_DrawPixelU(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  Color color = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  DrawPixel(posX, posY, color);
  return 0;
}

// Draw a pixel (Vector version)
static int l_raylib_DrawPixelV(lua_State *L) {
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  DrawPixelV(position, color);
  return 0;
}

// Draw a pixel (Vector version) (unpacked version)
static int l_raylib_DrawPixelVU(lua_State *L) {
  Vector2 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Color color = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  DrawPixelV(position, color);
  return 0;
}

// Draw a plane XZ
static int l_raylib_DrawPlane(lua_State *L) {
  Vector3 centerPos = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Vector2 size = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawPlane(centerPos, size, color);
  return 0;
}

// Draw a plane XZ (unpacked version)
static int l_raylib_DrawPlaneU(lua_State *L) {
  Vector3 centerPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Vector2 size = {luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawPlane(centerPos, size, color);
  return 0;
}

// Draw a regular polygon (Vector version)
static int l_raylib_DrawPoly(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  int sides = luaL_checkinteger(L, 2);
  float radius = luaL_checknumber(L, 3);
  float rotation = luaL_checknumber(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawPoly(center, sides, radius, rotation, color);
  return 0;
}

// Draw a regular polygon (Vector version) (unpacked version)
static int l_raylib_DrawPolyU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  int sides = luaL_checkinteger(L, 3);
  float radius = luaL_checknumber(L, 4);
  float rotation = luaL_checknumber(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawPoly(center, sides, radius, rotation, color);
  return 0;
}

// Draw a ray line
static int l_raylib_DrawRay(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  DrawRay(ray, color);
  return 0;
}

// Draw a ray line (unpacked version)
static int l_raylib_DrawRayU(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Color color = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  DrawRay(ray, color);
  return 0;
}

// Draw a color-filled rectangle
static int l_raylib_DrawRectangle(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawRectangle(posX, posY, width, height, color);
  return 0;
}

// Draw a color-filled rectangle (unpacked version)
static int l_raylib_DrawRectangleU(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawRectangle(posX, posY, width, height, color);
  return 0;
}

// Draw a gradient-filled rectangle with custom vertex colors
static int l_raylib_DrawRectangleGradientEx(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Color col1 = (*(Color*)luaL_checkudata(L, 2, "Color"));
  Color col2 = (*(Color*)luaL_checkudata(L, 3, "Color"));
  Color col3 = (*(Color*)luaL_checkudata(L, 4, "Color"));
  Color col4 = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawRectangleGradientEx(rec, col1, col2, col3, col4);
  return 0;
}

// Draw a gradient-filled rectangle with custom vertex colors (unpacked version)
static int l_raylib_DrawRectangleGradientExU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Color col1 = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color col2 = {luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12)};
  Color col3 = {luaL_checkinteger(L, 13),luaL_checkinteger(L, 14),luaL_checkinteger(L, 15),luaL_checkinteger(L, 16)};
  Color col4 = {luaL_checkinteger(L, 17),luaL_checkinteger(L, 18),luaL_checkinteger(L, 19),luaL_checkinteger(L, 20)};
  DrawRectangleGradientEx(rec, col1, col2, col3, col4);
  return 0;
}

// Draw a horizontal-gradient-filled rectangle
static int l_raylib_DrawRectangleGradientH(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color1 = (*(Color*)luaL_checkudata(L, 5, "Color"));
  Color color2 = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawRectangleGradientH(posX, posY, width, height, color1, color2);
  return 0;
}

// Draw a horizontal-gradient-filled rectangle (unpacked version)
static int l_raylib_DrawRectangleGradientHU(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color1 = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color color2 = {luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12)};
  DrawRectangleGradientH(posX, posY, width, height, color1, color2);
  return 0;
}

// Draw a vertical-gradient-filled rectangle
static int l_raylib_DrawRectangleGradientV(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color1 = (*(Color*)luaL_checkudata(L, 5, "Color"));
  Color color2 = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawRectangleGradientV(posX, posY, width, height, color1, color2);
  return 0;
}

// Draw a vertical-gradient-filled rectangle (unpacked version)
static int l_raylib_DrawRectangleGradientVU(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color1 = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color color2 = {luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12)};
  DrawRectangleGradientV(posX, posY, width, height, color1, color2);
  return 0;
}

// Draw rectangle outline
static int l_raylib_DrawRectangleLines(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawRectangleLines(posX, posY, width, height, color);
  return 0;
}

// Draw rectangle outline (unpacked version)
static int l_raylib_DrawRectangleLinesU(lua_State *L) {
  int posX = luaL_checkinteger(L, 1);
  int posY = luaL_checkinteger(L, 2);
  int width = luaL_checkinteger(L, 3);
  int height = luaL_checkinteger(L, 4);
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawRectangleLines(posX, posY, width, height, color);
  return 0;
}

// Draw rectangle outline with extended parameters
static int l_raylib_DrawRectangleLinesEx(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  int lineThick = luaL_checkinteger(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawRectangleLinesEx(rec, lineThick, color);
  return 0;
}

// Draw rectangle outline with extended parameters (unpacked version)
static int l_raylib_DrawRectangleLinesExU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  int lineThick = luaL_checkinteger(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  DrawRectangleLinesEx(rec, lineThick, color);
  return 0;
}

// Draw a color-filled rectangle with pro parameters
static int l_raylib_DrawRectanglePro(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Vector2 origin = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float rotation = luaL_checknumber(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawRectanglePro(rec, origin, rotation, color);
  return 0;
}

// Draw a color-filled rectangle with pro parameters (unpacked version)
static int l_raylib_DrawRectangleProU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 origin = {luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float rotation = luaL_checknumber(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawRectanglePro(rec, origin, rotation, color);
  return 0;
}

// Draw a color-filled rectangle
static int l_raylib_DrawRectangleRec(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  DrawRectangleRec(rec, color);
  return 0;
}

// Draw a color-filled rectangle (unpacked version)
static int l_raylib_DrawRectangleRecU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawRectangleRec(rec, color);
  return 0;
}

// Draw rectangle with rounded edges
static int l_raylib_DrawRectangleRounded(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  float roundness = luaL_checknumber(L, 2);
  int segments = luaL_checkinteger(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawRectangleRounded(rec, roundness, segments, color);
  return 0;
}

// Draw rectangle with rounded edges (unpacked version)
static int l_raylib_DrawRectangleRoundedU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float roundness = luaL_checknumber(L, 5);
  int segments = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawRectangleRounded(rec, roundness, segments, color);
  return 0;
}

// Draw rectangle with rounded edges outline
static int l_raylib_DrawRectangleRoundedLines(lua_State *L) {
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  float roundness = luaL_checknumber(L, 2);
  int segments = luaL_checkinteger(L, 3);
  int lineThick = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
  return 0;
}

// Draw rectangle with rounded edges outline (unpacked version)
static int l_raylib_DrawRectangleRoundedLinesU(lua_State *L) {
  Rectangle rec = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float roundness = luaL_checknumber(L, 5);
  int segments = luaL_checkinteger(L, 6);
  int lineThick = luaL_checkinteger(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
  return 0;
}

// Draw a color-filled rectangle (Vector version)
static int l_raylib_DrawRectangleV(lua_State *L) {
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 size = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawRectangleV(position, size, color);
  return 0;
}

// Draw a color-filled rectangle (Vector version) (unpacked version)
static int l_raylib_DrawRectangleVU(lua_State *L) {
  Vector2 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 size = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawRectangleV(position, size, color);
  return 0;
}

// Draw ring
static int l_raylib_DrawRing(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float innerRadius = luaL_checknumber(L, 2);
  float outerRadius = luaL_checknumber(L, 3);
  int startAngle = luaL_checkinteger(L, 4);
  int endAngle = luaL_checkinteger(L, 5);
  int segments = luaL_checkinteger(L, 6);
  Color color = (*(Color*)luaL_checkudata(L, 7, "Color"));
  DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw ring (unpacked version)
static int l_raylib_DrawRingU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float innerRadius = luaL_checknumber(L, 3);
  float outerRadius = luaL_checknumber(L, 4);
  int startAngle = luaL_checkinteger(L, 5);
  int endAngle = luaL_checkinteger(L, 6);
  int segments = luaL_checkinteger(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw ring outline
static int l_raylib_DrawRingLines(lua_State *L) {
  Vector2 center = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  float innerRadius = luaL_checknumber(L, 2);
  float outerRadius = luaL_checknumber(L, 3);
  int startAngle = luaL_checkinteger(L, 4);
  int endAngle = luaL_checkinteger(L, 5);
  int segments = luaL_checkinteger(L, 6);
  Color color = (*(Color*)luaL_checkudata(L, 7, "Color"));
  DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw ring outline (unpacked version)
static int l_raylib_DrawRingLinesU(lua_State *L) {
  Vector2 center = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  float innerRadius = luaL_checknumber(L, 3);
  float outerRadius = luaL_checknumber(L, 4);
  int startAngle = luaL_checkinteger(L, 5);
  int endAngle = luaL_checkinteger(L, 6);
  int segments = luaL_checkinteger(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
  return 0;
}

// Draw sphere
static int l_raylib_DrawSphere(lua_State *L) {
  Vector3 centerPos = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radius = luaL_checknumber(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawSphere(centerPos, radius, color);
  return 0;
}

// Draw sphere (unpacked version)
static int l_raylib_DrawSphereU(lua_State *L) {
  Vector3 centerPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radius = luaL_checknumber(L, 4);
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawSphere(centerPos, radius, color);
  return 0;
}

// Draw sphere with extended parameters
static int l_raylib_DrawSphereEx(lua_State *L) {
  Vector3 centerPos = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radius = luaL_checknumber(L, 2);
  int rings = luaL_checkinteger(L, 3);
  int slices = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawSphereEx(centerPos, radius, rings, slices, color);
  return 0;
}

// Draw sphere with extended parameters (unpacked version)
static int l_raylib_DrawSphereExU(lua_State *L) {
  Vector3 centerPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radius = luaL_checknumber(L, 4);
  int rings = luaL_checkinteger(L, 5);
  int slices = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawSphereEx(centerPos, radius, rings, slices, color);
  return 0;
}

// Draw sphere wires
static int l_raylib_DrawSphereWires(lua_State *L) {
  Vector3 centerPos = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  float radius = luaL_checknumber(L, 2);
  int rings = luaL_checkinteger(L, 3);
  int slices = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawSphereWires(centerPos, radius, rings, slices, color);
  return 0;
}

// Draw sphere wires (unpacked version)
static int l_raylib_DrawSphereWiresU(lua_State *L) {
  Vector3 centerPos = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  float radius = luaL_checknumber(L, 4);
  int rings = luaL_checkinteger(L, 5);
  int slices = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawSphereWires(centerPos, radius, rings, slices, color);
  return 0;
}

// Draw text (using default font)
static int l_raylib_DrawText(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int posX = luaL_checkinteger(L, 2);
  int posY = luaL_checkinteger(L, 3);
  int fontSize = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawText(text, posX, posY, fontSize, color);
  return 0;
}

// Draw text (using default font) (unpacked version)
static int l_raylib_DrawTextU(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int posX = luaL_checkinteger(L, 2);
  int posY = luaL_checkinteger(L, 3);
  int fontSize = luaL_checkinteger(L, 4);
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  DrawText(text, posX, posY, fontSize, color);
  return 0;
}

// Draw text using font and additional parameters
static int l_raylib_DrawTextEx(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  float fontSize = luaL_checknumber(L, 4);
  float spacing = luaL_checknumber(L, 5);
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawTextEx(font, text, position, fontSize, spacing, tint);
  return 0;
}

// Draw text using font and additional parameters (unpacked version)
static int l_raylib_DrawTextExU(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  Vector2 position = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  float fontSize = luaL_checknumber(L, 5);
  float spacing = luaL_checknumber(L, 6);
  Color tint = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawTextEx(font, text, position, fontSize, spacing, tint);
  return 0;
}

// Draw text using font inside rectangle limits
static int l_raylib_DrawTextRec(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  float fontSize = luaL_checknumber(L, 4);
  float spacing = luaL_checknumber(L, 5);
  bool wordWrap = lua_toboolean(L, 6);
  Color tint = (*(Color*)luaL_checkudata(L, 7, "Color"));
  DrawTextRec(font, text, rec, fontSize, spacing, wordWrap, tint);
  return 0;
}

// Draw text using font inside rectangle limits (unpacked version)
static int l_raylib_DrawTextRecU(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  Rectangle rec = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float fontSize = luaL_checknumber(L, 7);
  float spacing = luaL_checknumber(L, 8);
  bool wordWrap = lua_toboolean(L, 9);
  Color tint = {luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12),luaL_checkinteger(L, 13)};
  DrawTextRec(font, text, rec, fontSize, spacing, wordWrap, tint);
  return 0;
}

// Draw text using font inside rectangle limits with support for text selection
static int l_raylib_DrawTextRecEx(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char * text = (char*)luaL_checkudata(L, 2, "char");
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  float fontSize = luaL_checknumber(L, 4);
  float spacing = luaL_checknumber(L, 5);
  bool wordWrap = lua_toboolean(L, 6);
  Color tint = (*(Color*)luaL_checkudata(L, 7, "Color"));
  int selectStart = luaL_checkinteger(L, 8);
  int selectLength = luaL_checkinteger(L, 9);
  Color selectText = (*(Color*)luaL_checkudata(L, 10, "Color"));
  Color selectBack = (*(Color*)luaL_checkudata(L, 11, "Color"));
  DrawTextRecEx(font, text, rec, fontSize, spacing, wordWrap, tint, selectStart, selectLength, selectText, selectBack);
  return 0;
}

// Draw text using font inside rectangle limits with support for text selection (unpacked version)
static int l_raylib_DrawTextRecExU(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char * text = (char*)luaL_checkudata(L, 2, "char");
  Rectangle rec = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  float fontSize = luaL_checknumber(L, 7);
  float spacing = luaL_checknumber(L, 8);
  bool wordWrap = lua_toboolean(L, 9);
  Color tint = {luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12),luaL_checkinteger(L, 13)};
  int selectStart = luaL_checkinteger(L, 14);
  int selectLength = luaL_checkinteger(L, 15);
  Color selectText = {luaL_checkinteger(L, 16),luaL_checkinteger(L, 17),luaL_checkinteger(L, 18),luaL_checkinteger(L, 19)};
  Color selectBack = {luaL_checkinteger(L, 20),luaL_checkinteger(L, 21),luaL_checkinteger(L, 22),luaL_checkinteger(L, 23)};
  DrawTextRecEx(font, text, rec, fontSize, spacing, wordWrap, tint, selectStart, selectLength, selectText, selectBack);
  return 0;
}

// Draw a Texture2D
static int l_raylib_DrawTexture(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  int posX = luaL_checkinteger(L, 2);
  int posY = luaL_checkinteger(L, 3);
  Color tint = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawTexture(texture, posX, posY, tint);
  return 0;
}

// Draw a Texture2D (unpacked version)
static int l_raylib_DrawTextureU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  int posX = luaL_checkinteger(L, 6);
  int posY = luaL_checkinteger(L, 7);
  Color tint = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawTexture(texture, posX, posY, tint);
  return 0;
}

// Draw a Texture2D with extended parameters
static int l_raylib_DrawTextureEx(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  float rotation = luaL_checknumber(L, 3);
  float scale = luaL_checknumber(L, 4);
  Color tint = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawTextureEx(texture, position, rotation, scale, tint);
  return 0;
}

// Draw a Texture2D with extended parameters (unpacked version)
static int l_raylib_DrawTextureExU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Vector2 position = {luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  float rotation = luaL_checknumber(L, 8);
  float scale = luaL_checknumber(L, 9);
  Color tint = {luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12),luaL_checkinteger(L, 13)};
  DrawTextureEx(texture, position, rotation, scale, tint);
  return 0;
}

// Draws a texture (or part of it) that stretches or shrinks nicely
static int l_raylib_DrawTextureNPatch(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  NPatchInfo nPatchInfo = (*(NPatchInfo*)luaL_checkudata(L, 2, "NPatchInfo"));
  Rectangle destRec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  Vector2 origin = (*(Vector2*)luaL_checkudata(L, 4, "Vector2"));
  float rotation = luaL_checknumber(L, 5);
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawTextureNPatch(texture, nPatchInfo, destRec, origin, rotation, tint);
  return 0;
}

// Draws a texture (or part of it) that stretches or shrinks nicely (unpacked version)
static int l_raylib_DrawTextureNPatchU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  NPatchInfo nPatchInfo = (*(NPatchInfo*)luaL_checkudata(L, 6, "NPatchInfo"));
  Rectangle destRec = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10)};
  Vector2 origin = {luaL_checknumber(L, 11),luaL_checknumber(L, 12)};
  float rotation = luaL_checknumber(L, 13);
  Color tint = {luaL_checkinteger(L, 14),luaL_checkinteger(L, 15),luaL_checkinteger(L, 16),luaL_checkinteger(L, 17)};
  DrawTextureNPatch(texture, nPatchInfo, destRec, origin, rotation, tint);
  return 0;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters
static int l_raylib_DrawTexturePro(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Rectangle sourceRec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  Rectangle destRec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  Vector2 origin = (*(Vector2*)luaL_checkudata(L, 4, "Vector2"));
  float rotation = luaL_checknumber(L, 5);
  Color tint = (*(Color*)luaL_checkudata(L, 6, "Color"));
  DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
  return 0;
}

// Draw a part of a texture defined by a rectangle with 'pro' parameters (unpacked version)
static int l_raylib_DrawTextureProU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Rectangle sourceRec = {luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  Rectangle destRec = {luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13)};
  Vector2 origin = {luaL_checknumber(L, 14),luaL_checknumber(L, 15)};
  float rotation = luaL_checknumber(L, 16);
  Color tint = {luaL_checkinteger(L, 17),luaL_checkinteger(L, 18),luaL_checkinteger(L, 19),luaL_checkinteger(L, 20)};
  DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
  return 0;
}

// Draw texture quad with tiling and offset parameters
static int l_raylib_DrawTextureQuad(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Vector2 tiling = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 offset = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  Rectangle quad = (*(Rectangle*)luaL_checkudata(L, 4, "Rectangle"));
  Color tint = (*(Color*)luaL_checkudata(L, 5, "Color"));
  DrawTextureQuad(texture, tiling, offset, quad, tint);
  return 0;
}

// Draw texture quad with tiling and offset parameters (unpacked version)
static int l_raylib_DrawTextureQuadU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Vector2 tiling = {luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  Vector2 offset = {luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  Rectangle quad = {luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13)};
  Color tint = {luaL_checkinteger(L, 14),luaL_checkinteger(L, 15),luaL_checkinteger(L, 16),luaL_checkinteger(L, 17)};
  DrawTextureQuad(texture, tiling, offset, quad, tint);
  return 0;
}

// Draw a part of a texture defined by a rectangle
static int l_raylib_DrawTextureRec(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Rectangle sourceRec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  Color tint = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawTextureRec(texture, sourceRec, position, tint);
  return 0;
}

// Draw a part of a texture defined by a rectangle (unpacked version)
static int l_raylib_DrawTextureRecU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Rectangle sourceRec = {luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  Vector2 position = {luaL_checknumber(L, 10),luaL_checknumber(L, 11)};
  Color tint = {luaL_checkinteger(L, 12),luaL_checkinteger(L, 13),luaL_checkinteger(L, 14),luaL_checkinteger(L, 15)};
  DrawTextureRec(texture, sourceRec, position, tint);
  return 0;
}

// Draw a Texture2D with position defined as Vector2
static int l_raylib_DrawTextureV(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Color tint = (*(Color*)luaL_checkudata(L, 3, "Color"));
  DrawTextureV(texture, position, tint);
  return 0;
}

// Draw a Texture2D with position defined as Vector2 (unpacked version)
static int l_raylib_DrawTextureVU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Vector2 position = {luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  Color tint = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  DrawTextureV(texture, position, tint);
  return 0;
}

// Draw a color-filled triangle
static int l_raylib_DrawTriangle(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 v3 = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawTriangle(v1, v2, v3, color);
  return 0;
}

// Draw a color-filled triangle (unpacked version)
static int l_raylib_DrawTriangleU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 v3 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawTriangle(v1, v2, v3, color);
  return 0;
}

// Draw a triangle fan defined by points
static int l_raylib_DrawTriangleFan(lua_State *L) {
  int len = lua_rawlen(L, 1);
  Color *color = luaL_checkudata(L, 2, "Color");
  if (len < 6) return 0;
  if (rlCheckBufferLimit((len/2 - 2)*4)) rlglDraw();
#if defined(SUPPORT_FONT_TEXTURE)
  Texture2D texShapes = GetFontDefault().texture;
  Rectangle rec = GetFontDefault().chars[95].rec;
  Rectangle recTexShapes = (Rectangle){ rec.x + 1, rec.y + 1, rec.width - 2, rec.height - 2 };
#else
  Texture2D texShapes = GetTextureDefault();
  Rectangle recTexShapes = (Rectangle){ 0.0f, 0.0f, 1.0f, 1.0f };
#endif
  rlEnableTexture(texShapes.id);
  rlBegin(RL_QUADS);
  {
    float x0, y0, x1, y1, x2, y2;
    rlColor4ub(color->r, color->g, color->b, color->a);
    lua_rawgeti(L, 1, 1); x0 = luaL_checknumber(L, -1);
    lua_rawgeti(L, 1, 2); y0 = luaL_checknumber(L, -1);
    lua_rawgeti(L, 1, 3); x1 = luaL_checknumber(L, -1);
    lua_rawgeti(L, 1, 4); y1 = luaL_checknumber(L, -1);
    for (int i = 5; i <= len; i += 2)
    {
      lua_rawgeti(L, 1, i); x2 = luaL_checknumber(L, -1);
      lua_rawgeti(L, 1, i+1); y2 = luaL_checknumber(L, -1);
      rlTexCoord2f(recTexShapes.x/texShapes.width, recTexShapes.y/texShapes.height);
      rlVertex2f(x0, y0);

      rlTexCoord2f(recTexShapes.x/texShapes.width, (recTexShapes.y + recTexShapes.height)/texShapes.height);
      rlVertex2f(x1, y1);

      rlTexCoord2f((recTexShapes.x + recTexShapes.width)/texShapes.width, (recTexShapes.y + recTexShapes.height)/texShapes.height);
      rlVertex2f(x2, y2);

      rlTexCoord2f((recTexShapes.x + recTexShapes.width)/texShapes.width, recTexShapes.y/texShapes.height);
      rlVertex2f(x2, y2);
      x1 = x2; y1 = y2;
    }
    rlEnd();
    rlDisableTexture();
  }
  return 0;
}

// Draw triangle outline
static int l_raylib_DrawTriangleLines(lua_State *L) {
  Vector2 v1 = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Vector2 v2 = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Vector2 v3 = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  DrawTriangleLines(v1, v2, v3, color);
  return 0;
}

// Draw triangle outline (unpacked version)
static int l_raylib_DrawTriangleLinesU(lua_State *L) {
  Vector2 v1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Vector2 v2 = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector2 v3 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  DrawTriangleLines(v1, v2, v3, color);
  return 0;
}

// Enables cursor (unlock cursor)
static int l_raylib_EnableCursor(lua_State *L) {
  (void)L; // Suppress unused warning
  EnableCursor();
  return 0;
}

// End blending mode (reset to default: alpha blending)
static int l_raylib_EndBlendMode(lua_State *L) {
  (void)L; // Suppress unused warning
  EndBlendMode();
  return 0;
}

// End canvas drawing and swap buffers (double buffering)
static int l_raylib_EndDrawing(lua_State *L) {
  (void)L; // Suppress unused warning
  EndDrawing();
  return 0;
}

// Ends 2D mode with custom camera
static int l_raylib_EndMode2D(lua_State *L) {
  (void)L; // Suppress unused warning
  EndMode2D();
  return 0;
}

// Ends 3D mode and returns to default 2D orthographic mode
static int l_raylib_EndMode3D(lua_State *L) {
  (void)L; // Suppress unused warning
  EndMode3D();
  return 0;
}

// End scissor mode
static int l_raylib_EndScissorMode(lua_State *L) {
  (void)L; // Suppress unused warning
  EndScissorMode();
  return 0;
}

// End custom shader drawing (use default shader)
static int l_raylib_EndShaderMode(lua_State *L) {
  (void)L; // Suppress unused warning
  EndShaderMode();
  return 0;
}

// Ends drawing to render texture
static int l_raylib_EndTextureMode(lua_State *L) {
  (void)L; // Suppress unused warning
  EndTextureMode();
  return 0;
}

// End VR simulator stereo rendering
static int l_raylib_EndVrDrawing(lua_State *L) {
  (void)L; // Suppress unused warning
  EndVrDrawing();
  return 0;
}

// Export image data to file
static int l_raylib_ExportImage(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  const char* fileName = luaL_checkstring(L, 2);
  ExportImage(image, fileName);
  return 0;
}

// Export image as code file defining an array of bytes
static int l_raylib_ExportImageAsCode(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  const char* fileName = luaL_checkstring(L, 2);
  ExportImageAsCode(image, fileName);
  return 0;
}

// Export mesh data to file
static int l_raylib_ExportMesh(lua_State *L) {
  Mesh mesh = (*(Mesh*)luaL_checkudata(L, 1, "Mesh"));
  const char* fileName = luaL_checkstring(L, 2);
  ExportMesh(mesh, fileName);
  return 0;
}

// Export wave data to file
static int l_raylib_ExportWave(lua_State *L) {
  Wave wave = (*(Wave*)luaL_checkudata(L, 1, "Wave"));
  const char* fileName = luaL_checkstring(L, 2);
  ExportWave(wave, fileName);
  return 0;
}

// Export wave sample data to code (.h)
static int l_raylib_ExportWaveAsCode(lua_State *L) {
  Wave wave = (*(Wave*)luaL_checkudata(L, 1, "Wave"));
  const char* fileName = luaL_checkstring(L, 2);
  ExportWaveAsCode(wave, fileName);
  return 0;
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
static int l_raylib_Fade(lua_State *L) {
  Color color = (*(Color*)luaL_checkudata(L, 1, "Color"));
  float alpha = luaL_checknumber(L, 2);
  Color result = Fade(color, alpha);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f (unpacked version)
static int l_raylib_FadeU(lua_State *L) {
  Color color = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  float alpha = luaL_checknumber(L, 5);
  Color result = Fade(color, alpha);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

// Check if file exists
static int l_raylib_FileExists(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  bool result = FileExists(fileName);
  lua_pushboolean(L, result);
  return 1;
}

// Generate image: cellular algorithm. Bigger tileSize means bigger cells
static int l_raylib_GenImageCellular(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  int tileSize = luaL_checkinteger(L, 3);
  Image result = GenImageCellular(width, height, tileSize);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: checked
static int l_raylib_GenImageChecked(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  int checksX = luaL_checkinteger(L, 3);
  int checksY = luaL_checkinteger(L, 4);
  Color col1 = (*(Color*)luaL_checkudata(L, 5, "Color"));
  Color col2 = (*(Color*)luaL_checkudata(L, 6, "Color"));
  Image result = GenImageChecked(width, height, checksX, checksY, col1, col2);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: checked (unpacked version)
static int l_raylib_GenImageCheckedU(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  int checksX = luaL_checkinteger(L, 3);
  int checksY = luaL_checkinteger(L, 4);
  Color col1 = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color col2 = {luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11),luaL_checkinteger(L, 12)};
  Image result = GenImageChecked(width, height, checksX, checksY, col1, col2);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: plain color
static int l_raylib_GenImageColor(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  Image result = GenImageColor(width, height, color);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: plain color (unpacked version)
static int l_raylib_GenImageColorU(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color color = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Image result = GenImageColor(width, height, color);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image font atlas using chars info
static int l_raylib_GenImageFontAtlas(lua_State *L) {
  CharInfo* chars = (CharInfo*)luaL_checkudata(L, 1, "CharInfo");
  int charsCount = luaL_checkinteger(L, 2);
  int fontSize = luaL_checkinteger(L, 3);
  int padding = luaL_checkinteger(L, 4);
  int packMethod = luaL_checkinteger(L, 5);
  Image result = GenImageFontAtlas(chars, charsCount, fontSize, padding, packMethod);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: horizontal gradient
static int l_raylib_GenImageGradientH(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color left = (*(Color*)luaL_checkudata(L, 3, "Color"));
  Color right = (*(Color*)luaL_checkudata(L, 4, "Color"));
  Image result = GenImageGradientH(width, height, left, right);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: horizontal gradient (unpacked version)
static int l_raylib_GenImageGradientHU(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color left = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Color right = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  Image result = GenImageGradientH(width, height, left, right);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: radial gradient
static int l_raylib_GenImageGradientRadial(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  float density = luaL_checknumber(L, 3);
  Color inner = (*(Color*)luaL_checkudata(L, 4, "Color"));
  Color outer = (*(Color*)luaL_checkudata(L, 5, "Color"));
  Image result = GenImageGradientRadial(width, height, density, inner, outer);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: radial gradient (unpacked version)
static int l_raylib_GenImageGradientRadialU(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  float density = luaL_checknumber(L, 3);
  Color inner = {luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  Color outer = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  Image result = GenImageGradientRadial(width, height, density, inner, outer);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: vertical gradient
static int l_raylib_GenImageGradientV(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color top = (*(Color*)luaL_checkudata(L, 3, "Color"));
  Color bottom = (*(Color*)luaL_checkudata(L, 4, "Color"));
  Image result = GenImageGradientV(width, height, top, bottom);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: vertical gradient (unpacked version)
static int l_raylib_GenImageGradientVU(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  Color top = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Color bottom = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  Image result = GenImageGradientV(width, height, top, bottom);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: perlin noise
static int l_raylib_GenImagePerlinNoise(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  int offsetX = luaL_checkinteger(L, 3);
  int offsetY = luaL_checkinteger(L, 4);
  float scale = luaL_checknumber(L, 5);
  Image result = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate image: white noise
static int l_raylib_GenImageWhiteNoise(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  float factor = luaL_checknumber(L, 3);
  Image result = GenImageWhiteNoise(width, height, factor);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Generate cuboid mesh
static int l_raylib_GenMeshCube(lua_State *L) {
  float width = luaL_checknumber(L, 1);
  float height = luaL_checknumber(L, 2);
  float length = luaL_checknumber(L, 3);
  Mesh result = GenMeshCube(width, height, length);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate cubes-based map mesh from image data
static int l_raylib_GenMeshCubicmap(lua_State *L) {
  Image cubicmap = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Vector3 cubeSize = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Mesh result = GenMeshCubicmap(cubicmap, cubeSize);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate cubes-based map mesh from image data (unpacked version)
static int l_raylib_GenMeshCubicmapU(lua_State *L) {
  Image cubicmap = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Vector3 cubeSize = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Mesh result = GenMeshCubicmap(cubicmap, cubeSize);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate cylinder mesh
static int l_raylib_GenMeshCylinder(lua_State *L) {
  float radius = luaL_checknumber(L, 1);
  float height = luaL_checknumber(L, 2);
  int slices = luaL_checkinteger(L, 3);
  Mesh result = GenMeshCylinder(radius, height, slices);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate heightmap mesh from image data
static int l_raylib_GenMeshHeightmap(lua_State *L) {
  Image heightmap = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Vector3 size = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Mesh result = GenMeshHeightmap(heightmap, size);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate heightmap mesh from image data (unpacked version)
static int l_raylib_GenMeshHeightmapU(lua_State *L) {
  Image heightmap = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Vector3 size = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Mesh result = GenMeshHeightmap(heightmap, size);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate half-sphere mesh (no bottom cap)
static int l_raylib_GenMeshHemiSphere(lua_State *L) {
  float radius = luaL_checknumber(L, 1);
  int rings = luaL_checkinteger(L, 2);
  int slices = luaL_checkinteger(L, 3);
  Mesh result = GenMeshHemiSphere(radius, rings, slices);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate trefoil knot mesh
static int l_raylib_GenMeshKnot(lua_State *L) {
  float radius = luaL_checknumber(L, 1);
  float size = luaL_checknumber(L, 2);
  int radSeg = luaL_checkinteger(L, 3);
  int sides = luaL_checkinteger(L, 4);
  Mesh result = GenMeshKnot(radius, size, radSeg, sides);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate plane mesh (with subdivisions)
static int l_raylib_GenMeshPlane(lua_State *L) {
  float width = luaL_checknumber(L, 1);
  float length = luaL_checknumber(L, 2);
  int resX = luaL_checkinteger(L, 3);
  int resZ = luaL_checkinteger(L, 4);
  Mesh result = GenMeshPlane(width, length, resX, resZ);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate polygonal mesh
static int l_raylib_GenMeshPoly(lua_State *L) {
  int sides = luaL_checkinteger(L, 1);
  float radius = luaL_checknumber(L, 2);
  Mesh result = GenMeshPoly(sides, radius);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate sphere mesh (standard sphere)
static int l_raylib_GenMeshSphere(lua_State *L) {
  float radius = luaL_checknumber(L, 1);
  int rings = luaL_checkinteger(L, 2);
  int slices = luaL_checkinteger(L, 3);
  Mesh result = GenMeshSphere(radius, rings, slices);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate torus mesh
static int l_raylib_GenMeshTorus(lua_State *L) {
  float radius = luaL_checknumber(L, 1);
  float size = luaL_checknumber(L, 2);
  int radSeg = luaL_checkinteger(L, 3);
  int sides = luaL_checkinteger(L, 4);
  Mesh result = GenMeshTorus(radius, size, radSeg, sides);
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

// Generate BRDF texture
static int l_raylib_GenTextureBRDF(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int size = luaL_checkinteger(L, 2);
  Texture2D result = GenTextureBRDF(shader, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Generate BRDF texture (unpacked version)
static int l_raylib_GenTextureBRDFU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int size = luaL_checkinteger(L, 2);
  Texture2D result = GenTextureBRDF(shader, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Generate cubemap texture from HDR texture
static int l_raylib_GenTextureCubemap(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D skyHDR = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  int size = luaL_checkinteger(L, 3);
  Texture2D result = GenTextureCubemap(shader, skyHDR, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Generate cubemap texture from HDR texture (unpacked version)
static int l_raylib_GenTextureCubemapU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D skyHDR = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  int size = luaL_checkinteger(L, 7);
  Texture2D result = GenTextureCubemap(shader, skyHDR, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Generate irradiance texture using cubemap data
static int l_raylib_GenTextureIrradiance(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D cubemap = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  int size = luaL_checkinteger(L, 3);
  Texture2D result = GenTextureIrradiance(shader, cubemap, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Generate irradiance texture using cubemap data (unpacked version)
static int l_raylib_GenTextureIrradianceU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D cubemap = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  int size = luaL_checkinteger(L, 7);
  Texture2D result = GenTextureIrradiance(shader, cubemap, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Generate GPU mipmaps for a texture
static int l_raylib_GenTextureMipmaps(lua_State *L) {
  Texture2D* texture = (Texture2D*)luaL_checkudata(L, 1, "Texture2D");
  GenTextureMipmaps(texture);
  return 0;
}

// Generate prefilter texture using cubemap data
static int l_raylib_GenTexturePrefilter(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D cubemap = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  int size = luaL_checkinteger(L, 3);
  Texture2D result = GenTexturePrefilter(shader, cubemap, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Generate prefilter texture using cubemap data (unpacked version)
static int l_raylib_GenTexturePrefilterU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  Texture2D cubemap = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  int size = luaL_checkinteger(L, 7);
  Texture2D result = GenTexturePrefilter(shader, cubemap, size);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Returns camera transform matrix (view matrix)
static int l_raylib_GetCameraMatrix(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Matrix result = GetCameraMatrix(camera);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

// Returns camera transform matrix (view matrix) (unpacked version)
static int l_raylib_GetCameraMatrixU(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  Matrix result = GetCameraMatrix(camera);
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

// Get clipboard text content
static int l_raylib_GetClipboardText(lua_State *L) {
  const char* result = GetClipboardText();
  lua_pushstring(L, result);
  return 1;
}

// Get collision info between ray and ground plane (Y-normal plane)
static int l_raylib_GetCollisionRayGround(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  float groundHeight = luaL_checknumber(L, 2);
  RayHitInfo result = GetCollisionRayGround(ray, groundHeight);
  RayHitInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "RayHitInfo");
  return 1;
}

// Get collision info between ray and model
static int l_raylib_GetCollisionRayModel(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Model* model = (Model*)luaL_checkudata(L, 2, "Model");
  RayHitInfo result = GetCollisionRayModel(ray, model);
  RayHitInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "RayHitInfo");
  return 1;
}

// Get collision info between ray and triangle
static int l_raylib_GetCollisionRayTriangle(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Vector3 p1 = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  Vector3 p2 = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  Vector3 p3 = (*(Vector3*)luaL_checkudata(L, 4, "Vector3"));
  RayHitInfo result = GetCollisionRayTriangle(ray, p1, p2, p3);
  RayHitInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "RayHitInfo");
  return 1;
}

// Get collision info between ray and triangle (unpacked version)
static int l_raylib_GetCollisionRayTriangleU(lua_State *L) {
  Ray ray = (*(Ray*)luaL_checkudata(L, 1, "Ray"));
  Vector3 p1 = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Vector3 p2 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7)};
  Vector3 p3 = {luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10)};
  RayHitInfo result = GetCollisionRayTriangle(ray, p1, p2, p3);
  RayHitInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "RayHitInfo");
  return 1;
}

// Get collision rectangle for two rectangles collision
static int l_raylib_GetCollisionRec(lua_State *L) {
  Rectangle rec1 = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Rectangle rec2 = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  Rectangle result = GetCollisionRec(rec1, rec2);
  Rectangle* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Rectangle");
  return 1;
}

// Get collision rectangle for two rectangles collision (unpacked version)
static int l_raylib_GetCollisionRecU(lua_State *L) {
  Rectangle rec1 = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  Rectangle rec2 = {luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8)};
  Rectangle result = GetCollisionRec(rec1, rec2);
  Rectangle* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Rectangle");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.width);lua_pushnumber(L, result.height);
  return 4;
}

// Returns a Color struct from hexadecimal value
static int l_raylib_GetColor(lua_State *L) {
  int hexValue = luaL_checkinteger(L, 1);
  Color result = GetColor(hexValue);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

// Returns a Color struct from hexadecimal value (unpacked version)
static int l_raylib_GetColorU(lua_State *L) {
  int hexValue = luaL_checkinteger(L, 1);
  Color result = GetColor(hexValue);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

// Get filenames in a directory path (memory should be freed)
static int l_raylib_GetDirectoryFiles(lua_State *L) {
  int count;
  char **files = GetDirectoryFiles(luaL_checkstring(L,1), &count);
  for (int i = 0; i < count-1; i++) lua_pushstring(L, files[i]);
  ClearDirectoryFiles();
  return count;
}

// Get full path for a given fileName (uses static string)
static int l_raylib_GetDirectoryPath(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  const char* result = GetDirectoryPath(fileName);
  lua_pushstring(L, result);
  return 1;
}

// Get dropped files names (memory should be freed)
static int l_raylib_GetDroppedFiles(lua_State *L) {
  int count;
  char **files = GetDroppedFiles(&count);
  for (int i = 0; i < count; i++) lua_pushstring(L, files[i]);
  ClearDroppedFiles();
  return count;
}

// Get pointer to extension for a filename string
static int l_raylib_GetExtension(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  const char* result = GetExtension(fileName);
  lua_pushstring(L, result);
  return 1;
}

// Returns current FPS
static int l_raylib_GetFPS(lua_State *L) {
  int result = GetFPS();
  lua_pushinteger(L, result);
  return 1;
}

// Get file modification time (last write time)
static int l_raylib_GetFileModTime(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  long result = GetFileModTime(fileName);
  lua_pushnumber(L, result);
  return 1;
}

// Get pointer to filename for a path string
static int l_raylib_GetFileName(lua_State *L) {
  const char* filePath = luaL_checkstring(L, 1);
  const char* result = GetFileName(filePath);
  lua_pushstring(L, result);
  return 1;
}

// Get filename string without extension (memory should be freed)
static int l_raylib_GetFileNameWithoutExt(lua_State *L) {
  const char* filePath = luaL_checkstring(L, 1);
  const char* result = GetFileNameWithoutExt(filePath);
  lua_pushstring(L, result);
  free((void*)result);
  return 1;
}

// Get the default Font
static int l_raylib_GetFontDefault(lua_State *L) {
  Font result = GetFontDefault();
  Font* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Font");
  return 1;
}

// Returns time in seconds for last frame drawn
static int l_raylib_GetFrameTime(lua_State *L) {
  float result = GetFrameTime();
  lua_pushnumber(L, result);
  return 1;
}

// Return gamepad axis count for a gamepad
static int l_raylib_GetGamepadAxisCount(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int result = GetGamepadAxisCount(gamepad);
  lua_pushinteger(L, result);
  return 1;
}

// Return axis movement value for a gamepad axis
static int l_raylib_GetGamepadAxisMovement(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int axis = luaL_checkinteger(L, 2);
  float result = GetGamepadAxisMovement(gamepad, axis);
  lua_pushnumber(L, result);
  return 1;
}

// Get the last gamepad button pressed
static int l_raylib_GetGamepadButtonPressed(lua_State *L) {
  int result = GetGamepadButtonPressed();
  lua_pushinteger(L, result);
  return 1;
}

// Return gamepad internal name id
static int l_raylib_GetGamepadName(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  const char* result = GetGamepadName(gamepad);
  lua_pushstring(L, result);
  return 1;
}

// Get latest detected gesture
static int l_raylib_GetGestureDetected(lua_State *L) {
  int result = GetGestureDetected();
  lua_pushinteger(L, result);
  return 1;
}

// Get gesture drag angle
static int l_raylib_GetGestureDragAngle(lua_State *L) {
  float result = GetGestureDragAngle();
  lua_pushnumber(L, result);
  return 1;
}

// Get gesture drag vector
static int l_raylib_GetGestureDragVector(lua_State *L) {
  Vector2 result = GetGestureDragVector();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Get gesture drag vector (unpacked version)
static int l_raylib_GetGestureDragVectorU(lua_State *L) {
  Vector2 result = GetGestureDragVector();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Get gesture hold time in milliseconds
static int l_raylib_GetGestureHoldDuration(lua_State *L) {
  float result = GetGestureHoldDuration();
  lua_pushnumber(L, result);
  return 1;
}

// Get gesture pinch angle
static int l_raylib_GetGesturePinchAngle(lua_State *L) {
  float result = GetGesturePinchAngle();
  lua_pushnumber(L, result);
  return 1;
}

// Get gesture pinch delta
static int l_raylib_GetGesturePinchVector(lua_State *L) {
  Vector2 result = GetGesturePinchVector();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Get gesture pinch delta (unpacked version)
static int l_raylib_GetGesturePinchVectorU(lua_State *L) {
  Vector2 result = GetGesturePinchVector();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Get index position for a unicode character on font
static int l_raylib_GetGlyphIndex(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  int character = luaL_checkinteger(L, 2);
  int result = GetGlyphIndex(font, character);
  lua_pushinteger(L, result);
  return 1;
}

// Get pixel data from image as a Color struct array
static int l_raylib_GetImageData(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Color* result = GetImageData(image);
  if (result == NULL) lua_pushnil(L); else { Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = *result; luaL_setmetatable(L, "Color");}
  return 1;
}

// Get pixel data from image as Vector4 array (float normalized)
static int l_raylib_GetImageDataNormalized(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Vector4* result = GetImageDataNormalized(image);
  if (result == NULL) lua_pushnil(L); else { Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = *result; luaL_setmetatable(L, "Vector4");}
  return 1;
}

// Get latest key pressed
static int l_raylib_GetKeyPressed(lua_State *L) {
  int result = GetKeyPressed();
  lua_pushinteger(L, result);
  return 1;
}

// Get internal modelview matrix
static int l_raylib_GetMatrixModelview(lua_State *L) {
  Matrix result = GetMatrixModelview();
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

// Get internal modelview matrix (unpacked version)
static int l_raylib_GetMatrixModelviewU(lua_State *L) {
  Matrix result = GetMatrixModelview();
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

// Get number of connected monitors
static int l_raylib_GetMonitorCount(lua_State *L) {
  int result = GetMonitorCount();
  lua_pushinteger(L, result);
  return 1;
}

// Get primary monitor height
static int l_raylib_GetMonitorHeight(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  int result = GetMonitorHeight(monitor);
  lua_pushinteger(L, result);
  return 1;
}

// Get the human-readable, UTF-8 encoded name of the primary monitor
static int l_raylib_GetMonitorName(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  const char* result = GetMonitorName(monitor);
  lua_pushstring(L, result);
  return 1;
}

// Get primary monitor physical height in millimetres
static int l_raylib_GetMonitorPhysicalHeight(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  int result = GetMonitorPhysicalHeight(monitor);
  lua_pushinteger(L, result);
  return 1;
}

// Get primary monitor physical width in millimetres
static int l_raylib_GetMonitorPhysicalWidth(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  int result = GetMonitorPhysicalWidth(monitor);
  lua_pushinteger(L, result);
  return 1;
}

// Get primary monitor width
static int l_raylib_GetMonitorWidth(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  int result = GetMonitorWidth(monitor);
  lua_pushinteger(L, result);
  return 1;
}

// Returns mouse position XY
static int l_raylib_GetMousePosition(lua_State *L) {
  Vector2 result = GetMousePosition();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Returns mouse position XY (unpacked version)
static int l_raylib_GetMousePositionU(lua_State *L) {
  Vector2 result = GetMousePosition();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Returns a ray trace from mouse position
static int l_raylib_GetMouseRay(lua_State *L) {
  Vector2 mousePosition = (*(Vector2*)luaL_checkudata(L, 1, "Vector2"));
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 2, "Camera3D"));
  Ray result = GetMouseRay(mousePosition, camera);
  Ray* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Ray");
  return 1;
}

// Returns a ray trace from mouse position (unpacked version)
static int l_raylib_GetMouseRayU(lua_State *L) {
  Vector2 mousePosition = {luaL_checknumber(L, 1),luaL_checknumber(L, 2)};
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 3, "Camera3D"));
  Ray result = GetMouseRay(mousePosition, camera);
  Ray* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Ray");
  return 1;
}

// Returns mouse wheel movement Y
static int l_raylib_GetMouseWheelMove(lua_State *L) {
  int result = GetMouseWheelMove();
  lua_pushinteger(L, result);
  return 1;
}

// Returns mouse position X
static int l_raylib_GetMouseX(lua_State *L) {
  int result = GetMouseX();
  lua_pushinteger(L, result);
  return 1;
}

// Returns mouse position Y
static int l_raylib_GetMouseY(lua_State *L) {
  int result = GetMouseY();
  lua_pushinteger(L, result);
  return 1;
}

// Get music time length (in seconds)
static int l_raylib_GetMusicTimeLength(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  float result = GetMusicTimeLength(music);
  lua_pushnumber(L, result);
  return 1;
}

// Get current music time played (in seconds)
static int l_raylib_GetMusicTimePlayed(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  float result = GetMusicTimePlayed(music);
  lua_pushnumber(L, result);
  return 1;
}

// Returns next codepoint in a UTF8 encoded string
static int l_raylib_GetNextCodepoint(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int count;
  int result = GetNextCodepoint(text, &count);
  lua_pushinteger(L, result);
  lua_pushinteger(L, count);
  return 2;
}

// Get pixel data size in bytes (image or texture)
static int l_raylib_GetPixelDataSize(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  int format = luaL_checkinteger(L, 3);
  int result = GetPixelDataSize(width, height, format);
  lua_pushinteger(L, result);
  return 1;
}

// Returns a random value between min and max (both included)
static int l_raylib_GetRandomValue(lua_State *L) {
  int min = luaL_checkinteger(L, 1);
  int max = luaL_checkinteger(L, 2);
  int result = GetRandomValue(min, max);
  lua_pushinteger(L, result);
  return 1;
}

// Get pixel data from screen buffer and return an Image (screenshot)
static int l_raylib_GetScreenData(lua_State *L) {
  Image result = GetScreenData();
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Get current screen height
static int l_raylib_GetScreenHeight(lua_State *L) {
  int result = GetScreenHeight();
  lua_pushinteger(L, result);
  return 1;
}

// Get current screen width
static int l_raylib_GetScreenWidth(lua_State *L) {
  int result = GetScreenWidth();
  lua_pushinteger(L, result);
  return 1;
}

// Get default shader
static int l_raylib_GetShaderDefault(lua_State *L) {
  Shader result = GetShaderDefault();
  Shader* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Shader");
  return 1;
}

// Get shader uniform location
static int l_raylib_GetShaderLocation(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  const char* uniformName = luaL_checkstring(L, 2);
  int result = GetShaderLocation(shader, uniformName);
  lua_pushinteger(L, result);
  return 1;
}

// Get pixel data from GPU texture and return an Image
static int l_raylib_GetTextureData(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Image result = GetTextureData(texture);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Get pixel data from GPU texture and return an Image (unpacked version)
static int l_raylib_GetTextureDataU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Image result = GetTextureData(texture);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Get default texture
static int l_raylib_GetTextureDefault(lua_State *L) {
  Texture2D result = GetTextureDefault();
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Get default texture (unpacked version)
static int l_raylib_GetTextureDefaultU(lua_State *L) {
  Texture2D result = GetTextureDefault();
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Returns elapsed time in seconds since InitWindow()
static int l_raylib_GetTime(lua_State *L) {
  double result = GetTime();
  lua_pushnumber(L, result);
  return 1;
}

// Get touch points count
static int l_raylib_GetTouchPointsCount(lua_State *L) {
  int result = GetTouchPointsCount();
  lua_pushinteger(L, result);
  return 1;
}

// Returns touch position XY for a touch point index (relative to screen size)
static int l_raylib_GetTouchPosition(lua_State *L) {
  int index = luaL_checkinteger(L, 1);
  Vector2 result = GetTouchPosition(index);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Returns touch position XY for a touch point index (relative to screen size) (unpacked version)
static int l_raylib_GetTouchPositionU(lua_State *L) {
  int index = luaL_checkinteger(L, 1);
  Vector2 result = GetTouchPosition(index);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Returns touch position X for touch point 0 (relative to screen size)
static int l_raylib_GetTouchX(lua_State *L) {
  int result = GetTouchX();
  lua_pushinteger(L, result);
  return 1;
}

// Returns touch position Y for touch point 0 (relative to screen size)
static int l_raylib_GetTouchY(lua_State *L) {
  int result = GetTouchY();
  lua_pushinteger(L, result);
  return 1;
}

// Get samples data from wave as a floats array
static int l_raylib_GetWaveData(lua_State *L) {
  return luaL_error(L, "GetWaveData is pass");
}

// Get native window handle
static int l_raylib_GetWindowHandle(lua_State *L) {
  void* result = GetWindowHandle();
  if (result == NULL) lua_pushnil(L); else lua_pushlightuserdata(L, result);
  return 1;
}

// Get current working directory (uses static string)
static int l_raylib_GetWorkingDirectory(lua_State *L) {
  const char* result = GetWorkingDirectory();
  lua_pushstring(L, result);
  return 1;
}

// Returns the screen space position for a 3d world space position
static int l_raylib_GetWorldToScreen(lua_State *L) {
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 1, "Vector3"));
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 2, "Camera3D"));
  Vector2 result = GetWorldToScreen(position, camera);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Returns the screen space position for a 3d world space position (unpacked version)
static int l_raylib_GetWorldToScreenU(lua_State *L) {
  Vector3 position = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 4, "Camera3D"));
  Vector2 result = GetWorldToScreen(position, camera);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Hides cursor
static int l_raylib_HideCursor(lua_State *L) {
  (void)L; // Suppress unused warning
  HideCursor();
  return 0;
}

// Hide the window
static int l_raylib_HideWindow(lua_State *L) {
  (void)L; // Suppress unused warning
  HideWindow();
  return 0;
}

// Clear alpha channel to desired color
static int l_raylib_ImageAlphaClear(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  float threshold = luaL_checknumber(L, 3);
  ImageAlphaClear(image, color, threshold);
  return 0;
}

// Clear alpha channel to desired color (unpacked version)
static int l_raylib_ImageAlphaClearU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  float threshold = luaL_checknumber(L, 6);
  ImageAlphaClear(image, color, threshold);
  return 0;
}

// Crop image depending on alpha value
static int l_raylib_ImageAlphaCrop(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  float threshold = luaL_checknumber(L, 2);
  ImageAlphaCrop(image, threshold);
  return 0;
}

// Apply alpha mask to image
static int l_raylib_ImageAlphaMask(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Image alphaMask = (*(Image*)luaL_checkudata(L, 2, "Image"));
  ImageAlphaMask(image, alphaMask);
  return 0;
}

// Premultiply alpha channel
static int l_raylib_ImageAlphaPremultiply(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageAlphaPremultiply(image);
  return 0;
}

// Modify image color: brightness (-255 to 255)
static int l_raylib_ImageColorBrightness(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int brightness = luaL_checkinteger(L, 2);
  ImageColorBrightness(image, brightness);
  return 0;
}

// Modify image color: contrast (-100 to 100)
static int l_raylib_ImageColorContrast(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  float contrast = luaL_checknumber(L, 2);
  ImageColorContrast(image, contrast);
  return 0;
}

// Modify image color: grayscale
static int l_raylib_ImageColorGrayscale(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageColorGrayscale(image);
  return 0;
}

// Modify image color: invert
static int l_raylib_ImageColorInvert(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageColorInvert(image);
  return 0;
}

// Modify image color: replace color
static int l_raylib_ImageColorReplace(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  Color replace = (*(Color*)luaL_checkudata(L, 3, "Color"));
  ImageColorReplace(image, color, replace);
  return 0;
}

// Modify image color: replace color (unpacked version)
static int l_raylib_ImageColorReplaceU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Color replace = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  ImageColorReplace(image, color, replace);
  return 0;
}

// Modify image color: tint
static int l_raylib_ImageColorTint(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  ImageColorTint(image, color);
  return 0;
}

// Modify image color: tint (unpacked version)
static int l_raylib_ImageColorTintU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color color = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  ImageColorTint(image, color);
  return 0;
}

// Create an image duplicate (useful for transformations)
static int l_raylib_ImageCopy(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Image result = ImageCopy(image);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Crop an image to a defined rectangle
static int l_raylib_ImageCrop(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle crop = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  ImageCrop(image, crop);
  return 0;
}

// Crop an image to a defined rectangle (unpacked version)
static int l_raylib_ImageCropU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle crop = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  ImageCrop(image, crop);
  return 0;
}

// Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
static int l_raylib_ImageDither(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int rBpp = luaL_checkinteger(L, 2);
  int gBpp = luaL_checkinteger(L, 3);
  int bBpp = luaL_checkinteger(L, 4);
  int aBpp = luaL_checkinteger(L, 5);
  ImageDither(image, rBpp, gBpp, bBpp, aBpp);
  return 0;
}

// Draw a source image within a destination image
static int l_raylib_ImageDraw(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Image src = (*(Image*)luaL_checkudata(L, 2, "Image"));
  Rectangle srcRec = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  Rectangle dstRec = (*(Rectangle*)luaL_checkudata(L, 4, "Rectangle"));
  ImageDraw(dst, src, srcRec, dstRec);
  return 0;
}

// Draw a source image within a destination image (unpacked version)
static int l_raylib_ImageDrawU(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Image src = (*(Image*)luaL_checkudata(L, 2, "Image"));
  Rectangle srcRec = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  Rectangle dstRec = {luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10)};
  ImageDraw(dst, src, srcRec, dstRec);
  return 0;
}

// Draw rectangle within an image
static int l_raylib_ImageDrawRectangle(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  ImageDrawRectangle(dst, rec, color);
  return 0;
}

// Draw rectangle within an image (unpacked version)
static int l_raylib_ImageDrawRectangleU(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle rec = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  ImageDrawRectangle(dst, rec, color);
  return 0;
}

// Draw rectangle lines within an image
static int l_raylib_ImageDrawRectangleLines(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  int thick = luaL_checkinteger(L, 3);
  Color color = (*(Color*)luaL_checkudata(L, 4, "Color"));
  ImageDrawRectangleLines(dst, rec, thick, color);
  return 0;
}

// Draw rectangle lines within an image (unpacked version)
static int l_raylib_ImageDrawRectangleLinesU(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Rectangle rec = {luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  int thick = luaL_checkinteger(L, 6);
  Color color = {luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10)};
  ImageDrawRectangleLines(dst, rec, thick, color);
  return 0;
}

// Draw text (default font) within an image (destination)
static int l_raylib_ImageDrawText(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  const char* text = luaL_checkstring(L, 3);
  int fontSize = luaL_checkinteger(L, 4);
  Color color = (*(Color*)luaL_checkudata(L, 5, "Color"));
  ImageDrawText(dst, position, text, fontSize, color);
  return 0;
}

// Draw text (default font) within an image (destination) (unpacked version)
static int l_raylib_ImageDrawTextU(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Vector2 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  const char* text = luaL_checkstring(L, 4);
  int fontSize = luaL_checkinteger(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  ImageDrawText(dst, position, text, fontSize, color);
  return 0;
}

// Draw text (custom sprite font) within an image (destination)
static int l_raylib_ImageDrawTextEx(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Vector2 position = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  Font font = (*(Font*)luaL_checkudata(L, 3, "Font"));
  const char* text = luaL_checkstring(L, 4);
  float fontSize = luaL_checknumber(L, 5);
  float spacing = luaL_checknumber(L, 6);
  Color color = (*(Color*)luaL_checkudata(L, 7, "Color"));
  ImageDrawTextEx(dst, position, font, text, fontSize, spacing, color);
  return 0;
}

// Draw text (custom sprite font) within an image (destination) (unpacked version)
static int l_raylib_ImageDrawTextExU(lua_State *L) {
  Image* dst = (Image*)luaL_checkudata(L, 1, "Image");
  Vector2 position = {luaL_checknumber(L, 2),luaL_checknumber(L, 3)};
  Font font = (*(Font*)luaL_checkudata(L, 4, "Font"));
  const char* text = luaL_checkstring(L, 5);
  float fontSize = luaL_checknumber(L, 6);
  float spacing = luaL_checknumber(L, 7);
  Color color = {luaL_checkinteger(L, 8),luaL_checkinteger(L, 9),luaL_checkinteger(L, 10),luaL_checkinteger(L, 11)};
  ImageDrawTextEx(dst, position, font, text, fontSize, spacing, color);
  return 0;
}

// Extract color palette from image to maximum size (memory should be freed)
static int l_raylib_ImageExtractPalette(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  int maxPaletteSize = luaL_checkinteger(L, 2);
  int extractCount;
  Color* result = ImageExtractPalette(image, maxPaletteSize, &extractCount);
  for (int i = 0; i < extractCount; i++)
  {
    Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = *result; luaL_setmetatable(L, "Color");
  }
  return extractCount;
}

// Flip image horizontally
static int l_raylib_ImageFlipHorizontal(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageFlipHorizontal(image);
  return 0;
}

// Flip image vertically
static int l_raylib_ImageFlipVertical(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageFlipVertical(image);
  return 0;
}

// Convert image data to desired format
static int l_raylib_ImageFormat(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int newFormat = luaL_checkinteger(L, 2);
  ImageFormat(image, newFormat);
  return 0;
}

// Generate all mipmap levels for a provided image
static int l_raylib_ImageMipmaps(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageMipmaps(image);
  return 0;
}

// Resize image (Bicubic scaling algorithm)
static int l_raylib_ImageResize(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int newWidth = luaL_checkinteger(L, 2);
  int newHeight = luaL_checkinteger(L, 3);
  ImageResize(image, newWidth, newHeight);
  return 0;
}

// Resize canvas and fill with color
static int l_raylib_ImageResizeCanvas(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int newWidth = luaL_checkinteger(L, 2);
  int newHeight = luaL_checkinteger(L, 3);
  int offsetX = luaL_checkinteger(L, 4);
  int offsetY = luaL_checkinteger(L, 5);
  Color color = (*(Color*)luaL_checkudata(L, 6, "Color"));
  ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, color);
  return 0;
}

// Resize canvas and fill with color (unpacked version)
static int l_raylib_ImageResizeCanvasU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int newWidth = luaL_checkinteger(L, 2);
  int newHeight = luaL_checkinteger(L, 3);
  int offsetX = luaL_checkinteger(L, 4);
  int offsetY = luaL_checkinteger(L, 5);
  Color color = {luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8),luaL_checkinteger(L, 9)};
  ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, color);
  return 0;
}

// Resize image (Nearest-Neighbor scaling algorithm)
static int l_raylib_ImageResizeNN(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  int newWidth = luaL_checkinteger(L, 2);
  int newHeight = luaL_checkinteger(L, 3);
  ImageResizeNN(image, newWidth, newHeight);
  return 0;
}

// Rotate image counter-clockwise 90deg
static int l_raylib_ImageRotateCCW(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageRotateCCW(image);
  return 0;
}

// Rotate image clockwise 90deg
static int l_raylib_ImageRotateCW(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  ImageRotateCW(image);
  return 0;
}

// Create an image from text (default font)
static int l_raylib_ImageText(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int fontSize = luaL_checkinteger(L, 2);
  Color color = (*(Color*)luaL_checkudata(L, 3, "Color"));
  Image result = ImageText(text, fontSize, color);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Create an image from text (default font) (unpacked version)
static int l_raylib_ImageTextU(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int fontSize = luaL_checkinteger(L, 2);
  Color color = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  Image result = ImageText(text, fontSize, color);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Create an image from text (custom sprite font)
static int l_raylib_ImageTextEx(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  float fontSize = luaL_checknumber(L, 3);
  float spacing = luaL_checknumber(L, 4);
  Color tint = (*(Color*)luaL_checkudata(L, 5, "Color"));
  Image result = ImageTextEx(font, text, fontSize, spacing, tint);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Create an image from text (custom sprite font) (unpacked version)
static int l_raylib_ImageTextExU(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  float fontSize = luaL_checknumber(L, 3);
  float spacing = luaL_checknumber(L, 4);
  Color tint = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Image result = ImageTextEx(font, text, fontSize, spacing, tint);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Convert image to POT (power-of-two)
static int l_raylib_ImageToPOT(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color fillColor = (*(Color*)luaL_checkudata(L, 2, "Color"));
  ImageToPOT(image, fillColor);
  return 0;
}

// Convert image to POT (power-of-two) (unpacked version)
static int l_raylib_ImageToPOTU(lua_State *L) {
  Image* image = (Image*)luaL_checkudata(L, 1, "Image");
  Color fillColor = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  ImageToPOT(image, fillColor);
  return 0;
}

// Initialize audio device and context
static int l_raylib_InitAudioDevice(lua_State *L) {
  (void)L; // Suppress unused warning
  InitAudioDevice();
  return 0;
}

// Init audio stream (to stream raw audio pcm data)
static int l_raylib_InitAudioStream(lua_State *L) {
  unsigned int sampleRate = luaL_checkinteger(L, 1);
  unsigned int sampleSize = luaL_checkinteger(L, 2);
  unsigned int channels = luaL_checkinteger(L, 3);
  AudioStream result = InitAudioStream(sampleRate, sampleSize, channels);
  AudioStream* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "AudioStream");
  return 1;
}

// Init VR simulator for selected device parameters
static int l_raylib_InitVrSimulator(lua_State *L) {
  (void)L; // Suppress unused warning
  InitVrSimulator();
  return 0;
}

// Initialize window and OpenGL context
static int l_raylib_InitWindow(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  const char* title = luaL_checkstring(L, 3);
  InitWindow(width, height, title);
  return 0;
}

// Check if any audio stream buffers requires refill
static int l_raylib_IsAudioBufferProcessed(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  bool result = IsAudioBufferProcessed(stream);
  lua_pushboolean(L, result);
  return 1;
}

// Check if audio device has been initialized successfully
static int l_raylib_IsAudioDeviceReady(lua_State *L) {
  bool result = IsAudioDeviceReady();
  lua_pushboolean(L, result);
  return 1;
}

// Check if audio stream is playing
static int l_raylib_IsAudioStreamPlaying(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  bool result = IsAudioStreamPlaying(stream);
  lua_pushboolean(L, result);
  return 1;
}

// Check if cursor is not visible
static int l_raylib_IsCursorHidden(lua_State *L) {
  bool result = IsCursorHidden();
  lua_pushboolean(L, result);
  return 1;
}

// Check if a file has been dropped into window
static int l_raylib_IsFileDropped(lua_State *L) {
  bool result = IsFileDropped();
  lua_pushboolean(L, result);
  return 1;
}

// Check file extension
static int l_raylib_IsFileExtension(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  const char* ext = luaL_checkstring(L, 2);
  bool result = IsFileExtension(fileName, ext);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a gamepad is available
static int l_raylib_IsGamepadAvailable(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  bool result = IsGamepadAvailable(gamepad);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a gamepad button is being pressed
static int l_raylib_IsGamepadButtonDown(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int button = luaL_checkinteger(L, 2);
  bool result = IsGamepadButtonDown(gamepad, button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a gamepad button has been pressed once
static int l_raylib_IsGamepadButtonPressed(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int button = luaL_checkinteger(L, 2);
  bool result = IsGamepadButtonPressed(gamepad, button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a gamepad button has been released once
static int l_raylib_IsGamepadButtonReleased(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int button = luaL_checkinteger(L, 2);
  bool result = IsGamepadButtonReleased(gamepad, button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a gamepad button is NOT being pressed
static int l_raylib_IsGamepadButtonUp(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  int button = luaL_checkinteger(L, 2);
  bool result = IsGamepadButtonUp(gamepad, button);
  lua_pushboolean(L, result);
  return 1;
}

// Check gamepad name (if available)
static int l_raylib_IsGamepadName(lua_State *L) {
  int gamepad = luaL_checkinteger(L, 1);
  const char* name = luaL_checkstring(L, 2);
  bool result = IsGamepadName(gamepad, name);
  lua_pushboolean(L, result);
  return 1;
}

// Check if a gesture have been detected
static int l_raylib_IsGestureDetected(lua_State *L) {
  int gesture = luaL_checkinteger(L, 1);
  bool result = IsGestureDetected(gesture);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a key is being pressed
static int l_raylib_IsKeyDown(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  bool result = IsKeyDown(key);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a key has been pressed once
static int l_raylib_IsKeyPressed(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  bool result = IsKeyPressed(key);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a key has been released once
static int l_raylib_IsKeyReleased(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  bool result = IsKeyReleased(key);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a key is NOT being pressed
static int l_raylib_IsKeyUp(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  bool result = IsKeyUp(key);
  lua_pushboolean(L, result);
  return 1;
}

// Check model animation skeleton match
static int l_raylib_IsModelAnimationValid(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  ModelAnimation anim = (*(ModelAnimation*)luaL_checkudata(L, 2, "ModelAnimation"));
  bool result = IsModelAnimationValid(model, anim);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a mouse button is being pressed
static int l_raylib_IsMouseButtonDown(lua_State *L) {
  int button = luaL_checkinteger(L, 1);
  bool result = IsMouseButtonDown(button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a mouse button has been pressed once
static int l_raylib_IsMouseButtonPressed(lua_State *L) {
  int button = luaL_checkinteger(L, 1);
  bool result = IsMouseButtonPressed(button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a mouse button has been released once
static int l_raylib_IsMouseButtonReleased(lua_State *L) {
  int button = luaL_checkinteger(L, 1);
  bool result = IsMouseButtonReleased(button);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if a mouse button is NOT being pressed
static int l_raylib_IsMouseButtonUp(lua_State *L) {
  int button = luaL_checkinteger(L, 1);
  bool result = IsMouseButtonUp(button);
  lua_pushboolean(L, result);
  return 1;
}

// Check if music is playing
static int l_raylib_IsMusicPlaying(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  bool result = IsMusicPlaying(music);
  lua_pushboolean(L, result);
  return 1;
}

// Check if a sound is currently playing
static int l_raylib_IsSoundPlaying(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  bool result = IsSoundPlaying(sound);
  lua_pushboolean(L, result);
  return 1;
}

// Detect if VR simulator is ready
static int l_raylib_IsVrSimulatorReady(lua_State *L) {
  bool result = IsVrSimulatorReady();
  lua_pushboolean(L, result);
  return 1;
}

// Check if window is currently hidden
static int l_raylib_IsWindowHidden(lua_State *L) {
  bool result = IsWindowHidden();
  lua_pushboolean(L, result);
  return 1;
}

// Check if window has been minimized (or lost focus)
static int l_raylib_IsWindowMinimized(lua_State *L) {
  bool result = IsWindowMinimized();
  lua_pushboolean(L, result);
  return 1;
}

// Check if window has been initialized successfully
static int l_raylib_IsWindowReady(lua_State *L) {
  bool result = IsWindowReady();
  lua_pushboolean(L, result);
  return 1;
}

// Check if window has been resized
static int l_raylib_IsWindowResized(lua_State *L) {
  bool result = IsWindowResized();
  lua_pushboolean(L, result);
  return 1;
}

// Load font from file into GPU memory (VRAM)
static int l_raylib_LoadFont(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Font result = LoadFont(fileName);
  Font* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Font");
  return 1;
}

// Load font data for further use
static int l_raylib_LoadFontData(lua_State *L) {
  return luaL_error(L, "LoadFontData is pass");
}

// Load font from file with extended parameters
static int l_raylib_LoadFontEx(lua_State *L) {
  return luaL_error(L, "LoadFontEx is pass");
}

// Load font from Image (XNA style)
static int l_raylib_LoadFontFromImage(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Color key = (*(Color*)luaL_checkudata(L, 2, "Color"));
  int firstChar = luaL_checkinteger(L, 3);
  Font result = LoadFontFromImage(image, key, firstChar);
  Font* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Font");
  return 1;
}

// Load font from Image (XNA style) (unpacked version)
static int l_raylib_LoadFontFromImageU(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Color key = {luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  int firstChar = luaL_checkinteger(L, 6);
  Font result = LoadFontFromImage(image, key, firstChar);
  Font* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Font");
  return 1;
}

// Load image from file into CPU memory (RAM)
static int l_raylib_LoadImage(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Image result = LoadImage(fileName);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Load image from Color array data (RGBA - 32bit)
static int l_raylib_LoadImageEx(lua_State *L) {
  Color* pixels = (Color*)luaL_checkudata(L, 1, "Color");
  int width = luaL_checkinteger(L, 2);
  int height = luaL_checkinteger(L, 3);
  Image result = LoadImageEx(pixels, width, height);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Load image from raw data with parameters
static int l_raylib_LoadImagePro(lua_State *L) {
  void* data = luaX_checklightuserdata(L, 1, "?");
  int width = luaL_checkinteger(L, 2);
  int height = luaL_checkinteger(L, 3);
  int format = luaL_checkinteger(L, 4);
  Image result = LoadImagePro(data, width, height, format);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Load image from RAW file data
static int l_raylib_LoadImageRaw(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  int width = luaL_checkinteger(L, 2);
  int height = luaL_checkinteger(L, 3);
  int format = luaL_checkinteger(L, 4);
  int headerSize = luaL_checkinteger(L, 5);
  Image result = LoadImageRaw(fileName, width, height, format, headerSize);
  Image* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Image");
  return 1;
}

// Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
static int l_raylib_LoadMaterialDefault(lua_State *L) {
  Material result = LoadMaterialDefault();
  Material* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Material");
  return 1;
}

// Load materials from model file
static int l_raylib_LoadMaterials(lua_State *L) {
  int count;
  Material *materials = LoadMaterials(luaL_checkstring(L,1), &count);
	for (int i = 0; i < count; i++) {
    Material *material = lua_newuserdata(L, sizeof *material);
    *material = materials[i];
    luaL_setmetatable(L, "Material");
  }
  return count;
}

// Load meshes from model file
static int l_raylib_LoadMeshes(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  int meshCount;
  Mesh* result = LoadMeshes(fileName, &meshCount);
  for (int i = 0; i < meshCount; i++)
  {
    Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result[i]; luaL_setmetatable(L, "Mesh");
  }
  return meshCount;
}

// Load model from files (meshes and materials)
static int l_raylib_LoadModel(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Model result = LoadModel(fileName);
  Model* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Model");
  return 1;
}

// Load model animations from file
static int l_raylib_LoadModelAnimations(lua_State *L) {
  int count = 0;
  ModelAnimation *animations = LoadModelAnimations(luaL_checkstring(L, 1), &count);
  for (int i = 0; i < count; i++) {
    ModelAnimation *anim = lua_newuserdata(L, sizeof *anim); *anim = animations[i]; luaL_setmetatable(L, "ModelAnimation");
  }
  return count;
}

// Load model from generated mesh (default material)
static int l_raylib_LoadModelFromMesh(lua_State *L) {
  Mesh mesh = (*(Mesh*)luaL_checkudata(L, 1, "Mesh"));
  Model result = LoadModelFromMesh(mesh);
  Model* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Model");
  return 1;
}

// Load music stream from file
static int l_raylib_LoadMusicStream(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Music result = LoadMusicStream(fileName);
  if (result == NULL) lua_pushnil(L); else { OpaqueMusic *userdata = lua_newuserdata(L, sizeof *userdata); userdata->data = result; luaL_setmetatable(L, "Music");}
  return 1;
}

// Load texture for rendering (framebuffer)
static int l_raylib_LoadRenderTexture(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  RenderTexture2D result = LoadRenderTexture(width, height);
  RenderTexture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "RenderTexture2D");
  return 1;
}

// Load shader from files and bind default locations
static int l_raylib_LoadShader(lua_State *L) {
  const char* vsFileName = luaL_checkstring(L, 1);
  const char* fsFileName = luaL_checkstring(L, 2);
  Shader result = LoadShader(vsFileName, fsFileName);
  Shader* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Shader");
  return 1;
}

// Load shader from code strings and bind default locations
static int l_raylib_LoadShaderCode(lua_State *L) {
  char* vsCode = (char*)luaL_checkstring(L, 1);
  char* fsCode = (char*)luaL_checkstring(L, 2);
  Shader result = LoadShaderCode(vsCode, fsCode);
  Shader* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Shader");
  return 1;
}

// Load sound from file
static int l_raylib_LoadSound(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Sound result = LoadSound(fileName);
  Sound* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Sound");
  return 1;
}

// Load sound from wave data
static int l_raylib_LoadSoundFromWave(lua_State *L) {
  Wave wave = (*(Wave*)luaL_checkudata(L, 1, "Wave"));
  Sound result = LoadSoundFromWave(wave);
  Sound* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Sound");
  return 1;
}

// Load chars array from text file
static int l_raylib_LoadText(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  char* result = LoadText(fileName);
  lua_pushstring(L, result);
  return 1;
}

// Load texture from file into GPU memory (VRAM)
static int l_raylib_LoadTexture(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Texture2D result = LoadTexture(fileName);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Load texture from file into GPU memory (VRAM) (unpacked version)
static int l_raylib_LoadTextureU(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Texture2D result = LoadTexture(fileName);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Load cubemap from image, multiple image cubemap layouts supported
static int l_raylib_LoadTextureCubemap(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  int layoutType = luaL_checkinteger(L, 2);
  Texture2D result = LoadTextureCubemap(image, layoutType);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Load cubemap from image, multiple image cubemap layouts supported (unpacked version)
static int l_raylib_LoadTextureCubemapU(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  int layoutType = luaL_checkinteger(L, 2);
  Texture2D result = LoadTextureCubemap(image, layoutType);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Load texture from image data
static int l_raylib_LoadTextureFromImage(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Texture2D result = LoadTextureFromImage(image);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

// Load texture from image data (unpacked version)
static int l_raylib_LoadTextureFromImageU(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  Texture2D result = LoadTextureFromImage(image);
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

// Load wave data from file
static int l_raylib_LoadWave(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  Wave result = LoadWave(fileName);
  Wave* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Wave");
  return 1;
}

// Load wave data from raw array data
static int l_raylib_LoadWaveEx(lua_State *L) {
  void* data = luaX_checklightuserdata(L, 1, "?");
  int sampleCount = luaL_checkinteger(L, 2);
  int sampleRate = luaL_checkinteger(L, 3);
  int sampleSize = luaL_checkinteger(L, 4);
  int channels = luaL_checkinteger(L, 5);
  Wave result = LoadWaveEx(data, sampleCount, sampleRate, sampleSize, channels);
  Wave* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Wave");
  return 1;
}

// Measure string width for default font
static int l_raylib_MeasureText(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int fontSize = luaL_checkinteger(L, 2);
  int result = MeasureText(text, fontSize);
  lua_pushinteger(L, result);
  return 1;
}

// Measure string size for Font
static int l_raylib_MeasureTextEx(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  float fontSize = luaL_checknumber(L, 3);
  float spacing = luaL_checknumber(L, 4);
  Vector2 result = MeasureTextEx(font, text, fontSize, spacing);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

// Measure string size for Font (unpacked version)
static int l_raylib_MeasureTextExU(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  const char* text = luaL_checkstring(L, 2);
  float fontSize = luaL_checknumber(L, 3);
  float spacing = luaL_checknumber(L, 4);
  Vector2 result = MeasureTextEx(font, text, fontSize, spacing);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

// Compute mesh binormals
static int l_raylib_MeshBinormals(lua_State *L) {
  Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
  MeshBinormals(mesh);
  return 0;
}

// Compute mesh bounding box limits
static int l_raylib_MeshBoundingBox(lua_State *L) {
  Mesh mesh = (*(Mesh*)luaL_checkudata(L, 1, "Mesh"));
  BoundingBox result = MeshBoundingBox(mesh);
  BoundingBox* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "BoundingBox");
  return 1;
}

// Compute mesh tangents
static int l_raylib_MeshTangents(lua_State *L) {
  Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
  MeshTangents(mesh);
  return 0;
}

// Open URL with default system browser (if available)
static int l_raylib_OpenURL(lua_State *L) {
  const char* url = luaL_checkstring(L, 1);
  OpenURL(url);
  return 0;
}

// Pause audio stream
static int l_raylib_PauseAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  PauseAudioStream(stream);
  return 0;
}

// Pause music playing
static int l_raylib_PauseMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  PauseMusicStream(music);
  return 0;
}

// Pause a sound
static int l_raylib_PauseSound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  PauseSound(sound);
  return 0;
}

// Play audio stream
static int l_raylib_PlayAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  PlayAudioStream(stream);
  return 0;
}

// Start music playing
static int l_raylib_PlayMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  PlayMusicStream(music);
  return 0;
}

// Play a sound
static int l_raylib_PlaySound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  PlaySound(sound);
  return 0;
}

// Resume audio stream
static int l_raylib_ResumeAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  ResumeAudioStream(stream);
  return 0;
}

// Resume playing paused music
static int l_raylib_ResumeMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  ResumeMusicStream(music);
  return 0;
}

// Resume a paused sound
static int l_raylib_ResumeSound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  ResumeSound(sound);
  return 0;
}

// Set pitch for audio stream (1.0 is base level)
static int l_raylib_SetAudioStreamPitch(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  float pitch = luaL_checknumber(L, 2);
  SetAudioStreamPitch(stream, pitch);
  return 0;
}

// Set volume for audio stream (1.0 is max level)
static int l_raylib_SetAudioStreamVolume(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  float volume = luaL_checknumber(L, 2);
  SetAudioStreamVolume(stream, volume);
  return 0;
}

// Set camera alt key to combine with mouse movement (free camera)
static int l_raylib_SetCameraAltControl(lua_State *L) {
  int altKey = luaL_checkinteger(L, 1);
  SetCameraAltControl(altKey);
  return 0;
}

// Set camera mode (multiple camera modes available)
static int l_raylib_SetCameraMode(lua_State *L) {
  Camera3D camera = (*(Camera3D*)luaL_checkudata(L, 1, "Camera3D"));
  int mode = luaL_checkinteger(L, 2);
  SetCameraMode(camera, mode);
  return 0;
}

// Set camera move controls (1st person and 3rd person cameras)
static int l_raylib_SetCameraMoveControls(lua_State *L) {
  int frontKey = luaL_checkinteger(L, 1);
  int backKey = luaL_checkinteger(L, 2);
  int rightKey = luaL_checkinteger(L, 3);
  int leftKey = luaL_checkinteger(L, 4);
  int upKey = luaL_checkinteger(L, 5);
  int downKey = luaL_checkinteger(L, 6);
  SetCameraMoveControls(frontKey, backKey, rightKey, leftKey, upKey, downKey);
  return 0;
}

// Set camera pan key to combine with mouse movement (free camera)
static int l_raylib_SetCameraPanControl(lua_State *L) {
  int panKey = luaL_checkinteger(L, 1);
  SetCameraPanControl(panKey);
  return 0;
}

// Set camera smooth zoom key to combine with mouse (free camera)
static int l_raylib_SetCameraSmoothZoomControl(lua_State *L) {
  int szKey = luaL_checkinteger(L, 1);
  SetCameraSmoothZoomControl(szKey);
  return 0;
}

// Set clipboard text content
static int l_raylib_SetClipboardText(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  SetClipboardText(text);
  return 0;
}

// Setup window configuration flags (view FLAGS)
static int l_raylib_SetConfigFlags(lua_State *L) {
  unsigned int flags = luaL_checkinteger(L, 1);
  SetConfigFlags(flags);
  return 0;
}

// Set a custom key to exit program (default is ESC)
static int l_raylib_SetExitKey(lua_State *L) {
  int key = luaL_checkinteger(L, 1);
  SetExitKey(key);
  return 0;
}

// Enable a set of gestures using flags
static int l_raylib_SetGesturesEnabled(lua_State *L) {
  unsigned int gestureFlags = luaL_checkinteger(L, 1);
  SetGesturesEnabled(gestureFlags);
  return 0;
}

// Set master volume (listener)
static int l_raylib_SetMasterVolume(lua_State *L) {
  float volume = luaL_checknumber(L, 1);
  SetMasterVolume(volume);
  return 0;
}

// Set texture for a material map type (MAP_DIFFUSE, MAP_SPECULAR...)
static int l_raylib_SetMaterialTexture(lua_State *L) {
  Material* material = (Material*)luaL_checkudata(L, 1, "Material");
  int mapType = luaL_checkinteger(L, 2);
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 3, "Texture2D"));
  SetMaterialTexture(material, mapType, texture);
  return 0;
}

// Set texture for a material map type (MAP_DIFFUSE, MAP_SPECULAR...) (unpacked version)
static int l_raylib_SetMaterialTextureU(lua_State *L) {
  Material* material = (Material*)luaL_checkudata(L, 1, "Material");
  int mapType = luaL_checkinteger(L, 2);
  Texture2D texture = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  SetMaterialTexture(material, mapType, texture);
  return 0;
}

// Set a custom modelview matrix (replaces internal modelview matrix)
static int l_raylib_SetMatrixModelview(lua_State *L) {
  Matrix view = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  SetMatrixModelview(view);
  return 0;
}

// Set a custom modelview matrix (replaces internal modelview matrix) (unpacked version)
static int l_raylib_SetMatrixModelviewU(lua_State *L) {
  Matrix view = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  SetMatrixModelview(view);
  return 0;
}

// Set a custom projection matrix (replaces internal projection matrix)
static int l_raylib_SetMatrixProjection(lua_State *L) {
  Matrix proj = (*(Matrix*)luaL_checkudata(L, 1, "Matrix"));
  SetMatrixProjection(proj);
  return 0;
}

// Set a custom projection matrix (replaces internal projection matrix) (unpacked version)
static int l_raylib_SetMatrixProjectionU(lua_State *L) {
  Matrix proj = {luaL_checknumber(L, 1),luaL_checknumber(L, 2),luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16)};
  SetMatrixProjection(proj);
  return 0;
}

// Set material for a mesh
static int l_raylib_SetModelMeshMaterial(lua_State *L) {
  Model* model = (Model*)luaL_checkudata(L, 1, "Model");
  int meshId = luaL_checkinteger(L, 2);
  int materialId = luaL_checkinteger(L, 3);
  SetModelMeshMaterial(model, meshId, materialId);
  return 0;
}

// Set mouse offset
static int l_raylib_SetMouseOffset(lua_State *L) {
  int offsetX = luaL_checkinteger(L, 1);
  int offsetY = luaL_checkinteger(L, 2);
  SetMouseOffset(offsetX, offsetY);
  return 0;
}

// Set mouse position XY
static int l_raylib_SetMousePosition(lua_State *L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  SetMousePosition(x, y);
  return 0;
}

// Set mouse scaling
static int l_raylib_SetMouseScale(lua_State *L) {
  float scaleX = luaL_checknumber(L, 1);
  float scaleY = luaL_checknumber(L, 2);
  SetMouseScale(scaleX, scaleY);
  return 0;
}

// Set music loop count (loop repeats)
static int l_raylib_SetMusicLoopCount(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  int count = luaL_checkinteger(L, 2);
  SetMusicLoopCount(music, count);
  return 0;
}

// Set pitch for a music (1.0 is base level)
static int l_raylib_SetMusicPitch(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  float pitch = luaL_checknumber(L, 2);
  SetMusicPitch(music, pitch);
  return 0;
}

// Set volume for music (1.0 is max level)
static int l_raylib_SetMusicVolume(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  float volume = luaL_checknumber(L, 2);
  SetMusicVolume(music, volume);
  return 0;
}

// Set shader uniform value
static int l_raylib_SetShaderValue(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  const void* value = luaX_checklightuserdata(L, 3, "?");
  int uniformType = luaL_checkinteger(L, 4);
  SetShaderValue(shader, uniformLoc, value, uniformType);
  return 0;
}

static int l_raylib_SetShaderValueFloat(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  float value = luaL_checknumber(L, 3);
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_FLOAT);
  return 0;
}

static int l_raylib_SetShaderValueIVec2(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector2 value = (*(IVector2*)luaL_checkudata(L, 3, "IVector2"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC2);
  return 0;
}

static int l_raylib_SetShaderValueIVec2U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector2 value = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC2);
  return 0;
}

static int l_raylib_SetShaderValueIVec3(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector3 value = (*(IVector3*)luaL_checkudata(L, 3, "IVector3"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC3);
  return 0;
}

static int l_raylib_SetShaderValueIVec3U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector3 value = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC3);
  return 0;
}

static int l_raylib_SetShaderValueIVec4(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector4 value = (*(IVector4*)luaL_checkudata(L, 3, "IVector4"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC4);
  return 0;
}

static int l_raylib_SetShaderValueIVec4U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  IVector4 value = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_IVEC4);
  return 0;
}

static int l_raylib_SetShaderValueInt(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  int value = luaL_checkinteger(L, 3);
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_INT);
  return 0;
}

// Set shader uniform value (matrix 4x4)
static int l_raylib_SetShaderValueMatrix(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Matrix mat = (*(Matrix*)luaL_checkudata(L, 3, "Matrix"));
  SetShaderValueMatrix(shader, uniformLoc, mat);
  return 0;
}

// Set shader uniform value (matrix 4x4) (unpacked version)
static int l_raylib_SetShaderValueMatrixU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Matrix mat = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9),luaL_checknumber(L, 10),luaL_checknumber(L, 11),luaL_checknumber(L, 12),luaL_checknumber(L, 13),luaL_checknumber(L, 14),luaL_checknumber(L, 15),luaL_checknumber(L, 16),luaL_checknumber(L, 17),luaL_checknumber(L, 18)};
  SetShaderValueMatrix(shader, uniformLoc, mat);
  return 0;
}

static int l_raylib_SetShaderValueSampler2D(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  int value = luaL_checkinteger(L, 3);
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_SAMPLER2D);
  return 0;
}

// Set shader uniform value for texture
static int l_raylib_SetShaderValueTexture(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 3, "Texture2D"));
  SetShaderValueTexture(shader, uniformLoc, texture);
  return 0;
}

// Set shader uniform value for texture (unpacked version)
static int l_raylib_SetShaderValueTextureU(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Texture2D texture = {luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7)};
  SetShaderValueTexture(shader, uniformLoc, texture);
  return 0;
}

// Set shader uniform value vector
static int l_raylib_SetShaderValueV(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  const void* value = luaX_checklightuserdata(L, 3, "?");
  int uniformType = luaL_checkinteger(L, 4);
  int count = luaL_checkinteger(L, 5);
  SetShaderValueV(shader, uniformLoc, value, uniformType, count);
  return 0;
}

static int l_raylib_SetShaderValueVec2(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector2 value = (*(Vector2*)luaL_checkudata(L, 3, "Vector2"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC2);
  return 0;
}

static int l_raylib_SetShaderValueVec2U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector2 value = {luaL_checknumber(L, 3),luaL_checknumber(L, 4)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC2);
  return 0;
}

static int l_raylib_SetShaderValueVec3(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector3 value = (*(Vector3*)luaL_checkudata(L, 3, "Vector3"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC3);
  return 0;
}

static int l_raylib_SetShaderValueVec3U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector3 value = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC3);
  return 0;
}

static int l_raylib_SetShaderValueVec4(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector4 value = (*(Vector4*)luaL_checkudata(L, 3, "Vector4"));
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC4);
  return 0;
}

static int l_raylib_SetShaderValueVec4U(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  int uniformLoc = luaL_checkinteger(L, 2);
  Vector4 value = {luaL_checknumber(L, 3),luaL_checknumber(L, 4),luaL_checknumber(L, 5),luaL_checknumber(L, 6)};
  SetShaderValue(shader, uniformLoc, &value, UNIFORM_VEC4);
  return 0;
}

// Define default texture used to draw shapes
static int l_raylib_SetShapesTexture(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  Rectangle source = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  SetShapesTexture(texture, source);
  return 0;
}

// Define default texture used to draw shapes (unpacked version)
static int l_raylib_SetShapesTextureU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  Rectangle source = {luaL_checknumber(L, 6),luaL_checknumber(L, 7),luaL_checknumber(L, 8),luaL_checknumber(L, 9)};
  SetShapesTexture(texture, source);
  return 0;
}

// Set pitch for a sound (1.0 is base level)
static int l_raylib_SetSoundPitch(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  float pitch = luaL_checknumber(L, 2);
  SetSoundPitch(sound, pitch);
  return 0;
}

// Set volume for a sound (1.0 is max level)
static int l_raylib_SetSoundVolume(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  float volume = luaL_checknumber(L, 2);
  SetSoundVolume(sound, volume);
  return 0;
}

// Set target FPS (maximum)
static int l_raylib_SetTargetFPS(lua_State *L) {
  int fps = luaL_checkinteger(L, 1);
  SetTargetFPS(fps);
  return 0;
}

// Set texture scaling filter mode
static int l_raylib_SetTextureFilter(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  int filterMode = luaL_checkinteger(L, 2);
  SetTextureFilter(texture, filterMode);
  return 0;
}

// Set texture scaling filter mode (unpacked version)
static int l_raylib_SetTextureFilterU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  int filterMode = luaL_checkinteger(L, 6);
  SetTextureFilter(texture, filterMode);
  return 0;
}

// Set texture wrapping mode
static int l_raylib_SetTextureWrap(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  int wrapMode = luaL_checkinteger(L, 2);
  SetTextureWrap(texture, wrapMode);
  return 0;
}

// Set texture wrapping mode (unpacked version)
static int l_raylib_SetTextureWrapU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  int wrapMode = luaL_checkinteger(L, 6);
  SetTextureWrap(texture, wrapMode);
  return 0;
}

// Set a trace log callback to enable custom logging
static int l_raylib_SetTraceLogCallback(lua_State *L) {
  TraceLogCallback callback = (*(TraceLogCallback*)luaL_checkudata(L, 1, "TraceLogCallback"));
  SetTraceLogCallback(callback);
  return 0;
}

// Set the exit threshold (minimum) log level
static int l_raylib_SetTraceLogExit(lua_State *L) {
  int logType = luaL_checkinteger(L, 1);
  SetTraceLogExit(logType);
  return 0;
}

// Set the current threshold (minimum) log level
static int l_raylib_SetTraceLogLevel(lua_State *L) {
  int logType = luaL_checkinteger(L, 1);
  SetTraceLogLevel(logType);
  return 0;
}

// Set stereo rendering configuration parameters 
static int l_raylib_SetVrConfiguration(lua_State *L) {
  VrDeviceInfo info = (*(VrDeviceInfo*)luaL_checkudata(L, 1, "VrDeviceInfo"));
  Shader distortion = (*(Shader*)luaL_checkudata(L, 2, "Shader"));
  SetVrConfiguration(info, distortion);
  return 0;
}

// Set icon for window (only PLATFORM_DESKTOP)
static int l_raylib_SetWindowIcon(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  SetWindowIcon(image);
  return 0;
}

// Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
static int l_raylib_SetWindowMinSize(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  SetWindowMinSize(width, height);
  return 0;
}

// Set monitor for the current window (fullscreen mode)
static int l_raylib_SetWindowMonitor(lua_State *L) {
  int monitor = luaL_checkinteger(L, 1);
  SetWindowMonitor(monitor);
  return 0;
}

// Set window position on screen (only PLATFORM_DESKTOP)
static int l_raylib_SetWindowPosition(lua_State *L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);
  SetWindowPosition(x, y);
  return 0;
}

// Set window dimensions
static int l_raylib_SetWindowSize(lua_State *L) {
  int width = luaL_checkinteger(L, 1);
  int height = luaL_checkinteger(L, 2);
  SetWindowSize(width, height);
  return 0;
}

// Set title for window (only PLATFORM_DESKTOP)
static int l_raylib_SetWindowTitle(lua_State *L) {
  const char* title = luaL_checkstring(L, 1);
  SetWindowTitle(title);
  return 0;
}

// Shows cursor
static int l_raylib_ShowCursor(lua_State *L) {
  (void)L; // Suppress unused warning
  ShowCursor();
  return 0;
}

// Stop audio stream
static int l_raylib_StopAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  StopAudioStream(stream);
  return 0;
}

// Stop music playing
static int l_raylib_StopMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  StopMusicStream(music);
  return 0;
}

// Stop playing a sound
static int l_raylib_StopSound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  StopSound(sound);
  return 0;
}

// Load integer value from storage file (from defined position)
static int l_raylib_StorageLoadValue(lua_State *L) {
  int position = luaL_checkinteger(L, 1);
  int result = StorageLoadValue(position);
  lua_pushinteger(L, result);
  return 1;
}

// Save integer value to storage file (to defined position)
static int l_raylib_StorageSaveValue(lua_State *L) {
  int position = luaL_checkinteger(L, 1);
  int value = luaL_checkinteger(L, 2);
  StorageSaveValue(position, value);
  return 0;
}

// Takes a screenshot of current screen (saved a .png)
static int l_raylib_TakeScreenshot(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  TakeScreenshot(fileName);
  return 0;
}

// Append text at specific position and move cursor!
static int l_raylib_TextAppend(lua_State *L) {
  return luaL_error(L, "TextAppend is pass");
}

// Get total number of characters (codepoints) in a UTF8 encoded string
static int l_raylib_TextCountCodepoints(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  unsigned int result = TextCountCodepoints(text);
  lua_pushinteger(L, result);
  return 1;
}

// Find first text occurrence within a string
static int l_raylib_TextFindIndex(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* find = luaL_checkstring(L, 2);
  int result = TextFindIndex(text, find);
  lua_pushinteger(L, result);
  return 1;
}

// Text formatting with variables (sprintf style)
static int l_raylib_TextFormat(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* result = TextFormat(text);
  lua_pushstring(L, result);
  return 1;
}

// Insert text in a position (memory should be freed!)
static int l_raylib_TextInsert(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* insert = luaL_checkstring(L, 2);
  int position = luaL_checkinteger(L, 3);
  const char* result = TextInsert(text, insert, position);
  lua_pushstring(L, result);
  free((void*)result);
  return 1;
}

// Check if two text string are equal
static int l_raylib_TextIsEqual(lua_State *L) {
  const char* text1 = luaL_checkstring(L, 1);
  const char* text2 = luaL_checkstring(L, 2);
  bool result = TextIsEqual(text1, text2);
  lua_pushboolean(L, result);
  return 1;
}

// Join text strings with delimiter
static int l_raylib_TextJoin(lua_State *L) {
  return luaL_error(L, "TextJoin is pass");
}

// Get text length, checks for '\0' ending
static int l_raylib_TextLength(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  unsigned int result = TextLength(text);
  lua_pushinteger(L, result);
  return 1;
}

// Replace text string (memory should be freed!)
static int l_raylib_TextReplace(lua_State *L) {
  char* text = (char*)luaL_checkstring(L, 1);
  const char* replace = luaL_checkstring(L, 2);
  const char* by = luaL_checkstring(L, 3);
  const char* result = TextReplace(text, replace, by);
  lua_pushstring(L, result);
  free((void*)result);
  return 1;
}

// Split text into multiple strings
static int l_raylib_TextSplit(lua_State *L) {
  return luaL_error(L, "TextSplit is pass");
}

// Get a piece of a text string
static int l_raylib_TextSubtext(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int position = luaL_checkinteger(L, 2);
  int length = luaL_checkinteger(L, 3);
  const char* result = TextSubtext(text, position, length);
  lua_pushstring(L, result);
  return 1;
}

// Get integer value from text (negative values not supported)
static int l_raylib_TextToInteger(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int result = TextToInteger(text);
  lua_pushinteger(L, result);
  return 1;
}

// Get lower case version of provided string
static int l_raylib_TextToLower(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* result = TextToLower(text);
  lua_pushstring(L, result);
  return 1;
}

// Get Pascal case notation version of provided string
static int l_raylib_TextToPascal(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* result = TextToPascal(text);
  lua_pushstring(L, result);
  return 1;
}

// Get upper case version of provided string
static int l_raylib_TextToUpper(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  const char* result = TextToUpper(text);
  lua_pushstring(L, result);
  return 1;
}

// Toggle fullscreen mode (only PLATFORM_DESKTOP)
static int l_raylib_ToggleFullscreen(lua_State *L) {
  (void)L; // Suppress unused warning
  ToggleFullscreen();
  return 0;
}

// Enable/Disable VR experience
static int l_raylib_ToggleVrMode(lua_State *L) {
  (void)L; // Suppress unused warning
  ToggleVrMode();
  return 0;
}

// Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR)
static int l_raylib_TraceLog(lua_State *L) {
  int logType = luaL_checkinteger(L, 1);
  const char* text = luaL_checkstring(L, 2);
  TraceLog(logType, text);
  return 0;
}

// Show the window
static int l_raylib_UnhideWindow(lua_State *L) {
  (void)L; // Suppress unused warning
  UnhideWindow();
  return 0;
}

// Unload Font from GPU memory (VRAM)
static int l_raylib_UnloadFont(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  UnloadFont(font);
  return 0;
}

// Unload image from CPU memory (RAM)
static int l_raylib_UnloadImage(lua_State *L) {
  Image image = (*(Image*)luaL_checkudata(L, 1, "Image"));
  UnloadImage(image);
  return 0;
}

// Unload material from GPU memory (VRAM)
static int l_raylib_UnloadMaterial(lua_State *L) {
  Material material = (*(Material*)luaL_checkudata(L, 1, "Material"));
  UnloadMaterial(material);
  return 0;
}

// Unload mesh from memory (RAM and/or VRAM)
static int l_raylib_UnloadMesh(lua_State *L) {
  Mesh* mesh = (Mesh*)luaL_checkudata(L, 1, "Mesh");
  UnloadMesh(mesh);
  return 0;
}

// Unload model from memory (RAM and/or VRAM)
static int l_raylib_UnloadModel(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  UnloadModel(model);
  return 0;
}

// Unload animation data
static int l_raylib_UnloadModelAnimation(lua_State *L) {
  ModelAnimation anim = (*(ModelAnimation*)luaL_checkudata(L, 1, "ModelAnimation"));
  UnloadModelAnimation(anim);
  return 0;
}

// Unload music stream
static int l_raylib_UnloadMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  UnloadMusicStream(music);
  return 0;
}

// Unload render texture from GPU memory (VRAM)
static int l_raylib_UnloadRenderTexture(lua_State *L) {
  RenderTexture2D target = (*(RenderTexture2D*)luaL_checkudata(L, 1, "RenderTexture2D"));
  UnloadRenderTexture(target);
  return 0;
}

// Unload shader from GPU memory (VRAM)
static int l_raylib_UnloadShader(lua_State *L) {
  Shader shader = (*(Shader*)luaL_checkudata(L, 1, "Shader"));
  UnloadShader(shader);
  return 0;
}

// Unload sound
static int l_raylib_UnloadSound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  UnloadSound(sound);
  return 0;
}

// Unload texture from GPU memory (VRAM)
static int l_raylib_UnloadTexture(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  UnloadTexture(texture);
  return 0;
}

// Unload texture from GPU memory (VRAM) (unpacked version)
static int l_raylib_UnloadTextureU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  UnloadTexture(texture);
  return 0;
}

// Unload wave data
static int l_raylib_UnloadWave(lua_State *L) {
  Wave wave = (*(Wave*)luaL_checkudata(L, 1, "Wave"));
  UnloadWave(wave);
  return 0;
}

// Update audio stream buffers with data
static int l_raylib_UpdateAudioStream(lua_State *L) {
  AudioStream stream = (*(AudioStream*)luaL_checkudata(L, 1, "AudioStream"));
  const void* data = luaX_checklightuserdata(L, 2, "?");
  int samplesCount = luaL_checkinteger(L, 3);
  UpdateAudioStream(stream, data, samplesCount);
  return 0;
}

// Update camera position for selected mode
static int l_raylib_UpdateCamera(lua_State *L) {
  Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
  UpdateCamera(camera);
  return 0;
}

// Update model animation pose
static int l_raylib_UpdateModelAnimation(lua_State *L) {
  Model model = (*(Model*)luaL_checkudata(L, 1, "Model"));
  ModelAnimation anim = (*(ModelAnimation*)luaL_checkudata(L, 2, "ModelAnimation"));
  int frame = luaL_checkinteger(L, 3);
  UpdateModelAnimation(model, anim, frame);
  return 0;
}

// Updates buffers for music streaming
static int l_raylib_UpdateMusicStream(lua_State *L) {
  Music music = ((OpaqueMusic*)luaL_checkudata(L, 1, "Music"))->data;
  UpdateMusicStream(music);
  return 0;
}

// Update sound buffer with new data
static int l_raylib_UpdateSound(lua_State *L) {
  Sound sound = (*(Sound*)luaL_checkudata(L, 1, "Sound"));
  const void* data = luaX_checklightuserdata(L, 2, "?");
  int samplesCount = luaL_checkinteger(L, 3);
  UpdateSound(sound, data, samplesCount);
  return 0;
}

// Update GPU texture with new data
static int l_raylib_UpdateTexture(lua_State *L) {
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 1, "Texture2D"));
  const void* pixels = luaX_checklightuserdata(L, 2, "?");
  UpdateTexture(texture, pixels);
  return 0;
}

// Update GPU texture with new data (unpacked version)
static int l_raylib_UpdateTextureU(lua_State *L) {
  Texture2D texture = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4),luaL_checkinteger(L, 5)};
  const void* pixels = luaX_checklightuserdata(L, 6, "?");
  UpdateTexture(texture, pixels);
  return 0;
}

// Update VR tracking (position and orientation) and camera
static int l_raylib_UpdateVrTracking(lua_State *L) {
  Camera3D* camera = (Camera3D*)luaL_checkudata(L, 1, "Camera3D");
  UpdateVrTracking(camera);
  return 0;
}

// Copy a wave to a new wave
static int l_raylib_WaveCopy(lua_State *L) {
  Wave wave = (*(Wave*)luaL_checkudata(L, 1, "Wave"));
  Wave result = WaveCopy(wave);
  Wave* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Wave");
  return 1;
}

// Crop a wave to defined samples range
static int l_raylib_WaveCrop(lua_State *L) {
  Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");
  int initSample = luaL_checkinteger(L, 2);
  int finalSample = luaL_checkinteger(L, 3);
  WaveCrop(wave, initSample, finalSample);
  return 0;
}

// Convert wave data to desired format
static int l_raylib_WaveFormat(lua_State *L) {
  Wave* wave = (Wave*)luaL_checkudata(L, 1, "Wave");
  int sampleRate = luaL_checkinteger(L, 2);
  int sampleSize = luaL_checkinteger(L, 3);
  int channels = luaL_checkinteger(L, 4);
  WaveFormat(wave, sampleRate, sampleSize, channels);
  return 0;
}

// Check if KEY_ESCAPE pressed or Close icon pressed
static int l_raylib_WindowShouldClose(lua_State *L) {
  bool result = WindowShouldClose();
  lua_pushboolean(L, result);
  return 1;
}

static int l_raylib_AudioStream_new(lua_State *L) {
  AudioStream* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "AudioStream");
  if (lua_gettop(L) == 1) {
   AudioStream temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_AudioStream_meta(lua_State *L) {
  luaL_getmetatable(L, "AudioStream");
  return 1;
}

static int l_raylib_BoneInfo_new(lua_State *L) {
  BoneInfo* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "BoneInfo");
  if (lua_gettop(L) == 1) {
   BoneInfo temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_BoneInfo_meta(lua_State *L) {
  luaL_getmetatable(L, "BoneInfo");
  return 1;
}

static int l_raylib_BoundingBox_new(lua_State *L) {
  BoundingBox* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "BoundingBox");
  if (lua_gettop(L) == 1) {
   BoundingBox temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_BoundingBox_meta(lua_State *L) {
  luaL_getmetatable(L, "BoundingBox");
  return 1;
}

static int l_raylib_Camera2D_new(lua_State *L) {
  Camera2D* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Camera2D");
  if (lua_gettop(L) == 1) {
   Camera2D temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Camera2D_meta(lua_State *L) {
  luaL_getmetatable(L, "Camera2D");
  return 1;
}

static int l_raylib_Camera3D_new(lua_State *L) {
  Camera3D* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Camera3D");
  if (lua_gettop(L) == 1) {
   Camera3D temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Camera3D_meta(lua_State *L) {
  luaL_getmetatable(L, "Camera3D");
  return 1;
}

static int l_raylib_CharInfo_new(lua_State *L) {
  CharInfo* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "CharInfo");
  if (lua_gettop(L) == 1) {
   CharInfo temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_CharInfo_meta(lua_State *L) {
  luaL_getmetatable(L, "CharInfo");
  return 1;
}

static int l_raylib_Color_new(lua_State *L) {
  Color* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Color");
  if (lua_gettop(L) == 1) {
   Color temp = {};
   *obj = temp;
  } else {
    obj->r = luaL_checkinteger(L, 1);
    obj->g = luaL_checkinteger(L, 2);
    obj->b = luaL_checkinteger(L, 3);
    obj->a = luaL_checkinteger(L, 4);
  }
  return 1;
}

static int l_raylib_Color_meta(lua_State *L) {
  luaL_getmetatable(L, "Color");
  return 1;
}

static int l_raylib_Font_new(lua_State *L) {
  Font* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Font");
  if (lua_gettop(L) == 1) {
   Font temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Font_meta(lua_State *L) {
  luaL_getmetatable(L, "Font");
  return 1;
}

static int l_raylib_IVector2_new(lua_State *L) {
  IVector2* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "IVector2");
  if (lua_gettop(L) == 1) {
   IVector2 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checkinteger(L, 1);
    obj->y = luaL_checkinteger(L, 2);
  }
  return 1;
}

static int l_raylib_IVector2_meta(lua_State *L) {
  luaL_getmetatable(L, "IVector2");
  return 1;
}

static int l_raylib_IVector3_new(lua_State *L) {
  IVector3* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "IVector3");
  if (lua_gettop(L) == 1) {
   IVector3 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checkinteger(L, 1);
    obj->y = luaL_checkinteger(L, 2);
    obj->z = luaL_checkinteger(L, 3);
  }
  return 1;
}

static int l_raylib_IVector3_meta(lua_State *L) {
  luaL_getmetatable(L, "IVector3");
  return 1;
}

static int l_raylib_IVector4_new(lua_State *L) {
  IVector4* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "IVector4");
  if (lua_gettop(L) == 1) {
   IVector4 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checkinteger(L, 1);
    obj->y = luaL_checkinteger(L, 2);
    obj->z = luaL_checkinteger(L, 3);
    obj->w = luaL_checkinteger(L, 4);
  }
  return 1;
}

static int l_raylib_IVector4_meta(lua_State *L) {
  luaL_getmetatable(L, "IVector4");
  return 1;
}

static int l_raylib_Image_new(lua_State *L) {
  Image* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Image");
  if (lua_gettop(L) == 1) {
   Image temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Image_meta(lua_State *L) {
  luaL_getmetatable(L, "Image");
  return 1;
}

static int l_raylib_Material_new(lua_State *L) {
  Material* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Material");
  if (lua_gettop(L) == 1) {
   Material temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Material_meta(lua_State *L) {
  luaL_getmetatable(L, "Material");
  return 1;
}

static int l_raylib_MaterialMap_new(lua_State *L) {
  MaterialMap* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "MaterialMap");
  if (lua_gettop(L) == 1) {
   MaterialMap temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_MaterialMap_meta(lua_State *L) {
  luaL_getmetatable(L, "MaterialMap");
  return 1;
}

static int l_raylib_Matrix_new(lua_State *L) {
  Matrix* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Matrix");
  if (lua_gettop(L) == 1) {
   Matrix temp = {};
   *obj = temp;
  } else {
    obj->m0 = luaL_checknumber(L, 1);
    obj->m4 = luaL_checknumber(L, 2);
    obj->m8 = luaL_checknumber(L, 3);
    obj->m12 = luaL_checknumber(L, 4);
    obj->m1 = luaL_checknumber(L, 5);
    obj->m5 = luaL_checknumber(L, 6);
    obj->m9 = luaL_checknumber(L, 7);
    obj->m13 = luaL_checknumber(L, 8);
    obj->m2 = luaL_checknumber(L, 9);
    obj->m6 = luaL_checknumber(L, 10);
    obj->m10 = luaL_checknumber(L, 11);
    obj->m14 = luaL_checknumber(L, 12);
    obj->m3 = luaL_checknumber(L, 13);
    obj->m7 = luaL_checknumber(L, 14);
    obj->m11 = luaL_checknumber(L, 15);
    obj->m15 = luaL_checknumber(L, 16);
  }
  return 1;
}

static int l_raylib_Matrix_meta(lua_State *L) {
  luaL_getmetatable(L, "Matrix");
  return 1;
}

static int l_raylib_Mesh_new(lua_State *L) {
  Mesh* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Mesh");
  if (lua_gettop(L) == 1) {
   Mesh temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Mesh_meta(lua_State *L) {
  luaL_getmetatable(L, "Mesh");
  return 1;
}

static int l_raylib_Model_new(lua_State *L) {
  Model* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Model");
  if (lua_gettop(L) == 1) {
   Model temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Model_meta(lua_State *L) {
  luaL_getmetatable(L, "Model");
  return 1;
}

static int l_raylib_ModelAnimation_new(lua_State *L) {
  ModelAnimation* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "ModelAnimation");
  if (lua_gettop(L) == 1) {
   ModelAnimation temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_ModelAnimation_meta(lua_State *L) {
  luaL_getmetatable(L, "ModelAnimation");
  return 1;
}

static int l_raylib_NPatchInfo_new(lua_State *L) {
  NPatchInfo* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "NPatchInfo");
  if (lua_gettop(L) == 1) {
   NPatchInfo temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_NPatchInfo_meta(lua_State *L) {
  luaL_getmetatable(L, "NPatchInfo");
  return 1;
}

static int l_raylib_Ray_new(lua_State *L) {
  Ray* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Ray");
  if (lua_gettop(L) == 1) {
   Ray temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Ray_meta(lua_State *L) {
  luaL_getmetatable(L, "Ray");
  return 1;
}

static int l_raylib_RayHitInfo_new(lua_State *L) {
  RayHitInfo* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "RayHitInfo");
  if (lua_gettop(L) == 1) {
   RayHitInfo temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_RayHitInfo_meta(lua_State *L) {
  luaL_getmetatable(L, "RayHitInfo");
  return 1;
}

static int l_raylib_Rectangle_new(lua_State *L) {
  Rectangle* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Rectangle");
  if (lua_gettop(L) == 1) {
   Rectangle temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checknumber(L, 1);
    obj->y = luaL_checknumber(L, 2);
    obj->width = luaL_checknumber(L, 3);
    obj->height = luaL_checknumber(L, 4);
  }
  return 1;
}

static int l_raylib_Rectangle_meta(lua_State *L) {
  luaL_getmetatable(L, "Rectangle");
  return 1;
}

static int l_raylib_RenderTexture2D_new(lua_State *L) {
  RenderTexture2D* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "RenderTexture2D");
  if (lua_gettop(L) == 1) {
   RenderTexture2D temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_RenderTexture2D_meta(lua_State *L) {
  luaL_getmetatable(L, "RenderTexture2D");
  return 1;
}

static int l_raylib_Shader_new(lua_State *L) {
  Shader* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Shader");
  if (lua_gettop(L) == 1) {
   Shader temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Shader_meta(lua_State *L) {
  luaL_getmetatable(L, "Shader");
  return 1;
}

static int l_raylib_Sound_new(lua_State *L) {
  Sound* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Sound");
  if (lua_gettop(L) == 1) {
   Sound temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Sound_meta(lua_State *L) {
  luaL_getmetatable(L, "Sound");
  return 1;
}

static int l_raylib_Texture2D_new(lua_State *L) {
  Texture2D* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Texture2D");
  if (lua_gettop(L) == 1) {
   Texture2D temp = {};
   *obj = temp;
  } else {
    obj->id = luaL_checkinteger(L, 1);
    obj->width = luaL_checkinteger(L, 2);
    obj->height = luaL_checkinteger(L, 3);
    obj->mipmaps = luaL_checkinteger(L, 4);
    obj->format = luaL_checkinteger(L, 5);
  }
  return 1;
}

static int l_raylib_Texture2D_meta(lua_State *L) {
  luaL_getmetatable(L, "Texture2D");
  return 1;
}

static int l_raylib_Transform_new(lua_State *L) {
  Transform* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Transform");
  if (lua_gettop(L) == 1) {
   Transform temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Transform_meta(lua_State *L) {
  luaL_getmetatable(L, "Transform");
  return 1;
}

static int l_raylib_Vector2_new(lua_State *L) {
  Vector2* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Vector2");
  if (lua_gettop(L) == 1) {
   Vector2 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checknumber(L, 1);
    obj->y = luaL_checknumber(L, 2);
  }
  return 1;
}

static int l_raylib_Vector2_meta(lua_State *L) {
  luaL_getmetatable(L, "Vector2");
  return 1;
}

static int l_raylib_Vector3_new(lua_State *L) {
  Vector3* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Vector3");
  if (lua_gettop(L) == 1) {
   Vector3 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checknumber(L, 1);
    obj->y = luaL_checknumber(L, 2);
    obj->z = luaL_checknumber(L, 3);
  }
  return 1;
}

static int l_raylib_Vector3_meta(lua_State *L) {
  luaL_getmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Vector4_new(lua_State *L) {
  Vector4* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Vector4");
  if (lua_gettop(L) == 1) {
   Vector4 temp = {};
   *obj = temp;
  } else {
    obj->x = luaL_checknumber(L, 1);
    obj->y = luaL_checknumber(L, 2);
    obj->z = luaL_checknumber(L, 3);
    obj->w = luaL_checknumber(L, 4);
  }
  return 1;
}

static int l_raylib_Vector4_meta(lua_State *L) {
  luaL_getmetatable(L, "Vector4");
  return 1;
}

static int l_raylib_VrDeviceInfo_new(lua_State *L) {
  VrDeviceInfo* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "VrDeviceInfo");
  if (lua_gettop(L) == 1) {
   VrDeviceInfo temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_VrDeviceInfo_meta(lua_State *L) {
  luaL_getmetatable(L, "VrDeviceInfo");
  return 1;
}

static int l_raylib_Wave_new(lua_State *L) {
  Wave* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "Wave");
  if (lua_gettop(L) == 1) {
   Wave temp = {};
   *obj = temp;
  }
  return 1;
}

static int l_raylib_Wave_meta(lua_State *L) {
  luaL_getmetatable(L, "Wave");
  return 1;
}

static const luaL_Reg l_raylib_functions[] = {
  {"BeginBlendMode", l_raylib_BeginBlendMode},
  {"BeginDrawing", l_raylib_BeginDrawing},
  {"BeginMode2D", l_raylib_BeginMode2D},
  {"BeginMode3D", l_raylib_BeginMode3D},
  {"BeginScissorMode", l_raylib_BeginScissorMode},
  {"BeginShaderMode", l_raylib_BeginShaderMode},
  {"BeginTextureMode", l_raylib_BeginTextureMode},
  {"BeginVrDrawing", l_raylib_BeginVrDrawing},
  {"ChangeDirectory", l_raylib_ChangeDirectory},
  {"CheckCollisionBoxSphere", l_raylib_CheckCollisionBoxSphere},
  {"CheckCollisionBoxes", l_raylib_CheckCollisionBoxes},
  {"CheckCollisionCircleRec", l_raylib_CheckCollisionCircleRec},
  {"CheckCollisionCircles", l_raylib_CheckCollisionCircles},
  {"CheckCollisionPointCircle", l_raylib_CheckCollisionPointCircle},
  {"CheckCollisionPointRec", l_raylib_CheckCollisionPointRec},
  {"CheckCollisionPointTriangle", l_raylib_CheckCollisionPointTriangle},
  {"CheckCollisionRayBox", l_raylib_CheckCollisionRayBox},
  {"CheckCollisionRaySphere", l_raylib_CheckCollisionRaySphere},
  {"CheckCollisionRaySphereEx", l_raylib_CheckCollisionRaySphereEx},
  {"CheckCollisionRecs", l_raylib_CheckCollisionRecs},
  {"CheckCollisionSpheres", l_raylib_CheckCollisionSpheres},
  {"ClearBackground", l_raylib_ClearBackground},
  {"ClearDirectoryFiles", l_raylib_ClearDirectoryFiles},
  {"ClearDroppedFiles", l_raylib_ClearDroppedFiles},
  {"CloseAudioDevice", l_raylib_CloseAudioDevice},
  {"CloseAudioStream", l_raylib_CloseAudioStream},
  {"CloseVrSimulator", l_raylib_CloseVrSimulator},
  {"CloseWindow", l_raylib_CloseWindow},
  {"ColorFromHSV", l_raylib_ColorFromHSV},
  {"ColorNormalize", l_raylib_ColorNormalize},
  {"ColorToHSV", l_raylib_ColorToHSV},
  {"ColorToInt", l_raylib_ColorToInt},
  {"DisableCursor", l_raylib_DisableCursor},
  {"DrawBillboard", l_raylib_DrawBillboard},
  {"DrawBillboardRec", l_raylib_DrawBillboardRec},
  {"DrawBoundingBox", l_raylib_DrawBoundingBox},
  {"DrawCircle", l_raylib_DrawCircle},
  {"DrawCircle3D", l_raylib_DrawCircle3D},
  {"DrawCircleGradient", l_raylib_DrawCircleGradient},
  {"DrawCircleLines", l_raylib_DrawCircleLines},
  {"DrawCircleSector", l_raylib_DrawCircleSector},
  {"DrawCircleSectorLines", l_raylib_DrawCircleSectorLines},
  {"DrawCircleV", l_raylib_DrawCircleV},
  {"DrawCube", l_raylib_DrawCube},
  {"DrawCubeTexture", l_raylib_DrawCubeTexture},
  {"DrawCubeV", l_raylib_DrawCubeV},
  {"DrawCubeWires", l_raylib_DrawCubeWires},
  {"DrawCubeWiresV", l_raylib_DrawCubeWiresV},
  {"DrawCylinder", l_raylib_DrawCylinder},
  {"DrawCylinderWires", l_raylib_DrawCylinderWires},
  {"DrawFPS", l_raylib_DrawFPS},
  {"DrawGizmo", l_raylib_DrawGizmo},
  {"DrawGrid", l_raylib_DrawGrid},
  {"DrawLine", l_raylib_DrawLine},
  {"DrawLine3D", l_raylib_DrawLine3D},
  {"DrawLineBezier", l_raylib_DrawLineBezier},
  {"DrawLineEx", l_raylib_DrawLineEx},
  {"DrawLineStrip", l_raylib_DrawLineStrip},
  {"DrawLineV", l_raylib_DrawLineV},
  {"DrawModel", l_raylib_DrawModel},
  {"DrawModelEx", l_raylib_DrawModelEx},
  {"DrawModelWires", l_raylib_DrawModelWires},
  {"DrawModelWiresEx", l_raylib_DrawModelWiresEx},
  {"DrawPixel", l_raylib_DrawPixel},
  {"DrawPixelV", l_raylib_DrawPixelV},
  {"DrawPlane", l_raylib_DrawPlane},
  {"DrawPoly", l_raylib_DrawPoly},
  {"DrawRay", l_raylib_DrawRay},
  {"DrawRectangle", l_raylib_DrawRectangle},
  {"DrawRectangleGradientEx", l_raylib_DrawRectangleGradientEx},
  {"DrawRectangleGradientH", l_raylib_DrawRectangleGradientH},
  {"DrawRectangleGradientV", l_raylib_DrawRectangleGradientV},
  {"DrawRectangleLines", l_raylib_DrawRectangleLines},
  {"DrawRectangleLinesEx", l_raylib_DrawRectangleLinesEx},
  {"DrawRectanglePro", l_raylib_DrawRectanglePro},
  {"DrawRectangleRec", l_raylib_DrawRectangleRec},
  {"DrawRectangleRounded", l_raylib_DrawRectangleRounded},
  {"DrawRectangleRoundedLines", l_raylib_DrawRectangleRoundedLines},
  {"DrawRectangleV", l_raylib_DrawRectangleV},
  {"DrawRing", l_raylib_DrawRing},
  {"DrawRingLines", l_raylib_DrawRingLines},
  {"DrawSphere", l_raylib_DrawSphere},
  {"DrawSphereEx", l_raylib_DrawSphereEx},
  {"DrawSphereWires", l_raylib_DrawSphereWires},
  {"DrawText", l_raylib_DrawText},
  {"DrawTextEx", l_raylib_DrawTextEx},
  {"DrawTextRec", l_raylib_DrawTextRec},
  {"DrawTextRecEx", l_raylib_DrawTextRecEx},
  {"DrawTexture", l_raylib_DrawTexture},
  {"DrawTextureEx", l_raylib_DrawTextureEx},
  {"DrawTextureNPatch", l_raylib_DrawTextureNPatch},
  {"DrawTexturePro", l_raylib_DrawTexturePro},
  {"DrawTextureQuad", l_raylib_DrawTextureQuad},
  {"DrawTextureRec", l_raylib_DrawTextureRec},
  {"DrawTextureV", l_raylib_DrawTextureV},
  {"DrawTriangle", l_raylib_DrawTriangle},
  {"DrawTriangleFan", l_raylib_DrawTriangleFan},
  {"DrawTriangleLines", l_raylib_DrawTriangleLines},
  {"EnableCursor", l_raylib_EnableCursor},
  {"EndBlendMode", l_raylib_EndBlendMode},
  {"EndDrawing", l_raylib_EndDrawing},
  {"EndMode2D", l_raylib_EndMode2D},
  {"EndMode3D", l_raylib_EndMode3D},
  {"EndScissorMode", l_raylib_EndScissorMode},
  {"EndShaderMode", l_raylib_EndShaderMode},
  {"EndTextureMode", l_raylib_EndTextureMode},
  {"EndVrDrawing", l_raylib_EndVrDrawing},
  {"ExportImage", l_raylib_ExportImage},
  {"ExportImageAsCode", l_raylib_ExportImageAsCode},
  {"ExportMesh", l_raylib_ExportMesh},
  {"ExportWave", l_raylib_ExportWave},
  {"ExportWaveAsCode", l_raylib_ExportWaveAsCode},
  {"Fade", l_raylib_Fade},
  {"FileExists", l_raylib_FileExists},
  {"GenImageCellular", l_raylib_GenImageCellular},
  {"GenImageChecked", l_raylib_GenImageChecked},
  {"GenImageColor", l_raylib_GenImageColor},
  {"GenImageFontAtlas", l_raylib_GenImageFontAtlas},
  {"GenImageGradientH", l_raylib_GenImageGradientH},
  {"GenImageGradientRadial", l_raylib_GenImageGradientRadial},
  {"GenImageGradientV", l_raylib_GenImageGradientV},
  {"GenImagePerlinNoise", l_raylib_GenImagePerlinNoise},
  {"GenImageWhiteNoise", l_raylib_GenImageWhiteNoise},
  {"GenMeshCube", l_raylib_GenMeshCube},
  {"GenMeshCubicmap", l_raylib_GenMeshCubicmap},
  {"GenMeshCylinder", l_raylib_GenMeshCylinder},
  {"GenMeshHeightmap", l_raylib_GenMeshHeightmap},
  {"GenMeshHemiSphere", l_raylib_GenMeshHemiSphere},
  {"GenMeshKnot", l_raylib_GenMeshKnot},
  {"GenMeshPlane", l_raylib_GenMeshPlane},
  {"GenMeshPoly", l_raylib_GenMeshPoly},
  {"GenMeshSphere", l_raylib_GenMeshSphere},
  {"GenMeshTorus", l_raylib_GenMeshTorus},
  {"GenTextureBRDF", l_raylib_GenTextureBRDF},
  {"GenTextureCubemap", l_raylib_GenTextureCubemap},
  {"GenTextureIrradiance", l_raylib_GenTextureIrradiance},
  {"GenTextureMipmaps", l_raylib_GenTextureMipmaps},
  {"GenTexturePrefilter", l_raylib_GenTexturePrefilter},
  {"GetCameraMatrix", l_raylib_GetCameraMatrix},
  {"GetClipboardText", l_raylib_GetClipboardText},
  {"GetCollisionRayGround", l_raylib_GetCollisionRayGround},
  {"GetCollisionRayModel", l_raylib_GetCollisionRayModel},
  {"GetCollisionRayTriangle", l_raylib_GetCollisionRayTriangle},
  {"GetCollisionRec", l_raylib_GetCollisionRec},
  {"GetColor", l_raylib_GetColor},
  {"GetDirectoryFiles", l_raylib_GetDirectoryFiles},
  {"GetDirectoryPath", l_raylib_GetDirectoryPath},
  {"GetDroppedFiles", l_raylib_GetDroppedFiles},
  {"GetExtension", l_raylib_GetExtension},
  {"GetFPS", l_raylib_GetFPS},
  {"GetFileModTime", l_raylib_GetFileModTime},
  {"GetFileName", l_raylib_GetFileName},
  {"GetFileNameWithoutExt", l_raylib_GetFileNameWithoutExt},
  {"GetFontDefault", l_raylib_GetFontDefault},
  {"GetFrameTime", l_raylib_GetFrameTime},
  {"GetGamepadAxisCount", l_raylib_GetGamepadAxisCount},
  {"GetGamepadAxisMovement", l_raylib_GetGamepadAxisMovement},
  {"GetGamepadButtonPressed", l_raylib_GetGamepadButtonPressed},
  {"GetGamepadName", l_raylib_GetGamepadName},
  {"GetGestureDetected", l_raylib_GetGestureDetected},
  {"GetGestureDragAngle", l_raylib_GetGestureDragAngle},
  {"GetGestureDragVector", l_raylib_GetGestureDragVector},
  {"GetGestureHoldDuration", l_raylib_GetGestureHoldDuration},
  {"GetGesturePinchAngle", l_raylib_GetGesturePinchAngle},
  {"GetGesturePinchVector", l_raylib_GetGesturePinchVector},
  {"GetGlyphIndex", l_raylib_GetGlyphIndex},
  {"GetImageData", l_raylib_GetImageData},
  {"GetImageDataNormalized", l_raylib_GetImageDataNormalized},
  {"GetKeyPressed", l_raylib_GetKeyPressed},
  {"GetMatrixModelview", l_raylib_GetMatrixModelview},
  {"GetMonitorCount", l_raylib_GetMonitorCount},
  {"GetMonitorHeight", l_raylib_GetMonitorHeight},
  {"GetMonitorName", l_raylib_GetMonitorName},
  {"GetMonitorPhysicalHeight", l_raylib_GetMonitorPhysicalHeight},
  {"GetMonitorPhysicalWidth", l_raylib_GetMonitorPhysicalWidth},
  {"GetMonitorWidth", l_raylib_GetMonitorWidth},
  {"GetMousePosition", l_raylib_GetMousePosition},
  {"GetMouseRay", l_raylib_GetMouseRay},
  {"GetMouseWheelMove", l_raylib_GetMouseWheelMove},
  {"GetMouseX", l_raylib_GetMouseX},
  {"GetMouseY", l_raylib_GetMouseY},
  {"GetMusicTimeLength", l_raylib_GetMusicTimeLength},
  {"GetMusicTimePlayed", l_raylib_GetMusicTimePlayed},
  {"GetNextCodepoint", l_raylib_GetNextCodepoint},
  {"GetPixelDataSize", l_raylib_GetPixelDataSize},
  {"GetRandomValue", l_raylib_GetRandomValue},
  {"GetScreenData", l_raylib_GetScreenData},
  {"GetScreenHeight", l_raylib_GetScreenHeight},
  {"GetScreenWidth", l_raylib_GetScreenWidth},
  {"GetShaderDefault", l_raylib_GetShaderDefault},
  {"GetShaderLocation", l_raylib_GetShaderLocation},
  {"GetTextureData", l_raylib_GetTextureData},
  {"GetTextureDefault", l_raylib_GetTextureDefault},
  {"GetTime", l_raylib_GetTime},
  {"GetTouchPointsCount", l_raylib_GetTouchPointsCount},
  {"GetTouchPosition", l_raylib_GetTouchPosition},
  {"GetTouchX", l_raylib_GetTouchX},
  {"GetTouchY", l_raylib_GetTouchY},
  {"GetWaveData", l_raylib_GetWaveData},
  {"GetWindowHandle", l_raylib_GetWindowHandle},
  {"GetWorkingDirectory", l_raylib_GetWorkingDirectory},
  {"GetWorldToScreen", l_raylib_GetWorldToScreen},
  {"HideCursor", l_raylib_HideCursor},
  {"HideWindow", l_raylib_HideWindow},
  {"ImageAlphaClear", l_raylib_ImageAlphaClear},
  {"ImageAlphaCrop", l_raylib_ImageAlphaCrop},
  {"ImageAlphaMask", l_raylib_ImageAlphaMask},
  {"ImageAlphaPremultiply", l_raylib_ImageAlphaPremultiply},
  {"ImageColorBrightness", l_raylib_ImageColorBrightness},
  {"ImageColorContrast", l_raylib_ImageColorContrast},
  {"ImageColorGrayscale", l_raylib_ImageColorGrayscale},
  {"ImageColorInvert", l_raylib_ImageColorInvert},
  {"ImageColorReplace", l_raylib_ImageColorReplace},
  {"ImageColorTint", l_raylib_ImageColorTint},
  {"ImageCopy", l_raylib_ImageCopy},
  {"ImageCrop", l_raylib_ImageCrop},
  {"ImageDither", l_raylib_ImageDither},
  {"ImageDraw", l_raylib_ImageDraw},
  {"ImageDrawRectangle", l_raylib_ImageDrawRectangle},
  {"ImageDrawRectangleLines", l_raylib_ImageDrawRectangleLines},
  {"ImageDrawText", l_raylib_ImageDrawText},
  {"ImageDrawTextEx", l_raylib_ImageDrawTextEx},
  {"ImageExtractPalette", l_raylib_ImageExtractPalette},
  {"ImageFlipHorizontal", l_raylib_ImageFlipHorizontal},
  {"ImageFlipVertical", l_raylib_ImageFlipVertical},
  {"ImageFormat", l_raylib_ImageFormat},
  {"ImageMipmaps", l_raylib_ImageMipmaps},
  {"ImageResize", l_raylib_ImageResize},
  {"ImageResizeCanvas", l_raylib_ImageResizeCanvas},
  {"ImageResizeNN", l_raylib_ImageResizeNN},
  {"ImageRotateCCW", l_raylib_ImageRotateCCW},
  {"ImageRotateCW", l_raylib_ImageRotateCW},
  {"ImageText", l_raylib_ImageText},
  {"ImageTextEx", l_raylib_ImageTextEx},
  {"ImageToPOT", l_raylib_ImageToPOT},
  {"InitAudioDevice", l_raylib_InitAudioDevice},
  {"InitAudioStream", l_raylib_InitAudioStream},
  {"InitVrSimulator", l_raylib_InitVrSimulator},
  {"InitWindow", l_raylib_InitWindow},
  {"IsAudioBufferProcessed", l_raylib_IsAudioBufferProcessed},
  {"IsAudioDeviceReady", l_raylib_IsAudioDeviceReady},
  {"IsAudioStreamPlaying", l_raylib_IsAudioStreamPlaying},
  {"IsCursorHidden", l_raylib_IsCursorHidden},
  {"IsFileDropped", l_raylib_IsFileDropped},
  {"IsFileExtension", l_raylib_IsFileExtension},
  {"IsGamepadAvailable", l_raylib_IsGamepadAvailable},
  {"IsGamepadButtonDown", l_raylib_IsGamepadButtonDown},
  {"IsGamepadButtonPressed", l_raylib_IsGamepadButtonPressed},
  {"IsGamepadButtonReleased", l_raylib_IsGamepadButtonReleased},
  {"IsGamepadButtonUp", l_raylib_IsGamepadButtonUp},
  {"IsGamepadName", l_raylib_IsGamepadName},
  {"IsGestureDetected", l_raylib_IsGestureDetected},
  {"IsKeyDown", l_raylib_IsKeyDown},
  {"IsKeyPressed", l_raylib_IsKeyPressed},
  {"IsKeyReleased", l_raylib_IsKeyReleased},
  {"IsKeyUp", l_raylib_IsKeyUp},
  {"IsModelAnimationValid", l_raylib_IsModelAnimationValid},
  {"IsMouseButtonDown", l_raylib_IsMouseButtonDown},
  {"IsMouseButtonPressed", l_raylib_IsMouseButtonPressed},
  {"IsMouseButtonReleased", l_raylib_IsMouseButtonReleased},
  {"IsMouseButtonUp", l_raylib_IsMouseButtonUp},
  {"IsMusicPlaying", l_raylib_IsMusicPlaying},
  {"IsSoundPlaying", l_raylib_IsSoundPlaying},
  {"IsVrSimulatorReady", l_raylib_IsVrSimulatorReady},
  {"IsWindowHidden", l_raylib_IsWindowHidden},
  {"IsWindowMinimized", l_raylib_IsWindowMinimized},
  {"IsWindowReady", l_raylib_IsWindowReady},
  {"IsWindowResized", l_raylib_IsWindowResized},
  {"LoadFont", l_raylib_LoadFont},
  {"LoadFontData", l_raylib_LoadFontData},
  {"LoadFontEx", l_raylib_LoadFontEx},
  {"LoadFontFromImage", l_raylib_LoadFontFromImage},
  {"LoadImage", l_raylib_LoadImage},
  {"LoadImageEx", l_raylib_LoadImageEx},
  {"LoadImagePro", l_raylib_LoadImagePro},
  {"LoadImageRaw", l_raylib_LoadImageRaw},
  {"LoadMaterialDefault", l_raylib_LoadMaterialDefault},
  {"LoadMaterials", l_raylib_LoadMaterials},
  {"LoadMeshes", l_raylib_LoadMeshes},
  {"LoadModel", l_raylib_LoadModel},
  {"LoadModelAnimations", l_raylib_LoadModelAnimations},
  {"LoadModelFromMesh", l_raylib_LoadModelFromMesh},
  {"LoadMusicStream", l_raylib_LoadMusicStream},
  {"LoadRenderTexture", l_raylib_LoadRenderTexture},
  {"LoadShader", l_raylib_LoadShader},
  {"LoadShaderCode", l_raylib_LoadShaderCode},
  {"LoadSound", l_raylib_LoadSound},
  {"LoadSoundFromWave", l_raylib_LoadSoundFromWave},
  {"LoadText", l_raylib_LoadText},
  {"LoadTexture", l_raylib_LoadTexture},
  {"LoadTextureCubemap", l_raylib_LoadTextureCubemap},
  {"LoadTextureFromImage", l_raylib_LoadTextureFromImage},
  {"LoadWave", l_raylib_LoadWave},
  {"LoadWaveEx", l_raylib_LoadWaveEx},
  {"MeasureText", l_raylib_MeasureText},
  {"MeasureTextEx", l_raylib_MeasureTextEx},
  {"MeshBinormals", l_raylib_MeshBinormals},
  {"MeshBoundingBox", l_raylib_MeshBoundingBox},
  {"MeshTangents", l_raylib_MeshTangents},
  {"OpenURL", l_raylib_OpenURL},
  {"PauseAudioStream", l_raylib_PauseAudioStream},
  {"PauseMusicStream", l_raylib_PauseMusicStream},
  {"PauseSound", l_raylib_PauseSound},
  {"PlayAudioStream", l_raylib_PlayAudioStream},
  {"PlayMusicStream", l_raylib_PlayMusicStream},
  {"PlaySound", l_raylib_PlaySound},
  {"ResumeAudioStream", l_raylib_ResumeAudioStream},
  {"ResumeMusicStream", l_raylib_ResumeMusicStream},
  {"ResumeSound", l_raylib_ResumeSound},
  {"SetAudioStreamPitch", l_raylib_SetAudioStreamPitch},
  {"SetAudioStreamVolume", l_raylib_SetAudioStreamVolume},
  {"SetCameraAltControl", l_raylib_SetCameraAltControl},
  {"SetCameraMode", l_raylib_SetCameraMode},
  {"SetCameraMoveControls", l_raylib_SetCameraMoveControls},
  {"SetCameraPanControl", l_raylib_SetCameraPanControl},
  {"SetCameraSmoothZoomControl", l_raylib_SetCameraSmoothZoomControl},
  {"SetClipboardText", l_raylib_SetClipboardText},
  {"SetConfigFlags", l_raylib_SetConfigFlags},
  {"SetExitKey", l_raylib_SetExitKey},
  {"SetGesturesEnabled", l_raylib_SetGesturesEnabled},
  {"SetMasterVolume", l_raylib_SetMasterVolume},
  {"SetMaterialTexture", l_raylib_SetMaterialTexture},
  {"SetMatrixModelview", l_raylib_SetMatrixModelview},
  {"SetMatrixProjection", l_raylib_SetMatrixProjection},
  {"SetModelMeshMaterial", l_raylib_SetModelMeshMaterial},
  {"SetMouseOffset", l_raylib_SetMouseOffset},
  {"SetMousePosition", l_raylib_SetMousePosition},
  {"SetMouseScale", l_raylib_SetMouseScale},
  {"SetMusicLoopCount", l_raylib_SetMusicLoopCount},
  {"SetMusicPitch", l_raylib_SetMusicPitch},
  {"SetMusicVolume", l_raylib_SetMusicVolume},
  {"SetShaderValue", l_raylib_SetShaderValue},
  {"SetShaderValueFloat", l_raylib_SetShaderValueFloat},
  {"SetShaderValueIVec2", l_raylib_SetShaderValueIVec2},
  {"SetShaderValueIVec3", l_raylib_SetShaderValueIVec3},
  {"SetShaderValueIVec4", l_raylib_SetShaderValueIVec4},
  {"SetShaderValueInt", l_raylib_SetShaderValueInt},
  {"SetShaderValueMatrix", l_raylib_SetShaderValueMatrix},
  {"SetShaderValueSampler2D", l_raylib_SetShaderValueSampler2D},
  {"SetShaderValueTexture", l_raylib_SetShaderValueTexture},
  {"SetShaderValueV", l_raylib_SetShaderValueV},
  {"SetShaderValueVec2", l_raylib_SetShaderValueVec2},
  {"SetShaderValueVec3", l_raylib_SetShaderValueVec3},
  {"SetShaderValueVec4", l_raylib_SetShaderValueVec4},
  {"SetShapesTexture", l_raylib_SetShapesTexture},
  {"SetSoundPitch", l_raylib_SetSoundPitch},
  {"SetSoundVolume", l_raylib_SetSoundVolume},
  {"SetTargetFPS", l_raylib_SetTargetFPS},
  {"SetTextureFilter", l_raylib_SetTextureFilter},
  {"SetTextureWrap", l_raylib_SetTextureWrap},
  {"SetTraceLogCallback", l_raylib_SetTraceLogCallback},
  {"SetTraceLogExit", l_raylib_SetTraceLogExit},
  {"SetTraceLogLevel", l_raylib_SetTraceLogLevel},
  {"SetVrConfiguration", l_raylib_SetVrConfiguration},
  {"SetWindowIcon", l_raylib_SetWindowIcon},
  {"SetWindowMinSize", l_raylib_SetWindowMinSize},
  {"SetWindowMonitor", l_raylib_SetWindowMonitor},
  {"SetWindowPosition", l_raylib_SetWindowPosition},
  {"SetWindowSize", l_raylib_SetWindowSize},
  {"SetWindowTitle", l_raylib_SetWindowTitle},
  {"ShowCursor", l_raylib_ShowCursor},
  {"StopAudioStream", l_raylib_StopAudioStream},
  {"StopMusicStream", l_raylib_StopMusicStream},
  {"StopSound", l_raylib_StopSound},
  {"StorageLoadValue", l_raylib_StorageLoadValue},
  {"StorageSaveValue", l_raylib_StorageSaveValue},
  {"TakeScreenshot", l_raylib_TakeScreenshot},
  {"TextAppend", l_raylib_TextAppend},
  {"TextCountCodepoints", l_raylib_TextCountCodepoints},
  {"TextFindIndex", l_raylib_TextFindIndex},
  {"TextFormat", l_raylib_TextFormat},
  {"TextInsert", l_raylib_TextInsert},
  {"TextIsEqual", l_raylib_TextIsEqual},
  {"TextJoin", l_raylib_TextJoin},
  {"TextLength", l_raylib_TextLength},
  {"TextReplace", l_raylib_TextReplace},
  {"TextSplit", l_raylib_TextSplit},
  {"TextSubtext", l_raylib_TextSubtext},
  {"TextToInteger", l_raylib_TextToInteger},
  {"TextToLower", l_raylib_TextToLower},
  {"TextToPascal", l_raylib_TextToPascal},
  {"TextToUpper", l_raylib_TextToUpper},
  {"ToggleFullscreen", l_raylib_ToggleFullscreen},
  {"ToggleVrMode", l_raylib_ToggleVrMode},
  {"TraceLog", l_raylib_TraceLog},
  {"UnhideWindow", l_raylib_UnhideWindow},
  {"UnloadFont", l_raylib_UnloadFont},
  {"UnloadImage", l_raylib_UnloadImage},
  {"UnloadMaterial", l_raylib_UnloadMaterial},
  {"UnloadMesh", l_raylib_UnloadMesh},
  {"UnloadModel", l_raylib_UnloadModel},
  {"UnloadModelAnimation", l_raylib_UnloadModelAnimation},
  {"UnloadMusicStream", l_raylib_UnloadMusicStream},
  {"UnloadRenderTexture", l_raylib_UnloadRenderTexture},
  {"UnloadShader", l_raylib_UnloadShader},
  {"UnloadSound", l_raylib_UnloadSound},
  {"UnloadTexture", l_raylib_UnloadTexture},
  {"UnloadWave", l_raylib_UnloadWave},
  {"UpdateAudioStream", l_raylib_UpdateAudioStream},
  {"UpdateCamera", l_raylib_UpdateCamera},
  {"UpdateModelAnimation", l_raylib_UpdateModelAnimation},
  {"UpdateMusicStream", l_raylib_UpdateMusicStream},
  {"UpdateSound", l_raylib_UpdateSound},
  {"UpdateTexture", l_raylib_UpdateTexture},
  {"UpdateVrTracking", l_raylib_UpdateVrTracking},
  {"WaveCopy", l_raylib_WaveCopy},
  {"WaveCrop", l_raylib_WaveCrop},
  {"WaveFormat", l_raylib_WaveFormat},
  {"WindowShouldClose", l_raylib_WindowShouldClose},
  {"CheckCollisionBoxSphereU", l_raylib_CheckCollisionBoxSphereU},
  {"CheckCollisionCircleRecU", l_raylib_CheckCollisionCircleRecU},
  {"CheckCollisionCirclesU", l_raylib_CheckCollisionCirclesU},
  {"CheckCollisionPointCircleU", l_raylib_CheckCollisionPointCircleU},
  {"CheckCollisionPointRecU", l_raylib_CheckCollisionPointRecU},
  {"CheckCollisionPointTriangleU", l_raylib_CheckCollisionPointTriangleU},
  {"CheckCollisionRaySphereU", l_raylib_CheckCollisionRaySphereU},
  {"CheckCollisionRecsU", l_raylib_CheckCollisionRecsU},
  {"CheckCollisionSpheresU", l_raylib_CheckCollisionSpheresU},
  {"ClearBackgroundU", l_raylib_ClearBackgroundU},
  {"ColorFromHSVU", l_raylib_ColorFromHSVU},
  {"ColorNormalizeU", l_raylib_ColorNormalizeU},
  {"ColorToHSVU", l_raylib_ColorToHSVU},
  {"ColorToIntU", l_raylib_ColorToIntU},
  {"DrawBillboardU", l_raylib_DrawBillboardU},
  {"DrawBillboardRecU", l_raylib_DrawBillboardRecU},
  {"DrawBoundingBoxU", l_raylib_DrawBoundingBoxU},
  {"DrawCircleU", l_raylib_DrawCircleU},
  {"DrawCircle3DU", l_raylib_DrawCircle3DU},
  {"DrawCircleGradientU", l_raylib_DrawCircleGradientU},
  {"DrawCircleLinesU", l_raylib_DrawCircleLinesU},
  {"DrawCircleSectorU", l_raylib_DrawCircleSectorU},
  {"DrawCircleSectorLinesU", l_raylib_DrawCircleSectorLinesU},
  {"DrawCircleVU", l_raylib_DrawCircleVU},
  {"DrawCubeU", l_raylib_DrawCubeU},
  {"DrawCubeTextureU", l_raylib_DrawCubeTextureU},
  {"DrawCubeVU", l_raylib_DrawCubeVU},
  {"DrawCubeWiresU", l_raylib_DrawCubeWiresU},
  {"DrawCubeWiresVU", l_raylib_DrawCubeWiresVU},
  {"DrawCylinderU", l_raylib_DrawCylinderU},
  {"DrawCylinderWiresU", l_raylib_DrawCylinderWiresU},
  {"DrawGizmoU", l_raylib_DrawGizmoU},
  {"DrawLineU", l_raylib_DrawLineU},
  {"DrawLine3DU", l_raylib_DrawLine3DU},
  {"DrawLineBezierU", l_raylib_DrawLineBezierU},
  {"DrawLineExU", l_raylib_DrawLineExU},
  {"DrawLineVU", l_raylib_DrawLineVU},
  {"DrawModelU", l_raylib_DrawModelU},
  {"DrawModelExU", l_raylib_DrawModelExU},
  {"DrawModelWiresU", l_raylib_DrawModelWiresU},
  {"DrawModelWiresExU", l_raylib_DrawModelWiresExU},
  {"DrawPixelU", l_raylib_DrawPixelU},
  {"DrawPixelVU", l_raylib_DrawPixelVU},
  {"DrawPlaneU", l_raylib_DrawPlaneU},
  {"DrawPolyU", l_raylib_DrawPolyU},
  {"DrawRayU", l_raylib_DrawRayU},
  {"DrawRectangleU", l_raylib_DrawRectangleU},
  {"DrawRectangleGradientExU", l_raylib_DrawRectangleGradientExU},
  {"DrawRectangleGradientHU", l_raylib_DrawRectangleGradientHU},
  {"DrawRectangleGradientVU", l_raylib_DrawRectangleGradientVU},
  {"DrawRectangleLinesU", l_raylib_DrawRectangleLinesU},
  {"DrawRectangleLinesExU", l_raylib_DrawRectangleLinesExU},
  {"DrawRectangleProU", l_raylib_DrawRectangleProU},
  {"DrawRectangleRecU", l_raylib_DrawRectangleRecU},
  {"DrawRectangleRoundedU", l_raylib_DrawRectangleRoundedU},
  {"DrawRectangleRoundedLinesU", l_raylib_DrawRectangleRoundedLinesU},
  {"DrawRectangleVU", l_raylib_DrawRectangleVU},
  {"DrawRingU", l_raylib_DrawRingU},
  {"DrawRingLinesU", l_raylib_DrawRingLinesU},
  {"DrawSphereU", l_raylib_DrawSphereU},
  {"DrawSphereExU", l_raylib_DrawSphereExU},
  {"DrawSphereWiresU", l_raylib_DrawSphereWiresU},
  {"DrawTextU", l_raylib_DrawTextU},
  {"DrawTextExU", l_raylib_DrawTextExU},
  {"DrawTextRecU", l_raylib_DrawTextRecU},
  {"DrawTextRecExU", l_raylib_DrawTextRecExU},
  {"DrawTextureU", l_raylib_DrawTextureU},
  {"DrawTextureExU", l_raylib_DrawTextureExU},
  {"DrawTextureNPatchU", l_raylib_DrawTextureNPatchU},
  {"DrawTextureProU", l_raylib_DrawTextureProU},
  {"DrawTextureQuadU", l_raylib_DrawTextureQuadU},
  {"DrawTextureRecU", l_raylib_DrawTextureRecU},
  {"DrawTextureVU", l_raylib_DrawTextureVU},
  {"DrawTriangleU", l_raylib_DrawTriangleU},
  {"DrawTriangleLinesU", l_raylib_DrawTriangleLinesU},
  {"FadeU", l_raylib_FadeU},
  {"GenImageCheckedU", l_raylib_GenImageCheckedU},
  {"GenImageColorU", l_raylib_GenImageColorU},
  {"GenImageGradientHU", l_raylib_GenImageGradientHU},
  {"GenImageGradientRadialU", l_raylib_GenImageGradientRadialU},
  {"GenImageGradientVU", l_raylib_GenImageGradientVU},
  {"GenMeshCubicmapU", l_raylib_GenMeshCubicmapU},
  {"GenMeshHeightmapU", l_raylib_GenMeshHeightmapU},
  {"GenTextureBRDFU", l_raylib_GenTextureBRDFU},
  {"GenTextureCubemapU", l_raylib_GenTextureCubemapU},
  {"GenTextureIrradianceU", l_raylib_GenTextureIrradianceU},
  {"GenTexturePrefilterU", l_raylib_GenTexturePrefilterU},
  {"GetCameraMatrixU", l_raylib_GetCameraMatrixU},
  {"GetCollisionRayTriangleU", l_raylib_GetCollisionRayTriangleU},
  {"GetCollisionRecU", l_raylib_GetCollisionRecU},
  {"GetColorU", l_raylib_GetColorU},
  {"GetGestureDragVectorU", l_raylib_GetGestureDragVectorU},
  {"GetGesturePinchVectorU", l_raylib_GetGesturePinchVectorU},
  {"GetMatrixModelviewU", l_raylib_GetMatrixModelviewU},
  {"GetMousePositionU", l_raylib_GetMousePositionU},
  {"GetMouseRayU", l_raylib_GetMouseRayU},
  {"GetTextureDataU", l_raylib_GetTextureDataU},
  {"GetTextureDefaultU", l_raylib_GetTextureDefaultU},
  {"GetTouchPositionU", l_raylib_GetTouchPositionU},
  {"GetWorldToScreenU", l_raylib_GetWorldToScreenU},
  {"ImageAlphaClearU", l_raylib_ImageAlphaClearU},
  {"ImageColorReplaceU", l_raylib_ImageColorReplaceU},
  {"ImageColorTintU", l_raylib_ImageColorTintU},
  {"ImageCropU", l_raylib_ImageCropU},
  {"ImageDrawU", l_raylib_ImageDrawU},
  {"ImageDrawRectangleU", l_raylib_ImageDrawRectangleU},
  {"ImageDrawRectangleLinesU", l_raylib_ImageDrawRectangleLinesU},
  {"ImageDrawTextU", l_raylib_ImageDrawTextU},
  {"ImageDrawTextExU", l_raylib_ImageDrawTextExU},
  {"ImageResizeCanvasU", l_raylib_ImageResizeCanvasU},
  {"ImageTextU", l_raylib_ImageTextU},
  {"ImageTextExU", l_raylib_ImageTextExU},
  {"ImageToPOTU", l_raylib_ImageToPOTU},
  {"LoadFontFromImageU", l_raylib_LoadFontFromImageU},
  {"LoadTextureU", l_raylib_LoadTextureU},
  {"LoadTextureCubemapU", l_raylib_LoadTextureCubemapU},
  {"LoadTextureFromImageU", l_raylib_LoadTextureFromImageU},
  {"MeasureTextExU", l_raylib_MeasureTextExU},
  {"SetMaterialTextureU", l_raylib_SetMaterialTextureU},
  {"SetMatrixModelviewU", l_raylib_SetMatrixModelviewU},
  {"SetMatrixProjectionU", l_raylib_SetMatrixProjectionU},
  {"SetShaderValueIVec2U", l_raylib_SetShaderValueIVec2U},
  {"SetShaderValueIVec3U", l_raylib_SetShaderValueIVec3U},
  {"SetShaderValueIVec4U", l_raylib_SetShaderValueIVec4U},
  {"SetShaderValueMatrixU", l_raylib_SetShaderValueMatrixU},
  {"SetShaderValueTextureU", l_raylib_SetShaderValueTextureU},
  {"SetShaderValueVec2U", l_raylib_SetShaderValueVec2U},
  {"SetShaderValueVec3U", l_raylib_SetShaderValueVec3U},
  {"SetShaderValueVec4U", l_raylib_SetShaderValueVec4U},
  {"SetShapesTextureU", l_raylib_SetShapesTextureU},
  {"SetTextureFilterU", l_raylib_SetTextureFilterU},
  {"SetTextureWrapU", l_raylib_SetTextureWrapU},
  {"UnloadTextureU", l_raylib_UnloadTextureU},
  {"UpdateTextureU", l_raylib_UpdateTextureU},
  {"AudioStream", l_raylib_AudioStream_new},
  {"AudioStreamMeta", l_raylib_AudioStream_meta},
  {"BoneInfo", l_raylib_BoneInfo_new},
  {"BoneInfoMeta", l_raylib_BoneInfo_meta},
  {"BoundingBox", l_raylib_BoundingBox_new},
  {"BoundingBoxMeta", l_raylib_BoundingBox_meta},
  {"Camera2D", l_raylib_Camera2D_new},
  {"Camera2DMeta", l_raylib_Camera2D_meta},
  {"Camera3D", l_raylib_Camera3D_new},
  {"Camera3DMeta", l_raylib_Camera3D_meta},
  {"CharInfo", l_raylib_CharInfo_new},
  {"CharInfoMeta", l_raylib_CharInfo_meta},
  {"Color", l_raylib_Color_new},
  {"ColorMeta", l_raylib_Color_meta},
  {"Font", l_raylib_Font_new},
  {"FontMeta", l_raylib_Font_meta},
  {"IVector2", l_raylib_IVector2_new},
  {"IVector2Meta", l_raylib_IVector2_meta},
  {"IVector3", l_raylib_IVector3_new},
  {"IVector3Meta", l_raylib_IVector3_meta},
  {"IVector4", l_raylib_IVector4_new},
  {"IVector4Meta", l_raylib_IVector4_meta},
  {"Image", l_raylib_Image_new},
  {"ImageMeta", l_raylib_Image_meta},
  {"Material", l_raylib_Material_new},
  {"MaterialMeta", l_raylib_Material_meta},
  {"MaterialMap", l_raylib_MaterialMap_new},
  {"MaterialMapMeta", l_raylib_MaterialMap_meta},
  {"Matrix", l_raylib_Matrix_new},
  {"MatrixMeta", l_raylib_Matrix_meta},
  {"Mesh", l_raylib_Mesh_new},
  {"MeshMeta", l_raylib_Mesh_meta},
  {"Model", l_raylib_Model_new},
  {"ModelMeta", l_raylib_Model_meta},
  {"ModelAnimation", l_raylib_ModelAnimation_new},
  {"ModelAnimationMeta", l_raylib_ModelAnimation_meta},
  {"NPatchInfo", l_raylib_NPatchInfo_new},
  {"NPatchInfoMeta", l_raylib_NPatchInfo_meta},
  {"Ray", l_raylib_Ray_new},
  {"RayMeta", l_raylib_Ray_meta},
  {"RayHitInfo", l_raylib_RayHitInfo_new},
  {"RayHitInfoMeta", l_raylib_RayHitInfo_meta},
  {"Rectangle", l_raylib_Rectangle_new},
  {"RectangleMeta", l_raylib_Rectangle_meta},
  {"RenderTexture2D", l_raylib_RenderTexture2D_new},
  {"RenderTexture2DMeta", l_raylib_RenderTexture2D_meta},
  {"Shader", l_raylib_Shader_new},
  {"ShaderMeta", l_raylib_Shader_meta},
  {"Sound", l_raylib_Sound_new},
  {"SoundMeta", l_raylib_Sound_meta},
  {"Texture2D", l_raylib_Texture2D_new},
  {"Texture2DMeta", l_raylib_Texture2D_meta},
  {"Transform", l_raylib_Transform_new},
  {"TransformMeta", l_raylib_Transform_meta},
  {"Vector2", l_raylib_Vector2_new},
  {"Vector2Meta", l_raylib_Vector2_meta},
  {"Vector3", l_raylib_Vector3_new},
  {"Vector3Meta", l_raylib_Vector3_meta},
  {"Vector4", l_raylib_Vector4_new},
  {"Vector4Meta", l_raylib_Vector4_meta},
  {"VrDeviceInfo", l_raylib_VrDeviceInfo_new},
  {"VrDeviceInfoMeta", l_raylib_VrDeviceInfo_meta},
  {"Wave", l_raylib_Wave_new},
  {"WaveMeta", l_raylib_Wave_meta},
  {NULL, NULL}
};

static int l_raylib_AudioStream_set_sampleRate(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int sampleRate = luaL_checkinteger(L, 2);
  obj->sampleRate = sampleRate;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_sampleRate(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int result = obj->sampleRate;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_sampleSize(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int sampleSize = luaL_checkinteger(L, 2);
  obj->sampleSize = sampleSize;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_sampleSize(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int result = obj->sampleSize;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_channels(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int channels = luaL_checkinteger(L, 2);
  obj->channels = channels;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_channels(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int result = obj->channels;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_audioBuffer(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  void* audioBuffer = luaX_checklightuserdata(L, 2, "?");
  obj->audioBuffer = audioBuffer;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_audioBuffer(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  void* result = obj->audioBuffer;
  if (result == NULL) lua_pushnil(L); else lua_pushlightuserdata(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_format(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  int format = luaL_checkinteger(L, 2);
  obj->format = format;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_format(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  int result = obj->format;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_source(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int source = luaL_checkinteger(L, 2);
  obj->source = source;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_source(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  unsigned int result = obj->source;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_AudioStream_set_bufferAt(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 2) return luaL_error(L, "Index out of bounds %d", idx, 2);
  unsigned int buffersv = luaL_checkinteger(L, 3);
  obj->buffers[idx] = buffersv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_AudioStream_get_bufferAt(lua_State *L) {
  AudioStream* obj = luaL_checkudata(L, 1, "AudioStream");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 2) return luaL_error(L, "Index out of bounds %d", idx, 2);
  unsigned int result = obj->buffers[idx];
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_AudioStream[] = {
  {"getSampleRate", l_raylib_AudioStream_get_sampleRate},
  {"setSampleRate", l_raylib_AudioStream_set_sampleRate},
  {"getSampleSize", l_raylib_AudioStream_get_sampleSize},
  {"setSampleSize", l_raylib_AudioStream_set_sampleSize},
  {"getChannels", l_raylib_AudioStream_get_channels},
  {"setChannels", l_raylib_AudioStream_set_channels},
  {"getAudioBuffer", l_raylib_AudioStream_get_audioBuffer},
  {"setAudioBuffer", l_raylib_AudioStream_set_audioBuffer},
  {"getFormat", l_raylib_AudioStream_get_format},
  {"setFormat", l_raylib_AudioStream_set_format},
  {"getSource", l_raylib_AudioStream_get_source},
  {"setSource", l_raylib_AudioStream_set_source},
  {"getBufferAt", l_raylib_AudioStream_get_bufferAt},
  {"setBufferAt", l_raylib_AudioStream_set_bufferAt},
  {NULL, NULL}
};

static void l_raylib_AudioStream_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "AudioStream");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_AudioStream, 0);
  lua_pop(L, 1);
}

static int l_raylib_BoneInfo_set_nameAt(lua_State *L) {
  BoneInfo* obj = luaL_checkudata(L, 1, "BoneInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 32) return luaL_error(L, "Index out of bounds %d", idx, 32);
  char namev = luaL_checkinteger(L, 3);
  obj->name[idx] = namev;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_BoneInfo_get_nameAt(lua_State *L) {
  BoneInfo* obj = luaL_checkudata(L, 1, "BoneInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 32) return luaL_error(L, "Index out of bounds %d", idx, 32);
  char result = obj->name[idx];
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_BoneInfo_set_parent(lua_State *L) {
  BoneInfo* obj = luaL_checkudata(L, 1, "BoneInfo");
  int parent = luaL_checkinteger(L, 2);
  obj->parent = parent;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_BoneInfo_get_parent(lua_State *L) {
  BoneInfo* obj = luaL_checkudata(L, 1, "BoneInfo");
  int result = obj->parent;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_BoneInfo[] = {
  {"getNameAt", l_raylib_BoneInfo_get_nameAt},
  {"setNameAt", l_raylib_BoneInfo_set_nameAt},
  {"getParent", l_raylib_BoneInfo_get_parent},
  {"setParent", l_raylib_BoneInfo_set_parent},
  {NULL, NULL}
};

static void l_raylib_BoneInfo_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "BoneInfo");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_BoneInfo, 0);
  lua_pop(L, 1);
}

static int l_raylib_BoundingBox_set_min(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 min = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->min = min;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_BoundingBox_get_min(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 result = obj->min;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_BoundingBox_set_minU(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 min = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->min = min;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_BoundingBox_get_minU(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 result = obj->min;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_BoundingBox_set_max(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 max = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->max = max;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_BoundingBox_get_max(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 result = obj->max;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_BoundingBox_set_maxU(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 max = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->max = max;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_BoundingBox_get_maxU(lua_State *L) {
  BoundingBox* obj = luaL_checkudata(L, 1, "BoundingBox");
  Vector3 result = obj->max;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static const luaL_Reg l_raylib_BoundingBox[] = {
  {"getMin", l_raylib_BoundingBox_get_min},
  {"setMin", l_raylib_BoundingBox_set_min},
  {"getMinU", l_raylib_BoundingBox_get_minU},
  {"setMinU", l_raylib_BoundingBox_set_minU},
  {"getMax", l_raylib_BoundingBox_get_max},
  {"setMax", l_raylib_BoundingBox_set_max},
  {"getMaxU", l_raylib_BoundingBox_get_maxU},
  {"setMaxU", l_raylib_BoundingBox_set_maxU},
  {NULL, NULL}
};

static void l_raylib_BoundingBox_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "BoundingBox");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_BoundingBox, 0);
  lua_pop(L, 1);
}

static int l_raylib_Camera2D_set_offset(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 offset = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  obj->offset = offset;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera2D_get_offset(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 result = obj->offset;
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_raylib_Camera2D_set_offsetU(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 offset = {luaL_checknumber(L, 2), luaL_checknumber(L, 3)};
  obj->offset = offset;
  lua_pop(L, 2);
  return 1;
}

static int l_raylib_Camera2D_get_offsetU(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 result = obj->offset;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_raylib_Camera2D_set_target(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 target = (*(Vector2*)luaL_checkudata(L, 2, "Vector2"));
  obj->target = target;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera2D_get_target(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 result = obj->target;
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_raylib_Camera2D_set_targetU(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 target = {luaL_checknumber(L, 2), luaL_checknumber(L, 3)};
  obj->target = target;
  lua_pop(L, 2);
  return 1;
}

static int l_raylib_Camera2D_get_targetU(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  Vector2 result = obj->target;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_raylib_Camera2D_set_rotation(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  float rotation = luaL_checknumber(L, 2);
  obj->rotation = rotation;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera2D_get_rotation(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  float result = obj->rotation;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Camera2D_set_zoom(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  float zoom = luaL_checknumber(L, 2);
  obj->zoom = zoom;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera2D_get_zoom(lua_State *L) {
  Camera2D* obj = luaL_checkudata(L, 1, "Camera2D");
  float result = obj->zoom;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Camera2D[] = {
  {"getOffset", l_raylib_Camera2D_get_offset},
  {"setOffset", l_raylib_Camera2D_set_offset},
  {"getOffsetU", l_raylib_Camera2D_get_offsetU},
  {"setOffsetU", l_raylib_Camera2D_set_offsetU},
  {"getTarget", l_raylib_Camera2D_get_target},
  {"setTarget", l_raylib_Camera2D_set_target},
  {"getTargetU", l_raylib_Camera2D_get_targetU},
  {"setTargetU", l_raylib_Camera2D_set_targetU},
  {"getRotation", l_raylib_Camera2D_get_rotation},
  {"setRotation", l_raylib_Camera2D_set_rotation},
  {"getZoom", l_raylib_Camera2D_get_zoom},
  {"setZoom", l_raylib_Camera2D_set_zoom},
  {NULL, NULL}
};

static void l_raylib_Camera2D_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Camera2D");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Camera2D, 0);
  lua_pop(L, 1);
}

static int l_raylib_Camera3D_set_position(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->position = position;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera3D_get_position(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->position;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Camera3D_set_positionU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 position = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->position = position;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Camera3D_get_positionU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->position;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_Camera3D_set_target(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 target = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->target = target;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera3D_get_target(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->target;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Camera3D_set_targetU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 target = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->target = target;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Camera3D_get_targetU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->target;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_Camera3D_set_up(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 up = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->up = up;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera3D_get_up(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->up;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Camera3D_set_upU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 up = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->up = up;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Camera3D_get_upU(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  Vector3 result = obj->up;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_Camera3D_set_fovy(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  float fovy = luaL_checknumber(L, 2);
  obj->fovy = fovy;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera3D_get_fovy(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  float result = obj->fovy;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Camera3D_set_type(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  int type = luaL_checkinteger(L, 2);
  obj->type = type;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Camera3D_get_type(lua_State *L) {
  Camera3D* obj = luaL_checkudata(L, 1, "Camera3D");
  int result = obj->type;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Camera3D[] = {
  {"getPosition", l_raylib_Camera3D_get_position},
  {"setPosition", l_raylib_Camera3D_set_position},
  {"getPositionU", l_raylib_Camera3D_get_positionU},
  {"setPositionU", l_raylib_Camera3D_set_positionU},
  {"getTarget", l_raylib_Camera3D_get_target},
  {"setTarget", l_raylib_Camera3D_set_target},
  {"getTargetU", l_raylib_Camera3D_get_targetU},
  {"setTargetU", l_raylib_Camera3D_set_targetU},
  {"getUp", l_raylib_Camera3D_get_up},
  {"setUp", l_raylib_Camera3D_set_up},
  {"getUpU", l_raylib_Camera3D_get_upU},
  {"setUpU", l_raylib_Camera3D_set_upU},
  {"getFovy", l_raylib_Camera3D_get_fovy},
  {"setFovy", l_raylib_Camera3D_set_fovy},
  {"getType", l_raylib_Camera3D_get_type},
  {"setType", l_raylib_Camera3D_set_type},
  {NULL, NULL}
};

static void l_raylib_Camera3D_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Camera3D");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Camera3D, 0);
  lua_pop(L, 1);
}

static int l_raylib_CharInfo_set_value(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int value = luaL_checkinteger(L, 2);
  obj->value = value;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_value(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int result = obj->value;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_CharInfo_set_rec(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  Rectangle rec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  obj->rec = rec;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_rec(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  Rectangle result = obj->rec;
  Rectangle* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Rectangle");
  return 1;
}

static int l_raylib_CharInfo_set_recU(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  Rectangle rec = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5)};
  obj->rec = rec;
  lua_pop(L, 4);
  return 1;
}

static int l_raylib_CharInfo_get_recU(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  Rectangle result = obj->rec;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.width);lua_pushnumber(L, result.height);
  return 4;
}

static int l_raylib_CharInfo_set_offsetX(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int offsetX = luaL_checkinteger(L, 2);
  obj->offsetX = offsetX;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_offsetX(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int result = obj->offsetX;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_CharInfo_set_offsetY(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int offsetY = luaL_checkinteger(L, 2);
  obj->offsetY = offsetY;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_offsetY(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int result = obj->offsetY;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_CharInfo_set_advanceX(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int advanceX = luaL_checkinteger(L, 2);
  obj->advanceX = advanceX;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_advanceX(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int result = obj->advanceX;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_CharInfo_set_dataAt(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned char datav = luaL_checkinteger(L, 3);
  obj->data[idx] = datav;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_CharInfo_get_dataAt(lua_State *L) {
  CharInfo* obj = luaL_checkudata(L, 1, "CharInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned char result = obj->data[idx];
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_CharInfo[] = {
  {"getValue", l_raylib_CharInfo_get_value},
  {"setValue", l_raylib_CharInfo_set_value},
  {"getRec", l_raylib_CharInfo_get_rec},
  {"setRec", l_raylib_CharInfo_set_rec},
  {"getRecU", l_raylib_CharInfo_get_recU},
  {"setRecU", l_raylib_CharInfo_set_recU},
  {"getOffsetX", l_raylib_CharInfo_get_offsetX},
  {"setOffsetX", l_raylib_CharInfo_set_offsetX},
  {"getOffsetY", l_raylib_CharInfo_get_offsetY},
  {"setOffsetY", l_raylib_CharInfo_set_offsetY},
  {"getAdvanceX", l_raylib_CharInfo_get_advanceX},
  {"setAdvanceX", l_raylib_CharInfo_set_advanceX},
  {"getDataAt", l_raylib_CharInfo_get_dataAt},
  {"setDataAt", l_raylib_CharInfo_set_dataAt},
  {NULL, NULL}
};

static void l_raylib_CharInfo_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "CharInfo");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_CharInfo, 0);
  lua_pop(L, 1);
}

static int l_raylib_Color__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Color *self = lua_touserdata(L, 1);
    Color *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->r == other->r && self->g == other->g && self->b == other->b && self->a == other->a);
  }
  return 1;
}

static int l_raylib_Color_unpack(lua_State *L) {
  Color *self = luaL_checkudata(L, 1, "Color");
  lua_pushinteger(L, self->r);
  lua_pushinteger(L, self->g);
  lua_pushinteger(L, self->b);
  lua_pushinteger(L, self->a);
  return 4;
}

static int l_raylib_Color_set_r(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char r = luaL_checkinteger(L, 2);
  obj->r = r;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Color_get_r(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char result = obj->r;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Color_set_g(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char g = luaL_checkinteger(L, 2);
  obj->g = g;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Color_get_g(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char result = obj->g;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Color_set_b(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char b = luaL_checkinteger(L, 2);
  obj->b = b;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Color_get_b(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char result = obj->b;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Color_set_a(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char a = luaL_checkinteger(L, 2);
  obj->a = a;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Color_get_a(lua_State *L) {
  Color* obj = luaL_checkudata(L, 1, "Color");
  unsigned char result = obj->a;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Color[] = {
  {"getR", l_raylib_Color_get_r},
  {"setR", l_raylib_Color_set_r},
  {"getG", l_raylib_Color_get_g},
  {"setG", l_raylib_Color_set_g},
  {"getB", l_raylib_Color_get_b},
  {"setB", l_raylib_Color_set_b},
  {"getA", l_raylib_Color_get_a},
  {"setA", l_raylib_Color_set_a},
  {"__eq", l_raylib_Color__eq},
  {"unpack", l_raylib_Color_unpack},
  {NULL, NULL}
};

static void l_raylib_Color_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Color");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Color, 0);
  lua_pop(L, 1);
}

static int l_raylib_Font_set_texture(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  obj->texture = texture;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Font_get_texture(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  Texture2D result = obj->texture;
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

static int l_raylib_Font_set_textureU(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  Texture2D texture = {luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4), luaL_checkinteger(L, 5), luaL_checkinteger(L, 6)};
  obj->texture = texture;
  lua_pop(L, 5);
  return 1;
}

static int l_raylib_Font_get_textureU(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  Texture2D result = obj->texture;
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

static int l_raylib_Font_set_baseSize(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int baseSize = luaL_checkinteger(L, 2);
  obj->baseSize = baseSize;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Font_get_baseSize(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int result = obj->baseSize;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Font_set_charsCount(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int charsCount = luaL_checkinteger(L, 2);
  obj->charsCount = charsCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Font_get_charsCount(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int result = obj->charsCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Font_set_charAt(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->charsCount) return luaL_error(L, "Index out of bounds %d", idx);
  CharInfo charsv = (*(CharInfo*)luaL_checkudata(L, 3, "CharInfo"));
  obj->chars[idx] = charsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Font_get_charAt(lua_State *L) {
  Font* obj = luaL_checkudata(L, 1, "Font");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->charsCount) return luaL_error(L, "Index out of bounds %d", idx);
  CharInfo result = obj->chars[idx];
  CharInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "CharInfo");
  return 1;
}

static const luaL_Reg l_raylib_Font[] = {
  {"getTexture", l_raylib_Font_get_texture},
  {"setTexture", l_raylib_Font_set_texture},
  {"getTextureU", l_raylib_Font_get_textureU},
  {"setTextureU", l_raylib_Font_set_textureU},
  {"getBaseSize", l_raylib_Font_get_baseSize},
  {"setBaseSize", l_raylib_Font_set_baseSize},
  {"getCharsCount", l_raylib_Font_get_charsCount},
  {"setCharsCount", l_raylib_Font_set_charsCount},
  {"getCharAt", l_raylib_Font_get_charAt},
  {"setCharAt", l_raylib_Font_set_charAt},
  {NULL, NULL}
};

static void l_raylib_Font_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Font");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Font, 0);
  lua_pop(L, 1);
}

static int l_raylib_IVector2__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    IVector2 *self = lua_touserdata(L, 1);
    IVector2 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y);
  }
  return 1;
}

static int l_raylib_IVector2_unpack(lua_State *L) {
  IVector2 *self = luaL_checkudata(L, 1, "IVector2");
  lua_pushinteger(L, self->x);
  lua_pushinteger(L, self->y);
  return 2;
}

static int l_raylib_IVector2_set_x(lua_State *L) {
  IVector2* obj = luaL_checkudata(L, 1, "IVector2");
  int x = luaL_checkinteger(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector2_get_x(lua_State *L) {
  IVector2* obj = luaL_checkudata(L, 1, "IVector2");
  int result = obj->x;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector2_set_y(lua_State *L) {
  IVector2* obj = luaL_checkudata(L, 1, "IVector2");
  int y = luaL_checkinteger(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector2_get_y(lua_State *L) {
  IVector2* obj = luaL_checkudata(L, 1, "IVector2");
  int result = obj->y;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_IVector2[] = {
  {"getX", l_raylib_IVector2_get_x},
  {"setX", l_raylib_IVector2_set_x},
  {"getY", l_raylib_IVector2_get_y},
  {"setY", l_raylib_IVector2_set_y},
  {"__eq", l_raylib_IVector2__eq},
  {"unpack", l_raylib_IVector2_unpack},
  {NULL, NULL}
};

static void l_raylib_IVector2_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "IVector2");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_IVector2, 0);
  lua_pop(L, 1);
}

static int l_raylib_IVector3__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    IVector3 *self = lua_touserdata(L, 1);
    IVector3 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y && self->z == other->z);
  }
  return 1;
}

static int l_raylib_IVector3_unpack(lua_State *L) {
  IVector3 *self = luaL_checkudata(L, 1, "IVector3");
  lua_pushinteger(L, self->x);
  lua_pushinteger(L, self->y);
  lua_pushinteger(L, self->z);
  return 3;
}

static int l_raylib_IVector3_set_x(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int x = luaL_checkinteger(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector3_get_x(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int result = obj->x;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector3_set_y(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int y = luaL_checkinteger(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector3_get_y(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int result = obj->y;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector3_set_z(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int z = luaL_checkinteger(L, 2);
  obj->z = z;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector3_get_z(lua_State *L) {
  IVector3* obj = luaL_checkudata(L, 1, "IVector3");
  int result = obj->z;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_IVector3[] = {
  {"getX", l_raylib_IVector3_get_x},
  {"setX", l_raylib_IVector3_set_x},
  {"getY", l_raylib_IVector3_get_y},
  {"setY", l_raylib_IVector3_set_y},
  {"getZ", l_raylib_IVector3_get_z},
  {"setZ", l_raylib_IVector3_set_z},
  {"__eq", l_raylib_IVector3__eq},
  {"unpack", l_raylib_IVector3_unpack},
  {NULL, NULL}
};

static void l_raylib_IVector3_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "IVector3");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_IVector3, 0);
  lua_pop(L, 1);
}

static int l_raylib_IVector4__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    IVector4 *self = lua_touserdata(L, 1);
    IVector4 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y && self->z == other->z && self->w == other->w);
  }
  return 1;
}

static int l_raylib_IVector4_unpack(lua_State *L) {
  IVector4 *self = luaL_checkudata(L, 1, "IVector4");
  lua_pushinteger(L, self->x);
  lua_pushinteger(L, self->y);
  lua_pushinteger(L, self->z);
  lua_pushinteger(L, self->w);
  return 4;
}

static int l_raylib_IVector4_set_x(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int x = luaL_checkinteger(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector4_get_x(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int result = obj->x;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector4_set_y(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int y = luaL_checkinteger(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector4_get_y(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int result = obj->y;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector4_set_z(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int z = luaL_checkinteger(L, 2);
  obj->z = z;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector4_get_z(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int result = obj->z;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_IVector4_set_w(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int w = luaL_checkinteger(L, 2);
  obj->w = w;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_IVector4_get_w(lua_State *L) {
  IVector4* obj = luaL_checkudata(L, 1, "IVector4");
  int result = obj->w;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_IVector4[] = {
  {"getX", l_raylib_IVector4_get_x},
  {"setX", l_raylib_IVector4_set_x},
  {"getY", l_raylib_IVector4_get_y},
  {"setY", l_raylib_IVector4_set_y},
  {"getZ", l_raylib_IVector4_get_z},
  {"setZ", l_raylib_IVector4_set_z},
  {"getW", l_raylib_IVector4_get_w},
  {"setW", l_raylib_IVector4_set_w},
  {"__eq", l_raylib_IVector4__eq},
  {"unpack", l_raylib_IVector4_unpack},
  {NULL, NULL}
};

static void l_raylib_IVector4_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "IVector4");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_IVector4, 0);
  lua_pop(L, 1);
}

static int l_raylib_Image_set_data(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  void* data = luaX_checklightuserdata(L, 2, "?");
  obj->data = data;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Image_get_data(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  void* result = obj->data;
  if (result == NULL) lua_pushnil(L); else lua_pushlightuserdata(L, result);
  return 1;
}

static int l_raylib_Image_set_width(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int width = luaL_checkinteger(L, 2);
  obj->width = width;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Image_get_width(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int result = obj->width;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Image_set_height(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int height = luaL_checkinteger(L, 2);
  obj->height = height;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Image_get_height(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int result = obj->height;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Image_set_mipmaps(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int mipmaps = luaL_checkinteger(L, 2);
  obj->mipmaps = mipmaps;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Image_get_mipmaps(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int result = obj->mipmaps;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Image_set_format(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int format = luaL_checkinteger(L, 2);
  obj->format = format;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Image_get_format(lua_State *L) {
  Image* obj = luaL_checkudata(L, 1, "Image");
  int result = obj->format;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Image[] = {
  {"getData", l_raylib_Image_get_data},
  {"setData", l_raylib_Image_set_data},
  {"getWidth", l_raylib_Image_get_width},
  {"setWidth", l_raylib_Image_set_width},
  {"getHeight", l_raylib_Image_get_height},
  {"setHeight", l_raylib_Image_set_height},
  {"getMipmaps", l_raylib_Image_get_mipmaps},
  {"setMipmaps", l_raylib_Image_set_mipmaps},
  {"getFormat", l_raylib_Image_get_format},
  {"setFormat", l_raylib_Image_set_format},
  {NULL, NULL}
};

static void l_raylib_Image_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Image");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Image, 0);
  lua_pop(L, 1);
}

static int l_raylib_Material_set_shader(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  Shader shader = (*(Shader*)luaL_checkudata(L, 2, "Shader"));
  obj->shader = shader;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Material_get_shader(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  Shader result = obj->shader;
  Shader* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Shader");
  return 1;
}

static int l_raylib_Material_set_mapAt(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= MAX_MATERIAL_MAPS) return luaL_error(L, "Index out of bounds %d", idx, MAX_MATERIAL_MAPS);
  MaterialMap mapsv = (*(MaterialMap*)luaL_checkudata(L, 3, "MaterialMap"));
  obj->maps[idx] = mapsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Material_get_mapAt(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= MAX_MATERIAL_MAPS) return luaL_error(L, "Index out of bounds %d", idx, MAX_MATERIAL_MAPS);
  MaterialMap result = obj->maps[idx];
  MaterialMap* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "MaterialMap");
  return 1;
}

static int l_raylib_Material_set_paramAt(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float paramsv = luaL_checknumber(L, 3);
  obj->params[idx] = paramsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Material_get_paramAt(lua_State *L) {
  Material* obj = luaL_checkudata(L, 1, "Material");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->params[idx];
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Material[] = {
  {"getShader", l_raylib_Material_get_shader},
  {"setShader", l_raylib_Material_set_shader},
  {"getMapAt", l_raylib_Material_get_mapAt},
  {"setMapAt", l_raylib_Material_set_mapAt},
  {"getParamAt", l_raylib_Material_get_paramAt},
  {"setParamAt", l_raylib_Material_set_paramAt},
  {NULL, NULL}
};

static void l_raylib_Material_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Material");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Material, 0);
  lua_pop(L, 1);
}

static int l_raylib_MaterialMap_set_texture(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  obj->texture = texture;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_MaterialMap_get_texture(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Texture2D result = obj->texture;
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

static int l_raylib_MaterialMap_set_textureU(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Texture2D texture = {luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4), luaL_checkinteger(L, 5), luaL_checkinteger(L, 6)};
  obj->texture = texture;
  lua_pop(L, 5);
  return 1;
}

static int l_raylib_MaterialMap_get_textureU(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Texture2D result = obj->texture;
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

static int l_raylib_MaterialMap_set_color(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  obj->color = color;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_MaterialMap_get_color(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Color result = obj->color;
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

static int l_raylib_MaterialMap_set_colorU(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Color color = {luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4), luaL_checkinteger(L, 5)};
  obj->color = color;
  lua_pop(L, 4);
  return 1;
}

static int l_raylib_MaterialMap_get_colorU(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  Color result = obj->color;
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

static int l_raylib_MaterialMap_set_value(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  float value = luaL_checknumber(L, 2);
  obj->value = value;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_MaterialMap_get_value(lua_State *L) {
  MaterialMap* obj = luaL_checkudata(L, 1, "MaterialMap");
  float result = obj->value;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_MaterialMap[] = {
  {"getTexture", l_raylib_MaterialMap_get_texture},
  {"setTexture", l_raylib_MaterialMap_set_texture},
  {"getTextureU", l_raylib_MaterialMap_get_textureU},
  {"setTextureU", l_raylib_MaterialMap_set_textureU},
  {"getColor", l_raylib_MaterialMap_get_color},
  {"setColor", l_raylib_MaterialMap_set_color},
  {"getColorU", l_raylib_MaterialMap_get_colorU},
  {"setColorU", l_raylib_MaterialMap_set_colorU},
  {"getValue", l_raylib_MaterialMap_get_value},
  {"setValue", l_raylib_MaterialMap_set_value},
  {NULL, NULL}
};

static void l_raylib_MaterialMap_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "MaterialMap");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_MaterialMap, 0);
  lua_pop(L, 1);
}

static int l_raylib_Matrix__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Matrix *self = lua_touserdata(L, 1);
    Matrix *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->m0 == other->m0 && self->m4 == other->m4 && self->m8 == other->m8 && self->m12 == other->m12 && self->m1 == other->m1 && self->m5 == other->m5 && self->m9 == other->m9 && self->m13 == other->m13 && self->m2 == other->m2 && self->m6 == other->m6 && self->m10 == other->m10 && self->m14 == other->m14 && self->m3 == other->m3 && self->m7 == other->m7 && self->m11 == other->m11 && self->m15 == other->m15);
  }
  return 1;
}

static int l_raylib_Matrix_unpack(lua_State *L) {
  Matrix *self = luaL_checkudata(L, 1, "Matrix");
  lua_pushnumber(L, self->m0);
  lua_pushnumber(L, self->m4);
  lua_pushnumber(L, self->m8);
  lua_pushnumber(L, self->m12);
  lua_pushnumber(L, self->m1);
  lua_pushnumber(L, self->m5);
  lua_pushnumber(L, self->m9);
  lua_pushnumber(L, self->m13);
  lua_pushnumber(L, self->m2);
  lua_pushnumber(L, self->m6);
  lua_pushnumber(L, self->m10);
  lua_pushnumber(L, self->m14);
  lua_pushnumber(L, self->m3);
  lua_pushnumber(L, self->m7);
  lua_pushnumber(L, self->m11);
  lua_pushnumber(L, self->m15);
  return 16;
}

static int l_raylib_Matrix_set_m0(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m0 = luaL_checknumber(L, 2);
  obj->m0 = m0;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m0(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m0;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m4(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m4 = luaL_checknumber(L, 2);
  obj->m4 = m4;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m4(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m4;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m8(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m8 = luaL_checknumber(L, 2);
  obj->m8 = m8;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m8(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m8;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m12(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m12 = luaL_checknumber(L, 2);
  obj->m12 = m12;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m12(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m12;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m1(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m1 = luaL_checknumber(L, 2);
  obj->m1 = m1;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m1(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m1;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m5(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m5 = luaL_checknumber(L, 2);
  obj->m5 = m5;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m5(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m5;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m9(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m9 = luaL_checknumber(L, 2);
  obj->m9 = m9;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m9(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m9;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m13(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m13 = luaL_checknumber(L, 2);
  obj->m13 = m13;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m13(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m13;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m2(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m2 = luaL_checknumber(L, 2);
  obj->m2 = m2;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m2(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m2;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m6(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m6 = luaL_checknumber(L, 2);
  obj->m6 = m6;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m6(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m6;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m10(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m10 = luaL_checknumber(L, 2);
  obj->m10 = m10;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m10(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m10;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m14(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m14 = luaL_checknumber(L, 2);
  obj->m14 = m14;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m14(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m14;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m3(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m3 = luaL_checknumber(L, 2);
  obj->m3 = m3;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m3(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m3;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m7(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m7 = luaL_checknumber(L, 2);
  obj->m7 = m7;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m7(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m7;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m11(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m11 = luaL_checknumber(L, 2);
  obj->m11 = m11;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m11(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m11;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Matrix_set_m15(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float m15 = luaL_checknumber(L, 2);
  obj->m15 = m15;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Matrix_get_m15(lua_State *L) {
  Matrix* obj = luaL_checkudata(L, 1, "Matrix");
  float result = obj->m15;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Matrix[] = {
  {"getM0", l_raylib_Matrix_get_m0},
  {"setM0", l_raylib_Matrix_set_m0},
  {"getM4", l_raylib_Matrix_get_m4},
  {"setM4", l_raylib_Matrix_set_m4},
  {"getM8", l_raylib_Matrix_get_m8},
  {"setM8", l_raylib_Matrix_set_m8},
  {"getM12", l_raylib_Matrix_get_m12},
  {"setM12", l_raylib_Matrix_set_m12},
  {"getM1", l_raylib_Matrix_get_m1},
  {"setM1", l_raylib_Matrix_set_m1},
  {"getM5", l_raylib_Matrix_get_m5},
  {"setM5", l_raylib_Matrix_set_m5},
  {"getM9", l_raylib_Matrix_get_m9},
  {"setM9", l_raylib_Matrix_set_m9},
  {"getM13", l_raylib_Matrix_get_m13},
  {"setM13", l_raylib_Matrix_set_m13},
  {"getM2", l_raylib_Matrix_get_m2},
  {"setM2", l_raylib_Matrix_set_m2},
  {"getM6", l_raylib_Matrix_get_m6},
  {"setM6", l_raylib_Matrix_set_m6},
  {"getM10", l_raylib_Matrix_get_m10},
  {"setM10", l_raylib_Matrix_set_m10},
  {"getM14", l_raylib_Matrix_get_m14},
  {"setM14", l_raylib_Matrix_set_m14},
  {"getM3", l_raylib_Matrix_get_m3},
  {"setM3", l_raylib_Matrix_set_m3},
  {"getM7", l_raylib_Matrix_get_m7},
  {"setM7", l_raylib_Matrix_set_m7},
  {"getM11", l_raylib_Matrix_get_m11},
  {"setM11", l_raylib_Matrix_set_m11},
  {"getM15", l_raylib_Matrix_get_m15},
  {"setM15", l_raylib_Matrix_set_m15},
  {"__eq", l_raylib_Matrix__eq},
  {"unpack", l_raylib_Matrix_unpack},
  {NULL, NULL}
};

static void l_raylib_Matrix_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Matrix");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Matrix, 0);
  lua_pop(L, 1);
}

static int l_raylib_Mesh_set_vertexCount(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int vertexCount = luaL_checkinteger(L, 2);
  obj->vertexCount = vertexCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_vertexCount(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int result = obj->vertexCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_triangleCount(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int triangleCount = luaL_checkinteger(L, 2);
  obj->triangleCount = triangleCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_triangleCount(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int result = obj->triangleCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_vertexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->vertexCount) return luaL_error(L, "Index out of bounds %d", idx);
  float verticesv = luaL_checknumber(L, 3);
  obj->vertices[idx] = verticesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_vertexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->vertexCount) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->vertices[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_texcoordAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float texcoordsv = luaL_checknumber(L, 3);
  obj->texcoords[idx] = texcoordsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_texcoordAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->texcoords[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_texcoords2At(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float texcoords2v = luaL_checknumber(L, 3);
  obj->texcoords2[idx] = texcoords2v;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_texcoords2At(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->texcoords2[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_normalAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float normalsv = luaL_checknumber(L, 3);
  obj->normals[idx] = normalsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_normalAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->normals[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_tangentAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float tangentsv = luaL_checknumber(L, 3);
  obj->tangents[idx] = tangentsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_tangentAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->tangents[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_colorAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned char colorsv = luaL_checkinteger(L, 3);
  obj->colors[idx] = colorsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_colorAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned char result = obj->colors[idx];
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_indexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned short indicesv = luaL_checkinteger(L, 3);
  obj->indices[idx] = indicesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_indexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  unsigned short result = obj->indices[idx];
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_animVertexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float animVerticesv = luaL_checknumber(L, 3);
  obj->animVertices[idx] = animVerticesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_animVertexAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->animVertices[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_animNormalAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float animNormalsv = luaL_checknumber(L, 3);
  obj->animNormals[idx] = animNormalsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_animNormalAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->animNormals[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_boneIdAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  int boneIdsv = luaL_checkinteger(L, 3);
  obj->boneIds[idx] = boneIdsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_boneIdAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  int result = obj->boneIds[idx];
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_boneWeightAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float boneWeightsv = luaL_checknumber(L, 3);
  obj->boneWeights[idx] = boneWeightsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_boneWeightAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  float result = obj->boneWeights[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Mesh_set_vaoId(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  unsigned int vaoId = luaL_checkinteger(L, 2);
  obj->vaoId = vaoId;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_vaoId(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  unsigned int result = obj->vaoId;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Mesh_set_vboIdAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 7) return luaL_error(L, "Index out of bounds %d", idx, 7);
  unsigned int vboIdv = luaL_checkinteger(L, 3);
  obj->vboId[idx] = vboIdv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Mesh_get_vboIdAt(lua_State *L) {
  Mesh* obj = luaL_checkudata(L, 1, "Mesh");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 7) return luaL_error(L, "Index out of bounds %d", idx, 7);
  unsigned int result = obj->vboId[idx];
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Mesh[] = {
  {"getVertexCount", l_raylib_Mesh_get_vertexCount},
  {"setVertexCount", l_raylib_Mesh_set_vertexCount},
  {"getTriangleCount", l_raylib_Mesh_get_triangleCount},
  {"setTriangleCount", l_raylib_Mesh_set_triangleCount},
  {"getVertexAt", l_raylib_Mesh_get_vertexAt},
  {"setVertexAt", l_raylib_Mesh_set_vertexAt},
  {"getTexcoordAt", l_raylib_Mesh_get_texcoordAt},
  {"setTexcoordAt", l_raylib_Mesh_set_texcoordAt},
  {"getTexcoords2At", l_raylib_Mesh_get_texcoords2At},
  {"setTexcoords2At", l_raylib_Mesh_set_texcoords2At},
  {"getNormalAt", l_raylib_Mesh_get_normalAt},
  {"setNormalAt", l_raylib_Mesh_set_normalAt},
  {"getTangentAt", l_raylib_Mesh_get_tangentAt},
  {"setTangentAt", l_raylib_Mesh_set_tangentAt},
  {"getColorAt", l_raylib_Mesh_get_colorAt},
  {"setColorAt", l_raylib_Mesh_set_colorAt},
  {"getIndexAt", l_raylib_Mesh_get_indexAt},
  {"setIndexAt", l_raylib_Mesh_set_indexAt},
  {"getAnimVertexAt", l_raylib_Mesh_get_animVertexAt},
  {"setAnimVertexAt", l_raylib_Mesh_set_animVertexAt},
  {"getAnimNormalAt", l_raylib_Mesh_get_animNormalAt},
  {"setAnimNormalAt", l_raylib_Mesh_set_animNormalAt},
  {"getBoneIdAt", l_raylib_Mesh_get_boneIdAt},
  {"setBoneIdAt", l_raylib_Mesh_set_boneIdAt},
  {"getBoneWeightAt", l_raylib_Mesh_get_boneWeightAt},
  {"setBoneWeightAt", l_raylib_Mesh_set_boneWeightAt},
  {"getVaoId", l_raylib_Mesh_get_vaoId},
  {"setVaoId", l_raylib_Mesh_set_vaoId},
  {"getVboIdAt", l_raylib_Mesh_get_vboIdAt},
  {"setVboIdAt", l_raylib_Mesh_set_vboIdAt},
  {NULL, NULL}
};

static void l_raylib_Mesh_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Mesh");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Mesh, 0);
  lua_pop(L, 1);
}

static int l_raylib_Model_set_transform(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  Matrix transform = (*(Matrix*)luaL_checkudata(L, 2, "Matrix"));
  obj->transform = transform;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_transform(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  Matrix result = obj->transform;
  Matrix* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Matrix");
  return 1;
}

static int l_raylib_Model_set_transformU(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  Matrix transform = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6), luaL_checknumber(L, 7), luaL_checknumber(L, 8), luaL_checknumber(L, 9), luaL_checknumber(L, 10), luaL_checknumber(L, 11), luaL_checknumber(L, 12), luaL_checknumber(L, 13), luaL_checknumber(L, 14), luaL_checknumber(L, 15), luaL_checknumber(L, 16), luaL_checknumber(L, 17)};
  obj->transform = transform;
  lua_pop(L, 16);
  return 1;
}

static int l_raylib_Model_get_transformU(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  Matrix result = obj->transform;
  lua_pushnumber(L, result.m0);lua_pushnumber(L, result.m4);lua_pushnumber(L, result.m8);lua_pushnumber(L, result.m12);lua_pushnumber(L, result.m1);lua_pushnumber(L, result.m5);lua_pushnumber(L, result.m9);lua_pushnumber(L, result.m13);lua_pushnumber(L, result.m2);lua_pushnumber(L, result.m6);lua_pushnumber(L, result.m10);lua_pushnumber(L, result.m14);lua_pushnumber(L, result.m3);lua_pushnumber(L, result.m7);lua_pushnumber(L, result.m11);lua_pushnumber(L, result.m15);
  return 16;
}

static int l_raylib_Model_set_meshCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int meshCount = luaL_checkinteger(L, 2);
  obj->meshCount = meshCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_meshCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int result = obj->meshCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Model_set_meshAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->meshCount) return luaL_error(L, "Index out of bounds %d", idx);
  Mesh meshesv = (*(Mesh*)luaL_checkudata(L, 3, "Mesh"));
  obj->meshes[idx] = meshesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_meshAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->meshCount) return luaL_error(L, "Index out of bounds %d", idx);
  Mesh result = obj->meshes[idx];
  Mesh* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Mesh");
  return 1;
}

static int l_raylib_Model_set_materialCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int materialCount = luaL_checkinteger(L, 2);
  obj->materialCount = materialCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_materialCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int result = obj->materialCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Model_set_materialAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->materialCount) return luaL_error(L, "Index out of bounds %d", idx);
  Material materialsv = (*(Material*)luaL_checkudata(L, 3, "Material"));
  obj->materials[idx] = materialsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_materialAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->materialCount) return luaL_error(L, "Index out of bounds %d", idx);
  Material result = obj->materials[idx];
  Material* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Material");
  return 1;
}

static int l_raylib_Model_set_meshMaterialAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  int meshMaterialv = luaL_checkinteger(L, 3);
  obj->meshMaterial[idx] = meshMaterialv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_meshMaterialAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  int result = obj->meshMaterial[idx];
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Model_set_boneCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int boneCount = luaL_checkinteger(L, 2);
  obj->boneCount = boneCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_boneCount(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int result = obj->boneCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Model_set_bonAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->boneCount) return luaL_error(L, "Index out of bounds %d", idx);
  BoneInfo bonesv = (*(BoneInfo*)luaL_checkudata(L, 3, "BoneInfo"));
  obj->bones[idx] = bonesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_bonAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->boneCount) return luaL_error(L, "Index out of bounds %d", idx);
  BoneInfo result = obj->bones[idx];
  BoneInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "BoneInfo");
  return 1;
}

static int l_raylib_Model_set_bindPoseAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  Transform bindPosev = (*(Transform*)luaL_checkudata(L, 3, "Transform"));
  obj->bindPose[idx] = bindPosev;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Model_get_bindPoseAt(lua_State *L) {
  Model* obj = luaL_checkudata(L, 1, "Model");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  Transform result = obj->bindPose[idx];
  Transform* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Transform");
  return 1;
}

static const luaL_Reg l_raylib_Model[] = {
  {"getTransform", l_raylib_Model_get_transform},
  {"setTransform", l_raylib_Model_set_transform},
  {"getTransformU", l_raylib_Model_get_transformU},
  {"setTransformU", l_raylib_Model_set_transformU},
  {"getMeshCount", l_raylib_Model_get_meshCount},
  {"setMeshCount", l_raylib_Model_set_meshCount},
  {"getMeshAt", l_raylib_Model_get_meshAt},
  {"setMeshAt", l_raylib_Model_set_meshAt},
  {"getMaterialCount", l_raylib_Model_get_materialCount},
  {"setMaterialCount", l_raylib_Model_set_materialCount},
  {"getMaterialAt", l_raylib_Model_get_materialAt},
  {"setMaterialAt", l_raylib_Model_set_materialAt},
  {"getMeshMaterialAt", l_raylib_Model_get_meshMaterialAt},
  {"setMeshMaterialAt", l_raylib_Model_set_meshMaterialAt},
  {"getBoneCount", l_raylib_Model_get_boneCount},
  {"setBoneCount", l_raylib_Model_set_boneCount},
  {"getBonAt", l_raylib_Model_get_bonAt},
  {"setBonAt", l_raylib_Model_set_bonAt},
  {"getBindPoseAt", l_raylib_Model_get_bindPoseAt},
  {"setBindPoseAt", l_raylib_Model_set_bindPoseAt},
  {NULL, NULL}
};

static void l_raylib_Model_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Model");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Model, 0);
  lua_pop(L, 1);
}

static int l_raylib_ModelAnimation_set_boneCount(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int boneCount = luaL_checkinteger(L, 2);
  obj->boneCount = boneCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_ModelAnimation_get_boneCount(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int result = obj->boneCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_ModelAnimation_set_bonAt(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->boneCount) return luaL_error(L, "Index out of bounds %d", idx);
  BoneInfo bonesv = (*(BoneInfo*)luaL_checkudata(L, 3, "BoneInfo"));
  obj->bones[idx] = bonesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_ModelAnimation_get_bonAt(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= obj->boneCount) return luaL_error(L, "Index out of bounds %d", idx);
  BoneInfo result = obj->bones[idx];
  BoneInfo* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "BoneInfo");
  return 1;
}

static int l_raylib_ModelAnimation_set_frameCount(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int frameCount = luaL_checkinteger(L, 2);
  obj->frameCount = frameCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_ModelAnimation_get_frameCount(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int result = obj->frameCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_ModelAnimation_set_framePosAt(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  Transform* framePosesv = (Transform*)luaL_checkudata(L, 3, "Transform");
  obj->framePoses[idx] = framePosesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_ModelAnimation_get_framePosAt(lua_State *L) {
  ModelAnimation* obj = luaL_checkudata(L, 1, "ModelAnimation");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0) return luaL_error(L, "Index out of bounds %d", idx);
  Transform* result = obj->framePoses[idx];
  if (result == NULL) lua_pushnil(L); else { Transform* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = *result; luaL_setmetatable(L, "Transform");}
  return 1;
}

static const luaL_Reg l_raylib_ModelAnimation[] = {
  {"getBoneCount", l_raylib_ModelAnimation_get_boneCount},
  {"setBoneCount", l_raylib_ModelAnimation_set_boneCount},
  {"getBonAt", l_raylib_ModelAnimation_get_bonAt},
  {"setBonAt", l_raylib_ModelAnimation_set_bonAt},
  {"getFrameCount", l_raylib_ModelAnimation_get_frameCount},
  {"setFrameCount", l_raylib_ModelAnimation_set_frameCount},
  {"getFramePosAt", l_raylib_ModelAnimation_get_framePosAt},
  {"setFramePosAt", l_raylib_ModelAnimation_set_framePosAt},
  {NULL, NULL}
};

static void l_raylib_ModelAnimation_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "ModelAnimation");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_ModelAnimation, 0);
  lua_pop(L, 1);
}

static int l_raylib_NPatchInfo_set_sourceRec(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  Rectangle sourceRec = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  obj->sourceRec = sourceRec;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_sourceRec(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  Rectangle result = obj->sourceRec;
  Rectangle* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Rectangle");
  return 1;
}

static int l_raylib_NPatchInfo_set_sourceRecU(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  Rectangle sourceRec = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5)};
  obj->sourceRec = sourceRec;
  lua_pop(L, 4);
  return 1;
}

static int l_raylib_NPatchInfo_get_sourceRecU(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  Rectangle result = obj->sourceRec;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.width);lua_pushnumber(L, result.height);
  return 4;
}

static int l_raylib_NPatchInfo_set_left(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int left = luaL_checkinteger(L, 2);
  obj->left = left;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_left(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int result = obj->left;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_NPatchInfo_set_top(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int top = luaL_checkinteger(L, 2);
  obj->top = top;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_top(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int result = obj->top;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_NPatchInfo_set_right(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int right = luaL_checkinteger(L, 2);
  obj->right = right;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_right(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int result = obj->right;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_NPatchInfo_set_bottom(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int bottom = luaL_checkinteger(L, 2);
  obj->bottom = bottom;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_bottom(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int result = obj->bottom;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_NPatchInfo_set_type(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int type = luaL_checkinteger(L, 2);
  obj->type = type;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_NPatchInfo_get_type(lua_State *L) {
  NPatchInfo* obj = luaL_checkudata(L, 1, "NPatchInfo");
  int result = obj->type;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_NPatchInfo[] = {
  {"getSourceRec", l_raylib_NPatchInfo_get_sourceRec},
  {"setSourceRec", l_raylib_NPatchInfo_set_sourceRec},
  {"getSourceRecU", l_raylib_NPatchInfo_get_sourceRecU},
  {"setSourceRecU", l_raylib_NPatchInfo_set_sourceRecU},
  {"getLeft", l_raylib_NPatchInfo_get_left},
  {"setLeft", l_raylib_NPatchInfo_set_left},
  {"getTop", l_raylib_NPatchInfo_get_top},
  {"setTop", l_raylib_NPatchInfo_set_top},
  {"getRight", l_raylib_NPatchInfo_get_right},
  {"setRight", l_raylib_NPatchInfo_set_right},
  {"getBottom", l_raylib_NPatchInfo_get_bottom},
  {"setBottom", l_raylib_NPatchInfo_set_bottom},
  {"getType", l_raylib_NPatchInfo_get_type},
  {"setType", l_raylib_NPatchInfo_set_type},
  {NULL, NULL}
};

static void l_raylib_NPatchInfo_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "NPatchInfo");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_NPatchInfo, 0);
  lua_pop(L, 1);
}

static int l_raylib_Ray_set_position(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->position = position;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Ray_get_position(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 result = obj->position;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Ray_set_positionU(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 position = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->position = position;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Ray_get_positionU(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 result = obj->position;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_Ray_set_direction(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 direction = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->direction = direction;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Ray_get_direction(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 result = obj->direction;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Ray_set_directionU(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 direction = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->direction = direction;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Ray_get_directionU(lua_State *L) {
  Ray* obj = luaL_checkudata(L, 1, "Ray");
  Vector3 result = obj->direction;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static const luaL_Reg l_raylib_Ray[] = {
  {"getPosition", l_raylib_Ray_get_position},
  {"setPosition", l_raylib_Ray_set_position},
  {"getPositionU", l_raylib_Ray_get_positionU},
  {"setPositionU", l_raylib_Ray_set_positionU},
  {"getDirection", l_raylib_Ray_get_direction},
  {"setDirection", l_raylib_Ray_set_direction},
  {"getDirectionU", l_raylib_Ray_get_directionU},
  {"setDirectionU", l_raylib_Ray_set_directionU},
  {NULL, NULL}
};

static void l_raylib_Ray_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Ray");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Ray, 0);
  lua_pop(L, 1);
}

static int l_raylib_RayHitInfo_set_hit(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  bool hit = lua_toboolean(L, 2);
  obj->hit = hit;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RayHitInfo_get_hit(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  bool result = obj->hit;
  lua_pushboolean(L, result);
  return 1;
}

static int l_raylib_RayHitInfo_set_distance(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  float distance = luaL_checknumber(L, 2);
  obj->distance = distance;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RayHitInfo_get_distance(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  float result = obj->distance;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_RayHitInfo_set_position(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 position = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->position = position;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RayHitInfo_get_position(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 result = obj->position;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_RayHitInfo_set_positionU(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 position = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->position = position;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_RayHitInfo_get_positionU(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 result = obj->position;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_RayHitInfo_set_normal(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 normal = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->normal = normal;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RayHitInfo_get_normal(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 result = obj->normal;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_RayHitInfo_set_normalU(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 normal = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->normal = normal;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_RayHitInfo_get_normalU(lua_State *L) {
  RayHitInfo* obj = luaL_checkudata(L, 1, "RayHitInfo");
  Vector3 result = obj->normal;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static const luaL_Reg l_raylib_RayHitInfo[] = {
  {"getHit", l_raylib_RayHitInfo_get_hit},
  {"setHit", l_raylib_RayHitInfo_set_hit},
  {"getDistance", l_raylib_RayHitInfo_get_distance},
  {"setDistance", l_raylib_RayHitInfo_set_distance},
  {"getPosition", l_raylib_RayHitInfo_get_position},
  {"setPosition", l_raylib_RayHitInfo_set_position},
  {"getPositionU", l_raylib_RayHitInfo_get_positionU},
  {"setPositionU", l_raylib_RayHitInfo_set_positionU},
  {"getNormal", l_raylib_RayHitInfo_get_normal},
  {"setNormal", l_raylib_RayHitInfo_set_normal},
  {"getNormalU", l_raylib_RayHitInfo_get_normalU},
  {"setNormalU", l_raylib_RayHitInfo_set_normalU},
  {NULL, NULL}
};

static void l_raylib_RayHitInfo_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "RayHitInfo");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_RayHitInfo, 0);
  lua_pop(L, 1);
}

static int l_raylib_Rectangle__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Rectangle *self = lua_touserdata(L, 1);
    Rectangle *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y && self->width == other->width && self->height == other->height);
  }
  return 1;
}

static int l_raylib_Rectangle_unpack(lua_State *L) {
  Rectangle *self = luaL_checkudata(L, 1, "Rectangle");
  lua_pushnumber(L, self->x);
  lua_pushnumber(L, self->y);
  lua_pushnumber(L, self->width);
  lua_pushnumber(L, self->height);
  return 4;
}

static int l_raylib_Rectangle_set_x(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float x = luaL_checknumber(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Rectangle_get_x(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float result = obj->x;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Rectangle_set_y(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float y = luaL_checknumber(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Rectangle_get_y(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float result = obj->y;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Rectangle_set_width(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float width = luaL_checknumber(L, 2);
  obj->width = width;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Rectangle_get_width(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float result = obj->width;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Rectangle_set_height(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float height = luaL_checknumber(L, 2);
  obj->height = height;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Rectangle_get_height(lua_State *L) {
  Rectangle* obj = luaL_checkudata(L, 1, "Rectangle");
  float result = obj->height;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Rectangle[] = {
  {"getX", l_raylib_Rectangle_get_x},
  {"setX", l_raylib_Rectangle_set_x},
  {"getY", l_raylib_Rectangle_get_y},
  {"setY", l_raylib_Rectangle_set_y},
  {"getWidth", l_raylib_Rectangle_get_width},
  {"setWidth", l_raylib_Rectangle_set_width},
  {"getHeight", l_raylib_Rectangle_get_height},
  {"setHeight", l_raylib_Rectangle_set_height},
  {"__eq", l_raylib_Rectangle__eq},
  {"unpack", l_raylib_Rectangle_unpack},
  {NULL, NULL}
};

static void l_raylib_Rectangle_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Rectangle");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Rectangle, 0);
  lua_pop(L, 1);
}

static int l_raylib_RenderTexture2D_set_id(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  unsigned int id = luaL_checkinteger(L, 2);
  obj->id = id;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RenderTexture2D_get_id(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  unsigned int result = obj->id;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_RenderTexture2D_set_texture(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  obj->texture = texture;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RenderTexture2D_get_texture(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D result = obj->texture;
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

static int l_raylib_RenderTexture2D_set_textureU(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D texture = {luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4), luaL_checkinteger(L, 5), luaL_checkinteger(L, 6)};
  obj->texture = texture;
  lua_pop(L, 5);
  return 1;
}

static int l_raylib_RenderTexture2D_get_textureU(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D result = obj->texture;
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

static int l_raylib_RenderTexture2D_set_depth(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D depth = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  obj->depth = depth;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RenderTexture2D_get_depth(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D result = obj->depth;
  Texture2D* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Texture2D");
  return 1;
}

static int l_raylib_RenderTexture2D_set_depthU(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D depth = {luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4), luaL_checkinteger(L, 5), luaL_checkinteger(L, 6)};
  obj->depth = depth;
  lua_pop(L, 5);
  return 1;
}

static int l_raylib_RenderTexture2D_get_depthU(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  Texture2D result = obj->depth;
  lua_pushinteger(L, result.id);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);lua_pushinteger(L, result.mipmaps);lua_pushinteger(L, result.format);
  return 5;
}

static int l_raylib_RenderTexture2D_set_depthTexture(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  bool depthTexture = lua_toboolean(L, 2);
  obj->depthTexture = depthTexture;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_RenderTexture2D_get_depthTexture(lua_State *L) {
  RenderTexture2D* obj = luaL_checkudata(L, 1, "RenderTexture2D");
  bool result = obj->depthTexture;
  lua_pushboolean(L, result);
  return 1;
}

static const luaL_Reg l_raylib_RenderTexture2D[] = {
  {"getId", l_raylib_RenderTexture2D_get_id},
  {"setId", l_raylib_RenderTexture2D_set_id},
  {"getTexture", l_raylib_RenderTexture2D_get_texture},
  {"setTexture", l_raylib_RenderTexture2D_set_texture},
  {"getTextureU", l_raylib_RenderTexture2D_get_textureU},
  {"setTextureU", l_raylib_RenderTexture2D_set_textureU},
  {"getDepth", l_raylib_RenderTexture2D_get_depth},
  {"setDepth", l_raylib_RenderTexture2D_set_depth},
  {"getDepthU", l_raylib_RenderTexture2D_get_depthU},
  {"setDepthU", l_raylib_RenderTexture2D_set_depthU},
  {"getDepthTexture", l_raylib_RenderTexture2D_get_depthTexture},
  {"setDepthTexture", l_raylib_RenderTexture2D_set_depthTexture},
  {NULL, NULL}
};

static void l_raylib_RenderTexture2D_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "RenderTexture2D");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_RenderTexture2D, 0);
  lua_pop(L, 1);
}

static int l_raylib_Shader_set_id(lua_State *L) {
  Shader* obj = luaL_checkudata(L, 1, "Shader");
  unsigned int id = luaL_checkinteger(L, 2);
  obj->id = id;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Shader_get_id(lua_State *L) {
  Shader* obj = luaL_checkudata(L, 1, "Shader");
  unsigned int result = obj->id;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Shader_set_locAt(lua_State *L) {
  Shader* obj = luaL_checkudata(L, 1, "Shader");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= MAX_SHADER_LOCATIONS) return luaL_error(L, "Index out of bounds %d", idx, MAX_SHADER_LOCATIONS);
  int locsv = luaL_checkinteger(L, 3);
  obj->locs[idx] = locsv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Shader_get_locAt(lua_State *L) {
  Shader* obj = luaL_checkudata(L, 1, "Shader");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= MAX_SHADER_LOCATIONS) return luaL_error(L, "Index out of bounds %d", idx, MAX_SHADER_LOCATIONS);
  int result = obj->locs[idx];
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Shader[] = {
  {"getId", l_raylib_Shader_get_id},
  {"setId", l_raylib_Shader_set_id},
  {"getLocAt", l_raylib_Shader_get_locAt},
  {"setLocAt", l_raylib_Shader_set_locAt},
  {NULL, NULL}
};

static void l_raylib_Shader_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Shader");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Shader, 0);
  lua_pop(L, 1);
}

static int l_raylib_Sound_set_audioBuffer(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  void* audioBuffer = luaX_checklightuserdata(L, 2, "?");
  obj->audioBuffer = audioBuffer;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Sound_get_audioBuffer(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  void* result = obj->audioBuffer;
  if (result == NULL) lua_pushnil(L); else lua_pushlightuserdata(L, result);
  return 1;
}

static int l_raylib_Sound_set_source(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  unsigned int source = luaL_checkinteger(L, 2);
  obj->source = source;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Sound_get_source(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  unsigned int result = obj->source;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Sound_set_buffer(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  unsigned int buffer = luaL_checkinteger(L, 2);
  obj->buffer = buffer;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Sound_get_buffer(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  unsigned int result = obj->buffer;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Sound_set_format(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  int format = luaL_checkinteger(L, 2);
  obj->format = format;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Sound_get_format(lua_State *L) {
  Sound* obj = luaL_checkudata(L, 1, "Sound");
  int result = obj->format;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Sound[] = {
  {"getAudioBuffer", l_raylib_Sound_get_audioBuffer},
  {"setAudioBuffer", l_raylib_Sound_set_audioBuffer},
  {"getSource", l_raylib_Sound_get_source},
  {"setSource", l_raylib_Sound_set_source},
  {"getBuffer", l_raylib_Sound_get_buffer},
  {"setBuffer", l_raylib_Sound_set_buffer},
  {"getFormat", l_raylib_Sound_get_format},
  {"setFormat", l_raylib_Sound_set_format},
  {NULL, NULL}
};

static void l_raylib_Sound_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Sound");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Sound, 0);
  lua_pop(L, 1);
}

static int l_raylib_Texture2D__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Texture2D *self = lua_touserdata(L, 1);
    Texture2D *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->id == other->id && self->width == other->width && self->height == other->height && self->mipmaps == other->mipmaps && self->format == other->format);
  }
  return 1;
}

static int l_raylib_Texture2D_unpack(lua_State *L) {
  Texture2D *self = luaL_checkudata(L, 1, "Texture2D");
  lua_pushinteger(L, self->id);
  lua_pushinteger(L, self->width);
  lua_pushinteger(L, self->height);
  lua_pushinteger(L, self->mipmaps);
  lua_pushinteger(L, self->format);
  return 5;
}

static int l_raylib_Texture2D_set_id(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  unsigned int id = luaL_checkinteger(L, 2);
  obj->id = id;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Texture2D_get_id(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  unsigned int result = obj->id;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Texture2D_set_width(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int width = luaL_checkinteger(L, 2);
  obj->width = width;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Texture2D_get_width(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int result = obj->width;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Texture2D_set_height(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int height = luaL_checkinteger(L, 2);
  obj->height = height;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Texture2D_get_height(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int result = obj->height;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Texture2D_set_mipmaps(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int mipmaps = luaL_checkinteger(L, 2);
  obj->mipmaps = mipmaps;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Texture2D_get_mipmaps(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int result = obj->mipmaps;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Texture2D_set_format(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int format = luaL_checkinteger(L, 2);
  obj->format = format;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Texture2D_get_format(lua_State *L) {
  Texture2D* obj = luaL_checkudata(L, 1, "Texture2D");
  int result = obj->format;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Texture2D[] = {
  {"getId", l_raylib_Texture2D_get_id},
  {"setId", l_raylib_Texture2D_set_id},
  {"getWidth", l_raylib_Texture2D_get_width},
  {"setWidth", l_raylib_Texture2D_set_width},
  {"getHeight", l_raylib_Texture2D_get_height},
  {"setHeight", l_raylib_Texture2D_set_height},
  {"getMipmaps", l_raylib_Texture2D_get_mipmaps},
  {"setMipmaps", l_raylib_Texture2D_set_mipmaps},
  {"getFormat", l_raylib_Texture2D_get_format},
  {"setFormat", l_raylib_Texture2D_set_format},
  {"__eq", l_raylib_Texture2D__eq},
  {"unpack", l_raylib_Texture2D_unpack},
  {NULL, NULL}
};

static void l_raylib_Texture2D_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Texture2D");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Texture2D, 0);
  lua_pop(L, 1);
}

static int l_raylib_Transform_set_translation(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 translation = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->translation = translation;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Transform_get_translation(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 result = obj->translation;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Transform_set_translationU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 translation = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->translation = translation;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Transform_get_translationU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 result = obj->translation;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static int l_raylib_Transform_set_rotation(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector4 rotation = (*(Vector4*)luaL_checkudata(L, 2, "Vector4"));
  obj->rotation = rotation;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Transform_get_rotation(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector4 result = obj->rotation;
  Vector4* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector4");
  return 1;
}

static int l_raylib_Transform_set_rotationU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector4 rotation = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5)};
  obj->rotation = rotation;
  lua_pop(L, 4);
  return 1;
}

static int l_raylib_Transform_get_rotationU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector4 result = obj->rotation;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);lua_pushnumber(L, result.w);
  return 4;
}

static int l_raylib_Transform_set_scale(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 scale = (*(Vector3*)luaL_checkudata(L, 2, "Vector3"));
  obj->scale = scale;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Transform_get_scale(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 result = obj->scale;
  Vector3* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector3");
  return 1;
}

static int l_raylib_Transform_set_scaleU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 scale = {luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)};
  obj->scale = scale;
  lua_pop(L, 3);
  return 1;
}

static int l_raylib_Transform_get_scaleU(lua_State *L) {
  Transform* obj = luaL_checkudata(L, 1, "Transform");
  Vector3 result = obj->scale;
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);lua_pushnumber(L, result.z);
  return 3;
}

static const luaL_Reg l_raylib_Transform[] = {
  {"getTranslation", l_raylib_Transform_get_translation},
  {"setTranslation", l_raylib_Transform_set_translation},
  {"getTranslationU", l_raylib_Transform_get_translationU},
  {"setTranslationU", l_raylib_Transform_set_translationU},
  {"getRotation", l_raylib_Transform_get_rotation},
  {"setRotation", l_raylib_Transform_set_rotation},
  {"getRotationU", l_raylib_Transform_get_rotationU},
  {"setRotationU", l_raylib_Transform_set_rotationU},
  {"getScale", l_raylib_Transform_get_scale},
  {"setScale", l_raylib_Transform_set_scale},
  {"getScaleU", l_raylib_Transform_get_scaleU},
  {"setScaleU", l_raylib_Transform_set_scaleU},
  {NULL, NULL}
};

static void l_raylib_Transform_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Transform");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Transform, 0);
  lua_pop(L, 1);
}

static int l_raylib_Vector2__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Vector2 *self = lua_touserdata(L, 1);
    Vector2 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y);
  }
  return 1;
}

static int l_raylib_Vector2_unpack(lua_State *L) {
  Vector2 *self = luaL_checkudata(L, 1, "Vector2");
  lua_pushnumber(L, self->x);
  lua_pushnumber(L, self->y);
  return 2;
}

static int l_raylib_Vector2_set_x(lua_State *L) {
  Vector2* obj = luaL_checkudata(L, 1, "Vector2");
  float x = luaL_checknumber(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector2_get_x(lua_State *L) {
  Vector2* obj = luaL_checkudata(L, 1, "Vector2");
  float result = obj->x;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector2_set_y(lua_State *L) {
  Vector2* obj = luaL_checkudata(L, 1, "Vector2");
  float y = luaL_checknumber(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector2_get_y(lua_State *L) {
  Vector2* obj = luaL_checkudata(L, 1, "Vector2");
  float result = obj->y;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Vector2[] = {
  {"getX", l_raylib_Vector2_get_x},
  {"setX", l_raylib_Vector2_set_x},
  {"getY", l_raylib_Vector2_get_y},
  {"setY", l_raylib_Vector2_set_y},
  {"__eq", l_raylib_Vector2__eq},
  {"unpack", l_raylib_Vector2_unpack},
  {NULL, NULL}
};

static void l_raylib_Vector2_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Vector2");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Vector2, 0);
  lua_pop(L, 1);
}

static int l_raylib_Vector3__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Vector3 *self = lua_touserdata(L, 1);
    Vector3 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y && self->z == other->z);
  }
  return 1;
}

static int l_raylib_Vector3_unpack(lua_State *L) {
  Vector3 *self = luaL_checkudata(L, 1, "Vector3");
  lua_pushnumber(L, self->x);
  lua_pushnumber(L, self->y);
  lua_pushnumber(L, self->z);
  return 3;
}

static int l_raylib_Vector3_set_x(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float x = luaL_checknumber(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector3_get_x(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float result = obj->x;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector3_set_y(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float y = luaL_checknumber(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector3_get_y(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float result = obj->y;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector3_set_z(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float z = luaL_checknumber(L, 2);
  obj->z = z;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector3_get_z(lua_State *L) {
  Vector3* obj = luaL_checkudata(L, 1, "Vector3");
  float result = obj->z;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Vector3[] = {
  {"getX", l_raylib_Vector3_get_x},
  {"setX", l_raylib_Vector3_set_x},
  {"getY", l_raylib_Vector3_get_y},
  {"setY", l_raylib_Vector3_set_y},
  {"getZ", l_raylib_Vector3_get_z},
  {"setZ", l_raylib_Vector3_set_z},
  {"__eq", l_raylib_Vector3__eq},
  {"unpack", l_raylib_Vector3_unpack},
  {NULL, NULL}
};

static void l_raylib_Vector3_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Vector3");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Vector3, 0);
  lua_pop(L, 1);
}

static int l_raylib_Vector4__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    Vector4 *self = lua_touserdata(L, 1);
    Vector4 *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->x == other->x && self->y == other->y && self->z == other->z && self->w == other->w);
  }
  return 1;
}

static int l_raylib_Vector4_unpack(lua_State *L) {
  Vector4 *self = luaL_checkudata(L, 1, "Vector4");
  lua_pushnumber(L, self->x);
  lua_pushnumber(L, self->y);
  lua_pushnumber(L, self->z);
  lua_pushnumber(L, self->w);
  return 4;
}

static int l_raylib_Vector4_set_x(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float x = luaL_checknumber(L, 2);
  obj->x = x;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector4_get_x(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float result = obj->x;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector4_set_y(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float y = luaL_checknumber(L, 2);
  obj->y = y;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector4_get_y(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float result = obj->y;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector4_set_z(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float z = luaL_checknumber(L, 2);
  obj->z = z;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector4_get_z(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float result = obj->z;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_Vector4_set_w(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float w = luaL_checknumber(L, 2);
  obj->w = w;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Vector4_get_w(lua_State *L) {
  Vector4* obj = luaL_checkudata(L, 1, "Vector4");
  float result = obj->w;
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Vector4[] = {
  {"getX", l_raylib_Vector4_get_x},
  {"setX", l_raylib_Vector4_set_x},
  {"getY", l_raylib_Vector4_get_y},
  {"setY", l_raylib_Vector4_set_y},
  {"getZ", l_raylib_Vector4_get_z},
  {"setZ", l_raylib_Vector4_set_z},
  {"getW", l_raylib_Vector4_get_w},
  {"setW", l_raylib_Vector4_set_w},
  {"__eq", l_raylib_Vector4__eq},
  {"unpack", l_raylib_Vector4_unpack},
  {NULL, NULL}
};

static void l_raylib_Vector4_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Vector4");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Vector4, 0);
  lua_pop(L, 1);
}

static int l_raylib_VrDeviceInfo_set_hResolution(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int hResolution = luaL_checkinteger(L, 2);
  obj->hResolution = hResolution;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_hResolution(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int result = obj->hResolution;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_vResolution(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int vResolution = luaL_checkinteger(L, 2);
  obj->vResolution = vResolution;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_vResolution(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int result = obj->vResolution;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_hScreenSize(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float hScreenSize = luaL_checknumber(L, 2);
  obj->hScreenSize = hScreenSize;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_hScreenSize(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->hScreenSize;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_vScreenSize(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float vScreenSize = luaL_checknumber(L, 2);
  obj->vScreenSize = vScreenSize;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_vScreenSize(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->vScreenSize;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_vScreenCenter(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float vScreenCenter = luaL_checknumber(L, 2);
  obj->vScreenCenter = vScreenCenter;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_vScreenCenter(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->vScreenCenter;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_eyeToScreenDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float eyeToScreenDistance = luaL_checknumber(L, 2);
  obj->eyeToScreenDistance = eyeToScreenDistance;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_eyeToScreenDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->eyeToScreenDistance;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_lensSeparationDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float lensSeparationDistance = luaL_checknumber(L, 2);
  obj->lensSeparationDistance = lensSeparationDistance;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_lensSeparationDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->lensSeparationDistance;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_interpupillaryDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float interpupillaryDistance = luaL_checknumber(L, 2);
  obj->interpupillaryDistance = interpupillaryDistance;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_interpupillaryDistance(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  float result = obj->interpupillaryDistance;
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_lensDistortionValuAt(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 4) return luaL_error(L, "Index out of bounds %d", idx, 4);
  float lensDistortionValuesv = luaL_checknumber(L, 3);
  obj->lensDistortionValues[idx] = lensDistortionValuesv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_lensDistortionValuAt(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 4) return luaL_error(L, "Index out of bounds %d", idx, 4);
  float result = obj->lensDistortionValues[idx];
  lua_pushnumber(L, result);
  return 1;
}

static int l_raylib_VrDeviceInfo_set_chromaAbCorrectionAt(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 4) return luaL_error(L, "Index out of bounds %d", idx, 4);
  float chromaAbCorrectionv = luaL_checknumber(L, 3);
  obj->chromaAbCorrection[idx] = chromaAbCorrectionv;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_VrDeviceInfo_get_chromaAbCorrectionAt(lua_State *L) {
  VrDeviceInfo* obj = luaL_checkudata(L, 1, "VrDeviceInfo");
  int idx = luaL_checkinteger(L, 2);
  if (idx < 0 || idx >= 4) return luaL_error(L, "Index out of bounds %d", idx, 4);
  float result = obj->chromaAbCorrection[idx];
  lua_pushnumber(L, result);
  return 1;
}

static const luaL_Reg l_raylib_VrDeviceInfo[] = {
  {"getHResolution", l_raylib_VrDeviceInfo_get_hResolution},
  {"setHResolution", l_raylib_VrDeviceInfo_set_hResolution},
  {"getVResolution", l_raylib_VrDeviceInfo_get_vResolution},
  {"setVResolution", l_raylib_VrDeviceInfo_set_vResolution},
  {"getHScreenSize", l_raylib_VrDeviceInfo_get_hScreenSize},
  {"setHScreenSize", l_raylib_VrDeviceInfo_set_hScreenSize},
  {"getVScreenSize", l_raylib_VrDeviceInfo_get_vScreenSize},
  {"setVScreenSize", l_raylib_VrDeviceInfo_set_vScreenSize},
  {"getVScreenCenter", l_raylib_VrDeviceInfo_get_vScreenCenter},
  {"setVScreenCenter", l_raylib_VrDeviceInfo_set_vScreenCenter},
  {"getEyeToScreenDistance", l_raylib_VrDeviceInfo_get_eyeToScreenDistance},
  {"setEyeToScreenDistance", l_raylib_VrDeviceInfo_set_eyeToScreenDistance},
  {"getLensSeparationDistance", l_raylib_VrDeviceInfo_get_lensSeparationDistance},
  {"setLensSeparationDistance", l_raylib_VrDeviceInfo_set_lensSeparationDistance},
  {"getInterpupillaryDistance", l_raylib_VrDeviceInfo_get_interpupillaryDistance},
  {"setInterpupillaryDistance", l_raylib_VrDeviceInfo_set_interpupillaryDistance},
  {"getLensDistortionValuAt", l_raylib_VrDeviceInfo_get_lensDistortionValuAt},
  {"setLensDistortionValuAt", l_raylib_VrDeviceInfo_set_lensDistortionValuAt},
  {"getChromaAbCorrectionAt", l_raylib_VrDeviceInfo_get_chromaAbCorrectionAt},
  {"setChromaAbCorrectionAt", l_raylib_VrDeviceInfo_set_chromaAbCorrectionAt},
  {NULL, NULL}
};

static void l_raylib_VrDeviceInfo_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "VrDeviceInfo");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_VrDeviceInfo, 0);
  lua_pop(L, 1);
}

static int l_raylib_Wave_set_sampleCount(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int sampleCount = luaL_checkinteger(L, 2);
  obj->sampleCount = sampleCount;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Wave_get_sampleCount(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int result = obj->sampleCount;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Wave_set_sampleRate(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int sampleRate = luaL_checkinteger(L, 2);
  obj->sampleRate = sampleRate;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Wave_get_sampleRate(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int result = obj->sampleRate;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Wave_set_sampleSize(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int sampleSize = luaL_checkinteger(L, 2);
  obj->sampleSize = sampleSize;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Wave_get_sampleSize(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int result = obj->sampleSize;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Wave_set_channels(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int channels = luaL_checkinteger(L, 2);
  obj->channels = channels;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Wave_get_channels(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  unsigned int result = obj->channels;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raylib_Wave_set_data(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  void* data = luaX_checklightuserdata(L, 2, "?");
  obj->data = data;
  lua_pop(L, 1);
  return 1;
}

static int l_raylib_Wave_get_data(lua_State *L) {
  Wave* obj = luaL_checkudata(L, 1, "Wave");
  void* result = obj->data;
  if (result == NULL) lua_pushnil(L); else lua_pushlightuserdata(L, result);
  return 1;
}

static const luaL_Reg l_raylib_Wave[] = {
  {"getSampleCount", l_raylib_Wave_get_sampleCount},
  {"setSampleCount", l_raylib_Wave_set_sampleCount},
  {"getSampleRate", l_raylib_Wave_get_sampleRate},
  {"setSampleRate", l_raylib_Wave_set_sampleRate},
  {"getSampleSize", l_raylib_Wave_get_sampleSize},
  {"setSampleSize", l_raylib_Wave_set_sampleSize},
  {"getChannels", l_raylib_Wave_get_channels},
  {"setChannels", l_raylib_Wave_set_channels},
  {"getData", l_raylib_Wave_get_data},
  {"setData", l_raylib_Wave_set_data},
  {NULL, NULL}
};

static void l_raylib_Wave_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "Wave");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raylib_Wave, 0);
  lua_pop(L, 1);
}

LUAMOD_API int luaopen_raylib(lua_State *L) {
  luaL_newlib(L, l_raylib_functions);
  l_raylib_AudioStream_register(L, NULL);
  l_raylib_BoneInfo_register(L, NULL);
  l_raylib_BoundingBox_register(L, NULL);
  l_raylib_Camera2D_register(L, NULL);
  l_raylib_Camera3D_register(L, NULL);
  l_raylib_CharInfo_register(L, NULL);
  l_raylib_Color_register(L, NULL);
  l_raylib_Font_register(L, NULL);
  l_raylib_IVector2_register(L, NULL);
  l_raylib_IVector3_register(L, NULL);
  l_raylib_IVector4_register(L, NULL);
  l_raylib_Image_register(L, NULL);
  l_raylib_Material_register(L, NULL);
  l_raylib_MaterialMap_register(L, NULL);
  l_raylib_Matrix_register(L, NULL);
  l_raylib_Mesh_register(L, NULL);
  l_raylib_Model_register(L, NULL);
  l_raylib_ModelAnimation_register(L, NULL);
  l_raylib_NPatchInfo_register(L, NULL);
  l_raylib_Ray_register(L, NULL);
  l_raylib_RayHitInfo_register(L, NULL);
  l_raylib_Rectangle_register(L, NULL);
  l_raylib_RenderTexture2D_register(L, NULL);
  l_raylib_Shader_register(L, NULL);
  l_raylib_Sound_register(L, NULL);
  l_raylib_Texture2D_register(L, NULL);
  l_raylib_Transform_register(L, NULL);
  l_raylib_Vector2_register(L, NULL);
  l_raylib_Vector3_register(L, NULL);
  l_raylib_Vector4_register(L, NULL);
  l_raylib_VrDeviceInfo_register(L, NULL);
  l_raylib_Wave_register(L, NULL);
  lua_pushnumber(L, PI);
  lua_setfield(L, -2, "PI");
  lua_pushinteger(L, MAX_TOUCH_POINTS);
  lua_setfield(L, -2, "MAX_TOUCH_POINTS");
  lua_pushinteger(L, MAX_SHADER_LOCATIONS);
  lua_setfield(L, -2, "MAX_SHADER_LOCATIONS");
  lua_pushinteger(L, MAX_MATERIAL_MAPS);
  lua_setfield(L, -2, "MAX_MATERIAL_MAPS");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = LIGHTGRAY; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "LIGHTGRAY");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = GRAY; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "GRAY");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = DARKGRAY; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "DARKGRAY");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = YELLOW; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "YELLOW");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = GOLD; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "GOLD");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = ORANGE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "ORANGE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = PINK; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "PINK");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = RED; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "RED");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = MAROON; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "MAROON");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = GREEN; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "GREEN");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = LIME; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "LIME");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = DARKGREEN; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "DARKGREEN");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = SKYBLUE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "SKYBLUE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BLUE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BLUE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = DARKBLUE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "DARKBLUE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = PURPLE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "PURPLE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = VIOLET; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "VIOLET");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = DARKPURPLE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "DARKPURPLE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BEIGE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BEIGE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BROWN; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BROWN");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = DARKBROWN; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "DARKBROWN");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = WHITE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "WHITE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BLACK; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BLACK");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BLANK; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BLANK");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = MAGENTA; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "MAGENTA");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = RAYWHITE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "RAYWHITE");
  lua_pushinteger(L, FLAG_SHOW_LOGO);
  lua_setfield(L, -2, "FLAG_SHOW_LOGO");
  lua_pushinteger(L, FLAG_FULLSCREEN_MODE);
  lua_setfield(L, -2, "FLAG_FULLSCREEN_MODE");
  lua_pushinteger(L, FLAG_WINDOW_RESIZABLE);
  lua_setfield(L, -2, "FLAG_WINDOW_RESIZABLE");
  lua_pushinteger(L, FLAG_WINDOW_UNDECORATED);
  lua_setfield(L, -2, "FLAG_WINDOW_UNDECORATED");
  lua_pushinteger(L, FLAG_WINDOW_TRANSPARENT);
  lua_setfield(L, -2, "FLAG_WINDOW_TRANSPARENT");
  lua_pushinteger(L, FLAG_WINDOW_HIDDEN);
  lua_setfield(L, -2, "FLAG_WINDOW_HIDDEN");
  lua_pushinteger(L, FLAG_WINDOW_ALWAYS_RUN);
  lua_setfield(L, -2, "FLAG_WINDOW_ALWAYS_RUN");
  lua_pushinteger(L, FLAG_MSAA_4X_HINT);
  lua_setfield(L, -2, "FLAG_MSAA_4X_HINT");
  lua_pushinteger(L, FLAG_VSYNC_HINT);
  lua_setfield(L, -2, "FLAG_VSYNC_HINT");
  lua_pushinteger(L, LOG_ALL);
  lua_setfield(L, -2, "LOG_ALL");
  lua_pushinteger(L, LOG_TRACE);
  lua_setfield(L, -2, "LOG_TRACE");
  lua_pushinteger(L, LOG_DEBUG);
  lua_setfield(L, -2, "LOG_DEBUG");
  lua_pushinteger(L, LOG_INFO);
  lua_setfield(L, -2, "LOG_INFO");
  lua_pushinteger(L, LOG_WARNING);
  lua_setfield(L, -2, "LOG_WARNING");
  lua_pushinteger(L, LOG_ERROR);
  lua_setfield(L, -2, "LOG_ERROR");
  lua_pushinteger(L, LOG_FATAL);
  lua_setfield(L, -2, "LOG_FATAL");
  lua_pushinteger(L, LOG_NONE);
  lua_setfield(L, -2, "LOG_NONE");
  lua_pushinteger(L, KEY_APOSTROPHE);
  lua_setfield(L, -2, "KEY_APOSTROPHE");
  lua_pushinteger(L, KEY_COMMA);
  lua_setfield(L, -2, "KEY_COMMA");
  lua_pushinteger(L, KEY_MINUS);
  lua_setfield(L, -2, "KEY_MINUS");
  lua_pushinteger(L, KEY_PERIOD);
  lua_setfield(L, -2, "KEY_PERIOD");
  lua_pushinteger(L, KEY_SLASH);
  lua_setfield(L, -2, "KEY_SLASH");
  lua_pushinteger(L, KEY_ZERO);
  lua_setfield(L, -2, "KEY_ZERO");
  lua_pushinteger(L, KEY_ONE);
  lua_setfield(L, -2, "KEY_ONE");
  lua_pushinteger(L, KEY_TWO);
  lua_setfield(L, -2, "KEY_TWO");
  lua_pushinteger(L, KEY_THREE);
  lua_setfield(L, -2, "KEY_THREE");
  lua_pushinteger(L, KEY_FOUR);
  lua_setfield(L, -2, "KEY_FOUR");
  lua_pushinteger(L, KEY_FIVE);
  lua_setfield(L, -2, "KEY_FIVE");
  lua_pushinteger(L, KEY_SIX);
  lua_setfield(L, -2, "KEY_SIX");
  lua_pushinteger(L, KEY_SEVEN);
  lua_setfield(L, -2, "KEY_SEVEN");
  lua_pushinteger(L, KEY_EIGHT);
  lua_setfield(L, -2, "KEY_EIGHT");
  lua_pushinteger(L, KEY_NINE);
  lua_setfield(L, -2, "KEY_NINE");
  lua_pushinteger(L, KEY_SEMICOLON);
  lua_setfield(L, -2, "KEY_SEMICOLON");
  lua_pushinteger(L, KEY_EQUAL);
  lua_setfield(L, -2, "KEY_EQUAL");
  lua_pushinteger(L, KEY_A);
  lua_setfield(L, -2, "KEY_A");
  lua_pushinteger(L, KEY_B);
  lua_setfield(L, -2, "KEY_B");
  lua_pushinteger(L, KEY_C);
  lua_setfield(L, -2, "KEY_C");
  lua_pushinteger(L, KEY_D);
  lua_setfield(L, -2, "KEY_D");
  lua_pushinteger(L, KEY_E);
  lua_setfield(L, -2, "KEY_E");
  lua_pushinteger(L, KEY_F);
  lua_setfield(L, -2, "KEY_F");
  lua_pushinteger(L, KEY_G);
  lua_setfield(L, -2, "KEY_G");
  lua_pushinteger(L, KEY_H);
  lua_setfield(L, -2, "KEY_H");
  lua_pushinteger(L, KEY_I);
  lua_setfield(L, -2, "KEY_I");
  lua_pushinteger(L, KEY_J);
  lua_setfield(L, -2, "KEY_J");
  lua_pushinteger(L, KEY_K);
  lua_setfield(L, -2, "KEY_K");
  lua_pushinteger(L, KEY_L);
  lua_setfield(L, -2, "KEY_L");
  lua_pushinteger(L, KEY_M);
  lua_setfield(L, -2, "KEY_M");
  lua_pushinteger(L, KEY_N);
  lua_setfield(L, -2, "KEY_N");
  lua_pushinteger(L, KEY_O);
  lua_setfield(L, -2, "KEY_O");
  lua_pushinteger(L, KEY_P);
  lua_setfield(L, -2, "KEY_P");
  lua_pushinteger(L, KEY_Q);
  lua_setfield(L, -2, "KEY_Q");
  lua_pushinteger(L, KEY_R);
  lua_setfield(L, -2, "KEY_R");
  lua_pushinteger(L, KEY_S);
  lua_setfield(L, -2, "KEY_S");
  lua_pushinteger(L, KEY_T);
  lua_setfield(L, -2, "KEY_T");
  lua_pushinteger(L, KEY_U);
  lua_setfield(L, -2, "KEY_U");
  lua_pushinteger(L, KEY_V);
  lua_setfield(L, -2, "KEY_V");
  lua_pushinteger(L, KEY_W);
  lua_setfield(L, -2, "KEY_W");
  lua_pushinteger(L, KEY_X);
  lua_setfield(L, -2, "KEY_X");
  lua_pushinteger(L, KEY_Y);
  lua_setfield(L, -2, "KEY_Y");
  lua_pushinteger(L, KEY_Z);
  lua_setfield(L, -2, "KEY_Z");
  lua_pushinteger(L, KEY_SPACE);
  lua_setfield(L, -2, "KEY_SPACE");
  lua_pushinteger(L, KEY_ESCAPE);
  lua_setfield(L, -2, "KEY_ESCAPE");
  lua_pushinteger(L, KEY_ENTER);
  lua_setfield(L, -2, "KEY_ENTER");
  lua_pushinteger(L, KEY_TAB);
  lua_setfield(L, -2, "KEY_TAB");
  lua_pushinteger(L, KEY_BACKSPACE);
  lua_setfield(L, -2, "KEY_BACKSPACE");
  lua_pushinteger(L, KEY_INSERT);
  lua_setfield(L, -2, "KEY_INSERT");
  lua_pushinteger(L, KEY_DELETE);
  lua_setfield(L, -2, "KEY_DELETE");
  lua_pushinteger(L, KEY_RIGHT);
  lua_setfield(L, -2, "KEY_RIGHT");
  lua_pushinteger(L, KEY_LEFT);
  lua_setfield(L, -2, "KEY_LEFT");
  lua_pushinteger(L, KEY_DOWN);
  lua_setfield(L, -2, "KEY_DOWN");
  lua_pushinteger(L, KEY_UP);
  lua_setfield(L, -2, "KEY_UP");
  lua_pushinteger(L, KEY_PAGE_UP);
  lua_setfield(L, -2, "KEY_PAGE_UP");
  lua_pushinteger(L, KEY_PAGE_DOWN);
  lua_setfield(L, -2, "KEY_PAGE_DOWN");
  lua_pushinteger(L, KEY_HOME);
  lua_setfield(L, -2, "KEY_HOME");
  lua_pushinteger(L, KEY_END);
  lua_setfield(L, -2, "KEY_END");
  lua_pushinteger(L, KEY_CAPS_LOCK);
  lua_setfield(L, -2, "KEY_CAPS_LOCK");
  lua_pushinteger(L, KEY_SCROLL_LOCK);
  lua_setfield(L, -2, "KEY_SCROLL_LOCK");
  lua_pushinteger(L, KEY_NUM_LOCK);
  lua_setfield(L, -2, "KEY_NUM_LOCK");
  lua_pushinteger(L, KEY_PRINT_SCREEN);
  lua_setfield(L, -2, "KEY_PRINT_SCREEN");
  lua_pushinteger(L, KEY_PAUSE);
  lua_setfield(L, -2, "KEY_PAUSE");
  lua_pushinteger(L, KEY_F1);
  lua_setfield(L, -2, "KEY_F1");
  lua_pushinteger(L, KEY_F2);
  lua_setfield(L, -2, "KEY_F2");
  lua_pushinteger(L, KEY_F3);
  lua_setfield(L, -2, "KEY_F3");
  lua_pushinteger(L, KEY_F4);
  lua_setfield(L, -2, "KEY_F4");
  lua_pushinteger(L, KEY_F5);
  lua_setfield(L, -2, "KEY_F5");
  lua_pushinteger(L, KEY_F6);
  lua_setfield(L, -2, "KEY_F6");
  lua_pushinteger(L, KEY_F7);
  lua_setfield(L, -2, "KEY_F7");
  lua_pushinteger(L, KEY_F8);
  lua_setfield(L, -2, "KEY_F8");
  lua_pushinteger(L, KEY_F9);
  lua_setfield(L, -2, "KEY_F9");
  lua_pushinteger(L, KEY_F10);
  lua_setfield(L, -2, "KEY_F10");
  lua_pushinteger(L, KEY_F11);
  lua_setfield(L, -2, "KEY_F11");
  lua_pushinteger(L, KEY_F12);
  lua_setfield(L, -2, "KEY_F12");
  lua_pushinteger(L, KEY_LEFT_SHIFT);
  lua_setfield(L, -2, "KEY_LEFT_SHIFT");
  lua_pushinteger(L, KEY_LEFT_CONTROL);
  lua_setfield(L, -2, "KEY_LEFT_CONTROL");
  lua_pushinteger(L, KEY_LEFT_ALT);
  lua_setfield(L, -2, "KEY_LEFT_ALT");
  lua_pushinteger(L, KEY_LEFT_SUPER);
  lua_setfield(L, -2, "KEY_LEFT_SUPER");
  lua_pushinteger(L, KEY_RIGHT_SHIFT);
  lua_setfield(L, -2, "KEY_RIGHT_SHIFT");
  lua_pushinteger(L, KEY_RIGHT_CONTROL);
  lua_setfield(L, -2, "KEY_RIGHT_CONTROL");
  lua_pushinteger(L, KEY_RIGHT_ALT);
  lua_setfield(L, -2, "KEY_RIGHT_ALT");
  lua_pushinteger(L, KEY_RIGHT_SUPER);
  lua_setfield(L, -2, "KEY_RIGHT_SUPER");
  lua_pushinteger(L, KEY_KB_MENU);
  lua_setfield(L, -2, "KEY_KB_MENU");
  lua_pushinteger(L, KEY_LEFT_BRACKET);
  lua_setfield(L, -2, "KEY_LEFT_BRACKET");
  lua_pushinteger(L, KEY_BACKSLASH);
  lua_setfield(L, -2, "KEY_BACKSLASH");
  lua_pushinteger(L, KEY_RIGHT_BRACKET);
  lua_setfield(L, -2, "KEY_RIGHT_BRACKET");
  lua_pushinteger(L, KEY_GRAVE);
  lua_setfield(L, -2, "KEY_GRAVE");
  lua_pushinteger(L, KEY_KP_0);
  lua_setfield(L, -2, "KEY_KP_0");
  lua_pushinteger(L, KEY_KP_1);
  lua_setfield(L, -2, "KEY_KP_1");
  lua_pushinteger(L, KEY_KP_2);
  lua_setfield(L, -2, "KEY_KP_2");
  lua_pushinteger(L, KEY_KP_3);
  lua_setfield(L, -2, "KEY_KP_3");
  lua_pushinteger(L, KEY_KP_4);
  lua_setfield(L, -2, "KEY_KP_4");
  lua_pushinteger(L, KEY_KP_5);
  lua_setfield(L, -2, "KEY_KP_5");
  lua_pushinteger(L, KEY_KP_6);
  lua_setfield(L, -2, "KEY_KP_6");
  lua_pushinteger(L, KEY_KP_7);
  lua_setfield(L, -2, "KEY_KP_7");
  lua_pushinteger(L, KEY_KP_8);
  lua_setfield(L, -2, "KEY_KP_8");
  lua_pushinteger(L, KEY_KP_9);
  lua_setfield(L, -2, "KEY_KP_9");
  lua_pushinteger(L, KEY_KP_DECIMAL);
  lua_setfield(L, -2, "KEY_KP_DECIMAL");
  lua_pushinteger(L, KEY_KP_DIVIDE);
  lua_setfield(L, -2, "KEY_KP_DIVIDE");
  lua_pushinteger(L, KEY_KP_MULTIPLY);
  lua_setfield(L, -2, "KEY_KP_MULTIPLY");
  lua_pushinteger(L, KEY_KP_SUBTRACT);
  lua_setfield(L, -2, "KEY_KP_SUBTRACT");
  lua_pushinteger(L, KEY_KP_ADD);
  lua_setfield(L, -2, "KEY_KP_ADD");
  lua_pushinteger(L, KEY_KP_ENTER);
  lua_setfield(L, -2, "KEY_KP_ENTER");
  lua_pushinteger(L, KEY_KP_EQUAL);
  lua_setfield(L, -2, "KEY_KP_EQUAL");
  lua_pushinteger(L, KEY_BACK);
  lua_setfield(L, -2, "KEY_BACK");
  lua_pushinteger(L, KEY_MENU);
  lua_setfield(L, -2, "KEY_MENU");
  lua_pushinteger(L, KEY_VOLUME_UP);
  lua_setfield(L, -2, "KEY_VOLUME_UP");
  lua_pushinteger(L, KEY_VOLUME_DOWN);
  lua_setfield(L, -2, "KEY_VOLUME_DOWN");
  lua_pushinteger(L, MOUSE_LEFT_BUTTON);
  lua_setfield(L, -2, "MOUSE_LEFT_BUTTON");
  lua_pushinteger(L, MOUSE_RIGHT_BUTTON);
  lua_setfield(L, -2, "MOUSE_RIGHT_BUTTON");
  lua_pushinteger(L, MOUSE_MIDDLE_BUTTON);
  lua_setfield(L, -2, "MOUSE_MIDDLE_BUTTON");
  lua_pushinteger(L, GAMEPAD_PLAYER1);
  lua_setfield(L, -2, "GAMEPAD_PLAYER1");
  lua_pushinteger(L, GAMEPAD_PLAYER2);
  lua_setfield(L, -2, "GAMEPAD_PLAYER2");
  lua_pushinteger(L, GAMEPAD_PLAYER3);
  lua_setfield(L, -2, "GAMEPAD_PLAYER3");
  lua_pushinteger(L, GAMEPAD_PLAYER4);
  lua_setfield(L, -2, "GAMEPAD_PLAYER4");
  lua_pushinteger(L, GAMEPAD_BUTTON_UNKNOWN);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_UNKNOWN");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_FACE_UP);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_FACE_UP");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_FACE_DOWN");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_FACE_LEFT");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_FACE_UP);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_FACE_UP");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_TRIGGER_1");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_TRIGGER_2");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2");
  lua_pushinteger(L, GAMEPAD_BUTTON_MIDDLE_LEFT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_MIDDLE_LEFT");
  lua_pushinteger(L, GAMEPAD_BUTTON_MIDDLE);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_MIDDLE");
  lua_pushinteger(L, GAMEPAD_BUTTON_MIDDLE_RIGHT);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_MIDDLE_RIGHT");
  lua_pushinteger(L, GAMEPAD_BUTTON_LEFT_THUMB);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_LEFT_THUMB");
  lua_pushinteger(L, GAMEPAD_BUTTON_RIGHT_THUMB);
  lua_setfield(L, -2, "GAMEPAD_BUTTON_RIGHT_THUMB");
  lua_pushinteger(L, GAMEPAD_AXIS_UNKNOWN);
  lua_setfield(L, -2, "GAMEPAD_AXIS_UNKNOWN");
  lua_pushinteger(L, GAMEPAD_AXIS_LEFT_X);
  lua_setfield(L, -2, "GAMEPAD_AXIS_LEFT_X");
  lua_pushinteger(L, GAMEPAD_AXIS_LEFT_Y);
  lua_setfield(L, -2, "GAMEPAD_AXIS_LEFT_Y");
  lua_pushinteger(L, GAMEPAD_AXIS_RIGHT_X);
  lua_setfield(L, -2, "GAMEPAD_AXIS_RIGHT_X");
  lua_pushinteger(L, GAMEPAD_AXIS_RIGHT_Y);
  lua_setfield(L, -2, "GAMEPAD_AXIS_RIGHT_Y");
  lua_pushinteger(L, GAMEPAD_AXIS_LEFT_TRIGGER);
  lua_setfield(L, -2, "GAMEPAD_AXIS_LEFT_TRIGGER");
  lua_pushinteger(L, GAMEPAD_AXIS_RIGHT_TRIGGER);
  lua_setfield(L, -2, "GAMEPAD_AXIS_RIGHT_TRIGGER");
  lua_pushinteger(L, LOC_VERTEX_POSITION);
  lua_setfield(L, -2, "LOC_VERTEX_POSITION");
  lua_pushinteger(L, LOC_VERTEX_TEXCOORD01);
  lua_setfield(L, -2, "LOC_VERTEX_TEXCOORD01");
  lua_pushinteger(L, LOC_VERTEX_TEXCOORD02);
  lua_setfield(L, -2, "LOC_VERTEX_TEXCOORD02");
  lua_pushinteger(L, LOC_VERTEX_NORMAL);
  lua_setfield(L, -2, "LOC_VERTEX_NORMAL");
  lua_pushinteger(L, LOC_VERTEX_TANGENT);
  lua_setfield(L, -2, "LOC_VERTEX_TANGENT");
  lua_pushinteger(L, LOC_VERTEX_COLOR);
  lua_setfield(L, -2, "LOC_VERTEX_COLOR");
  lua_pushinteger(L, LOC_MATRIX_MVP);
  lua_setfield(L, -2, "LOC_MATRIX_MVP");
  lua_pushinteger(L, LOC_MATRIX_MODEL);
  lua_setfield(L, -2, "LOC_MATRIX_MODEL");
  lua_pushinteger(L, LOC_MATRIX_VIEW);
  lua_setfield(L, -2, "LOC_MATRIX_VIEW");
  lua_pushinteger(L, LOC_MATRIX_PROJECTION);
  lua_setfield(L, -2, "LOC_MATRIX_PROJECTION");
  lua_pushinteger(L, LOC_VECTOR_VIEW);
  lua_setfield(L, -2, "LOC_VECTOR_VIEW");
  lua_pushinteger(L, LOC_COLOR_DIFFUSE);
  lua_setfield(L, -2, "LOC_COLOR_DIFFUSE");
  lua_pushinteger(L, LOC_COLOR_SPECULAR);
  lua_setfield(L, -2, "LOC_COLOR_SPECULAR");
  lua_pushinteger(L, LOC_COLOR_AMBIENT);
  lua_setfield(L, -2, "LOC_COLOR_AMBIENT");
  lua_pushinteger(L, LOC_MAP_ALBEDO);
  lua_setfield(L, -2, "LOC_MAP_ALBEDO");
  lua_pushinteger(L, LOC_MAP_METALNESS);
  lua_setfield(L, -2, "LOC_MAP_METALNESS");
  lua_pushinteger(L, LOC_MAP_NORMAL);
  lua_setfield(L, -2, "LOC_MAP_NORMAL");
  lua_pushinteger(L, LOC_MAP_ROUGHNESS);
  lua_setfield(L, -2, "LOC_MAP_ROUGHNESS");
  lua_pushinteger(L, LOC_MAP_OCCLUSION);
  lua_setfield(L, -2, "LOC_MAP_OCCLUSION");
  lua_pushinteger(L, LOC_MAP_EMISSION);
  lua_setfield(L, -2, "LOC_MAP_EMISSION");
  lua_pushinteger(L, LOC_MAP_HEIGHT);
  lua_setfield(L, -2, "LOC_MAP_HEIGHT");
  lua_pushinteger(L, LOC_MAP_CUBEMAP);
  lua_setfield(L, -2, "LOC_MAP_CUBEMAP");
  lua_pushinteger(L, LOC_MAP_IRRADIANCE);
  lua_setfield(L, -2, "LOC_MAP_IRRADIANCE");
  lua_pushinteger(L, LOC_MAP_PREFILTER);
  lua_setfield(L, -2, "LOC_MAP_PREFILTER");
  lua_pushinteger(L, LOC_MAP_BRDF);
  lua_setfield(L, -2, "LOC_MAP_BRDF");
  lua_pushinteger(L, UNIFORM_FLOAT);
  lua_setfield(L, -2, "UNIFORM_FLOAT");
  lua_pushinteger(L, UNIFORM_VEC2);
  lua_setfield(L, -2, "UNIFORM_VEC2");
  lua_pushinteger(L, UNIFORM_VEC3);
  lua_setfield(L, -2, "UNIFORM_VEC3");
  lua_pushinteger(L, UNIFORM_VEC4);
  lua_setfield(L, -2, "UNIFORM_VEC4");
  lua_pushinteger(L, UNIFORM_INT);
  lua_setfield(L, -2, "UNIFORM_INT");
  lua_pushinteger(L, UNIFORM_IVEC2);
  lua_setfield(L, -2, "UNIFORM_IVEC2");
  lua_pushinteger(L, UNIFORM_IVEC3);
  lua_setfield(L, -2, "UNIFORM_IVEC3");
  lua_pushinteger(L, UNIFORM_IVEC4);
  lua_setfield(L, -2, "UNIFORM_IVEC4");
  lua_pushinteger(L, UNIFORM_SAMPLER2D);
  lua_setfield(L, -2, "UNIFORM_SAMPLER2D");
  lua_pushinteger(L, MAP_ALBEDO);
  lua_setfield(L, -2, "MAP_ALBEDO");
  lua_pushinteger(L, MAP_METALNESS);
  lua_setfield(L, -2, "MAP_METALNESS");
  lua_pushinteger(L, MAP_NORMAL);
  lua_setfield(L, -2, "MAP_NORMAL");
  lua_pushinteger(L, MAP_ROUGHNESS);
  lua_setfield(L, -2, "MAP_ROUGHNESS");
  lua_pushinteger(L, MAP_OCCLUSION);
  lua_setfield(L, -2, "MAP_OCCLUSION");
  lua_pushinteger(L, MAP_EMISSION);
  lua_setfield(L, -2, "MAP_EMISSION");
  lua_pushinteger(L, MAP_HEIGHT);
  lua_setfield(L, -2, "MAP_HEIGHT");
  lua_pushinteger(L, MAP_CUBEMAP);
  lua_setfield(L, -2, "MAP_CUBEMAP");
  lua_pushinteger(L, MAP_IRRADIANCE);
  lua_setfield(L, -2, "MAP_IRRADIANCE");
  lua_pushinteger(L, MAP_PREFILTER);
  lua_setfield(L, -2, "MAP_PREFILTER");
  lua_pushinteger(L, MAP_BRDF);
  lua_setfield(L, -2, "MAP_BRDF");
  lua_pushinteger(L, UNCOMPRESSED_GRAYSCALE);
  lua_setfield(L, -2, "UNCOMPRESSED_GRAYSCALE");
  lua_pushinteger(L, UNCOMPRESSED_GRAY_ALPHA);
  lua_setfield(L, -2, "UNCOMPRESSED_GRAY_ALPHA");
  lua_pushinteger(L, UNCOMPRESSED_R5G6B5);
  lua_setfield(L, -2, "UNCOMPRESSED_R5G6B5");
  lua_pushinteger(L, UNCOMPRESSED_R8G8B8);
  lua_setfield(L, -2, "UNCOMPRESSED_R8G8B8");
  lua_pushinteger(L, UNCOMPRESSED_R5G5B5A1);
  lua_setfield(L, -2, "UNCOMPRESSED_R5G5B5A1");
  lua_pushinteger(L, UNCOMPRESSED_R4G4B4A4);
  lua_setfield(L, -2, "UNCOMPRESSED_R4G4B4A4");
  lua_pushinteger(L, UNCOMPRESSED_R8G8B8A8);
  lua_setfield(L, -2, "UNCOMPRESSED_R8G8B8A8");
  lua_pushinteger(L, UNCOMPRESSED_R32);
  lua_setfield(L, -2, "UNCOMPRESSED_R32");
  lua_pushinteger(L, UNCOMPRESSED_R32G32B32);
  lua_setfield(L, -2, "UNCOMPRESSED_R32G32B32");
  lua_pushinteger(L, UNCOMPRESSED_R32G32B32A32);
  lua_setfield(L, -2, "UNCOMPRESSED_R32G32B32A32");
  lua_pushinteger(L, COMPRESSED_DXT1_RGB);
  lua_setfield(L, -2, "COMPRESSED_DXT1_RGB");
  lua_pushinteger(L, COMPRESSED_DXT1_RGBA);
  lua_setfield(L, -2, "COMPRESSED_DXT1_RGBA");
  lua_pushinteger(L, COMPRESSED_DXT3_RGBA);
  lua_setfield(L, -2, "COMPRESSED_DXT3_RGBA");
  lua_pushinteger(L, COMPRESSED_DXT5_RGBA);
  lua_setfield(L, -2, "COMPRESSED_DXT5_RGBA");
  lua_pushinteger(L, COMPRESSED_ETC1_RGB);
  lua_setfield(L, -2, "COMPRESSED_ETC1_RGB");
  lua_pushinteger(L, COMPRESSED_ETC2_RGB);
  lua_setfield(L, -2, "COMPRESSED_ETC2_RGB");
  lua_pushinteger(L, COMPRESSED_ETC2_EAC_RGBA);
  lua_setfield(L, -2, "COMPRESSED_ETC2_EAC_RGBA");
  lua_pushinteger(L, COMPRESSED_PVRT_RGB);
  lua_setfield(L, -2, "COMPRESSED_PVRT_RGB");
  lua_pushinteger(L, COMPRESSED_PVRT_RGBA);
  lua_setfield(L, -2, "COMPRESSED_PVRT_RGBA");
  lua_pushinteger(L, COMPRESSED_ASTC_4x4_RGBA);
  lua_setfield(L, -2, "COMPRESSED_ASTC_4x4_RGBA");
  lua_pushinteger(L, COMPRESSED_ASTC_8x8_RGBA);
  lua_setfield(L, -2, "COMPRESSED_ASTC_8x8_RGBA");
  lua_pushinteger(L, FILTER_POINT);
  lua_setfield(L, -2, "FILTER_POINT");
  lua_pushinteger(L, FILTER_BILINEAR);
  lua_setfield(L, -2, "FILTER_BILINEAR");
  lua_pushinteger(L, FILTER_TRILINEAR);
  lua_setfield(L, -2, "FILTER_TRILINEAR");
  lua_pushinteger(L, FILTER_ANISOTROPIC_4X);
  lua_setfield(L, -2, "FILTER_ANISOTROPIC_4X");
  lua_pushinteger(L, FILTER_ANISOTROPIC_8X);
  lua_setfield(L, -2, "FILTER_ANISOTROPIC_8X");
  lua_pushinteger(L, FILTER_ANISOTROPIC_16X);
  lua_setfield(L, -2, "FILTER_ANISOTROPIC_16X");
  lua_pushinteger(L, CUBEMAP_AUTO_DETECT);
  lua_setfield(L, -2, "CUBEMAP_AUTO_DETECT");
  lua_pushinteger(L, CUBEMAP_LINE_VERTICAL);
  lua_setfield(L, -2, "CUBEMAP_LINE_VERTICAL");
  lua_pushinteger(L, CUBEMAP_LINE_HORIZONTAL);
  lua_setfield(L, -2, "CUBEMAP_LINE_HORIZONTAL");
  lua_pushinteger(L, CUBEMAP_CROSS_THREE_BY_FOUR);
  lua_setfield(L, -2, "CUBEMAP_CROSS_THREE_BY_FOUR");
  lua_pushinteger(L, CUBEMAP_CROSS_FOUR_BY_THREE);
  lua_setfield(L, -2, "CUBEMAP_CROSS_FOUR_BY_THREE");
  lua_pushinteger(L, CUBEMAP_PANORAMA);
  lua_setfield(L, -2, "CUBEMAP_PANORAMA");
  lua_pushinteger(L, WRAP_REPEAT);
  lua_setfield(L, -2, "WRAP_REPEAT");
  lua_pushinteger(L, WRAP_CLAMP);
  lua_setfield(L, -2, "WRAP_CLAMP");
  lua_pushinteger(L, WRAP_MIRROR_REPEAT);
  lua_setfield(L, -2, "WRAP_MIRROR_REPEAT");
  lua_pushinteger(L, WRAP_MIRROR_CLAMP);
  lua_setfield(L, -2, "WRAP_MIRROR_CLAMP");
  lua_pushinteger(L, FONT_DEFAULT);
  lua_setfield(L, -2, "FONT_DEFAULT");
  lua_pushinteger(L, FONT_BITMAP);
  lua_setfield(L, -2, "FONT_BITMAP");
  lua_pushinteger(L, FONT_SDF);
  lua_setfield(L, -2, "FONT_SDF");
  lua_pushinteger(L, BLEND_ALPHA);
  lua_setfield(L, -2, "BLEND_ALPHA");
  lua_pushinteger(L, BLEND_ADDITIVE);
  lua_setfield(L, -2, "BLEND_ADDITIVE");
  lua_pushinteger(L, BLEND_MULTIPLIED);
  lua_setfield(L, -2, "BLEND_MULTIPLIED");
  lua_pushinteger(L, GESTURE_NONE);
  lua_setfield(L, -2, "GESTURE_NONE");
  lua_pushinteger(L, GESTURE_TAP);
  lua_setfield(L, -2, "GESTURE_TAP");
  lua_pushinteger(L, GESTURE_DOUBLETAP);
  lua_setfield(L, -2, "GESTURE_DOUBLETAP");
  lua_pushinteger(L, GESTURE_HOLD);
  lua_setfield(L, -2, "GESTURE_HOLD");
  lua_pushinteger(L, GESTURE_DRAG);
  lua_setfield(L, -2, "GESTURE_DRAG");
  lua_pushinteger(L, GESTURE_SWIPE_RIGHT);
  lua_setfield(L, -2, "GESTURE_SWIPE_RIGHT");
  lua_pushinteger(L, GESTURE_SWIPE_LEFT);
  lua_setfield(L, -2, "GESTURE_SWIPE_LEFT");
  lua_pushinteger(L, GESTURE_SWIPE_UP);
  lua_setfield(L, -2, "GESTURE_SWIPE_UP");
  lua_pushinteger(L, GESTURE_SWIPE_DOWN);
  lua_setfield(L, -2, "GESTURE_SWIPE_DOWN");
  lua_pushinteger(L, GESTURE_PINCH_IN);
  lua_setfield(L, -2, "GESTURE_PINCH_IN");
  lua_pushinteger(L, GESTURE_PINCH_OUT);
  lua_setfield(L, -2, "GESTURE_PINCH_OUT");
  lua_pushinteger(L, CAMERA_CUSTOM);
  lua_setfield(L, -2, "CAMERA_CUSTOM");
  lua_pushinteger(L, CAMERA_FREE);
  lua_setfield(L, -2, "CAMERA_FREE");
  lua_pushinteger(L, CAMERA_ORBITAL);
  lua_setfield(L, -2, "CAMERA_ORBITAL");
  lua_pushinteger(L, CAMERA_FIRST_PERSON);
  lua_setfield(L, -2, "CAMERA_FIRST_PERSON");
  lua_pushinteger(L, CAMERA_THIRD_PERSON);
  lua_setfield(L, -2, "CAMERA_THIRD_PERSON");
  lua_pushinteger(L, CAMERA_PERSPECTIVE);
  lua_setfield(L, -2, "CAMERA_PERSPECTIVE");
  lua_pushinteger(L, CAMERA_ORTHOGRAPHIC);
  lua_setfield(L, -2, "CAMERA_ORTHOGRAPHIC");
  lua_pushinteger(L, NPT_9PATCH);
  lua_setfield(L, -2, "NPT_9PATCH");
  lua_pushinteger(L, NPT_3PATCH_VERTICAL);
  lua_setfield(L, -2, "NPT_3PATCH_VERTICAL");
  lua_pushinteger(L, NPT_3PATCH_HORIZONTAL);
  lua_setfield(L, -2, "NPT_3PATCH_HORIZONTAL");
  return 1;
}
