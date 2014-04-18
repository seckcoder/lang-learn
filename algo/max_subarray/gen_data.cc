#include <random>
#include <fstream>

using namespace std;

int main(void) {
  int n = 500;
  int *A = (int*)malloc(n*sizeof(int));
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(-100, 100);
  for(int i = 0; i < n; i++) {
    A[i] = dis(gen);
  }
  ofstream ofs("test.dat");
  for(int i = 0 ; i < n; i++) {
    ofs << A[i] << endl;
  }
  ofs.close();
  free(A);
  return 0;
}
