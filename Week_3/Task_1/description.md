# Plurality
## Problem to Solve
Elections come in all shapes and sizes. In the UK, the Prime Minister is officially appointed by the monarch, who generally chooses the leader of the political party that wins the most seats in the House of Commons. The United States uses a multi-step Electoral College process where citizens vote on how each state should allocate Electors who then elect the President.

Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” or “winner take all”). In the plurality vote, every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

For this problem, you’ll implement a program that runs a plurality election, per the below.

## The code
Each candidate has two fields: a string called ```name``` representing the candidate’s name, and an int called ```votes``` representing the number of votes the candidate has.
```
// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;
```
Then the program copies command-line arguments into the array ```candidates```. After that it asks the user to type in the number of voters:
```
int voter_count = get_int("Number of voters: ");
```
Then, the program lets every voter type in a vote, calling the ```vote``` function on each ```candidate``` voted for. Finally, ```main``` makes a call to the ```print_winner``` function to print out the winner (or winners) of the election.

## Be sure to test your code to make sure it handles…

- An election with any number of candidate (up to the MAX of 9)
- Voting for a candidate by name
- Invalid votes for candidates who are not on the ballot
- Printing the winner of the election if there is only one
- Printing the winner of the election if there are multiple winners
