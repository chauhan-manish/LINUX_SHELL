#include <bits/stdc++.h>
using namespace std;

long split(string command, vector<string> &args, char delim)
{
	bool flag=0;
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
					//flag = 1;
					m=s.size();
					s=s.substr( 1,m-2);
					//cout<<s<<"\n";
					
				}
				if( mp.find(s)!=mp.end())
					s=mp[s];
				
				args[k++] = s;
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
			//cout<<s<<"\n";
		}
		if( mp.find(s)!=mp.end())
						s=mp[s];
		args[k++] = s;
	}
	args[k]="\0";
	return k;
}