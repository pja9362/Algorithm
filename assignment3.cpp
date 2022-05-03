#include <iostream>
#include <cstdio>
#include <chrono>

using namespace std;
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

bool Validate(int n, int *d) 
// n 개수 (샘플: 1,000,000) 범위 : 1,000 <= n <= 100,000,000
// d : n개의 정수로 이루어진 배열 
{
	//d[0] ~ d[n-1] 까지 비교
	for(int i=1;i<n;i++)
	{
		if( d[i-1] > d[i] )
		{
			return false; // sorting 오류
		}
	}	
	return true;
}
//quickSort
// void quickSort(int* arr, int start, int end) {
// 	if (start >= end) return; //원소가 1개일 때 종료
// 	int pivot = start;

// 	int left = start + 1;
// 	int right = end;

// 	while (left <= right) {//전복되기 전까지 반복
// 		while (left <= end && arr[left] <= arr[pivot])
// 			left++; //pivot보다 큰 걸 찾을 때까지 계속 오른쪽으로 이동
// 		while (right > start && arr[right] >= arr[pivot])
// 			right--;
// 		if (left > right) //엇갈렸을 때 pivot과 작은 데이터의 위치 변경
// 			swap(arr[pivot], arr[right]);
// 		else //엇갈리지 않았으면 큰 수와 작은 수 위치 변경
// 			swap(arr[left], arr[right]);
// 	}

// 	//분할하여 오른쪽과 왼쪽 각각을 실행
// 	quickSort(arr, start, right - 1); //현재 right위치에 pivot이 있으니 그 왼쪽
// 	quickSort(arr, right + 1, end);
// }
// void MyVeryFastSort(int n, int *d) {
//     quickSort(d, 0, n-1);
// }

// Insertion Sort
// void MyVeryFastSort(int n, int *d) {
//     for (int i = 1; i < n; i++) { //두 번째 원소부터 적정 위치 찾기
// 		// 자기 자신부터 왼쪽으로 한칸씩 움직임
//         for (int j = i; j > 0; j--) { //swap이 있으니 [0]이 아닌 [1] 인덱스까지만 순회
//             if (d[j] < d[j - 1]) {
//                     swap(d[j], d[j - 1]);
//             }
//             else break;		
//         }
// 	}
// }

// Selection Sort
// void MyVeryFastSort(int n, int *d) {
//     for (int i = 0; i < n; i++) {
// 	int min_index = i; //가장 작은 원소가 와야 할 위치 인덱스
// 	for (int j = i + 1; j < n; j++) {//하나씩 비교하면서 가장 작은 값의 위치 찾음
// 		if (d[min_index] > d[j]) {
// 				min_index = j;
// 		}
// 	}
// 		swap(d[i], d[min_index]);
// 	}
// }
// Bubble Sort
// void MyVeryFastSort(int n, int *d) {
//     for(int i = 0; i < n-1; i++){
//         for(int j = n-1; j > i; j--){
//             if(d[j-1] > d[j]) std::swap(d[j-1], d[j]);
//         }
//     }
// }
//퀵정렬
int partition(int list[], int left, int right)
{
    int pivot=list[left], tmp, low=left, high=right+1;
 
    do{
        do
        low++;
        while(low<=right && list[low]<pivot);
 
        do
        high--;
        while(high>=left && list[high]>pivot);
        if(low<high) SWAP(list[low], list[high], tmp);
    }while(low<high);
 
    SWAP(list[left], list[high], tmp);
    return high;
}
void quick_sort(int list[], int left, int right)
{
    if(left<right)
    {
        int q=partition(list, left, right);
        quick_sort(list, left, q-1);
        quick_sort(list, q+1, right);
    }
}
// void MyVeryFastSort(int n, int *d) {
//     quick_sort(d, 0, n-1);
// }


void radixSort(int *data, int n) {
    int bucket[10], dummy[n], max, i, index, lsd = 1;
    max = data[0];
    
    /* find the largest key */
    for (i = 0; i < n; i++) {
        if (data[i] > max)
            max = data[i];
    }
    
    while (max / lsd > 0) {
        memset(bucket, 0, sizeof(int) * 10);
        memset(dummy, 0 , sizeof(int) * n);
     
        for (i = 0; i < n; i++) {
            index = (data[i] / lsd) % 10;
            bucket[index]++;
        }
      
        for (i = 1; i < 10; i++)
            bucket[i] = bucket[i] + bucket[i-1];
        
        /* sort the elements based on current significant digit */
        for (i = n-1; i >= 0; i--) {
            index = (data[i] / lsd) % 10;
            index = --bucket[index];
            dummy[index] = data[i];

        }
        

        for (i = 0; i < n; i++)
            data[i] = dummy[i];
        lsd = lsd * 10;
    }
}
 
void MyVeryFastSort(int n,int * data) {
    if(n>800000) {
        quick_sort(data, 0, n-1);
    }
    else {
        int neg[n],pos[n],j=0,k=0,l=0;
        for(int i=0;i<n;i++){
            if(data[i]<0){
                neg[j] = data[i];
                neg[j] = abs(neg[j]);
                j++;
                
            } else {
                pos[k] = data[i];
                k++;
            }
        }
        radixSort(neg, j);
        
        // printf("\n Negative Numbers\n");
        // for(int i=0;i<j;i++){
        //     printf("%d | ",neg[i]);
        // }
        radixSort(pos, k);
        
        // printf("\n Positive Numbers\n");
        // for(int i=0;i<k;i++){
        //     printf("%d | ",pos[i]);
        // }
        l = j-1;
        for(int i=0;i<j;i++){
            data[i] = neg[l];
            data[i] = data[i]-(neg[l]*2);
            l=l-1;
            
        }
        l = 0;
        for(int i=j;i<n;i++){
            data[i] = pos[l++];
        }
    }
}

//
int main(void) {
    int n=8000000;
    int *arr;
   
    arr = new int [n];    
    //난수배열넣기 for
    srand(time(NULL));
    printf("정렬 전: \n");
    for (int i = 0; i < n; i++)
    {
        // arr[i] = rand() % n;
        arr[i] = (rand() % 200000001 + (-100000000));
        //printf("%d\n", arr[i]);
    }
    // int n=10;
    // int arr[10] = {-1221, 324,128947,-214687,9135721,-1324,234,-232,0,33};

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    MyVeryFastSort(n,arr);
    
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	
    printf("정렬 후: \n");
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
    double res_time = elapsed_time.count();

	bool res_validate = Validate( n , arr );	
	// 정수 개수 n
	// n 개의 정수로 이루어진 배열 d

	// Write the results (corretness and time)
	if( res_validate ) {printf("OKAY\n"); }
	else { printf("WRONG\n");  }
	printf( "%d\n" , (int)res_time );

    delete [] arr;
    return 1;
}
