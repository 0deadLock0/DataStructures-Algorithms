
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void insertionSort(vector<float>& nums)
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

void bucketSort(vector<float>& nums)
{
	//only works for non-negative values
	for(float& nn:nums)
		assert(nn>=0);

	const int n=nums.size();

	const int bucketsCount=n;

	float maxNum=nums[0];
	float minNum=nums[0];
	for(int i=1;i<n;++i)
	{
		if(nums[i]<minNum)
			minNum=nums[i];
		if(nums[i]>maxNum)
			maxNum=nums[i];
	}

	auto ceilDiv=[](int div,int quo){return (div+quo-1)/quo;};
	int range=ceilDiv(maxNum-minNum+1,bucketsCount);

	vector<vector<float>> buckets(bucketsCount);
	for(float& nn:nums)
	{
		int correspondingBucket=(nn-minNum)/range;
		buckets[correspondingBucket].push_back(nn);
	}

	for(vector<float>& bb:buckets)
		insertionSort(bb); //prefered Insertion Sort because it is faster for nearly sorted array

	for(int i=bucketsCount-1,l=n-1;i>=0;--i)
		for(int j=buckets[i].size()-1;j>=0;--j,--l)
			nums[l]=buckets[i][j];

}

int main()
{
	vector<float> nums={4.2, 5.3, 3.4, 3.5, 4.9, 2.9};
	bucketSort(nums);
	for(float& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}