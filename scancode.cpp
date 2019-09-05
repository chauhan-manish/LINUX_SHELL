#include<bits/stdc++.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
using namespace std;


struct termios orig_termios;
void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
	
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	struct termios termios_p = orig_termios;
	termios_p.c_lflag &= ~( ECHO | ICANON );
	//termios_p.c_cc[VMIN]=1;
	//termios_p.c_cc[VTIME]=1;
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &termios_p);
	
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
/*
void SetCursorPosition(int XPos, int YPos) {
    printf("\033[%d;%dH",YPos+1,XPos+1);
}
void getCursor(int* x, int* y) {
   printf("\033[6n");  /* This escape sequence !writes! the current
                          coordinates to the terminal.
                          We then have to read it from there, see [4,5].
                          Needs <termios.h>,<unistd.h> and some others 
   scanf("\033[%d;%dR", x, y);
}
// Or platform independent using (n)curses
#include <curses.h> // similar name for windows
initscr(); // is required before getxy call
getyx(curscr, y, x);
void getyx(WINDOW *win, int y, int x);
*/
int main()
{
	enableRawMode();
	char c;
	string s="";
	char ch[3]={1,0,0};
	while(ch[0]!='\n')
	{
		ch[0]=getchar();
		if(ch[0]==27)
		{
			ch[1]=getchar();
			ch[2]=getchar();
			if(ch[2]=='A')
			{
				cout<<'A';
			}
			else if(ch[2]=='B')
			{
				cout<<'B';
			}
			else if(ch[2]=='C')
			{
				cout<<'C';
			}
			else if(ch[2]=='D')
			{
				cout<<'D';
			}
		}
		else
		{
			cout<<ch[0];
		}
	}
	getline(cin,s);
	cout<<s<<"\n";
}
	