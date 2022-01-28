#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)

bool A[37][37];

void setup() {
	rep(i, 37)rep(j, 37)A[i][j] = false;
	rep(i, 21) {
		if (i % 7 == 6) {
			int p[7] = { -9,-8,-7,-2,-1,0,7 };
			rep(j, 7) {
				int k = i + p[j];
				if (k > 0) {
					A[i][k] = true;
				}
			}
		}
		else if (i == 5 || i == 12 || i == 19) {
			int p[7] = { -9,-7,-2,0,1,7,8 };
			int q[7] = { -1,-1,0,0,0,1,1 };
			rep(j, 7) {
				int k = i + p[j];
				if (i / 7 + q[j] == k / 7) {
					A[i][k] = true;
				}
			}
		}
		else {
			int p[7] = { -9,-7,-2,0,2,7,9 };
			int q[7] = { -1,-1,0,0,0,1,1 };
			rep(j, 7) {
				int k = i + p[j];
				if (k >= 0 && i / 7 + q[j] == k / 7) {
					A[i][k] = true;
				}
			}
		}
	}
	for (int i = 21; i < 26; i++) {
		int p[7] = { -9,-7,-2,0,2,5,7 };
		int q[7] = { -1,-1,0,0,0,1,1 };
		rep(j, 7) {
			int k = i + p[j];
			if (i / 7 + q[j] == k / 7) {
				A[i][k] = true;
			}
		}
	}
	int tmp[7] = { 17,19,24,26,27,31,32 };
	rep(i, 7)A[26][tmp[i]] = true;
	int tmp1[7] = { 18,19,20,25,26,27,32 };
	rep(i, 7)A[27][tmp1[i]] = true;
	int tmp2[5] = { 21,23,28,30,33 };
	rep(i, 5)A[28][tmp2[i]] = A[29][tmp2[i] + 1] = true;
	int tmp3[7] = { 23,25,28,30,32,33,35 };
	rep(i, 7)A[30][tmp3[i]] = true;
	int tmp4[7] = { 24,26,29,31,32,34,35 };
	rep(i, 7)A[31][tmp4[i]] = true;
	int tmp0[7] = { 25, 26, 27, 30, 31, 32, 35 };
	rep(i, 7)A[32][tmp0[i]] = true;
	int tmp5[5] = { 28,30,33,35,36 };
	rep(i, 5)A[33][tmp5[i]] = true;
	int tmp6[5] = { 29,31,34,35,36 };
	rep(i, 5)A[34][tmp6[i]] = true;
	int tmp7[7] = { 30,31,32,33,34,35,36 };
	rep(i, 7)A[35][tmp7[i]] = true;
	int tmp8[4] = { 33,34,35,36 };
	rep(i, 4)A[36][tmp8[i]] = true;
	return;
}

int main() {
	setup();

	int n;
	cin >> n;
	vector<int>a(n);
	for (auto& i : a)cin >> i;
	bool B[37][38];
	rep(i, 37)rep(j, 37)B[i][j] = A[i][j];
	rep(i, 37)B[i][37] = false;
	for (auto i : a)B[i][37] = true;
	vector<int>gomi;

	rep(i, 37) {
		if (!B[i][i]) {
			for (int j = i + 1; j < 37; j++) {
				if (B[j][i]) {
					rep(k, 38)swap(B[i][k], B[j][k]);
					break;
				}
				if (j == 36) {
					gomi.push_back(i);
				}
			}
		}
		rep(j, 37) {
			if (j != i && B[j][i]) {
				rep(k, 38) {
					B[j][k] ^= B[i][k];
				}
			}
		}
	}
	//26,31,34が残る
	for (auto i : gomi) {
		if (B[i][37]) {
			cout << i << "のせいで不能" << endl;
		}
	}
	int size = 100;
	vector<int>ans;
	rep(i, 8) {
		vector<int>cnt;
		if (i & 1)cnt.push_back(26);
		if (i & 2)cnt.push_back(31);
		if (i & 4)cnt.push_back(34);
		rep(j, 37) {
			bool tmp = false;
			if (i & 1 && B[j][26])tmp ^= true;
			if (i & 2 && B[j][31])tmp ^= true;
			if (i & 4 && B[j][34])tmp ^= true;
			if (tmp ^ B[j][37])cnt.push_back(j);
		}
		if (size > cnt.size()) {
			size = cnt.size();
			ans.assign(cnt.size(), 0);
			rep(i, cnt.size())ans[i] = cnt[i];
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (auto i : ans)cout << i << " ";
	return 0;
}