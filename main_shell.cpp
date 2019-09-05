#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//#include "alias.cpp"
using namespace std;
map < string, string >mp;

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
	//cout<<s1<<"\n";
	fin.close();
	return s1;
}

long split(string command, vector<string> &args, char delim)
{
	long i=0,n=command.size(),k=0;
	string s="";
	for(i=0;i<n;i++)
	{
		if(command[i]!=delim)
		{	
			s+=command[i];
		}
		else
		{
			if(s.size()>0)
			{
				args[k++] = s;
				s="";
			}
		}
		
	}
	if(s.size()>0)
	{
		args[k++] = s;
	}
	args[k]="\0";
	return k;
}
void alias(string command)
{
	vector<string>al(20);
	char delim='=';
	string x,y;
	long n = split(command, al, delim);
	x=al[0];
	y=al[1];
	//cout<<x<<"\n"<<y<<"\n";
	if( al[1][0]=='"')
	{
		n=y.size();
		y=y.substr( 1,n-3);
		//cout<<x<<"\n"<<y<<"\n";
	}
	if( mp.find(x)!=mp.end())
		mp[x]=y;
	else
		mp.insert( make_pair( x, y ));
}
int main()
{
	int fd, ioredir ;
	char delim;
	char *args[100];
	vector< string >str(100);
	pid_t pid;
	string ps1="", tmp = getenv("USER"), command, filename="temp.txt";
	long i, n, x, j;
	tmp = tmp + "@" + prompt() + ": ";
	//cout<< ps1;
	while(1)
	{
		char path[100]={'\0'};
		ps1="";
		ps1 = tmp + getcwd(path,100) + "$ ";
		cout << ps1;
		getline( cin, command );
		if(command == "")
			continue;

		delim = '|';
		n = split(command, str, delim);
		//cout<<n<<"\n";
		if( n > 1 )
		{
			///////////////////  pipe
			delim = ' ';
			vector< string >ar(20);
			x = split(str[0], ar, delim);
			for(j=0; j<x; j++)
			{
				args[j]=(char*)ar[j].c_str();
			}
			args[j]=NULL;
			
			pid=fork();
			if( pid==0 )
			{
				fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			
			for(i=1;i<n-1;i++)
			{
				x = split(str[i], ar, delim);
				for(j=0; j<x; j++)
					args[j]=(char*)ar[j].c_str();
				args[j++]=(char*)filename.c_str();
				args[j]=NULL;
				pid=fork();
				if( pid==0 )
				{
					fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			}
			x = split(str[i], ar, delim);
			for(j=0; j<x; j++)
				args[j]=(char*)ar[j].c_str();
			args[j++]=(char*)filename.c_str();
			args[j]=NULL;
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
		else
		{
			delim = ' ';
			x = split(command, str, delim);
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
			if(str[0]=="cd")
			{
				chdir((char*)str[1].c_str());
			}
			else if(str[0]=="alias")
			{
				string ax="";
				for(i=1; i<x; i++)
					ax += str[i] + " ";
				//cout<<ax<<"\n";
				alias(ax);

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