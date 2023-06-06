#include <bits/stdc++.h>

using namespace std;

int calcVal(vector<vector<int>>& mat) {
    int val = 0;
    for(int i = 0;  i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            val = val*10 + mat[i][j];
        }
    }
    return val;
}

vector<vector<int>> getMatrix(int val) {
    vector<vector<int>> mat(3, vector<int>(3));
    for(int i = 2; i >= 0; i--) {
        for(int j = 2; j >= 0; j--) {
            mat[i][j] = val%10;
            val /= 10;
        }
    }
    return mat;
}

int printSol(int val, unordered_map<int, vector<int>>& dp, bool toPrint) {
    int steps = 0;
    while(val != 123456789) {
        vector<int> state = dp[val];
        int dr = state[0], dc = state[1];

        if(toPrint) {
            cout << val << "\t---\t";
            if(dr == 1) {
                cout << " Move top piece ";
            } else if(dr == -1) {
                cout << " Move bottom piece";
            } else if(dc == 1) {
                cout << " Move left piece";
            } else if(dc == -1) {
                cout << " Move right piece";
            }
            cout << "\t--->\t" << val << endl;
        }

        val = state[2];
        steps++;
    }
    return steps;
}

void solve(int target, unordered_map<int, vector<int>>& dp) {
    int src = 123456789;
    unordered_set<int> vis;
    queue<int> q;
    q.push(src);
    dp[src] = {-1, 0, 0, 0};
    vis.insert(src);
    int d[] = {0, 1, 0, -1, 0};
    int state = q.front();
    while(!q.empty()) {
        state = q.front();
        q.pop();
        if(state == target) return;
        vector<int> res = {-1, 0, 0, INT_MAX};
        vector<vector<int>> mat = getMatrix(state);
        int r = -1, c = -1;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(mat[i][j] == 9) {
                    r = i; c = j;
                    break;
                }
            }
            if(r != -1) break;
        }
        for(int i = 0; i < 4; i++) {
            int R = r + d[i], C = c + d[i+1];
            if(R >= 0 && R < 3 && C >= 0 && C < 3) {
                swap(mat[r][c], mat[R][C]);
                int nextState = calcVal(mat);
                if(vis.find(nextState) == vis.end()) {
                    q.push(nextState);
                    dp[nextState] = {d[i], d[i+1], state};
                    vis.insert(nextState);
                }
                swap(mat[r][c], mat[R][C]);
            }
        }
    }
    // cout << state;
}

int main()
{
    int originalState;
    cin >> originalState;
    unordered_map<int, vector<int>> dp; // state => {dr, dc, nextState}
    solve(originalState, dp);
    printSol(originalState, dp, true);
    return 0;
}
