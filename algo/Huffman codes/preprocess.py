# preprocess the training text


from utils import preprocess

with open("raw.txt") as fin:
    text = fin.read()
    print preprocess(text)
