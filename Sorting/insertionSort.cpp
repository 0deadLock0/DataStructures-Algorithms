
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& nums)
{
	const int n=nums.size();
	for(int i=1;i<n;++i)
	{
		int val=nums[i];
		int k=i-1;
		for(;k>=0 && val<nums[k];--k)
			nums[k+1]=nums[k];
		nums[k+1]=val;
	}
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	insertionSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}