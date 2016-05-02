CST229 - Regular Language Recognizer
Alberto Martinez
Submitted to: Metzler

This program will take a file as input and turn the contents of that file
into a state machine.  Then, the program will accept input from the user
and determine whether the provided input is acceptable to the derived state
machine.

The machine input file is formatted to accept 4 different parts.  The first
part is the alphabet which is simply a listing of all acceptable characters
for the language.  The second part will define the states.  There can be
1 - n states and therefore each state is made on-the-fly.  Each line
preceded by a T will create a new state in order starting at 0.  So the
first T line will be state 0, the second T line will be state 1 and so on.
The third part is the starting state of the machine.  This is a single
line preceded by a S with a number designating the starting state.  The
final part is setting the states which are acceptable.  This must be the
final line and the line must be preceded with an 'F'.  The numbers
following the F are the states that will be set as accepting states.

The scope of this program allows only for 10 states to be defined.
In the state definitions, the '*' denotes a wild card which summarizes
"all characters in the alphabet."

machine format:

<alphabet>
T<states and their transitions>
S<starting state>
F<final state>