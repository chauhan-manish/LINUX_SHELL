void xdg( string str)
{
	string prog_name;
	char *args[100];
	vector <string >arg(20);
	char delim = '.';
	long j, n = split( str, arg, delim);
	
	if ( arg[n-1] == "mkv" || arg[n-1] == "mp3" || arg[n-1] == "mp4" )
		prog_name = "vlc";
	else if( arg[n-1] == "jpg" || arg[n-1] == "png" || arg[n-1] == "jpeg" )
		prog_name = "eog";
	else if( arg[n-1] == "txt" || arg[n-1] == "cpp" || arg[n-1] == "html" )
		prog_name = "gedit";
	
	args[0]=(char *)prog_name.c_str(); 
	args[1]=(char*)str.c_str(); 
	args[2]=NULL;
	pid_t pid=fork();
	if( pid==0 )
	{
		if( execvp(args[0], args) == -1)
		{
			perror(args[0]);
		}
	}
	else
		wait(0);
	
}
