long split(string command, vector<string> &args, char delim)
{
	long i=0,n=command.size(),k=0,m;
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
				if( s[0]=='"' || s[0]=='\'')
				{
					m=s.size();
					s=s.substr( 1,m-2);
					
				}
				if( mp.find(s)!=mp.end())
					s=mp[s];
				if( s == "$$" )
					s = to_string(getpid());
				args[k++] = s;
				//cout<<s<<"\n";
				s="";
			}
		}
		
	}
	if(s.size()>0)
	{
		if( s[0]=='"' || s[0]=='\'')
		{
			m=s.size();
			s=s.substr( 1,m-2);
		}
		if( mp.find(s)!=mp.end())
			s=mp[s];
		if( s == "$$" )
			s = to_string(getpid());
				
		//cout<<s<<"\n";
		args[k++] = s;
	}
	args[k]="\0";
	return k;
}