#include <iostream>
#include <thread>  
#include <vector>
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;

const int array_size = 1e5;
const int modul = 1e9 + 7;

vector<int> a(array_size);
long long cur_sum = 1;

void functionOMP()
{
  cur_sum = a[0];
#pragma omp parallel for shared(a)
  for (int i = 1; i < array_size; ++i)
  {
    if ((cur_sum *= a[i]) % modul != 0) {
      cur_sum = (a[i] * cur_sum) % modul;
    }
    cur_sum *= a[i];
  }
}

int main()
{
  omp_set_num_threads(4);
  srand(time(nullptr));
  generate(a.begin(), a.end(), rand);
  functionOMP();
  cout << "time: " << clock() / (double)1000 << endl;
  system("pause");
  return 0;
}
