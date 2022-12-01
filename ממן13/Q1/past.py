words = ["adopt", "bake", "beam", "cook", "time", "grill", "waved", "hire"]


past_tense = []
for word in words:
     if word.endswith('e'):
        past_word = word + 'd'
     elif not word.endswith('ed'):
        past_word = word + 'ed'
     else:
        past_word  = word

     past_tense.append(past_word)
     
for past in past_tense:
    print(past)
