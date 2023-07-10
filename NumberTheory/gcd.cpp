
#include <iostream>
#include <vector>

using namespace std;

int64_t getGcdIterative(int64_t a,int64_t b)
{
	while(b!=0)
	{
		int64_t temp=a%b;
		a=b;
		b=temp;
	}
	return a;
}

int64_t getGcd(int64_t a,int64_t b)
{
	if(b==0)
		return a;
	else
		return getGcd(b,a%b);
}

int64_t getGcd(const vector<int64_t>& nums)
{
	int64_t gcd=nums.front();
	for(const int64_t& nn:nums)
		gcd=getGcd(nn,gcd);
	return gcd;
}

int main()
{
	// int64_t num1=152,num2=816;
	// cout<<getGcd(num1,num2)<<endl;

	vector<int64_t> nums={2,22,12,2324,232,32,332,234,32};
	cout<<getGcd(nums);

	return 0;
}