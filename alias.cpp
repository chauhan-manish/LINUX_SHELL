void alias(string command)
{
	vector<string>al(20);
	char delim='=';
	string x,y;
	long i=0, n=command.size(), k=0, m;
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
				if( mp.find(s)!=mp.end())
					s=mp[s];
				al[k++] = s;
				//cout<<s<<"\n";
				s="";
			}
		}
		
	}
	if(s.size()>0)
	{
		if( mp.find(s)!=mp.end())
			s=mp[s];
		//cout<<s<<"\n";
		al[k++] = s;
	}
	
	x=al[0];
	y=al[1];
	if( al[1][0]=='"')
	{
		n=y.size();
		y=y.substr( 1,n-3);
	}
	if( mp.find(x)!=mp.end())
		mp[x]=y;
	else
		mp.insert( make_pair( x, y ));
}