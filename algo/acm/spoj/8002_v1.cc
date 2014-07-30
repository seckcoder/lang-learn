#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

long long *tree, *flag;

void update(int index, int start, int end, int& from, int& to, long long val) {
	if (to < start || from > end)
		return;
	if (from <= start && to >= end) {
		tree[index] += ((long long) (end - start + 1)) * val;
		flag[index] += val;
	} else {
		int mid = (end + start) / 2;
		tree[index * 2 + 1] += ((long long) (mid - start + 1)) * flag[index];
		tree[index * 2 + 2] += ((long long) (end - mid)) * flag[index];
		flag[2 * index + 1] += flag[index];
		flag[2 * index + 2] += flag[index];
		flag[index] = 0;
		update(2 * index + 1, start, mid, from, to, val);
		update(2 * index + 2, mid + 1, end, from, to, val);
		tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
	}
}

long long query(int index, int start, int end, int& from, int& to) {
	if (to < start || from > end)
		return 0;
	if (from <= start && to >= end) {
		return tree[index];
	} else {
		int mid = (end + start) / 2;
		tree[2 * index + 1] += ((long long) (mid - start + 1)) * flag[index];
		tree[2 * index + 2] += ((long long) (end - mid)) * flag[index];
		flag[2 * index + 1] += flag[index];
		flag[2 * index + 2] += flag[index];
		flag[index] = 0;
		return query(2 * index + 1, start, mid, from, to)
				+ query(2 * index + 2, mid + 1, end, from, to);
	}
}

void get() {
	int cases;
	scanf("%d", &cases);
	while (cases--) {
		int size, queries;
		scanf("%d%d", &size, &queries);
		int length = size * 4;
		tree = new long long[length];
		flag = new long long[length];
		for (int i = 0; i < length; i++)
			flag[i] = tree[i] = 0;
		while (queries--) {
			int type;
			scanf("%d", &type);
			if (type == 0) {
				int from = 0, to = 0, val;
				scanf("%d%d%d", &from, &to, &val);
				from--, to--;
				update(0, 0, size - 1, from, to, val);
			} else {
				int from = 0, to = 0;
				scanf("%d%d", &from, &to);
				from--, to--;
				long long res = query(0, 0, size - 1, from, to);
				cout << res << endl;
			}
		}
		free(flag);
		free(tree);
	}
}

int main() {
	get();
	return 0;
}
