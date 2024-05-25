# Runoff
## Problem to Solve
You already know about plurality elections, which follow a very simple algorithm for determining the winner of an election: every voter gets one vote, and the candidate with the most votes wins.
There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference. 
By considering ranked preferences, a voting system may be able to choose a winner that better reflects the preferences of the voters.
One such ranked choice voting system is the instant runoff system. In an instant runoff election, voters can rank as many candidates as they wish. If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.

If no candidate has more than 50% of the vote, then an “instant runoff” occurrs. The candidate who received the fewest number of votes is eliminated from the election, and anyone who originally chose that candidate as their first preference now has their second preference considered. Why do it this way? Effectively, this simulates what would have happened if the least popular candidate had not been in the election to begin with.

The process repeats: if no candidate has a majority of the votes, the last place candidate is eliminated, and anyone who voted for them will instead vote for their next preference (who hasn’t themselves already been eliminated). Once a candidate has a majority, that candidate is declared the winner.

Sounds a bit more complicated than a plurality vote, doesn’t it? But it arguably has the benefit of being an election system where the winner of the election more accurately represents the preferences of the voters. 

**In a file called runoff.c in a folder called runoff, create a program to simulate a runoff election.**

## The code in runoff.c
Every ```candidate``` has a ```string``` field for their ```name```, an ```int``` representing the number of ```votes``` they currently have, and a ```bool``` value called ```eliminated``` that indicates whether the candidate has been eliminated from the election. The array ```candidates``` will keep track of all of the candidates in the election.

```preferences``` is the two-dimensional array. The array ```preferences[i]``` will represent all of the preferences for ```voter``` number ```i```. The integer, ```preferences[i][j]```, will store the index of the candidate, from the ```candidates``` array, who is the jth preference for voter i.

Now onto ```main```. After determining the number of candidates and the number of voters, the main voting loop begins, giving every voter a chance to vote. As the voter enters their preferences, the ```vote``` function is called to keep track of all of the preferences. If at any point, the ballot is deemed to be invalid, the program exits.

Once all of the votes are in, another loop begins: this one’s going to keep looping through the runoff process of checking for a winner and eliminating the last place candidate until there is a winner.

The first call here is to a function called ```tabulate```, which should look at all of the voters’ preferences and compute the current vote totals, by looking at each voter’s top choice candidate who hasn’t yet been eliminated. Next, the ```print_winner``` function should print out the winner if there is one; if there is, the program is over. But otherwise, the program needs to determine the fewest number of votes anyone still in the election received (via a call to ```find_min```). If it turns out that everyone in the election is tied with the same number of votes (as determined by the ```is_tie``` function), the election is declared a tie; otherwise, the last-place candidate (or candidates) is eliminated from the election via a call to the ```eliminate``` function.
