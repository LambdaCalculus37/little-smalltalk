Class Float :Number
[
	= aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 66 self aNumber>]
			ifFalse: [super = aNumber]
|
	< aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 62 self aNumber>]
			ifFalse: [super < aNumber]
|
	> aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 63 self aNumber>]
			ifFalse: [ super > aNumber]
|
	+ aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 60 self aNumber>]
			ifFalse: [super + aNumber]
|
	- aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 61 self aNumber>]
			ifFalse: [super - aNumber]
|
	* aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 68 self aNumber>]
			ifFalse: [super * aNumber]
|
	/ aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 69 self aNumber>]
			ifFalse: [super / aNumber]
|
	^ aNumber
		^ <primitive 6 self aNumber>
			ifTrue:  [<primitive 88 self aNumber>]
			ifFalse: [super raisedTo: aNumber]
|
	arcCos
		^ Radian new: <primitive 85 self>
|
	arcSin
		^ Radian new: <primitive 84 self>
|
	arcTan
		^ Radian new: <primitive 86 self>
|
	asFloat
		^ self
|
	asString
		^ <primitive 78 self>
|
	ceiling
		^ <primitive 73 self>
|
	coerce: aNumber
		^ aNumber asFloat
|
	exp
		^ <primitive 79 self>
|
	floor
		^ <primitive 72 self>
|
	fractionPart
		^ <primitive 76 self>
|
	gamma
		^ <primitive 77 self>
|
	integerPart
		^ <primitive 75 self>
|
	ln
		^ <primitive 70 self>
|
	radix: aNumber
		^ <primitive 89 self aNumber>
|
	rounded
		^ <primitive 72 (self + 0.5)>
|
	sqrt
		^ <primitive 71 self>
|
	truncated
		^ (self < 0.0)  ifTrue:  [<primitive 73 self>]
				ifFalse: [<primitive 72 self>]
]
