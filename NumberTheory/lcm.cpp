
#include <iostream>
#include <vector>

using namespace std;

int64_t getGcd(int64_t a,int64_t b)
{
	if(b==0)
		return a;
	else
		return getGcd(b,a%b);
}
int64_t getLCM(int64_t a,int64_t b)
{
	return (a*b)/getGcd(a,b);
}

int64_t getLCM(const vector<int64_t>& nums)
{
	int64_t lcm=nums.front();
	for(const int64_t& nn:nums)
		lcm=getLCM(nn,lcm);
	return lcm;
}

int main()
{
	// int64_t num1=10,num2=12;
	// cout<<getLCM(num1,num2)<<endl;

	vector<int64_t> nums={1,2,3,4,5,6,7,8,9,10};
	cout<<getLCM(nums);

	return 0;
}