#include "page5.h"
#include <stdlib.h>

BOTTONS blue[8][8], purple[8][8], white[8][8], yellow[8][8], canpla[8][8], pan[8][8], block[8][8],
timergage, timergage2, timeclock, player15, player25, turn5;

SDL_Texture* texturepage51, * texturepage52, * texturepage53,* texturepage54, * texturepage55;

SDL_Color textcolorpage5 = { 255, 255, 255 };

SDL_Rect textquadpage51 = { 564, 0, 60, 60 };
SDL_Rect textquadpage52 = { 72, 200, 100, 100 };
SDL_Rect textquadpage53 = { 991, 200,100, 100 };
SDL_Rect textquadpage54 = { 72, 30, 125, 125 };
SDL_Rect textquadpage55 = { 991, 30, 125, 125 };

char timebuffer[256];

time_t setime5 = 0;
time_t nowtime5 = 0;


int ldimg_page5() {
    image = IMG_Load("timer.jpg");
    if (image == NULL) {
        printf("Failed to load image : timergage \n");
        return 1;
    }
    timergage.texture = SDL_CreateTextureFromSurface(renderer, image);
    timergage2.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("pana.bmp");
    if (image == NULL) {
        printf("timeclock Failed to load image. \n");
        return 1;
    }
    timeclock.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("playerpan1 Failed to load image. \n");
        return 1;
    }
    player15.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("playerp.png");
    if (image == NULL) {
        printf("playerpan2 Failed to load image. \n");
        return 1;
    }
    player25.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    image = IMG_Load("turn.jpg");
    if (image == NULL) {
        printf("turn Failed to load image. \n");
        return 1;
    }
    turn5.texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if ((maal1 == 1) || (maal2 == 1)) {
        image = IMG_Load("white.bmp");
        if (image == NULL) {
            printf("white Failed to load image. \n");
            return 1;
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                white[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
            }
        }
        SDL_FreeSurface(image);
    }
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

    int m = 0;
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

    m = 0;
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

    image = IMG_Load("stone.png");
    if (image == NULL) {
        printf("stone Failed to load image. \n");
        return 1;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            block[i][j].texture = SDL_CreateTextureFromSurface(renderer, image);
        }
    }
    SDL_FreeSurface(image);

    return 0;
}
int ldttf_page5() {
    textsurface = TTF_RenderText_Blended(font, "1P", textcolorpage5);

    texturepage54 = SDL_CreateTextureFromSurface(renderer, textsurface);

    if (isai == 0) {
        textsurface = TTF_RenderText_Blended(font, "2P", textcolorpage5);
    }
    else textsurface = TTF_RenderText_Blended(font, "AI", textcolorpage5);

    texturepage55 = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_FreeSurface(textsurface);


    sprintf_s(timebuffer, sizeof(timebuffer), "%d", (int)(30 - (nowtime5 - setime5)));

    textsurface = TTF_RenderText_Blended(font, timebuffer, textcolor);

    texturepage51 = SDL_CreateTextureFromSurface(renderer, textsurface);

    sprintf_s(timebuffer, sizeof(timebuffer), "%d", (int)num1);

    textsurface = TTF_RenderText_Blended(font, timebuffer, textcolor);

    texturepage52 = SDL_CreateTextureFromSurface(renderer, textsurface);

    sprintf_s(timebuffer, sizeof(timebuffer), "%d", (int)num2);

    textsurface = TTF_RenderText_Blended(font, timebuffer, textcolor);

    texturepage53 = SDL_CreateTextureFromSurface(renderer, textsurface);

    return 1;
}
void sizeinitpage5() {
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

    initx = initxx;
    inity = inityy;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            block[i][j].rect.w = WIDTHOFMAL;
            block[i][j].rect.h = HEIGHTOFMAL;
            block[i][j].rect.x = initx;
            block[i][j].rect.y = inity;
            initx += WIDTHOFMAL;
        }
        initx = initxx;
        inity += HEIGHTOFMAL;
    }

    timeclock.rect.w = 108;
    timeclock.rect.h = 64;
    timeclock.rect.x = 540;
    timeclock.rect.y = 0;

    timergage.rect.w = 270;
    timergage.rect.h = 64;
    timergage.rect.x = 270;
    timergage.rect.y = 0;

    timergage2.rect.w = 270;
    timergage2.rect.h = 64;
    timergage2.rect.x = 644;
    timergage2.rect.y = 0;

    player15.rect.w = 270;
    player15.rect.h = 640;
    player15.rect.x = 0;
    player15.rect.y = 0;

    player25.rect.w = 270;
    player25.rect.h = 640;
    player25.rect.x = 918;
    player25.rect.y = 0;

    if (k % 2 == 1) {
        turn5.rect.w = 250;
        turn5.rect.h = 125;
        turn5.rect.x = 10;
        turn5.rect.y = 505;
    }
    else {
        turn5.rect.w = 250;
        turn5.rect.h = 125;
        turn5.rect.x = 928;
        turn5.rect.y = 505;
    }
}
void init_show_page5() {
   
}
void setpan_page5() {
    gamepan[3][4] = gamepan[4][3] = 1;
    gamepan[3][3] = gamepan[4][4] = 2;

    int i, x, y;
    int j = 0;
    srand(time(NULL));

    for (i = 0; ; i++) {

        x = rand() % 8;
        y = rand() % 8;

        if ((gamepan[x][y] == 1) || (gamepan[x][y] == 2) || (gamepan[x][y] == 3) || (gamepan[x][y] == 4)) {
            continue;
        }
        else {

            gamepan[x][y] = 4;

            j++;

            if (j == 5) {
                break;
            }
        }

    }
}
void bottondown_page5() {
    SDL_GetMouseState(&x, &y);

    x = (x - 270) / 81;
    y = (y - 64) / 72;

    malswitch(y, x);

    if (k % 2 == 1) {
        turn5.rect.w = 250;
        turn5.rect.h = 125;
        turn5.rect.x = 10;
        turn5.rect.y = 505;
    }
    else {
        turn5.rect.w = 250;
        turn5.rect.h = 125;
        turn5.rect.x = 928;
        turn5.rect.y = 505;
    }

    threetozero();

    canplace();

    alnum();

    if (alnum() == 1) {
        printf("end1"); //Ȯ�ο� ���� ����
        page += 1;
        reset_xy();
        setpage();
        close_page5();
    }
    else if (alnum() == 2) {
        k++;
        threetozero();
        canplace();
        if (alnum() == 2) {
            printf("end2"); // Ȯ�ο� ���� ����
            page += 1;
            reset_xy();
            setpage();
            close_page5();
        }
    }
    if ((isai == 1) && (k % 2 == 0)) {

        aipanswitch();

    }
}
void bottonmove_page5(SDL_Event e) {

}
void close_page5() {
    isai = 0;
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
    SDL_DestroyTexture(texturepage51);
    SDL_DestroyTexture(texturepage52);
    SDL_DestroyTexture(texturepage53);
}
void init_page5() {
    while (ldimg_page5() != 0 );
    ldttf_page5();
    sizeinitpage5();
    init_show_page5();
    setpan_page5();
    canplace();
    resettimer();
    alnum();
}
void showttf5() {
    SDL_RenderCopy(renderer, texturepage54, NULL, &textquadpage54);

    SDL_RenderCopy(renderer, texturepage55, NULL, &textquadpage55);

    SDL_RenderCopy(renderer, texturepage51, NULL, &textquadpage51);

    SDL_RenderCopy(renderer, texturepage52, NULL, &textquadpage52);

    SDL_RenderCopy(renderer, texturepage53, NULL, &textquadpage53);
}
void showimage5() {
    SDL_RenderCopy(renderer, timergage.texture, NULL, &(timergage.rect));


    SDL_RenderCopy(renderer, timergage2.texture, NULL, &(timergage2.rect));


    SDL_RenderCopy(renderer, timeclock.texture, NULL, &(timeclock.rect));

    SDL_RenderCopy(renderer, player15.texture, NULL, &(player15.rect));

    SDL_RenderCopy(renderer, player25.texture, NULL, &(player25.rect));

    SDL_RenderCopy(renderer, turn5.texture, NULL, &(turn5.rect));

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
            if ((gamepan[i][j] == 4)) {
                SDL_RenderCopy(renderer, block[i][j].texture, NULL, &(block[i][j].rect));
            }
        }
    }
}