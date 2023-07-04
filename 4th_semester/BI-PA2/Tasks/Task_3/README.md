# Task description
    The task is to implement the classes CRange and CRangeList, which will represent integer intervals and their lists.

    We assume intervals of integers. An interval can contain only one number or several numbers. We will write single-element intervals only as one number, i.e. 42. Multi-element intervals in square brackets. E.g. the interval <1..5> contains the numbers 1,2,3,4,5. A range of integers is implemented by the CRange class. Since we want to work with a large range of numbers, this class will store the interval limits as long long numbers (we also want to work with negative numbers). The CRange interface is:

    constructor (lo, hi)
    initializes the instance to an interval in the range lo to hi. The constructor checks that lo ≤ hi. If the condition is not met, a std::logic_error exception will be thrown (the standard exception from the stdexcept header file).
    next
    Derive other interfaces according to the constructions from the attached sample code, of course you can also add other methods depending on your implementation. It is only necessary to observe the size of the instance - max. 2x the size of long long.
    The CRangeList class will represent a list of such intervals. When folding the intervals into a CRangeList instance, we will store the intervals as compactly as possible. So, for example, we merge adjacent or overlapping intervals into one longer interval. The CRangeList instance will provide interfaces for inserting intervals, removing intervals, testing a value, and outputting. In the bonus test, the class will further offer an additional interface for ease of use (see below). The specific interface required will be:

    implicit constructor
    initializes an empty list of intervals
    destructor, copy constructor, op=
    they will be implemented if they are needed and if the automatically generated form is not enough. We recommend using a suitable container for storing intervals and leaving copying and moving to automatically generated code.
    includes(long long) / includes(CRange)
    method checks if the list of intervals contains the specified value / the entire specified interval of values. If yes, it returns true, if not, it returns false.
    +=
    additional intervals will be added to the list using this operator. The operator ensures that the added intervals are stored compactly (interval merging). Since we are working with whole numbers, merging intervals is somewhat unusual. It is natural to merge overlapping intervals, e.g.:
    <10..20> and <15..30>,
    <10..30> and <15..18>, where appropriate
    <10..20> and <20..30>,
    However, the intervals <10..20> and <21..30> are also merged, although they do not touch or overlap. However, together they cover the entire interval <10..30>. However, the intervals <10..19> and <21..30> do not merge anymore, they do not cover the number 20.
    -=
    this operator will remove further intervals from the list. Subtraction can also be understood as a set difference. The operator ensures that after removal the intervals are stored compactly (removal of unnecessary intervals).
    =
    this operator can be used to set the contents to a list of intervals on the right (compactly stored, of course).
    ==, !=
    operators compare the contents of two instances. We consider two instances to be identical if they have an identical list of intervals.
    <<
    operator outputs the contents of the list to the specified output stream. The list will be enclosed in braces, each interval separated by a comma. Single-element intervals will be displayed as a number, longer intervals in curly brackets. The format of the listing is obvious from the samples. The intervals will be displayed in ascending order.
    The task also offers a bonus test in which an additional interface is required to facilitate work with the list of intervals. When solving, you can decide whether to implement this extended interface (that is, try for a bonus) or not:

    leave the EXTENDED_SYNTAX preprocessor directive commented out if you are not going to implement the extended interface. Missing syntactic constructions will not be translated and the bonus test will not award extra points.
    If you are going to implement extended syntax, define the preprocessor directive EXTENDED_SYNTAX (uncomment). In this situation, the test environment will use the extended syntax and evaluate the fulfillment of the bonus test.
    Attention, if you define the preprocessor directive EXTENDED_SYNTAX and the necessary interface is not implemented, the compilation ends with an error.
    Interfaces required for the Syntax Bonus Test:
    constructor to initialize with a list of values
    fills the instance with the specified intervals,
    range for loop
    the CRangeList instance must be usable in the range for cycle, where iterate over individual intervals in ascending order,
    the output operator must always display the interval in decimal form, if the stream is set differently, the stream setting must be modified and then restored.