#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;
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

long split(string command, vector<string> &args, char *delim)
{
	char* ptr = strtok( (char*)command.c_str(), delim);
	long i=0;
	while(ptr != NULL)
	{
		
		args[i] = string(ptr);
		//cout<<args[i]<<"\n";
		ptr = strtok(NULL, delim);
		i++;
	}
	args[i]="\0";
	return i;
}
long split1(string command, char *args[100], char *delim)
{
	char* ptr = strtok( (char*)command.c_str(), delim);
	long i=0;
	while(ptr != NULL)
	{
		
		args[i] = ptr;
		//cout<<string(args[i])<<"\n";
		ptr = strtok(NULL, delim);
		i++;
	}
	args[i]=NULL;
	return i;
}
int main()
{
	int fd;
	char* delim;
	char *args[100];
	vector< string >str(100);
	pid_t pid;
	string ps1, tmp = getenv("USER"), command, filename="temp.txt";
	long i, n, x;
	tmp = tmp + "@" + prompt() + ": ";
	//cout<< ps1;
	while(1)
	{
		char path[100]={'\0'};
		ps1="";
		ps1 = tmp + getcwd(path,100) + "$ ";
		cout << ps1;
		getline( cin, command );
		
		delim = "|";
		n = split(command, str, delim);
		if( n > 1 )
		{
			//cout<<n<<"\n";
			delim = " ";
			x = split1(str[0], args, delim);
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
				x = split1(str[i], args, delim);
				args[x++]=(char*)filename.c_str();
				args[x]=NULL;
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
			
			filename="temp.txt";
			x = split1(str[1], args, delim);
			args[x++]=(char*)filename.c_str();
			args[x]=NULL;
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
			delim = " ";
			split1(command, args, delim);
			if(string(args[0])=="cd")
			{
				chdir(args[1]);
			}
			else
			{
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