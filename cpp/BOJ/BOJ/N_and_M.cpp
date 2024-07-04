// 15649 (1)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>

int N, M;
int answer[8];
bool check[8];

void solve(int depth = 0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << answer[i] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = 0; i < N; i++) {
		if (check[i]) continue;
		answer[depth] = i + 1;
		check[i] = true;
		solve(depth + 1);
		check[i] = false;
		
	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;

	solve();

}

// 15650 (2)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>

int N, M;
int answer[8];

void solve(int depth = 0, int value=1) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << answer[i] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = value; i <= N; i++) {
		answer[depth] = i;
		solve(depth + 1, i + 1);
		
	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;

	solve();

}

// 15651 (3)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>

int N, M;
int answer[8];

void solve(int depth = 0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << answer[i] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = 0; i < N; i++) {
		answer[depth] = i + 1;
		solve(depth + 1);

	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;

	solve();

}

// 15652 (4)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>

int N, M;
int answer[8];

void solve(int depth = 0, int value=1) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << answer[i] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = value; i <= N; i++) {
		answer[depth] = i;
		solve(depth + 1, i);
		
	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;

	solve();

}


// 15654 (5)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>
#include <algorithm>

int N, M;
int answer[8], value[8];
bool check[8];

void solve(int depth = 0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << value[answer[i]] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = 0; i < N; i++) {
		if (check[i]) continue;
		answer[depth] = i;
		check[i] = true;
		solve(depth + 1);
		check[i] = false;
		
	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
		std::cin >> value[i];

	std::sort(std::begin(value), std::begin(value) + N);

	solve();

}


// 15655 (6)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>
#include <algorithm>

int N, M;
int answer[8], value[8];

void solve(int depth = 0, int index = 0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << value[answer[i]] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = index; i < N; i++) {
		answer[depth] = i;
		solve(depth + 1, i + 1);

	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
		std::cin >> value[i];

	std::sort(std::begin(value), std::begin(value) + N);

	solve();

}

// 15656 (7)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>
#include <algorithm>

int N, M;
int answer[8], value[8];

void solve(int depth = 0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << value[answer[i]] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = 0; i < N; i++) {
		answer[depth] = i;
		solve(depth + 1);

	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
		std::cin >> value[i];

	std::sort(std::begin(value), std::begin(value) + N);

	solve();

}

// 15657 (8)
#define _CRT_SECURE_NO_SECURE_

#include <iostream>
#include <algorithm>

int N, M;
int answer[8], value[8];

void solve(int depth = 0, int index=0) {
	if (depth == M) {
		for (int i = 0; i < M; i++) {
			std::cout << value[answer[i]] << " ";

		}
		std::cout << "\n";
		return;
	}


	for (int i = index; i < N; i++) {
		answer[depth] = i;
		solve(depth + 1, i);

	}
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
		std::cin >> value[i];

	std::sort(std::begin(value), std::begin(value) + N);

	solve();

}

// 15663 (9)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

int n, m, arr[8], answer[8];
bool isuse[8];
std::string key;
std::unordered_map<std::string, bool> check;

void solve(int depth = 0, int index = 0) {
	if (depth == m) {
		key = "";
		for (int i = 0; i < m; i++) {
			key += answer[i];
			key += " ";
		}

		if (check[key]) return;

		check[key] = true;
		for (int i = 0; i < m; i++) {
			std::cout << answer[i] << " ";
		}
		std::cout <<  "\n";


		return;
	}

	for (int i = 0; i < n; i++) {
		if (isuse[i]) continue;
		answer[depth] = arr[i];
		isuse[i] = true;
		solve(depth + 1, i + 1);
		isuse[i] = false;

	}




}




int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;

	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	std::sort(std::begin(arr), std::begin(arr) + n);


	solve();


}

// 15664 (10)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

int n, m, arr[8], answer[8];
std::string key;
std::unordered_map<std::string, bool> check;

void solve(int depth = 0, int index = 0) {
	if (depth == m) {
		key = "";
		for (int i = 0; i < m; i++) {
			key += answer[i];
			key += " ";
		}

		if (check[key]) return;

		check[key] = true;
		for (int i = 0; i < m; i++) {
			std::cout << answer[i] << " ";
		}
		std::cout << "\n";


		return;
	}

	for (int i = index; i < n; i++) {
		answer[depth] = arr[i];
		solve(depth + 1, i + 1);
	}




}




int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;

	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	std::sort(std::begin(arr), std::begin(arr) + n);


	solve();


}

// 15665 (11)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

int n, m, arr[8], answer[8];
std::string key;
std::unordered_map<std::string, bool> check;

void solve(int depth = 0) {
	if (depth == m) {
		key = "";
		for (int i = 0; i < m; i++) {
			key += answer[i];
			key += " ";
		}

		if (check[key]) return;

		check[key] = true;
		for (int i = 0; i < m; i++) {
			std::cout << answer[i] << " ";
		}
		std::cout << "\n";


		return;
	}

	for (int i = 0; i < n; i++) {
		answer[depth] = arr[i];
		solve(depth + 1);
	}

}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;

	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	std::sort(std::begin(arr), std::begin(arr) + n);


	solve();


}

// 15666 (12)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

int n, m, arr[8], answer[8];
std::string key;
std::unordered_map<std::string, bool> check;

void solve(int depth = 0, int index = 0) {
	if (depth == m) {
		key = "";
		for (int i = 0; i < m; i++) {
			key += answer[i];
			key += " ";
		}

		if (check[key]) return;

		check[key] = true;
		for (int i = 0; i < m; i++) {
			std::cout << answer[i] << " ";
		}
		std::cout << "\n";


		return;
	}

	for (int i = index; i < n; i++) {
		answer[depth] = arr[i];
		solve(depth + 1, i);
	}




}




int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;

	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	std::sort(std::begin(arr), std::begin(arr) + n);


	solve();


}