

#include <vector>
#include <iostream>
using namespace std;



/*
 * Proof that following method is O(n)
 * 
 * First we prove the following algorithm is right
 *
 * 
 */
void first_element_smaller(const vector<int> &input,
    vector<int> &output) {

  if (input.size() == 0) return;
  output.push_back(input[0]);
  vector<int> first_smaller_indices;
  first_smaller_indices.push_back(0);
  for (int i = 1; i < input.size(); i++) {
    
    int start = i-1;
    int first_smaller_index = i;

    do {
      if (input[start] < input[i]) {
        first_smaller_index = start;
        break;
      } else {
        start = first_smaller_indices[start];
      }
    } while (start != first_smaller_indices[start]);
    
    first_smaller_indices.push_back(first_smaller_index);
    output.push_back(input[first_smaller_index]);
  }
}


int main() {
  vector<int> input = {4,6,3,2,8,7,9, 21, 23, 15};
  vector<int> output;
  first_element_smaller(input, output);
  for (int i = 0; i < output.size(); i++) {
    cout << output[i] << " ";
  }
  cout << endl;
  return 0;
}

