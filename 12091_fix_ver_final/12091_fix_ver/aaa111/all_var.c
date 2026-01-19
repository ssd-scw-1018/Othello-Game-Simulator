#include "all_var.h"

//소스파일이다.

// SDL 이벤트 변수이다
SDL_Event event;

// SDL 화면 변수이다.
SDL_Window* window;

// SDL 렌더 변수이다
SDL_Renderer* renderer;

// 이미지를 로드하고 렌더하기 위한 임시변수이다
SDL_Surface* image = NULL;

// 텍스트를 렌더하기 위한 임시변수이다
SDL_Surface* textsurface = NULL;

// 폰트를 열고 사용하기 위한 변수이다
TTF_Font* font;

// 기본 글자색인 검은색이다.
SDL_Color textcolor = { 0, 0, 0 };

// 오델로 게임을 처리할 판을 이차원 배열의 형태로 선언했다
// 총 64칸보드라, 8*8 이차원배열로 표현했다
// 각 칸의 값이 0이면 아무것도 없는 칸, 1이면 1p의 말이 있는상태, 2이면 2p의 말이 있는 상태
// 3이면 말을 둘 수 있는 칸인 상태, 4면 변칙 오델로에서 말을 둘 수 없는 곳을 의미한다.
int gamepan[8][8] = { 0 };

// 누구의 턴인지 특정하기 위한 변수이다. 홀수이면 1p, 짝수이면 2p 턴이다
int k = 1;

// 플레이어가 고른 캐릭터를 확인하기 위한 변수이다.
// 0은 아무것도 고르지 않은 초기상태, 1은 white, 2는 yellow, 3은 purple, 4는 blue를 골랐다는 것을 의미한다
// 두 말은 같은 것을 고를 수는 없다
int maal1 = 0, maal2 = 0;

// 게임을 계속 하기위한 변수이다 1이 되면 게임이 종료된다
int quit = 0;

// 게임 화면을 나타내는 변수이다.
// 1부터 6까지 있으며 1은 시작화면 2는 게임 모드 설정 화면 3은 캐릭터 설정화면 
// 4는 일반 오델로 게임 5는 변칙 오델로 게임 6은 게임결과화면을 의미한다
int page = 1;

// 게임 모드를 정하는 변수이다 1은 기본 오델로 2는 변칙 오델로를 의미한다
int gamemod = 1; 

// 마우스 입력을 처리할 변수이다. x, y 는 화면 왼쪽 위를 기준으로 값을 정한다
int x, y;

// 반복문에 사용되는 변수이다
int i, j;

// AI와의 대전 여부를 뜻한다. 1은 2p가 ai가 되며 0은 일반 게임상태를 의미한다
int isai = 0;

// 게임판의 상태를 나타내는 변수이다
// 게임판(gamepan[i][j])에서 0의 개수, 1의 개수, 2의 개수, 3의 개수를 의미한다.
int num0, num1, num2, num3;

// 누구의 턴인지 확인하기 위한 변수이다.
// 위의 k와 같이 사용되어 k가 홀수이면 whoturn은 1 , reverse 는 2 . 반대로 짝수이면 whoturn은 2, reverse는 1이 된다.
int whoturn, reverse;

// 게임 화면을 생성하는 과정을 모은 함수이다 . 
// 성공적으로 화면 생성시 1을 반환하고 실패시 0을 반환한다. 
int createwindows() {

    // SDL 비디오 초기화 함수이다 초기화 실패시 음수를 반환하고 성공시 0을 반환한다.
    int f = SDL_Init(SDL_INIT_VIDEO); 

    // 초기화에 대한 에러처리로 0을 반환하고 종료한다.
    if (f < 0) {
        printf("fail to init");
        return 0;
    }
    else {  // 초기화 성공시 화면생성 함수로 OTEHLLO 라는 이름의 화면을 생성한다
        window = SDL_CreateWindow("OTHELLO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1188, 640, SDL_WINDOW_SHOWN);

        // 화면 생성 실패시 0을 반환하고 종료한다.
        if (window == NULL) {
            printf("fail to create window");
            return 0;
        }
    }
    // // 2D 렌더를 생성한다
    renderer = SDL_CreateRenderer(window, -1, 0);
    // 성공적으로 마쳤다면 1을 반환한다.
    return 1;
}

// 폰트에 대한 초기화 함수이다. 성공시 1, 실패시 0을 반환한다.
int fontinit() {
    // SDL TTF초기화 함수이다. 실패시 -1을 반환한다.
    if (TTF_Init() == -1) {
        printf("fail to load font");
        return 0;  //초기화에 실패했다면 0을 반환하고 fontinit()함수를 종료한다
    }
    //성공적으로 마쳤다면 1을 반환한다.
    return 1;
}

// 페이지에 따라 화면을 출력해주는 함수이다.
// 2페이지라면 2페이지 화면을 렌더링하게 한다.
// 각각의 함수에 대한 정의는 각 함수 페이지 소스 파일에 있다
void showimageall() {
    if (page == 1) {
        showimage1();
    }
    else if (page == 2) {
        showimage2();
    }
    else if (page == 3) {
        showimage3();
    }
    else if (page == 4) {
        showimage4();
    }
    else if (page == 5) {
        showimage5();
    }
    else if (page == 6) {
        showimage6();
    }
}

// 페이지에 따라 텍스트를 출력해주는 함수이다.
// 마찬가지로 2페이지라면 2페이지에 사용되는 텍스트를 출력해준다
void showttfall() {
    if (page == 1) {
        showttf1();
    }
    else if (page == 2) {
        showttf2();
    }
    else if (page == 3) {
        showttf3();
    }
    else if (page == 4) {
        showttf4();
    }
    else if (page == 5) {
        showttf5();
    }
    else if (page == 6) {
        showttf6();
    }
}

// 페이지에 따라 이미지 로드, 텍스트 로드 등의 설정을 초기화해주고 화면을 출력해주는 함수이다..
void setpage() {
    if (page == 1) {
        init_page1();
    }
    else if (page == 2) {
        init_page2();
    }
    else if (page == 3) {
        init_page3();
    }
    else if (page == 4) {
        init_page4();
    }
    else if (page == 5) {
        init_page5();
    }
    else if (page == 6) {
        init_page6();
    }
}

// 페이지에 따라 마우스 클릭 이벤트를 처리하는 함수이다.  
void bottondown() {
    if (page == 1) {
        bottondown_page1();
    }
    else if (page == 2) {
        bottondown_page2();
    }
    else if (page == 3) {
        bottondown_page3();
    }
    else if (page == 4) {
        bottondown_page4();
    }
    else if (page == 5) {
        bottondown_page5();
    }
    else if (page == 6) {
        bottondown_page6();
    }
}

// 페이지에 따라 마우스 움직임 이벤트를 처리하는 함수이다
void bottonmove() {
    if (page == 1) {
        bottonmove_page1(event);
    }
    else if (page == 2) {
        bottonmove_page2(event);
    }
    else if (page == 4) {
        bottonmove_page4(event);
    }
    else if (page == 5) {
        bottonmove_page5(event);
    }
    else if (page == 6) {
        bottonmove_page6(event);
    }
}

// 이미지, 텍스트를 렌더링하는 과정을 모은 함수이다.  
void renderimage() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    showimageall();
    showttfall();
    SDL_RenderPresent(renderer);
}

// 제일 처음 실행되어 화면 생성, 폰트초기화, 화면 출력을 하게 되는 함수이다.
void init_initall() {
    createwindows();
    fontinit();
    setpage();
}

// 입력받은 마우스 좌표를 -1, -1로 초기화시키는 함수이다.
// 잘못된 입력을 방지하기 위해서 사용한다.
void reset_xy() {
    x = -1, y = -1;
}

// 프로그램을 종료하는 과정을 모은 함수이다.
void closeall() {
    TTF_CloseFont(font);

    SDL_FreeSurface(image);
    image = NULL;

    SDL_DestroyWindow(window);

    SDL_Quit();
}

// 페이지 4, 페이지 5 (게임화면)에서 타이머를 출력해주는 함수이다.
void show_timer() {
    if (page == 4) {
        timer();
    }
    else if (page == 5) {
        timer();
    }
}