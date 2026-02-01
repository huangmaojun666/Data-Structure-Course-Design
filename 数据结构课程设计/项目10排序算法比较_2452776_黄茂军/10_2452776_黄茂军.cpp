#include<iostream>
using namespace std;
//随机函数，生成指定个数的随机数
int* generateRandomNumbers(int count) {
	int* numbers = new int[count];
	for (int i = 0; i < count; i++) {
		numbers[i] = rand() ;
	}
	return numbers;
}
//冒泡排序
void bubbleSort(int arr[], int n, long long& comparisonCount, double& timeTaken) {
	comparisonCount = 0;
	clock_t startTime = clock();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			comparisonCount++;
			if (arr[j] > arr[j + 1]) {
				// 交换 arr[j] 和 arr[j+1]
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}

//直接插入排序
void insertionSort(int arr[], int n, long long& comparisonCount, double& timeTaken) {
	comparisonCount = 0;
	clock_t startTime = clock();
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0) {
			comparisonCount++;
			if (arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
			}
			else {
				break;
			}
		}
		arr[j + 1] = key;
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
//选择排序
void selectionSort(int arr[], int n, long long& comparisonCount, double& timeTaken)
{
	comparisonCount = 0;
	clock_t startTime = clock();
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			comparisonCount++;
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		// 交换 arr[i] 和 arr[minIndex]
		int temp = arr[i];
		arr[i] = arr[minIndex];
		arr[minIndex] = temp;
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
//希尔排序
void shellSort(int arr[], int n, long long& comparisonCount, double& timeTaken)
{
	comparisonCount = 0;
	clock_t startTime = clock();
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap; j -= gap) {
				comparisonCount++;
				if (arr[j - gap] > temp) {
					arr[j] = arr[j - gap];
				}
				else {
					break;
				}
			}
			arr[j] = temp;
		}
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
// 快速排序的递归函数
void quickSortInternal(int arr[], int left, int right, long long& comparisonCount)
{
	if (left >= right)
	{
		return;
	}

	int pivot = arr[right];
	int i = left - 1;

	for (int j = left; j < right; j++)
	{
		comparisonCount++;
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[right]);
	int pivotIndex = i + 1;
	quickSortInternal(arr, left, pivotIndex - 1, comparisonCount);
	quickSortInternal(arr, pivotIndex + 1, right, comparisonCount);
}
//快速排序
void quickSort(int arr[], int left, int right, long long& comparisonCount, double& timeTaken)
{
	if (left == 0 && right >= 0)
	{
		// 只在最外层调用时计时
		comparisonCount = 0;
		clock_t startTime = clock();

		// 递归排序
		quickSortInternal(arr, left, right, comparisonCount);

		clock_t endTime = clock();
		timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
		return;
	}

}


//推排序
void heapSort(int arr[], int n, long long& comparisonCount, double& timeTaken) {
	comparisonCount = 0;
	clock_t startTime = clock();
	// 构建最大堆
	// 从最后一个非叶子节点开始调整堆
	for (int i = n / 2 - 1; i >= 0; i--) {
		int largest = i;
		while (true) {
			int left = 2 * largest + 1;
			int right = 2 * largest + 2;
			int newLargest = largest;
			if (left < n) {
				comparisonCount++;
				if (arr[left] > arr[newLargest]) {
					newLargest = left;
				}
			}
			if (right < n) {
				comparisonCount++;
				if (arr[right] > arr[newLargest]) {
					newLargest = right;
				}
			}
			if (newLargest != largest) {
				swap(arr[largest], arr[newLargest]);
				largest = newLargest;
			}
			else {
				break;
			}
		}
	}
	// 一个个从堆中取出元素
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		int largest = 0;
		while (true) {
			int left = 2 * largest + 1;
			int right = 2 * largest + 2;
			int newLargest = largest;
			if (left < i) {
				comparisonCount++;
				if (arr[left] > arr[newLargest]) {
					newLargest = left;
				}
			}
			if (right < i) {
				comparisonCount++;
				if (arr[right] > arr[newLargest]) {
					newLargest = right;
				}
			}
			if (newLargest != largest) {
				swap(arr[largest], arr[newLargest]);
				largest = newLargest;
			}
			else {
				break;
			}
		}
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
//归并排序辅助函数：合并两个有序子数组
void merge(int arr[], int left, int mid, int right, long long& comparisonCount) {
	int n1 = mid - left + 1;// 左子数组长度
	int n2 = right - mid;// 右子数组长度
	int* L = new int[n1];
	int* R = new int[n2];
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];
	int i = 0;
	int j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		comparisonCount++;
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}
//归并排序
void mergeSort(int arr[], int left, int right, long long& comparisonCount, double& timeTaken) {
	clock_t startTime = clock();
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid, comparisonCount, timeTaken);
		mergeSort(arr, mid + 1, right, comparisonCount, timeTaken);
		merge(arr, left, mid, right, comparisonCount);
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
//基数排序辅助函数：按位计数排序
//exp 是当前位的权值，比如exp=1表示个位，exp=10表示十位
void countingSortForRadix(int arr[], int n, int exp,long long& comparisonCount) {
	int* output = new int[n];
	int count[10] = { 0 };
	for (int i = 0; i < n; i++) {
		count[(arr[i] / exp) % 10]++;
	}
	// 修改 count[i]，使其包含该位上小于等于 i 的元素个数
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
	delete[] output;
}
//基数排序
void radixSort(int arr[], int n,long long& comparisonCount, double& timeTaken) {
	comparisonCount = 0;
	clock_t startTime = clock();
	int maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > maxVal) {
			maxVal = arr[i];
		}
	}
	for (int exp = 1; maxVal / exp > 0; exp *= 10) {
		countingSortForRadix(arr, n, exp, comparisonCount);
	}
	clock_t endTime = clock();
	timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
}
int main() {
	cout << "**                  排序算法比较                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**                 1 --- 冒泡排序                 **" << endl;
	cout << "**                 2 --- 选择排序                 **" << endl;
	cout << "**                 3 --- 直接插入排序             **" << endl;
	cout << "**                 4 --- 希尔排序                 **" << endl;
	cout << "**                 5 --- 快速排序                 **" << endl;
	cout << "**                 6 --- 堆排序                   **" << endl;
	cout << "**                 7 --- 归并排序                 **" << endl;
	cout << "**                 8 --- 基数排序                 **" << endl;
	cout << "**                 9 --- 退出程序                 **" << endl;
	cout << "====================================================" << endl;
	int n;
	while (1) {
		cout << "请输入产生随机数的个数：";
		cin >> n;
		if(cin.fail() || n <= 0) {
			cout << "输入无效，请输入一个正整数。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		break;
	}
	int* numbers = generateRandomNumbers(n);
	int choice;
	while (1) {
		cout << endl;
		cout << "请选择排序算法：        ";
		cin >> choice;
		if (cin.fail() || choice < 1 || choice > 9) {
			cout << "输入无效，请输入1到9之间的整数。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (choice == 9) {
			cout << "退出程序。" << endl;
			break;
		}
		int* arr = new int[n];
		copy(numbers, numbers + n, arr);
		long long comparisonCount = 0;
		double timeTaken = 0.0;
		switch (choice) {
		case 1:
			bubbleSort(arr, n, comparisonCount, timeTaken);
			cout << "冒泡排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "冒泡排序比较次数：      " << comparisonCount << endl;
			break;
		case 2:
			selectionSort(arr, n, comparisonCount, timeTaken);
			cout << "选择排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "选择排序比较次数：      " << comparisonCount << endl;
			break;
		case 3:
			insertionSort(arr, n, comparisonCount, timeTaken);
			cout << "直接插入排序所用时间：  " << timeTaken << "秒" << endl;
			cout << "直接插入排序比较次数：  " << comparisonCount << endl;
			break;
		case 4:
			shellSort(arr, n, comparisonCount, timeTaken);
			cout << "希尔排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "希尔排序比较次数：      " << comparisonCount << endl;
			break;
		case 5:
			quickSort(arr, 0, n - 1, comparisonCount, timeTaken);
			cout << "快速排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "快速排序比较次数：      " << comparisonCount << endl;
			break;
		case 6:
			heapSort(arr, n, comparisonCount, timeTaken);
			cout << "堆排序所用时间：        " << timeTaken << "秒" << endl;
			cout << "堆排序比较次数：        " << comparisonCount << endl;
			break;
		case 7:
			mergeSort(arr, 0, n - 1, comparisonCount, timeTaken);
			cout << "归并排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "归并排序比较次数：      " << comparisonCount << endl;
			break;
		case 8:
			radixSort(arr, n, comparisonCount, timeTaken);
			cout << "基数排序所用时间：      " << timeTaken << "秒" << endl;
			cout << "基数排序比较次数：      " << comparisonCount << endl;
			break;
		}
		delete[] arr;
	}
}