Class  Process

[  block
	(self state == #TERMINATED)
	    ifTrue: [self termErr: 'block'.  ^ nil].
	<primitive 145  self 2>.
	^ self state

|  resume
	(self state == #TERMINATED)
	    ifTrue: [self termErr: 'resume'.  ^ nil].
	<primitive 145  self 0>.
	^ self state

|  suspend
	(self state == #TERMINATED)
	    ifTrue: [self termErr: 'suspend'.  ^ nil].
	<primitive 145  self 1>.
	^ self state

|  state  | pstate |
	pstate <- <primitive 146  self>.
	(pstate = 0) ifTrue: [pstate <- #READY.  ^ pstate].
	(pstate = 1) ifTrue: [pstate <- #SUSPENDED.  ^ pstate].
	(pstate = 2) ifTrue: [pstate <- #BLOCKED.  ^ pstate].
	(pstate = 3) ifTrue: [pstate <- #BLOCKED.  ^ pstate].
	(pstate >= 4) ifTrue: [pstate <- #TERMINATED.  ^ pstate]

|  terminate
	<primitive 142  self>.
	^ self state

|  termErr: msgName
	('Cannot ',msgName,' a terminated process.') print

|  unblock
	(self state == #TERMINATED)
	    ifTrue: [self termErr: 'unblock'.  ^ nil].
	<primitive 145  self 3>.
	^ self state

|  yield
	^ nil
]
