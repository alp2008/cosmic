#include "TXLib.h"
struct Fly
{
    int x;
    int y;
    int w;
    int h;
    bool visible;
    HDC image_right;
    HDC image_left;
    HDC image;
};

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

struct Button
{
int x;
int y;
int w;
int h;
const char* text;

void draw()
{
    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);
    txRectangle(x+3, y+3, x+w+3, y+h+3);
    txSetFillColor (TX_WHITE);
    txRectangle(x, y, x+w, y+h);
    txDrawText(x, y, x+w, y+h, text);
}
void change()
{
    txSetColor (TX_WHITE);
    txSetFillColor (TX_BLACK);
    txRectangle(x, y, x+x, y+h);
    txDrawText(x, y, x+w, y+h, text);
}

bool mouse_over()
{
    if (txMouseX()>x && txMouseX() && txMouseY()>y && txMouseY()<y+h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool mouse_click()
{
    if(txMouseButtons() == 1 &&
       txMouseX() > x &&
       txMouseX() < x+w &&
       txMouseY() > y &&
       txMouseY() < y+h)
    {
    return true;
    }
    else
    {
    return false;
    }
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

    Fly fly =  {20,10,102,44,false,txLoadImage ("pictures/bulletright.bmp"),txLoadImage ("pictures/bulletleft.bmp"), fly.image_left};
    int xfly;
    int yfly;

    Bullet bul = {0, 0, true, 0, 20};

    Barrier barr{900,400,150,150, true, txLoadImage ("pictures/astra.bmp")};

    Barrier ber[4];
    ber[0] = {800,0,80,248,true,txLoadImage ("pictures/stbd.bmp")};
    ber[1] = {600,378,80,248,true,txLoadImage ("pictures/stb.bmp")};
    ber[2] = {400,0,80,248,true,txLoadImage ("pictures/stbd.bmp")};
    ber[3] = {200,378,80,248,true,txLoadImage ("pictures/stb.bmp")};
    string PAGE = "Menu";

    //int count_bar = 8;
    /*Barrier bar[count_bar];
    bar[0] = {50, 50, 52, 44, false, txLoadImage ("pictures/astr3.bmp")};
    for(int i=1; i<=count_bar; i++)
    {
        bar[i] = {bar[i-1].x+100, 50, 52, 44, true, txLoadImage ("pictures/astr3.bmp")};
    }*/
    Barrier bar[8];
    bar[0] = {50, 200, 52, 44, true, txLoadImage ("pictures/astr1.bmp")};
    bar[1] = {150, 50, 52, 44, true, txLoadImage ("pictures/astr2.bmp")};
    bar[2] = {250, 50, 52, 44, true, txLoadImage ("pictures/astr3.bmp")};
    bar[3] = {350, 400, 52, 44, true, txLoadImage ("pictures/astr4.bmp")};
    bar[4] = {500, 50, 52, 44, true, txLoadImage ("pictures/astr1.bmp")};
    bar[5] = {550, 150, 52, 44, true, txLoadImage ("pictures/astr2.bmp")};
    bar[6] = {700, 400, 52, 44, true, txLoadImage ("pictures/astr3.bmp")};
    bar[7] = {750, 200, 52, 44, true, txLoadImage ("pictures/astr4.bmp")};


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();
        txBegin();
        if(PAGE == "Menu")
        {
            txSetColor(TX_BLACK);
            txSetFillColor(TX_BLACK);
            txRectangle(53, 53, 203,103);
            txSetFillColor(TX_WHITE);
            txRectangle(50, 50, 200,100);
            txDrawText(50, 50, 200, 100, "CTAPT");
        }
        txBitBlt (txDC(), xFon, yFon,1000,625,Fon);

        xspaceman = spaceman.x;
        yspaceman = spaceman.y;

        txTransparentBlt (txDC(), fly.x, fly.y,20,10,fly.image,0, 0,TX_BLACK);
        if(!GetAsyncKeyState (VK_RIGHT) and !GetAsyncKeyState (VK_LEFT))
        {
            fly.visible = false;
        }
        yfly = fly.y;
        xfly = fly.x;
        fly.x = spaceman.x+107;
        fly.y = spaceman.y+20;

        txTransparentBlt (txDC(), spaceman.x, spaceman.y,107,50,spaceman.image,0, 0,TX_BLACK);
        if(GetAsyncKeyState(VK_UP))
        {
            spaceman.y -= 10;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            spaceman.y += 10;bul.x = spaceman.x+95;
            bul.y = spaceman.y+35;
        }
        if(GetAsyncKeyState (VK_RIGHT))
        {
            spaceman.image = spaceman.image_right;
            fly.x = spaceman.x-10;
            fly.image = fly.image_right;
            spaceman.x += 10;
            fly.visible = true;
            bul.x = spaceman.x+95;
            bul.y = spaceman.y+35;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            spaceman.image = spaceman.image_left;
            fly.image = fly.image_left;
            spaceman.x -= 10;
            fly.visible = true;
            bul.x = spaceman.x+10;
            bul.y = spaceman.y+35;
        }

        txTransparentBlt (txDC(), barr.x, barr.y,150, 150 ,barr.image, 0, 0,TX_BLACK);

             for(int i=0; i<4; i++)
        {
            if (ber[i].visible)
                txTransparentBlt(txDC(), ber[i].x, ber[i].y, 80 ,248, ber[i].image, 0, 0, TX_BLACK);

            if(spaceman.x+spaceman.w > ber[i].x && spaceman.x < ber[i].x+ber[i].w &&
               spaceman.y+spaceman.h > ber[i].y && spaceman.y <ber[i].y+ber[i].h)
            {
                spaceman.x = xspaceman;
                spaceman.y = yspaceman;
                fly.y = yfly;
                fly.x = xfly;
            }
        }

            if(spaceman.x+spaceman.w > barr.x && spaceman.x < barr.x+barr.w &&
               spaceman.y+spaceman.h > barr.y && spaceman.y <barr.y+barr.h)
            {
                spaceman.x = xspaceman;
                spaceman.y = yspaceman;
                fly.y = yfly;
                fly.x = xfly;
            }



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
            bul.x = spaceman.x+95;
            bul.y = spaceman.y+35;
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
