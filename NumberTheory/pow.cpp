
#include <iostream>

using namespace std;

int64_t myPowRecursive(int64_t num,int64_t power)
{
	if(power==0)
		return 1;
	else if(power==1)
		return num;
	else
	{
		int64_t subResult=myPowRecursive(num,power>>1);
		int64_t result=subResult*subResult;
		if(power&1)
			result*=num;
		return result;
	}
}

int64_t myPow(int64_t num,int64_t power)
{
	int64_t result=1;
	while(power>0)
	{
		if(power&1)
			result*=num;
		num*=num;
		power>>=1;
	}
	return result;
}
int main()
{
	int64_t num=3;
	int64_t power=7;

	cout<<myPow(num,power)<<endl;

	return 0;
}