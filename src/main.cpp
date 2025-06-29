#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "fonts/8bitBold.h"

Rectangle windowSize = {0, 0, 800, 500};

void drawTitle(Font myFont, bool& title) {
    if (IsCursorHidden() && !IsCursorOnScreen()) {
        EnableCursor();
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    const char* titleText = "Yaju Senpai\nHome Run Derby";
    const char* startText = "start";
    const char* resetText = "reset";
    const char* exitText = "exit";
    const int spacing = 2;

    Vector2 titleTextSize = MeasureTextEx(myFont, titleText, 50, (float)spacing);
    Vector2 startTextSize = MeasureTextEx(myFont, startText, 24, (float)spacing);
    Vector2 resetTextSize = MeasureTextEx(myFont, resetText, 24, (float)spacing);
    Vector2 exitTextSize = MeasureTextEx(myFont, exitText, 24, (float)spacing);

    float titlePosX = (GetScreenWidth() - titleTextSize.x) / 2.0f;
    float titlePosY = (GetScreenHeight() - titleTextSize.y) / 17.0f;

    float startPosX = (GetScreenWidth() - startTextSize.x) / 2.0f;
    float startPosY = (GetScreenHeight() - startTextSize.y) / 1.5f;

    float resetPosX = (GetScreenWidth() - resetTextSize.x) / 2.0f;
    float resetPosY = startPosY + 50;

    float exitPosX = (GetScreenWidth() - exitTextSize.x) / 2.0f;
    float exitPosY = resetPosY + 50;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (mouseX >= startPosX && mouseX <= startPosX+24*5 && mouseY >= startPosY && mouseY <= startPosY+24) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            DisableCursor();
            title = false;
        }
        DrawRectangleLines(startPosX, startPosY, 24*5, 24, {255, 0, 0, 255});
    } else if (mouseX >= resetPosX && mouseX <= resetPosX+24*5 && mouseY >= resetPosY && mouseY <= resetPosY+24) {
        DrawRectangleLines(resetPosX, resetPosY, 24*5, 24, {255, 0, 0, 255});
    } else if (mouseX >= exitPosX && mouseX <= exitPosX+24*5 && mouseY >= exitPosY && mouseY <= exitPosY+24) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            CloseWindow();
            std::cout << "exit" << std::endl;
        }
        DrawRectangleLines(exitPosX, exitPosY, 24*4, 24, {255, 0, 0, 255});
    }

    DrawTextEx(myFont, titleText, (Vector2){ titlePosX, titlePosY }, 50, (float)spacing, BLACK);
    DrawTextEx(myFont, startText, (Vector2){ startPosX, startPosY }, 24, (float)spacing, BLACK);
    DrawTextEx(myFont, resetText, (Vector2){ resetPosX, resetPosY }, 24, (float)spacing, BLACK);
    DrawTextEx(myFont, exitText, (Vector2){ exitPosX, exitPosY }, 24, (float)spacing, BLACK);
    EndDrawing();
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowSize.width, windowSize.height, "Yaju Senpai Home Run Derby");

    SetExitKey(KEY_NULL);

    Font myFont = LoadFontFromMemory(
        ".ttf", // フォントのフォーマット
        __8bitBold_ttf, // 8bitBold.h で定義されたバイト配列名 (例: eightBitBoldFont)
    __8bitBold_ttf_len, // 8bitBold.h で定義されたサイズ変数名 (例: eightBitBoldFont_SIZE)
    1000, // フォントサイズ
    nullptr,
    0);

    bool title = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        windowSize.width = GetScreenWidth();
        windowSize.height = GetScreenHeight();

        drawTitle(myFont, title);
    }

    UnloadFont(myFont);
    CloseWindow();
    return 0;
}
