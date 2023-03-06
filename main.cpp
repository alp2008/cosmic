#include "TXLib.h"
struct Spaceman
{
    int x;
    int y;
    int w;
    int h;
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
    bool visible;
    HDC image;
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

    Spaceman spaceman = {107,50,102,44,txLoadImage ("pictures/spacemanr.bmp"),txLoadImage ("pictures/spacemanl.bmp"), spaceman.image_left};
    int xspaceman;
    int yspaceman;

    Bullet bul = {0, 0, true, 0, 15};

    Barrier barr{500,200,300,300, true, txLoadImage ("pictures/astra.bmp")};

    Barrier ber[2];
    ber[0] = {0,100,151,470,true,txLoadImage ("pictures/stbd.bmp")};
    ber[1] = {100,625,151,470,true,txLoadImage ("pictures/stb.bmp")};

    Barrier bar[8];
    bar[0] = {50, 50, 52, 44, true, txLoadImage ("pictures/astr1.bmp")};
    bar[1] = {150, 50, 52, 44, true, txLoadImage ("pictures/astr2.bmp")};
    bar[2] = {250, 50, 52, 44, true, txLoadImage ("pictures/astr3.bmp")};
    bar[3] = {350, 50, 52, 44, true, txLoadImage ("pictures/astr4.bmp")};
    bar[4] = {450, 50, 52, 44, true, txLoadImage ("pictures/astr1.bmp")};
    bar[5] = {550, 50, 52, 44, true, txLoadImage ("pictures/astr2.bmp")};
    bar[6] = {650, 50, 52, 44, true, txLoadImage ("pictures/astr3.bmp")};
    bar[7] = {750, 50, 52, 44, true, txLoadImage ("pictures/astr4.bmp")};

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();

        txBegin();
        txBitBlt (txDC(), xFon, yFon,1000,625,Fon);

        xspaceman = spaceman.x;
        yspaceman = spaceman.y;

        txTransparentBlt (txDC(), spaceman.x, spaceman.y,107,50,spaceman.image,0, 0,TX_BLACK);
        if(GetAsyncKeyState(VK_UP))
        {
            spaceman.y -= 10;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            spaceman.y += 10;
        }
        if(GetAsyncKeyState (VK_RIGHT))
        {
            spaceman.image = spaceman.image_right;
            spaceman.x += 10;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            spaceman.image = spaceman.image_left;
            spaceman.x -= 10;
        }

            txTransparentBlt (txDC(), barr.x, barr.y,300, 300 ,barr.image, 0, 0,TX_BLACK);

            if(spaceman.x+spaceman.w > barr.x && spaceman.x < barr.x+barr.w &&
               spaceman.y+spaceman.h > barr.y && spaceman.y <barr.y+barr.h)
            {
                spaceman.x = xspaceman;
                spaceman.y = yspaceman;
            }

            int x1=400;
            int x2=700;
            int y2=625;
            int u1=300;


         for(int i=0; i<8; i++)
        {
            if (bar[i].visible)
                txTransparentBlt(txDC(), bar[i].x, bar[i].y, 52,44, bar[i].image, 0, 0, TX_BLACK);
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
    txDeleteDC (spaceman.image);
    txDeleteDC (spaceman.image_right);
    txDeleteDC (spaceman.image_left);

txTextCursor (false);
return 0;
}
