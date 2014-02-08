from itertools import chain


def demo_chain():

    seq1 = xrange(1, 5)
    seq2 = xrange(5, 10)

    return [i for i in chain(seq1, seq2)]

def demo_compress():
    data = range(1, 5)
print demo_chain()
