"""
A program to generate username for Weibo/Twitter
"""


from morse import translateToMorseCode
from huffman import HuffmanTree
from utils import preprocess

def generate(sentence):
    with open('train.txt') as fin:
        train = fin.read()
        train += ' ' + preprocess(sentence)
        morse_codes = translateToMorseCode(train)
        huffman_tree = HuffmanTree()
        huffman_tree.train(morse_codes)
        print huffman_tree.translate(preprocess(sentence))
