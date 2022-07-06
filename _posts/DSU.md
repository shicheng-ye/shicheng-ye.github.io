+++
banner = "banners/placeholder.png"
categories = ["Data Structure"]
date = "2020-10-19T13:39:46+02:00"
menu = ""
tags = []
title = "DSU"

+++



### Step 1. DSU简介

一个 DSU(Disjoint Set Union)数据结构可以用来维护图形连接组件的数据，并快速查询它们。有两种操作：

`① dsu.find(node x)`
找到元素 x 所在的集合的代表，该操作也可以用于判断两个元素是否位于同一个集合。

`② dsu.union(node x, node y)`
把元素 x 和元素 y 所在的集合合并，要求 x和 y 所在的集合不相交，如果相交则不合并。

为了实现这一点，我们跟踪父结点，它会记录同一连接节点中较小结点的所在的集合。如果结点是它自己的父结点，我们将其称为连接结点的领导者。



### Step 2. 代码实现


我们使用两种技术来提高运行时的复杂性：`路径压缩和按秩合并`。

路径压缩涉及将 find 函数中的 x=parent[x] 更改为 parent[x]=find(parent[x])。
按秩合并涉及到将发现的工作量平均分配给领导者。每当 dsu.union(x, y) 时，我们都有两个领导者 xr，yr，并且我们要选择是要 parent[x]=yr 还是 parent[y]=xr。我们选择有更多子节点的领导者作为领导者。

具体地说，rank 的含义是 x 的跟随者少于 2 ^ rank[x]，这个策略可以作为 dsu.find 中的递归循环可中的界限。

```
class DSU {
public:
	DSU(int size) {
        parent = new int[size];
        for (int i = 0; i < size; i++) parent[i] = i;
        rank = new int[size];
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unions(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) {
            return false;
        } else if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
private:
	int* parent;
    int* rank;
};
```



### Step 3. 例题应用

###### [684. 冗余连接(LeetCode)](https://leetcode-cn.com/problems/redundant-connection/)

在本问题中, 树指的是一个连通且无环的无向图。

输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。

返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。答案边 [u, v] 应满足相同的格式 u < v。

```
输入: [[1,2], [1,3], [2,3]]
输出: [2,3]
解释: 给定的无向图为:
  1
 / \
2 - 3
```

**Answer:**

```
class DSU{
	//...
}

class Solution {
public:
    int MAX_EDGE_VAL = 1000;

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DSU* dsu = new DSU(MAX_EDGE_VAL + 1);
        for (auto edge: edges) {
            if (!dsu->unions(edge[0], edge[1])) return edge;
        }
        return vector<int>();
    }
};
```

