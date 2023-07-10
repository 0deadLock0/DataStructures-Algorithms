
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int64_t> getCoPrimesCountTill(int limit)
{
	vector<int64_t> coPrimesCount(limit+1);
	iota(coPrimesCount.begin(),coPrimesCount.end(),0);
	coPrimesCount[1]=0;
	for(int i=2;i<=limit;++i)
	{
		if(coPrimesCount[i]!=i)
			continue;
		for(int j=2*i;j<=limit;j+=i)
		{
			coPrimesCount[j]*=(i-1);
			coPrimesCount[j]/=i;
		}
		--coPrimesCount[i];
	}
	return coPrimesCount;
}

int main()
{
	const int limit=20;
	vector<int64_t> coPrimesCount=getCoPrimesCountTill(limit);

	for(int i=1;i<coPrimesCount.size();++i)
		cout<<i<<"-"<<coPrimesCount[i]<<" ";
	cout<<"\n";

	return 0;
}