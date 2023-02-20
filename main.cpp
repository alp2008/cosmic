#include "TXLib.h"

struct Spaceman
{
    int x;
    int y;
    HDC image_right;
    HDC image_left;
    HDC image;

};
struct Barrier
{
    int x;
    int y;
    int w;
    int h;
    COLORREF color;
    bool visible;

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

    Spaceman spaceman = {200,196,txLoadImage ("pictures/spacemanr.bmp"),txLoadImage ("pictures/spacemanl.bmp"), spaceman.image_left};

    Bullet bul = {0, 0, true, 0, 15};

    Barrier bar[8];
    bar[0] = {50, 50, 50, 50, TX_WHITE, true};
    bar[1] = {150, 50, 50, 50, TX_GREEN, true};
    bar[2] = {250, 50, 50, 50, TX_WHITE, true};
    bar[3] = {350, 50, 50, 50, TX_GREEN, true};
    bar[4] = {450, 50, 50, 50, TX_WHITE, true};
    bar[5] = {550, 50, 50, 50, TX_GREEN, true};
    bar[6] = {650, 50, 50, 50, TX_WHITE, true};
    bar[7] = {750, 50, 50, 50, TX_GREEN, true};

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();

        txBegin();
        txBitBlt (txDC(), xFon, yFon,1000,625,Fon);

        txTransparentBlt (txDC(), spaceman.x, spaceman.y,136,69,spaceman.image,0, 0,TX_BLACK);
        if(GetAsyncKeyState(VK_UP))
        {
            spaceman.y -= 15;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            spaceman.y += 15;
        }
        if(GetAsyncKeyState (VK_RIGHT))
        {
            spaceman.image = spaceman.image_right;
            spaceman.x += 15;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            spaceman.image = spaceman.image_left;
            spaceman.x -= 15;
        }
            int x1=400;
            int x2=700;
            int y2=625;
            int u1=300;

         for(int i=0; i<8; i++)
        {
            if (bar[i].visible)    bar[i].draw();
        }

        if(bul.visible)
        {
            bul.draw();
            bul.y -= bul.vy;
        }


        for(int i=0; i<8; i++)
        {
            if( bul.x >  bar[i].x &&
                bul.x <  bar[i].x + bar[i].w &&
                bul.y >  bar[i].y &&
                bul.y <  bar[i].y + bar[i].h)
            {
                bar[i].visible = false;
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
