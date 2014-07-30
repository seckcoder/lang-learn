    n个数1,2,...n, 顺时针排成一个环。每次从这个环中移除第k个数。第i次移除的计数应该从第i-1次移除的下一个数开始。
    比如:

        n = 6, k = 2: 
            6  1 
          5      2
             4 3

    第一次应该移除2, 第二次应该移除4(从3开始数第2个)，第三次移除6，第四次移除3, 第五次移除1, 第六次移除5。

    问题：

        f(n, k, i)表示给定n,k，第i次移除的数。求f(n, k, i)和f(n, k, i-1)的递推关系。

    我自己想了下，没想出来。。。。问一下大家的想法....


def J(n):
    if n == 1:
        return 1
    elif n % 2 == 0:
        return 2*J(n/2)-1
    else:
        return 2*J(n/2)+1
    
for i in range(1, 16):
    print i, J(i)
