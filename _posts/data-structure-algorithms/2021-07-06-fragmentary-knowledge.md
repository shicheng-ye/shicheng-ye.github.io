---
layout: post
title:  "Fragmentary knowledge"
date:   2021-07-06 11:09:40 +0800
categories: others
---





## 杂记

+++



```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 200 * 1000 + 11;

int p[N];
int d[N];
vector<int> g[N];

void dfs(int v, int pr = -1, int dst = 0) {
	d[v] = dst;
	p[v] = pr;
	for (auto to : g[v]) {
		if (to != pr) {
			dfs(to, v, dst + 1);
		}
	}
}


int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		--x, --y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	
	dfs(0);
	set<pair<int, int>> st;
	for (int i = 0; i < n; ++i) {
		if (d[i] > 2) {
			st.insert(make_pair(-d[i], i));
		}
	}
	
	int ans = 0;
	while (!st.empty()) {
		int v = st.begin()->second;
		v = p[v];
		++ans;
		auto it = st.find(make_pair(-d[v], v));
		if (it != st.end()) {
			st.erase(it);
		}
		for (auto to : g[v]) {
			auto it = st.find(make_pair(-d[to], to));
			if (it != st.end()) {
				st.erase(it);
			}
		}
	}
	
	printf("%d\n", ans);
        system("pause");
}
```







### Memset

#### 简介

memset 函数是内存赋值函数，用来给某一块内存空间进行赋值的。

原型为 ：

```c++
void *memset(void *s, int v, size_t n);  
```

这里s可以是数组名，也可以是指向某一内在空间的指针；v为要填充的值；n为要填充的字节数； 

#### 应用

① 数组置0（通用）

```c++
memset(dp, 0, sizeof(dp));
```

② 无符号整数组置最值

即每个字节置为 0xff

```c++
memset(dp, 0xff, sizeof(dp));

```

③ 有符号整数置最值（memset能达到的最值）

```c++
memset(dp, 0x7f, sizeof(dp));
memset(arr,0x80,sizeof(arr)); //set int to -2139062144
```

④ 有符号整数置-1

即每个字节变成 0xff（-1补码）

```c++
memset(dp, -1, sizeof(dp));
memset(dp, 0xff, sizeof(dp));
```

⑤ Double置最值

```c++
memset(arr,0x7F,sizeof(arr)); //set double to 1.38242e+306
memset(arr,0xFE,sizeof(arr)); //set double to -5.31401e+303
```

---



### DP

[[198. House Robber](https://leetcode-cn.com/problems/house-robber/)](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

```c++
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
```

动态转移方程：

```c++
dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
// 若不抢这家，那么本次最大值为上次最大值；反之为上上次最大值＋这次
```



[746. Min Cost Climbing Stairs](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)

 ```c++
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
 ```

动态转移方程：

```c++
dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
// 到达i点有两种方案：要么从前一次过来，要么从前前一格过来
```



[53. Maximum Subarray](https://leetcode-cn.com/problems/maximum-subarray/)

```c++
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

动态转移方程：

```c++
dp[i] = (dp[i-1] > 0 ? dp[i-1] + nums[i] : nums[i])
//dp[i] 代表以元素 nums[i] 为结尾的连续子数组最大和。
```



[392. Is Subsequence](https://leetcode-cn.com/problems/is-subsequence/)

```c++
Input: s = "abc", t = "ahbgdc"
Output: true
```

动态转移方程：

```c++
dp[i] = (t[i] == s[dp[i-1]] ? dp[i-1]+1 : dp[i-1]);
// dp[i] 表示t的第i位已匹配至s的dp[i]位
```



#### 经典dp 0-1背包

给你一个可装载重量为`W`的背包和`N`个物品，每个物品有重量和价值两个属性。其中第`i`个物品的重量为`wt[i]`，价值为`val[i]`，现在让你用这个背包装物品，最多能装的价值是多少？

```c++
N = 3, W = 4
wt = [2, 1, 3]
val = [4, 2, 3]
```

`dp[i][w] `的定义如下：对于容量为`w`的背包，装`前i`个物品，可以装的最大价值。

① 若第i个物品的`wt[i] > w`，那么一定不会拿取。则容量为`w`的包装`前i`个物品可得到的价值则为容量为`w的`包装`前i-1`个物品可得到的价值，即`dp[i][w] = dp[i-1][w]`。

② 若第i个物品的`wt[i] <= w`，那么则有以下两种情况	

​	a.不拿。容量为`w`的包装`前i个`物品可得到的值则为容量为`w`的包装`前i-1`个物品可得到的价值，即`dp[i][w] = dp[i-1][w]。`

​	b.拿走。容量为`w`的包装`前i个`物品可得到的值则为容量为`w-wt[i]`的包装`前i-1`个物品可得到的价值+`第i项物品的价值`，即 `dp[i][w] = dp[i - 1][w - wt[i-1]] + val[i-1]`。

二者取最优解即可。

```c++
int knapsack(int W, int N, vector<int>& wt, vector<int>& val) {
    // vector 全填入 0，base case 已初始化
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - wt[i-1] < 0) {
                // 当前背包容量装不下，只能选择不装入背包
                dp[i][w] = dp[i - 1][w];
            } else {
                // 装入或者不装入背包，择优
                dp[i][w] = max(dp[i - 1][w - wt[i-1]] + val[i-1], 
                               dp[i - 1][w]);
            }
        }
    }

    return dp[N][W];
}
```

[P1048 采药](https://www.luogu.com.cn/problem/P1048)






