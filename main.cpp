#include "TXLib.h"
    int xSpaceman = 200;
    int ySpaceman = 196;
    int xSpaceman2 = 100;
    int ySpaceman2 = 100;
    int vxSpaceman = 10;
    int vxSpaceman2 = 10;
    int xFon = 0;
    int yFon = 0;

int main()
{

txCreateWindow (800, 600);

HDC  Fon = txLoadImage ("pictures/fon.bmp");
HDC  Spaceman = txLoadImage ("pictures/kosmleft.bmp");
HDC  Spaceman3 = txLoadImage ("pictures/kosmright.bmp");
HDC  Spaceman2 = txLoadImage ("pictures/kosm2right.bmp");
HDC  Spaceman4 = txLoadImage ("pictures/kosm2left.bmp");
HDC  Spaceman5 = txLoadImage ("pictures/kosmleft1.bmp");

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();

        txBegin();
        txBitBlt (txDC(), xFon, yFon,800,600,Fon);


        if(GetAsyncKeyState('W'))
        {
            yFon -= 10;
        }
        if(GetAsyncKeyState('S'))
        {
            yFon += 10;
        }
        if(GetAsyncKeyState('A'))
        {
            xFon -= 10;
        }
        if(GetAsyncKeyState('D'))
        {
            xFon += 10;
        }

        txTransparentBlt (txDC(), xSpaceman, ySpaceman,200,196,Spaceman,TX_BLACK);
        if(GetAsyncKeyState(VK_UP))
        {
            ySpaceman -= 10;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            ySpaceman += 10;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            xSpaceman += 10;
            Spaceman=Spaceman3;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            xSpaceman -= 10;
            Spaceman=Spaceman5;
        }


        txTransparentBlt (txDC(), xSpaceman2, ySpaceman2,200,196,Spaceman2, 0,0, TX_BLACK);
        xSpaceman2 = xSpaceman2 +vxSpaceman2;

        if(xSpaceman2 > 800 - 147 || xSpaceman2 < 0)
        {
            vxSpaceman2 = - vxSpaceman2;
        }


        txEnd;
        txSleep(10);

    }

    txDeleteDC (Fon);
    txDeleteDC (Spaceman);
    txDeleteDC (Spaceman2);
    txDeleteDC (Spaceman3);
    txDeleteDC (Spaceman4);
    txDeleteDC (Spaceman5);

txTextCursor (false);
return 0;
}
