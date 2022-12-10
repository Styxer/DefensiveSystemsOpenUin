words = ["adopt", "bake", "beam", "cook", "time", "grill", "waved", "hire"]


tense_past = []

for word in words:
  if word.endswith("e"):
    tense_past.append(word + "d")
  elif word.endswith("ed"):
    tense_past.append(word)
  else:
    tense_past.append(word + "ed")

print(tense_past)


print(tense_past)