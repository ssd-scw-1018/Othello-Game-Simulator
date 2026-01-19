#include "page1.h"

// 오셀로 게임 코드입니다(페이지 1).
// page 1에 사용될 함수들을 정리한 소스파일이다.

BOTTONS startscreen, // 배경화면을 렌더링할 변수이다
        botton1,    // 제목 블럭을 렌더링할 변수이다
        botton2,    // start 블럭을 렌더링할 변수이다
        botton3;    // exit 블럭을 렌더링할 변수이다

SDL_Rect renderQuad11 = { 474, 85, 200, 100 };  // othello 텍스트를 렌더링할 상자이다
SDL_Rect renderQuad12 = { 499, 323, 150, 75 };  // start 텍스트를 렌더링할 상자이다
SDL_Rect renderQuad13 = { 499, 515, 150, 75 };  // exit 텍스트를 렌더링할 상자이다

SDL_Texture* texture11, // othello 텍스트를 사용하기 위한 변수이다
            * texture12, // start 텍스트를 사용하기 위한 변수이다
            * texture13; // exit 텍스트를 사용하기 위한 변수이다

// page 1에 사용될 이미지들을 로드하는 함수이다.
// 성공적으로 이미지 로드 시 0을 반환하고 
// 실패시 어떤 이미지를 로드 실패했는지 알려주고 1을반환한다. 
int ldimg_page1() {
    // 1페이지의 제목 블록을 로드한다.
    image = IMG_Load("titleblock.bmp");
    if (image == NULL) {
        printf("Failed to load image : titlebutton \n");
        return 1;
    }
    botton1.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    // 1페이지의 버튼2와 3을 로드한다
    // 버튼 2는 다음 페이지로 넘어간는 버튼이다
    // 버튼 3은 게임을 종료하는 버튼이다
    image = SDL_LoadBMP("botton.bmp");
    if (image == NULL) {
        printf("Failed to load image : button  \n");
        return 1;
    }
    botton2.texture = SDL_CreateTextureFromSurface(renderer, image);
    botton3.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    // 게임의 배경화면을 로드한다
    image = IMG_Load("back1.png");
    if (image == NULL) {
        printf("startscreen Failed to load image. \n");
        return 1;
    }
    startscreen.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return 0;
}
// 페이지 1에 사용될 텍스트를 로드하는 함수이다 
// 성공시 0, 실패시 1을 반환한다
int ldttf_page1() {
    // 폰트는 Maplestory Light.ttf (출처 : ㈜넥슨코리아)를 사용하였다
    // TTF 파일을 크기 200으로 오픈한다.
    font = TTF_OpenFont("Maplestory Light.ttf", 200);
    if (font == NULL) { // 파일 오픈 실패시 1을 반환하고 종료한다
        printf("fail to open font MAPLE");
        return 1;
    }
    // 제목 블록에 사용될 OTHELLO 텍스트를 만들고 texture11에 렌더한다.
    textsurface = TTF_RenderText_Blended(font, "OTHELLO", textcolor);

    texture11 = SDL_CreateTextureFromSurface(renderer, textsurface);
    // textsurface 를 사용이 끝났으니 비워주고 폰트를 닫아준다.
    SDL_FreeSurface(textsurface);
    TTF_CloseFont(font);
    // Modak-Regular.ttf 파일을 로드한다 (출처 : https://fonts.google.com/specimen/Modak)
    font = TTF_OpenFont("Modak-Regular.ttf", 60);
    if (font == NULL) { // 폰트 파일 로드에 실패하면 에러 메세지 출력 후 1을 반환한다.
        printf("fail to open font MODAK");
        return 1;
    }
    // 버튼 2에 출력할 start텍스트를 만들고 texture12에 렌더한다
    textsurface = TTF_RenderText_Blended(font, "START", textcolor);
    texture12 = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    // textsurface 의 사용이 끝났으니 비워준다. 

    // 버튼 3에 출력할 exit 텍스트를 만들고 texture13에 렌더한다
    textsurface = TTF_RenderText_Blended(font, "EXIT", textcolor);
    texture13 = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    // textsurface 의 사용이 끝났으니 비워준다. 

    // 성공적으로 마무리 되었다면 0을 반환한다.
    return 0;
}

// 페이지 1에 쓰이는 이미지들의 크기와 위치를 초기화하는 함수이다. 
void sizeinitpage1() {

    // 배경화면의 크기는 화면 전체의 크기와 같게 한다.
    startscreen.rect.w = 1188;
    startscreen.rect.h = 640;
    startscreen.rect.x = 0;
    startscreen.rect.y = 0;

    // 제목 블럭의 크기와 위치이다
    botton1.rect.w = 688;
    botton1.rect.h = 217;
    botton1.rect.x = 230;
    botton1.rect.y = 20;

    // 버튼 2 (start)블럭의 크기와 위치이다
    botton2.rect.w = 492;
    botton2.rect.h = 154;
    botton2.rect.x = 328;
    botton2.rect.y = 275;

    // 버튼 3 (exit)블럭의 크기와 위치이다
    botton3.rect.w = 492;
    botton3.rect.h = 154;
    botton3.rect.x = 328;
    botton3.rect.y = 467;
}
// 페이지 1이 종료될 때 (다음 페이지로 넘어가거나 종료) 사용이 끝난 텍스쳐들을 파괴하는 함수이다.
// 페이지 값이 변경되면 사용한다. 
void close_page1() {
    SDL_DestroyTexture(botton1.texture);
    SDL_DestroyTexture(botton2.texture);
    SDL_DestroyTexture(botton3.texture);
    SDL_DestroyTexture(texture11);
    SDL_DestroyTexture(texture12);
    SDL_DestroyTexture(texture13);
}
// 페이지 1에서 마우스 클릭 이벤트를 다루는 함수이다.
void bottondown_page1() {
    // 마우스의 x, y 좌표를 받는다
    SDL_GetMouseState(&x, &y);
    if ((x > botton2.rect.x) && (x < botton2.rect.x + botton2.rect.w) &&
        (y > botton2.rect.y) && (y < botton2.rect.y + botton2.rect.h)) {    // 사용자가 버튼 2(start)를 누르면
        page++; // 페이지 수를 1 증가시킨다
        close_page1();  // 페이지 1 종료 함수를 실행한다
        reset_xy(); // 입력받은 x y 좌표를 -1로 초기화시킨다
        setpage();  // page 값이 바뀌었으니 page2를 세팅한다
    }
    else if ((x > botton3.rect.x) && (x < botton3.rect.x + botton3.rect.w) &&
             (y > botton3.rect.y) && (y < botton3.rect.y + botton3.rect.h)) {   // 사용자가 버튼 3(exit)을 누르면
        quit = 1; // quit 값을 1로 바꾸고
        close_page1();  // 페이지 1 종료 함수를 실행한다.
    }
}
// 페이지 1에서 마우스 움직임 이벤트를 다루는 함수이다.
void bottonmove_page1(SDL_Event e) {

    // 마우스의 좌표를 받아온다
    int motionx = e.motion.x, motiony = e.motion.y;


    // 만약 마우스가 버튼 2 위에 있다면 버튼 2를 어둡게 만든다 
    if ((motionx > botton2.rect.x) && (motionx < botton2.rect.x + botton2.rect.w) &&
        (motiony > botton2.rect.y) && (motiony < botton2.rect.y + botton2.rect.h)) {
            SDL_SetTextureColorMod(botton2.texture, 100, 100, 100);
        }// 만약 마우스가 버튼 3 위에 있다면 버튼 3을 어둡게 만든다
    else if ((motionx > botton3.rect.x) && (motionx < botton3.rect.x + botton3.rect.w) &&
             (motiony > botton3.rect.y) && (motiony < botton3.rect.y + botton3.rect.h)) {
            SDL_SetTextureColorMod(botton3.texture, 100, 100, 100);
        }
    else { // 만약 버튼 2,3 위에서 벗어난다면 버튼을 다시 밝게 한다 
            ldimg_page1();
        }
}
// 페이지 1의 이미지들을 렌더하는 함수이다.
void showimage1() {
    // 배경화면을 렌더한다
    SDL_RenderCopy(renderer, startscreen.texture, NULL, &(startscreen.rect));
    // 제목블럭을 렌더한다
    SDL_RenderCopy(renderer, botton1.texture, NULL, &(botton1.rect));
    // 버튼 2 (start)를 렌더한다
    SDL_RenderCopy(renderer, botton2.texture, NULL, &(botton2.rect));
    // 버튼 3 (exit)를 렌더한다
    SDL_RenderCopy(renderer, botton3.texture, NULL, &(botton3.rect));
}
// 페이지 1의 텍스트를 렌더하는 함수이다
void showttf1() {
    // othello 텍스트를 제목 블록 위에 출력한다
    SDL_RenderCopy(renderer, texture11, NULL, &renderQuad11);
    // start 텍스트를 버튼 2 위에 출력한다
    SDL_RenderCopy(renderer, texture12, NULL, &renderQuad12);
    // exit 텍스트를 버튼 3 위에 출력한다
    SDL_RenderCopy(renderer, texture13, NULL, &renderQuad13);
}
// 페이지 1을 시작하는 함수이다.
// 페이지 1 시작시 필요한 초기 환경을 세팅한다
void init_page1() {
    // 페이지1에 사용될 이미지를 로드한다 이미지 로드에 실패하면 성공할때까지 반복
    while (ldimg_page1() != 0 );
    // 페이지1에 사용될 텍스트를 로드한다 텍스트 로드에 실패하면 성공할때까지 반복
    while (ldttf_page1() != 0 );
    // 페이지 1의 이미지들의 크기, 위치를 초기화한다
    sizeinitpage1();
}
