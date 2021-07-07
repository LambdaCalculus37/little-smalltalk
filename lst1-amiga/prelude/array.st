Class Array :ArrayedCollection
[
	new: aValue
		^ <primitive 114 aValue>
|
	at: aNumber
		( (aNumber < 1) or: [aNumber > <primitive 4 self> ] )
			ifTrue: [ self error: 'index error'. ^nil ].
		^ <primitive 111 self aNumber >
|
	at: aNumber put: aValue
		( (aNumber < 1) or: [aNumber > <primitive 4 self> ] )
			ifTrue: [ self error: 'index error'. ^nil ].
		<primitive 112 self aNumber aValue >.
		^ aValue
|
	grow: newObject
		^ <primitive 113 self newObject>
|
	printString		| value i |
		value <- ')'.
		i <- <primitive 4 self>.
		[i > 0] whileTrue: 
			[ value <- <primitive 111 self i>  printString ,
					' ', value.
				    i <- i - 1].
		^ '#( ' , value
|
	size
		^ <primitive 4 self>
]
