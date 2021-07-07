temp <- <primitive 110 2 >
<primitive 112 temp 1		" set: " \
	#( #[ 33 96 245] \
	#(  ) ) >

<primitive 112 temp 2		" printString " \
	#( #[ 48 16 169 11 17 243 245] \
	#( 'test value '  ) ) >

<primitive 98 #Test \
	<primitive 97 #Test #Object #Smalltalk:prelude/test.st \
	#(  #var ) \
	#( #set: #printString  ) \
	temp 2 3 > >

