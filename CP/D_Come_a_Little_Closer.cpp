#include <bits/stdc++.h>
using namespace std;

int main() {
    long long t;
    cin >> t;
    while(t--) {
        long long n;
        cin >> n;
        vector<pair<long long, long long>> points(n);
        vector<long long> xs, ys;

        for (int i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
            xs.push_back(points[i].first);
            ys.push_back(points[i].second);
        }

        // Sort x and y coordinates
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        // Candidates for bounding box dimensions
        vector<long long> candidate_areas;

        // Case 1: move one point that determines min_x
        if (n > 1) {
            long long min_x = xs[1];
            long long max_x = xs[n - 1];
            long long min_y = ys[0];
            long long max_y = ys[n - 1];
            if(((max_x - min_x + 1) * (max_y - min_y + 1))==(n-1)){
                if((max_x - min_x + 1) >(max_y - min_y + 1)){
                    max_x++;
                }
                else{
                    max_y++;
                }
            }
            candidate_areas.push_back((max_x - min_x + 1) * (max_y - min_y + 1));
        }

        // Case 2: move one point that determines max_x
        if (n > 1) {
            long long min_x = xs[0];
            long long max_x = xs[n - 2];
            long long min_y = ys[0];
            long long max_y = ys[n - 1];
            if(((max_x - min_x + 1) * (max_y - min_y + 1))==(n-1)){
                if((max_x - min_x + 1) >(max_y - min_y + 1)){
                    max_x++;
                }
                else{
                    max_y++;
                }
            }
            candidate_areas.push_back((max_x - min_x + 1) * (max_y - min_y + 1));
        }

        // Case 3: move one point that determines min_y
        if (n > 1) {
            long long min_y = ys[1];
            long long max_y = ys[n - 1];
            long long min_x = xs[0];
            long long max_x = xs[n - 1];
            if(((max_x - min_x + 1) * (max_y - min_y + 1))==(n-1)){
                if((max_x - min_x + 1) >(max_y - min_y + 1)){
                    max_x++;
                }
                else{
                    max_y++;
                }
            }
            candidate_areas.push_back((max_x - min_x + 1) * (max_y - min_y + 1));
        }

        if (n > 1) {
            long long min_y = ys[0];
            long long max_y = ys[n - 2];
            long long min_x = xs[0];
            long long max_x = xs[n - 1];
            if(((max_x - min_x + 1) * (max_y - min_y + 1))==(n-1)){
                if((max_x - min_x + 1) >(max_y - min_y + 1)){
                    max_x++;
                }
                else{
                    max_y++;
                }
            }
            candidate_areas.push_back((max_x - min_x + 1) * (max_y - min_y + 1));
        }
        if (n == 1) {
            cout << 1 << endl;
        } else {
            long long ans = *min_element(candidate_areas.begin(), candidate_areas.end());
            cout << ans << endl;
        }
    }

    return 0;
}
