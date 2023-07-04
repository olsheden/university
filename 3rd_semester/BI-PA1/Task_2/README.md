# Task description
    The task is to implement a program that decides for a trio of given points in the 2D plane whether they lie on a common line.

    The input to the program is the X and Y coordinates of the triplet of points in the 2D plane. The coordinates are given as two decimal numbers, the first number representing the X component and the second number representing the Y component.

    The program analyzes the relative position of the given points and decides which of the three conclusions is valid:

    two or all three of the specified points are congruent,
    the 3 points are different from each other and do not lie on the same line, or
    the specified 3 points are different from each other and lie on the same line (then the program additionally determines the intersection point).
    The format of the output is clear from the examples below.
    The program must check the input data for correctness. If an incorrect value (non-numeric) is entered on the input, then the program will detect an error, display an error message on the standard output as shown in the example, and exit.

    The program work samples:
    Point A:
    1 2
    Point B:
    3 4
    Item C:
    5 6
    The points are on one prime.
    The middle point is point B.
    Point A:
    0.1 0.2
    Point B:
    0.3 0.4
    Point C:
    0.5 0.6
    Points lie on one prime.
    The middle point is point B.
    Point A:
    10 10
    Point B:
    0 10
    Point C:
    10 0
    The points do not lie on one prime.
    Point A:
    0 1
    Point B:
    0 3
    Point C:
    0 2
    The points lie on one prime.
    The middle point is point C.
    Point A:
    1 0
    Point B:
    2 0
    Point C:
    -3 0
    Points lie on one prime.
    The middle point is point A.
    Point A:
    1 1
    Point B:
    2 2
    Point C:
    1 1
    Some points merge.
    Point A:
    10 20
    Point B:
    5 xyz
    Incorrect entry.