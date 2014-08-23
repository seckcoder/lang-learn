



total = 0
c_total = 0
h_total = 0
l_total = 0
y_total = 0
s_total = 0


with open("data/ikea.txt", "r") as fin:
    for l in fin:
        l = l.strip()
        if l:
            count, ty = l.split(' ')
            count = float(count)
            total += count
            if ty == "c":
                c_total += count
            elif ty == "h":
                h_total += count
            elif ty == "y":
                y_total += count
            elif ty == "l":
                l_total += count
            elif ty == "s":
                s_total += count
            else:
                print "error"
def withtax(c):
    return c*1.09

Meta = {
    "c":c_total,
    "h":h_total,
    "l":l_total,
    "y":y_total,
    "s":s_total
}

withtax_total = 0
for ty, cnt in Meta.iteritems():
    print ty, cnt, withtax(cnt)
    withtax_total += withtax(cnt)
print withtax_total
