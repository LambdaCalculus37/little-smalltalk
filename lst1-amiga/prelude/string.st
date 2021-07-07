Class String :ArrayedCollection
[
	, aString
		^ <primitive 103 self 
			(<primitive 6 self aString>
				ifTrue:  [aString]
				ifFalse: [aString printString])>
|
	= aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 101 self aString> = 0]
			ifFalse: [self compareError]
|
	< aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 101 self aString> < 0]
			ifFalse: [self compareError]
|
	<=  aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 101 self aString> <= 0]
			ifFalse: [self compareError]
|
	>=  aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 101 self aString> >= 0]
			ifFalse: [self compareError]
|
	>  aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 101 self aString> > 0]
			ifFalse: [self compareError]
|
	asSymbol
		^ <primitive 108 self>
|
	at: aNumber
		^ <primitive 104 self aNumber>
|
	at: aNumber put: aChar
		<primitive 105 self aNumber aChar>
|
	compareError
		^ self error: 'strings can only be compared to strings'
|
	copyFrom: start to: stop
		^ <primitive 106 self start (stop - start + 1) >
|
	copyFrom: start length: len
		^ <primitive 106 self start len >
|
	deepCopy
		^ <primitive 107 self >
|
	new: size
		^ <primitive 115 size>
|
	printAt: aPoint
		<primitive 126 self (aPoint x) (aPoint y)>
|
	printString
		^ <primitive 109 self>
|
	print
		<primitive 121 self>
|
	size
		^ <primitive 100 self>
|
	sameAs: aString
		^ <primitive 6 self aString>
			ifTrue:  [<primitive 102 self aString>]
			ifFalse: [self compareError]
]
