#include "page2.h"

// 오셀로 게임 코드입니다(페이지 2).
// page 2에 사용될 함수들을 정리한 소스파일이다.

BOTTONS botton4, // normal 블럭이다.
        botton2, // special 블럭이다
        botton3, // back 블럭이다
        back2;  // 배경화면을 위한 변수이다

SDL_Rect renderQuad21 = { 489, 128, 170, 80 };  //normal 텍스트를 출력하기 위한 상자이다
SDL_Rect renderQuad22 = { 499, 323, 150, 75 };   //special 텍스트를 출력하기 위한 상자이다
SDL_Rect renderQuad23 = { 499, 515, 150, 75 };   //back 텍스트를 출력하기 위한 상자이다

SDL_Texture* texture21, //normal 텍스트를 위한 변수이다.
            * texture22, //special 텍스트를 위한 변수이다.
            * texture23;  //back 텍스트를 위한 변수이다.

// page 2에 사용될 이미지들을 로드하는 함수이다.
// 성공적으로 이미지 로드 시 0을 반환하고 
// 실패시 어떤 이미지를 로드 실패했는지 알려주고 1을반환한다. 
int ldimg_page2() {
    // 2페이지의 버튼 2, 3, 4를 로드한다
    // 버튼 2는 변칙 오델로 게임을 하게하고
    // 버튼 3은 페이지 1로 돌아가게 하고
    // 버튼 4는 일반 오델로 게임을 하게 한다
    image = SDL_LoadBMP("botton.bmp");
    if (image == NULL) {    
        printf("Failed to load image : button \n");
        return 1;
    }
    botton4.texture = SDL_CreateTextureFromSurface(renderer, image);
    botton2.texture = SDL_CreateTextureFromSurface(renderer, image);
    botton3.texture = SDL_CreateTextureFromSurface(renderer, image);
    
    // texture 생성이 끝났으니 image를 비워준다
    SDL_FreeSurface(image);

    // 게임의 배경화면을 로드한다
    image = IMG_Load("back1.png");
    if (image == NULL) {
        printf("Failed to load image : startscreen \n");
        return 1;
    }
    back2.texture = SDL_CreateTextureFromSurface(renderer, image);
    // texture 생성이 끝났으니 image를 비워준다
    SDL_FreeSurface(image);

    return 0;
}
// 페이지 2에 사용될 텍스트를 로드하는 함수이다 
// 성공시 0, 실패시 1을 반환한다
int ldttf_page2() {
    // 버튼 4에 사용될 normal 텍스트를 만든다
    textsurface = TTF_RenderText_Blended(font, "NORMAL", textcolor);
    texture21 = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    // 버튼 2에 사용될 normal 텍스트를 만든다
    textsurface = TTF_RenderText_Blended(font, "SPECIAL", textcolor);
    texture22 = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    // 버튼 3에 사용될 normal 텍스트를 만든다
    textsurface = TTF_RenderText_Blended(font, "BACK", textcolor);
    texture23 = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);

    return 0;
}
// 페이지 2에 쓰이는 이미지들의 크기와 위치를 초기화하는 함수이다. 
void sizeinitpage2() {
    // 배경화면의 크기는 화면 전체의 크기와 같게 한다.
    back2.rect.w = 1188;
    back2.rect.h = 640;
    back2.rect.x = 0;
    back2.rect.y = 0;
     // 버튼 4 (exit)블럭의 크기와 위치이다
    botton4.rect.w = 492;
    botton4.rect.h = 154;
    botton4.rect.x = 328;
    botton4.rect.y = 83;
    // 버튼 2와 3은 페이지 1의 설정을 그대로 이어쓴다
}
// 페이지 2가 종료될 때 (다음 페이지로 넘어가거나 종료) 사용이 끝난 텍스쳐들을 파괴하는 함수이다.
// 페이지 값이 변경되면 사용한다. 
void close_page2() {
    SDL_DestroyTexture(botton2.texture);
    SDL_DestroyTexture(botton3.texture);
    SDL_DestroyTexture(botton4.texture);
    SDL_DestroyTexture(texture21);
    SDL_DestroyTexture(texture22);
    SDL_DestroyTexture(texture23);
}

// 페이지 2에서 마우스 클릭 이벤트를 다루는 함수이다.
void bottondown_page2() {
    // 마우스의 x, y 좌표를 받는다
    SDL_GetMouseState(&x, &y);

    if ((x > botton2.rect.x) && (x < botton2.rect.x + botton2.rect.w)
        && (y > botton2.rect.y) && (y < botton2.rect.y + botton2.rect.h)) { // 사용자가 버튼 2(special)를 누르면
        page++; // 페이지 수를 1 증가시킨다
        gamemod = 2; // gamemode를 2 (일반 오델로 게임)으로 설정한다
        reset_xy(); // 입력받은 x y 좌표를 -1로 초기화시킨다
        close_page2(); // 페이지 2 종료 함수를 실행한다
        setpage();// page 값이 바뀌었으니 page3를 세팅한다
    }
    else if ((x > botton3.rect.x) && (x < botton3.rect.x + botton3.rect.w)
        && (y > botton3.rect.y) && (y < botton3.rect.y + botton3.rect.h)) {// 사용자가 버튼 3(back)을 누르면
        page--; // 페이지 수를 1 감소시킨다
        reset_xy();// 입력받은 x y 좌표를 -1로 초기화시킨다
        close_page2();// 페이지 2 종료 함수를 실행한다
        setpage();// page 값이 바뀌었으니 page1를 세팅한다
    }
    else if ((x > botton4.rect.x) && (x < botton4.rect.x + botton4.rect.w)
        && (y > botton4.rect.y) && (y < botton4.rect.y + botton4.rect.h)) {// 사용자가 버튼 3(normal)을 누르면
        page++;// 페이지 수를 1 증가시킨다
        gamemod = 1;// gamemode를 1 (변칙 오델로 게임)으로 설정한다
        reset_xy();// 입력받은 x y 좌표를 -1로 초기화시킨다
        close_page2();// 페이지 2 종료 함수를 실행한다
        setpage();// page 값이 바뀌었으니 page3를 세팅한다
    }
}
// 페이지 2에서 마우스 움직임 이벤트를 다루는 함수이다.
void bottonmove_page2(SDL_Event e) {
    // 마우스의 좌표를 받아온다
    int motionx = e.motion.x, motiony = e.motion.y;

    // 만약 마우스가 버튼 2 위에 있다면 버튼 2를 어둡게 만든다 
    if ((motionx > botton2.rect.x) && (motionx < botton2.rect.x + botton2.rect.w)
        && (motiony > botton2.rect.y) && (motiony < botton2.rect.y + botton2.rect.h)) {
        SDL_SetTextureColorMod(botton2.texture, 100, 100, 100);
    }// 만약 마우스가 버튼 3 위에 있다면 버튼 3을 어둡게 만든다
    else if ((motionx > botton3.rect.x) && (motionx < botton3.rect.x + botton3.rect.w)
        && (motiony > botton3.rect.y) && (motiony < botton3.rect.y + botton3.rect.h)) {
        SDL_SetTextureColorMod(botton3.texture, 100, 100, 100);
    }
    // 만약 마우스가 버튼 4 위에 있다면 버튼 4를 어둡게 만든다
    else if ((motionx > botton4.rect.x) && (motionx < botton4.rect.x + botton4.rect.w)
        && (motiony > botton4.rect.y) && (motiony < botton4.rect.y + botton4.rect.h)) {
        SDL_SetTextureColorMod(botton4.texture, 100, 100, 100);
    }
    else {// 만약 버튼 2,3,4 위에서 벗어난다면 버튼을 다시 밝게 한다 
        ldimg_page2();
    }
}
// 페이지 2의 텍스트를 렌더하는 함수이다
void showttf2() {
    SDL_RenderCopy(renderer, texture21, NULL, &renderQuad21);

    SDL_RenderCopy(renderer, texture22, NULL, &renderQuad22);

    SDL_RenderCopy(renderer, texture23, NULL, &renderQuad23);
}
// 페이지 2을 시작하는 함수이다.
// 페이지 2 시작시 필요한 초기 환경을 세팅한다
void init_page2() {
    // 페이지2에 사용될 이미지를 로드한다 이미지 로드에 실패하면 성공할때까지 반복
    while (ldimg_page2() != 0 );
    // 페이지2에 사용될 텍스트를 로드한다 텍스트 로드에 실패하면 성공할때까지 반복
    while (ldttf_page2() != 0 );
    // 페이지 2의 이미지들의 크기, 위치를 초기화한다
    sizeinitpage2();
}
// 페이지 2의 이미지들을 렌더하는 함수이다.
void showimage2() {
    // 배경화면을 렌더한다
    SDL_RenderCopy(renderer, back2.texture, NULL, &(back2.rect));
    // 버튼 4를 렌더한다
    SDL_RenderCopy(renderer, botton4.texture, NULL, &(botton4.rect));
    // 버튼 2를 렌더한다
    SDL_RenderCopy(renderer, botton2.texture, NULL, &(botton2.rect));
    // 버튼 3을 렌더한다
    SDL_RenderCopy(renderer, botton3.texture, NULL, &(botton3.rect));
}