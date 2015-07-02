


// tree
// List
// HashMap !
// O(1) for lookup, O(1) for insert
// key, value data structure
// 
// "Implementation": Talk about this: He means the implementation.
//  Use a vector/array to store data. For each key, we hash the key into int, which 
//  can be used as index into the vector.
//  
//  If collision happened, we append the data into a list. The list is stored in the array.
//
//  link to Collabedit. 
//  
//  
//  
//  
//
// Array
// Stack
// Queue
// 

class Solution {
  public:
    // pass
    // Walk through the code
    // Explain what you have done.
    // Yes. Of course, it returned the right answer.
    String commonWords(String input_str) {
      // split by "." and empty space and ','
      // You said, sorry, I forgot how to represent it in regular expression.
      // O(n) with respect to number of words.
      // Because, the insert complexity of hash map is O(1), we have n words.
      // lookup complexity of hash map is also O(1)
      // Therefore, the time complexity is O(n)
      // 
      //
      // Use ordered map/called SortedTree map in Java? instead of hash map. Which can
      // query the most common words in the map.
      //
      // 
      input_str = input_str.lower();
      input_str.replace(".", " ");
      input_str.replace(",", " ");
      Array[String] str_arr = input_str.split([' '.,]);
      // split the input_str into array of string
      split(input_str, str_arr);
      // Use Hashmap
      HashMap<String, int> hash_map;
      int max_hash_freq = -1;
      String ans;
      for (int i = 0; i < str_arr.size(); i++) {
        // str not found in the hash map
        if (hash_map[str_arr[i]] == NULL) {
          hash_map[str_arr[i]] = 1;
        } else {
          hash_map[str_arr[i]] += 1;
        }
        // if greater than max_hash_freq, update it since this maybe a possible
        // answer
      }
      ArrayList<String> ans;
      // Iterate through every element of hash map
      for (HashMap<string,int>::iterator iter = hash_map.begin();
          iter != hash_map.end(); iter++) {
        if (iter.value <= num) {
          ans.append(iter.string);
        }
      }

      // However, I think it means return the top 3 frequency elements.
      // we can use a tree map
     return str_lst;
    }
};
