#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////
#include <iostream>
using namespace std;
void quickSort(int *arr, int start, int end) {
	if (start >= end) return; //원소가 1개일 때 종료
	int pivot = start;

	int left = start + 1;
	int right = end;

	while (left <= right) {//전복되기 전까지 반복
		while (left <= end && arr[left] <= arr[pivot])
			left++; //pivot보다 큰 걸 찾을 때까지 계속 오른쪽으로 이동
		while (right > start && arr[right] >= arr[pivot])
			right--;
		if (left > right) //엇갈렸을 때 pivot과 작은 데이터의 위치 변경
			swap(arr[pivot], arr[right]);
		else //엇갈리지 않았으면 큰 수와 작은 수 위치 변경
			swap(arr[left], arr[right]);
			
	}

	//분할하여 오른쪽과 왼쪽 각각을 실행
	quickSort(arr, start, right - 1); //현재 right위치에 pivot이 있으니 그 왼쪽
	quickSort(arr, right + 1, end);
}

void MyVeryFastSort(int n, int *d)
// n 개수 (샘플: 1,000,000) 범위 : 1,000 <= n <= 100,000,000
// d : n개의 정수로 이루어진 배열 
{

	quickSort(d, 0, n-1);

}
// void MyVeryFastSort(int n, int *d)
// // n 개수 (샘플: 1,000,000) 범위 : 1,000 <= n <= 100,000,000
// // d : n개의 정수로 이루어진 배열 
// {

// }



/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////


// Utilized to check the correctness
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

int main(int argc, char **argv)
{
	if( argc != 3 )
	{
		fprintf( stderr , "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int n, *d; 
	// n 개수 (샘플: 1,000,000) 범위 : 1,000 <= n <= 100,000,000
	// d : n개의 정수로 이루어진 배열 
	FILE *input = fopen( argv[1] , "rb" ); // rb means 'read binary'
	int e = fread( &n , sizeof(int) , 1 , input ); // sizeof(int)*1 만큼을 n에 저장 (개수 지정)
	d = new int [ n ]; // (길이 n 만큼의 배열 생성)

	// 다시 호출하면, 증가한 위치에서부터 파일 읽기 시작
	// n=10, 10 a1,a2,a3,a4 ... a10 총 11개의 값
	e = fread( d , sizeof(int) , n , input ); // sizeof(int)*n 만큼을 d에 저장

	fclose(input);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your sorting algorithm
	// 정수 개수 n
	// n 개의 정수로 이루어진 배열 d
	MyVeryFastSort( n , d );

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	bool res_validate = Validate( n , d );	
	// 정수 개수 n
	// n 개의 정수로 이루어진 배열 d

	// Write the results (corretness and time)
	FILE *output = fopen( argv[2] , "w" );
	if( res_validate ) { fprintf( output , "OKAY\n" ); printf("OKAY\n"); }
	else { fprintf( output , "WRONG\n" ); printf("WRONG\n");  }
	fprintf( output , "%d\n" , (int)res_time );
	printf( "%d\n" , (int)res_time );
	fclose(output);

	delete [] d;

	return 1;
}