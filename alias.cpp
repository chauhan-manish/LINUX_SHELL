#include <bits/stdc++.h>
using namespace std;
map< string, string >mp;
/*long split(string command, vector<string> &args, char *delim)
{
	char* ptr = strtok( (char*)command.c_str(), delim);
	long i=0;
	while(ptr != NULL)
	{
		if(string(ptr)!=" ")
		{	args[i] = string(ptr);
			//cout<<args[i]<<"\n";
			i++;
		}
		ptr = strtok(NULL, delim);
		
	}
	args[i]="\0";
	return i;
}
*/
void alias(string command)
{
	vector<string>al(20);
	char *delim="=";
	string x;
	long n = split1(command, al, delim);
	cout<<al[0]<<"\n"<<al[1]<<"\n";
	if( al[1][0]=='"')
	{
		n=al[1].size();
		x=al[1].substr( 1,n-3);
		mp.insert( make_pair( al[0], x ));
	}
	else
		mp.insert( make_pair( al[0], al[1] ));
}
/*
int main()
{
	char *delim=" ";
	string s,x="";
	getline(cin, s);
	vector<string >args(20);
	long i,n = split(s, args, delim);
	if(args[0]=="alias")
	{
		for(i=1;i<n;i++)
			x+=args[i]+" ";
		//cout<<x;
		alias(x);
	}
	return 0;
}
*/