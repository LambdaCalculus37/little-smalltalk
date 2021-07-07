Class Radian :Magnitude
| value |
[
        new: x
                value <- <primitive 80 (x asFloat) >

|	< arg
		^ value < arg asFloat

|	= arg
		^ value = arg asFloat

|       sin
                ^ <primitive 81 value>

|       cos
                ^ <primitive 82 value>

|       tan
                ^ <primitive 81 value> / <primitive 82 value>

|       asFloat
                ^ value

|       printString
                ^ value asString , ' radians'
]
