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

void split(string command, char* args[])
{
	const char* delim=" ";
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
}

int main()
{
	char *args[100],*ptr, path[100];
	string ps1 = getenv("USER"), command;
	long i,x=5;
	ps1 = ps1 + "@" + prompt() + ": ";
	ps1 = ps1 + getcwd(path,100) + "$ ";
	//cout<< ps1;
	while(x--)
	{
		//path = getcwd(path,100);
		cout << ps1;
		getline( cin, command );
		split(command, args);
		pid_t pid=fork();
		
		if( pid==0 )
		{
			/*int fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(1);
			dup(fd);
			close(fd);
			*/
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
	return 0;
}