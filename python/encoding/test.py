import codecs

#with codecs.open("tmp.txt", "r", "utf-8") as fin:
with open("tmp.txt", "r") as fin:
    lines = []
    for line in fin:
        print type(line)
        lines.append(line)

    lines.sort()
    for line in lines:
        print line
