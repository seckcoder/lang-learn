






// 开外音
//
//
// NASA projects?
// What's the computer projects are you working on.
//
// 
// 放大一点
// 再放大一点
//
// 1. differentiate between lower case and upper case
// 2. string is splitted by empty space?
// like comma, ., 
//
// 3. should we return the most frequent string or all the count of the string?
//
// sort the items by count.
//
// in last step we retrive the sub_str from the str,count pairs
//
// We split the string by comma and empyt space, and then convert
// all string into lower case since we don't differentiate between lower case
// and upper case.
//
// Since you want me to count the number of strings in the whole string.
// 
// dictionary in python is just a hash table.
//
// O(n) memory, O(1) lookup and insert time complexity
// n is number of all characters.
// 
// yes.
// 
// Sorry, I misunderstood your meaning. I mean the number of unique strings, but
// the characters are not unique. The complexity is O(n) with n being the number of 
// unique strings. Not number of unique characters. 
//
// Space complexity is O(n * l) with n being number of unique sub strings,
// and l being the max length of str. the sub strings of the input string.
// like 
// 
// 你说得太不自信了。
// 
// 
//
// Should we consider empty space in the count? Yes. 
//
// Just say this:
// O(Number of unique characters).Yes
// 
// Just say this:
// O(1) for each chaacter.
//
// Hash table has lookup complexity of O(1).
// This is based on amorted analysis.
// 
// So you mean we should consisder the count in the hash table?
//
// Since if we only consider the key, the space complexity is O(number of unique characters)
//
// If you hash the character into integers, then the complexity also differs.
// But generally, the space complexity is O(n) with n being the number of unique characters.
//
// ascii
// You mean only ASCII characters or may contain unicode characters.
//
// Yes. 
//
// Spacing work in memory?
//
//  Yes. The hash table makes this through rehashing.
//  So first it allocates a small amount of memory, then it dynamically 
//  ajusts the size of the container.
//
//  Yes.
//
//  So basically, first suppose size of the container is n.
//  Then for a given character, if the hashed value is not contaiend in the size n,
//  then it conducts rehashing.
//
//  Generally, it allocates a container of size 2*n.
//  Then it traversed  every character of the origianl container of size n,
//  rehash the existing character, and move it accordingly.
//
//  First allocates a large amount of memory, then rehash existing key, value items 
//  stored in the hash table.
//
// Say this
//  255, which is the number of ascii characters.
//
//  What do you mean by 70 percent.
//
//  I mean 255 is the maximum size of memory needed for ascii characters.
//
//  Yes. we can start with 20 or 30 or 40. Generally, it depends on the real world
//  application. If the input string is very large, we can assume that most characters
//  will appeart in the hash table. So we should let the starting size being large.
//
//
//  Time complexity?
//  O(n) with n being the length of input string
//  tiems log n
//  O(n*lgn) for the sort. I didn't consider the sort procedure.
//
//  Yes!
//  But we can make it faster. The best is O(n*log10).
//
//  We can make it by using a heap. Heap is heap.
//
//  
//  Use a fixe sized heap with the size being 10. 
//  If we add an element larger than the existing eleements in the heap,
//  then we remove the smallest element from the heap.
//
//  Sorry?
//  
//  Yes.
//  
//  top 10. Yes. 
//  Sicne we always maintain the top 10 elements.
//
//  You mean the unique chars size is smalelr than 10? Of course,
//  when the number of unique chars is smalelr than 10, of course the heap size
//  is smaller than 10.
//
//  Yes.
//  If bgger than 10, as we meaintain a fixed size heap, the size of the heap
//  will never bigger than 10. We always remove the samllest element in the heap,
//  if the size of heap is gonna bigger than 10 as I has mentioned previously.
//
//
//  No.
//  
// 
//
// 
// 
//
//
// Use python
//
// 不要随便切换。






// 声音调大点

// What technology
// machine learning algorithm?
// cloud computing

// key part is performance tunning.

// AWS expeirence. 

// run our whoe platform on the AWS.
// EC2 as backend server,


// signal is not very good.

// List 

// linked list .
//
// operations we consider:
//  insert, remove, search
//
// remove: O(1), 
// insert: O(1)
// search: O(n) with n being the length of the list
//
// Array List:
//
// remove: O(n)
// insert at any position: O(n)
// search by index: O(1)
// search by value: O(n)

// in linked list, when we search a value, we
// have to search from the beining, and traverse the whole
// list to find whether a value exist.
//
// In array list, array can be accessed randomly.
// So we get an element by index in O(1)
// 
// For linked list, If we insert at any positino, it's also O(1)
// For array list, if we insert a value at a positin,
// we need to move all elements after it.


// map interface.
//
// Hash map or Tree map?
// These two are differnt. 
//
// Time complexity?
//
// For hash map,
//
// First, let's talk about time complexity:
//
// it has O(1) time of add and remove and search an element
//
// Sure.
//
//
// I get it.
// Follow me.
//
//
// So I will talk first about the data struture we use to impleemnt hash mpa.
//
// Generally, we can use a random access array to implement the hash map.
//
// If we want to add aan element,
// in hash map, we add a key, value pair to it.
// That is, we first hash the value to get the key,
// the key can be the index of the array
// 
// Then we can put the value in the array by the index.
//
// This is the add operation. Which is O(1) time complexity
//
// In hash map, we add a linked list to each index of array.
// If we have a collision, we add multiple values to the linked list.
// 
// C++
//
// What's the coin values available?
// What do you mean minimum set of coins?
//
//
// What's the maximum allowable value of the price?
// 放大点
// Explain basic idea:
// Say this:
// We can solve this in dynamic progrmaming.
//
// We have 
// focus
//
// Generally, we solve this problem from the inductive
// equaltion.
// As we have mentioned,
// let min_set being the dp value.
// Then we have the inductive equaltion:
//
// this problem from the inductive // equaltion.
// As we have mentioned,
// let min_set being the dp value
// What are you doing? copy the following equaltto the collabedit? 
// "copy the following to the collabeidt:"
// min_set[price] = min{min_set[price-coins[i]]+1, min_set[price]};
//
// 
// The time complexity?
// And The time complexity is O(price). Since we have only 4 coins. The exact should be O(4*price) but it's eqal to O(price)k
//
// 
/

first line:

we decalre the min_set as the dp value.

min_set[0] = 0 means when the price is 0, we need only
0 coins to fullfill the requirement.

Then we enuemrate the cur_price from 1 to price, since
we want to try every price and produce the solution bottom up.

The following two for loops is just direct application of the inductive equation.

For each price, we try every coin value with it.
if the prices is greater equal than the coin value,
   then we know we can use the coin value.

   We also need to decide whether min_set is equal to INT_MAX. Since otherwise, tehre must not be a combination
   to form the min_set.

   That's it.


// Actually this is best solution I can think right now.
// Can you give me any hint?
//
// Can you provide me a hint about the optimized solution?
//  I really want to know about it. It would be great
//  if you could send it to me through email.
//  
//  So this is a greedy algorithm? All done.
