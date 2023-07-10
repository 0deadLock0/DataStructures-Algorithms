
#include <iostream>
#include <vector>

using namespace std;

void swap(int& a,int& b)
{
	int c=a;
	a=b;
	b=c;
}

void selectionSort(vector<int>& nums)
{
	const int n=nums.size();
	for(int i=0;i<n;++i)
	{
		int minIndex=i;
		for(int j=i+1;j<n;++j)
			if(nums[j]<nums[minIndex])
				minIndex=j;
		swap(nums[i],nums[minIndex]);
	}
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	selectionSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}