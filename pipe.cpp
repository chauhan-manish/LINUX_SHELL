void pipeline( string command , bool flag)
{
	char delim = '|';
	vector < string >str(10);
	long n = split(command, str, delim);
	long rfd, fd, in, out, i, j;
	pid_t pid;
	string filename;
	char *args[100];
	delim = ' ';
	vector< string >ar(20);
	long x = split(str[0], ar, delim);
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
	if( !flag )
		n--;
		
	for(i=1;i<n;i++)
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
	
	if( !flag )
	{
		filename="write.txt";
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
}
