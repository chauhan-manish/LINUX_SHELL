struct termios orig_termios;

string getinput()
{
	string command="";
	//enableRawMode();
	tcgetattr(STDIN_FILENO, &orig_termios);
	//atexit(disableRawMode);
	struct termios termios_p = orig_termios;
	termios_p.c_lflag &= ~( ECHO | ICANON );
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &termios_p);
	
	char c;
	string s="";
	char ch[3]={1,0,0};
	long count=0, k=history.size(), n = mp["$PS1"].size(), m, p;
	p=n;m=n;
	while(ch[0]!='\n')
	{
		ch[0]=getchar();
		if(ch[0] == 0x3f)
		{
			cout<<"^C";
			command="";
			break;
		}
		else if( ch[0] == 0x7f)
		{
			if( m > n )
			{
				p--;
				m--;
				cout<<"\b \b";
				command = command.substr(0, command.size()-1 );
			}
		}
		else if(ch[0]==27)
		{
			ch[1]=getchar();
			ch[2]=getchar();
			if(ch[2]=='A')
			{
				cout<<"\r                                                                                                                                        \r";
				k--;
				if(k<-1)
					k=-1;
				cout<<mp["$PS1"];
				if(k>=0)
				{
					cout<<history[k];
					command = history[k];
					m = n + history[k].size();
					p=m;
				}
			}
			else if(ch[2]=='B')
			{
				cout<<"\r                                                                                                                                        \r";
				k++;
				if(k>=history.size())
					k=history.size()-1;
				
				cout<<mp["$PS1"];
				if(k<history.size())
				{
					cout<<history[k];
					command = history[k];
					m = n + history[k].size();
					p=m;
				}
			}
			else if(ch[2]=='C')
			{
				//right cursor
			}
			else if(ch[2]=='D')
			{
				//left cursor
				if( p > n )
				{
					m--;
					p--;
					printf("\b");
				}
			}
		}
		else
		{
			cout<<ch[0];
			command+=ch[0];
			m++;
			p++;
		}
	}
	command = command.substr(0, command.size()-1 );
	//cout<<command<<command.size();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	return command;
}
/* 
int main()
{
	history.push_back("echo");
	history.push_back("cat");
	history.push_back("ls -l");
	history.push_back("wc new.txt");
	history.push_back("type");
	history.push_back("date");
	history.push_back("cal 2019");
	
	cout<<getinput();
}
 */