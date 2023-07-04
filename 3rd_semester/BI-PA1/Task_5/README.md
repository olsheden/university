# Task description
    The task is to create a program that will help the control tower radar operator.

    In air traffic control, it is important to watch for potential aircraft collisions. The radar senses the positions of the aircraft and the program checks the distances between the aircraft. We want to implement a program that, for a given set of aircraft coordinates, decides where there is a potential collision, i.e. which aircraft are closest to each other.

    The input to the program is the coordinates and the labels of the planes. For simplicity, we assume that the coordinates of the planes are planar, i.e., the position of the plane is determined by the x and y coordinates. The coordinates are in the form of decimal numbers. The coordinates are separated by a comma, followed by a colon and the name (identification) of the aircraft. The aircraft name is a string without spaces and whitespace, not more than 199 characters long, and is not unambiguous (there may be two or more aircraft with the same name in the input). There may be a large number of aircraft on the input, the number of which is not known in advance. The input ends with the active end of the file (EOF to stdin). The format of the input is obvious from the examples below.

    The output of the program is the distance of the closest pair of aircraft. If there are multiple pairs of aircraft at the same (smallest) distance, the program will output the number of pairs of aircraft at that (smallest) distance. This is followed by a listing of all pairs of planes that have this (smallest) distance between them. The listing of pairs of planes has no specified order (the lines of the listing can be arranged arbitrarily, as well as the planes in a pair on a line). When comparing, the test environment will adjust the listing if necessary.

    The program must treat the input data. If the input data is incorrect, the program will detect this, display an error message, and exit. The following is considered an error:

    Non-numeric coordinates (not a valid decimal number),
    missing/absent separators (comma, colon),
    less than two aircraft on the input (otherwise no minimum distance defined).
    Your program will be run in a limited test environment. It is limited by the run time (the limit can be seen in the log of the reference solution) and also limited by the size of the available memory. Depending on the chosen algorithm, the task may be more computationally demanding. A correct implementation of the naive algorithm passes all tests except the bonus test, so it has a chance to get a nominal 100% score. To pass the bonus test, a more efficient algorithm that can handle a larger volume of test data (large number of aircraft) in a short time is needed.

    Example of the program's work:
    Aircraft positions:
    0,0: KLM
    5,0: Lufthansa
    10.0: SmartWings
    7.0: AirFrance
    2.0: Qantas
    Distance of closest aircraft: 2.000000
    Pairs found: 2
    KLM - Qantas
    Lufthansa - AirFrance
    Aircraft position:
    0,5: Qantas
    5.0: KLM
    0.0: AirFrance
    5.5: Lufthansa
    2.5,2.5: KLM
    Distance of nearest aircraft: 3.535534
    Pairs found: 4
    Qantas - KLM
    AirFrance - KLM
    KLM - KLM
    KLM - Lufthansa
    Aircraft positions:
    -10,-5: Ryanair
    10,0: LOT
    12,12: SmartWings
    Distance of nearest aircraft: 12.165525
    Pairs found: 1
    LOT - SmartWings
    Aircraft position:
    -1000000,0: LOT
    1000000.0: KLM
    5000000,0: AirFrance
    Distance of nearest aircraft: 2000000.000000
    Pairs found: 1
    LOT - KLM
    Aircraft position:
    10,10: AirFrance
    10,10: Lufthansa
    20, 20: Ryanair
    20,20: Wizz
    20,20: Qantas
    10,10: LOT
    Distance of nearest aircraft: 0.000000
    Pairs found: 6
    AirFrance - Lufthansa
    AirFrance - LOT
    Lufthansa - LOT
    Ryanair - Wizz
    Ryanair - Qantas
    Wizz - Qantas
    Aircraft position:
    3,abc: CSA
    Incorrect entry.
    Aircraft position:
    0,0: LOT
    5.8 KLM
    Incorrect input.