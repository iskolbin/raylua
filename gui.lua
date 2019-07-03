local raylib = require('raylib')
local raygui = require('raygui')

local screenWidth = 690;
local screenHeight = 560;

raylib.InitWindow(screenWidth, screenHeight, "raygui - controls test suite")

while not raylib.WindowShouldClose() do
	raylib.BeginDrawing()
	do
		raylib.ClearBackground(raylib.RAYWHITE)
    raygui.GuiLineU(25,280,750,10)
    raygui.GuiGroupBoxU(20,320,190,100,  raygui.GuiIconText(raygui.RICON_GEAR, "FONT"))
    raygui.GuiLabelU(30,340,60,20, "Size");
    raygui.GuiSpinnerU(95,340,100,20,10, 10, 40, true);
    raygui.GuiLabelU(30,380,60,20, "Spacing")
    raygui.GuiSpinnerU(95,380,100,20, 1, 1, 10, true)
	end
	raylib.EndDrawing()
end

raylib.CloseWindow()
