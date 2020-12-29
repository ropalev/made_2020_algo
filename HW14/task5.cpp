#include <bits/stdc++.h>


typedef long double ld;
typedef int64_t ll;
typedef uint64_t ull;
typedef int32_t int32;

using namespace std;


vector <ll> power31, power37;
vector <string> strings;

void fill_power(int32 n) {
	power31.resize(n + 1);
	int32 p31 = 31;
	power31[0] = 1;
	for (int32 i = 1; i <= n; i++) {
		power31[i] = power31[i - 1] * p31;
	}

}

unordered_map<ll, int32> fill_hash(string &s, int length) {
	vector<pair <ll, int32> > hash31(s.size() - length + 1);
	for (int32 i = 0; i < length; i++) {
		hash31[0].first = hash31[0].first * 31 + (s[i] - 'a' + 1);
	}
	for (int32 i = 1; i <= s.size() - length; i++) {
		hash31[i].first = (hash31[i - 1].first - (s[i - 1] - 'a' + 1) * power31[length - 1]) * 31 + (s[i + length - 1] - 'a' + 1);
		hash31[i].second = i;
	}
	unordered_map<ll, int32> res(hash31.begin(), hash31.end());
	return res;
}

int32 maxima = 0;
unordered_map<ll, int32> answered;

bool check(ll length) {
	unordered_map<ll, int32> answer = fill_hash(strings[0], length);
	for (int32 i = 1; i < strings.size(); i++) {
		unordered_map<ll, int32> temp;
		unordered_map<ll, int32> temp2 = fill_hash(strings[i], length);
		for (auto it : temp2) {
			auto super_it = answer.find(it.first);
			if (super_it != answer.end()) {
				temp.insert(*super_it);
			}
		}
		swap(answer, temp);
	}
	return !answer.empty();
}

int main() {
	int32 k;
	cin >> k;
	strings.resize(k);
	for (int32 i = 0; i < k; i++) {
		cin >> strings[i];
	}
	sort(strings.begin(), strings.end(), [](const string & a, const string & b){return a.size() < b.size();});
	fill_power(strings.back().size() + 1);
	ll l = -1, r = strings.front().size() + 1, m;
	while (1 < r - l) {
		m = (r + l) / 2;
		if (check(m)) {
			l = m;
		} else {
			r = m;
		}
	}
	cout << strings[0].substr(answered.begin()->second, maxima) << '\n';
}