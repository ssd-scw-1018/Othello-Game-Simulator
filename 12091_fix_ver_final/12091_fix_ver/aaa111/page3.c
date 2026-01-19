#include "page3.h"

// 오셀로 게임 코드입니다(페이지 3).
// page 3에 사용될 함수들을 정리한 소스파일이다.

BOTTONS mal[4], // 플레이어가 고를 수 있는 게임 말이다
        player1p, player2p, // 플레이어 1, 2의 보드블럭이다
        readya1, readya2,   // 플레이어 1, 2의 준비블럭이다, 준비 버튼 1이 눌려야 2를 누를 수 있다
        aibotton, //ai 대전 블럭이다
        gobotton, // 시작 버튼 블럭이다, ready 버튼 두개가 다 눌려야 누를 수 있다.
        check, readycheck1, readycheck2, // 버튼이 눌리면 check 표시가 뜬다.
        back3; //배경화면이다.

SDL_Texture* texturepage31, // 1p 를 출력하기 위한 변수
            * texturepage32; // 2p 를 출력하기 위한 변수 ( ai 대전 시 ai 를 출력)

SDL_Color textcolorpage3 = { 255, 255, 40 };// page 3에서는 노란색으로 1p 2p 출력

SDL_Rect textquadpage31 = { 72, 30, 125, 125 }; // 1p 를 출력하기 위한 상자
SDL_Rect textquadpage32 = { 991, 30, 125, 125 };// 2p 를 출력하기 위한 상자 ( ai 대전 시 ai 를 출력)

int canready = 0;   // 플레이어 1이 말을 선택하고 나면 플레이어 1 준비가능상태가 된다
                    // 준비 가능 상태가 되면 값이 1이 된다

//플레이어 1,2의 준비상태를 나타낸다
//1이면 준비상태, 0이면 준비되지 않은 상태이다
int areready1 = 0, areready2 = 0;

// 플레이어 1,2가 모두 준비상태이면 
// cango =1 이 되고 게임 시작 버튼을 누를 수 있게 된다.
int cango = 0;

// page 3에 사용될 이미지들을 로드하는 함수이다.
// 성공적으로 이미지 로드 시 0을 반환하고 
// 실패시 어떤 이미지를 로드 실패했는지 알려주고 1을반환한다. 
int ldimg_page3() {
    // 게임의 배경화면을 로드한다
    image = IMG_Load("back1.png");
    if (image == NULL) {
        printf("Failed to load image : startscreen \n");
        return 1;
    }
    back3.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 사용자 캐릭터 0을 로드한다
    image = IMG_Load("white.bmp");
    if (image == NULL) {
        printf("Failed to load image : white  \n");
        return 1;
    }
    mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 사용자 캐릭터 1을 로드한다
    image = IMG_Load("yellow.bmp");
    if (image == NULL) {
        printf("Failed to load image : yellow  \n");
        return 1;
    }
    mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 사용자 캐릭터 2을 로드한다
    image = IMG_Load("purple.jpg");
    if (image == NULL) {
        printf("Failed to load image : purple \n");
        return 1;
    }
    mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 사용자 캐릭터 3을 로드한다
    image = IMG_Load("blue.jpg");
    if (image == NULL) {
        printf("Failed to load image : blue  \n");
        return 1;
    }
    mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 플레이어 1, 2의 플레이어보드를 로드한다
    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("Failed to load image : playerpan  \n");
        return 1;
    }
    player1p.texture = SDL_CreateTextureFromSurface(renderer, image);
    player2p.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 준비 버튼1, 2를 로드한다
    image = IMG_Load("ready.jpg");
    if (image == NULL) {
        printf("Failed to load image : ready \n");
        return 1;
    }
    readya1.texture = SDL_CreateTextureFromSurface(renderer, image);
    readya2.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // ai 대전 버튼을 로드한다
    image = IMG_Load("ai.png");
    if (image == NULL) {
        printf("Failed to load image : ai_image \n");
        return 1;
    }
    aibotton.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 체크 이미지를 로드한다
    image = IMG_Load("check.png");
    if (image == NULL) {
        printf("Failed to load image : check \n");
        return 1;
    }
    check.texture = SDL_CreateTextureFromSurface(renderer, image);
    readycheck1.texture = SDL_CreateTextureFromSurface(renderer, image);
    readycheck2.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    // 게임 시작 버튼을 로드한다
    image = IMG_Load("go.jpg");
    if (image == NULL) {
        printf("Failed to load image : go_image \n");
        return 1;
    }
    gobotton.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return 0;
}
// 페이지 3에 사용될 텍스트를 로드하는 함수이다 
// 성공시 0, 실패시 1을 반환한다
int ldttf_page3() {
    // 왼쪽 위에 1p텍스트를 만든다
    textsurface = TTF_RenderText_Blended(font, "1P", textcolorpage3);

    texturepage31 = SDL_CreateTextureFromSurface(renderer, textsurface);
    // 오른쪽 위에 2p 텍스트를 만든다
    // 단 ai 대전 버튼을 클릭시 2p 텍스트가 ai 로 바뀐다
    if (isai == 0) {
        textsurface = TTF_RenderText_Blended(font, "2P", textcolorpage3);
    }
    else textsurface = TTF_RenderText_Blended(font, "AI", textcolorpage3);

    texturepage32 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);
    // textsurface 의 사용이 끝났으니 비워준다. 

    // 성공적으로 마무리 되었다면 0을 반환한다.
    return 0;
}
// 페이지 3에 쓰이는 이미지들의 크기와 위치를 초기화하는 함수이다. 
void sizeinitpage3() {
    // 배경화면의 크기는 화면 전체의 크기와 같게 한다.
    back3.rect.w = 1188;
    back3.rect.h = 640;
    back3.rect.x = 0;
    back3.rect.y = 0;
    // 플레이어보드1 블럭의 크기와 위치이다
    player1p.rect.w = 270;
    player1p.rect.h = 640;
    player1p.rect.x = 0;
    player1p.rect.y = 0;
    // 플레이어보드2 블럭의 크기와 위치이다
    player2p.rect.w = 270;
    player2p.rect.h = 640;
    player2p.rect.x = 918;
    player2p.rect.y = 0;

    // 말 블럭 4개의 크기와 위치이다
    for (int i = 0; i < 4; i++) {
        mal[i].rect.w = 132;
        mal[i].rect.h = 132;
        mal[i].rect.x = 300 + (152 * i);
        mal[i].rect.y = 368;
    }
    // 준비버튼 1의 크기와 위치이다
    readya1.rect.w = 250;
    readya1.rect.h = 125;
    readya1.rect.x = 10;
    readya1.rect.y = 505;
    // 준비버튼 2의 크기와 위치이다
    readya2.rect.w = 250;
    readya2.rect.h = 125;
    readya2.rect.x = 928;
    readya2.rect.y = 505;
    // ai 대전 버튼의 크기와 위치이다
    aibotton.rect.w = 100;
    aibotton.rect.h = 90;
    aibotton.rect.x = 770;
    aibotton.rect.y = 70;
    // ai 체크 의 크기와 위치이다
    check.rect.w = 120;
    check.rect.h = 120;
    check.rect.x = 765;
    check.rect.y = 20;
    // 준비체크 1의 크기와 위치이다
    readycheck1.rect.w = 120;
    readycheck1.rect.h = 120;
    readycheck1.rect.x = 75;
    readycheck1.rect.y = 505;
    // 준비체크 2의 크기와 위치이다
    readycheck2.rect.w = 120;
    readycheck2.rect.h = 120;
    readycheck2.rect.x = 988;
    readycheck2.rect.y = 505;
    // 게임시작버튼의 크기와 위치이다
    gobotton.rect.w = 300;
    gobotton.rect.h = 132;
    gobotton.rect.x = 444;
    gobotton.rect.y = 504;
}
// 페이지 3이 종료될 때 (다음 페이지로 넘어가거나 종료) 사용이 끝난 텍스쳐들을 파괴하는 함수이다.
// 페이지 값이 변경되면 사용한다. 
void close_page3() {
    // 체크들의 show 값을 0으로 바꿔준다
    // 만약 바꾸지 않으면 다음  페이지에서도 체크가 표시된다
    check.show = readycheck1.show = readycheck2.show = 0;
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(mal[i].texture);
    }
    // 텍스쳐들을 파괴한다
    SDL_DestroyTexture(player1p.texture);
    SDL_DestroyTexture(player2p.texture);
    SDL_DestroyTexture(readya1.texture);
    SDL_DestroyTexture(readya2.texture);
    SDL_DestroyTexture(aibotton.texture);
    SDL_DestroyTexture(check.texture);
    SDL_DestroyTexture(readycheck1.texture);
    SDL_DestroyTexture(readycheck2.texture);
    SDL_DestroyTexture(gobotton.texture);
    SDL_DestroyTexture(texturepage31);
    SDL_DestroyTexture(texturepage32);
}
// 페이지 3에서 마우스 클릭 이벤트를 다루는 함수이다.
void bottondown_page3() {
    // 마우스의 x, y 좌표를 받는다
    SDL_GetMouseState(&x, &y);
     // 사용자가 ai 대전 버튼을 누르면
    if ((x > aibotton.rect.x) && (x < aibotton.rect.x + aibotton.rect.w)
        && (y > aibotton.rect.y) && (y < aibotton.rect.y + aibotton.rect.h)) {
        if (check.show != 1) { // is ai를 1로 설정하고 check 이미지를 보이게 한다
            check.show = 1;
            isai = 1;
            ldttf_page3(); // 2p 텍스트를 ai로 바꾼다
        }
        // 출력하되 이미 한번 누른 상태라면 다시 클릭시 
        // ai 대전 값은 0이 되고 check는 보이지 않게 한다
        else if (check.show == 1) {
            check.show = 0;
            isai = 0;
            ldttf_page3();
        }
    }
    // 만약 말 0을 누른다면
    if ((x > mal[0].rect.x) && (x < mal[0].rect.x + mal[0].rect.w)
        && (y > mal[0].rect.y) && (y < mal[0].rect.y + mal[0].rect.h)) {
            // 플레이어 2 말을 고르지 않은 상태에서
        if (maal2 == 0) {
            maal1 = 1;
            canready = 1;
            // 플레이어 말 값은 1로 설정하고
            // 준비 버튼 1를 누를 수 있게 된다

            SDL_SetTextureColorMod(mal[0].texture, 100, 100, 100);
            // 말 0의 밝기를 낮추고 나머지 말들은 밝게 한다

            image = IMG_Load("yellow.bmp");
            if (image == NULL) {
                printf("Failed to load image : yellow \n");
            }
            mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("purple.jpg");
            if (image == NULL) {
                printf("Failed to load image : purple  \n");
            }
            mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("blue.jpg");
            if (image == NULL)
                printf("Failed to load image : blue  \n");
            mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);

        }
        // 만약 플레이어 1 말을 고른 상태에서 
        // 플레이어 1이 고른 말이 0이 아니면
        // 플레이어 2의 말을 0으로 한다
        else if ((maal2 != 0) && (maal1 != 1)) {
            maal2 = 1;
            canready = 2;

            SDL_SetTextureColorMod(mal[0].texture, 100, 100, 100);

            if (maal1 != 2) {
                image = IMG_Load("yellow.bmp");
                if (image == NULL)
                    printf("yellow Failed to load image. \n");
                mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 3) {
                image = IMG_Load("purple.jpg");
                if (image == NULL)
                    printf("purple Failed to load image. \n");
                mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 4) {
                image = IMG_Load("blue.jpg");
                if (image == NULL)
                    printf("blue Failed to load image. \n");
                mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
        }

    }
    // 플레이어 2의 말을 고르지 않은 상태에서
    // 말 1을 누르면
    // 플레이어 말 값은 2로 설정하고
    // 준비 버튼 1를 누를 수 있게 된다
    if ((x > mal[1].rect.x) && (x < mal[1].rect.x + mal[1].rect.w)
        && (y > mal[1].rect.y) && (y < mal[1].rect.y + mal[1].rect.h)) {
        if (maal2 == 0) {
            maal1 = 2;
            canready = 1;

            SDL_SetTextureColorMod(mal[1].texture, 100, 100, 100);

            image = IMG_Load("white.bmp");
            if (image == NULL)
                printf("Failed to load image : white  \n");
            mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("purple.jpg");
            if (image == NULL)
                printf("Failed to load image : purple  \n");
            mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("blue.jpg");
            if (image == NULL)
                printf("Failed to load image : blue  \n");
            mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
        }
        else if ((maal2 != 0) && (maal1 != 2)) {
            maal2 = 2;
            canready = 2;

            SDL_SetTextureColorMod(mal[1].texture, 100, 100, 100);

            if (maal1 != 1) {
                image = IMG_Load("white.bmp");
                if (image == NULL)
                    printf("Failed to load image : white  \n");
                mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 3) {
                image = IMG_Load("purple.jpg");
                if (image == NULL)
                    printf("Failed to load image : purple  \n");
                mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 4) {
                image = IMG_Load("blue.jpg");
                if (image == NULL)
                    printf("Failed to load image : blue  \n");
                mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
        }

    }
    if ((x > mal[2].rect.x) && (x < mal[2].rect.x + mal[2].rect.w)
        && (y > mal[2].rect.y) && (y < mal[2].rect.y + mal[2].rect.h)) {
        if (maal2 == 0) {
            maal1 = 3;
            canready = 1;

            SDL_SetTextureColorMod(mal[2].texture, 100, 100, 100);

            image = IMG_Load("white.bmp");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("blue.jpg");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("yellow.bmp");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
        }
        else if ((maal2 != 0) && (maal1 != 3)) {
            maal2 = 3;
            canready = 2;

            SDL_SetTextureColorMod(mal[2].texture, 100, 100, 100);

            if (maal1 != 1) {
                image = IMG_Load("white.bmp");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 2) {
                image = IMG_Load("yellow.bmp");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 4) {
                image = IMG_Load("blue.jpg");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[3].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
        }

    }
    if ((x > mal[3].rect.x) && (x < mal[3].rect.x + mal[3].rect.w)
        && (y > mal[3].rect.y) && (y < mal[3].rect.y + mal[3].rect.h)) {
        if (maal2 == 0) {
            maal1 = 4;
            canready = 1;

            SDL_SetTextureColorMod(mal[3].texture, 100, 100, 100);


            image = IMG_Load("white.bmp");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("purple.jpg");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);


            image = IMG_Load("yellow.bmp");
            if (image == NULL)
                printf("pana Failed to load image. \n");
            mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);

        }
        else if ((maal2 != 0) && (maal1 != 4)) {
            maal2 = 4;
            canready = 2;

            SDL_SetTextureColorMod(mal[3].texture, 100, 100, 100);

            if (maal1 != 1) {
                image = IMG_Load("white.bmp");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[0].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 3) {
                image = IMG_Load("purple.jpg");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[2].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
            if (maal1 != 2) {
                image = IMG_Load("yellow.bmp");
                if (image == NULL)
                    printf("pana Failed to load image. \n");
                mal[1].texture = SDL_CreateTextureFromSurface(renderer, image);
                SDL_FreeSurface(image);
            }
        }
    }
    // 만약 플레이어 1이 말을 고른 상태에서
    // 준비 버튼 1을 누른다면
    if ((x > readya1.rect.x) && (x < readya1.rect.x + readya1.rect.w)
        && (y > readya1.rect.y) && (y < readya1.rect.y + readya1.rect.h) && (canready == 1)) {
            // 플레이어 1의 준비상태를 1로 변경한다
        areready1 = 1;
        // 플레이어 2의 말을 고를 수 있는 상태로 변경한다
        maal2 = -1;
    }
    // 만약 플레이어 2가 말을 고른 상태에서
    // 준비 버튼 2을 누른다면
    if ((x > readya2.rect.x) && (x < readya2.rect.x + readya2.rect.w)
        && (y > readya2.rect.y) && (y < readya2.rect.y + readya2.rect.h) && (canready == 2)) {
        // 플레이어 2의 준비상태를 1로 변경한다
        areready2 = 1;
    }
    // 만약 플레이어 1이 준비상태라먄
    // 준비버튼 1에 check 표시를 띄운다
    if (areready1 == 1) {
        readycheck1.show = 1;
    }
    // 플레이어 1이 준비상태가 아니면 check표시를 지운다
    else readycheck1.show = 0;
    // 만약 플레이어 2이 준비상태라먄
    // 준비버튼 2에 check 표시를 띄운다
    if (areready2 == 1) {
        readycheck2.show = 1;
    }
    // 플레이어 2이 준비상태가 아니면 check표시를 지운다
    else readycheck2.show = 0;

    // 만약 플레이어 1, 2가 모두 준비상태라면
    // 시작 버튼을 누를 수 있다
    if ((areready1 == 1) && (areready2 == 1)) {
        cango = 1;
    }
    else cango = 0;

    // 시작버튼을 누른다면
    if ((x > gobotton.rect.x) && (x < gobotton.rect.x + gobotton.rect.w)
        && (y > gobotton.rect.y) && (y < gobotton.rect.y + gobotton.rect.h) && (cango == 1)) {
            // 노말모드를 택했다면 페이지 4로간다
        if (gamemod == 1) {
            page++;
        }
        // 변칙모드를 택했다면 페이지 5로 간다
        else if (gamemod == 2) {
            page += 2;
        }
        // 새 페이지를 세팅한다
        setpage();
        // 페이지 3을 닫는다
        close_page3();
        // 입력받은 x y 좌표를 초기화한다
        reset_xy();
        // 재실행을 위해 다음 값들은 다시 0으로 초기화시킨다
        canready = areready1 = areready2 = cango = 0;
        k = 1;
    }
}
// 페이지 3 을 시작하는 함수이다.
// 페이지 3 시작시 필요한 초기 환경을 세팅한다
void init_page3() {
    // 페이지3에 사용될 이미지를 로드한다 이미지 로드에 실패하면 성공할때까지 반복
    while (ldimg_page3() != 0 );
    // 페이지3에 사용될 텍스트를 로드한다 텍스트 로드에 실패하면 성공할때까지 반복
    while (ldttf_page3() != 0 );
    // 페이지 3의 이미지들의 크기, 위치를 초기화한다
    sizeinitpage3();
}
// 페이지 3의 텍스트를 렌더하는 함수이다
void showttf3() {
    SDL_RenderCopy(renderer, texturepage31, NULL, &textquadpage31);
    SDL_RenderCopy(renderer, texturepage32, NULL, &textquadpage32);
}
// 페이지 3의 이미지들을 렌더하는 함수이다.
void showimage3() {
    // 배경화면을 렌더한다
    SDL_RenderCopy(renderer, back3.texture, NULL, &(back3.rect));
    // 플레이어1,2보드를 렌더한다
    SDL_RenderCopy(renderer, player1p.texture, NULL, &(player1p.rect));
    SDL_RenderCopy(renderer, player2p.texture, NULL, &(player2p.rect));
    // 플레이어 말 0~3을 렌더한다
    SDL_RenderCopy(renderer, mal[0].texture, NULL, &(mal[0].rect));
    SDL_RenderCopy(renderer, mal[1].texture, NULL, &(mal[1].rect));
    SDL_RenderCopy(renderer, mal[2].texture, NULL, &(mal[2].rect));
    SDL_RenderCopy(renderer, mal[3].texture, NULL, &(mal[3].rect));
    // 준비버튼 1,2 를 렌더한다
    SDL_RenderCopy(renderer, readya1.texture, NULL, &(readya1.rect));
    SDL_RenderCopy(renderer, readya2.texture, NULL, &(readya2.rect));
    // ai대전버튼을 렌더한다
    SDL_RenderCopy(renderer, aibotton.texture, NULL, &(aibotton.rect));
    // 게임 시작 버튼을 렌더한다
    SDL_RenderCopy(renderer, gobotton.texture, NULL, &(gobotton.rect));
    // ai대전버튼을 누른 상태에서 check.show 값은 1이 된다
    if (check.show == 1) {
        SDL_RenderCopy(renderer, check.texture, NULL, &(check.rect));
    }
    if (readycheck1.show == 1) {
        SDL_RenderCopy(renderer, readycheck1.texture, NULL, &(readycheck1.rect));
    }
    if (readycheck2.show == 1) {
        SDL_RenderCopy(renderer, readycheck2.texture, NULL, &(readycheck2.rect));
    }
}
