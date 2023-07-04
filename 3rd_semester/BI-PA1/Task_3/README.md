# Task description
    The task is to implement a function (not the whole program, just the function) that will count how many times the bells on the tower will ring in a given time interval.

    We assume a clock on the tower that can ring the bells to tell time. The clock is equipped with a pair of bells:

    bell #1, which strikes the minutes. It always rings in multiples of 15 minutes, chiming 1x to 4x (XX:00 - 4x, XX:15 - 1x, XX:30 - 2x and XX:45 - 3x).
    Bell #2, which strikes the hours, rings as many times as the hour hand indicates. Thus at midnight 12 times, at 1:00 am 1x, at 2:00 am 2x, ..., at 12:00 am 12 times, at 1:00 pm 1x, at 2:00 pm 2x, ...,
    on Sundays, the clock is off all day. So the last bell rings on Saturday at 23:45 and then on Monday at 00:00.
    Our function receives two time data as parameters - the beginning and the end of the time interval. The start and end are given by year, month, day, hour and minute. The function calculates how many times the clock strikes one bell and the other bell during this interval. For the calculation, we consider a closed interval, so if it chimes at the beginning/end of the specified interval, we include these chimes in the result.

    The required function has the interface:

    int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2, 
            long long int * b1, long long int * b2 )
    y1, m1, d1, h1, i1
    are input parameters that represent the year, month, day, hour and minute of the beginning of the interval,
    y2, m2, d2, h2, i2
    are input parameters that represent the year, month, day, hour and minute of the end of the interval,
    b1
    is the output parameter into which the function will store the calculated number of bell rings #1. The function will set this parameter only if the input parameters are correct. If incorrect inputs are entered, the value cannot be determined. In this case, the function signals failure and leaves the output parameter unchanged.
    b2
    is the output parameter into which the function will store the calculated number of rings of bell #2. The function will only set this parameter if the input parameters are correct. If incorrect inputs are specified, the value cannot be determined. In this case, the function signals failure and leaves the output parameter unchanged.
    function return value
    will be set to 1 for success (correct input parameters) or 0 for failure (incorrect input parameters).
    If incorrect input parameters are entered, the return value should be 0 (failure). Correct input parameter values must satisfy:

    year is greater than 1600,
    month is valid (1 to 12),
    day is valid (1 to the number of days in the month),
    hour is valid (0 to 23),
    minute is valid (0 to 59),
    the specified interval start time does not occur until after the specified interval end time.
    Submit a source file that contains an implementation of the requested bells function. Add your other support functions that are called from bells to the source file. The function will be called from the test environment, so it is important to follow the specified function interface exactly. Use the code from the sample below as the basis for the implementation. Missing from the code is filling in the bells function (and any other support functions). The sample contains the test function main, the values given are used in the basic test. Note that the header file insertion and the main function are wrapped in a conditional compilation block (#ifdef/#endif). Please leave the conditional translation blocks in the committed source file as well. Conditional translation will simplify your work. When compiled on your machine, you can run and test the program normally. When compiling on Progtest, the main function and the header file insertion "disappear", i.e. they will not interfere with the header files and the main function of the test environment.

    When calculating the time, we consider the Gregorian calendar. That is, months always have 30 or always 31 days, the exception being February, which has 28 days (nonleap year) or 29 days (leap year). According to the Gregorian calendar:

    years are not leap years,
    except for years divisible by 4, which are leap years,
    except for years divisible by 100, which are not leap years,
    except for years divisible by 400, which are leap years,
    except for years divisible by 4000, which are not leap years. This rule has never been applied and has not yet been officially adopted. It is one of the proposals under consideration that would bring the Gregorian calendar closer to reality. We will consider it in our implementation.
    Thus, the years 1901, 1902, 1903, 1905, ... are non-transitive (rule 1), the years 1904, 1908, ..., 1996, 2004, ... are transitive (rule 2), the years 1700, 1800, 1900, 2100, ... are non-transitive (rule 3), the years 1600, 2000, 2400, ..., 3600, 4400, ... are transitive (rule 4), and the years 4000, 8000, ... are non-transitive (rule 5).

    Your program will be run in a limited test environment. It is limited by the run time (the limit is visible in the log of the reference solution) and also limited by the amount of available memory. The time limits are set so that a reasonable implementation of the naive algorithm passes all mandatory tests. A solution that performs well in the mandatory tests can receive a nominal 100% score. The bonus tests require time-efficient computation even for large intervals (high years well in excess of 4000).