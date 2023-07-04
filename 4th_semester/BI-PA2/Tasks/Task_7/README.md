# Task description
    The task is to implement a class template that can compile score sheets depending on the entered inputs - the results of matches between pairs of opponents.

    We assume that we have several rivals. In one match, a pair of opponents compete, the result of the match is somehow described (for example, by a Boolean value, a pair of points, a pair of times, ...). Since we want to have a generic class, the result of the match will be represented as a generic data type. In this way, several results for the entered pairs of opponents will be inserted into the class (opponents are uniquely identified by name - string). Subsequently, we want to find out whether, on the basis of the entered results, it is possible to compile a clear list of results and possibly calculate this list. The trick is that when compiling the result, we only want to base it on the winner/loser information from the entered matches.

    The result sheet is uniquely determined if for each opponent Xi at position i:

    Xi beat all opponents Xj, i+1 ≤ j ≤ n. He beat opponents either directly or indirectly (Xi beat Xa, Xa beat Xb, ..., Xz beat Xj, i+1 ≤ a < b < ... < j ≤ n),
    Xi has not won or tied with any opponent Xk, 0 ≤ k ≤ i-1.
    Let's take an example where it was specified that A will beat B and B will defeat C. Then the correct score sheet is probably A B C. But if it were specified that:

    A beats B
    B beats C
    C beats A
    eventual:
    A beats B
    A beats C
    eventual:
    A beats B
    B draws with C
    then the scoreboard cannot be determined unambiguously (we would have to provide information about other matches or determine the order based on other criteria, we will not do that in this task).
    It was mentioned that a match is specified as a triple (opponent1, opponent2, result) where the result is some data type describing such as scores, times, or whatever. The result needs to be converted to information about the winner/draw/loser, the comparator (comparator) passed to the method for determining the result sheet will be in charge of this. A comparator is a function, functor, or lambda-expression that returns a return value for a given result:

    negative if opponent1 lost,
    zero if opponent1 and opponent2 tied,
    positive if opponent1 won.
    The overall interface of the CContest class template will be:

    the template is parameterized by the generic parameter M_
    this type describes the result of the match. The data type M_ is guaranteed to be moveable, copyable, and destructible (CopyConstructibe, MoveConstructible, CopyAssignable, MoveAssignable, and Destructible). Other properties of the type are not guaranteed, in particular, it is not guaranteed that the type M_ has an implicit constructor (it may not be DefaultConstructible).
    implicit constructor
    creates an empty instance of CContest,
    addMatch(contestant1, contestant2, result)
    method will add the result between contestant1 and contestant2. Opponents are entered as strings. The result result is of data type M_. The method stores information about this match in some storage in its instance. AddMatch calls can be chained. The method throws a std::logic_error exception if the match result between contestant1 and contestant2 has already been specified.
    isOrdered (comparator)
    the method decides whether the completed match results lead to a clear score sheet or not. The return value is true if the result list is unique, false if not. The call parameter is a comparator - a function, functor or lambda expression that will be called when getting the match result (converts M_ to a negative number / zero / positive number as described above). The method must not modify the CContest instance and must not throw exceptions.
    results (comparator)
    method calculates the result sheet. The result is an STL list (std::list) of strings with the names of the opponents in order from first (overall winner) to last. If the result list cannot be constructed (it is not unambiguous), the method throws a std::logic_error exception. The comparator parameter has the same meaning as for the isOrdered method.