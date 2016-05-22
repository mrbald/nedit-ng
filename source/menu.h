/*******************************************************************************
*                                                                              *
* menu.h -- Nirvana Editor Menu Header File                                    *
*                                                                              *
* Copyright 2004 The NEdit Developers                                          *
*                                                                              *
* This is free software; you can redistribute it and/or modify it under the    *
* terms of the GNU General Public License as published by the Free Software    *
* Foundation; either version 2 of the License, or (at your option) any later   *
* version. In addition, you may distribute versions of this program linked to  *
* Motif or Open Motif. See README for details.                                 *
*                                                                              *
* This software is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for    *
* more details.                                                                *
*                                                                              *
* You should have received a copy of the GNU General Public License along with *
* software; if not, write to the Free Software Foundation, Inc., 59 Temple     *
* Place, Suite 330, Boston, MA  02111-1307 USA                                 *
*                                                                              *
* Nirvana Text Editor                                                          *
* July 31, 2001                                                                *
*                                                                              *
*******************************************************************************/

#ifndef MENU_H_
#define MENU_H_

#include <X11/Intrinsic.h>

#define PERMANENT_MENU_ITEM (XtPointer)1
#define TEMPORARY_MENU_ITEM (XtPointer)2

class Document;

Widget CreateBGMenu(Document *window);
Widget CreateMenuBar(Widget parent, Document *window);
Widget CreateTabContextMenu(Widget parent, Document *window);
XtActionsRec *GetMenuActions(int *nActions);
void AddBGMenuAction(Widget widget);
void AddTabContextMenuAction(Widget widget);
void AddToPrevOpenMenu(const char *filename);
void CheckCloseDim();
void HidePointerOnKeyedEvent(Widget w, XEvent *event);
void InstallMenuActions(XtAppContext context);
void InvalidateWindowMenus();
void ReadNEditDB();
void ShowHiddenTearOff(Widget menuPane);
void WriteNEditDB();


#endif
