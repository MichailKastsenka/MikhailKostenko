// SpidersOnTheTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define MAXN 400001

int last[MAXN];
std::vector<int> g[MAXN];

void dfs(int cur, int from = -1) {
    std::vector<int> ans;
    for (auto& to : g[cur])
    {
        if (to == from) continue;
        dfs(to, cur);
        if (last[to]) ans.push_back(last[to]);
    }
    if (ans.size() % 2)
    {
        if (last[cur]) // use current node for answer
        {
            last[cur] = 0;
            ans.push_back(cur);
        }
        else  // current node don't use now, try for parent answer
        {
            last[cur] = ans.back();
            ans.pop_back();
        }
    }
    for (int i = 0; i < ans.size(); i += 2)
        std::cout << ans[i] << ' ' << ans[i + 1] << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, q;
    std::cin >> n >> q;
    for (int i = 0; i < q; i++)
    {
        int v;
        std::cin >> v;
        last[v] = v;
    }
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        std::cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
    return 0;
}