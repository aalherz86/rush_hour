// Ali Alherz
//
#include "fonts.h"


void showCredit() {
    Rect n;

    n.bot = 400;
    n.left = 280;
    n.center = 0;
    ggprint8b(&n, 16, 0x00ffffff, "Ali Alherz");
}
