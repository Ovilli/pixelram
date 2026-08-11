#ifndef RAYLIB_H
#define RAYLIB_H
#include <stdbool.h>
#include <stdint.h>
typedef struct Color { unsigned char r,g,b,a; } Color;
typedef struct Texture2D { unsigned int id; int width,height,mipmaps,format; } Texture2D;
typedef struct Image { void *data; int width,height,mipmaps,format; } Image;
typedef struct Vector2 { float x,y; } Vector2;
enum {
  KEY_A=1,
  KEY_APOSTROPHE=2,
  KEY_B=3,
  KEY_BACKSPACE=4,
  KEY_C=5,
  KEY_COMMA=6,
  KEY_D=7,
  KEY_DELETE=8,
  KEY_DOWN=9,
  KEY_E=10,
  KEY_EIGHT=11,
  KEY_END=12,
  KEY_ENTER=13,
  KEY_EQUAL=14,
  KEY_ESCAPE=15,
  KEY_F=16,
  KEY_F1=17,
  KEY_F10=18,
  KEY_F11=19,
  KEY_F12=20,
  KEY_F2=21,
  KEY_F3=22,
  KEY_F4=23,
  KEY_F5=24,
  KEY_F6=25,
  KEY_F7=26,
  KEY_F8=27,
  KEY_F9=28,
  KEY_FIVE=29,
  KEY_FOUR=30,
  KEY_G=31,
  KEY_GRAVE=32,
  KEY_H=33,
  KEY_HOME=34,
  KEY_I=35,
  KEY_INSERT=36,
  KEY_J=37,
  KEY_K=38,
  KEY_L=39,
  KEY_LEFT=40,
  KEY_LEFT_ALT=41,
  KEY_LEFT_BRACKET=42,
  KEY_LEFT_CONTROL=43,
  KEY_LEFT_SHIFT=44,
  KEY_M=45,
  KEY_MINUS=46,
  KEY_N=47,
  KEY_NINE=48,
  KEY_NULL=49,
  KEY_O=50,
  KEY_ONE=51,
  KEY_P=52,
  KEY_PAGE_DOWN=53,
  KEY_PAGE_UP=54,
  KEY_PERIOD=55,
  KEY_Q=56,
  KEY_R=57,
  KEY_RIGHT=58,
  KEY_RIGHT_ALT=59,
  KEY_RIGHT_BRACKET=60,
  KEY_RIGHT_CONTROL=61,
  KEY_RIGHT_SHIFT=62,
  KEY_S=63,
  KEY_SEMICOLON=64,
  KEY_SEVEN=65,
  KEY_SIX=66,
  KEY_SLASH=67,
  KEY_SPACE=68,
  KEY_T=69,
  KEY_TAB=70,
  KEY_THREE=71,
  KEY_TWO=72,
  KEY_U=73,
  KEY_UP=74,
  KEY_V=75,
  KEY_W=76,
  KEY_X=77,
  KEY_Y=78,
  KEY_Z=79,
  KEY_ZERO=80,
  MOUSE_BUTTON_LEFT=81,
  MOUSE_BUTTON_MIDDLE=82,
  MOUSE_BUTTON_RIGHT=83,
  LOG_WARNING=84,
  PIXELFORMAT_UNCOMPRESSED_R8G8B8A8=85,
  TEXTURE_FILTER_POINT=86
};

void SetTraceLogLevel(int);
void InitWindow(int,int,const char*);
void SetExitKey(int);
Texture2D LoadTextureFromImage(Image);
void CloseWindow(void);
void SetTextureFilter(Texture2D,int);
void SetTargetFPS(int);
void SetWindowSize(int,int);
void UnloadTexture(Texture2D);
bool WindowShouldClose(void);
bool IsWindowFullscreen(void);
void ToggleFullscreen(void);
void SetWindowTitle(const char*);
void UpdateTexture(Texture2D,const void*);
void BeginDrawing(void);
void ClearBackground(Color);
void DrawTexture(Texture2D,int,int,Color);
void EndDrawing(void);
bool IsKeyDown(int);
bool IsKeyPressed(int);
bool IsKeyReleased(int);
Vector2 GetMousePosition(void);
Vector2 GetMouseDelta(void);
void SetMousePosition(int,int);
bool IsMouseButtonDown(int);
bool IsMouseButtonPressed(int);
bool IsMouseButtonReleased(int);
void DisableCursor(void);
void EnableCursor(void);
double GetTime(void);
void WaitTime(double);
static const Color BLACK={0,0,0,255};
static const Color WHITE={255,255,255,255};
#endif
