with open("words.txt") as f:
    words = f.read().split('\n')

new_words = []
for w in words:
    if len(w) > 2:
        new_words.append(w)

new_words = "\n".join(new_words)
print(new_words)

with open("words.txt", "w") as f:
    f.write(new_words)