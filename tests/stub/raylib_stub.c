#include "raylib.h"
static double fake_time = 0.0;
void SetTraceLogLevel(int x){(void)x;}
void InitWindow(int a,int b,const char*c){(void)a;(void)b;(void)c;}
void SetExitKey(int x){(void)x;}
Texture2D LoadTextureFromImage(Image i){Texture2D t={1,i.width,i.height,1,i.format}; return t;}
void CloseWindow(void){}
void SetTextureFilter(Texture2D t,int x){(void)t;(void)x;}
void SetTargetFPS(int x){(void)x;}
void SetWindowSize(int a,int b){(void)a;(void)b;}
void UnloadTexture(Texture2D t){(void)t;}
bool WindowShouldClose(void){return false;}
bool IsWindowFullscreen(void){return false;}
void ToggleFullscreen(void){}
void SetWindowTitle(const char*s){(void)s;}
void UpdateTexture(Texture2D t,const void*p){(void)t;(void)p;}
void BeginDrawing(void){}
void ClearBackground(Color c){(void)c;}
void DrawTexture(Texture2D t,int x,int y,Color c){(void)t;(void)x;(void)y;(void)c;}
void EndDrawing(void){}
bool IsKeyDown(int x){(void)x;return false;}
bool IsKeyPressed(int x){(void)x;return false;}
bool IsKeyReleased(int x){(void)x;return false;}
Vector2 GetMousePosition(void){Vector2 p={0,0};return p;}
Vector2 GetMouseDelta(void){Vector2 p={0,0};return p;}
void SetMousePosition(int x,int y){(void)x;(void)y;}
bool IsMouseButtonDown(int x){(void)x;return false;}
bool IsMouseButtonPressed(int x){(void)x;return false;}
bool IsMouseButtonReleased(int x){(void)x;return false;}
void DisableCursor(void){}
void EnableCursor(void){}
double GetTime(void){return fake_time;}
void WaitTime(double x){fake_time += x;}
