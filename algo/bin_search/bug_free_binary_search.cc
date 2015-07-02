


/*
 *
 * 最简单的二分查找. 在一个数组里面找是否存在某个数
 * A是数组，在A[p-r]里面找是否存在某个数, 存在返回index,否则返回-1
 * 
 */

int binSearch(int A[], int p, int r, int v) {
  while (p <= r) {
    int m = (p+r)/2;
    if (A[m] < v) {
      p = m + 1; // 注意点: 在不相等的时候一定要+1/-1，这样可以保证考虑的数组范围在每个循环都减小。因此避免死循环。
    } else if (A[m] > v) {
      r = m - 1;
    } else {
      // 找到了
      return m;
    }
  }
  return -1;
}


// 下面是二分查找的变形。需要用到我的方法
//
// 方法的关键是引入一个辅助变量mark, 来帮助在每个循环都能够缩小范围, 避免死循环

/*
 * 变形1: 在数组中找到和v相等的最小的index
 * Example:
 *   search 2 in [1,2,2,3,3,4], return 1
 *   search 3 in [1,2,2,3,3,4], return 3
 * 
 *
 *
 */

int binSearch(int A[], int p, int r, int v) {
  int mark = -1; // 首先把mark设为一个不可能的值
  // 注意和上面一样，我们考虑的数组范围[p-r], 在每个循环后都减少了，因此避免了死循环
  while (p <= r) {
    int m = (p+r)/2;
    if (A[m] < v) {
      p = m + 1;
    } else if (A[m] > v) {
      r = m - 1;
    } else {
      // 关键的地方。当A[m] == v时，我们怎么办?
      mark = m; // mark保存这个值。因为m可能是我们需要的index.
      r = m - 1; // 更新r。因为我们需要返回最小的index.
    }
  }
  return mark;
}

// 思考: 如果需要返回最大的index应该怎么办?


// 变形2:
//  对于一个有序数组[1,2,3,4], 我们从中间折断为[1,2]和[3,4], 然后拼接这个
//  折断后的数组为[3,4,1,2]。
//
//  现在，假如给一个折断后拼接的数组A, 你返回这个数组最小值的index.
//  Example: 
//    [3,4,5,1,2] -> return 3 since A[3] = 1
//  假定数组中所有值都不相同(这个面试的时候要问一下面试官，如果存在相同的值的话
//  这个方法不好使了)
//
//  这题是要我们找小于A[p]的值里面最小的那个。
//  
//

int binSearch(int A[], int p, int r) {
  int mark = - 1;
  int base = A[p]; // 参照值
  while (p <= r) {
    int m = (p+r) / 2;
    if (A[m] < base) {
      mark = m; // 找到一个，用mark标记
      r = m-1; // 我们试试有没有更小的
    } else {
      p = m + 1;
    }
  }
  return mark;
}
