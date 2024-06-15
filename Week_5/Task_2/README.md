# Speller
## Problem to Solve
Implement a program that spell-checks a file using a hash table.
The challenge ahead of you is to implement the fastest spell checker you can! By “fastest,” though, we’re talking actual “wall-clock,” not asymptotic, time.

## Background
In ```speller.c```, we’ve put together a program that’s designed to spell-check a file after loading a dictionary of words from disk into memory. That dictionary, meanwhile, is implemented in a file called ```dictionary.c```. (It could just be implemented in ```speller.c```, but as programs get more complex, it’s often convenient to break them into multiple files.) The prototypes for the functions therein, meanwhile, are defined not in ```dictionary.c``` itself but in ```dictionary.h``` instead. That way, both ```speller.c``` and ```dictionary.c``` can ```#include``` the file. 

### texts/
So that you can test your implementation of speller, we’ve also provided you with a whole bunch of texts, among them the script from La La Land, the text of the Affordable Care Act, three million bytes from Tolstoy, some excerpts from The Federalist Papers and Shakespeare, and more. So that you know what to expect, open and skim each of those files, all of which are in a directory called ```texts```.

The output of speller, if executed with, say,

```./speller texts/lalaland.txt```
will eventually resemble the below.

Below’s some of the output you’ll see. For information’s sake, we’ve excerpted some examples of “misspellings.” And lest we spoil the fun, we’ve omitted our own statistics for now.
```
MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```
```TIME IN load``` represents the number of seconds that speller spends executing your implementation of load. ```TIME IN check``` represents the number of seconds that speller spends, in total, executing your implementation of check. ```TIME IN size``` represents the number of seconds that speller spends executing your implementation of size. ```TIME IN unload``` represents the number of seconds that speller spends executing your implementation of unload. ```TIME IN TOTAL``` is the sum of those four measurements.

Note that these times may vary somewhat across executions of speller, depending on what else your codespace is doing, even if you don’t change your code.

Incidentally, to be clear, by “misspelled” we simply mean that some word is not in the dictionary provided.

### Makefile
And, lastly, recall that ```make``` automates compilation of your code so that you don’t have to execute ```clang``` manually along with a whole bunch of switches. However, as your programs grow in size, ```make``` won’t be able to infer from context anymore how to compile your code; you’ll need to start telling make how to compile your program, particularly when they involve multiple source (i.e., .c) files, as in the case of this problem. And so we’ll utilize a ```Makefile```, a configuration file that tells make exactly what to do. Open up ```Makefile```, and you should see four lines:

1. The first line tells ```make``` to execute the subsequent lines whenever you yourself execute ```make speller``` (or just ```make```).
2. The second line tells ```make``` how to compile ```speller.c``` into machine code (i.e., ```speller.o```).
3. The third line tells ```make``` how to compile ```dictionary.c``` into machine code (i.e., ```dictionary.o```).
4. The fourth line tells ```make``` to link ```speller.o``` and ```dictionary.o``` in a file called ```speller```.
   
**Be sure to compile speller by executing ```make speller``` (or just ```make```). Executing ```make dictionary``` won’t work!**

## Specification
Alright, the challenge now before you is to implement, in order, ```load```, ```hash```, ```size```, ```check```, and ```unload``` as efficiently as possible using a hash table in such a way that ```TIME IN load```, ```TIME IN check```, ```TIME IN size```, and ```TIME IN unload``` are all minimized. To be sure, it’s not obvious what it even means to be minimized, inasmuch as these benchmarks will certainly vary as you feed speller different values for dictionary and for text. But therein lies the challenge, if not the fun, of this problem. This problem is your chance to design. Although we invite you to minimize space, your ultimate enemy is time. But before you dive in, some specifications from us.

- You may not alter ```speller.c``` or ```Makefile```.
- You may alter ```dictionary.c```, but you may not alter the declarations (i.e., prototypes) of ```load```, ```hash```, ```size```, ```check```, and ```unload```. You may, though, add new functions and (local or global) variables to ```dictionary.c```.
- You may change the value of ```N``` in ```dictionary.c```, so that your hash table can have more buckets.
- You may alter ```dictionary.h```, but you may not alter the declarations of ```load```, ```hash```, ```size```, ```check```, and ```unload```.
- Your implementation of ```check``` must be case-insensitive. In other words, if ```foo``` is in dictionary, then check should return ```true``` given any capitalization thereof; none of ```foo```, ```foO```, ```fOo```, ```fOO```, ```fOO```, ```Foo```, ```FoO```, ```FOo```, and ```FOO``` should be considered misspelled.
- Capitalization aside, your implementation of check should only return ```true``` for words actually in dictionary. Beware hard-coding common words (e.g., the), lest we pass your implementation a dictionary without those same words. Moreover, the only possessives allowed are those actually in dictionary. In other words, even if ```foo``` is in dictionary, ```check``` should return ```false``` given ```foo's``` if ```foo's``` is not also in dictionary.
- You may assume that any dictionary passed to your program will be structured exactly like ours, alphabetically sorted from top to bottom with one word per line, each of which ends with ```\n```. You may also assume that dictionary will contain at least one word, that no word will be longer than ```LENGTH``` (a constant defined in ```dictionary.h```) characters, that no word will appear more than once, that each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe.
- You may assume that ```check``` will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes.
- Your spell checker may only take text and, optionally, dictionary as input. Although you might be inclined (particularly if among those more comfortable) to “pre-process” our default dictionary in order to derive an “ideal hash function” for it, you may not save the output of any such pre-processing to disk in order to load it back into memory on subsequent runs of your spell checker in order to gain an advantage.
- Your spell checker must not leak any memory. Be sure to check for leaks with ```valgrind```.
- The hash function you write should ultimately be your own, not one you search for online.

## How to Test
```
./speller texts/lalaland.txt > student.txt
```
Compare your program’s output (assuming you redirected it to, e.g., ```student.txt```) against one of the answer keys:
```
diff -y student.txt keys/lalaland.txt
```
If your program’s output matches the staff’s, diff will output two columns that should be identical except for, perhaps, the running times at the bottom. If the columns differ, though, you’ll see a ```>``` or ```|``` where they differ. 
```
MISSPELLED WORDS                                                MISSPELLED WORDS

TECHNO                                                          TECHNO
L                                                               L
                                                              > Thelonious
Prius                                                           Prius
                                                              > MIA
L                                                               L
```
Finally, be sure to test with both the default large and small dictionaries. Be careful not to assume that if your solution runs successfully with the large dictionary it will also run successfully with the small one. Here’s how to try the small dictionary:
```
./speller dictionaries/small texts/cat.txt
```
### For more information
https://cs50.harvard.edu/x/2024/psets/5/speller/
