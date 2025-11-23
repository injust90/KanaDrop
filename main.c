#include "raylib.h"

#define MAX_INPUT_CHARS 9

int main (void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	char name [MAX_INPUT_CHARS + 1] = "\0";
	int letterCount = 0;

	int framesCounter = 0;

	Rectangle textBox = { screenWidth/2.0f - 100, 180, 225, 50 };
	bool mouseOnText = false;

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
		if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
		else mouseOnText = false;

		if (mouseOnText)
		{
			// Set the window's cursor to the I-Beam
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			// Get char pressed (unicode) on the queue
			int key = GetCharPressed();
			
			// Only allows keys in range [32..125]
			while (key > 0)
			{
				if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
						name[letterCount] = (char)key;
						name[letterCount+1] = '\0';
						letterCount++;
				}

				key = GetCharPressed();
			}

			if (IsKeyPressed(KEY_BACKSPACE))
			{
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
		}

		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		if (mouseOnText) framesCounter++;
		else framesCounter = 0;

		deltaCircle.y += GetFrameTime()*speed;
		deltaTextY += GetFrameTime()*speed;

		BeginDrawing();
			ClearBackground(BLACK);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText) 
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			else
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

		    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

		    if (mouseOnText)
		    {
			if (letterCount < MAX_INPUT_CHARS)
			{
			    // Draw blinking underscore char
			    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}
			else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
		    }


			// Draw circle to screen
			// DrawCircleV(deltaCircle, circleRadius, WHITE);

			// Draw text above circles
			// DrawText("Testing 日本語", 10, (int)deltaTextY, 24, WHITE);
		
		EndDrawing();
	}

	CloseWindow();
}
