
#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums, int l, int m, int r)
{
	const int n=r-l+1;
	vector<int> mergedArr(n);
	for(int i=l,j=m+1,k=0;i<=m && j<=r;)
	{
		if(nums[i]<=nums[j])
		{
			mergedArr[k]=nums[i];
			++i;
			++k;
		}
		else
		{
			mergedArr[k]=nums[j];
			++j;
			++k;
		}

		while(i==m+1 && j<=r)
		{
			mergedArr[k]=nums[j];
			++j;
			++k;
		}
		while(j==r+1 && i<=m)
		{
			mergedArr[k]=nums[i];
			++i;
			++k;
		}
	}
	
	for(int k=0;k<n;++k)
		nums[l+k]=mergedArr[k];
}

void mergeSort(vector<int>& nums, int l, int r)
{
	if(r-l+1<=1)
		return;

	int m=l+(r-l)/2;

	mergeSort(nums,l,m);
	mergeSort(nums,m+1,r);

	merge(nums,l,m,r);
}

void mergeSort(vector<int>& nums)
{
	mergeSort(nums,0,nums.size()-1);
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	mergeSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";
	
	return 0;
}