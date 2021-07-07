Class ByteArray :ArrayedCollection
[
	new: size
		^ <primitive 116 size>
|
	at: index
		^ <primitive 118 self index>
|
	at: index put: value
		<primitive 119 self index value>
|
	printString	| str |
		str <- '#[ '.
		(1 to: self size)
			do: [:i | str <- str , (self at: i) printString , ' '].
		^ str , ']'
|
	size
		^ <primitive 117 self>
]

