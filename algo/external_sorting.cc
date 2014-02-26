#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using std::string;
using std::vector;
using std::sort;

const int MEM_SIZE = 16; // 16 bytes(hold 4 integers)

const string filename = "data/exteral_sorting.dat";

typedef struct {
  int* base;
  int num;
  int idx;
} mem_ptr ;

void init_mem_ptr(mem_ptr* ptr, int* base,
                      int num) {
  ptr->base = base;
  ptr->num = num;
  ptr->idx = 0;
}

class BufferedFile {
 public:
  BufferedFile(const string &filename, int* buffer, int buffer_size) {
    fname_ = filename;
    buf_ = buffer;
    buf_size_ = buffer_size;
    file_eof_ = false;
    fpos_ = 0;
    front_ = tail_ = 0;
  }
  void read() {
    // read from fpos, with buffer_size, if not more to read, set finish flag
    assert(!file_eof_);
    front_ = tail_ = 0;
    FILE* fin = fopen(fname_.c_str(), "r");
    if (fin != NULL) {
      if (!fseek(fin, fpos_, SEEK_SET)) {
        // failed ...
      }
      for(int i = 0; i < buf_size_; i++) {
        int v;
        fscanf(fin, "%d", &v);
        if (feof(fin)) {
          file_eof_ = true;
          break;
        }
        entail(v, false);
      }
      fpos_ = ftell(fin);
      fclose(fin);
    } else {
      // todo: error handling
      exit(-1);
    }
  }
  bool empty() {
    return front_ == tail_;
  }
  bool full() {
    return (front_ == 0) && (tail_ == buf_size_);
  }
  void entail(int v, bool append_to_file) {
    // write_to_file signal whether to write to file when buffer is full
    buf_[tail_] = v;
    tail_ += 1;
    if (append_to_file && full()) {
      append();
    }
  }
  void append() {
    FILE* fout = fopen(fname_.c_str(), "a");
    for(int i = front_; i < tail_; i++) {
      fprintf(fout, "%d\n", buf_[i]);
    }
    fclose(fout);
    front_ = tail_ = 0;
  }
  int defront() {
    int v = buf_[front_];
    front_ = front_ + 1;
    return v;
  }
  bool front(int *pv) {
    // get front value, if failed, return false
    if (finished()) {
      return false;
    } else if (empty()) {
      // queue is empty
      read();
      if (empty()) {
        return false;
      } else {
        *pv = buf_[front_];
        return true;
      }
    } else {
      //printf("%d %d\n", front_, tail_);
      *pv = buf_[front_];
      return true;
    }
  }
  bool finished() {
    if (file_eof_ && empty()) {
      return true;
    } else {
      return false;
    }
  }
  void clear_file() {
    FILE* f = fopen(fname_.c_str(), "w");
    fclose(f);
    front_ = tail_ = 0;
  }
 private:
  string fname_;
  int* buf_;
  int buf_size_;
  bool file_eof_;
  long int fpos_;
  int front_;
  int tail_;
};

void merge_sort(vector<BufferedFile> bfs, BufferedFile cache) {
  while (true) {
    int min_idx = -1;
    int min_v = INT_MAX;
    int finished_num = 0;
    for(int i =0; i < bfs.size(); i++) {
      int v;
      if (!bfs[i].front(&v)) {
        finished_num += 1;
        continue; // ignore this
      } else if (v < min_v) {
          min_v = v;
          min_idx = i;
      }
    }
    if (min_v != INT_MAX) {
      //printf("%d\n", max_v);
      cache.entail(min_v, true);
      bfs[min_idx].defront();
    }
    if (finished_num == bfs.size()) {
      break;
    }
  }
  cache.append();
}

int read_ints(FILE* fin, int* mem, int max_size) {
  for(int i = 0; i < max_size; i++) {
    int v;
    fscanf(fin, "%d", &v);
    if (feof(fin)) {
      return i;
    }
    //printf("%d : %d\n",i,  v);
    mem[i] = v;
  }
  return max_size;
}

void print_ints(int* mem, int num) {
  for(int i = 0; i < num; i++) {
    printf("%d\n", mem[i]);
  }
}

void write_ints(string fname, int* mem, int num) {
  FILE* fout = fopen(fname.c_str(), "w");
  if (fout != NULL) {
    for(int i = 0; i < num; i++) {
      fprintf(fout, "%d ", mem[i]);
    }
    fclose(fout);
  } else {
    // todo: error handling
  }
}
void external_sorting() {
  int max_int_num = MEM_SIZE / sizeof(int);
  int* mem = new int[max_int_num];
  vector<string> subfnames;
  int file_counter = 0;
  FILE* fin = fopen("data/external_sorting.dat", "r");
  while (true) {
    int int_num = read_ints(fin, mem, max_int_num);
    if (int_num == 0) {
      break;
    }
    sort(mem, mem+int_num);
    char temp[100];
    sprintf(temp, "%s_%d", "temp/external_sorting", file_counter);
    file_counter += 1;
    string fname = temp;
    write_ints(fname, mem, int_num);
    subfnames.push_back(fname);
    if (int_num < max_int_num) {
      break;
    }
  }
  fclose(fin);

  int file_count = subfnames.size();
  int unit_int_num = max_int_num / file_count;
  printf("file_count:%d unit_int_num:%d\n", file_count, unit_int_num);
  BufferedFile cache(string("data/external_sorting.out"),
                     &mem[file_count*unit_int_num],
                     unit_int_num);
  cache.clear_file();
  vector<BufferedFile> bfs;
  for(int i = 0; i < file_counter; i++) {
    BufferedFile bf(subfnames[i], &mem[i*unit_int_num], unit_int_num);
    bfs.push_back(bf);
  }
  merge_sort(bfs, cache);
}


int main(int argc, const char *argv[])
{
  external_sorting();
  //test();
  return 0;
}
