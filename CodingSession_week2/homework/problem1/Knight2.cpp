// https://tooo1.tistory.com/171
// https://100100e.tistory.com/82
// https://yabmoons.tistory.com/28

#include<iostream>
#include<cstring>
#include<queue>
 
#define MAX 20
using namespace std;
 
int l;
bool Visit[MAX][MAX];
 
int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
 
pair<int, int> Start, End;
 
void Initialize()
{
    memset(Visit, false, sizeof(Visit));
}
 
void Input()
{
    cin >> l;
    cin >> Start.first >> Start.second;
    cin >> End.first >> End.second;
}
 
void BFS(int a, int b)
{
    queue<pair<pair<int, int>, int >> Q;
    Q.push(make_pair(make_pair(a, b), 0));
    Visit[a][b] = true;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int Cnt = Q.front().second;
        Q.pop();
 
        if (x == End.first && y == End.second)
        {
            cout << Cnt << endl;
            return;
        }
 
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && ny >= 0 && nx < l && ny < l)
            {
                if (Visit[nx][ny] == false)
                {
                    Visit[nx][ny] = true;
                    Q.push(make_pair(make_pair(nx, ny), Cnt + 1));
                }
            }
        }
    }
}
 
void Solution()
{
    BFS(Start.first, Start.second);
}
 
void Solve()
{
    int Tc;
    cin >> Tc;
    for (int T = 1; T <= Tc; T++)
    {
        Initialize();
        Input();
        Solution();
    }
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}

