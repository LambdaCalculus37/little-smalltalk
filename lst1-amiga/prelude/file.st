Class File :SequenceableCollection
[
	modeCharacter
		<primitive 133 self 0>
|
	modeInteger
		<primitive 133 self 2>
|
	modeString
		<primitive 133 self 1>
|
	at: aPosition
		<primitive 135 self aPosition>.
		^ self read
|
	at: aPosition put: anObject
		<primitive 135 self aPosition>.
		^ self write: anObject
|
	currentKey
		^ <primitive 136 self>
|
	first
		^ self at: 0
|
	next
		^ self read
|
	open: aName
		<primitive 130 self aName 'r' >
|
	open: aName for: opType
		<primitive 130 self aName opType >
|
	read
		^ <primitive 131 self>
|
	size
		^ <primitive 134 self>
|
	write: anObject
		^ <primitive 132 self anObject>
]
