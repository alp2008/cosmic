#include "TXLib.h"

    int xSpaceman2 = 100;
    int ySpaceman2 = 100;
    int vxSpaceman = 10;
    int xFon = -1800;
    int yFon = -1200;

int main()
    {
txCreateWindow (800, 600)
txBitBlt (txDC(), xFon, yFon,3600,2400,Fon);

txTransparentBlt (txDC(), xSpaceman2, ySpaceman2,147,150,Spaceman2,TX_BLACK);
xSpaceman2 = xSpaceman2 +vxSpaceman2;

    if(xSpaceman2 > 800 - 147 || xSpaceman2 < 0)
    {
        vxSpaceman2 = - vxSpaceman2;
    }


    txEnd;

    txTextCursor (false);
    return 0;
    }