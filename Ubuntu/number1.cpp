#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

// 큐 활용 너비우선 탐색 (Breadth First Search Using queue)
void BFS(pair<int,int> input[],int n, int *cnt){
    
    // x,y 이동 가능 조합 
    int moveX[] = {1,2,2,1,-1,-2,-2,-1};
    int moveY[] = {2,1,-1,-2,-2,-1,1,2};

    int arr[20][20]; // 체스판 (길이 최대 20x20) (board size NxN, 4<=N<=20)
    bool visited[20][20]; // 체스판 개별 칸 방문 여부 

    memset(arr, 0, sizeof(arr));
    memset(visited, false, sizeof(visited));

    queue< pair<int, int> > q;

    // push "start position"
    q.push(make_pair(input[0].first, input[0].second));

    visited[input[0].first][input[0].second] = true;

    while(!q.empty()){
        // x,y : 현위치 (now position), newX,newY : 이동위치 (new position)
        int x,y,newX,newY;

        x = q.front().first;
        y = q.front().second;

        q.pop();

        // 도착지에 도달했다면 (reach the destination)
        if(x == input[1].first && y == input[1].second){

            *cnt = arr[x][y];

            while(!q.empty()){
                q.pop();
            }
            break;
        }
        
        // 반복문 돌며 이동 가능 조합 탐색
        for(int i = 0; i < 8; i++){
            newX = x + moveX[i];
            newY = y + moveY[i];
            
            if(newX >= 0 && newX < n && newY >= 0 && newY < n){
                if(visited[newX][newY] == false){
                    visited[newX][newY] = true; // 신규 방문 -> 방문 표시 (false to true)
                    arr[newX][newY] = arr[x][y] + 1;
                    q.push(make_pair(newX, newY)); // 위치 업데이트해서 큐에 push (push "updated postion")
                }
            }
        }
        // 도착할 수 없는 위치 -> -1 출력 (if the destination is unreachable, output -1)
        *cnt = -1;
    }
}
 
int main(int argc, char * argv[]) {
    FILE *inputFile = fopen(argv[1], "r");
    if(inputFile == NULL)
        printf("ERROR\n");

    int size;
    int startX, startY, finalX, finalY;

    fscanf(inputFile, "%d", size);
    fscanf(inputFile, "%d %d", &startX, &startY);
    fscanf(inputFile, "%d %d", &finalX, &finalY);
    fclose(inputFile);

    // input(0) : 출발지(start position), input(1) : 도착지(final position)
    pair<int, int> input[2];

    input[0].first = startX;
    input[0].second = startY;
    input[1].first = finalX;
    input[1].second = finalY;

    int cnt=0; // to count the number of Kight's move
    int *ptr =&cnt;
    BFS(input, size, ptr);

    FILE *outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%d", cnt);
    fclose(outputFile);

    return 0;
}