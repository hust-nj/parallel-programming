# include <bits/stdc++.h>
using namespace std;
namespace aka{
vector<vector<int> > solveAkari(vector<vector<int> > & g);
}

void checkAkari(vector<vector<int> > & g, vector<vector<int> > & ans);
void displayAkari(vector<vector<int> > & ans);

int main ()
{
    int n, m, tmp;
    cin >> n >> m;
    vector<vector<int> > g;
    for (int i = 1; i <= n; ++i) {
        g.push_back(vector<int>());
        for (int j = 1; j <= m; ++j) {
            cin >> tmp;
            g[i-1].push_back(tmp);
        }
    }
    vector<vector<int> > ans = aka::solveAkari(g);
    checkAkari(g, ans);
    return 0;
}

void checkAkari(vector<vector<int> > & g, vector<vector<int> > & ans)
{
    int n = (int)g.size(), m = (int)g[0].size();
    if (n != (int)ans.size() || m != (int)ans[0].size()) {
        cout << "The original size does not match!" << endl;
        displayAkari(ans);
        return ;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] >= -1 && g[i][j] <= 4) {
                if (ans[i][j] != g[i][j]) {
                    cout << "The original picture does not match the black grid!" << endl;
                    displayAkari(ans);
                    return ;
                }
            }
            else {
                if (ans[i][j] >= -1 && ans[i][j] <= 4) {
                    cout << "The original picture does not match the black grid!" << endl;
                    displayAkari(ans);
                    return ;
                }
            }
        }
    }
    int ps[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (ans[i][j] >= 0 && ans[i][j] <= 4) {
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    int dx = i + ps[k][0], dy = j + ps[k][1];
                    if (dx >= 0 && dx < n && dy >= 0 && dy < m && ans[dx][dy] == 5) ++cnt;
                }
                if (cnt != ans[i][j]) {
                    cout << "The number of lights around the black grid does not match the number!" << endl;
                    displayAkari(ans);
                    return ;
                }
            }
            else if (ans[i][j] == 5) {
                for (int k = i + 1; k < n; ++k) {
                    if (ans[k][j] >= -1 && ans[k][j] <= 4) break;
                    if (ans[k][j] == 5) {
                        cout << "Two lights shine on each other!" << endl;
                        displayAkari(ans);
                        return ;
                    }
                }
                for (int k = j + 1; k < m; ++k) {
                    if (ans[i][k] >= -1 && ans[i][k] <= 4) break;
                    if (ans[i][k] == 5) {
                        cout << "Two lights shine on each other!" << endl;
                        displayAkari(ans);
                        return ;
                    }
                }
            }
            else if (ans[i][j] == -2) {
                bool flag = true;
                for (int k = i + 1; k < n; ++k) {
                    if (ans[k][j] >= -1 && ans[k][j] <= 4) break;
                    if (ans[k][j] == 5) flag = false;
                }
                for (int k = i - 1; k >= 0; --k) {
                    if (ans[k][j] >= -1 && ans[k][j] <= 4) break;
                    if (ans[k][j] == 5) flag = false;
                }
                for (int k = j + 1; k < m; ++k) {
                    if (ans[i][k] >= -1 && ans[i][k] <= 4) break;
                    if (ans[i][k] == 5) flag = false;
                }
                for (int k = j - 1; k >= 0; --k) {
                    if (ans[i][k] >= -1 && ans[i][k] <= 4) break;
                    if (ans[i][k] == 5) flag = false;
                }
                if (flag == true) {
                    cout << "There's a place where all the lights don't shine!" << endl;
                    displayAkari(ans);
                    return ;
                }
            }
        }
    }
    cout << "The answer is right!";
}

void displayAkari(vector<vector<int> > & ans)
{
    printf("your magic matrix is following: \n");
    int n = ans.size(), m = ans[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%4d", ans[i][j]);
        }
        printf("\n");
    }
}

#include<cstring>
using namespace std;

namespace aka{
//请在命名空间内编写代码，否则后果自负

#define TO(x) (x += 8)
#define FROM(x) (x -= 8)
#define CHECK(c) (c.x >= 0 && c.x < n && c.y >= 0 && c.y < m)
struct Cord{
    int x;
    int y;
    Cord(int x, int y): x(x),y(y){ }
};

int n, m;
int sum;
int lightsum;
vector<Cord> c4, c3, c2, c1, c0;
vector<vector<int> > ans;
vector<Cord> blackAside;
vector<Cord> noblackAside;
const int ref[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};
inline void radiate(const Cord &c)
{
    for (int i = c.x  - 1; i >= 0 && !(-1 <= ans[i][c.y] && ans[i][c.y] <= 4); --i)
    {
        if (ans[i][c.y] == -2) lightsum--;
        TO(ans[i][c.y]);
    }
    for (int i = c.x + 1; i <= n-1 && !(-1 <= ans[i][c.y] && ans[i][c.y] <= 4); ++i)
    {
        if (ans[i][c.y] == -2) lightsum--;
        TO(ans[i][c.y]);
    }
    for (int j = c.y - 1; j >= 0 && !(-1 <= ans[c.x][j] && ans[c.x][j] <= 4); --j)
    {
        if (ans[c.x][j] == -2) lightsum--;
        TO(ans[c.x][j]);
    }
    for (int j = c.y + 1; j <= m-1 && !(-1 <= ans[c.x][j] && ans[c.x][j] <= 4); ++j)
    {
        if (ans[c.x][j] == -2) lightsum--;
        TO(ans[c.x][j]);
    }
}

inline void unradiate(const Cord &c)
{
    for (int i = c.x  - 1; i >= 0 && !(-1 <= ans[i][c.y] && ans[i][c.y] <= 4); --i)
    {
        FROM(ans[i][c.y]);
        if (ans[i][c.y] == -2) lightsum++;
    }
    for (int i = c.x + 1; i <= n-1 && !(-1 <= ans[i][c.y] && ans[i][c.y] <= 4); ++i)
    {
        FROM(ans[i][c.y]);
        if (ans[i][c.y] == -2) lightsum++;
    }
    for (int j = c.y - 1; j >= 0 && !(-1 <= ans[c.x][j] && ans[c.x][j] <= 4); --j)
    {
        FROM(ans[c.x][j]);
        if (ans[c.x][j] == -2) lightsum++;
    }
    for (int j = c.y + 1; j <= m-1 && !(-1 <= ans[c.x][j] && ans[c.x][j] <= 4); ++j)
    {
        FROM(ans[c.x][j]);
        if (ans[c.x][j] == -2) lightsum++;
    }
}


int vis[15][15];
void addBlackAside(vector<Cord> & cv)
{
    for (vector<Cord>::iterator it = cv.begin(); it != cv.end(); ++it)
    {
        Cord &c = *it;
        for (int k = 0; k < 4; ++k)
        {
            Cord side = Cord(c.x+ref[k][0], c.y+ref[k][1]);
            if (CHECK(side) && ans[side.x][side.y] == -2 && vis[side.x][side.y] == 0){
                // printf("(%d, %d)\n", c.x, c.y);
                blackAside.push_back(Cord(side.x, side.y));
                vis[side.x][side.y] = 1;
            }
        }
    }
    
}


bool dfsNoBlack(int v)
{
    // printf("noblack %d\n", v);
    Cord &c = noblackAside[v];
    if (ans[c.x][c.y] == -2){
        ans[c.x][c.y] = 5;
        lightsum--;
        radiate(c);
    } else {
        return false;
    }

    bool flag = false;
    if (lightsum == 0){
        return true;
    } else {
        for (int i = v+1; i < noblackAside.size(); ++i)
        {
            flag |= dfsNoBlack(i);
        }  
    }
    if(flag == false) { // 回退
        ans[c.x][c.y] = -2;
        lightsum++;
        unradiate(c);
        return false;
    }
    return true;
}

bool dfsBlack(int v)
{
    // printf("black %d\n", v);
    Cord &c = blackAside[v];
    if (ans[c.x][c.y] == -2){
        for (int k = 0; k < 4; ++k)
        {
            Cord cc = Cord(c.x+ref[k][0], c.y+ref[k][1]);
            if (CHECK(cc) && ans[cc.x][cc.y] == 0){
                return false;
            }
        }
        for (int k = 0; k < 4; ++k)
        {
            Cord cc = Cord(c.x+ref[k][0], c.y+ref[k][1]);
            if (CHECK(cc) && ans[cc.x][cc.y] >= 1 && ans[cc.x][cc.y] <= 4){
                ans[cc.x][cc.y] -= 1;
                sum--;
            }
        }
        ans[c.x][c.y] = 5;
        lightsum--;
        radiate(c);
    } else {
        return false;
    }
    bool flag = false;
    if(sum == 0) {
        for (int i = 0; i < noblackAside.size(); ++i)
            flag |= dfsNoBlack(i);
    } else {
        for (int i = v + 1; i < blackAside.size(); ++i)
            flag |= dfsBlack(i);
    }
    if (flag == false){ // 如果失败退回
        for (int k = 0; k < 4; ++k)
        {
            Cord cc = Cord(c.x+ref[k][0], c.y+ref[k][1]);
            if (CHECK(cc) && ans[cc.x][cc.y] >= 0 && ans[cc.x][cc.y] <= 4){
                ans[cc.x][cc.y] += 1;
                sum++;
            }
        }
        ans[c.x][c.y] = -2;
        lightsum++;
        unradiate(c);
        return false;
    }
    return true;
}

inline void backup(vector<Cord> &cv, vector<vector<int> > &ans, int num)
{
    for(vector<Cord>::iterator it = cv.begin(); it != cv.end(); ++it)
    {
        ans[it->x][it->y] = num;
    }
}

vector<vector<int> > solveAkari(vector<vector<int> > & g)
{
    // 请在此函数内返回最后求得的结果
    ans = g;
    n = (int)g.size(); m = (int)g[0].size();
    lightsum = n * m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (g[i][j] == 4){
                c4.push_back(Cord(i,j));
                vis[i][j] = 1;
                sum += 4;
                lightsum--;
            } else if (g[i][j] == 3){
                c3.push_back(Cord(i,j));
                vis[i][j] = 1;
                sum += 3;
                lightsum--;
            } else if (g[i][j] == 2){
                c2.push_back(Cord(i, j));
                vis[i][j] = 1;
                sum += 2;
                lightsum--;
            } else if (g[i][j] == 1){
                c1.push_back(Cord(i,j));
                vis[i][j] = 1;
                sum += 1;
                lightsum--;
            } else if (g[i][j] == 0){
                c0.push_back(Cord(i,j));
                vis[i][j] = 1;
                lightsum--;              
            } else if (g[i][j] == -1) {
                vis[i][j] = 1;
                lightsum--;
            }
        }

    addBlackAside(c4);
    addBlackAside(c3);
    addBlackAside(c2);
    addBlackAside(c1);
    addBlackAside(c0);
    

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (vis[i][j] == 0)
            {
                noblackAside.push_back(Cord(i,j));
            }

    if(sum == 0) {
        for (int i = 0; i < noblackAside.size(); ++i)
            if (dfsNoBlack(i)) break;
    } else {
        for (int i = 0; i < blackAside.size(); ++i)
            if (dfsBlack(i)) break;
    }

    backup(c4, ans, 4);
    backup(c3, ans, 3);
    backup(c2, ans, 2);
    backup(c1, ans, 1);
    return ans;
}
}