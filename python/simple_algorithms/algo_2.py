"""
Algo 2 (Coin change problem)
Given:
A player can score only 3,5,10 runs.
Given the total run scored by the player, calculate the possible combination of 3,5,10 from that score.

Example:
Input: n = 20
Output: 4
There are following 4 ways to reach 20
(10, 10)
(5, 5, 10)
(5, 5, 5, 5)
(3, 3, 3, 3, 3, 5)

Approach:
Create an array of size (N+1)
Everytime a player hits 3, update the array such that arr[i] += arr[i-3]
Similarly for 5, arr[i] += arr[i-5]
Similarly for 10, arr[i] += arr[i-10]
"""
# Score (Input) 
N = 20
possible_scoring_options = [3,5,10]

x = [0] * (N+1)
x[0] = 1

for score in possible_scoring_options:
    for i in range(score, N+1):
        x[i] += x[i-score]

print("Number of combination: ", x[N])
