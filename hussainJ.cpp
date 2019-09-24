// Hussain Jafri

#include "fonts.h"

void displayName() {
    Rect n;
    n.bot = 380;
    n.left = 280;
    n.center = 0;
    ggprint8b(&n, 16, 0x00fffff, "Hussain Jafri");
}
