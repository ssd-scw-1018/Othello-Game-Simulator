#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include <time.h>
#include <stdio.h>
#include <sdl_image.h>#pragma comment (lib,"sdl_image")
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "page5.h"
#include "page6.h"

#define initxx  270
#define inityy  64
#define WIDTHOFMAL  81
#define HEIGHTOFMAL  72

extern SDL_Event event;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Surface* image;
extern SDL_Surface* textsurface ;
extern TTF_Font* font;
extern SDL_Color textcolor;

typedef struct botton {
    SDL_Rect rect;
    SDL_Texture* texture;
    int show;
}BOTTONS;                
                
extern int x;
extern int y;
extern int gamepan[8][8];

extern int whoturn;
extern int reverse;

extern int k;

extern int i, j;

extern int num0, num1, num2, num3;

extern int maal1, maal2;

extern int quit;

extern int page ;

extern int gamemod; // 1은 기본 오델로 2는 변칙 오델로임을 의미한다

extern int isai;


int createwindows();
int fontinit();
void showimageall();
void showttfall();
void setpage();
void bottondown();
void bottonmove();
void renderimage();
void init_initall();
void reset_xy();
void closeall();
void show_timer();
