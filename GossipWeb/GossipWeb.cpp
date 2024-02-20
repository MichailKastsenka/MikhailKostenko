// GossipWeb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 300001

std::vector<int> pr, g[MAXN * 10];
int lp[MAXN], rast[MAXN * 10], pred[MAXN * 10];

void Sieve()
{
    for (int i = 2; i <= MAXN; i++) // The Sieve of Eratosthenes with O(MAXN) time
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && pr[j] * i <= MAXN; j++)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}
int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    Sieve();
    int n, s, t;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> t;
        while (t > 1) // Create graph
        {
            g[i + MAXN].push_back(lp[t]);
            g[lp[t]].push_back(i + MAXN);
            t /= lp[t];
        }
    }
    std::cin >> s >> t;
    s--; t--;
    std::fill(rast, rast + MAXN * 10, INT_MAX);
    rast[s + MAXN] = 1;
    std::queue<int> q;
    q.push(s + MAXN);
    while (!q.empty())  // breadth find search
    {
        int v = q.front();
        q.pop();
        for (auto& to : g[v])
            if (rast[to] == INT_MAX)
            {
                rast[to] = rast[v] + v / MAXN;
                pred[to] = v;
                q.push(to);
            }
    }
    t += MAXN;
    if (rast[t] == INT_MAX) std::cout << -1;
    else
    {
        std::cout << rast[t] << '\n';
        std::vector <int> ans;
        do
        {
            if (t >= MAXN) ans.push_back(t - MAXN + 1);
            t = pred[t];
        } while (t);
        for (int i = ans.size() - 1; i >= 0; i--)
        {
            std::cout << ans[i] << ' ';
        }
    }
    return 0;
}
