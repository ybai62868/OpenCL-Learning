# include <cstdio>
# include <iostream>

using namespace std;

# define MAX 12
int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];

int main(void)
{
	int m, n, p; cin >> m >> n >> p;

	// Create the matrix_1 (m x n), matrix_2(n x p)
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) {
			a[i][j] = rand() % 3 + 1;
		}
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < p;j++) {
			b[i][j] = rand() % 3 + 1;
		}
	}

	// Output the matrix_1 and matrix_2
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < p;j++) {
			cout << b[i][j] << " ";
		}
		cout << endl;
	}

	// Gemm
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < p;j++) {
			int temp = 0;
			for (int k = 0;k < n;k++) {
				temp += a[i][k] * b[k][j];
			}
			c[i][j] = temp;
		}
	}

	// Output the matrix_3
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < p;j++) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}