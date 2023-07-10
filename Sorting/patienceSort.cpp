
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void patienceSort(vector<int>& nums)
{
	const int n=nums.size();
	vector<vector<int>> piles;
	for(int i=0;i<n;++i)
	{
		vector<vector<int>>::iterator pos=lower_bound(piles.begin(),piles.end(),nums[i],[](const vector<int>& pile,const int& val){return pile.back()<val;});
		if(pos==piles.end())
			piles.push_back(vector<int>{nums[i]});
		else
			pos->push_back(nums[i]);
	}

	auto cmp=[](vector<vector<int>>::iterator itr1,vector<vector<int>>::iterator itr2){ assert(!itr1->empty() && !itr2->empty()); return itr1->back() > itr2->back();};

	priority_queue<vector<vector<int>>::iterator,vector<vector<vector<int>>::iterator>,decltype(cmp)> minHeap(cmp);
	for(vector<vector<int>>::iterator itr=piles.begin();itr!=piles.end();++itr)
		minHeap.push(itr);

	for(int i=0;i<n;++i)
	{
		vector<vector<int>>::iterator itr=minHeap.top();
		minHeap.pop();
		
		nums[i]=itr->back();
		itr->pop_back();

		if(!itr->empty())
			minHeap.push(itr);
	}
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	patienceSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}