#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
 
 
void bfs(pair<int, int> input[], int size){
    
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

            cout << arr[x][y] << '\n';
            
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
 
int main(int argc, const char * argv[]) {
    int n;
    // input(0) : 출발지, input(1) : 도착지
    pair<int, int> input[2];

    cin >> n; // 체스판 사이즈
    // cin >> srcX >> srcY >> dstX >> dstY;
    for(int i=0; i<2; i++){
        int x,y; cin >> x >> y;
        input[i].first = x;
        input[i].second = y;
    }

    bfs(input, n);


    return 0;
}