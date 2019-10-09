// Ali Alherz
// 
//
// 
//
//
/* the debugging steps:
 * 1. recognize that a bug exists.
 * 2. isolate the bad code.
 * 3. fix bad codes.
 * 4. test the source code.
 */


#include "fonts.h"


void showCredit() {
    Rect n;

    n.bot = 400;
    n.left = 280;
    n.center = 0;
    ggprint8b(&n, 16, 0x00ffffff, "Ali Alherz");
}
 

void phpInfo()
{
        char hostname[255] = "odin.cs.csub.edu";
        char pagename[255] = "/~aalherz/3350/lab3/lab3.php";
}
