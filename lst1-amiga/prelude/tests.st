Class One
| two |
[
	start
		^ self one
|
	one
		two <- Two new.
		two two: self
|
	three
		two four
]
Class Two
[
	two: back
		back three
|
	four
		'in four' print.
		self gak
]

