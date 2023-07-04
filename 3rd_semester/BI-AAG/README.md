# The task
The goal of this scoring programming problem is to implement algorithms that allow you to find a minimal deterministic finite automaton that accepts the intersection, or union, of the languages specified by a pair of finite automata. Thus, the goal is to implement a set of two functions in C++ with signatures

  •DFA unify(const NFA&, const NFA&); and
  •DFA intersect(const NFA&, const NFA&); .
Both of these functions must return the minimum automaton for the language.

The input, or output, of the algorithms are finite automata in the form of NFA and DFA structures, respectively. The first structure, NFA, represents a nondeterministic finite automaton (but for some transition functions it can be said to be deterministic). The second structure, DFA, represents only a deterministic finite automaton. These structures are just simple data structures that maintain the data representing the automaton and do not perform any content validity checks. Proper initialization and filling with content is the concern of whoever creates them.

These structures are defined in the test environment (so don't define them in your task), see the sample code in the attached sample file. For simplicity, states are defined as unsigned values and alphabet symbols as uint8_t values.

The input to the unify and intersect functions are guaranteed to be valid non-deterministic finite automata. They will satisfy the following properties:

The sets of states (NFA::m_States) and alphabet symbols (NFA::m_Alphabet) will be non-empty.
The initial and final states (NFA::m_InitialState and NFA::m_FinalStates, respectively) will be elements of the set of NFA::m_States.
If there is no alphabet symbol q and a transition defined in the automaton for a state, then the key (q, a) will not exist in NFA::m_Transitions at all.
Also, only symbols and states that are specified in the alphabet symbol set and the state set occur in the NFA::m_Transitions table.
The comparison of automata with the reference result is done through testing the isomorphism of transition functions of minimal deterministic finite automata and sets of finite states. Thus, your output may differ from the reference output at most in the naming of the states, otherwise it will be evaluated as incorrect. The resulting DFA must also satisfy the conditions of the automaton definition, i.e. the same as above for the NFA must apply (except for the obvious changes due to different transition function definitions).

If the result is an automaton accepting an empty language, a single-state automaton with an unchanged alphabet, an empty set of transitions and end-states must be passed (see one of the sample tests). It may also happen that the two input automata are over different alphabets. We then expect the result to be an automaton over the union of these alphabets.

Submit a source file that contains the implementation of the required functions for the task. Add your other supporting functions or data structures to the source file. The functions will be called from the test environment, so it is important to follow the specified function interface exactly. Failure to do so will result in a compilation error. Use the code from the sample below as a basis for implementation. Missing from the code are the implementations of the two functions mentioned above (and any other supporting functions or data structures). The sample contains a test function main, the values given are used in the basic test. Note that the insertion of header files, DFA and NFA structures, and the main function are wrapped in a conditional compilation block (#ifdef/#endif). Leave the definitions of these structures, the include preprocessor directives, and the main function in the conditional compilation blocks and in the committed source file, or your program will not compile.

Conditional translation will simplify your work. You can run and test the program normally while it is compiled on your computer. However, when compiling on Progtest, everything inside these blocks will "disappear", i.e. it will not interfere with header files, already defined structures or main test environment functions.

For a basic implementation, you can use the downloadable file below in the Sample Data section. This file also contains some basic tests, but keep in mind that the results of your implementation may differ in the naming of the states. The tests are set according to the results given by one of the reference solutions. So you may need to modify them.

Your program will be run in a limited test environment. It is limited by the run time (the limit is visible in the log of the reference solution) and also limited by the amount of memory available.

Notes:
  •The necessary algorithms for this assignment have been discussed in lectures and exercises.
  •To be minimal, an automaton must satisfy certain properties.
  •Keep in mind that the inputs are various valid automata as defined in the lecture. For example, there may be only one end state and it may be in an unreachable part of •the automaton (i.e., the automaton language may be empty) or there may be no end state.
  •The output of both implemented functions must be a valid automaton. In particular, pay attention to the correct initialization of the DFA attributes due to the constraints above.
  •The time limit is set quite benevolently. It should be sufficient for a naive implementation of the algorithms from the lecture. However, not all algorithms are suitable.
  •Think carefully about which unification algorithm you will implement. By choosing appropriately, the implementation of the problem can be considerably shortened.
  •The sample data is set according to one of the reference solutions. The numbering of the states is chosen in the order of the visit of a given state by the BFS algorithm
  started from the initial state of the automaton. The expansion of edges in the transition diagram is done in the lexicographic order of the automaton alphabet, i.e., if state q expands and there are transitions δ(q, b) = p and δ(q, a)=r, we first discover state r.
  •The determinization algorithm performed as presented in the lecture produces an automaton with states that satisfy certain properties. You can use them to make your program more efficient.