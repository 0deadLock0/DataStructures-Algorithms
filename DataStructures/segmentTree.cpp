
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

template <typename T>
class SegmentTree
{
	private:
		const int N;
		vector<T> nums;
		vector<T> tree;
		const function<T(T, T)> combine;
		void build(int treeIndex, int arrIndexLow, int arrIndexHigh)
		{
			if( arrIndexLow == arrIndexHigh )
			{
				this->tree[treeIndex] = this->nums[arrIndexLow];
				return;
			}

			int treeIndexLeft = (treeIndex << 1) + 1;
			int treeIndexRight = (treeIndex << 1) + 2;
			
			int arrIndexMid = arrIndexLow + ((arrIndexHigh - arrIndexLow) >> 1);
		
			this->build(treeIndexLeft, arrIndexLow, arrIndexMid);
			this->build(treeIndexRight, arrIndexMid + 1, arrIndexHigh);

			this->tree[treeIndex] = this->combine(this->tree[treeIndexLeft], this->tree[treeIndexRight]);
		}
		T range_result(int treeIndex, int curRangeIndexLow, int curRangeIndexHigh, int targetRangeIndexLow, int targetRangeIndexHigh)
		{
			if( targetRangeIndexLow <= curRangeIndexLow && curRangeIndexHigh <= targetRangeIndexHigh )
				return this->tree[treeIndex];
			
			int treeIndexLeft = (treeIndex << 1) + 1;
			int treeIndexRight = (treeIndex << 1) + 2;
			
			int curRangeIndexMid = curRangeIndexLow + ((curRangeIndexHigh - curRangeIndexLow) >> 1);

			if( targetRangeIndexHigh <= curRangeIndexMid )
				return this->range_result(treeIndexLeft, curRangeIndexLow, curRangeIndexMid, targetRangeIndexLow, targetRangeIndexHigh);
			else if( curRangeIndexMid < targetRangeIndexLow )
				return this->range_result(treeIndexRight, curRangeIndexMid + 1, curRangeIndexHigh, targetRangeIndexLow, targetRangeIndexHigh);
		
			T leftResult = this->range_result(treeIndexLeft, curRangeIndexLow, curRangeIndexMid, targetRangeIndexLow, curRangeIndexMid);
			T rightResult = this->range_result(treeIndexRight, curRangeIndexMid + 1, curRangeIndexHigh, curRangeIndexMid + 1, targetRangeIndexHigh);
		
			return this->combine(leftResult, rightResult);
		}
		void update_index(int treeIndex, int arrIndexLow, int arrIndexHigh, int arrIndexTarget, T updateValue)
		{
			if( arrIndexLow == arrIndexHigh )
			{
				this->tree[treeIndex] = updateValue;
				this->nums[arrIndexTarget] = updateValue;
				return;
			}

			int treeIndexLeft = (treeIndex << 1) + 1;
			int treeIndexRight = (treeIndex << 1) + 2;

			int arrIndexMid = arrIndexLow + ((arrIndexHigh - arrIndexLow) >> 1);

			if( arrIndexTarget <= arrIndexMid )
				this->update_index(treeIndexLeft, arrIndexLow, arrIndexMid, arrIndexTarget, updateValue);
			else
				this->update_index(treeIndexRight, arrIndexMid + 1, arrIndexHigh, arrIndexTarget, updateValue);

			this->tree[treeIndex] = this->combine(this->tree[treeIndexLeft], this->tree[treeIndexRight]);
		}
	public:
		SegmentTree(const vector<T>& numsArr, function<T(T, T)> combineFunction) : N(numsArr.size()), combine(combineFunction)
		{
			this->nums = numsArr;
			const int TreeSize = (1 << (int)((ceil(log2(N))) + 1)) - 1;
			this->tree.resize(TreeSize);

			this->build(0, 0, this->N-1);
		}
		T range_result(int arrIndexLow, int arrIndexHigh)
		{
			assert(arrIndexLow <= arrIndexHigh);

			return this->range_result(0, 0, this->N - 1, arrIndexLow, arrIndexHigh);
		}
		void update_index(int arrIndex, T updateValue)
		{
			this->update_index(0, 0, this->N - 1, arrIndex, updateValue);
		}
};

int sumNums(int a, int b)
{
	return a + b;
}

int main()
{
	vector<int> nums = {1, 3, 5, 7, 9, 11};

	SegmentTree<int> st(nums, sumNums);

	cout << st.range_result(1, 3) << endl;

	st.update_index(1, 10);

	cout << st.range_result(1, 3) << endl;

	return 0;
}