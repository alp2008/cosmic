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
    bool visible;
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
    {bool visible;
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



    HDC menu = txLoadImage("Pictures/fon1.bmp");
    HDC Fon = txLoadImage ("pictures/fon.bmp");
    HDC Fon2 = txLoadImage ("pictures/fon2.bmp");
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

    Bullet bul = {0, 0, true, 0, 20};

    Barrier barr{900,400,150,150, true,astr};

    Barrier ber[4];
    ber[0] = {800,0,80,248,true,stolb2};
    ber[1] = {600,378,80,248,true,stolb1};
    ber[2] = {400,0,80,248,true,stolb2};
    ber[3] = {200,378,80,248,true,stolb1};

    int level = 1;

    string PAGE = "Menu";

    Barrier bar[8];
    bar[0] = {50, 200, 52, 44, true, astr1};
    bar[1] = {150, 50, 52, 44, true, astr2};
    bar[2] = {250, 50, 52, 44, true, astr3};
    bar[3] = {350, 400, 52, 44, true, astr4};
    bar[4] = {500, 50, 52, 44, true, astr1};
    bar[5] = {550, 150, 52, 44, true, astr2};
    bar[6] = {790, 400, 52, 44, true, astr3};
    bar[7] = {750, 200, 52, 44, true, astr4};

    Button btn_start = {400, 150, 200, 50, "ÑÒÀÐÒ"};
    Button btn_about = {400, 250, 200, 50, "ÎÁ ÈÃÐÅ"};
    Button btn_exit =  {400, 350, 200, 50, "ÂÛÕÎÄ"};


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
            txBitBlt(txDC(), 0, 0, 1000, 625, menu);
            btn_start.draw();

            if(btn_start.mouse_over())
            {
                btn_start.change();
            }
            if(btn_start.mouse_click())
            {
                PAGE = "Game";
            }
            btn_about.draw();
            if(btn_about.mouse_over())
            {
                btn_about.change();
            }
            if(btn_about.mouse_click())
            {
                PAGE = "About";
            }
            btn_exit.draw();
            if(btn_exit.mouse_over())
            {
                btn_exit.change();
            }
            if(btn_exit.mouse_click())
            {
                txDisableAutoPause();
                return 0;ber[0].visible=false;
            }
        }

        if(PAGE == "Game")
        {
            txTransparentBlt (txDC(),xFon, yFon, 1000, 625, Fon);
            xspaceman = spaceman.x;
            yspaceman = spaceman.y;

            txTransparentBlt (txDC(), spaceman.x, spaceman.y,107,50,spaceman.image,0, 0,TX_BLACK);
            if(GetAsyncKeyState('W'))
            {
                spaceman.y -= 10;
            }
            if(GetAsyncKeyState('S'))
            {
                spaceman.y += 10;
            }
            if(GetAsyncKeyState ('D'))
            {
                spaceman.image = spaceman.image_right;
                spaceman.x += 10;
            }
            if(GetAsyncKeyState ('A'))
            {
                spaceman.image = spaceman.image_left;
                spaceman.x -= 10;
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
                }
            }

                if(spaceman.x+spaceman.w > barr.x && spaceman.x < barr.x+barr.w &&
                   spaceman.y+spaceman.h > barr.y && spaceman.y <barr.y+barr.h)
                {
                    spaceman.x = xspaceman;
                    spaceman.y = yspaceman;
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

             if((txGetPixel(spaceman.x, spaceman.y+spaceman.h) == RGB(255, 0, 0)) && (level == 1))
            {
                Fon = txLoadImage("Pictures/fon.bmp");
                spaceman.x = 100;
                spaceman.y = 200;
                for(int i=0; i<8; i++)
                {
                bar[0].x=100;
                bar[1].x=200;
                bar[2].x=300;
                bar[3].x=400;
                bar[4].x=500;
                bar[5].x=600;
                bar[6].x=750;
                bar[7].x=800;
                bar[i].visible=true;
                }
                level = 2;
            }

            for(int i=0; i<8; i++)
            {
                if(bar[0].visible
                or bar[1].visible
                or bar[2].visible
                or bar[3].visible
                or bar[4].visible
                or bar[5].visible
                or bar[6].visible
                or bar[7].visible)
                {
                    barr.x = 900;
                }
                else
                {
                    barr.x = 1500;
                }
            }

            char str[100];
            sprintf(str, "Óðîâåíü -  %d", level);
            txSetColor(TX_YELLOW);
            txDrawText(300, 5, 500, 50, str);

            if((txGetPixel(spaceman.x, spaceman.y+spaceman.h) == RGB(255, 0, 0)) && (level == 2))
            {
                Fon = txLoadImage("Pictures/fon.bmp");
                spaceman.x = 100;
                spaceman.y = 200;
                for(int i=0; i<8; i++)
                {
                bar[0].x=150;
                bar[1].x=250;
                bar[2].x=320;
                bar[3].x=440;
                bar[4].x=580;
                bar[5].x=690;
                bar[6].x=750;
                bar[7].x=890;
                bar[i].visible=true;
                }
                level = 3;
            }

            if((txGetPixel(spaceman.x, spaceman.y+spaceman.h) == RGB(255, 0, 0)) && (level == 3))
            {
                Fon = txLoadImage("Pictures/fin.bmp");
                spaceman.visible=false;
                spaceman.x=1000000000;
                for(int i=0; i<3; i++)
                {
                    ber[0].visible=false;
                    ber[1].visible=false;
                    ber[2].visible=false;
                    ber[3].visible=false;
                }
            }
        }

        if(PAGE == "About")
        {
                txTransparentBlt (txDC(),0, 0, 1000, 625, Fon2);
        }

            txEnd;
            txSleep(10);
        }

txTextCursor (false);
return 0;

}
