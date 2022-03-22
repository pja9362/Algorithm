#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
 
int arr[21][21];
bool checked[21][21];
 
// int dx[8] = {1,2,2,1,-1,-2,-2,-1};
// int dy[8] = {2,1,-1,-2,-2,-1,1,2};
 
// int I;//체스판의 한 변의 길이
// queue<pair<int, int>> q;
// int srcX, srcY, dstX, dstY;

// a: 출발 x좌표, b: 출발 y좌표
void bfs(int a, int b, int *ptrX, int *ptrY, int size, int *dX, int *dY){
    queue<pair<int, int>> q;
    q.push(make_pair(a, b));
    checked[a][b] = true;
    while(!q.empty()){
        int x = q.front().first; 
        int y = q.front().second;
        q.pop();
        
        if(x == *dX && y == *dY){
            cout << arr[x][y] << '\n';
            // arr[x][y] : 이동횟수
            while(!q.empty()){
                q.pop();
            }
            break;
        }
        
        for(int i = 0; i < 8; i++){
            int nx = x + ptrX[i];
            int ny = y + ptrY[i];
            
            if(nx >= 0 && nx < size && ny >= 0 && ny < size){
                if(checked[nx][ny] == false){
                    checked[nx][ny] = true;
                    arr[nx][ny] = arr[x][y] + 1;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }
}
 
int main(int argc, const char * argv[]) {
    int arr[21][21];
    bool checked[21][21];

    // int (*ptrArr)[21] = arr;
    // bool (*ptrBool)[21] = checked;

    int I;
    int srcX, srcY, dstX, dstY;


    int dx[8] = {1,2,2,1,-1,-2,-2,-1};
    int dy[8] = {2,1,-1,-2,-2,-1,1,2};

    int *ptrX = dx;
    int *ptrY = dy;

    cin >> I; // 체스판의 크기
    // 좌표 순서대로 입력
    cin >> srcX >> srcY >> dstX >> dstY;

    int *ptrdX = &dstX;
    int *ptrdY = &dstY;

    bfs(srcX, srcY, ptrX, ptrY, I, ptrdX, ptrdY);

    // void* memset(void* ptr, int value, size_t num);

    memset(arr, 0, sizeof(arr));
    memset(checked, false, sizeof(checked));

    return 0;
}

// 백준 7562 : https://www.acmicpc.net/problem/7562
// https://sw-ko.tistory.com/137

// #include <iostream>
// #include <queue>
// #include <cstring>
// using namespace std;
 
// int arr[301][301];
// bool checked[301][301];
 
// int dx[8] = {1,2,2,1,-1,-2,-2,-1};
// int dy[8] = {2,1,-1,-2,-2,-1,1,2};
 
// int I;//체스판의 한 변의 길이
// queue<pair<int, int>> q;
// int srcX, srcY, dstX, dstY;
 
// void bfs(int a, int b){
//     q.push(make_pair(a, b));
//     checked[a][b] = true;
//     while(!q.empty()){
//         int x = q.front().first;
//         int y = q.front().second;
//         q.pop();
        
//         if(x == dstX && y == dstY){
//             cout << arr[x][y] << '\n';
            
//             while(!q.empty()){
//                 q.pop();
//             }
//             break;
//         }
        
//         for(int i = 0; i < 8; i++){
//             int nx = x + dx[i];
//             int ny = y + dy[i];
            
//             if(nx >= 0 && nx < I && ny >= 0 && ny < I){
//                 if(checked[nx][ny] == false){
//                     checked[nx][ny] = true;
//                     arr[nx][ny] = arr[x][y] + 1;
//                     q.push(make_pair(nx, ny));
//                 }
//             }
//         }
//     }
// }
 
// int main(int argc, const char * argv[]) {
//     int T;
//     cin >> T;
 
//     for(int i = 0; i < T; i++){
//         cin >> I;
//         cin >> srcX >> srcY >> dstX >> dstY;
//         bfs(srcX, srcY);
//         memset(arr, 0, sizeof(arr));
//         memset(checked, false, sizeof(checked));
//     }
//     return 0;
// }