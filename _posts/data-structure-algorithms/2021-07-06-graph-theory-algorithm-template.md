---
layout: post
title:  "Graph-theory algorithm template"
date:   2021-07-06 11:09:40 +0800
categories: algorithm
---



### Step 1. 建图 + DFS/BFS 

[P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000 + 5;

struct Edge{
    int to, nxt;
} e[maxn * 10];
int head[maxn], tot, vst[maxn];
vector<pair<int, int> > tmp;

bool cmp(pair<int, int> x, pair<int, int> y){  //排序规则
	if(x.first == y.first)  //v相同按u排序
	return x.second > y.second;
	else return x.first > y.first;  //否则按v从大到小排序
}

void add(int u, int v){
    e[++tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}

void bfs(int rt){
    queue<int> q;
    q.push(rt);
    vst[rt] = 1;
    while (!q.empty()){
        int u = q.front();
        cout << u << " ";
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            int v = e[i].to;
            if (!vst[v]){
                q.push(v);
                vst[v] = 1;
            } 
        }    
        q.pop();
    }
}

void dfs(int rt){
    cout << rt << " ";
    vst[rt] = 1;
    for (int i = head[rt]; i != -1; i = e[i].nxt) {
        int v = e[i].to;
        if (!vst[v]){
            //vst[v] = 1;
            dfs(v);
        } 
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    int m, n;
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        tmp.push_back(make_pair(u, v));
    }
    sort(tmp.begin(), tmp.end(), cmp);
    for (int i = 0; i < m; ++i) {
        add(tmp[i].first, tmp[i].second);
    }
    dfs(1);
    cout << endl;
    memset(vst, 0, sizeof(vst));
    bfs(1);
    return 0;
}
```



### Step 2. 建图 + 拓扑排序 

[P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)

```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5005;
const int mod = 80112002;

struct Edge{
    int to, nxt;
}e[maxn*100];
int head[maxn], tot, ans, indegree[maxn], cnt[maxn];

void add(int u, int v){
    e[++tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}

void topo_sort(int n){
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            cnt[i] = 1;
        }
    }
    while (!q.empty()){
        int u = q.front();
        q.pop();
        if (head[u] == -1) ans = (ans + cnt[u]) % mod;
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            int v = e[i].to;
            cnt[v] = (cnt[v] + cnt[u]) % mod;
            indegree[v]--;
            if (indegree[v] == 0){
                q.push(v);
            }
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    int n, m, u, v;
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        add(u, v);
        indegree[v]++;
    }
    topo_sort(n);
    cout << ans << endl;
    return 0;
}
```

