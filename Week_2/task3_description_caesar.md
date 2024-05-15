# Caesar

## Problem to Solve
Supposedly, Caesar (yes, that Caesar) used to “encrypt” (i.e., conceal in a reversible way) confidential messages by shifting each letter therein by some number of places. For instance, he might write A as B, B as C, C as D, …, and, wrapping around alphabetically, Z as A. And so, to say HELLO to someone, Caesar might write IFMMP instead. Upon receiving such messages from Caesar, recipients would have to “decrypt” them by shifting letters in the opposite direction by the same number of places.

The secrecy of this “cryptosystem” relied on only Caesar and the recipients knowing a secret, the number of places by which Caesar had shifted his letters (e.g., 1). Not particularly secure by modern standards, but, hey, if you’re perhaps the first in the world to do it, pretty secure!

Unencrypted text is generally called plaintext. Encrypted text is generally called ciphertext. And the secret used is called a key.

**In a file called caesar.c in a folder called caesar, write a program that enables you to encrypt messages using Caesar’s cipher. At the time the user executes the program, they should decide, by providing a command-line argument, what the key should be in the secret message they’ll provide at runtime. We shouldn’t necessarily assume that the user’s key is going to be a number; though you may assume that, if it is a number, it will be a positive integer.**

## Specification
Design and implement a program, caesar, that encrypts messages using Caesar’s cipher.

- Implement your program in a file called caesar.c in a directory called caesar.
- Your program must accept a single command-line argument, a non-negative integer. Let’s call it ***k*** for the sake of discussion.
- If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with ```printf```) and return from ```main``` a value of ```1``` (which tends to signify an error) immediately.
- If any of the characters of the command-line argument is not a decimal digit, your program should print the message ```Usage: ./caesar key``` and return from ```main``` a value of ```1```.
- Do not assume that ***k*** will be less than or equal to 26. Your program should work for all non-negative integral values of ***k***. In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for ***k*** that’s too big or almost too big to fit in an int. (Recall that an int can overflow.) But, even if ***k*** is greater than 26, alphabetical characters in your program’s input should remain alphabetical characters in your program’s output. For instance, if ***k*** is 
***27***, ```A``` should not become ```\``` even though ```\``` is ***27*** positions away from ```A``` in ASCII; ```A``` should become ```B```, since ```B``` is ***27*** positions away from ```A```, provided you wrap around from ```Z``` to ```A```.
- Your program must output ```plaintext: ``` (with two spaces but without a newline) and then prompt the user for a string of plaintext (using get_string).
- Your program must output ```ciphertext: ``` (with one space but without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext “rotated” by k positions; non-alphabetical characters should be outputted unchanged.
- Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though rotated, must remain lowercase letters.
- After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
