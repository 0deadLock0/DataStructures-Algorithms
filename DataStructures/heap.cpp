
#include <bits/stdc++.h>

using namespace std;

template <typename T> class Heap
{
	private:
		vector<T> elements;
		function<bool(const T,const T)> compare;
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
			while(i>0 && this->compare(this->elements[i], this->elements[p]))
			{
				swap(this->elements[i], this->elements[p]);
				i=p;
				p=this->parent(i);
			}
		}
		void heapifyDown(int i)
		{
			int l=this->leftChild(i);
			int r=this->rightChild(i);
			while(i<this->elements.size())
			{
				int minIndex=i;
				if(l<this->elements.size() && this->compare(this->elements[l], this->elements[minIndex]))
					minIndex=l;
				if(r<this->elements.size() && this->compare(this->elements[r], this->elements[minIndex]))
					minIndex=r;
				if(minIndex!=i)
				{
					swap(this->elements[i], this->elements[minIndex]);
					i=minIndex;
					l=this->leftChild(i);
					r=this->rightChild(i);
				}
				else
					break;
			}
		}
	public:
		Heap(int n=10,function<bool(const T,const T)> cmp=less<T>()) : compare(cmp)
		{
			this->elements.reserve(n);
		}
		bool empty() const
		{
			return this->elements.empty();
		}
		void push(T val)
		{
			this->elements.push_back(val);
			this->heapifyUp(this->elements.size()-1);
		}
		T top() const
		{
			return this->elements.front();
		}
		void pop()
		{
			if(this->empty())
				throw range_error("Heap already empty");
			T topVal=this->top();
			
			swap(this->elements.front(),this->elements.back());
			this->elements.pop_back();
			this->heapifyDown(0);
		}
		void display() const
		{
			for(const T& ee:this->elements)
				cout<<ee<<" ";
			cout<<"\n";
		}
		static void sort(vector<T>& elements,function<bool(const T, const T)> cmp=less<T>())
		{
			Heap heap(elements.size(),cmp);
			for(const T& ee:elements)
				heap.push(ee);
			for(int i=0;i<elements.size();++i,heap.pop())
				elements[i]=heap.top();
		}
};


int main()
{
	const int n=10;
	vector<int> nums(n);
	iota(nums.begin(),nums.end(),1);

	srand(unsigned(time(nullptr)));

	random_shuffle(nums.begin(),nums.end());

	Heap heap(n);
	for(const int& nn:nums)
		heap.push(nn);

	heap.display();

	for(;!heap.empty();heap.pop())
		cout<<heap.top()<<" ";
	cout<<"\n";

	return 0;
}