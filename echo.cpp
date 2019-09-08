void echo( string command )
{
	char delim;
	char *args[100];
	string s;
	vector< string >str(20);
	long n, i, x, pos;
	pid_t pid;
	if( command.find('"') != string::npos )
	{
		delim = '"';
		x = split( command, str, delim);
		//cout<<str[0]<<"\n"<<str[1]<<"\n";
		vector< string >ar(20);
		delim = ' ';
		
		map< string,string > :: iterator it;
		for( it=mp.begin(); it!=mp.end(); it++)
		{
			s = it->first;
			//cout<<s<<" ";
			pos = str[x-1].find(s);
			if(  pos!= string::npos )
			{
				str[x-1].replace(str[x-1].begin()+pos, str[x-1].begin()+pos+s.size(), it->second);
			}
			
		}
		pos = str[x-1].find("$$");
		if(  pos!= string::npos )
		{
			str[x-1].replace(str[x-1].begin()+pos, str[x-1].begin()+pos+2, to_string(getpid()) );
		}
		//cout<<str[x-1]<<"\n";
		
		
		n = split( str[0], ar, delim);
		for(i=0; i<n; i++)
			args[i]=(char*)ar[i].c_str();
		
		args[i]=(char*)str[x-1].c_str();
		i++;
		args[i]=NULL;
		
		pid = fork();
		if( pid==0 )
		{	cout<<"lol";
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
		n = split( command, str, delim);
		for(i=0; i<n; i++)
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