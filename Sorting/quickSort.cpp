
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int& a,int& b)
{
	int c=a;
	a=b;
	b=c;
}

void quickSort(vector<int>& nums, int l, int r)
{
	if(r-l+1<=1)
		return;

	int randIndex=l+rand()%(r-l+1);
	int pivotVal=nums[randIndex];
	int i=l;
	int j=l;
	int k=r;
	while(j<=k)
	{
		if(nums[j]<pivotVal)
		{
			swap(nums[i],nums[j]);
			++i;
			++j;
		}
		else if(nums[j]==pivotVal)
			++j;
		else
		{
			swap(nums[k],nums[j]);
			--k;
		}
	}

	quickSort(nums,l,i-1);
	quickSort(nums,k+1,r);
}

void quickSort(vector<int>& nums)
{
	quickSort(nums,0,nums.size()-1);
}

int main()
{
	srand(unsigned(time(nullptr)));

	vector<int> nums={4, -5, 3, 3, 9, -2};

	quickSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";
	
	return 0;
}