// #include <bits/stdc++.h>
// using namespace std;

// long long count_turns(long long h, long long d)
// {
//     if (d <= 0)
//         return 0;
//     else if (h <= 1)
//         return 1 + count_turns(h + 1, d);
//     else if (h <= 3)
//         return 2 * d - 1;
//     else
//     {
//         long long left = 0;
//         long long right = d;
//         long long ans = 0;
//         while (left <= right)
//         {
//             long long mid = (left + right) / 2;
//             long long max = (mid * (mid + 1) / 2) - 1;
//             if (max == 0)
//             {
//                 ans = mid;
//                 left = mid + 1;
//                 continue;
//             }
//             long long times = (h - 2) / max;
//             if (times * mid >= d)
//             {
//                 left = mid + 1;
//                 ans = mid;
//             }
//             else
//                 right = mid - 1;
//         }
//         ans = ans + 1;
//         if (ans < 2)
//         {
//             long long div = (h - 2) / 2;
//             d -= (2 * div);
//             return 3 * div + count_turns(h - (2 * div), d);
//         }
//         else
//         {
//             long long a = (h - 2) / ((ans * (ans + 1)) / 2 - 1);
//             d -= a * ans;
//             if (d == 0)
//                 return (ans + 1) * a - 1;
//             return (ans + 1) * a + count_turns(h - a * ((ans * (ans + 1)) / 2 - 1), d);
//         }
//     }
// }
// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     long long t;
//     cin >> t;
//     while (t--)
//     {
//         long long h, d;
//         cin >> h >> d;
//         long long count = 0;
//         long long answer = count_turns(h, d);
//         cout << answer << endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll testCases;
    cin >> testCases;
    while (testCases--)
    {
        ll initialHealth, distanceToTravel;
        cin >> initialHealth >> distanceToTravel;

        ll minRestsNeeded = 1e9;
        ll left = 0, right = distanceToTravel + 1;

        while (left <= right)
        {
            ll rests = (left + right) / 2;

            ll movementSegments = rests + 1;
            ll totalHealthBudget = rests + initialHealth;

            if (movementSegments > distanceToTravel)
            {
                right = rests - 1;
                continue;
            }

            ll maxSegmentLength = distanceToTravel / movementSegments + (distanceToTravel % movementSegments != 0);
            ll shortSegmentCount = maxSegmentLength * movementSegments - distanceToTravel;
            ll longSegmentCount = movementSegments - shortSegmentCount;

            ll damageFromShortSegment = maxSegmentLength * (maxSegmentLength - 1) / 2;
            ll damageFromLongSegment = maxSegmentLength * (maxSegmentLength + 1) / 2;

            ll totalDamage = shortSegmentCount * damageFromShortSegment + longSegmentCount * damageFromLongSegment;

            if (totalDamage < totalHealthBudget)
            {
                minRestsNeeded = min(minRestsNeeded, rests);
                right = rests - 1;
            }
            else
            {
                left = rests + 1;
            }
        }

        ll totalTurns = minRestsNeeded + distanceToTravel;
        ll simpleStrategyTurns = 2 * distanceToTravel;

        cout << min(totalTurns, simpleStrategyTurns) << endl;
    }
}