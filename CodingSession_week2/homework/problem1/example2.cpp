#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>
 
using namespace std;
 
 
int bfs(pair<int, int> input[], int n){
  queue<pair<int, int>> q;
  int dp[300][300];
  for(int i=0; i<300; i++)
    for(int j=0; j<300; j++)
        dp[i][j]=-1;
        
  int count=0;
  int kx = input[0].first;
  int ky = input[0].second;
  q.push({kx, ky});
  dp[input[0].first][input[0].second]=0;
//   printf("start a,b = %d, %d\n", input[0].first, input[0].second);
  while(count==0 || q.size() > 1 ){
    int a = q.front().first;
    int b = q.front().second;
    //printf("a,b = %d, %d\n",a,b);
    q.pop();
    if(a==input[1].first && b==input[1].second){
        //printf("return !!! : %d=%d, %d=%d\n",a, input[1].first,b,input[1].second);
        if(count==0)
            return count;
        else return count-1;
    }
    if(a==kx && b == ky){
        count++;
        q.push({kx, ky});
    }        
    //printf("count : %d\n", count);
    // 말이동 가능 한 자리면 이동
    // 1.  경로에 대해 모두 고려하는 if문 8개 만들기 or for문으로 구조화 시키기 고민해보자
    // 2. 고려하면서 dp에 저장하기
    // 3. 현재위치가 도착위치면 count 를 리턴한다.
    for(int i=0; i<2; i++){ // i<2 를 i>2 라고 해서 함수가 끊기고리턴값이 쓰레기값으로 봔환되어 디버깅이 어려웠음
      for(int j=0; j<2; j++){
        for(int k=0; k<2; k++){
            //printf("i:%d, j:%d, k:%d\n", i, j ,k);
          int x=0,y=0,X=0,Y=0;
          if(i==0){
            x=1;
            y=2;
          }else{
            x=2;
            y=1;
          }
          if(j==0) x = abs(x);
          if(j==1 && x > 0) x = -x;
          if(k==0) y = abs(y);
          if(k==1 && y > 0) y = -y;
          X = x+a;
          Y = y+b;
          
          if(X >= 0 && X < n && Y >= 0 && Y < n){
              if(dp[X][Y]==-1){ // push하는 거를 if문 안에 넣지 않아서 해당범위에 있는 모든 좌표들이 푸쉬가 되었다. 디버깅 
                dp[X][Y]=count;
                //printf("dp[%d][%d] : %d\n", X,Y,dp[X][Y]);
                q.push({X,Y});
              }
          }
        }
      }
    }
  }
}
 
int main(){

    int n; cin >> n; // 체스판 length
    pair<int, int> input[2];

    // queue<pair<int, int>> q;

    // for(int i=0; i<2; i++){
    //     int a,b; cin >> a >> b;
    //     input[i].first = a;
    //     input[i].second = b;
    // }

    printf("%d\n", bfs(input, n));
}
