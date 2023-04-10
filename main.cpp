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
        txRectangle(x, y, x+w, y+h);
        txDrawText(x, y, x+w, y+h, text);
    }

    bool mouse_over()
    {
        if(txMouseX()>x && txMouseX()<x+w && txMouseY()>y && txMouseY()<y+h)
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
        if( txMouseButtons() == 1  &&
            txMouseX() > x && txMouseX() < x+w &&
            txMouseY() > y && txMouseY() < y+h)
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



    HDC menu = txLoadImage("Pictures/fon.bmp");
    HDC Fon = txLoadImage ("pictures/fon.bmp");
    HDC spacemanr = txLoadImage("pictures/spacemanr.bmp");
    HDC spacemanl= txLoadImage("pictures/spacemanl.bmp");
    HDC bulletr = txLoadImage("pictures/bulletright.bmp");
    HDC bulletl = txLoadImage("pictures/bulletleft.bmp");
    HDC astr = txLoadImage("pictures/astra.bmp");
    HDC astr1 = txLoadImage("pictures/astr1.bmp");
    HDC astr2 = txLoadImage("pictures/astr2.bmp");
    HDC astr3 = txLoadImage("pictures/astr3.bmp");
    HDC astr4 = txLoadImage("pictures/astr4.bmp");
    HDC stolb1 = txLoadImage("pictures/stb.bmp");
    HDC stolb2 = txLoadImage("pictures/stbd.bmp");

    int xmenu = 0;
    int ymenu = 0;
    int xFon = 0;
    int yFon = 0;

    Spaceman spaceman = {107,50,102,44,spacemanr,spacemanl, spaceman.image_left};
    int xspaceman;
    int yspaceman;

    Fly fly =  {20,10,102,44,false,bulletr,bulletl, fly.image_left};
    int xfly;
    int yfly;

    Bullet bul = {0, 0, true, 0, 20};

    Barrier barr{900,400,150,150, true,astr};

    Barrier ber[4];
    ber[0] = {800,0,80,248,true,stolb2};
    ber[1] = {600,378,80,248,true,stolb1};
    ber[2] = {400,0,80,248,true,stolb2};
    ber[3] = {200,378,80,248,true,stolb1};

    int level = 1;

    string PAGE = "Game";

    Barrier bar[8];
    bar[0] = {50, 200, 52, 44, true, astr1};
    bar[1] = {150, 50, 52, 44, true, astr2};
    bar[2] = {250, 50, 52, 44, true, astr3};
    bar[3] = {350, 400, 52, 44, true, astr4};
    bar[4] = {500, 50, 52, 44, true, astr1};
    bar[5] = {550, 150, 52, 44, true, astr2};
    bar[6] = {700, 400, 52, 44, true, astr3};
    bar[7] = {750, 200, 52, 44, true, astr4};

    Button btn_start = {300,  50, 200, 50, "ÑÒÀÐÒ"};
    Button btn_about = {300, 150, 200, 50, "ÎÁ ÈÃÐÅ"};
    Button btn_exit =  {300, 250, 200, 50, "ÂÛÕÎÄ"};


    while(true)
    {
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txClear();
        txBegin();
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            PAGE = "Menu";
        }
        if(PAGE == "Menu")
        {
            txBitBlt(txDC(), 0, 0, 800, 600, menu);
            //Êíîïêà ÑÒÀÐÒ
            btn_start.draw();
            if(btn_start.mouse_over())
            {
                btn_start.change();
            }
            if(btn_start.mouse_click())
            {
                PAGE = "Game";
            }
            //Êíîïêà ÎÁ ÈÃÐÅ
            btn_about.draw();
            if(btn_about.mouse_over())
            {
                btn_about.change();
            }
            if(btn_about.mouse_click())
            {
                PAGE = "";
            }
            //Êíîïêà ÂÛÕÎÄ
            btn_exit.draw();
            if(btn_exit.mouse_over())
            {
                btn_exit.change();
            }
            if(btn_exit.mouse_click())
            {
                txDisableAutoPause();
                return 0;
            }
        }

        if(PAGE == "Game")
        {
            txTransparentBlt (txDC(),xFon, yFon, 800, 600, Fon);
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
    }

    txDeleteDC (Fon);
    txDeleteDC (menu);
    txDeleteDC (spacemanr);
    txDeleteDC (spacemanl);
    txDeleteDC (bulletr);
    txDeleteDC (bulletl);
    txDeleteDC (astr1);
    txDeleteDC (astr2);
    txDeleteDC (astr3);
    txDeleteDC (astr4);
    txDeleteDC (astr);
    txDeleteDC (stolb1);
    txDeleteDC (stolb2);

txTextCursor (false);
return 0;
}
