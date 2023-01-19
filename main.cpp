#include "TXLib.h"
    int xSpaceman = 200;
    int ySpaceman = 196;
    int xSpaceman2 = 100;
    int ySpaceman2 = 100;
    int vxSpaceman = 10;
    int xFon = -1800;
    int yFon = -1200;

int main()
{
HDC  Fon = txLoadImage ("fon.bmp");
HDC  Spaceman = txLoadImage ("kosm.bmp");
HDC  Spaceman2 = txLoadImage ("kosm2.bmp");
    {
txCreateWindow (800, 600)
txBitBlt (txDC(), xFon, yFon,3600,2400,Fon);

if(GetAsyncKeyState('w'))
{
    yFon -= 10;
}
if(GetAsyncKeyState('s'))
{
    yFon += 10;
}
if(GetAsyncKeyState('a'))
{
    xFon -= 10;
}
if(GetAsyncKeyState('d'))
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
    ySpaceman += 10;
}
if(GetAsyncKeyState(VK_LEFT))
{
    ySpaceman -= 10;
}


txTransparentBlt (txDC(), xSpaceman2, ySpaceman2,200,196,Spaceman2, 0,0, TX_BLACK);
xSpaceman2 = xSpaceman2 +vxSpaceman2;

    if(xSpaceman2 > 800 - 147 || xSpaceman2 < 0)
    {
        vxSpaceman2 = - vxSpaceman2;
    }


    txEnd;
    {
    {
    while(  GetAsyncKeyState (VK_ESCAPE))
        txSetFillColor(TX_BLACK);
        txSetColor(TX_WHITE);
        txClear();

        txBitBlt(txDC(),0,0,800,600,Fon);
        txTransparentBlt (txDC(), xspaceman,yspaceman, 200,196, spaceman 0,0, TX_BLACK)
    }
    txDeleteDC (Fon);

    txTextCursor (false);
    return 0;
    }

