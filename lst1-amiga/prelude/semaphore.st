Class  Semaphore :List
| excessSignals |

[  new
	excessSignals <- 0

|  new: aNumber
	excessSignals <- aNumber

|  signal
	<primitive 148>.	"start atomic action"
	(self isEmpty)
	  ifTrue: [excessSignals <- excessSignals + 1]
	  ifFalse: [self removeFirst unblock].
	<primitive 149>		"end atomic action"

|  wait
	<primitive 148>.	"start atomic actions"
	(excessSignals = 0)
	  ifTrue: [self addLast: selfProcess.
		   selfProcess block]
	  ifFalse: [excessSignals <- excessSignals - 1].
	<primitive 149>		"end atomic actions"
]
