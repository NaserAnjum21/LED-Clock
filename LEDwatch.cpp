# include "iGraphics.h"
#include <stdio.h>
#include <time.h>

void gettime(int t[])
{
    time_t ctime;
    struct tm * current;
    time ( &ctime );
    current = localtime ( &ctime );
    t[0] = current->tm_hour;
    t[1] = current->tm_min;
    t[2] = current->tm_sec;
}


int i, j, k, a, p = 68, z, tim = 1;
int digit[6];
int t[3] = {};
bool pin[6][7] = {{true}}; //array to switch the segments on or off


// 3d array, digits->segments->coordinates
double xa[6][7][6] = {{{50, 48, 48, 50, 52, 52},
        {52, 54, 114, 116, 114, 54},
        {50 + p, 48 + p, 48 + p, 50 + p, 52 + p, 52 + p},
        {52, 54, 114, 116, 114, 54},
        {50, 48, 48, 50, 52, 52},
        {52, 54, 114, 116, 114, 54},
        {50 + p, 48 + p, 48 + p, 50 + p, 52 + p, 52 + p}
    }
};

double ya[6][7][6] = {{{200, 202, 262, 264, 262, 202},
        {264, 266, 266, 264, 262, 262},
        {200, 202, 262, 264, 262, 202},
        {264 - p + 2, 266 - p + 2, 266 - p + 2, 264 - p + 2, 262 - p + 2, 262 - p + 2},
        {200 - p, 202 - p, 262 - p, 264 - p, 262 - p, 202 - p},
        {264 - 2 * p + 4, 266 - 2 * p + 4, 266 - 2 * p + 4, 264 - 2 * p + 4, 262 - 2 * p + 4, 262 - 2 * p + 4},
        {200 - p, 202 - p, 262 - p, 264 - p, 262 - p, 202 - p}
    }
};



void shift() //function to move or right shift the digits by only incrementing the x-coordinates
{
    for(a = 1; a < 6; a++)
    {
        if(a % 2 == 0) z = 160;
        else z = 100;
        for(j = 0; j < 7; j++)
        {
            for(k = 0; k < 6; k++)
            {
                xa[a][j][k] = xa[a - 1][j][k] + z;
                ya[a][j][k] = ya[a - 1][j][k];
            }
        }
    }
}

void cut() //function to separate the digits from hours,minutes,seconds
{
    int ix, jx, num;
    for(ix = 0, jx = 0; ix <= 2; ix++)
    {
        num = t[ix];
        digit[jx++] = num / 10;
        digit[jx++] = num % 10;

    }
}

void sync() //function to set the segment states for each possible digits
{
    int ix, jx;
    gettime(t);
    cut();
    for(ix = 5; ix >= 0; ix--)
    {
        if(digit[ix] == 0)
        {
            pin[ix][3] = false;
        }
        else if(digit[ix] == 1)
        {
            pin[ix][3] = false;
            pin[ix][0] = false;
            pin[ix][1] = false;
            pin[ix][4] = false;
            pin[ix][5] = false;
        }
        else if(digit[ix] == 2)
        {
            pin[ix][0] = false;
            pin[ix][6] = false;
        }
        else if(digit[ix] == 3)
        {
            pin[ix][0] = false;
            pin[ix][4] = false;
        }
        else if(digit[ix] == 4)
        {
            pin[ix][1] = false;
            pin[ix][4] = false;
            pin[ix][5] = false;
        }
        else if(digit[ix] == 5)
        {
            pin[ix][2] = false;
            pin[ix][4] = false;
        }
        else if(digit[ix] == 6)
        {
            pin[ix][2] = false;
        }
        else if(digit[ix] == 7)
        {
            pin[ix][0] = false;
            pin[ix][4] = false;
            pin[ix][5] = false;
            pin[ix][3] = false;
        }
        else if(digit[ix] == 9)
        {
            pin[ix][4] = false;
        }

    }

}

void circle() //function to draw the beeping circles in between
{
    iFilledCircle(270, 232, 10);
    iFilledCircle(270, 164, 10);
    iFilledCircle(520, 232, 10);
    iFilledCircle(520, 164, 10);
}

void timer() //function used to change the value of a variable after certain time interval using iSetTImer in main() first
{
    tim = tim * (-1);
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{

    iClear();

    iSetColor(186, 85, 211);

    memset(pin, true, sizeof(pin));
    gettime(t);
    sync();

    for(i = 0; i < 6; i++)
        for(j = 0; j < 7; j++)
        {
            if(pin[i][j] == true)
                iFilledPolygon(xa[i][j], ya[i][j], 6);
        }

    iSetColor(255, 192, 203);
    if(tim == 1) circle();

    iSetColor(0, 0, 255);
    iText(10, 10, "Press END to exit");

    iSetColor(25, 100, 175);
    iText(700, 10, "Made By Naser Anjum Samudro (1505099)");

}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{

}

void iKeyboard(unsigned char key)
{

}

void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

}


int main()
{

    shift();

    iSetTimer(500, timer);

    iInitialize(1000, 500, "LED Watch");

    return 0;
}

