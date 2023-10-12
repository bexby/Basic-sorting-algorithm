#include<iostream>
#include<ctime>
using namespace std;

void fastSort(int array[], int start, int end)	//是递归调用的算法
{
	/*
	* ---快排的基本介绍---
	* 首先任意选取一个记录作为枢轴（通常是第一个记录），然后重新排列其他记录，使
	* 关键字较它小的都在它前面，关键字较它大的都在它后面，一趟排序完后枢轴的位置
	* 就确定了，把原来的序列分割为两个子序列，在子序列中继续快排，直到完全有序
	*
	* 快速排序最好情况时每一趟都把序列分为两个长度相等的子序列，此时时间复杂度为nlog2(n)
	* 最坏情况是元素已经顺序或逆序，每一趟都把序列分为一个空序列和一个最长的子序列，此时时间复杂度为n^2
	* 平均情况时间复杂度约为1.39nlog2(n),相比于其他算法更接近最好情况时间复杂度，经验表明也是最快的排序算法
	*/
	if (start < end)	//如果start小于end，即传递的数组长度大于1
	{
		/*
		* 当关键字基本有序时，退化为冒泡排序，从而时间大大增加，下面是改善这种情况的方法
		* 根据序列头，中，尾三个元素大小判断，取大小为中值的元素作为枢轴放在第一位
		*（与头元素交换），这样可以使2个子序列的长度相近
		*/
		int valueA = max(array[start], array[(start + end) / 2]);
		int indexA = array[start] == valueA ? start : (start + end) / 2;
		int valueB = min(valueA, array[end]);
		int indexB = array[end] == valueB ? end : indexA;
		if (indexB == indexA)
		{
			//这里的意思是indexA指示的值要比某一个值大，又比某一个值小，所以它是中值
			//虽然indexA还不确定是start还是(start+end)/2，但依旧可以和头元素交换
			int temp = array[start];
			array[start] = array[indexA];
			array[indexA] = temp;
		}
		else
		{
			//此时indexA指示的已经是最大值了，但具体是start还是(start+end)/2还不知
			if (array[start] < array[end] || array[(start + end) / 2] < array[end])
			{
				//end指示的不可能大于最大值，此时就可以确定中值是end指示的值了
				int temp = array[start];
				array[start] = array[end];
				array[end] = temp;
			}
			else if (array[start] > array[(start + end)/2])
			{
				//若执行到这里，说明end没有大于它们的任何一个，说明中值在indexA
				//指示的值中产生，当中值是start时不用交换
				int temp = array[start];
				array[start] = array[(start + end) / 2];
				array[(start + end) / 2] = temp;
			}
		}

		/*
		* 直到下面这部分才是快排的主要内容
		* 思想是，t指针从尾元素向前移动，找到第一个比枢轴元素小的元素并和它交换位置，
		* 然后轮到s指针从头元素向后移动，找到第一个比枢轴元素大的元素并和枢轴元素当前
		* 的位置交换位置，如此轮流直到s，t相遇
		*/

		int center = array[start];	//先保存枢轴的值
		int s = start;	
		int t = end;	
		while (t > s)	//仅当s,t没有相遇时才能继续，否则说明整个序列已经被扫描完
		{
			//这一步有必要加上t>s这个条件且必须放在前面，否则当t减到-1时发生索引错误，下面同理
			while (t > s && array[t] >= center)	
			{
				t--;
			}
			/*
			* 实际上，当t移动时，s所指的位置就是枢轴元素当前位置；当s移动时，t所指
			* 的位置就是枢轴元素当前位置。所以可以省略交换位置的步骤，现把最开始枢轴
			* 元素的值保存下来，然后把当前指针所指的值直接赋给枢轴的位置。最后s，t相
			* 遇的位置就是枢轴最终的位置
			*/
			array[s] = array[t];
			while (t > s && array[s] <= center)
			{
				s++;
			}
			array[t] = array[s];
		}
		array[t] = center;	//把枢轴的值赋给枢轴最终的位置
		fastSort(array, start, t - 1);	//把子序列递归调用
		fastSort(array, t + 1, end);
	}
}

int getRand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}


int main()
{
	srand((unsigned int)time(NULL));
	int array[20] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		array[i] = getRand(0, 100);
	}
	fastSort(array, 0, 19);
	for (int i = 0; i < 20; i++)
	{
		cout << array[i] << " ";
	}
}