// How did you hear about us?



// android ............................

// cloud operation engineer
//
//
// Challenges:
//
// 1. Frontend framework/server to choose
// 2. Backend database design.
//
//    We need design the database schema to optimize the performance.
//   a) For mysql, 
//      
//      As we have different query cases, we need to design the schema accordingly to provide the best query perofmrance
//
//
//    Also, we also need to build the index, benchmarking to get what's the bottleneck,
//    do some partioning.
//
//   Waht kind of differnce do you want to know? Can you give us a more specific. 
//   
//   Mysql is sql data base
//   HBase is nosql data base
//
//
//   HBase provides a command line interface for us to modify it. 
//
//   
//   You question is too general... It's hard to get what you really want....
//   
//
//   During our experiement, we know mysql is good at storing small/relational dataset, compared with HBase. While HBase is designed to store large document. 
//
//
//   EMR, Load balancer, S3 to store data.
//
//   
//   EC2.
//
//   Yes. We build our database on EC2 for mysql. But for hbase, we use the hbase
//   provided in EMR.
//
//   Yes. We do load balancing on many ec2 servers. For each ec2 server, we have one
//   mysql instance. 
//
//   We don't need to keep it sync since we don't have any modification query.
//   All our query is just read the database. Yes.
//
//
//   Yes. Signal.....
//
//   Yes. First computer science then ece, why?
//
//   Because, they are almost the same....
//
//   
//   No , I don't need to. 
//   plan. 
//   
//   What language ? Java.
//
//   Currently, no.
//   I want to go to san Diego because of friend!!!! 加分加分加分啊啊啊啊啊啊啊，快说快说
//
//   I love programming. I want devote my whole life and passion to programming.
//  
//
//   Programming is very interesting also very challenging. 
//
//   1. We can learn a lot from programming. 
//   
//
//
//   
//
//   
//
//   
//
//   
//   
// 



// "Contain space?????"""""
//
//z
string compression(string str) {

  String res;

  if (str.empty()) return res;

  int start_idx = 0;

  // Nothing I can do to optimize the code. It's already O(n)
  // Use StringBuilder instead of simple string concatenation
  // since string concatenation will create and destroy the object
  // repeatedly.
  //
  // 1. Allocate the string memory just before the iteration reduce
  // the load of garbage collection
  //
  // 2. One important optimization is that like, for string with only
  // one character:a, we provide a instead of a1. This will compress the string
  // more effectively.
  // For example, suppose the input str is : abcdef, then the output str
  // will be a1b1c1d1e1f1. As a result, the returned string is not compressed but even
  // with greater length.
  // 
  //
  // 
  //
  //
  // 
  // aabbcc
  // 0, 2
  while (start_idx < str.length()) {
    char c = str[start_idx];
    // copy the current character
    res += c;

    // new_idx >= start_idx+1
    int new_idx = countChar(str, start_idx+1, c);

    if (new_idx - start_idx > 1) {
      // new_idx - start_idx is the count of characters.
      // create a new string contains the count
      res += String(new_idx-start_idx);
    }
    // update the index
    start_idx = new_idx;
  }
  return res;
}

// count number of characters that are equal to c. Return the index that's different from current char or reaches the end.
int countChar(string str, int start_idx, char c) {
  while (start_idx < str.length() && str[start_idx] == c) {
    start_idx += 1;
  }
  return start_idx;
}
// Corner case: what if there is only one characters?????????????????
// ???
// a1? or just a. That's important.
//
// Just copy it, almost the same as java.
//
//
// 
//
// 他们就不该用StringBuilder.我是按Java写的。。。
