#define RAYGUI_IMPLEMENTATION
#define RAYGUI_TEXTBOX_EXTENDED
#define RAYGUI_RICONS_SUPPORT
#include <raygui.h>

static int l_raygui_GuiButton(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  bool result = GuiButton(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiButtonU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  bool result = GuiButton(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiCheckBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  bool checked = lua_toboolean(L, 3);
  bool result = GuiCheckBox(bounds, text, checked);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiCheckBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  bool checked = lua_toboolean(L, 6);
  bool result = GuiCheckBox(bounds, text, checked);
  lua_pushboolean(L, result);
  return 1;
}

// Color Panel control
static int l_raygui_GuiColorBarAlpha(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  float alpha = luaL_checknumber(L, 2);
  float result = GuiColorBarAlpha(bounds, alpha);
  lua_pushnumber(L, result);
  return 1;
}

// Color Panel control (unpacked version)
static int l_raygui_GuiColorBarAlphaU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  float alpha = luaL_checknumber(L, 5);
  float result = GuiColorBarAlpha(bounds, alpha);
  lua_pushnumber(L, result);
  return 1;
}

// Color Panel control
static int l_raygui_GuiColorBarHue(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  float hue = luaL_checknumber(L, 2);
  float result = GuiColorBarHue(bounds, hue);
  lua_pushnumber(L, result);
  return 1;
}

// Color Panel control (unpacked version)
static int l_raygui_GuiColorBarHueU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  float hue = luaL_checknumber(L, 5);
  float result = GuiColorBarHue(bounds, hue);
  lua_pushnumber(L, result);
  return 1;
}

// Color Panel control
static int l_raygui_GuiColorPanel(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  Color result = GuiColorPanel(bounds, color);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

// Color Panel control (unpacked version)
static int l_raygui_GuiColorPanelU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color result = GuiColorPanel(bounds, color);
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

static int l_raygui_GuiColorPicker(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Color color = (*(Color*)luaL_checkudata(L, 2, "Color"));
  Color result = GuiColorPicker(bounds, color);
  Color* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Color");
  return 1;
}

static int l_raygui_GuiColorPickerU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Color color = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Color result = GuiColorPicker(bounds, color);
  lua_pushinteger(L, result.r);lua_pushinteger(L, result.g);lua_pushinteger(L, result.b);lua_pushinteger(L, result.a);
  return 4;
}

static int l_raygui_GuiComboBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  int active = luaL_checkinteger(L, 3);
  int result = GuiComboBox(bounds, text, active);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiComboBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  int active = luaL_checkinteger(L, 6);
  int result = GuiComboBox(bounds, text, active);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiDisable(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiDisable();
  return 0;
}

static int l_raygui_GuiDropdownBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  int active = luaL_checkinteger(L, 3);
  bool editMode = lua_toboolean(L, 4);
  bool result = GuiDropdownBox(bounds, text, &active, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, active);
  return 2;
}

static int l_raygui_GuiDropdownBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 2);
  int active = luaL_checkinteger(L, 3);
  bool editMode = lua_toboolean(L, 4);
  bool result = GuiDropdownBox(bounds, text, &active, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, active);
  return 2;
}

static int l_raygui_GuiDummyRec(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  GuiDummyRec(bounds, text);
  return 0;
}

static int l_raygui_GuiDummyRecU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  GuiDummyRec(bounds, text);
  return 0;
}

static int l_raygui_GuiEnable(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiEnable();
  return 0;
}

static int l_raygui_GuiFade(lua_State *L) {
  float alpha = luaL_checknumber(L, 1);
  GuiFade(alpha);
  return 0;
}

static int l_raygui_GuiFont(lua_State *L) {
  Font font = (*(Font*)luaL_checkudata(L, 1, "Font"));
  GuiFont(font);
  return 0;
}

static int l_raygui_GuiGetStyle(lua_State *L) {
  int control = luaL_checkinteger(L, 1);
  int property = luaL_checkinteger(L, 2);
  int result = GuiGetStyle(control, property);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiGrid(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  float spacing = luaL_checknumber(L, 2);
  int subdivs = luaL_checkinteger(L, 3);
  Vector2 result = GuiGrid(bounds, spacing, subdivs);
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_raygui_GuiGridU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  float spacing = luaL_checknumber(L, 5);
  int subdivs = luaL_checkinteger(L, 6);
  Vector2 result = GuiGrid(bounds, spacing, subdivs);
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_raygui_GuiGroupBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  GuiGroupBox(bounds, text);
  return 0;
}

static int l_raygui_GuiGroupBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  GuiGroupBox(bounds, text);
  return 0;
}

static int l_raygui_GuiIconText(lua_State *L) {
  int iconId = luaL_checkinteger(L, 1);
  const char* text = luaL_checkstring(L, 2);
  const char* result = GuiIconText(iconId, text);
  lua_pushstring(L, result);
  return 1;
}

static int l_raygui_GuiImageButton(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  bool result = GuiImageButton(bounds, texture);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiImageButtonU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Texture2D texture = {};
  bool result = GuiImageButton(bounds, texture);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiImageButtonEx(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Texture2D texture = (*(Texture2D*)luaL_checkudata(L, 2, "Texture2D"));
  Rectangle texSource = (*(Rectangle*)luaL_checkudata(L, 3, "Rectangle"));
  const char* text = luaL_checkstring(L, 4);
  bool result = GuiImageButtonEx(bounds, texture, texSource, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiImageButtonExU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Texture2D texture = {};
  Rectangle texSource = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  const char* text = luaL_checkstring(L, 9);
  bool result = GuiImageButtonEx(bounds, texture, texSource, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiLabel(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  GuiLabel(bounds, text);
  return 0;
}

static int l_raygui_GuiLabelU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  GuiLabel(bounds, text);
  return 0;
}

static int l_raygui_GuiLabelButton(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  bool result = GuiLabelButton(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiLabelButtonU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  bool result = GuiLabelButton(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiLine(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  GuiLine(bounds, text);
  return 0;
}

static int l_raygui_GuiLineU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  GuiLine(bounds, text);
  return 0;
}

static int l_raygui_GuiListView(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  bool editMode = lua_toboolean(L, 2);
  const char* text = luaL_checkstring(L, 3);
  int active;
  int scrollIndex;
  bool result = GuiListView(bounds, text, &active, &scrollIndex, editMode);
  lua_pushboolean(L, result);
	lua_pushinteger(L, active);
	lua_pushinteger(L, scrollIndex);
  return 3;
}

static int l_raygui_GuiListViewEx(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  bool editMode = lua_toboolean(L, 2);
  const char* text[64];
  int n = lua_gettop(L);
  int count = n-2;
  int enabled;
  int active;
  int focus;
  int scrollIndex;
  for (int i = 0; i < count; i++) {
    text[i] = luaL_checkstring(L, i+2);
  }
  bool result = GuiListViewEx(bounds, text, count, &enabled, &active, &focus, &scrollIndex, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, enabled);
  lua_pushinteger(L, active);
  lua_pushinteger(L, focus);
  lua_pushinteger(L, scrollIndex);
  return 5;
}

static int l_raygui_GuiListViewExU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  bool editMode = lua_toboolean(L, 5);
	const char* text[64];
	int n = lua_gettop(L);
	int count = n-2;
  int enabled;
  int active;
  int focus;
  int scrollIndex;
	for (int i = 0; i < count; i++) {
		text[i] = luaL_checkstring(L, i+2);
	}
  bool result = GuiListViewEx(bounds, text, count, &enabled, &active, &focus, &scrollIndex, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, enabled);
  lua_pushinteger(L, active);
  lua_pushinteger(L, focus);
  lua_pushinteger(L, scrollIndex);
	return 5;
}

static int l_raygui_GuiListViewU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  bool editMode = lua_toboolean(L, 2);
  const char* text = luaL_checkstring(L, 3);
  int active;
  int scrollIndex;
  bool result = GuiListView(bounds, text, &active, &scrollIndex, editMode);
  lua_pushboolean(L, result);
	lua_pushinteger(L, active);
	lua_pushinteger(L, scrollIndex);
  return 3;
}

static int l_raygui_GuiLoadStyle(lua_State *L) {
  const char* fileName = luaL_checkstring(L, 1);
  GuiLoadStyle(fileName);
  return 0;
}

static int l_raygui_GuiLoadStyleDefault(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiLoadStyleDefault();
  return 0;
}

static int l_raygui_GuiLoadStyleProps(lua_State *L) {
  int count = lua_gettop(L)-1;
  int props[NUM_PROPS_DEFAULT + NUM_PROPS_EXTENDED];
  for (int i = 0; i < count; i++) {
    props[i] = luaL_checkinteger(L, i+1);
  }
  GuiLoadStyleProps(props, count);
  return 0;
}

static int l_raygui_GuiLock(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiLock();
  return 0;
}

static int l_raygui_GuiMessageBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* windowTitle = luaL_checkstring(L, 2);
  const char* message = luaL_checkstring(L, 3);
  const char* buttons = luaL_checkstring(L, 4);
  int result = GuiMessageBox(bounds, windowTitle, message, buttons);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiMessageBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* windowTitle = luaL_checkstring(L, 5);
  const char* message = luaL_checkstring(L, 6);
  const char* buttons = luaL_checkstring(L, 7);
  int result = GuiMessageBox(bounds, windowTitle, message, buttons);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiPanel(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  GuiPanel(bounds);
  return 0;
}

static int l_raygui_GuiPanelU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  GuiPanel(bounds);
  return 0;
}

static int l_raygui_GuiProgressBar(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  float value = luaL_checknumber(L, 3);
  float minValue = luaL_checknumber(L, 4);
  float maxValue = luaL_checknumber(L, 5);
  bool showValue = lua_toboolean(L, 6);
  float result = GuiProgressBar(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiProgressBarU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  float value = luaL_checknumber(L, 6);
  float minValue = luaL_checknumber(L, 7);
  float maxValue = luaL_checknumber(L, 8);
  bool showValue = lua_toboolean(L, 9);
  float result = GuiProgressBar(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiScrollBar(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  int value = luaL_checkinteger(L, 2);
  int minValue = luaL_checkinteger(L, 3);
  int maxValue = luaL_checkinteger(L, 4);
  int result = GuiScrollBar(bounds, value, minValue, maxValue);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiScrollBarU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  int value = luaL_checkinteger(L, 5);
  int minValue = luaL_checkinteger(L, 6);
  int maxValue = luaL_checkinteger(L, 7);
  int result = GuiScrollBar(bounds, value, minValue, maxValue);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiScrollPanel(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  Rectangle content = (*(Rectangle*)luaL_checkudata(L, 2, "Rectangle"));
  Vector2 scroll;
  Rectangle result = GuiScrollPanel(bounds, content, &scroll);
	lua_pushnumber(L, scroll.x);lua_pushnumber(L, scroll.y);
  return 3;
}

static int l_raygui_GuiScrollPanelU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  Rectangle content = {luaL_checkinteger(L, 5),luaL_checkinteger(L, 6),luaL_checkinteger(L, 7),luaL_checkinteger(L, 8)};
  Vector2 scroll;
  Rectangle result = GuiScrollPanel(bounds, content, &scroll);
  lua_pushinteger(L, result.x);lua_pushinteger(L, result.y);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);
	lua_pushnumber(L, scroll.x);lua_pushnumber(L, scroll.y);
	return 6;
}

static int l_raygui_GuiSetStyle(lua_State *L) {
  int control = luaL_checkinteger(L, 1);
  int property = luaL_checkinteger(L, 2);
  int value = luaL_checkinteger(L, 3);
  GuiSetStyle(control, property, value);
  return 0;
}

static int l_raygui_GuiSlider(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  float value = luaL_checknumber(L, 3);
  float minValue = luaL_checknumber(L, 4);
  float maxValue = luaL_checknumber(L, 5);
  bool showValue = lua_toboolean(L, 6);
  float result = GuiSlider(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiSliderU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  float value = luaL_checknumber(L, 6);
  float minValue = luaL_checknumber(L, 7);
  float maxValue = luaL_checknumber(L, 8);
  bool showValue = lua_toboolean(L, 9);
  float result = GuiSlider(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiSliderBar(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  float value = luaL_checknumber(L, 3);
  float minValue = luaL_checknumber(L, 4);
  float maxValue = luaL_checknumber(L, 5);
  bool showValue = lua_toboolean(L, 6);
  float result = GuiSliderBar(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiSliderBarU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  float value = luaL_checknumber(L, 6);
  float minValue = luaL_checknumber(L, 7);
  float maxValue = luaL_checknumber(L, 8);
  bool showValue = lua_toboolean(L, 9);
  float result = GuiSliderBar(bounds, text, value, minValue, maxValue, showValue);
  lua_pushnumber(L, result);
  return 1;
}

// Slider control with pro parameters NOTE: Other GuiSlider*() controls use this one
static int l_raygui_GuiSliderPro(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  float value = luaL_checknumber(L, 3);
  float minValue = luaL_checknumber(L, 4);
  float maxValue = luaL_checknumber(L, 5);
  int sliderWidth = luaL_checkinteger(L, 6);
  bool showValue = lua_toboolean(L, 7);
  float result = GuiSliderPro(bounds, text, value, minValue, maxValue, sliderWidth, showValue);
  lua_pushnumber(L, result);
  return 1;
}

// Slider control with pro parameters NOTE: Other GuiSlider*() controls use this one (unpacked version)
static int l_raygui_GuiSliderProU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  float value = luaL_checknumber(L, 6);
  float minValue = luaL_checknumber(L, 7);
  float maxValue = luaL_checknumber(L, 8);
  int sliderWidth = luaL_checkinteger(L, 9);
  bool showValue = lua_toboolean(L, 10);
  float result = GuiSliderPro(bounds, text, value, minValue, maxValue, sliderWidth, showValue);
  lua_pushnumber(L, result);
  return 1;
}

static int l_raygui_GuiSpinner(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  int value = luaL_checkinteger(L, 2);
  int minValue = luaL_checkinteger(L, 3);
  int maxValue = luaL_checkinteger(L, 4);
  bool editMode = lua_toboolean(L, 5);
  bool result = GuiSpinner(bounds, &value, minValue, maxValue, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, value);
  return 2;
}

static int l_raygui_GuiSpinnerU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  int value = luaL_checkinteger(L, 2);
  int minValue = luaL_checkinteger(L, 3);
  int maxValue = luaL_checkinteger(L, 4);
  bool editMode = lua_toboolean(L, 5);
  bool result = GuiSpinner(bounds, &value, minValue, maxValue, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, value);
  return 2;
}

static int l_raygui_GuiState(lua_State *L) {
  int state = luaL_checkinteger(L, 1);
  GuiState(state);
  return 0;
}

static int l_raygui_GuiStatusBar(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  GuiStatusBar(bounds, text);
  return 0;
}

static int l_raygui_GuiStatusBarU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  GuiStatusBar(bounds, text);
  return 0;
}

static int l_raygui_GuiTextBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  char* text = (char*)luaL_checkstring(L, 2);
  int textSize = luaL_checkinteger(L, 3);
  bool editMode = lua_toboolean(L, 4);
  bool result = GuiTextBox(bounds, text, textSize, editMode);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  char* text = (char*)luaL_checkstring(L, 5);
  int textSize = luaL_checkinteger(L, 6);
  bool editMode = lua_toboolean(L, 7);
  bool result = GuiTextBox(bounds, text, textSize, editMode);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxCopy(lua_State *L) {
  //const char* text = luaL_checkstring(L, 1);
  //GuiTextBoxCopy(text);
  return 0;
}

static int l_raygui_GuiTextBoxCut(lua_State *L) {
  //char* text = (char*)luaL_checkstring(L, 1);
  //GuiTextBoxCut(text);
  return 0;
}

static int l_raygui_GuiTextBoxDelete(lua_State *L) {
  //char* text = (char*)luaL_checkstring(L, 1);
  //int length = luaL_checkinteger(L, 2);
  //bool before = lua_toboolean(L, 3);
  //int result = GuiTextBoxDelete(text, length, before);
  //lua_pushinteger(L, result);
  //return 1;
  return 0;
}

static int l_raygui_GuiTextBoxGetActive(lua_State *L) {
  Rectangle result = GuiTextBoxGetActive();
  Rectangle* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Rectangle");
  return 1;
}

static int l_raygui_GuiTextBoxGetActiveU(lua_State *L) {
  Rectangle result = GuiTextBoxGetActive();
  lua_pushinteger(L, result.x);lua_pushinteger(L, result.y);lua_pushinteger(L, result.width);lua_pushinteger(L, result.height);
  return 4;
}

static int l_raygui_GuiTextBoxGetByteIndex(lua_State *L) {
  const char* text = luaL_checkstring(L, 1);
  int start = luaL_checkinteger(L, 2);
  int from = luaL_checkinteger(L, 3);
  int to = luaL_checkinteger(L, 4);
  int result = GuiTextBoxGetByteIndex(text, start, from, to);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxGetCursor(lua_State *L) {
  int result = GuiTextBoxGetCursor();
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxGetSelection(lua_State *L) {
  Vector2 result = GuiTextBoxGetSelection();
  Vector2* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "Vector2");
  return 1;
}

static int l_raygui_GuiTextBoxGetSelectionU(lua_State *L) {
  Vector2 result = GuiTextBoxGetSelection();
  lua_pushnumber(L, result.x);lua_pushnumber(L, result.y);
  return 2;
}

static int l_raygui_GuiTextBoxGetState(lua_State *L) {
  GuiTextBoxState result = GuiTextBoxGetState();
  GuiTextBoxState* userdata = lua_newuserdata(L, sizeof *userdata); *userdata = result; luaL_setmetatable(L, "GuiTextBoxState");
  return 1;
}

static int l_raygui_GuiTextBoxGetStateU(lua_State *L) {
  GuiTextBoxState result = GuiTextBoxGetState();
  lua_pushinteger(L, result.cursor);lua_pushinteger(L, result.start);lua_pushinteger(L, result.index);lua_pushinteger(L, result.select);
  return 4;
}

static int l_raygui_GuiTextBoxIsActive(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  bool result = GuiTextBoxIsActive(bounds);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxIsActiveU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  bool result = GuiTextBoxIsActive(bounds);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxMulti(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  char* text = (char*)luaL_checkstring(L, 2);
  int textSize = luaL_checkinteger(L, 3);
  bool editMode = lua_toboolean(L, 4);
  bool result = GuiTextBoxMulti(bounds, text, textSize, editMode);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxMultiU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  char* text = (char*)luaL_checkstring(L, 5);
  int textSize = luaL_checkinteger(L, 6);
  bool editMode = lua_toboolean(L, 7);
  bool result = GuiTextBoxMulti(bounds, text, textSize, editMode);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxPaste(lua_State *L) {
  //char* text = (char*)luaL_checkstring(L, 1);
  //int textSize = luaL_checkinteger(L, 2);
  //GuiTextBoxPaste(text, textSize);
  return 0;
}

static int l_raygui_GuiTextBoxSelectAll(lua_State *L) {
  //const char* text = luaL_checkstring(L, 1);
  //GuiTextBoxSelectAll(text);
  return 0;
}

static int l_raygui_GuiTextBoxSetActive(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  GuiTextBoxSetActive(bounds);
  return 0;
}

static int l_raygui_GuiTextBoxSetActiveU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  GuiTextBoxSetActive(bounds);
  return 0;
}

static int l_raygui_GuiTextBoxSetCursor(lua_State *L) {
  int cursor = luaL_checkinteger(L, 1);
  GuiTextBoxSetCursor(cursor);
  return 0;
}

static int l_raygui_GuiTextBoxSetSelection(lua_State *L) {
  int start = luaL_checkinteger(L, 1);
  int length = luaL_checkinteger(L, 2);
  GuiTextBoxSetSelection(start, length);
  return 0;
}

static int l_raygui_GuiTextBoxSetState(lua_State *L) {
  GuiTextBoxState state = (*(GuiTextBoxState*)luaL_checkudata(L, 1, "GuiTextBoxState"));
  GuiTextBoxSetState(state);
  return 0;
}

static int l_raygui_GuiTextBoxSetStateU(lua_State *L) {
  GuiTextBoxState state = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  GuiTextBoxSetState(state);
  return 0;
}

static int l_raygui_GuiTextInputBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* windowTitle = luaL_checkstring(L, 2);
  const char* message = luaL_checkstring(L, 3);
  char* text = (char*)luaL_checkstring(L, 4);
  const char* buttons = luaL_checkstring(L, 5);
  int result = GuiTextInputBox(bounds, windowTitle, message, text, buttons);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextInputBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* windowTitle = luaL_checkstring(L, 5);
  const char* message = luaL_checkstring(L, 6);
  char* text = (char*)luaL_checkstring(L, 7);
  const char* buttons = luaL_checkstring(L, 8);
  int result = GuiTextInputBox(bounds, windowTitle, message, text, buttons);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiToggle(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  bool active = lua_toboolean(L, 3);
  bool result = GuiToggle(bounds, text, active);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiToggleU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  bool active = lua_toboolean(L, 6);
  bool result = GuiToggle(bounds, text, active);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiToggleGroup(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  int active = luaL_checkinteger(L, 3);
  int result = GuiToggleGroup(bounds, text, active);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiToggleGroupU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  int active = luaL_checkinteger(L, 6);
  int result = GuiToggleGroup(bounds, text, active);
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiUnlock(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiUnlock();
  return 0;
}

static int l_raygui_GuiUpdateStyleComplete(lua_State *L) {
  (void)L; // Suppress unused warning
  GuiUpdateStyleComplete();
  return 0;
}

static int l_raygui_GuiValueBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  int value = luaL_checkinteger(L, 2);
  int minValue = luaL_checkinteger(L, 3);
  int maxValue = luaL_checkinteger(L, 4);
  bool editMode = lua_toboolean(L, 5);
  bool result = GuiValueBox(bounds, &value, minValue, maxValue, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, value);
  return 2;
}

static int l_raygui_GuiValueBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  int value = luaL_checkinteger(L, 2);
  int minValue = luaL_checkinteger(L, 3);
  int maxValue = luaL_checkinteger(L, 4);
  bool editMode = lua_toboolean(L, 5);
  bool result = GuiValueBox(bounds, &value, minValue, maxValue, editMode);
  lua_pushboolean(L, result);
  lua_pushinteger(L, value);
  return 2;
}

static int l_raygui_GuiWindowBox(lua_State *L) {
  Rectangle bounds = (*(Rectangle*)luaL_checkudata(L, 1, "Rectangle"));
  const char* text = luaL_checkstring(L, 2);
  bool result = GuiWindowBox(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiWindowBoxU(lua_State *L) {
  Rectangle bounds = {luaL_checkinteger(L, 1),luaL_checkinteger(L, 2),luaL_checkinteger(L, 3),luaL_checkinteger(L, 4)};
  const char* text = luaL_checkstring(L, 5);
  bool result = GuiWindowBox(bounds, text);
  lua_pushboolean(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxState_new(lua_State *L) {
  GuiTextBoxState* obj = lua_newuserdata(L, sizeof *obj); luaL_setmetatable(L, "GuiTextBoxState");
  if (lua_gettop(L) == 1) {
   GuiTextBoxState temp = {};
   *obj = temp;
  } else {
    obj->cursor = luaL_checkinteger(L, 1);
    obj->start = luaL_checkinteger(L, 2);
    obj->index = luaL_checkinteger(L, 3);
    obj->select = luaL_checkinteger(L, 4);
  }
  return 1;
}

static int l_raygui_GuiTextBoxState_meta(lua_State *L) {
  luaL_getmetatable(L, "GuiTextBoxState");
  return 1;
}

static const luaL_Reg l_raygui_functions[] = {
  {"GuiButton", l_raygui_GuiButton},
  {"GuiCheckBox", l_raygui_GuiCheckBox},
  {"GuiColorBarAlpha", l_raygui_GuiColorBarAlpha},
  {"GuiColorBarHue", l_raygui_GuiColorBarHue},
  {"GuiColorPanel", l_raygui_GuiColorPanel},
  {"GuiColorPicker", l_raygui_GuiColorPicker},
  {"GuiComboBox", l_raygui_GuiComboBox},
  {"GuiDisable", l_raygui_GuiDisable},
  {"GuiDropdownBox", l_raygui_GuiDropdownBox},
  {"GuiDropdownBoxU", l_raygui_GuiDropdownBoxU},
  {"GuiDummyRec", l_raygui_GuiDummyRec},
  {"GuiEnable", l_raygui_GuiEnable},
  {"GuiFade", l_raygui_GuiFade},
  {"GuiFont", l_raygui_GuiFont},
  {"GuiGetStyle", l_raygui_GuiGetStyle},
  {"GuiGrid", l_raygui_GuiGrid},
  {"GuiGroupBox", l_raygui_GuiGroupBox},
  {"GuiIconText", l_raygui_GuiIconText},
  {"GuiImageButton", l_raygui_GuiImageButton},
  {"GuiImageButtonEx", l_raygui_GuiImageButtonEx},
  {"GuiLabel", l_raygui_GuiLabel},
  {"GuiLabelButton", l_raygui_GuiLabelButton},
  {"GuiLine", l_raygui_GuiLine},
  {"GuiListView", l_raygui_GuiListView},
  {"GuiListViewEx", l_raygui_GuiListViewEx},
  {"GuiListViewExU", l_raygui_GuiListViewExU},
  {"GuiListViewU", l_raygui_GuiListViewU},
  {"GuiLoadStyle", l_raygui_GuiLoadStyle},
  {"GuiLoadStyleDefault", l_raygui_GuiLoadStyleDefault},
  {"GuiLoadStyleProps", l_raygui_GuiLoadStyleProps},
  {"GuiLock", l_raygui_GuiLock},
  {"GuiMessageBox", l_raygui_GuiMessageBox},
  {"GuiPanel", l_raygui_GuiPanel},
  {"GuiProgressBar", l_raygui_GuiProgressBar},
  {"GuiScrollBar", l_raygui_GuiScrollBar},
  {"GuiScrollPanel", l_raygui_GuiScrollPanel},
  {"GuiScrollPanelU", l_raygui_GuiScrollPanelU},
  {"GuiSetStyle", l_raygui_GuiSetStyle},
  {"GuiSlider", l_raygui_GuiSlider},
  {"GuiSliderBar", l_raygui_GuiSliderBar},
  {"GuiSliderPro", l_raygui_GuiSliderPro},
  {"GuiSpinner", l_raygui_GuiSpinner},
  {"GuiSpinnerU", l_raygui_GuiSpinnerU},
  {"GuiState", l_raygui_GuiState},
  {"GuiStatusBar", l_raygui_GuiStatusBar},
  {"GuiTextBox", l_raygui_GuiTextBox},
  {"GuiTextBoxCopy", l_raygui_GuiTextBoxCopy},
  {"GuiTextBoxCut", l_raygui_GuiTextBoxCut},
  {"GuiTextBoxDelete", l_raygui_GuiTextBoxDelete},
  {"GuiTextBoxGetActive", l_raygui_GuiTextBoxGetActive},
  {"GuiTextBoxGetByteIndex", l_raygui_GuiTextBoxGetByteIndex},
  {"GuiTextBoxGetCursor", l_raygui_GuiTextBoxGetCursor},
  {"GuiTextBoxGetSelection", l_raygui_GuiTextBoxGetSelection},
  {"GuiTextBoxGetState", l_raygui_GuiTextBoxGetState},
  {"GuiTextBoxIsActive", l_raygui_GuiTextBoxIsActive},
  {"GuiTextBoxMulti", l_raygui_GuiTextBoxMulti},
  {"GuiTextBoxPaste", l_raygui_GuiTextBoxPaste},
  {"GuiTextBoxSelectAll", l_raygui_GuiTextBoxSelectAll},
  {"GuiTextBoxSetActive", l_raygui_GuiTextBoxSetActive},
  {"GuiTextBoxSetCursor", l_raygui_GuiTextBoxSetCursor},
  {"GuiTextBoxSetSelection", l_raygui_GuiTextBoxSetSelection},
  {"GuiTextBoxSetState", l_raygui_GuiTextBoxSetState},
  {"GuiTextInputBox", l_raygui_GuiTextInputBox},
  {"GuiToggle", l_raygui_GuiToggle},
  {"GuiToggleGroup", l_raygui_GuiToggleGroup},
  {"GuiUnlock", l_raygui_GuiUnlock},
  {"GuiUpdateStyleComplete", l_raygui_GuiUpdateStyleComplete},
  {"GuiValueBox", l_raygui_GuiValueBox},
  {"GuiValueBoxU", l_raygui_GuiValueBoxU},
  {"GuiWindowBox", l_raygui_GuiWindowBox},
  {"GuiButtonU", l_raygui_GuiButtonU},
  {"GuiCheckBoxU", l_raygui_GuiCheckBoxU},
  {"GuiColorBarAlphaU", l_raygui_GuiColorBarAlphaU},
  {"GuiColorBarHueU", l_raygui_GuiColorBarHueU},
  {"GuiColorPanelU", l_raygui_GuiColorPanelU},
  {"GuiColorPickerU", l_raygui_GuiColorPickerU},
  {"GuiComboBoxU", l_raygui_GuiComboBoxU},
  {"GuiDummyRecU", l_raygui_GuiDummyRecU},
  {"GuiGridU", l_raygui_GuiGridU},
  {"GuiGroupBoxU", l_raygui_GuiGroupBoxU},
  {"GuiImageButtonU", l_raygui_GuiImageButtonU},
  {"GuiImageButtonExU", l_raygui_GuiImageButtonExU},
  {"GuiLabelU", l_raygui_GuiLabelU},
  {"GuiLabelButtonU", l_raygui_GuiLabelButtonU},
  {"GuiLineU", l_raygui_GuiLineU},
  {"GuiMessageBoxU", l_raygui_GuiMessageBoxU},
  {"GuiPanelU", l_raygui_GuiPanelU},
  {"GuiProgressBarU", l_raygui_GuiProgressBarU},
  {"GuiScrollBarU", l_raygui_GuiScrollBarU},
  {"GuiScrollPanelU", l_raygui_GuiScrollPanelU},
  {"GuiSliderU", l_raygui_GuiSliderU},
  {"GuiSliderBarU", l_raygui_GuiSliderBarU},
  {"GuiSliderProU", l_raygui_GuiSliderProU},
  {"GuiStatusBarU", l_raygui_GuiStatusBarU},
  {"GuiTextBoxU", l_raygui_GuiTextBoxU},
  {"GuiTextBoxGetActiveU", l_raygui_GuiTextBoxGetActiveU},
  {"GuiTextBoxGetSelectionU", l_raygui_GuiTextBoxGetSelectionU},
  {"GuiTextBoxGetStateU", l_raygui_GuiTextBoxGetStateU},
  {"GuiTextBoxIsActiveU", l_raygui_GuiTextBoxIsActiveU},
  {"GuiTextBoxMultiU", l_raygui_GuiTextBoxMultiU},
  {"GuiTextBoxSetActiveU", l_raygui_GuiTextBoxSetActiveU},
  {"GuiTextBoxSetStateU", l_raygui_GuiTextBoxSetStateU},
  {"GuiTextInputBoxU", l_raygui_GuiTextInputBoxU},
  {"GuiToggleU", l_raygui_GuiToggleU},
  {"GuiToggleGroupU", l_raygui_GuiToggleGroupU},
  {"GuiWindowBoxU", l_raygui_GuiWindowBoxU},
  {"GuiTextBoxState", l_raygui_GuiTextBoxState_new},
  {"GuiTextBoxStateMeta", l_raygui_GuiTextBoxState_meta},
  {NULL, NULL}
};

static int l_raygui_GuiTextBoxState__eq(lua_State *L) {
  lua_getmetatable(L, 1); lua_getmetatable(L, 2);
  if (lua_rawequal(L, -1, -2) == 0) {
    lua_pushboolean(L, 0);
  } else {
    GuiTextBoxState *self = lua_touserdata(L, 1);
    GuiTextBoxState *other = lua_touserdata(L, 2);
    lua_pushboolean(L, self->cursor == other->cursor && self->start == other->start && self->index == other->index && self->select == other->select);
  }
  return 1;
}

static int l_raygui_GuiTextBoxState_unpack(lua_State *L) {
  GuiTextBoxState *self = luaL_checkudata(L, 1, "GuiTextBoxState");
  lua_pushinteger(L, self->cursor);
  lua_pushinteger(L, self->start);
  lua_pushinteger(L, self->index);
  lua_pushinteger(L, self->select);
  return 4;
}

static int l_raygui_GuiTextBoxState_set_cursor(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int cursor = luaL_checkinteger(L, 2);
  obj->cursor = cursor;
  lua_pop(L, 1);
  return 1;
}

static int l_raygui_GuiTextBoxState_get_cursor(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int result = obj->cursor;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxState_set_start(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int start = luaL_checkinteger(L, 2);
  obj->start = start;
  lua_pop(L, 1);
  return 1;
}

static int l_raygui_GuiTextBoxState_get_start(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int result = obj->start;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxState_set_index(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int index = luaL_checkinteger(L, 2);
  obj->index = index;
  lua_pop(L, 1);
  return 1;
}

static int l_raygui_GuiTextBoxState_get_index(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int result = obj->index;
  lua_pushinteger(L, result);
  return 1;
}

static int l_raygui_GuiTextBoxState_set_select(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int select = luaL_checkinteger(L, 2);
  obj->select = select;
  lua_pop(L, 1);
  return 1;
}

static int l_raygui_GuiTextBoxState_get_select(lua_State *L) {
  GuiTextBoxState* obj = luaL_checkudata(L, 1, "GuiTextBoxState");
  int result = obj->select;
  lua_pushinteger(L, result);
  return 1;
}

static const luaL_Reg l_raygui_GuiTextBoxState[] = {
  {"getCursor", l_raygui_GuiTextBoxState_get_cursor},
  {"setCursor", l_raygui_GuiTextBoxState_set_cursor},
  {"getStart", l_raygui_GuiTextBoxState_get_start},
  {"setStart", l_raygui_GuiTextBoxState_set_start},
  {"getIndex", l_raygui_GuiTextBoxState_get_index},
  {"setIndex", l_raygui_GuiTextBoxState_set_index},
  {"getSelect", l_raygui_GuiTextBoxState_get_select},
  {"setSelect", l_raygui_GuiTextBoxState_set_select},
  {"__eq", l_raygui_GuiTextBoxState__eq},
  {"unpack", l_raygui_GuiTextBoxState_unpack},
  {NULL, NULL}
};

static void l_raygui_GuiTextBoxState_register(lua_State *L, const char *ref) {
  luaL_newmetatable(L, ref ? ref : "GuiTextBoxState");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, l_raygui_GuiTextBoxState, 0);
  lua_pop(L, 1);
}

LUAMOD_API int luaopen_raygui(lua_State *L) {
  luaL_newlib(L, l_raygui_functions);
  l_raygui_GuiTextBoxState_register(L, NULL);
  lua_pushinteger(L, TEXTEDIT_CURSOR_BLINK_FRAMES);
  lua_setfield(L, -2, "TEXTEDIT_CURSOR_BLINK_FRAMES");
  lua_pushinteger(L, NUM_CONTROLS);
  lua_setfield(L, -2, "NUM_CONTROLS");
  lua_pushinteger(L, NUM_PROPS_DEFAULT);
  lua_setfield(L, -2, "NUM_PROPS_DEFAULT");
  lua_pushinteger(L, NUM_PROPS_EXTENDED);
  lua_setfield(L, -2, "NUM_PROPS_EXTENDED");
  lua_pushinteger(L, GUI_STATE_NORMAL);
  lua_setfield(L, -2, "GUI_STATE_NORMAL");
  lua_pushinteger(L, GUI_STATE_FOCUSED);
  lua_setfield(L, -2, "GUI_STATE_FOCUSED");
  lua_pushinteger(L, GUI_STATE_PRESSED);
  lua_setfield(L, -2, "GUI_STATE_PRESSED");
  lua_pushinteger(L, GUI_STATE_DISABLED);
  lua_setfield(L, -2, "GUI_STATE_DISABLED");
  lua_pushinteger(L, GUI_TEXT_ALIGN_LEFT);
  lua_setfield(L, -2, "GUI_TEXT_ALIGN_LEFT");
  lua_pushinteger(L, GUI_TEXT_ALIGN_CENTER);
  lua_setfield(L, -2, "GUI_TEXT_ALIGN_CENTER");
  lua_pushinteger(L, GUI_TEXT_ALIGN_RIGHT);
  lua_setfield(L, -2, "GUI_TEXT_ALIGN_RIGHT");
  lua_pushinteger(L, DEFAULT);
  lua_setfield(L, -2, "DEFAULT");
  lua_pushinteger(L, LABEL);
  lua_setfield(L, -2, "LABEL");
  lua_pushinteger(L, BUTTON);
  lua_setfield(L, -2, "BUTTON");
  lua_pushinteger(L, TOGGLE);
  lua_setfield(L, -2, "TOGGLE");
  lua_pushinteger(L, SLIDER);
  lua_setfield(L, -2, "SLIDER");
  lua_pushinteger(L, PROGRESSBAR);
  lua_setfield(L, -2, "PROGRESSBAR");
  lua_pushinteger(L, CHECKBOX);
  lua_setfield(L, -2, "CHECKBOX");
  lua_pushinteger(L, COMBOBOX);
  lua_setfield(L, -2, "COMBOBOX");
  lua_pushinteger(L, DROPDOWNBOX);
  lua_setfield(L, -2, "DROPDOWNBOX");
  lua_pushinteger(L, TEXTBOX);
  lua_setfield(L, -2, "TEXTBOX");
  lua_pushinteger(L, VALUEBOX);
  lua_setfield(L, -2, "VALUEBOX");
  lua_pushinteger(L, SPINNER);
  lua_setfield(L, -2, "SPINNER");
  lua_pushinteger(L, LISTVIEW);
  lua_setfield(L, -2, "LISTVIEW");
  lua_pushinteger(L, COLORPICKER);
  lua_setfield(L, -2, "COLORPICKER");
  lua_pushinteger(L, SCROLLBAR);
  lua_setfield(L, -2, "SCROLLBAR");
  lua_pushinteger(L, RESERVED);
  lua_setfield(L, -2, "RESERVED");
  lua_pushinteger(L, BORDER_COLOR_NORMAL);
  lua_setfield(L, -2, "BORDER_COLOR_NORMAL");
  lua_pushinteger(L, BASE_COLOR_NORMAL);
  lua_setfield(L, -2, "BASE_COLOR_NORMAL");
  lua_pushinteger(L, TEXT_COLOR_NORMAL);
  lua_setfield(L, -2, "TEXT_COLOR_NORMAL");
  lua_pushinteger(L, BORDER_COLOR_FOCUSED);
  lua_setfield(L, -2, "BORDER_COLOR_FOCUSED");
  lua_pushinteger(L, BASE_COLOR_FOCUSED);
  lua_setfield(L, -2, "BASE_COLOR_FOCUSED");
  lua_pushinteger(L, TEXT_COLOR_FOCUSED);
  lua_setfield(L, -2, "TEXT_COLOR_FOCUSED");
  lua_pushinteger(L, BORDER_COLOR_PRESSED);
  lua_setfield(L, -2, "BORDER_COLOR_PRESSED");
  lua_pushinteger(L, BASE_COLOR_PRESSED);
  lua_setfield(L, -2, "BASE_COLOR_PRESSED");
  lua_pushinteger(L, TEXT_COLOR_PRESSED);
  lua_setfield(L, -2, "TEXT_COLOR_PRESSED");
  lua_pushinteger(L, BORDER_COLOR_DISABLED);
  lua_setfield(L, -2, "BORDER_COLOR_DISABLED");
  lua_pushinteger(L, BASE_COLOR_DISABLED);
  lua_setfield(L, -2, "BASE_COLOR_DISABLED");
  lua_pushinteger(L, TEXT_COLOR_DISABLED);
  lua_setfield(L, -2, "TEXT_COLOR_DISABLED");
  lua_pushinteger(L, BORDER_WIDTH);
  lua_setfield(L, -2, "BORDER_WIDTH");
  lua_pushinteger(L, INNER_PADDING);
  lua_setfield(L, -2, "INNER_PADDING");
  lua_pushinteger(L, TEXT_ALIGNMENT);
  lua_setfield(L, -2, "TEXT_ALIGNMENT");
  lua_pushinteger(L, RESERVED02);
  lua_setfield(L, -2, "RESERVED02");
  lua_pushinteger(L, TEXT_SIZE);
  lua_setfield(L, -2, "TEXT_SIZE");
  lua_pushinteger(L, TEXT_SPACING);
  lua_setfield(L, -2, "TEXT_SPACING");
  lua_pushinteger(L, LINE_COLOR);
  lua_setfield(L, -2, "LINE_COLOR");
  lua_pushinteger(L, BACKGROUND_COLOR);
  lua_setfield(L, -2, "BACKGROUND_COLOR");
  lua_pushinteger(L, GROUP_PADDING);
  lua_setfield(L, -2, "GROUP_PADDING");
  lua_pushinteger(L, SLIDER_WIDTH);
  lua_setfield(L, -2, "SLIDER_WIDTH");
  lua_pushinteger(L, TEXT_PADDING);
  lua_setfield(L, -2, "TEXT_PADDING");
  lua_pushinteger(L, CHECK_TEXT_PADDING);
  lua_setfield(L, -2, "CHECK_TEXT_PADDING");
  lua_pushinteger(L, SELECTOR_WIDTH);
  lua_setfield(L, -2, "SELECTOR_WIDTH");
  lua_pushinteger(L, SELECTOR_PADDING);
  lua_setfield(L, -2, "SELECTOR_PADDING");
  lua_pushinteger(L, ARROW_RIGHT_PADDING);
  lua_setfield(L, -2, "ARROW_RIGHT_PADDING");
  lua_pushinteger(L, MULTILINE_PADDING);
  lua_setfield(L, -2, "MULTILINE_PADDING");
  lua_pushinteger(L, COLOR_SELECTED_FG);
  lua_setfield(L, -2, "COLOR_SELECTED_FG");
  lua_pushinteger(L, COLOR_SELECTED_BG);
  lua_setfield(L, -2, "COLOR_SELECTED_BG");
  lua_pushinteger(L, SELECT_BUTTON_WIDTH);
  lua_setfield(L, -2, "SELECT_BUTTON_WIDTH");
  lua_pushinteger(L, SELECT_BUTTON_PADDING);
  lua_setfield(L, -2, "SELECT_BUTTON_PADDING");
  lua_pushinteger(L, SELECT_BUTTON_BORDER_WIDTH);
  lua_setfield(L, -2, "SELECT_BUTTON_BORDER_WIDTH");
  lua_pushinteger(L, ARROWS_SIZE);
  lua_setfield(L, -2, "ARROWS_SIZE");
  lua_pushinteger(L, SLIDER_PADDING);
  lua_setfield(L, -2, "SLIDER_PADDING");
  lua_pushinteger(L, SLIDER_SIZE);
  lua_setfield(L, -2, "SLIDER_SIZE");
  lua_pushinteger(L, SCROLL_SPEED);
  lua_setfield(L, -2, "SCROLL_SPEED");
  lua_pushinteger(L, SHOW_SPINNER_BUTTONS);
  lua_setfield(L, -2, "SHOW_SPINNER_BUTTONS");
  lua_pushinteger(L, SCROLLBAR_LEFT_SIDE);
  lua_setfield(L, -2, "SCROLLBAR_LEFT_SIDE");
  lua_pushinteger(L, SCROLLBAR_RIGHT_SIDE);
  lua_setfield(L, -2, "SCROLLBAR_RIGHT_SIDE");
  lua_pushinteger(L, ELEMENTS_HEIGHT);
  lua_setfield(L, -2, "ELEMENTS_HEIGHT");
  lua_pushinteger(L, ELEMENTS_PADDING);
  lua_setfield(L, -2, "ELEMENTS_PADDING");
  lua_pushinteger(L, SCROLLBAR_WIDTH);
  lua_setfield(L, -2, "SCROLLBAR_WIDTH");
  lua_pushinteger(L, SCROLLBAR_SIDE);
  lua_setfield(L, -2, "SCROLLBAR_SIDE");
  lua_pushinteger(L, COLOR_SELECTOR_SIZE);
  lua_setfield(L, -2, "COLOR_SELECTOR_SIZE");
  lua_pushinteger(L, BAR_WIDTH);
  lua_setfield(L, -2, "BAR_WIDTH");
  lua_pushinteger(L, BAR_PADDING);
  lua_setfield(L, -2, "BAR_PADDING");
  lua_pushinteger(L, BAR_SELECTOR_HEIGHT);
  lua_setfield(L, -2, "BAR_SELECTOR_HEIGHT");
  lua_pushinteger(L, BAR_SELECTOR_PADDING);
  lua_setfield(L, -2, "BAR_SELECTOR_PADDING");
  lua_pushinteger(L, KEY_RIGHT);
  lua_setfield(L, -2, "KEY_RIGHT");
  lua_pushinteger(L, KEY_LEFT);
  lua_setfield(L, -2, "KEY_LEFT");
  lua_pushinteger(L, KEY_DOWN);
  lua_setfield(L, -2, "KEY_DOWN");
  lua_pushinteger(L, KEY_UP);
  lua_setfield(L, -2, "KEY_UP");
  lua_pushinteger(L, KEY_BACKSPACE);
  lua_setfield(L, -2, "KEY_BACKSPACE");
  lua_pushinteger(L, KEY_ENTER);
  lua_setfield(L, -2, "KEY_ENTER");
  lua_pushinteger(L, MOUSE_LEFT_BUTTON);
  lua_setfield(L, -2, "MOUSE_LEFT_BUTTON");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = WHITE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "WHITE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = BLACK; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "BLACK");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = RAYWHITE; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "RAYWHITE");
  *((Color *)lua_newuserdata(L, sizeof(Color))) = GRAY; luaL_setmetatable(L, "Color");
  lua_setfield(L, -2, "GRAY");
  lua_pushinteger(L, ICON_TEXT_PADDING);
  lua_setfield(L, -2, "ICON_TEXT_PADDING");
  lua_pushinteger(L, ICON_TEXT_PADDING);
  lua_setfield(L, -2, "ICON_TEXT_PADDING");
  lua_pushinteger(L, WINDOW_CLOSE_BUTTON_PADDING);
  lua_setfield(L, -2, "WINDOW_CLOSE_BUTTON_PADDING");
  lua_pushinteger(L, WINDOW_STATUSBAR_HEIGHT);
  lua_setfield(L, -2, "WINDOW_STATUSBAR_HEIGHT");
  lua_pushinteger(L, GROUPBOX_LINE_THICK);
  lua_setfield(L, -2, "GROUPBOX_LINE_THICK");
  lua_pushinteger(L, GROUPBOX_TEXT_PADDING);
  lua_setfield(L, -2, "GROUPBOX_TEXT_PADDING");
  lua_pushinteger(L, GROUPBOX_PADDING);
  lua_setfield(L, -2, "GROUPBOX_PADDING");
  lua_pushinteger(L, LINE_THICK);
  lua_setfield(L, -2, "LINE_THICK");
  lua_pushinteger(L, LINE_TEXT_PADDING);
  lua_setfield(L, -2, "LINE_TEXT_PADDING");
  lua_pushinteger(L, LINE_TEXT_SPACING);
  lua_setfield(L, -2, "LINE_TEXT_SPACING");
  lua_pushinteger(L, PANEL_BORDER_WIDTH);
  lua_setfield(L, -2, "PANEL_BORDER_WIDTH");
  lua_pushnumber(L, GUI_SPINNER_HOLD_SPEED);
  lua_setfield(L, -2, "GUI_SPINNER_HOLD_SPEED");
  lua_pushinteger(L, VALUEBOX_MAX_CHARS);
  lua_setfield(L, -2, "VALUEBOX_MAX_CHARS");
  lua_pushinteger(L, GUI_TEXTBOX_CURSOR_SPEED_MODIFIER);
  lua_setfield(L, -2, "GUI_TEXTBOX_CURSOR_SPEED_MODIFIER");
  lua_pushinteger(L, VALUEBOX_MAX_CHARS);
  lua_setfield(L, -2, "VALUEBOX_MAX_CHARS");
  lua_pushinteger(L, COLORBARALPHA_CHECKED_SIZE);
  lua_setfield(L, -2, "COLORBARALPHA_CHECKED_SIZE");
  lua_pushinteger(L, MESSAGEBOX_BUTTON_HEIGHT);
  lua_setfield(L, -2, "MESSAGEBOX_BUTTON_HEIGHT");
  lua_pushinteger(L, MESSAGEBOX_BUTTON_PADDING);
  lua_setfield(L, -2, "MESSAGEBOX_BUTTON_PADDING");
  lua_pushnumber(L, GRID_COLOR_ALPHA);
  lua_setfield(L, -2, "GRID_COLOR_ALPHA");
  lua_pushinteger(L, MAX_TEXT_BUFFER_LENGTH);
  lua_setfield(L, -2, "MAX_TEXT_BUFFER_LENGTH");
  lua_pushinteger(L, MAX_SUBSTRINGS_COUNT);
  lua_setfield(L, -2, "MAX_SUBSTRINGS_COUNT");
  lua_pushinteger(L, RICONS_COUNT);
  lua_setfield(L, -2, "RICONS_COUNT");
  lua_pushinteger(L, RICONS_SIZE);
  lua_setfield(L, -2, "RICONS_SIZE");
  lua_pushinteger(L, RICON_NONE);
  lua_setfield(L, -2, "RICON_NONE");
  lua_pushinteger(L, RICON_FOLDER_FILE_OPEN);
  lua_setfield(L, -2, "RICON_FOLDER_FILE_OPEN");
  lua_pushinteger(L, RICON_FILE_SAVE_CLASSIC);
  lua_setfield(L, -2, "RICON_FILE_SAVE_CLASSIC");
  lua_pushinteger(L, RICON_FOLDER_OPEN);
  lua_setfield(L, -2, "RICON_FOLDER_OPEN");
  lua_pushinteger(L, RICON_FOLDER_SAVE);
  lua_setfield(L, -2, "RICON_FOLDER_SAVE");
  lua_pushinteger(L, RICON_FILE_OPEN);
  lua_setfield(L, -2, "RICON_FILE_OPEN");
  lua_pushinteger(L, RICON_FILE_SAVE);
  lua_setfield(L, -2, "RICON_FILE_SAVE");
  lua_pushinteger(L, RICON_FILE_EXPORT);
  lua_setfield(L, -2, "RICON_FILE_EXPORT");
  lua_pushinteger(L, RICON_FILE_NEW);
  lua_setfield(L, -2, "RICON_FILE_NEW");
  lua_pushinteger(L, RICON_FILE_DELETE);
  lua_setfield(L, -2, "RICON_FILE_DELETE");
  lua_pushinteger(L, RICON_FILETYPE_TEXT);
  lua_setfield(L, -2, "RICON_FILETYPE_TEXT");
  lua_pushinteger(L, RICON_FILETYPE_AUDIO);
  lua_setfield(L, -2, "RICON_FILETYPE_AUDIO");
  lua_pushinteger(L, RICON_FILETYPE_IMAGE);
  lua_setfield(L, -2, "RICON_FILETYPE_IMAGE");
  lua_pushinteger(L, RICON_FILETYPE_PLAY);
  lua_setfield(L, -2, "RICON_FILETYPE_PLAY");
  lua_pushinteger(L, RICON_FILETYPE_VIDEO);
  lua_setfield(L, -2, "RICON_FILETYPE_VIDEO");
  lua_pushinteger(L, RICON_FILETYPE_INFO);
  lua_setfield(L, -2, "RICON_FILETYPE_INFO");
  lua_pushinteger(L, RICON_FILE_COPY);
  lua_setfield(L, -2, "RICON_FILE_COPY");
  lua_pushinteger(L, RICON_FILE_CUT);
  lua_setfield(L, -2, "RICON_FILE_CUT");
  lua_pushinteger(L, RICON_FILE_PASTE);
  lua_setfield(L, -2, "RICON_FILE_PASTE");
  lua_pushinteger(L, RICON_CURSOR_HAND);
  lua_setfield(L, -2, "RICON_CURSOR_HAND");
  lua_pushinteger(L, RICON_CURSOR_POINTER);
  lua_setfield(L, -2, "RICON_CURSOR_POINTER");
  lua_pushinteger(L, RICON_CURSOR_CLASSIC);
  lua_setfield(L, -2, "RICON_CURSOR_CLASSIC");
  lua_pushinteger(L, RICON_PENCIL);
  lua_setfield(L, -2, "RICON_PENCIL");
  lua_pushinteger(L, RICON_PENCIL_BIG);
  lua_setfield(L, -2, "RICON_PENCIL_BIG");
  lua_pushinteger(L, RICON_BRUSH_CLASSIC);
  lua_setfield(L, -2, "RICON_BRUSH_CLASSIC");
  lua_pushinteger(L, RICON_BRUSH_PAINTER);
  lua_setfield(L, -2, "RICON_BRUSH_PAINTER");
  lua_pushinteger(L, RICON_WATER_DROP);
  lua_setfield(L, -2, "RICON_WATER_DROP");
  lua_pushinteger(L, RICON_COLOR_PICKER);
  lua_setfield(L, -2, "RICON_COLOR_PICKER");
  lua_pushinteger(L, RICON_RUBBER);
  lua_setfield(L, -2, "RICON_RUBBER");
  lua_pushinteger(L, RICON_COLOR_BUCKET);
  lua_setfield(L, -2, "RICON_COLOR_BUCKET");
  lua_pushinteger(L, RICON_TEXT_T);
  lua_setfield(L, -2, "RICON_TEXT_T");
  lua_pushinteger(L, RICON_TEXT_A);
  lua_setfield(L, -2, "RICON_TEXT_A");
  lua_pushinteger(L, RICON_SCALE);
  lua_setfield(L, -2, "RICON_SCALE");
  lua_pushinteger(L, RICON_RESIZE);
  lua_setfield(L, -2, "RICON_RESIZE");
  lua_pushinteger(L, RICON_FILTER_POINT);
  lua_setfield(L, -2, "RICON_FILTER_POINT");
  lua_pushinteger(L, RICON_FILTER_BILINEAR);
  lua_setfield(L, -2, "RICON_FILTER_BILINEAR");
  lua_pushinteger(L, RICON_CROP);
  lua_setfield(L, -2, "RICON_CROP");
  lua_pushinteger(L, RICON_CROP_ALPHA);
  lua_setfield(L, -2, "RICON_CROP_ALPHA");
  lua_pushinteger(L, RICON_SQUARE_TOGGLE);
  lua_setfield(L, -2, "RICON_SQUARE_TOGGLE");
  lua_pushinteger(L, RICON_SIMMETRY);
  lua_setfield(L, -2, "RICON_SIMMETRY");
  lua_pushinteger(L, RICON_SIMMETRY_HORIZONTAL);
  lua_setfield(L, -2, "RICON_SIMMETRY_HORIZONTAL");
  lua_pushinteger(L, RICON_SIMMETRY_VERTICAL);
  lua_setfield(L, -2, "RICON_SIMMETRY_VERTICAL");
  lua_pushinteger(L, RICON_LENS);
  lua_setfield(L, -2, "RICON_LENS");
  lua_pushinteger(L, RICON_LENS_BIG);
  lua_setfield(L, -2, "RICON_LENS_BIG");
  lua_pushinteger(L, RICON_EYE_ON);
  lua_setfield(L, -2, "RICON_EYE_ON");
  lua_pushinteger(L, RICON_EYE_OFF);
  lua_setfield(L, -2, "RICON_EYE_OFF");
  lua_pushinteger(L, RICON_FILTER_TOP);
  lua_setfield(L, -2, "RICON_FILTER_TOP");
  lua_pushinteger(L, RICON_FILTER);
  lua_setfield(L, -2, "RICON_FILTER");
  lua_pushinteger(L, RICON_TARGET_POINT);
  lua_setfield(L, -2, "RICON_TARGET_POINT");
  lua_pushinteger(L, RICON_TARGET_SMALL);
  lua_setfield(L, -2, "RICON_TARGET_SMALL");
  lua_pushinteger(L, RICON_TARGET_BIG);
  lua_setfield(L, -2, "RICON_TARGET_BIG");
  lua_pushinteger(L, RICON_TARGET_MOVE);
  lua_setfield(L, -2, "RICON_TARGET_MOVE");
  lua_pushinteger(L, RICON_CURSOR_MOVE);
  lua_setfield(L, -2, "RICON_CURSOR_MOVE");
  lua_pushinteger(L, RICON_CURSOR_SCALE);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE");
  lua_pushinteger(L, RICON_CURSOR_SCALE_RIGHT);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE_RIGHT");
  lua_pushinteger(L, RICON_CURSOR_SCALE_LEFT);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE_LEFT");
  lua_pushinteger(L, RICON_UNDO);
  lua_setfield(L, -2, "RICON_UNDO");
  lua_pushinteger(L, RICON_REDO);
  lua_setfield(L, -2, "RICON_REDO");
  lua_pushinteger(L, RICON_REREDO);
  lua_setfield(L, -2, "RICON_REREDO");
  lua_pushinteger(L, RICON_MUTATE);
  lua_setfield(L, -2, "RICON_MUTATE");
  lua_pushinteger(L, RICON_ROTATE);
  lua_setfield(L, -2, "RICON_ROTATE");
  lua_pushinteger(L, RICON_REPEAT);
  lua_setfield(L, -2, "RICON_REPEAT");
  lua_pushinteger(L, RICON_SHUFFLE);
  lua_setfield(L, -2, "RICON_SHUFFLE");
  lua_pushinteger(L, RICON_EMPTYBOX);
  lua_setfield(L, -2, "RICON_EMPTYBOX");
  lua_pushinteger(L, RICON_TARGET);
  lua_setfield(L, -2, "RICON_TARGET");
  lua_pushinteger(L, RICON_TARGET_SMALL_FILL);
  lua_setfield(L, -2, "RICON_TARGET_SMALL_FILL");
  lua_pushinteger(L, RICON_TARGET_BIG_FILL);
  lua_setfield(L, -2, "RICON_TARGET_BIG_FILL");
  lua_pushinteger(L, RICON_TARGET_MOVE_FILL);
  lua_setfield(L, -2, "RICON_TARGET_MOVE_FILL");
  lua_pushinteger(L, RICON_CURSOR_MOVE_FILL);
  lua_setfield(L, -2, "RICON_CURSOR_MOVE_FILL");
  lua_pushinteger(L, RICON_CURSOR_SCALE_FILL);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE_FILL");
  lua_pushinteger(L, RICON_CURSOR_SCALE_RIGHT_FILL);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE_RIGHT_FILL");
  lua_pushinteger(L, RICON_CURSOR_SCALE_LEFT_FILL);
  lua_setfield(L, -2, "RICON_CURSOR_SCALE_LEFT_FILL");
  lua_pushinteger(L, RICON_UNDO_FILL);
  lua_setfield(L, -2, "RICON_UNDO_FILL");
  lua_pushinteger(L, RICON_REDO_FILL);
  lua_setfield(L, -2, "RICON_REDO_FILL");
  lua_pushinteger(L, RICON_REREDO_FILL);
  lua_setfield(L, -2, "RICON_REREDO_FILL");
  lua_pushinteger(L, RICON_MUTATE_FILL);
  lua_setfield(L, -2, "RICON_MUTATE_FILL");
  lua_pushinteger(L, RICON_ROTATE_FILL);
  lua_setfield(L, -2, "RICON_ROTATE_FILL");
  lua_pushinteger(L, RICON_REPEAT_FILL);
  lua_setfield(L, -2, "RICON_REPEAT_FILL");
  lua_pushinteger(L, RICON_SHUFFLE_FILL);
  lua_setfield(L, -2, "RICON_SHUFFLE_FILL");
  lua_pushinteger(L, RICON_EMPTYBOX_SMALL);
  lua_setfield(L, -2, "RICON_EMPTYBOX_SMALL");
  lua_pushinteger(L, RICON_BOX);
  lua_setfield(L, -2, "RICON_BOX");
  lua_pushinteger(L, RICON_BOX_TOP);
  lua_setfield(L, -2, "RICON_BOX_TOP");
  lua_pushinteger(L, RICON_BOX_TOP_RIGHT);
  lua_setfield(L, -2, "RICON_BOX_TOP_RIGHT");
  lua_pushinteger(L, RICON_BOX_RIGHT);
  lua_setfield(L, -2, "RICON_BOX_RIGHT");
  lua_pushinteger(L, RICON_BOX_BOTTOM_RIGHT);
  lua_setfield(L, -2, "RICON_BOX_BOTTOM_RIGHT");
  lua_pushinteger(L, RICON_BOX_BOTTOM);
  lua_setfield(L, -2, "RICON_BOX_BOTTOM");
  lua_pushinteger(L, RICON_BOX_BOTTOM_LEFT);
  lua_setfield(L, -2, "RICON_BOX_BOTTOM_LEFT");
  lua_pushinteger(L, RICON_BOX_LEFT);
  lua_setfield(L, -2, "RICON_BOX_LEFT");
  lua_pushinteger(L, RICON_BOX_TOP_LEFT);
  lua_setfield(L, -2, "RICON_BOX_TOP_LEFT");
  lua_pushinteger(L, RICON_BOX_CENTER);
  lua_setfield(L, -2, "RICON_BOX_CENTER");
  lua_pushinteger(L, RICON_BOX_CIRCLE_MASK);
  lua_setfield(L, -2, "RICON_BOX_CIRCLE_MASK");
  lua_pushinteger(L, RICON_POT);
  lua_setfield(L, -2, "RICON_POT");
  lua_pushinteger(L, RICON_ALPHA_MULTIPLY);
  lua_setfield(L, -2, "RICON_ALPHA_MULTIPLY");
  lua_pushinteger(L, RICON_ALPHA_CLEAR);
  lua_setfield(L, -2, "RICON_ALPHA_CLEAR");
  lua_pushinteger(L, RICON_DITHERING);
  lua_setfield(L, -2, "RICON_DITHERING");
  lua_pushinteger(L, RICON_MIPMAPS);
  lua_setfield(L, -2, "RICON_MIPMAPS");
  lua_pushinteger(L, RICON_BOX_GRID);
  lua_setfield(L, -2, "RICON_BOX_GRID");
  lua_pushinteger(L, RICON_GRID);
  lua_setfield(L, -2, "RICON_GRID");
  lua_pushinteger(L, RICON_BOX_CORNERS_SMALL);
  lua_setfield(L, -2, "RICON_BOX_CORNERS_SMALL");
  lua_pushinteger(L, RICON_BOX_CORNERS_BIG);
  lua_setfield(L, -2, "RICON_BOX_CORNERS_BIG");
  lua_pushinteger(L, RICON_FOUR_BOXES);
  lua_setfield(L, -2, "RICON_FOUR_BOXES");
  lua_pushinteger(L, RICON_GRID_FILL);
  lua_setfield(L, -2, "RICON_GRID_FILL");
  lua_pushinteger(L, RICON_BOX_MULTISIZE);
  lua_setfield(L, -2, "RICON_BOX_MULTISIZE");
  lua_pushinteger(L, RICON_ZOOM_SMALL);
  lua_setfield(L, -2, "RICON_ZOOM_SMALL");
  lua_pushinteger(L, RICON_ZOOM_MEDIUM);
  lua_setfield(L, -2, "RICON_ZOOM_MEDIUM");
  lua_pushinteger(L, RICON_ZOOM_BIG);
  lua_setfield(L, -2, "RICON_ZOOM_BIG");
  lua_pushinteger(L, RICON_ZOOM_ALL);
  lua_setfield(L, -2, "RICON_ZOOM_ALL");
  lua_pushinteger(L, RICON_ZOOM_CENTER);
  lua_setfield(L, -2, "RICON_ZOOM_CENTER");
  lua_pushinteger(L, RICON_BOX_DOTS_SMALL);
  lua_setfield(L, -2, "RICON_BOX_DOTS_SMALL");
  lua_pushinteger(L, RICON_BOX_DOTS_BIG);
  lua_setfield(L, -2, "RICON_BOX_DOTS_BIG");
  lua_pushinteger(L, RICON_BOX_CONCENTRIC);
  lua_setfield(L, -2, "RICON_BOX_CONCENTRIC");
  lua_pushinteger(L, RICON_BOX_GRID_BIG);
  lua_setfield(L, -2, "RICON_BOX_GRID_BIG");
  lua_pushinteger(L, RICON_OK_TICK);
  lua_setfield(L, -2, "RICON_OK_TICK");
  lua_pushinteger(L, RICON_CROSS);
  lua_setfield(L, -2, "RICON_CROSS");
  lua_pushinteger(L, RICON_ARROW_LEFT);
  lua_setfield(L, -2, "RICON_ARROW_LEFT");
  lua_pushinteger(L, RICON_ARROW_RIGHT);
  lua_setfield(L, -2, "RICON_ARROW_RIGHT");
  lua_pushinteger(L, RICON_ARROW_BOTTOM);
  lua_setfield(L, -2, "RICON_ARROW_BOTTOM");
  lua_pushinteger(L, RICON_ARROW_TOP);
  lua_setfield(L, -2, "RICON_ARROW_TOP");
  lua_pushinteger(L, RICON_ARROW_LEFT_FILL);
  lua_setfield(L, -2, "RICON_ARROW_LEFT_FILL");
  lua_pushinteger(L, RICON_ARROW_RIGHT_FILL);
  lua_setfield(L, -2, "RICON_ARROW_RIGHT_FILL");
  lua_pushinteger(L, RICON_ARROW_BOTTOM_FILL);
  lua_setfield(L, -2, "RICON_ARROW_BOTTOM_FILL");
  lua_pushinteger(L, RICON_ARROW_TOP_FILL);
  lua_setfield(L, -2, "RICON_ARROW_TOP_FILL");
  lua_pushinteger(L, RICON_AUDIO);
  lua_setfield(L, -2, "RICON_AUDIO");
  lua_pushinteger(L, RICON_FX);
  lua_setfield(L, -2, "RICON_FX");
  lua_pushinteger(L, RICON_WAVE);
  lua_setfield(L, -2, "RICON_WAVE");
  lua_pushinteger(L, RICON_WAVE_SINUS);
  lua_setfield(L, -2, "RICON_WAVE_SINUS");
  lua_pushinteger(L, RICON_WAVE_SQUARE);
  lua_setfield(L, -2, "RICON_WAVE_SQUARE");
  lua_pushinteger(L, RICON_WAVE_TRIANGULAR);
  lua_setfield(L, -2, "RICON_WAVE_TRIANGULAR");
  lua_pushinteger(L, RICON_CROSS_SMALL);
  lua_setfield(L, -2, "RICON_CROSS_SMALL");
  lua_pushinteger(L, RICON_PLAYER_PREVIOUS);
  lua_setfield(L, -2, "RICON_PLAYER_PREVIOUS");
  lua_pushinteger(L, RICON_PLAYER_PLAY_BACK);
  lua_setfield(L, -2, "RICON_PLAYER_PLAY_BACK");
  lua_pushinteger(L, RICON_PLAYER_PLAY);
  lua_setfield(L, -2, "RICON_PLAYER_PLAY");
  lua_pushinteger(L, RICON_PLAYER_PAUSE);
  lua_setfield(L, -2, "RICON_PLAYER_PAUSE");
  lua_pushinteger(L, RICON_PLAYER_STOP);
  lua_setfield(L, -2, "RICON_PLAYER_STOP");
  lua_pushinteger(L, RICON_PLAYER_NEXT);
  lua_setfield(L, -2, "RICON_PLAYER_NEXT");
  lua_pushinteger(L, RICON_PLAYER_RECORD);
  lua_setfield(L, -2, "RICON_PLAYER_RECORD");
  lua_pushinteger(L, RICON_MAGNET);
  lua_setfield(L, -2, "RICON_MAGNET");
  lua_pushinteger(L, RICON_LOCK_CLOSE);
  lua_setfield(L, -2, "RICON_LOCK_CLOSE");
  lua_pushinteger(L, RICON_LOCK_OPEN);
  lua_setfield(L, -2, "RICON_LOCK_OPEN");
  lua_pushinteger(L, RICON_CLOCK);
  lua_setfield(L, -2, "RICON_CLOCK");
  lua_pushinteger(L, RICON_TOOLS);
  lua_setfield(L, -2, "RICON_TOOLS");
  lua_pushinteger(L, RICON_GEAR);
  lua_setfield(L, -2, "RICON_GEAR");
  lua_pushinteger(L, RICON_GEAR_BIG);
  lua_setfield(L, -2, "RICON_GEAR_BIG");
  lua_pushinteger(L, RICON_BIN);
  lua_setfield(L, -2, "RICON_BIN");
  lua_pushinteger(L, RICON_HAND_POINTER);
  lua_setfield(L, -2, "RICON_HAND_POINTER");
  lua_pushinteger(L, RICON_LASER);
  lua_setfield(L, -2, "RICON_LASER");
  lua_pushinteger(L, RICON_COIN);
  lua_setfield(L, -2, "RICON_COIN");
  lua_pushinteger(L, RICON_EXPLOSION);
  lua_setfield(L, -2, "RICON_EXPLOSION");
  lua_pushinteger(L, RICON_1UP);
  lua_setfield(L, -2, "RICON_1UP");
  lua_pushinteger(L, RICON_PLAYER);
  lua_setfield(L, -2, "RICON_PLAYER");
  lua_pushinteger(L, RICON_PLAYER_JUMP);
  lua_setfield(L, -2, "RICON_PLAYER_JUMP");
  lua_pushinteger(L, RICON_KEY);
  lua_setfield(L, -2, "RICON_KEY");
  lua_pushinteger(L, RICON_DEMON);
  lua_setfield(L, -2, "RICON_DEMON");
  lua_pushinteger(L, RICON_TEXT_POPUP);
  lua_setfield(L, -2, "RICON_TEXT_POPUP");
  lua_pushinteger(L, RICON_GEAR_EX);
  lua_setfield(L, -2, "RICON_GEAR_EX");
  lua_pushinteger(L, RICON_CRACK);
  lua_setfield(L, -2, "RICON_CRACK");
  lua_pushinteger(L, RICON_CRACK_POINTS);
  lua_setfield(L, -2, "RICON_CRACK_POINTS");
  lua_pushinteger(L, RICON_STAR);
  lua_setfield(L, -2, "RICON_STAR");
  lua_pushinteger(L, RICON_DOOR);
  lua_setfield(L, -2, "RICON_DOOR");
  lua_pushinteger(L, RICON_EXIT);
  lua_setfield(L, -2, "RICON_EXIT");
  lua_pushinteger(L, RICON_MODE_2D);
  lua_setfield(L, -2, "RICON_MODE_2D");
  lua_pushinteger(L, RICON_MODE_3D);
  lua_setfield(L, -2, "RICON_MODE_3D");
  lua_pushinteger(L, RICON_CUBE);
  lua_setfield(L, -2, "RICON_CUBE");
  lua_pushinteger(L, RICON_CUBE_FACE_TOP);
  lua_setfield(L, -2, "RICON_CUBE_FACE_TOP");
  lua_pushinteger(L, RICON_CUBE_FACE_LEFT);
  lua_setfield(L, -2, "RICON_CUBE_FACE_LEFT");
  lua_pushinteger(L, RICON_CUBE_FACE_FRONT);
  lua_setfield(L, -2, "RICON_CUBE_FACE_FRONT");
  lua_pushinteger(L, RICON_CUBE_FACE_BOTTOM);
  lua_setfield(L, -2, "RICON_CUBE_FACE_BOTTOM");
  lua_pushinteger(L, RICON_CUBE_FACE_RIGHT);
  lua_setfield(L, -2, "RICON_CUBE_FACE_RIGHT");
  lua_pushinteger(L, RICON_CUBE_FACE_BACK);
  lua_setfield(L, -2, "RICON_CUBE_FACE_BACK");
  lua_pushinteger(L, RICON_CAMERA);
  lua_setfield(L, -2, "RICON_CAMERA");
  lua_pushinteger(L, RICON_SPECIAL);
  lua_setfield(L, -2, "RICON_SPECIAL");
  lua_pushinteger(L, RICON_LINK_NET);
  lua_setfield(L, -2, "RICON_LINK_NET");
  lua_pushinteger(L, RICON_LINK_BOXES);
  lua_setfield(L, -2, "RICON_LINK_BOXES");
  lua_pushinteger(L, RICON_LINK_MULTI);
  lua_setfield(L, -2, "RICON_LINK_MULTI");
  lua_pushinteger(L, RICON_LINK);
  lua_setfield(L, -2, "RICON_LINK");
  lua_pushinteger(L, RICON_LINK_BROKE);
  lua_setfield(L, -2, "RICON_LINK_BROKE");
  lua_pushinteger(L, RICON_TEXT_NOTES);
  lua_setfield(L, -2, "RICON_TEXT_NOTES");
  lua_pushinteger(L, RICON_NOTEBOOK);
  lua_setfield(L, -2, "RICON_NOTEBOOK");
  lua_pushinteger(L, RICON_SUITCASE);
  lua_setfield(L, -2, "RICON_SUITCASE");
  lua_pushinteger(L, RICON_SUITCASE_ZIP);
  lua_setfield(L, -2, "RICON_SUITCASE_ZIP");
  lua_pushinteger(L, RICON_MAILBOX);
  lua_setfield(L, -2, "RICON_MAILBOX");
  lua_pushinteger(L, RICON_MONITOR);
  lua_setfield(L, -2, "RICON_MONITOR");
  lua_pushinteger(L, RICON_PRINTER);
  lua_setfield(L, -2, "RICON_PRINTER");
  lua_pushinteger(L, RICON_PHOTO_CAMERA);
  lua_setfield(L, -2, "RICON_PHOTO_CAMERA");
  lua_pushinteger(L, RICON_PHOTO_CAMERA_FLASH);
  lua_setfield(L, -2, "RICON_PHOTO_CAMERA_FLASH");
  lua_pushinteger(L, RICON_HOUSE);
  lua_setfield(L, -2, "RICON_HOUSE");
  lua_pushinteger(L, RICON_HEART);
  lua_setfield(L, -2, "RICON_HEART");
  lua_pushinteger(L, RICON_CORNER);
  lua_setfield(L, -2, "RICON_CORNER");
  lua_pushinteger(L, RICON_VERTICAL_BARS);
  lua_setfield(L, -2, "RICON_VERTICAL_BARS");
  lua_pushinteger(L, RICON_VERTICAL_BARS_FILL);
  lua_setfield(L, -2, "RICON_VERTICAL_BARS_FILL");
  lua_pushinteger(L, RICON_LIFE_BARS);
  lua_setfield(L, -2, "RICON_LIFE_BARS");
  lua_pushinteger(L, RICON_INFO);
  lua_setfield(L, -2, "RICON_INFO");
  lua_pushinteger(L, RICON_CROSSLINE);
  lua_setfield(L, -2, "RICON_CROSSLINE");
  lua_pushinteger(L, RICON_HELP);
  lua_setfield(L, -2, "RICON_HELP");
  lua_pushinteger(L, RICON_FILETYPE_ALPHA);
  lua_setfield(L, -2, "RICON_FILETYPE_ALPHA");
  lua_pushinteger(L, RICON_FILETYPE_HOME);
  lua_setfield(L, -2, "RICON_FILETYPE_HOME");
  lua_pushinteger(L, RICON_LAYERS_VISIBLE);
  lua_setfield(L, -2, "RICON_LAYERS_VISIBLE");
  lua_pushinteger(L, RICON_LAYERS);
  lua_setfield(L, -2, "RICON_LAYERS");
  lua_pushinteger(L, RICON_WINDOW);
  lua_setfield(L, -2, "RICON_WINDOW");
  return 1;
}
