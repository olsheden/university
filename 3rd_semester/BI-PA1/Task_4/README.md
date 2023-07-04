# Task description
    The task is to implement a program that will analyze a given number sequence.

    We assume a sequence of numbers. From this sequence we select continuous intervals, for example we can select the interval between the 5th and 10th given number. The interval must contain at least two numbers from the input sequence. For the selected interval, we determine the sum of the numbers that make it up. In this way, we select all possible intervals from the input sequence and for each interval we determine its sum. We are interested in how many pairs of different intervals will have the same sum.

    For example, for the input sequence:
    1 5 2 4 2 2 2
    there are a total of 21 possible intervals of length at least 2:
    0..1: 1 5 sum=6
    0..2: 1 5 2 sum=8
    0..3: 1 5 2 4 sum=12
    0..4: 1 5 2 4 2 sum=14
    0..5: 1 5 2 4 2 2 sum=16
    0..6: 1 5 2 4 2 2 2 sum=18
    1..2: 5 5 2 sum=7
    1..3: 5 2 4 sum=11
    1..4: 5 2 4 2 sum=13
    1..5: 5 2 4 2 2 sum=15
    1..6: 5 2 4 2 2 2 sum=17
    2..3: 2 4 sum=6
    2..4: 2 4 2 sum=8
    2..5: 2 4 2 2 sum=10
    2..6: 2 4 2 2 2 sum=12
    3..4: 4 2 sum=6
    3..5: 4 2 2 sum=8
    3..6: 4 2 2 2 sum=10
    4..5: 2 2 sum=4
    4..6: 2 2 2 sum=6
    5..6: 2 2 sum=4
    And from these 21 intervals, 12 pairs of different intervals with the same sum can be selected:
    0..1 ~ 2..3 sum=6  
    0..1 ~ 3..4 sum=6  
    0..1 ~ 4..6 sum=6  
    0..2 ~ 2..4 sum=8  
    0..2 ~ 3..5 sum=8  
    0..3 ~ 2..6 sum=12 
    2..3 ~ 3..4 sum=6  
    2..3 ~ 4..6 sum=6  
    2..4 ~ 3..5 sum=8  
    2..5 ~ 3..6 sum=10 
    3..4 ~ 4..6 sum=6  
    4..5 ~ 5..6 sum=4  
    The input to the program is a sequence of integers (positive, zero and negative). The input sequence ends when the end of the input is reached (EOF). There can be at most 2000 numbers in the input sequence.

    The output of the program is the number of pairs of intervals found with the same sum.

    The program must detect incorrect input. Consider the following as an error:

    the input sequence is empty (contains 0 numbers),
    the input sequence is too long (over 2000 numbers),
    the input value is not a valid integer.
    The problem is evaluated in bonus mode. Depending on the efficiency of the submitted program, the evaluation may be reduced (very inefficient program) or, on the contrary, extra points may be awarded in the bonus tests (efficient solution that can process longer input sequences quickly).

    Example of program work:
    Sequence:
    1 5 2 4
    Number of pairs: 1
    Sequence:
    1 5 2 4 2 2 2
    Number of pairs: 12
    Sequence:
    1 5 6
    20 -20
    Number of pairs: 3
    Sequence:
    2 2 1 7 7
    Number of pairs: 0
    Sequence:
    1 1 2 3 5 8
    Number of pairs: 0
    Sequence:
    abcd
    Incorrect input.