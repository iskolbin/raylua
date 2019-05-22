local r = require('raylib')
local screenWidth, screenHeight = 800, 450
r.InitWindow(screenWidth, screenHeight, "raylib [shapes] example - fan")

r.SetTargetFPS(60)

local function UpdateDraw()
	r.BeginDrawing()
	do
		r.ClearBackground(r.WHITE)
		r.DrawText("some basic shapes available on raylib", 20, 20, 20, r.GRAY)
		r.DrawLineStrip({screenWidth/4*3, 160,  screenWidth/4*3 - 20, 230,  screenWidth/4*3 + 20, 230}, r.DARKBLUE);
    r.DrawTriangleFan({screenWidth/4*1, 160,  screenWidth/4*1 - 20, 230,  screenWidth/4*1 + 20, 230}, r.ORANGE);
	end
	r.EndDrawing()
end

if r.EmscriptenSetMainLoop then
	r.EmscriptenSetMainLoop( UpdateDraw )	
else
	while not r.WindowShouldClose() do
		UpdateDraw()
	end
	r.CloseWindow()
end
