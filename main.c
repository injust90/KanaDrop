#include "raylib.h"

int main (void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "日本語タイピング");

	float currentFps = 60;

	// Store the position for the circle and text 
	Vector2 deltaCircle = { 400, (float)screenHeight / 3.0f};
	float deltaTextY = 0;
	// The speed applied to both circles
	const float speed = 30.0f;
	const float circleRadius = 32.0f;

	SetTargetFPS(currentFps);

	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		deltaCircle.y += GetFrameTime()*speed;
		deltaTextY += GetFrameTime()*speed;

		BeginDrawing();
			ClearBackground(BLACK);

			// Draw circle to screen
			DrawCircleV(deltaCircle, circleRadius, WHITE);

			// Draw text above circles
			DrawText("Testing 日本語", 10, (int)deltaTextY, 24, WHITE);
		
		EndDrawing();
	}

	UnloadFont(jpFont);
	CloseWindow();
}
