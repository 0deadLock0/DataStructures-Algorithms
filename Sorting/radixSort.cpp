
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void countingSort(vector<int>& nums,int exp)
{
	const int n=nums.size();
	const int m=10;
	vector<int> counts(m);
	for(const int& nn:nums)
		++counts[(nn/exp)%10];

	for(int i=1;i<m;++i)
		counts[i]+=counts[i-1];
	vector<int> copyNums(n);
	for(int i=n-1;i>=0;--i)
	{
		copyNums[counts[(nums[i]/exp)%10]-1]=nums[i];
		--counts[(nums[i]/exp)%10];
	}

	for(int i=0;i<n;++i)
		nums[i]=copyNums[i];
}

void radixSort(vector<int>& nums)
{
	for(const int& nn:nums)
		assert(nn>=0);

	int maxVal=0;
	for(const int& nn:nums)
		maxVal=(nn>maxVal)?nn:maxVal;

	for(int i=1;i<=maxVal;i*=10)
		countingSort(nums,i);
}

int main()
{
	vector<int> nums={42, 53, 3, 35, 409, 111, 29, 1, 1000};
	radixSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}