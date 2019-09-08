void alias(string command)
{
	vector<string>al(20);
	char delim='=';
	string x,y;
	long n = split(command, al, delim);
	x=al[0];
	y=al[1];
	if( al[1][0]=='"')
	{
		n=y.size();
		y=y.substr( 1,n-3);
		//cout<<x<<"\n"<<y<<"\n";
	}
	if( mp.find(x)!=mp.end())
		mp[x]=y;
	else
		mp.insert( make_pair( x, y ));
}