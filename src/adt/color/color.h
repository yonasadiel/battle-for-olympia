#ifndef COLOR_H
#define COLOR_H

#define CRED 1
#define CGREEN 2
#define CYELLOW 3
#define CBLUE 4
#define CMAGENTA 5
#define CCYAN 6

typedef int Color;

void PrintInColor(char c, Color Warna);
/**
 * I.S. c adalah karakter untuk diprint
 * F.S. c tmapil di layar sesuai Warna
 */

#endif