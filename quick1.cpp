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


void MyVeryFastSort(int n, int *d) {

    int *arr1; // to store the sorted number
    arr1 = new int[n]; 

    //int digit = n; <- use n as digit
    int size = n*2 - 1; // negative & positive
    int *arr2;

    int pos = 1; int idx=0; // init and declare values to store value about position, index when using array
    int num = 0;

    for (; ; pos*=n) {
        // bool to check whether if sorted or not (, 0=> unsorted, 1=> sorted)
        bool sorted = 1;

        arr2 = new int[size]; 

        for (idx = 0; idx < n; idx++) {
            num = (d[idx]/pos);
            sorted = sorted & (num == 0);

            ++arr2[num%n + size/2];
        }

        // need to sort elements
        if (sorted==0){
            for (idx=1; idx<size; idx++) {
                 arr2[idx] += arr2[idx-1];
            }
            for (idx=n; idx-- > 0;) {
                arr1[--arr2[d[idx]/pos%n + size/2]] = d[idx];
            }
            for (idx=0; idx<n; idx++) {
                d[idx] = arr1[idx];
            }

        } else break; // already sorted, don't have to sort anymore
    }

    delete [] arr1;
}

int main(void) {
    int n=100000000;
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
    // int n=13;
    // int arr[13] = {-1221,1928478479,12414214,-34124,10,324,128947,-214687,9135721,-1324,234,-232,0};

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    MyVeryFastSort(n,arr);
    
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	
    printf("정렬 후: \n");
	// for (int i = 0; i < n; i++) {
	// 	printf("%d\n", arr[i]);
	// }
    double res_time = elapsed_time.count();

	bool res_validate = Validate( n , arr );	
	// 정수 개수 n
	// n 개의 정수로 이루어진 배열 d

	// Write the arr1s (corretness and time)
	if( res_validate ) {printf("OKAY\n"); }
	else { printf("WRONG\n");  }
	printf( "%d\n" , (int)res_time );

    delete [] arr;
    return 1;
}
