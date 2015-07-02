


# version 1. the naive version



def sjt_naive(perm):
    yield perm

    n = len(perm)

    dirs = [-1]*n

    while True:
        def findMaxMobile():
            max_mobile_idx = -1
            for d,(idx,_) in zip(dirs, enumerate(perm)):
                if (d < 0 and idx != 0 and perm[idx] > perm[idx-1]) or \
                   (d > 0 and idx != n-1 and perm[idx] > perm[idx+1]):
                    if max_mobile_idx < 0 or perm[max_mobile_idx] < perm[idx]:
                        max_mobile_idx = idx
            return max_mobile_idx

        max_mobile_idx = findMaxMobile()

        if max_mobile_idx == -1:
            raise StopIteration

        max_mobile_v = perm[max_mobile_idx]


        def swap(idx1, idx2):
            perm[idx1],perm[idx2] = perm[idx2],perm[idx1]
            dirs[idx1],dirs[idx2] = dirs[idx2],dirs[idx1]

        if dirs[max_mobile_idx] < 0:
            swap(max_mobile_idx, max_mobile_idx-1)
        elif dirs[max_mobile_idx] > 0:
            swap(max_mobile_idx, max_mobile_idx+1)


        def reverseDir(idx):
            if dirs[idx] == -1:
                dirs[idx] = 1
            else:
                dirs[idx] = -1

        for idx,v in enumerate(perm):
            if v > max_mobile_v:
                reverseDir(idx)

        yield perm



for perm in sjt_naive(range(1,6)):
    print perm
