#include "page4.h"
#include <time.h>
#include <stdlib.h>

// 오셀로 게임 코드입니다(페이지 4).
// page 4에 사용될 함수들을 정리한 소스파일이다.

BOTTONS blue[8][8], purple[8][8], white[8][8], yellow[8][8], // 플레이어 말블럭들이다
    canpla[8][8], pan[8][8], // canpla는 말을 둘 수 있는곳, pan은 말이 없는 빈 공간이다
    timergage, timergage2, // timegage 왼쪽과 오른쪽이다
    timeclock, // timegage 사이에서 시간을 출력해주는 블럭이다. 시간은 30초에서 카운트다운 된다
    player14, player24, // 플레이어 1,2의 보드
    turn4;// 누구 턴인지 알려주는 블럭이다

SDL_Texture* texturepage41, // timeclock 블럭 위에서 시간을 출력하기 위한 텍스챠이다
            * texturepage42, // 플레이어 1의 점수를 출력하기 위한 텍스쳐이다
            * texturepage43, // 플레이어 2의 점수를 출력하기 위한 텍스쳐이다
            * texturepage44, // 1p를 출력하기 위한 텍스쳐
            * texturepage45; // 2p 혹은 ai를 출력하기 위한 텍스쳐이다

SDL_Color textcolorpage4 = { 255, 255, 255 }; // 4page에서 글자색은 검은색만을 사용한다

SDL_Rect textquadpage41 = { 564, 0, 60, 60 }; // 시간 출력을 위한 텍스트 상자이다
SDL_Rect textquadpage42 = { 72, 200, 100, 100 };// 플레이어 1의 점수를 출력하기 위한 텍스트 상자이다
SDL_Rect textquadpage43 = { 991, 200,100, 100 };// 플레이어 2의 점수를 출력하기 위한 텍스트 상자이다
SDL_Rect textquadpage44 = { 72, 30, 125, 125 };// 1p를 출력하기 위한 텍스트 상자이다
SDL_Rect textquadpage45 = { 991, 30, 125, 125 };// 2p 혹은 ai를 출력하기 위한 텍스트 상자이다

char timetime[256];// 숫자를 문자열로 바꿔주기 위한 버퍼이다

time_t setime = 0;  // 턴이 바뀌었을 때의 시간(초 단위)이다. 그 이후로 값이 바뀌는 순간은 턴이 바뀌었을 때이다
time_t nowtime = 0; // 턴이 바뀌고 지속해서 갱신된다
// nowtime - setime값은 턴이 남은 시간을 알려준다

// page 4에 사용될 이미지들을 로드하는 함수이다.
// 성공적으로 이미지 로드 시 0을 반환하고 
// 실패시 어떤 이미지를 로드 실패했는지 알려주고 1을반환한다. 
int ldimg_page4() {
    // 화면 상단에 사용될 붉은색 타이머 게이지를 로드한다
    image = IMG_Load("timer.jpg");
    if (image == NULL) {
        printf("Failed to load image : timergage1  \n");
        return 0;
    }
    timergage.texture = SDL_CreateTextureFromSurface(renderer, image);
    timergage2.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 시간출력 타이머 이미지를 로드한다
    image = IMG_Load("pana.bmp");
    if (image == NULL) {
        printf("timeclock Failed to load image. \n");
        return 0;
    }
    timeclock.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 플레이어 1,2의 보드를 로드한다
    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("playerpan1 Failed to load image. \n");
        return 0;
    }
    player14.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("playerpan2 Failed to load image. \n");
        return 0;
    }
    player24.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    // 턴 표시 블럭을 로드한다
    image = IMG_Load("turn.jpg");
    if (image == NULL) {
        printf("turn Failed to load image. \n");
        return 0;
    }
    turn4.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 플레이어 1 혹은 2가 말 1을 골랐다면
    // 말 1을 로드한다
	if ((maal1 == 1) || (maal2 == 1)) {
        image = IMG_Load("white.bmp");
        if (image == NULL) {
            printf("white Failed to load image. \n");
            return 0;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                white[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
        SDL_FreeSurface(image);
	}
    // 플레이어 1 혹은 2가 말 2을 골랐다면
    // 말 2을 로드한다
    if ((maal1 == 2) || (maal2 == 2)) {
        image = IMG_Load("yellow.bmp");
        if (image == NULL) {
            printf("yellow Failed to load image. \n");
            return 1;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                yellow[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
        SDL_FreeSurface(image);
    }
    // 플레이어 1 혹은 2가 말 3을 골랐다면
    // 말 3을 로드한다
    if ((maal1 == 3) || (maal2 == 3)) {
        image = IMG_Load("purple.jpg");
        if (image == NULL) {
            printf("purple Failed to load image. \n");
            return 1;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                purple[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
        SDL_FreeSurface(image);
    }
    // 플레이어 1 혹은 2가 말 4을 골랐다면
    // 말 4을 로드한다
    if ((maal1 == 4) || (maal2 == 4)) {
        image = SDL_LoadBMP("blue.jpg");
        if (image == NULL) {
            printf("blue Failed to load image. \n");
            return 1;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                blue[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
        SDL_FreeSurface(image);
    }
    // 체크 이미지를 로드한다
    // 말을 둘 수 있는 곳을 표시할 때 사용된다
    image = IMG_Load("check.png");
    if (image == NULL) {
        printf("canpla Failed to load image. \n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            canpla[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
        }
    }
    SDL_FreeSurface(image);
    // 짝수 칸은 연한 갈색을 로드한다
    image = IMG_Load("1732038255327.bmp");
    if (image == NULL) {
        printf("panb Failed to load image. \n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j + i) % 2 == 0) {
                pan[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
    }
    SDL_FreeSurface(image);
    // 홀수 칸은 진한 갈색을 로드한다
    image = IMG_Load("pana.bmp");
    if (image == NULL) {
        printf("pana Failed to load image. \n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((j + i) % 2 == 1) {
                pan[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
    }
    SDL_FreeSurface(image);

    return 0;
}
// 페이지 4에 사용될 텍스트를 로드하는 함수이다 
// 성공시 0, 실패시 1을 반환한다
int ldttf_page4() {
    // 1p 텍스트를 로드한다
    textsurface = TTF_RenderText_Blended(font, "1P", textcolorpage4);

    texturepage44 = SDL_CreateTextureFromSurface(renderer, textsurface);

    // 2p 텍스트를 로드한다
    // 만약 ai 대전이면 ai 를 로드한다

    if (isai == 0) {
        textsurface = TTF_RenderText_Blended(font, "2P", textcolorpage4);
    }
    else textsurface = TTF_RenderText_Blended(font, "AI", textcolorpage4);

    texturepage45 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);

    // 버퍼에 타이머를 입력해 문자열로 바꾼다

    sprintf_s(timetime, sizeof(timetime), "%d", (int)(30 - (nowtime - setime)));

    // 바꾼 문자열을 로드한다
    
    textsurface = TTF_RenderText_Blended(font, timetime, textcolor);

    texturepage41 = SDL_CreateTextureFromSurface(renderer, textsurface);

    // 버퍼에 플레이어1의 점수를 입력해 문자열로 바꾼다

    sprintf_s(timetime, sizeof(timetime), "%d", (int)num1);

    // 바꾼 문자열을 로드한다

    textsurface = TTF_RenderText_Blended(font, timetime, textcolor);

    texturepage42 = SDL_CreateTextureFromSurface(renderer, textsurface);

    // 버퍼에 플레이어2의 점수를 입력해 문자열로 바꾼다

    sprintf_s(timetime, sizeof(timetime), "%d", (int)num2);

    // 바꾼 문자열을 로드한다

    textsurface = TTF_RenderText_Blended(font, timetime, textcolor);

    texturepage43 = SDL_CreateTextureFromSurface(renderer, textsurface);
    return 0;
}
// 페이지 4에 쓰이는 이미지들의 크기와 위치를 초기화하는 함수이다. 
void sizeinitpage4() {
    //말 4종류의 위치와 canpla, pan를 초기화한다.
    int initx = initxx;
    int inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            purple[i][j].rect.w = WIDTHOFMAL;
            purple[i][j].rect.h = HEIGHTOFMAL;
            purple[i][j].rect.x = initx;
            purple[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            blue[i][j].rect.w = WIDTHOFMAL;
            blue[i][j].rect.h = HEIGHTOFMAL;
            blue[i][j].rect.x = initx;
            blue[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            canpla[i][j].rect.w = WIDTHOFMAL;
            canpla[i][j].rect.h = HEIGHTOFMAL;
            canpla[i][j].rect.x = initx;
            canpla[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            pan[i][j].rect.w = WIDTHOFMAL;
            pan[i][j].rect.h = HEIGHTOFMAL;
            pan[i][j].rect.x = initx;
            pan[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            white[i][j].rect.w = WIDTHOFMAL;
            white[i][j].rect.h = HEIGHTOFMAL;
            white[i][j].rect.x = initx;
            white[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            yellow[i][j].rect.w = WIDTHOFMAL;
            yellow[i][j].rect.h = HEIGHTOFMAL;
            yellow[i][j].rect.x = initx;
            yellow[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }
    // 타이머 블럭의 위치와 크기이다
    timeclock.rect.w = 108;
    timeclock.rect.h = 64;
    timeclock.rect.x = 540;
    timeclock.rect.y = 0;
    // 타이머 게이지의 위치와 크기이다
    timergage.rect.w = 270;
    timergage.rect.h = 64;
    timergage.rect.x = 270;
    timergage.rect.y = 0;

    timergage2.rect.w = 270;
    timergage2.rect.h = 64;
    timergage2.rect.x = 644;
    timergage2.rect.y = 0;
    // 플레이어 보드의 위치와 크기이다
    player14.rect.w = 270;
    player14.rect.h = 640;
    player14.rect.x = 0;
    player14.rect.y = 0;

    player24.rect.w = 270;
    player24.rect.h = 640;
    player24.rect.x = 918;
    player24.rect.y = 0;
    // 턴 지시의 위치와 크기이다
    // 1p의 턴에 1p에 위치하게 한다
    // 2p의 턴에는 2p에 위치하게 한다
    if (k % 2 == 1) {
        turn4.rect.w = 250;
        turn4.rect.h = 125;
        turn4.rect.x = 10;
        turn4.rect.y = 505;
    }
    else {
        turn4.rect.w = 250;
        turn4.rect.h = 125;
        turn4.rect.x = 928;
        turn4.rect.y = 505;
    }
}
// 페이지 4이 종료될 때 (다음 페이지로 넘어가거나 종료) 사용이 끝난 텍스쳐들을 파괴하는 함수이다.
// 페이지 값이 변경되면 사용한다. 
void close_page4() {
    SDL_DestroyTexture(timergage.texture);
    SDL_DestroyTexture(timergage2.texture);
    SDL_DestroyTexture(timeclock.texture);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            SDL_DestroyTexture(blue[i][j].texture);
            SDL_DestroyTexture(purple[i][j].texture);
            SDL_DestroyTexture(white[i][j].texture);
            SDL_DestroyTexture(yellow[i][j].texture);
            SDL_DestroyTexture(canpla[i][j].texture);
            SDL_DestroyTexture(pan[i][j].texture);
        }
    }
    SDL_DestroyTexture(texturepage41);
    SDL_DestroyTexture(texturepage42);
    SDL_DestroyTexture(texturepage43);
}
// 페이지 4에서 마우스 클릭 이벤트를 다루는 함수이다.
void bottondown_page4() {
        // 마우스의 x, y 좌표를 받는다
        SDL_GetMouseState(&x, &y);

        // 플레이어가 화면에 보이는 말을 클릭했다면
        // 그 값에 해당하는 배열 값으로 변환해준다.
        x = (x - 270) / 81;
        y = (y - 64) / 72;

        // 변환한 값으로 말을 뒤집는 함수를 실행
        malswitch(y, x);
        
        // 턴이 넘어갔으므로 턴 지시의 위치를 바꿔준다
        if (k % 2 == 1) {
            turn4.rect.w = 250;
            turn4.rect.h = 125;
            turn4.rect.x = 10;
            turn4.rect.y = 505;
        }
        else {
            turn4.rect.w = 250;
            turn4.rect.h = 125;
            turn4.rect.x = 928;
            turn4.rect.y = 505;
        }

        // gamepan에 남아있는 3들을 없애준다
        threetozero();
        // 둘 수 있는 곳을 다시 계산한다
        canplace();
        // 플레이어의 점수를 확인하고 턴 넘김 여부를 확인한다
        alnum();
        // 턴 넘김이 두번 이상 반복되고 반환값이 1이라면 게임을 종료하고 결과화면으로 넘어간다
        if (alnum() == 1) {
            printf("end1"); 
            page += 2;
            reset_xy();
            setpage();
            close_page4();
        }
        else if (alnum() == 2) {// 턴 넘김이 두번 이상 반복되고 반환값이 2이라면 게임을 종료하고 결과화면으로 넘어간다
            k++;
            threetozero();
            canplace();
            if (alnum() == 2) {
                printf("end2"); 
                page += 2;
                reset_xy();
                setpage();
                close_page4();
            }
        }
        if ((isai == 1)&&(k%2 == 0)) {

            aipanswitch();
            if (k % 2 == 1) {
                turn4.rect.w = 250;
                turn4.rect.h = 125;
                turn4.rect.x = 10;
                turn4.rect.y = 505;
            }
            else {
                turn4.rect.w = 250;
                turn4.rect.h = 125;
                turn4.rect.x = 928;
                turn4.rect.y = 505;
            }
        }
}
// 최초의 판을 초기화 하는 함수이다
void setpan_page4() {
    for(i = 0 ; i < 8 ; i ++){
        for (j = 0 ; j < 8 ; j++){
            gamepan[i][j] = 0;
        }
    }
    // 게임 룰을 따라 두칸씩 가지고 시작한다
    gamepan[3][4] = gamepan[4][3] = 1;
    gamepan[3][3] = gamepan[4][4] = 2;
}
// 둘 수 있는 곳을 찾는 함수이다.
// 둘 수 있는 곳의 gamepan 값을 3으로 바꾼다
void canplace() {
    // k가 홀수이면 1p의 턴
    if (k % 2 == 1) {
        whoturn = 1;
        reverse = 2;
    }
    // k가 짝수이면 2p의 턴이다
    else {
        whoturn = 2;
        reverse = 1;
    }

    int i, j, k;
    //������ ����
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i][j + 1] == reverse)) {
                for (k = j + 2; k < 8; k++) {
                    if ((gamepan[i][k] == 4) || (gamepan[i][k] == whoturn) || (gamepan[i][k] == 3)) {
                        break;
                    }
                    if (gamepan[i][k] == 0) {
                        gamepan[i][k] = 3;
                        break;
                    }
                }
            }
        }
    }
    //���ʹ���
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i][j - 1] == reverse)) {
                for (k = j - 2; k > 0; k--) {
                    if ((gamepan[i][k] == 4) || (gamepan[i][k] == whoturn) || (gamepan[i][k] == 3)) {
                        break;
                    }
                    if (gamepan[i][k] == 0) {
                        gamepan[i][k] = 3;
                        break;
                    }
                }
            }
        }
    }
    // �� ����
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i - 1][j] == reverse)) {
                for (k = i - 2; k > 0; k--) {
                    if ((gamepan[k][j] == 4) || (gamepan[k][j] == whoturn) || (gamepan[k][j] == 3)) {
                        break;
                    }
                    else if (gamepan[k][j] == 0) {
                        gamepan[k][j] = 3;
                        break;
                    }
                }
            }
        }
    }
    // �Ʒ� ����
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i + 1][j] == reverse)) {
                for (k = i + 2; k < 8; k++) {
                    if ((gamepan[k][j] == 4) || (gamepan[k][j] == whoturn) || (gamepan[k][j] == 3)) {
                        break;
                    }
                    else if (gamepan[k][j] == 0) {
                        gamepan[k][j] = 3;
                        break;
                    }
                }
            }
        }
    }
    // ���� �� �밢��
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i - 1][j - 1] == reverse)) {
                for (k = 2; k < 8; k++) {
                    if (((i - k) < 0) || ((j - k) < 0)) {
                        break;
                    }
                    if ((gamepan[i - k][j - k] == 4) || (gamepan[i - k][j - k] == whoturn) || (gamepan[i - k][j - k] == 3)) {
                        break;
                    }
                    else if (gamepan[i - k][j - k] == 0) {
                        gamepan[i - k][j - k] = 3;
                        break;
                    }
                }
            }
        }
    }
    // ������ �� �밢��
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i - 1][j + 1] == reverse)) {
                for (k = 2; k < 8; k++) {
                    if (((i - k) < 0) || ((j + k) >= 8)) {
                        break;
                    }
                    if ((gamepan[i - k][j + k] == 4) || (gamepan[i - k][j + k] == whoturn) || (gamepan[i - k][j + k] == 3)) {
                        break;
                    }
                    else if (gamepan[i - k][j + k] == 0) {
                        gamepan[i - k][j + k] = 3;
                        break;
                    }
                }
            }
        }
    }
    // ���� �Ʒ� �밢��
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i + 1][j - 1] == reverse)) {
                for (k = 2; k < 8; k++) {
                    if (((i + k) >= 8) || ((j - k) < 0)) {
                        break;
                    }
                    if ((gamepan[i + k][j - k] == 4) || (gamepan[i + k][j - k] == whoturn) || (gamepan[i + k][j - k] == 3)) {
                        break;
                    }
                    else if (gamepan[i + k][j - k] == 0) {
                        gamepan[i + k][j - k] = 3;
                        break;
                    }
                }
            }
        }
    }
    // ������ �Ʒ� �밢��
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((gamepan[i][j] == whoturn) && (gamepan[i + 1][j + 1] == reverse)) {
                for (k = 2; k < 8; k++) {
                    if (((i + k) >= 8) || ((j + k) >= 8)) {
                        break;
                    }
                    if ((gamepan[i + k][j + k] == 4) || (gamepan[i + k][j + k] == whoturn) || (gamepan[i + k][j + k] == 3)) {
                        break;
                    }
                    else if (gamepan[i + k][j + k] == 0) {
                        gamepan[i + k][j + k] = 3;
                        break;
                    }
                }
            }
        }
    }

}
int malswitch(int x, int y) {
   
    int n = 8;

        if ((x < 0) || (y < 0)) {
            return 0;
        }

        if (k % 2 == 1) {
            whoturn = 1;
            reverse = 2;
        }
        else {
            whoturn = 2;
            reverse = 1;
        }

        if ((gamepan[x][y] == 0) || (gamepan[x][y] == 1) || (gamepan[x][y] == 2) || (gamepan[x][y] == 4)) {
            printf("try again \n");
            return 0;
        }

        gamepan[x][y] = whoturn;

        // �� ����
        if (gamepan[x - 1][y] == reverse) {
            for (i = x - 2; i >= 0; i--) {
                if (gamepan[i][y] == whoturn) {
                    for (j = x - 1; j > i; j--) {
                        gamepan[j][y] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[i][y] == 0) || (gamepan[i][y] == 4) || (gamepan[i][y] == 3)) {
                    break;
                }
            }
        }

        // �Ʒ� ����
        if (gamepan[x + 1][y] == reverse) {
            for (i = x + 2; i < n; i++) {
                if (gamepan[i][y] == whoturn) {
                    for (j = x + 1; j < i; j++) {
                        gamepan[j][y] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[i][y] == 0) || (gamepan[i][y] == 4) || (gamepan[i][y] == 3)) {
                    break;
                }
            }
        }

        // ���� ����
        if (gamepan[x][y - 1] == reverse) {
            for (i = y - 2; i >= 0; i--) {
                if (gamepan[x][i] == whoturn) {
                    for (j = y - 1; j > i; j--) {
                        gamepan[x][j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x][i] == 0) || (gamepan[x][i] == 4) || (gamepan[x][i] == 3)) {
                    break;
                }
            }
        }
        //������ ����

        if (gamepan[x][y + 1] == reverse) {
            for (i = y + 2; i < n; i++) {
                if (gamepan[x][i] == whoturn) {
                    for (j = y + 1; j < i; j++) {
                        gamepan[x][j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x][i] == 0) || (gamepan[x][i] == 4) || (gamepan[x][i] == 3)) {
                    break;
                }
            }
        }

        // ���� �� �밢�� 
        if (gamepan[x - 1][y - 1] == reverse) {
            for (i = 2; i < n; i++) {
                if ((x - i < 0) || (y - i < 0)) {
                    break;
                }
                else if (gamepan[x - i][y - i] == whoturn) {
                    for (j = 1; j < i; j++) {
                        gamepan[x - j][y - j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x - i][y - i] == 0) || (gamepan[x - i][y - i] == 4) || (gamepan[x - i][y - i] == 3)) {
                    break;
                }
            }
        }

        // ������ �Ʒ� �밢��

        if (gamepan[x + 1][y + 1] == reverse) {
            for (i = 2; i < n; i++) {

                if ((x + i >= 8) || (y + i >= 8)) {
                    break;
                }

                else if (gamepan[x + i][y + i] == whoturn) {
                    for (j = 1; j < i; j++) {
                        gamepan[x + j][y + j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x + i][y + i] == 0) || (gamepan[x + i][y + i] == 4) || (gamepan[x + i][y + i] == 3)) {
                    break;
                }
            }
        }

        //���� �Ʒ� �밢��

        if (gamepan[x + 1][y - 1] == reverse) {
            for (i = 2; i < n; i++) {

                if ((x + i >= 8) || (y - i < 0)) {
                    break;
                }

                if (gamepan[x + i][y - i] == whoturn) {
                    for (j = 1; j < i; j++) {
                        gamepan[x + j][y - j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x + i][y - i] == 0) || (gamepan[x + i][y - i] == 4) || (gamepan[x + i][y - i] == 3)) {
                    break;
                }
            }
        }

        //������ �� �밢��

        if (gamepan[x - 1][y + 1] == reverse) {
            for (i = 2; i < n; i++) {

                if ((x - i < 0) || (y + i >= 8)) {
                    break;
                }

                else if (gamepan[x - i][y + i] == whoturn) {
                    for (j = 1; j < i; j++) {
                        gamepan[x - j][y + j] = whoturn;
                    }
                    break;
                }
                else if ((gamepan[x - i][y + i] == 0) || (gamepan[x - i][y + i] == 4) || (gamepan[x - i][y + i] == 3)) {
                    break;
                }
            }
        }
        k++;
        resettimer();
        return 1;
}

void threetozero() {
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (gamepan[i][j] == 3) {
                gamepan[i][j] = 0;
            }
        }
    }
}

int alnum() {
    num0 = num1 = num2 = num3 = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (gamepan[i][j] == 0) {
                num0++;
            }
            else if (gamepan[i][j] == 1) {
                num1++;
            }
            else if (gamepan[i][j] == 2) {
                num2++;
            }
            else if (gamepan[i][j] == 3) {
                num3++;
            }
        }
    }

    if ((num0 == 0) && (num3 == 0)) {
        printf("alnum");
        return 1;
    }
    else if (num3 == 0) {
        printf("alnum");
        return 2;
    }

    return 0;
}

void aipanswitch() {

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (gamepan[i][j] == 3) {
                break;
            }
        }
        if (gamepan[i][j] == 3) {
            break;
        }
    }
    x = i, y = j;

    malswitch(x, y);

    threetozero();

    canplace();

    alnum();

    if (alnum() == 1) {
        printf("end1"); //Ȯ�ο� ���� ����
        page += 2;
        reset_xy();
        setpage();
    }
    else if (alnum() == 2) {
        k++;
        threetozero();
        canplace();
        if (alnum() == 2) {
            printf("end2"); // Ȯ�ο� ���� ����
            page += 2;
            reset_xy();
            setpage();
        }
    }
}

void init_page4() {
    while (ldimg_page4() != 0 );
    ldttf_page4();
    sizeinitpage4();
    setpan_page4();
    canplace();
    resettimer();
    alnum();
}

void timer() {
    nowtime = time(NULL);
    timergage2.rect.w = 270 - 9 * (int)(nowtime - setime);
    timergage.rect.w = 270 - 9 * (int)(nowtime - setime);
    timergage.rect.x = 270 + 9 * (int)(nowtime - setime);

    ldttf_page4();
    if ((nowtime - setime) == 30) {
        aipanswitch();
        resettimer();
        if (isai == 1) {
            aipanswitch();
        }
    }
}

void resettimer() {
    timergage.rect.w = 270;
    timergage.rect.h = 64;
    timergage.rect.x = 270;
    timergage.rect.y = 0;

    timergage2.rect.w = 270;
    timergage2.rect.h = 64;
    timergage2.rect.x = 644;
    timergage2.rect.y = 0;
    setime = time(NULL);
}

void showttf4() {
    SDL_RenderCopy(renderer, texturepage44, NULL, &textquadpage44);

    SDL_RenderCopy(renderer, texturepage45, NULL, &textquadpage45);

    SDL_RenderCopy(renderer, texturepage41, NULL, &textquadpage41);

    SDL_RenderCopy(renderer, texturepage42, NULL, &textquadpage42);

    SDL_RenderCopy(renderer, texturepage43, NULL, &textquadpage43);
}

void showimage4() {
    if (k % 2 == 1) {
        turn4.rect.w = 250;
        turn4.rect.h = 125;
        turn4.rect.x = 10;
        turn4.rect.y = 505;
    }
    else {
        turn4.rect.w = 250;
        turn4.rect.h = 125;
        turn4.rect.x = 928;
        turn4.rect.y = 505;
    }

    SDL_RenderCopy(renderer, timergage.texture, NULL, &(timergage.rect));

    SDL_RenderCopy(renderer, timergage2.texture, NULL, &(timergage2.rect));

    SDL_RenderCopy(renderer, timeclock.texture, NULL, &(timeclock.rect));

    SDL_RenderCopy(renderer, player14.texture, NULL, &(player14.rect));

    SDL_RenderCopy(renderer, player24.texture, NULL, &(player24.rect));

    SDL_RenderCopy(renderer, turn4.texture, NULL, &(turn4.rect));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (maal1 == 1) {
                if ((gamepan[i][j] == 1)) {
                    SDL_RenderCopy(renderer, white[i][j].texture, NULL, &(white[i][j].rect));
                }
            }
            else if (maal1 == 2) {
                if ((gamepan[i][j] == 1)) {
                    SDL_RenderCopy(renderer, yellow[i][j].texture, NULL, &(yellow[i][j].rect));
                }
            }
            else if (maal1 == 3) {
                if ((gamepan[i][j] == 1)) {
                    SDL_RenderCopy(renderer, purple[i][j].texture, NULL, &(purple[i][j].rect));
                }
            }
            else if (maal1 == 4) {
                if ((gamepan[i][j] == 1)) {
                    SDL_RenderCopy(renderer, blue[i][j].texture, NULL, &(blue[i][j].rect));
                }
            }

            if (maal2 == 1) {
                if ((gamepan[i][j] == 2)) {
                    SDL_RenderCopy(renderer, white[i][j].texture, NULL, &(white[i][j].rect));
                }
            }
            else if (maal2 == 2) {
                if ((gamepan[i][j] == 2)) {
                    SDL_RenderCopy(renderer, yellow[i][j].texture, NULL, &(yellow[i][j].rect));
                }
            }
            else if (maal2 == 3) {
                if ((gamepan[i][j] == 2)) {
                    SDL_RenderCopy(renderer, purple[i][j].texture, NULL, &(purple[i][j].rect));
                }
            }
            else if (maal2 == 4) {
                if ((gamepan[i][j] == 2)) {
                    SDL_RenderCopy(renderer, blue[i][j].texture, NULL, &(blue[i][j].rect));
                }
            }
            if (((gamepan[i][j] == 0) || (gamepan[i][j] == 3))) {
                SDL_RenderCopy(renderer, pan[i][j].texture, NULL, &(pan[i][j].rect));
            }
            if ((gamepan[i][j] == 3)) {
                SDL_RenderCopy(renderer, canpla[i][j].texture, NULL, &(canpla[i][j].rect));
            }
        }
    }

}

void bottonmove_page4(SDL_Event e) {

}