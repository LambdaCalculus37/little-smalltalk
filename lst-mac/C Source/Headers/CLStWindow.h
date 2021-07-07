//=============================================================================//	Little Smalltalk, version 3//	Written by Tim Budd, Oregon State University, July 1988////	Symantec Think Class Library interface code �Julian Barkway, April 1994 ////	CLStWindow.h//	------------//	Overridden methods from CWindow//=============================================================================#pragma once#include "Glue.h"#include "CDesktop.h"#include "CDirector.h"#include "CLStDoc.h"#include "CWindow.h"						/* Interface for its superclass		*/class CLStWindow : public CWindow {public:	WINDOW		*theLStWindow;	CLStDoc		*itsDocument;		void		Close			(void);		// Sub-class Close to block default											// action	void		Remove			(void);		// Really close the window	CLStDoc 	*GetDocument 	(void);		// Return pointer to associated document};