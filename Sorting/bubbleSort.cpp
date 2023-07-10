
#include <iostream>
#include <vector>

using namespace std;

void swap(int& a,int& b)
{
	int c=a;
	a=b;
	b=c;
}

void bubbleSort(vector<int>& nums)
{
	const int n=nums.size();
	for(int i=0;i<n;++i)
		for(int j=0;j<n-i-1;++j)
			if(nums[j]>nums[j+1])
				swap(nums[j],nums[j+1]);
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	bubbleSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";
	
	return 0;
}