Class Class
[
	edit
		<primitive 150 self>
|
	list
		<primitive 157 self>
|
 	new		| superclass newinstance |
		superclass <- <primitive 151 self>.
		<primitive 3 superclass >
			ifTrue: [newinstance <- superclass new ]. 
		newinstance <- <primitive 153 self newinstance >.
		<primitive 155 self #new > 
			ifTrue: [newinstance <- newinstance new].
		^ newinstance
|
 	new: aValue 		| superclass newinstance |
		superclass <- <primitive 151 self>.
		<primitive 3 superclass >
			ifTrue: [newinstance <- superclass new ]. 
		newinstance <- <primitive 153 self newinstance >.
		<primitive 155 self #new: > 
			ifTrue: [newinstance <- newinstance new: aValue ].
		^ newinstance
|
 	printString
		^ <primitive 152 self >
|
	respondsTo
		<primitive 154 self>
|
	respondsTo: aSymbol		| aClass |
		aClass <- self.
		[aClass notNil] whileTrue:
			[ <primitive 155 aClass aSymbol> ifTrue: [ ^ true ].
			 aClass <- aClass superClass ].
		^ false
|
	superClass
		^ <primitive 151 self>

|
	variables
		^ <primitive 158 self>
|
	view
		<primitive 156 self>
]
