#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <csignal>
#include <termios.h>
using namespace std;

map < string, string >mp;
vector< string > history;
long calarm=0;

#include "split.cpp"
#include "alias.cpp"
#include "pipe.cpp"
#include "ioredir.cpp"
#include "scancode.cpp"
#include "xdg.cpp"
#include "echo.cpp"
int main();
 
void signalHandler(int signum)
{
	cout<<"Alarm Reminder\n";
	calarm--;
	ofstream fout;
	fout.open("/home/manish/OS/alarm.log");
	
	fout << to_string(calarm) << "\n";
	fout.close();

}

void init()
{
	mp.insert( make_pair( "$USER", getenv("USER") ) );
	mp.insert( make_pair( "$HOME", getenv("HOME") ) );
	mp.insert( make_pair( "$PATH", getenv("PATH") ) );
	
	ifstream fin;
	string s,s1="";
	fin.open("/home/manish/OS/alarm.log");
	while(fin)
	{
		getline(fin,s);
		s1+=s;
	}
	cout<<s1<<" Alarm Missed\n";
	fin.close();
	
	ofstream fout;
	fout.open("/home/manish/OS/alarm.log");
	
	fout << "0" << "\n";
	fout.close();

}

string prompt()
{
	ifstream fin;
	string a = "hostname", s, s1="";
	char *args[2];
	args[0] = (char*)a.c_str();
	args[1] = NULL;
	pid_t pid = fork();	
	if( pid == 0 )
	{
		int fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(1);
		dup(fd);
		close(fd);
		if( execvp(args[0], args) == -1)
		{
			perror(args[0]);
		}
	}
	else
	{
		wait(0);
	}
	fin.open("temp.txt");
	while(fin)
	{
		getline(fin,s);
		s1 += s;
		//cout<<s<<"\n";
	}
	mp.insert( make_pair("$HOSTNAME", s1) );
	//cout<<s1<<"\n";
	fin.close();
	return s1;
}

int main()
{
	signal(SIGALRM, signalHandler); 
	
	init();
	int fd, rfd, in, out;
	bool pipe, ioredir1, ioredir2;
	char delim;
	char *args[100];
	vector< string >str(100);
	pid_t pid;
	string ps1="", tmp = getenv("USER"), command, filename="temp.txt";
	long i, n, x, j;
	tmp = tmp + "@" + prompt() + ": ";
	//cout<< ps1;
	//mp.insert( make_pair( "$PS1", tmp) );
	string path=getenv("HOME");
	chdir(path.c_str());
		
	while(1)
	{
		ioredir1 = false;
		ioredir2 = false;
		pipe = false;
		char path[100]={'\0'};
		ps1="";
		ps1 = tmp + getcwd(path,100) + "$ ";
		
		if( mp.find("$PS1")!=mp.end())
			mp["$PS1"]=ps1;
		else
			mp.insert( make_pair( "$PS1", ps1) );
		cout << ps1;
		//getline( cin, command );
		command = getinput();

		if(command == "")
			continue;
		
		history.push_back(command);
			
		if( command.find(">>") != string::npos )
			ioredir2 = true;
		else if( command.find(">") != string::npos )
			ioredir1 = true;
		else if( command.find("|") != string::npos )
			pipe = true;
		
		if( ioredir1 )
		{
			delim = '>';
			ioredirection( command, delim, false);
		}
		else if( ioredir2 )
		{
			delim = '>>';
			ioredirection( command, delim, true);
		}
		else if( pipe )
		{
			pipeline( command, false);
		}
		else
		{
			delim = ' ';
			x = split(command, str, delim);
			if( str[0]=="exit")
				break;
			//cout<<str[0]<<"xxx"<<str[1]<<"\n";
			if( mp.find(str[0])!=mp.end() )
			{
				str[0] = mp[str[0]];
				//cout<<str[0]<<"\n";
				string ax="";
				for(i=0; i<x; i++)
					ax += str[i] + " ";
				//cout<<ax<<"\n";
				
				x = split(ax, str, delim);
				
			}
			if( str[0]=="cd" )
			{
				if(x==1)
					chdir(getenv("HOME"));
				else
					chdir((char*)str[1].c_str());
			}
			else if( str[0]=="alias" )
			{
				string ax="";
				for(i=1; i<x; i++)
					ax += str[i] + " ";
				//cout<<ax<<"\n";
				alias(ax);

			}
			else if( str[0]=="alarm" )
			{
				
				alarm(stoi(str[1]));
				calarm++;
				
			}
			else if( str[x-1]=="&" )
			{
				cout<<str[0]<<" "<<getpid();
				for(i=0; i<x-1; i++)
					args[i]=(char*)str[i].c_str();
				args[i]=NULL;
				pid=fork();
				if( pid==0 )
				{
					setpgid( 0,1 );					
					if( execvp(args[0], args) == -1)
					{
						perror(args[0]);
					}
				}
				else
				{
					//wait(0);
				}
			}
			else if( str[0] == "open" )
			{
				xdg( str[1] );
			}
			else if( str[0] == "echo" )
			{
				echo( command );
			}
			else
			{
				
				for(i=0; i<x; i++)
					args[i]=(char*)str[i].c_str();
				args[i]=NULL;
				pid=fork();
				if( pid==0 )
				{			
					if( execvp(args[0], args) == -1)
					{
						perror(args[0]);
					}
				}
				else
				{
					wait(0);
				}
			}
		}
	}
	return 0;
}