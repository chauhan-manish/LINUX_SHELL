#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;

map < string, string >mp;
vector< string > history;
#include "split.cpp"
#include "alias.cpp"

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

int main()
{
	int fd, rfd, ioredir , in, out;
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
		history.push_back(command);
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
				fd = open("write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			filename = "read.txt";
				
			for(i=1;i<n-1;i++)
			{
				char buffer[1000]={'\0'};
	
				rfd = open("read.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				fd = open("write.txt", O_RDONLY | O_CREAT , 0644);
				
				while (1)
				{
					in = read(fd, buffer, sizeof(buffer));
					if (in <= 0) 
						break;
					out = write(rfd, buffer, in);
					if (out <= 0) 
						break;
				}
				close(rfd);
				close(fd);
				
				x = split(str[i], ar, delim);
				for(j=0; j<x; j++)
					args[j]=(char*)ar[j].c_str();
				args[j++]=(char*)filename.c_str();
				args[j]=NULL;
				pid=fork();
				if( pid==0 )
				{
					fd = open("write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			char buffer[1000]={'\0'};
	
			rfd = open("read.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fd = open("write.txt", O_CREAT | O_RDONLY, 0644);
			
			while (1)
			{
				in = read(fd, buffer, sizeof(buffer));
				if (in <= 0) 
					break;
				out = write(rfd, buffer, in);
				if (out <= 0) 
					break;
			}
			close(rfd);
			close(fd);
			
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