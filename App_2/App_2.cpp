#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>

using namespace std;

const int N = 100;
vector<vector<int>> A(N), B(N), C(N);

void multiply(vector<vector<int>>A, vector<vector<int>>B, vector<vector<int>>C)
{
#pragma omp parallel for shared(A, B, C)
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j)
        C[k][i] += A[k][j] * B[j][i];
    }
  }
}

int main()
{
  srand(time(nullptr));

  cout << "There are " << omp_get_num_procs() << " processors in system." << endl;
  for (int i = 0; i < N; i++) {
    A[i].resize(N);
    B[i].resize(N);
    C[i].resize(N);
    for (int j = 0; j < N; j++) {
      A[i][j] = rand();
      B[i][j] = rand();
    }
  }

  cout << "START!!!\n";
  omp_set_num_threads(1);
  multiply(A, B, C);
  cout << "Execution time of algorithm's parallel=" << clock() / (double)1000 << endl;

  return 0;
}