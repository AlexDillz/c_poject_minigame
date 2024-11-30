//ObjectInit(&player, 10,220, 40,40, 'e');
//ObjectInit(NewObject(),420,0, 40,40, 'p');
//ObjectInit(NewObject(),420,100, 40,40, 'p');
//ObjectInit(NewObject(),420,200, 40,40, 'p');
//ObjectInit(NewObject(),420,300, 40,40, 'p');
//ObjectInit(NewObject(),420,400, 40,40, 'p');

//ObjectInit(NewObject(),0,300, 20,20, 'c');

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

#define _WIN32_WINT 0x0A00

#define bt2_id 2
#define edt1_id 3
#define cb1_id 4
#define btE_id 5



HWND bt_quit;
HWND cap1;
HWND CB;
HWND bt_send;
//HWND cap2;
HWND cap3;
HWND cap4;
HWND cap5;
HWND edt;
HWND hwnd;

char nameStr[200];
int level = 20;
int speedKiller = 2;
BOOL flagNextGame = FALSE;
int globalCount = 0;
char strGlobalCount[];


char digit_str[1000];
FILE *file;
char *arr[80];
int count_int;



FILE *fr;
FILE *f;
char *line[1000];
char substrings[1000];
char *token;
int intToken;
int position;


char raitingStr[10000];

char *lineRaiting[1000];

int count_str = 0;

int count1 = 0;
int seek1 = 0;
int stroka_nado;

char old_str[1000];
char new_str[1000];


char nameStrRaiting[200];



BOOL flagGame = FALSE;
BOOL flagCreate = FALSE;


typedef struct SPoint {
    float x,y;
} TPoint;

TPoint point (float x, float y)
{
    TPoint pt;
    pt.x = x;
    pt.y = y;
    return pt;
}

typedef struct SObject
{
    TPoint pos;
    TPoint size;
    COLORREF brush;
    TPoint speed;
    char oType;
    BOOL isDel;

} TObject, *PObject;

void ObjectInit(TObject *obj, float xPos, float yPos, float width, float heigh, char objType)
{
    obj->pos = point(xPos, yPos);
    obj->size = point (width, heigh);
    obj->brush = RGB (0,255,0);
    obj->speed = point(0,0);
    obj->oType = objType;
    if (objType == 'e') obj->brush = RGB(255,0,0);
    else if (objType == 'c') obj->brush = RGB(255,255,0);
    else if (objType == 'a') obj->brush = RGB(0,0,0);
    else if (objType == 'i') obj->brush = RGB(148,0,211);
    obj->isDel = FALSE;
}


BOOL ObjectCollision(TObject o1, TObject o2) // ‘ÛÌÍˆËˇ ÔÓ‚ÂÍË ÔÂÂÒÂ˜ÂÌËˇ ÍÓÓ‰ËÌ‡Ú
{
    return ((o1.pos.x + o1.size.x) > o2.pos.x) && (o1.pos.x < (o2.pos.x + o2.size.x)) &&
           ((o1.pos.y + o1.size.y) > o2.pos.y) && (o1.pos.y < (o2.pos.y + o2.size.y)); // ¬ÓÁ‚‡˘‡ÂÚ False ‚Ó ‚ÒÂı ÒÎÛ˜‡ˇı, ÍÓ„‰‡ ÍÓÓ‰ËÌ‡Ú˚ ÌÂ ÔÂÂÒÂÍ‡˛ÚÒˇ

}

void ObjectShow(TObject obj, HDC dc)
{
    SelectObject (dc, GetStockObject(DC_PEN));
    SetDCPenColor( dc, RGB(0, 0, 0));
    SelectObject (dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor( dc, obj.brush );


    BOOL (*shape)(HDC, int,int,int,int);
    shape = obj.oType == 'e' ? Ellipse : Rectangle;
    shape(dc, (int)(obj.pos.x), (int)(obj.pos.y),
          (int)(obj.pos.x + obj.size.x), (int)(obj.pos.y + obj.size.y));
}

RECT rct;
TObject player;

PObject mas = NULL;
int masCnt = 0;

void ObjectMove(TObject *obj)
{
    if (obj->oType == 'p')
    {
        obj->pos.x -=speedKiller; // Ó·‡ÚË ‚ÌËÏ‡ÌËÂ Ì‡ Ò‰‚Ë„ ·ÓÌÛÒ‡ ‚ÏÂÒÚÂ ÒÓ ÒÚÂÌÍÓÈ
        if (ObjectCollision(*obj, player))
        {
            for (int i = 0; i < masCnt; i++)
                mas[i].isDel = TRUE;

            //--------------------------------------------------
            fr = fopen("test1.txt", "r");

            position = 0;

            if (fr == NULL) {
                printf("Unable to open file1.\n");
                exit(1);
            }


            while (fgets(line, 10000, fr)) {
                token = strtok(line, " ");

                if (token == NULL) break;

                token = strtok(NULL, " ");
                if (token == NULL) break;

                intToken = atoi(token);
                if (globalCount <= intToken)

                {
                    position++;
                }


            }


            fclose(fr);

            strcpy(digit_str,"");

            itoa(globalCount, digit_str, 10);



            file = fopen("test1.txt", "r");
            if (file == NULL) {
                printf("Unable to open file2.\n");
                exit(1);
            }
            count1 = 0;
            seek1 = 0;
            stroka_nado = position - 1;

            strcpy(old_str, "");

            strcpy(new_str, "");






            while (fgets(arr, 80, file) != NULL)
            {


                if (count1 <= stroka_nado)
                {
                    strcat(old_str, arr);

                }
                if (count1 > stroka_nado)
                    strcat(new_str, arr);

                count1++;


            }

            strcpy(nameStrRaiting, "");
            strcat(nameStrRaiting, nameStr);
            strcat(nameStrRaiting, " ");

            strcat(nameStrRaiting, digit_str);
            strcat(nameStrRaiting, "\n");


            strcat(old_str, "");

            strcat(old_str, nameStrRaiting);
            strcat(old_str, new_str);

            strcpy(nameStrRaiting, "");




            fclose(file);

            file = fopen("test1.txt", "w");
            if (file == NULL) {
                printf("Unable to open file3.\n");
                exit(1);
            }
            fprintf(file, old_str);

            fclose(file);

            flagCreate = TRUE;
            flagGame = FALSE;

        }
        if (obj->pos.x <= 0)
        {
            obj->isDel = TRUE;
            flagNextGame = TRUE;
        }

    }
    if (obj->oType == 'c')
    {
        if (ObjectCollision(*obj, player))
        {
            speedKiller = 2;
            obj->isDel = TRUE;
            globalCount -=1;
        }
    }
    if (obj->oType == 'a')
    {
        if (ObjectCollision(*obj, player))
        {
            speedKiller = 8;
            obj->isDel = TRUE;
            globalCount += 2;
        }
    }
    if (obj->oType == 'i')
    {
        obj->pos.x -= speedKiller;
        if (ObjectCollision(*obj, player))
        {
            obj->isDel = TRUE;
            globalCount += 3;

        }
    }
    if (obj->oType == 'e')
    {
        if (obj->pos.x + obj->speed.x <= 0 || 0 >= obj->pos.y + obj->speed.y || obj->pos.y + obj->speed.y >= 440)
        {
            for (int i = 0; i < masCnt; i++)
                mas[i].isDel = TRUE;
            level = 0;
            globalCount = 0;
            WinInit();

        }
    }
    obj->pos.x += obj->speed.x;
    obj->pos.y += obj->speed.y;
}

PObject NewObject()
{

    masCnt++;
    mas = realloc( mas, sizeof(*mas) * masCnt);
    return mas + masCnt - 1;
}

void WinInit()
{

    if (level == 0)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 1)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 2)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 3)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 4)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 5)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 5;
    }
    else if (level == 6)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 6;
    }
    else if (level == 7)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 7;
    }
    else if (level == 8)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),0,150, 20,20, 'c');

        speedKiller = 7;
    }
    else if (level == 9)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 7;
    }
    else if (level == 10)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,100, 20,20, 'c');

        speedKiller = 8;
    }
    else if (level == 11)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),420,200, 40,40, 'i');

        ObjectInit(NewObject(),10,300, 20,20, 'c');

        speedKiller = 8;
    }
    else if (level == 12)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,150, 20,20, 'c');

        speedKiller = 8;
    }
    else if (level == 13)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        speedKiller = 8;
    }
    else if (level == 14)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,150, 20,20, 'c');

        speedKiller = 9;
    }
    else if (level == 15)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,180, 20,20, 'c');

        speedKiller = 9;
    }
    else if (level == 16)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,280, 20,20, 'a');

        speedKiller = 2;
    }
    else if (level == 17)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,70, 20,20, 'c');

        speedKiller = 8;
    }
    else if (level == 18)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,180, 20,20, 'a');

        speedKiller = 4;
    }
    else if (level == 19)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,300, 20,20, 'c');

        speedKiller = 8;

        Sleep(5);
    }
    else if (level == 20)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,100, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,180, 20,20, 'c');

        speedKiller = 8;

        Sleep(5);
    }
    else if (level == 21)
    {
        ObjectInit(&player, 10,220, 40,40, 'e');
        ObjectInit(NewObject(),420,0, 40,40, 'p');
        ObjectInit(NewObject(),420,50, 40,40, 'p');
        ObjectInit(NewObject(),420,150, 40,40, 'p');
        ObjectInit(NewObject(),420,200, 40,40, 'p');
        ObjectInit(NewObject(),420,250, 40,40, 'p');
        ObjectInit(NewObject(),420,300, 40,40, 'p');
        ObjectInit(NewObject(),420,350, 40,40, 'p');
        ObjectInit(NewObject(),420,400, 40,40, 'p');

        ObjectInit(NewObject(),10,150, 20,20, 'c');
        ObjectInit(NewObject(),10,210, 20,20, 'a');

        speedKiller = 2;

        Sleep(5);
    }
    else
    {
                   for (int i = 0; i < masCnt; i++)
                mas[i].isDel = TRUE;

            //--------------------------------------------------
            fr = fopen("test1.txt", "r");

            position = 0;

            if (fr == NULL) {
                printf("Unable to open file1.\n");
                exit(1);
            }


            while (fgets(line, 10000, fr)) {
                token = strtok(line, " ");

                if (token == NULL) break;

                token = strtok(NULL, " ");
                if (token == NULL) break;

                intToken = atoi(token);
                if (globalCount <= intToken)

                {
                    position++;
                }


            }


            fclose(fr);

            strcpy(digit_str,"");

            itoa(globalCount, digit_str, 10);



            file = fopen("test1.txt", "r");
            if (file == NULL) {
                printf("Unable to open file2.\n");
                exit(1);
            }
            count1 = 0;
            seek1 = 0;
            stroka_nado = position - 1;

            strcpy(old_str, "");

            strcpy(new_str, "");






            while (fgets(arr, 80, file) != NULL)
            {


                if (count1 <= stroka_nado)
                {
                    strcat(old_str, arr);

                }
                if (count1 > stroka_nado)
                    strcat(new_str, arr);

                count1++;


            }

            strcpy(nameStrRaiting, "");
            strcat(nameStrRaiting, nameStr);
            strcat(nameStrRaiting, " ");

            strcat(nameStrRaiting, digit_str);
            strcat(nameStrRaiting, "\n");


            strcat(old_str, "");

            strcat(old_str, nameStrRaiting);
            strcat(old_str, new_str);

            strcpy(nameStrRaiting, "");




            fclose(file);

            file = fopen("test1.txt", "w");
            if (file == NULL) {
                printf("Unable to open file3.\n");
                exit(1);
            }
            fprintf(file, old_str);

            fclose(file);

            flagCreate = TRUE;
            flagGame = FALSE;

        }
    }

void PlayerControl()
{
    static int playerSpeed = 5;
    player.speed.x = 0;
    player.speed.y = 0;
    if(GetKeyState('W') < 0) player.speed.y = -playerSpeed;
    if(GetKeyState('S') < 0) player.speed.y = playerSpeed;
    if(GetKeyState('A') < 0) player.speed.x = -playerSpeed;
    if(GetKeyState('D') < 0) player.speed.x = playerSpeed;
    if ((player.speed.x != 0) && (player.speed.y != 0))
        player.speed = point(player.speed.x * 0.7, player.speed.y * 0.7);
}

void DelObjects() //  œÓˆÂ‰Û‡ Û‰‡Îˇ˛˘‡ˇ ÔÓÏÂ˜ÂÌÌ˚Â Ó·˙ÂÍÚ˚ ËÁ Ï‡ÒÒË‚‡
{
    int i = 0;
    while (i < masCnt)
    {
        if (mas[i].isDel)
        {
            masCnt--;
            mas[i] = mas[masCnt];
            mas = realloc(mas, sizeof(*mas) * masCnt); //
        }
        else
            i++;
    }
}

//inicialization polojeniya kvadratov
void WinMove()
{
    PlayerControl();
    ObjectMove(&player);

    for (int i = 0; i < masCnt; i++)
    {
        ObjectMove(mas + i);

    }
    DelObjects();
    if (flagNextGame)
    {
        level++;
        globalCount++;
        printf("%d", globalCount);
        flagNextGame = FALSE;
        WinInit();
    }
}

void WinShow(HDC dc) // poluchaem na vhod contex ustroistva
{
    HDC memDC = CreateCompatibleDC(dc);
    HBITMAP memBM = CreateCompatibleBitmap(dc, rct.right - rct.left, rct.bottom - rct.top);
    SelectObject(memDC, memBM);

    SelectObject(memDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDC, RGB(255, 255, 255));
    Rectangle(memDC, 0,0,640,480);

    SelectObject(memDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDC, RGB(255, 0, 255));
    itoa(globalCount, strGlobalCount, 10);
    TextOutA(memDC, 0, 0, "Your score", 11);
    TextOutA(memDC, 80, 0, strGlobalCount, 3);

    ObjectShow(player, memDC);

    for (int i = 0; i < masCnt; i++)
        ObjectShow(mas[i], memDC);


    BitBlt(dc, 0,0, rct.right - rct.left, rct.bottom - rct.top, memDC, 0,0, SRCCOPY); // copy from memDC to dc
    DeleteDC(memDC);
    DeleteObject(memBM);
}

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
        PostQuitMessage(0);

    else if (message == WM_KEYDOWN)
        printf("code = %d\n", wparam);

    else if (message == WM_CHAR)
        printf("%c\n", wparam);

    else if (message == WM_SIZE)
        GetClientRect(hwnd, &rct);

    else if(LOWORD(wparam) == btE_id)
    {
        ShowWindow(bt_send, SW_HIDE);
        ShowWindow(bt_quit, SW_HIDE);
        ShowWindow(edt, SW_HIDE);
        flagGame = TRUE;
        WinInit();
    }
    else if (message == WM_COMMAND)
    {
        if (bt_quit == lparam)
            PostQuitMessage(0);

        else if (LOWORD(wparam) == edt1_id)
        {
            GetWindowText(lparam, nameStr, 100);
        }
    }
    else if (message == WM_MOUSEMOVE)
    {
        int xPos = LOWORD(lparam);
        int yPos = HIWORD(lparam);
        printf("mouse [%d, %d]\n", xPos, yPos);
    }

    else if (message == WM_LBUTTONDOWN)
        printf("mouse left button down\n");

    else return DefWindowProcA(hwnd, message, wparam, lparam);
}
int main()
{
    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "ura";
    wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);


    hwnd = CreateWindow("game", "pobeda",
                        WS_OVERLAPPEDWINDOW, 10, 10, 480, 480, NULL, NULL, NULL, NULL);
    HDC dc = GetDC(hwnd);
    ShowWindow(hwnd, SW_SHOWNORMAL);

    bt_quit = CreateWindow("button", "QUIT",
                           WS_VISIBLE | WS_CHILD,
                           180,370, 100,50,
                           hwnd, NULL, NULL, NULL);

    bt_send = CreateWindow("button", "ENTER",
                           WS_VISIBLE | WS_CHILD,
                           180,300, 100,50,
                           hwnd, btE_id, NULL, NULL);

    edt = CreateWindow("edit", "",
                       WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                       20,80, 160,20,
                       hwnd, edt1_id, NULL, NULL);

    cap1 = CreateWindow("static", "Enter your name and last name right here",
                        WS_VISIBLE | WS_CHILD,
                        200,80, 110,50,
                        hwnd, NULL, NULL, NULL);


//  cap2 = CreateWindow("static", "Choose your group right here",
//                  WS_VISIBLE | WS_CHILD,
//                      200,150, 120,35,
//                      hwnd, NULL, NULL, NULL);

    cap3 = CreateWindow("static", "Performed by a student of the M30-106C-22 group \nVictor Parfeniuk",
                        WS_VISIBLE | WS_CHILD,
                        0,360, 120,85,
                        hwnd, NULL, NULL, NULL);
    cap4 = CreateWindow("static", "'W' 'S' 'A' 'D' \n for moving",
                        WS_VISIBLE | WS_CHILD,
                        175,250, 110,40,
                        hwnd, NULL, NULL, NULL);
    f = fopen("test1.txt", "r");

    strcpy(raitingStr,"");

    count_str = 0;
    while (fgets(lineRaiting, 1000, f)) {
        strcat(raitingStr, lineRaiting);
        count_str++;
        if (count_str == 5)
        {
            fclose(f);
            break;

        }

    }


    cap5 = CreateWindow("static", raitingStr,
                        WS_VISIBLE | WS_CHILD,
                        290,290, 170,160,
                        hwnd, NULL, NULL, NULL);


//    CB = CreateWindow("combobox", "Choose your group",
//                        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
//                        20,150, 160, 150,
//                        hwnd, cb1_id, NULL, NULL);
//
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-101-C 22" );
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-102-C 22" );
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-103-C 22" );
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-104-C 22" );
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-105-C 22" );
//        SendMessage(CB, CB_ADDSTRING, 0, "M30-106-C 22" );

    MSG msg;

    while(1)
    {
        if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (flagGame)
            {

                WinMove();
                WinShow(dc);
                Sleep(5);
            }
            else
            {
                if (flagCreate)
                {
                    flagCreate = FALSE;


                    level = 0;
                    globalCount = 0;

                    strcpy(old_str,"");
                    strcpy(new_str,"");


                    SelectObject(dc, GetStockObject(DC_BRUSH));
                    SetDCBrushColor(dc, RGB(255, 255, 255)); // заливка квадрата белым цветом
                    Rectangle(dc, 0, 0, 640, 480);
                    for (int i = 0; i < masCnt; i++)
                    {
                        mas[i].isDel = TRUE;

                    }
                    // DelObjects();

                    ShowWindow(bt_quit, SW_SHOWNORMAL);

                    ShowWindow(bt_send, SW_SHOWNORMAL);

                    ShowWindow(edt, SW_SHOWNORMAL);

                    Sleep(100);
                    f = fopen("test1.txt", "r");


                    strcpy(raitingStr,"");

                    count_str = 0;
                    while (fgets(lineRaiting, 10000, f)) {
                        strcat(raitingStr, lineRaiting);
                        count_str++;
                        if (count_str == 5)
                        {
                            fclose(f);
                            break;

                        }

                    }

                    cap5 = CreateWindow("static", raitingStr,
                                        WS_VISIBLE | WS_CHILD,
                                        290,290, 170,160,
                                        hwnd, NULL, NULL, NULL);
                    cap3 = CreateWindow("static", "Performed by a student of the M30-106C-22 group \nVictor Parfeniuk",
                                        WS_VISIBLE | WS_CHILD,
                                        0,360, 120,85,
                                        hwnd, NULL, NULL, NULL);

                    cap4 = CreateWindow("static", "'W' 'S' 'A' 'D' \n for moving",
                                        WS_VISIBLE | WS_CHILD,
                                        175,250, 110,40,
                                        hwnd, NULL, NULL, NULL);


                }
            }


        }
    }

    return 0;
}
