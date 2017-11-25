/* #define CRED 1 */
/* #define CGREEN 2 */
/* #define CYELLOW 3 */
/* #define CBLUE 4 */
/* #define CMAGENTA 5 */
/* #define CCYAN 6 */

/* typedef int Color; */

#include "color.h"
#include <stdio.h>
#include "color.h"
#include "../pcolor/pcolor.h"

void PrintInColor(char c, Color Warna) {
  if      (Warna == CRED)     { print_red(c);     }
  else if (Warna == CGREEN)   { print_green(c);   }
  else if (Warna == CYELLOW)  { print_yellow(c);  }
  else if (Warna == CBLUE)    { print_blue(c);    }
  else if (Warna == CMAGENTA) { print_magenta(c); }
  else if (Warna == CCYAN)    { print_cyan(c);    }
  else                        { printf("%c", c);  }
}
