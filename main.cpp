#include "TXLib.h"

struct Spaceman
{
    int x;
    int y;
    HDC image;
    HDC image_left;
    HDC image_right;
};


struct Barrier
{
    int x;
    int y;
    int w;
    int h;
    bool visible;
    COLORREF color;
    void draw()
    {
        txSetColor(color);
        txSetFillColor(color);
        txRectangle(x, y, x+w, y+h);
    }
};
struct Bullet
{
    int x;
    int y;
    bool visible;
    int vx;
    int vy;
    void draw()
    {
       txSetColor (TX_WHITE);
       txSetFillColor (TX_BLACK);
       txCircle(x, y, 5);
    }
};

int main()
{

txCreateWindow (1000, 625);


    HDC  Fon = txLoadImage ("pictures/fon.bmp");
    int xFon = 0;
    int yFon = 0;

    Spaceman spaceman = {200,196,txLoadImage ("pictures/spacemanright.bmp"), txLoadImage ("pictures/spacemanleft.bmp"),txLoadImage ("pictures/spacemanright.bmp")};

    Bullet bul = {0, 0, true, 0, 10};

    Barrier bar[4];
    bar[1] = {500,0,50,50, true, TX_GREEN};
    bar[2] = {600,0,50,50, false, TX_WHITE};
    bar[3] = {700,0,50,50, true, TX_GREEN};
    bar[4] = {800,0,50,50, true, TX_WHITE};

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();

        txBegin();
        txBitBlt (txDC(), xFon, yFon,1000,625,Fon);

        txTransparentBlt (txDC(), spaceman.x, spaceman.y,136,69,spaceman.image_left,TX_BLACK);
        if(GetAsyncKeyState(VK_UP))
        {
            spaceman.y -= 10;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            spaceman.y += 10;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            spaceman.x += 10;
            spaceman.image = spaceman.image_right;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            spaceman.x -= 10;
            spaceman.image = spaceman.image_left;
        }
            int x1=400;
            int x2=700;
            int y2=625;
            int u1=300;

        for(int i=0; i<8; i++)
        {
            if (bar[i].visible)  bar[i].draw();
        }

        if(bul.visible)
            {
                bul.draw();
                bul.y -= bul.vy;
            }


        for(int i=0; i < 4; i++)
        {
            if( bul.x > bar[i].x &&
                bul.x < bar[i].x + bar[i].w &&
                bul.y > bar[i].y &&
                bul.y < bar[i].y + bar[i].h)
            {
                bar[1].visible = false;
            }
        }

        if(GetAsyncKeyState (VK_CONTROL))
            {
                bul.x = spaceman.x+108;
                bul.y = spaceman.y+44;
                bul.visible = true;
            }

        txEnd;
        txSleep(10);

    }

    txDeleteDC (Fon);

txTextCursor (false);
return 0;
}
