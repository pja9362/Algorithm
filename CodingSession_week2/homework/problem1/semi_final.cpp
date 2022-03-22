#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
 
 
void bfs(pair<int,int> input[],int size, int *cnt){
    
    int dx[] = {1,2,2,1,-1,-2,-2,-1};
    int dy[] = {2,1,-1,-2,-2,-1,1,2};

    int arr[20][20];
    bool visited[20][20];

// 필요한가?
    memset(arr, 0, sizeof(arr));
    memset(visited, false, sizeof(visited));
//
    queue<pair<int, int>> q;

    q.push(make_pair(input[0].first, input[0].second));

    visited[input[0].first][input[0].second] = true;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if(x == input[1].first && y == input[1].second){

//            cout << arr[x][y] << '\n';

            *cnt = arr[x][y];

            while(!q.empty()){
                q.pop();
            }
            break;
        }
        
        for(int i = 0; i < 8; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(nx >= 0 && nx < size && ny >= 0 && ny < size){
                if(visited[nx][ny] == false){
                    visited[nx][ny] = true;
                    arr[nx][ny] = arr[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
}
 
int main(int argc, char * argv[]) {
    FILE *inputFile = fopen(argv[1], "r");
    if(inputFile == NULL)
        printf("ERROR\n");

    int n;
    int srcX, srcY, dstX, dstY;

    fscanf(inputFile, "%d", &n);
    fscanf(inputFile, "%d %d", &srcX, &srcY);
    fscanf(inputFile, "%d %d", &dstX, &dstY);
    fclose(inputFile);

    // input(0) : 출발지, input(1) : 도착지
    pair<int, int> input[2];

    input[0].first = srcX;
    input[0].second = srcY;
    input[1].first = dstX;
    input[1].second = dstY;

    int cnt=0;
    int *ptr =&cnt;
    bfs(input, n, ptr);

    FILE *outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%d", cnt);
    fclose(outputFile);


    return 0;
}
