temp <- <primitive 110 3 >
<primitive 112 temp 1		" three " \
	#( #[ 16 128 0 242 245] \
	#( #four  ) ) >

<primitive 112 temp 2		" one " \
	#( #[ 64 160 96 16 32 129 1 242 245] \
	#( #Two #two:  ) ) >

<primitive 112 temp 3		" start " \
	#( #[ 32 128 0 243 245] \
	#( #one  ) ) >

<primitive 98 #One \
	<primitive 97 #One #Object #Smalltalk:prelude/tests.st \
	#(  #two ) \
	#( #three #one #start  ) \
	temp 1 3 > >

temp <- <primitive 110 2 >
<primitive 112 temp 1		" four " \
	#( #[ 48 168 242 32 128 1 242 245] \
	#( 'in four' #gak  ) ) >

<primitive 112 temp 2		" two: " \
	#( #[ 33 128 0 242 245] \
	#( #three  ) ) >

<primitive 98 #Two \
	<primitive 97 #Two #Object #Smalltalk:prelude/tests.st \
	#(  ) \
	#( #four #two:  ) \
	temp 2 2 > >

