A = ord('A')
Z = ord('Z')
ZERO = ord('0')
NINE = ord('0')

def valid(c):
    return (A <= ord(c) <= Z) or (ZERO <= ord(c) <= NINE)

def preprocess(sentence):
    s = ""
    for c in sentence.upper():
        if valid(c):
            s += c
        else:
            s += ' '
    s = ' '.join(s.split(' '))
    return s
