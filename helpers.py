from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    list_a = a.splitlines()
    list_b = b.splitlines()
    return sorted(set(list_a) & set(list_b))


def sentences(a, b):
    """Return sentences in both a and b"""

    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)
    return sorted(set(list_a) & set(list_b))

# Optional code for treating end of lines as end of sentences as well

#    list_a = a.splitlines()
#    list_b = b.splitlines()
#    sentences_a = []
#    sentences_b = []
#    for line in list_a:
#        y = sent_tokenize(line)
#        for x in y:
#            sentences_a.append(x)
#    for line in list_b:
#        y = sent_tokenize(line)
#        for x in y:
#            sentences_b.append(x)
#    return sorted(set(sentences_a) & set(sentences_b))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    list_a = []
    list_b = []
    for i in range(len(a) + 1 - n):
        print(i)
        list_a.append(a[i:i+n])
    for i in range(len(b) + 1 - n):
        list_b.append(b[i:i+n])
    return sorted(set(list_a) & set(list_b))