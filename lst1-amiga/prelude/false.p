temp <- <primitive 110 5 >
<primitive 112 temp 1		" not " \
	#( #[ 91 243 245] \
	#(  ) ) >

<primitive 112 temp 2		" ifFalse: " \
	#( #[ 33 165 243 245] \
	#(  ) ) >

<primitive 112 temp 3		" ifTrue: " \
	#( #[ 93 243 245] \
	#(  ) ) >

<primitive 112 temp 4		" ifFalse:ifTrue: " \
	#( #[ 33 165 243 245] \
	#(  ) ) >

<primitive 112 temp 5		" ifTrue:ifFalse: " \
	#( #[ 34 165 243 245] \
	#(  ) ) >

<primitive 98 #False \
	<primitive 97 #False #Boolean #Smalltalk:prelude/false.st \
	#(  ) \
	#( #not #ifFalse: #ifTrue: #ifFalse:ifTrue: #ifTrue:ifFalse:  ) \
	temp 3 2 > >

