void ioredirection( string command,  char delim, bool flag)
{
	long i, n, fd, rfd, in, out; 
	char *args[100];
	string filename, filename2="write.txt";
	
	vector< string >str(20);
	n = split(command, str, delim);
	bool pipe=false;
	vector< string >ar(20);
	
	if( command.find("|") != string::npos )
	{
		pipe = true;
		pipeline( str[0], true);
		
		delim = ' ';
		n = split(str[1], ar, delim);
		char buffer[1000]={'\0'};
		fd = open((char*)filename2.c_str(), O_RDONLY | O_CREAT , 0644);
		rfd = open((char*)ar[0].c_str(), O_CREAT | O_WRONLY, 0644);
		
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
	}
	else{
		
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
}