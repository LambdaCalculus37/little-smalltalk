temp <- <primitive 110 13 >
<primitive 112 temp 1		" up " \
	#( #[ 91 98 245] \
	#(  ) ) >

<primitive 112 temp 2		" turn: " \
	#( #[ 19 33 192 99 245] \
	#(  ) ) >

<primitive 112 temp 3		" location " \
	#( #[ 16 17 129 0 243 245] \
	#( #@  ) ) >

<primitive 112 temp 4		" isUp " \
	#( #[ 18 243 245] \
	#(  ) ) >

<primitive 112 temp 5		" goTo: " \
	#( #[ 18 246 11 16 17 33 10 49 33 10 50 250 4 177 242 \
 33 10 49 96 33 10 50 97 245] \
	#(  ) ) >

<primitive 112 temp 6		" go: " \
	#( #[ 19 128 0 128 1 33 194 10 41 16 192 114 19 128 0 \
 128 2 33 194 10 41 17 192 115 32 34 35 129 3 129 \
 4 242 245] \
	#( #radians #sin #cos #@ #goTo:  ) ) >

<primitive 112 temp 7		" extent:to: " \
	#( #[ 33 10 49 33 10 50 34 10 49 34 10 50 250 4 176 \
 242 245] \
	#(  ) ) >

<primitive 112 temp 8		" erase " \
	#( #[ 250 0 170 242 245] \
	#(  ) ) >

<primitive 112 temp 9		" down " \
	#( #[ 92 98 245] \
	#(  ) ) >

<primitive 112 temp 10		" direction: " \
	#( #[ 33 99 245] \
	#(  ) ) >

<primitive 112 temp 11		" direction " \
	#( #[ 19 243 245] \
	#(  ) ) >

<primitive 112 temp 12		" circleRadius: " \
	#( #[ 16 17 33 250 3 174 242 245] \
	#(  ) ) >

<primitive 112 temp 13		" new " \
	#( #[ 32 128 0 242 32 49 129 2 242 32 5 100 5 100 129 \
 3 129 4 242 245] \
	#( #up 0.0 #direction: #@ #goTo:  ) ) >

<primitive 98 #Pen \
	<primitive 97 #Pen #Object #Smalltalk:prelude/pen.st \
	#(  #x #y #up #direction ) \
	#( #up #turn: #location #isUp #goTo: #go: #extent:to: #erase #down #direction: #direction #circleRadius: #new  ) \
	temp 4 8 > >

temp <- <primitive 110 2 >
<primitive 112 temp 1		" goTo: " \
	#( #[ 32 128 0 247 6 32 33 145 1 248 21 242 16 32 128 \
 2 33 130 3 242 32 128 4 242 32 33 145 1 242 32 \
 128 5 242 245] \
	#( #isUp #goTo: #location #add:to: #up #down  ) ) >

<primitive 112 temp 2		" setForm: " \
	#( #[ 33 96 245] \
	#(  ) ) >

<primitive 98 #PenSave \
	<primitive 97 #PenSave #Pen #Smalltalk:prelude/pen.st \
	#(  #saveForm ) \
	#( #goTo: #setForm:  ) \
	temp 2 8 > >

temp <- <primitive 110 3 >
<primitive 112 temp 1		" with:displayAt: " \
	#( #[ 34 10 49 115 34 10 50 116 16 225 7 50 39 10 49 \
 117 39 10 50 118 33 128 0 242 33 37 10 49 35 192 \
 37 10 50 36 192 129 1 129 2 242 33 128 3 242 33 \
 38 10 49 35 192 38 10 50 36 192 129 1 129 2 242 \
 93 243 179 242 245] \
	#( #up #@ #goTo: #down  ) ) >

<primitive 112 temp 2		" add:to: " \
	#( #[ 16 5 53 160 241 33 11 50 242 241 34 11 51 242 189 \
 242 245] \
	#(  ) ) >

<primitive 112 temp 3		" new " \
	#( #[ 5 32 160 96 245] \
	#(  ) ) >

<primitive 98 #Form \
	<primitive 97 #Form #Object #Smalltalk:prelude/pen.st \
	#(  #lines ) \
	#( #with:displayAt: #add:to: #new  ) \
	temp 8 11 > >

temp <- <primitive 110 3 >
<primitive 112 temp 1		" spiral:angle: " \
	#( #[ 81 33 178 225 3 10 16 35 129 0 241 34 129 1 242 \
 243 179 242 245] \
	#( #go: #turn:  ) ) >

<primitive 112 temp 2		" poly:length: " \
	#( #[ 33 224 14 16 34 129 0 241 82 128 1 33 190 129 2 \
 242 243 183 242 245] \
	#( #go: #pi #turn:  ) ) >

<primitive 112 temp 3		" withPen: " \
	#( #[ 33 96 245] \
	#(  ) ) >

<primitive 98 #PenShow \
	<primitive 97 #PenShow #Object #Smalltalk:prelude/pen.st \
	#(  #bic ) \
	#( #spiral:angle: #poly:length: #withPen:  ) \
	temp 4 9 > >

