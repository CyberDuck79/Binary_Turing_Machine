# BINARY TURING MACHINE
## Personnal project
After studying the turing machine it became clear to me that modern computers are turing machines whose memory is the "abstract tape" and where there only to "symbols" in the alphabet : the 1 and the 0.  
It is an attempt to implement a binary turing machine with a "tape" of 8 bits.  
I wrote only two programs, in the form of transitions table, one for increment a number and another two decrement a number.  
## Transitions table Syntax :
X <- number of states  
state_nb:symbol_read:symbol_to_write:direction:new_state  
direction : 0 left, 1 right  
reading starts right.  
An error occur if there no state to go after a transition.  
An error occur if the the read head comes out of memory.  