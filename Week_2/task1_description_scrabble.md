# Problem to Solve

In the game of Scrabble, players create words to score points, and the number of points is the sum of the point values of each letter in the word.\
![Here is points of each letter](https://www.google.com/url?sa=i&url=https%3A%2F%2Fdev.to%2Fthepracticaldev%2Fdaily-challenge-8-scrabble-word-calculator-41f6&psig=AOvVaw39UrgCg_pEtvV11_MJMQSj&ust=1715809111937000&source=images&cd=vfe&opi=89978449&ved=0CBIQjRxqFwoTCKjvgpaNjoYDFQAAAAAdAAAAABAE) \

For example, if we wanted to score the word “CODE”, we would note that the ‘C’ is worth 3 points, the ‘O’ is worth 1 point, the ‘D’ is worth 2 points, and the ‘E’ is worth 1 point. Summing these, we get that “CODE” is worth 7 points. \

In a file called scrabble.c in a folder called scrabble, implement a program in C that determines the winner of a short Scrabble-like game. Your program should prompt for input twice: once for “Player 1” to input their word and once for “Player 2” to input their word. Then, depending on which player scores the most points, your program should either print “Player 1 wins!”, “Player 2 wins!”, or “Tie!” (in the event the two players score equal points).

# How to Test
Your program should behave per the examples below.

```
$ ./scrabble
Player 1: Question?
Player 2: Question!
Tie!
```

```
$ ./scrabble
Player 1: red
Player 2: wheelbarrow
Player 2 wins!
```

```
$ ./scrabble
Player 1: COMPUTER
Player 2: science
Player 1 wins!
```

```
$ ./scrabble
Player 1: Scrabble
Player 2: wiNNeR
Player 1 wins!
```
