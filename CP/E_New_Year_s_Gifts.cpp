#include <bits/stdc++.h>
using namespace std;

struct FriendData
{
    int id;
    int x;
    long long y, z;
    long long diff;
    int deadline;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        long long k;
        cin >> n >> m >> k;

        vector<long long> boxes(m);
        for (int i = 0; i < m; i++)
        {
            cin >> boxes[i];
        }
        sort(boxes.rbegin(), boxes.rend());

        vector<FriendData> friends(n);
        long long sum_y = 0;

        for (int i = 0; i < n; i++)
        {
            friends[i].id = i;
            cin >> friends[i].x >> friends[i].y >> friends[i].z;
            friends[i].diff = friends[i].z - friends[i].y;
            sum_y += friends[i].y;
        }

        if (sum_y > k)
        {
            cout << 0 << '\n';
            continue;
        }

        long long rem_budget = k - sum_y;

        vector<vector<int>> by_deadline(m);

        for (int i = 0; i < n; i++)
        {
            int low = 0, high = m - 1;
            int pos = -1;

            while (low <= high)
            {
                int mid = (low + high) / 2;
                if (boxes[mid] >= friends[i].x)
                {
                    pos = mid;
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }

            friends[i].deadline = pos;
            if (pos != -1)
            {
                by_deadline[pos].push_back(i);
            }
        }

        priority_queue<pair<long long, int>> pq;
        vector<bool> used(n, false);
        int boxed = 0;

        for (int i = m - 1; i >= 0; i--)
        {
            for (int idx : by_deadline[i])
            {
                pq.push({friends[idx].diff, idx});
            }
            if (!pq.empty())
            {
                pair<long long, int> top = pq.top();
                pq.pop();
                used[top.second] = true;
                boxed++;
            }
        }

        vector<long long> costs;
        for (int i = 0; i < n; i++)
        {
            if (!used[i])
            {
                costs.push_back(friends[i].diff);
            }
        }

        sort(costs.begin(), costs.end());

        int answer = boxed;
        for (long long c : costs)
        {
            if (rem_budget >= c)
            {
                rem_budget -= c;
                answer++;
            }
            else
            {
                break;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
