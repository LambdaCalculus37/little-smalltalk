Class Char :Magnitude
[
	== aChar
		^ <primitive 6 self aChar>
			ifTrue:  [<primitive 46 self aChar>]
			ifFalse: [false]
|	< aChar
		^ <primitive 6 self aChar>
			ifTrue:  [<primitive 42 self aChar>]
			ifFalse: [self compareError]
|
	= aChar
		^ <primitive 6 self aChar>
			ifTrue:  [<primitive 46 self aChar>]
			ifFalse: [self compareError]
|	> aChar
		^ <primitive 6 self aChar>
			ifTrue:  [<primitive 43 self aChar>]
			ifFalse: [self compareError]
|
	asciiValue
		^ <primitive 59 self>
|
	asLowercase
		^ <primitive 54 self>
			ifTrue:  [<primitive 57 self>]
			ifFalse: [self]
|
	asUppercase
		^ <primitive 53 self>
			ifTrue:  [<primitive 57 self>]
			ifFalse: [self]
|
	asString
		^ <primitive 58 self>
|
	compareError
		^ self error: 'char cannot be compared to non char'
|
	digitValue		| i |
		((i <- <primitive 50 self>) isNil)
			ifTrue: [self error: 'digitValue on nondigit char'].
		^ i
|
	isAlphaNumeric
		^ <primitive 56 self>
|
	isDigit
		^ self between: $0 and: $9
|
	isLetter
		^ self isLowercase or: [self isUppercase]
|
	isLowercase
		^ self between: $a and: $z 
|
	isSeparator
		^ <primitive 55 self>
|
	isUppercase
		^ (self between: $A and: $Z)
|
	isVowel
		^ <primitive 51 self>
|
	printString
		^ '$' , <primitive 58 self>
]
