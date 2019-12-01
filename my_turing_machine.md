### exemple programme :
double 11
5
state	read	write	move	jump
1		0		e		e		e
1		1		0		1		2
2		1		1		1		2
2		0		0		1		3
3		1		1		1		3
3		0		1		0		4
4		1		1		0		4
4		0		0		0		5
5		1		1		0		5
5		0		1		1		1

tape	11000000
result	11011000

# avec retour ? char tape[2]
- tape longeur 2 bytes - 16 bits
- arg dans le premier bytes, result dans second

# avec deux valeurs ? char tape[3]
- tape longeur 3 bytes - 24 bits
- 2 args dans les 2 permiers bytes, result dans 3eme

# avec appel ?
char			*program_mult;
char			*progam_div;
t_machine		mult = machine_ini(program_mult);
t_machine		div = machine_ini(program_div);

// execute return error;
mult->tape[] = {2, 5};
if (!mult->execute(mult))
	return (machine_error);
div->tape[] = {mult->tape[2], 2};
if (!div->execute(div))
	return (machine_error);
div->tape[2] -> 5

les tableaux de char serait des registres ?

# PROGRAMS
## add 1 to bytes
00010011 -> write 0 to all 1 and write 1 to 0
00010100
00100100 -> just add 1 to big endian
00100101

start big endian
states	3
state	read	write	move	jump
1		0		1		1		2
		1		0		1		3
2		0		(stop)
		1		(stop)
3		0		1		1		2
		1		0		1		3

## mult
	a		b		c
	6	*	5	=	30
                .
00000110 00000101 00000000
       .
00000110 00000101 00000000
      .
00000110 00000101 00000000
                        .
00000110 00000101 00000000
      .
00000110 00000101 00000010
                       .
00000110 00000101 00000010
    .
00000110 00000101 00000110
               .
00000110 00000101 00000110
              .
00000110 00000101 00000110
       .
00000110 00000101 00000110
      .
00000110 00000101 00000110
                      .
00000110 00000101 00000110
     .
00000110 00000101 00001110
                     .
00000110 00000101 00001110
    .
00000110 00000101 00001110
             .
00000110 00000101 00011110

start big endian b
state	read	write	move	jump
1		0		0		b++		1
		1		1		a=1		2
		end		(STOP)
2		0		0		a++		2
		1		1		c=b+a	3
		end				b++		1
3		0		1		a++		2
		1		0		c++		3

a b et c sont des masques binaires contenant 1 bit vrai servant d'index de lecture
le pointeur principale bouge selon le retour des actions move.
leur valeur commence a 1, on peut faire des actions dessus avant de jump via des machines plus simples
des machines a univer 1D infini capable de retourner si on arrive a end d'un registre
et capable d'assigner des additions de pointeurs et d'itérer.

# addition ?
exemple c=b+a
a copier dans c puis :
	a	+	b	=	dans a 7(64)
    .   +     .  =	 .      
1
if (a == 0)
	a++
else
	jump 3
jump 2 b0
2
while(b == 0)
	b++
b = 0
b++ = 1
jump 1 a
3
while(b == 0)
	b++
b = 0
b++ = 1
end