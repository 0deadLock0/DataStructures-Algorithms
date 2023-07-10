
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void swap(int& a,int& b)
{
	int c=a;
	a=b;
	b=c;
}

class Heap
{
	private:
		vector<int> nums;
		function<bool(int,int)> compare;
		int parent(int x)
		{
			return (x-1)/2;
		}
		int leftChild(int x)
		{
			return 2*x+1;
		}
		int rightChild(int x)
		{
			return 2*x+2;
		}
		void heapifyUp(int i)
		{
			int p=this->parent(i);
			while(i>0 && compare(nums[i],nums[p]))
			{
				swap(nums[i],nums[p]);
				i=p;
				p=this->parent(i);
			}
		}
		void heapifyDown(int i)
		{
			int l=this->leftChild(i);
			int r=this->rightChild(i);
			while(i<this->nums.size())
			{
				int minIndex=i;
				if(l<this->nums.size() && compare(nums[l],nums[minIndex]))
					minIndex=l;
				if(r<this->nums.size() && compare(nums[r],nums[minIndex]))
					minIndex=r;
				if(minIndex!=i)
				{
					swap(nums[i],nums[minIndex]);
					i=minIndex;
					l=this->leftChild(i);
					r=this->rightChild(i);
				}
				else
					break;
			}
		}
	public:
		Heap(int n=10,function<bool(int,int)> cmp=less<int>()) : compare(cmp)
		{
			this->nums.reserve(n);
		}
		bool empty() const
		{
			return this->nums.empty();
		}
		void push(int val)
		{
			this->nums.push_back(val);
			this->heapifyUp(this->nums.size()-1);
		}
		int top() const
		{
			return this->nums.front();
		}
		void pop()
		{
			if(this->empty())
				throw range_error("Heap already empty");
			int topVal=this->top();
			swap(this->nums.front(),this->nums.back());
			this->nums.pop_back();
			this->heapifyDown(0);
		}
		void display() const
		{
			for(const int& nn:this->nums)
				cout<<nn<<" ";
			cout<<"\n";
		}
};

void heapSort(vector<int>& nums,function<bool(int,int)> cmp=less<int>())
{
	Heap heap(nums.size(),cmp);
	for(const int& nn:nums)
		heap.push(nn);
	for(int i=0;i<nums.size();++i,heap.pop())
		nums[i]=heap.top();
}

int main()
{
	vector<int> nums={4, -5, 3, 3, 9, -2};
	heapSort(nums);
	for(const int& nn:nums)
		cout<<nn<<" ";
	cout<<"\n";

	return 0;
}