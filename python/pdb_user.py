#!/usr/bin/env python
def debug_demo(val):
    import pdb
    pdb.set_trace()
    if val <= 1600:
        print 'level 1'
        print 0
    elif val <= 3500:
        print 'level2'
        print (val-1600) * 0.05
    elif val <= 6500:
        print 'level 3'
        print (val-3500) * 0.10 + (3500 - 1600)*0.05
    else:
        print 'level 4'
        print (val - 6500) * 0.20 + (6500 - 3500) * 0.10 + (3500 - 1600) * 0.05
if __name__ == '__main__':
    debug_demo(4500)
