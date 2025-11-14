bitset<9> a;
bitset<9>b;
a.flip(3);
bitset<9>c=a&b, a|b, a^b;
~ inverse all bites
<< shifts left (save in new bitset) (<<= for save in same value)
>> shifts right (>>= ...)
a.test(4) - check this bit
a.set(2) - set the value true
a.reset(2) - reset the value false
a.count() - how many truths
a.any() - is the someone true?
