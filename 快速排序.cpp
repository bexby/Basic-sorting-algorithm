#include<iostream>
#include<ctime>
using namespace std;

void fastSort(int array[], int start, int end)	//�ǵݹ���õ��㷨
{
	/*
	* ---���ŵĻ�������---
	* ��������ѡȡһ����¼��Ϊ���ᣨͨ���ǵ�һ����¼����Ȼ����������������¼��ʹ
	* �ؼ��ֽ���С�Ķ�����ǰ�棬�ؼ��ֽ�����Ķ��������棬һ��������������λ��
	* ��ȷ���ˣ���ԭ�������зָ�Ϊ���������У����������м������ţ�ֱ����ȫ����
	*
	* ��������������ʱÿһ�˶������з�Ϊ����������ȵ������У���ʱʱ�临�Ӷ�Ϊnlog2(n)
	* ������Ԫ���Ѿ�˳�������ÿһ�˶������з�Ϊһ�������к�һ����������У���ʱʱ�临�Ӷ�Ϊn^2
	* ƽ�����ʱ�临�Ӷ�ԼΪ1.39nlog2(n),����������㷨���ӽ�������ʱ�临�Ӷȣ��������Ҳ�����������㷨
	*/
	if (start < end)	//���startС��end�������ݵ����鳤�ȴ���1
	{
		/*
		* ���ؼ��ֻ�������ʱ���˻�Ϊð�����򣬴Ӷ�ʱ�������ӣ������Ǹ�����������ķ���
		* ��������ͷ���У�β����Ԫ�ش�С�жϣ�ȡ��СΪ��ֵ��Ԫ����Ϊ������ڵ�һλ
		*����ͷԪ�ؽ���������������ʹ2�������еĳ������
		*/
		int valueA = max(array[start], array[(start + end) / 2]);
		int indexA = array[start] == valueA ? start : (start + end) / 2;
		int valueB = min(valueA, array[end]);
		int indexB = array[end] == valueB ? end : indexA;
		if (indexB == indexA)
		{
			//�������˼��indexAָʾ��ֵҪ��ĳһ��ֵ���ֱ�ĳһ��ֵС������������ֵ
			//��ȻindexA����ȷ����start����(start+end)/2�������ɿ��Ժ�ͷԪ�ؽ���
			int temp = array[start];
			array[start] = array[indexA];
			array[indexA] = temp;
		}
		else
		{
			//��ʱindexAָʾ���Ѿ������ֵ�ˣ���������start����(start+end)/2����֪
			if (array[start] < array[end] || array[(start + end) / 2] < array[end])
			{
				//endָʾ�Ĳ����ܴ������ֵ����ʱ�Ϳ���ȷ����ֵ��endָʾ��ֵ��
				int temp = array[start];
				array[start] = array[end];
				array[end] = temp;
			}
			else if (array[start] > array[(start + end)/2])
			{
				//��ִ�е����˵��endû�д������ǵ��κ�һ����˵����ֵ��indexA
				//ָʾ��ֵ�в���������ֵ��startʱ���ý���
				int temp = array[start];
				array[start] = array[(start + end) / 2];
				array[(start + end) / 2] = temp;
			}
		}

		/*
		* ֱ�������ⲿ�ֲ��ǿ��ŵ���Ҫ����
		* ˼���ǣ�tָ���βԪ����ǰ�ƶ����ҵ���һ��������Ԫ��С��Ԫ�ز���������λ�ã�
		* Ȼ���ֵ�sָ���ͷԪ������ƶ����ҵ���һ��������Ԫ�ش��Ԫ�ز�������Ԫ�ص�ǰ
		* ��λ�ý���λ�ã��������ֱ��s��t����
		*/

		int center = array[start];	//�ȱ��������ֵ
		int s = start;	
		int t = end;	
		while (t > s)	//����s,tû������ʱ���ܼ���������˵�����������Ѿ���ɨ����
		{
			//��һ���б�Ҫ����t>s��������ұ������ǰ�棬����t����-1ʱ����������������ͬ��
			while (t > s && array[t] >= center)	
			{
				t--;
			}
			/*
			* ʵ���ϣ���t�ƶ�ʱ��s��ָ��λ�þ�������Ԫ�ص�ǰλ�ã���s�ƶ�ʱ��t��ָ
			* ��λ�þ�������Ԫ�ص�ǰλ�á����Կ���ʡ�Խ���λ�õĲ��裬�ְ��ʼ����
			* Ԫ�ص�ֵ����������Ȼ��ѵ�ǰָ����ָ��ֱֵ�Ӹ��������λ�á����s��t��
			* ����λ�þ����������յ�λ��
			*/
			array[s] = array[t];
			while (t > s && array[s] <= center)
			{
				s++;
			}
			array[t] = array[s];
		}
		array[t] = center;	//�������ֵ�����������յ�λ��
		fastSort(array, start, t - 1);	//�������еݹ����
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