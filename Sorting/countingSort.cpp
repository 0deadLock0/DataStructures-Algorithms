
#include <iostream>
#include <vector>

using namespace std;

vector<int> countingSort(vector<int>& nums)
{
	int minVal=INT_MAX;
	int maxVal=INT_MIN;
	for(const int& nn:nums)
	{
		minVal=min(minVal,nn);
		maxVal=max(maxVal,nn);
	}

	const int n=nums.size();
	const int m=maxVal-minVal+1;
	vector<int> counts(m);
	for(const int& nn:nums)
		++counts[nn-minVal];

	// no extra memory for output array
	/*
	for(int i=0,j=0;i<n && j<m;++j)
		for(int k=0;k<counts[j];++k,++i)
			nums[i]=j+minVal;
	
	return nums;
	*/

	//stable (but not inplace)
	for(int i=1;i<m;++i)
		counts[i]+=counts[i-1];
	vector<int> copyNums(n);
	for(int i=n-1;i>=0;--i)
	{
		copyNums[counts[nums[i]-minVal]-1]=nums[i];
		--counts[nums[i]-minVal];
	}

	return copyNums;
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	nums=countingSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}