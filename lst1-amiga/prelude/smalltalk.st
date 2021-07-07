Class Smalltalk :Dictionary
[
	clearScreen
		<primitive 162>
|
	date
		^ <primitive 160 >
|
	debug: n
		^ <primitive 8 2 n>
|
	display
		^ <primitive 8 1 1>
|
	displayAssign
		^ <primitive 8 1 2>
|
	doPrimitive: primNumber withArguments: argArray
		^ <primitive 30 primNumber argArray>
|
	noDisplay
		^ <primitive 8 1 0>
|
	perform: aMessage withArguments: argArray
		^ <primitive 143 argArray aMessage >
|
	sh: command
		^ <primitive 125 command >
|
	time: aBlock		| start |
		start <- <primitive 161>.
		aBlock value.
		^ <primitive 161> - start
]
