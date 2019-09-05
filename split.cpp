#include <bits/stdc++.h>
using namespace std;

long split(string command, vector<string> &args, char delim)
{
	long i=0,n=command.size(),k=0;
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
				args[k++] = s;
				s="";
			}
		}
		
	}
	if(s.size()>0)
	{
		args[k++] = s;
	}
	args[k]="\0";
	return k;
}