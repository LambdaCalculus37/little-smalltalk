//=============================================================================//	Little Smalltalk, version 3//	Written by Tim Budd, Oregon State University, July 1988////	Symantec Think Class Library interface code //		�Julian Barkway, April 1994, all rights reserved. ////	CSelectPane.cp//	--------------//	Methods for a text editing pane which only allows selections.////=============================================================================#include "CSelectPane.h"#include "CPaneBorder.h"#include "CWindow.h"#include "CDocument.h"#include "Constants.h"#include <global.h>extern 	EventRecord  gLastMouseUp;extern 	CBureaucrat	*gGopher;	//={OVERRIDE}==================================================================// Initialise a shiny new select pane object.//=============================================================================void CSelectPane::ISelectPane (CView *encl, CBureaucrat *super, 								SizingOption hSizing, SizingOption vSizing,								short lineLength){	Rect		margin = {4, 4, 0, 0};		IEditText      (encl, super, 1, 1, 0, 0, hSizing, vSizing, 2000);	FitToEnclosure (TRUE, TRUE);	ResizeFrame    (&margin);	Specify   	   (kNotEditable, kSelectable, kStylable);}//={OVERRIDE}==================================================================// Null function because we want to maintain selection when user switches panes//=============================================================================void CSelectPane::Deactivate (void){}//={OVERRIDE}==================================================================// Select one full line with single click//=============================================================================void CSelectPane::DoClick (Point hitPt, short modifierKeys, long when){	TEHandle	teh;	LongPt		lp;	short		ln, startPos, endPos;		if (modifierKeys & optionKey)	// No selection when option key pressed		return;	teh = this->macTE;	QDToLongPt(hitPt, &lp);	ln = FindLine (GetCharOffset (&lp));	startPos = (*teh)->lineStarts [ln];	endPos   = (*teh)->lineStarts [ln + 1];	SetSelection (startPos, endPos, TRUE);}