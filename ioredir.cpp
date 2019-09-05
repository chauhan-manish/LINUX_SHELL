#include <bits/stdc++.h>
using namespace std;

void ioredirection( string command,  char delim, bool flag)
{
	long i, n, fd; 
	char *args[100];
	string filename;
	vector< string >str(20);
	n = split(command, str, delim);
	
	vector< string >ar(20);
	
	delim = ' ';
	n = split(str[0], ar, delim);
	for(i=0; i<n; i++)
		args[i]=(char*)ar[i].c_str();
	args[i]=NULL;
	vector< string >arr(20);
	n = split(str[1], arr, delim);
	filename = arr[0];
	
	pid_t pid=fork();
	if( pid==0 )
	{
		if( flag )
			fd = open( (char*)filename.c_str() , O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open( (char*)filename.c_str() , O_WRONLY | O_CREAT | O_TRUNC, 0644);
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