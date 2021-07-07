Class Object
[
 	== anObject
		^ <primitive 7 self anObject >
|
       ~~ x
                ^ (self == x) not
|
 	= x
		^ (self == x)
|
 	~= x
		^ (self = x) not
|
 	asString
		^ self class printString
|
        asSymbol
                ^ self asString asSymbol
|
	class
		^ <primitive 1 self >
|
        copy
                ^ self shallowCopy
|
        deepCopy		| size newobj |
		size <- <primitive 4 self>.
		(size < 0) 
			ifTrue: [^ self] "if special just copy object"
			ifFalse: [ newobj <- self class new.
			(1 to: size) do: [:i |
				<primitive 112 newobj i
					( <primitive 111 self i > copy ) > ].
				^ newobj ]
|
 	do: aBlock			| item |
		item <- self first.
		^ [item notNil] whileTrue:
			[aBlock value: item.  item <- self next]
|
	error: aString
		<primitive 122 aString self>
|
        first
                ^ self
|
        isKindOf: aClass                | objectClass |
                objectClass <- self class.
                [objectClass notNil] whileTrue:
                        [(objectClass == aClass) ifTrue: [^ true].
                         objectClass <- objectClass superClass].
                ^ false
|
        isMemberOf: aClass
                ^ aClass == self class

|
        isNil
                ^ false
|
        next
                ^ nil
|
        notNil
                ^ true
|
 	print
		<primitive 121 (self printString) >
|
 	printString
		^ self asString

|       respondsTo: cmd
                ^ self class respondsTo: cmd

|       shallowCopy		| size newobj |
		size <- <primitive 4 self>.
		(size < 0) 
			ifTrue: [^ self] "if special just copy object"
			ifFalse: [ newobj <- self class new.
				(1 to: size) do: [:i |
					<primitive 112 newobj i
						<primitive 111 self i > > ].
					^ newobj ]
]
