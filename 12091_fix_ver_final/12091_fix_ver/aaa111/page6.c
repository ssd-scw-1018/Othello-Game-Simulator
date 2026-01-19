#include "page6.h"

// 오셀로 게임 코드입니다(페이지 6).
// page 6에 사용될 함수들을 정리한 소스파일이다.

BOTTONS endbotton, restartbotton, player16, player26, back6, scoreboard;

SDL_Texture * texturepage61, * texturepage62, * texturepage63,//1p
* texturepage64,//2p
            * texturepage65,//win
    * texturepage66,//1p point
    * texturepage67;//2p point

SDL_Rect textquadpage61 = { 499, 315, 150, 75 };
SDL_Rect textquadpage62 = { 499, 507, 150, 75 };

SDL_Rect textquadpage63 = { 72, 30, 125, 125 };
SDL_Rect textquadpage64 = { 991, 30, 125, 125 };

SDL_Rect textquadpage65 = { 500, 70, 250, 200 };

SDL_Rect textquadpage66 = { 72, 200, 100, 100 };
SDL_Rect textquadpage67 = { 991, 200,100, 100 };


char buffer[256];


// page 6에 사용될 이미지들을 로드하는 함수이다.
// 성공적으로 이미지 로드 시 0을 반환하고 
// 실패시 어떤 이미지를 로드 실패했는지 알려주고 1을반환한다. 
int ldimg_page6() {
    // 게임의 배경화면을 로드한다
    image = IMG_Load("back1.png");
    if (image == NULL) {
        printf("startscreen Failed to load image. \n");
        return 1;
    }
    back6.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 플레이어 1,2의 보드를 로드한다
    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("playerpan1 Failed to load image. \n");
        return 1;
    }
    player16.texture = SDL_CreateTextureFromSurface(renderer, image);
    player26.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 종료버튼, 재시작 버튼을 로드한다
    image = SDL_LoadBMP("botton.bmp");
    if (image == NULL) {
        printf("endbotton Failed to load image. \n");
        return 1;
    }
    endbotton.texture = SDL_CreateTextureFromSurface(renderer, image);
    restartbotton.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return 0;
}
// 페이지 6에 사용될 텍스트를 로드하는 함수이다 
// 성공시 0, 실패시 1을 반환한다
int ldttf_page6() {
    // 재시작 버튼 위에 출력할 restart 텍스트를 렌더한다
    textsurface = TTF_RenderText_Blended(font, "RESTART", textcolor);

    texturepage61 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);
    // 종료 버튼 위에 출력할 end 텍스트를 렌더한다
    textsurface = TTF_RenderText_Blended(font, "END", textcolor);

    texturepage62 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);
    //  플레이어 보드 위에 출력할 1p, 2p 텍스트를 렌더한다
    textsurface = TTF_RenderText_Blended(font, "1P", textcolor);

    texturepage63 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);

    if (isai == 1) {
        textsurface = TTF_RenderText_Blended(font, "AI", textcolor);

        texturepage64 = SDL_CreateTextureFromSurface(renderer, textsurface);
    }
    else {
        textsurface = TTF_RenderText_Blended(font, "2P", textcolor);

        texturepage64 = SDL_CreateTextureFromSurface(renderer, textsurface);
    }
    SDL_FreeSurface(textsurface);

    // 만약 보드에서 플레이어 1의 말이 더 많다면 
    // 1p win을 중앙 상단에 출력한다
    if (num1 > num2) {
        textsurface = TTF_RenderText_Blended(font, "1P WIN", textcolor);

        texturepage65 = SDL_CreateTextureFromSurface(renderer, textsurface);

        SDL_FreeSurface(textsurface);
    }
    // 만약 보드에서 플레이어 2의 말이 더 많다면 
    // 2p win을 중앙 상단에 출력한다
    // 만약 ai 대전이라면 ai win을 출력한다
    else if (num1 < num2) {
        if (isai == 0) {
            textsurface = TTF_RenderText_Blended(font, "2P WIN", textcolor);

            texturepage65 = SDL_CreateTextureFromSurface(renderer, textsurface);
        }
        else {
            textsurface = TTF_RenderText_Blended(font, "AI WIN", textcolor);

            texturepage65 = SDL_CreateTextureFromSurface(renderer, textsurface);
        }

        SDL_FreeSurface(textsurface);
    }
    // 만약 보드에서 플레이어 1,2의 말이 같다면 
    // draw을 중앙 상단에 출력한다
    else {
        textsurface = TTF_RenderText_Blended(font, "DRAW", textcolor);

        texturepage65 = SDL_CreateTextureFromSurface(renderer, textsurface);

        SDL_FreeSurface(textsurface);
    }
    // 버퍼에 플레이어 1의 점수를 입력하여
    // 문자열로 만든 다음 렌더한다
    sprintf_s(buffer, sizeof(buffer), "%d", (int)num1);

    textsurface = TTF_RenderText_Blended(font, buffer, textcolor);

    texturepage66 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);

    // 버퍼에 플레이어 2의 점수를 입력하여
    // 문자열로 만든 다음 렌더한다

    sprintf_s(buffer, sizeof(buffer), "%d", (int)num2);

    textsurface = TTF_RenderText_Blended(font, buffer, textcolor);

    texturepage67 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);

    return 0;
}
// 페이지 6에 쓰이는 이미지들의 크기와 위치를 초기화하는 함수이다. 
void sizeinitpage6() {
    // 종료버튼의 크기와 위치이다
    endbotton.rect.w = 492;
    endbotton.rect.h = 154;
    endbotton.rect.x = 328;
    endbotton.rect.y = 467;

   // 재시작버튼의 크기와 위치이다
    restartbotton.rect.w = 492;
    restartbotton.rect.h = 154;
    restartbotton.rect.x = 328;
    restartbotton.rect.y = 275;
    // 배경화면의 크기는 화면 전체의 크기와 같게 한다.
    back6.rect.w = 1188;
    back6.rect.h = 640;
    back6.rect.x = 0;
    back6.rect.y = 0;
    //플레이어보드 1,2의 크기와 위치이다
    player16.rect.w = 270;
    player16.rect.h = 640;
    player16.rect.x = 0;
    player16.rect.y = 0;

    player26.rect.w = 270;
    player26.rect.h = 640;
    player26.rect.x = 918;
    player26.rect.y = 0;
}
// 페이지 6이 종료될 때 (다음 페이지로 넘어가거나 종료) 사용이 끝난 텍스쳐들을 파괴하는 함수이다.
// 페이지 값이 변경되면 사용한다. 
void close_page6() {
    SDL_DestroyTexture(endbotton.texture);
    SDL_DestroyTexture(restartbotton.texture);
    SDL_DestroyTexture(player16.texture);
    SDL_DestroyTexture(player26.texture);
    SDL_DestroyTexture(back6.texture);
    SDL_DestroyTexture(scoreboard.texture);
}
// 페이지 6에서 마우스 클릭 이벤트를 다루는 함수이다.
void bottondown_page6() {
    // 마우스의 x, y 좌표를 받는다
    SDL_GetMouseState(&x, &y);
    // 만약 종료 버튼을 누른다면
    if ((x > endbotton.rect.x) && (x < endbotton.rect.x + endbotton.rect.w)
        && (y > endbotton.rect.y) && (y < endbotton.rect.y + endbotton.rect.h)) {
        quit = 1;
        // quit 값을 1로 변경한다
        close_page6();
        // 페이지 6 종료 함수를 실행한다
        reset_xy(); // 입력받은 x y 좌표를 -1로 초기화시킨다
    }
    // 만약 재시작 버튼을 누른다면
    if ((x > restartbotton.rect.x) && (x < restartbotton.rect.x + restartbotton.rect.w)
        && (y > restartbotton.rect.y) && (y < restartbotton.rect.y + restartbotton.rect.h)) {
        page = 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                gamepan[i][j] = 0;
            }
        }
        reset_xy(); // 입력받은 x y 좌표를 -1로 초기화시킨다
        close_page6();// 페이지 6 종료 함수를 실행한다
        maal1 = 0; //플레이어 말을 초기화시킨다
        maal2 = 0;
        setpage();// page 값이 바뀌었으니 새로 세팅한다
    }
}
// 페이지 6에서 마우스 움직임 이벤트를 다루는 함수이다.
void bottonmove_page6(SDL_Event e) {
    // 마우스의 좌표를 받아온다
    int motionx = e.motion.x, motiony = e.motion.y;
    // 만약 마우스가 종료 버튼 위에 있다면 종료 버튼을 어둡게 만든다 
    if ((motionx > endbotton.rect.x) && (motionx < endbotton.rect.x + endbotton.rect.w)
        && (motiony > endbotton.rect.y) && (motiony < endbotton.rect.y + endbotton.rect.h)) {
        SDL_SetTextureColorMod(endbotton.texture, 100, 100, 100);
    }
    // 만약 마우스가 재시작 버튼 위에 있다면 종료 버튼을 어둡게 만든다
    else if ((motionx > restartbotton.rect.x) && (motionx < restartbotton.rect.x + restartbotton.rect.w)
        && (motiony > restartbotton.rect.y) && (motiony < restartbotton.rect.y + restartbotton.rect.h)) {
        SDL_SetTextureColorMod(restartbotton.texture, 100, 100, 100);
    }
    // 만약 종료버튼, 재시작 버튼을 벗어난다면 다시 밝게 한다
    else {
        ldimg_page6();
    }
}
// 페이지 6을 시작하는 함수이다.
// 페이지 6 시작시 필요한 초기 환경을 세팅한다
void init_page6() {
    while (ldimg_page6() != 0 );
    while (ldttf_page6() != 0 );
    sizeinitpage6();
}
// 페이지 6의 텍스트들을 렌더하는 함수이다.
void showttf6() {
    SDL_RenderCopy(renderer, texturepage61, NULL, &textquadpage61);
    SDL_RenderCopy(renderer, texturepage62, NULL, &textquadpage62);
    SDL_RenderCopy(renderer, texturepage63, NULL, &textquadpage63);
    SDL_RenderCopy(renderer, texturepage64, NULL, &textquadpage64);
    SDL_RenderCopy(renderer, texturepage65, NULL, &textquadpage65);
    SDL_RenderCopy(renderer, texturepage66, NULL, &textquadpage66);
    SDL_RenderCopy(renderer, texturepage67, NULL, &textquadpage67);
}
// 페이지 6의 이미지들을 렌더하는 함수이다.
void showimage6() {
    SDL_RenderCopy(renderer, back6.texture, NULL, &(back6.rect));
    SDL_RenderCopy(renderer, player16.texture, NULL, &(player16.rect));
    SDL_RenderCopy(renderer, player26.texture, NULL, &(player26.rect));
    SDL_RenderCopy(renderer, endbotton.texture, NULL, &(endbotton.rect));
    SDL_RenderCopy(renderer, restartbotton.texture, NULL, &(restartbotton.rect));
}