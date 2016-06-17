
#ifndef DOCUMENT_WIDGET_H_
#define DOCUMENT_WIDGET_H_

#include <QDialog>
#include <QPointer>
#include <QWidget>

#include "Bookmark.h"
#include "LockReasons.h"
#include "UserBGMenuCache.h"
#include "userCmds.h"
#include "util/FileFormats.h"

#include <Xm/Xm.h>

class UndoInfo;
class TextBuffer;
class Document;

class DocumentWidget : public QWidget {
	Q_OBJECT
public:
	DocumentWidget(const QString &name, QWidget *parent = 0, Qt::WindowFlags f = 0);
	~DocumentWidget();

private:
	// TODO(eteran): are these dialog's per window or per text document?
	QPointer<QDialog> dialogColors_;
	QPointer<QDialog> dialogFonts_; /* nullptr, unless font dialog is up */	

private:
	Atom fileClosedAtom_;              // Atom used to tell nc that the file is closed
	Bookmark markTable_[MAX_MARKS];    // marked locations in window
	Document ** writableWindows_;      // temporary list of writable windows, used during multi-file replacements
	FileFormats fileFormat_;           // whether to save the file straight (Unix format), or convert it to MS DOS style with \r\n line breaks
	LockReasons lockReasons_;          // all ways a file can be locked
	QString backlightCharTypes_;       // what backlighting to use
	QString boldFontName_;
	QString boldItalicFontName_;
	QString filename_;                 // name component of file being edited
	QString fontName_;                 // names of the text fonts in use
	QString italicFontName_;
	QString path_;                     // path component of file being edited
	TextBuffer *buffer_;               // holds the text being edited
	UserBGMenuCache userBGMenuCache_;  // shell & macro menu are shared over all "tabbed" documents, while each document has its own background menu.
	UserMenuCache *userMenuCache_;     // cache user menus:
	XFontStruct *boldFontStruct_;
	XFontStruct *boldItalicFontStruct_;
	XFontStruct *italicFontStruct_;    // fontStructs for highlighting fonts
	XmFontList fontList_;              // fontList for the primary font
	XtIntervalId flashTimeoutID_;      // timer procedure id for getting rid of highlighted matching paren.  Non-zero val. means highlight is drawn
	XtIntervalId markTimeoutID_;       // backup timer for mark event handler
	bool autoSave_;                    // is autosave turned on?
	bool backlightChars_;              // is char backlighting turned on?
	bool fileChanged_;                 // has window been modified?
	bool fileMissing_;                 // is the window's file gone?
	bool filenameSet_;                 // is the window still "Untitled"?
	bool highlightSyntax_;             // is syntax highlighting turned on?
	bool iSearchLastLiteralCase_;      // idem, for literal mode
	bool iSearchLastRegexCase_;        // idem, for regex mode in incremental search bar
	bool ignoreModify_;                // ignore modifications to text area
	bool modeMessageDisplayed_;        // special stats line banner for learn and shell command executing modes
	bool multiFileBusy_;               // suppresses multiple beeps/dialogs during multi-file replacements
	bool multiFileReplSelected_;       // selected during last multi-window replacement operation (history)
	bool overstrike_;                  // is overstrike mode turned on ?
	bool replaceFailed_;               // flags replacements failures during multi-file replacements
	bool saveOldVersion_;              // keep old version in filename.bck
	bool wasSelected_;                 // last selection state (for dim/undim of selection related menu items
	bool windowMenuValid_;             // is window menu up to date?
	char *modeMessage_;                // stats line banner content for learn and shell command executing modes
	char indentStyle_;                 // whether/how to auto indent
	char matchSyntaxBased_;            // Use syntax info to show matching
	char showMatchingStyle_;           // How to show matching parens: NO_FLASH, FLASH_DELIMIT, or FLASH_RANGE
	char wrapMode_;                    // line wrap style: NO_WRAP, NEWLINE_WRAP or CONTINUOUS_WRAP
	dev_t device_;                     // device where the file resides
	gid_t fileGid_;                    // last recorded group id of the file
	ino_t inode_;                      // file's inode
	int autoSaveCharCount_;            // count of single characters typed since last backup file generated
	int autoSaveOpCount_;              // count of editing operations ""
	int fHistIndex_;                   // history placeholders for
	int flashPos_;                     // position saved for erasing matching paren highlight (if one is drawn)
	int iSearchHistIndex_;             //   find and replace dialogs
	int iSearchLastBeginPos_;          // beg. pos. last match of current i.s.
	int iSearchStartPos_;              // start pos. of current incr. search
	int languageMode_;                 // identifies language mode currently selected in the window
	int nMarks_;                       // number of active bookmarks
	int nPanes_;                       // number of additional text editing areas, created by splitWindow
	int nWritableWindows_;             // number of elements in the list
	int rHistIndex_;
	int undoMemUsed_;                  // amount of memory (in bytes) dedicated to the undo list
	std::list<UndoInfo *> redo_;       // info for redoing last undone op
	std::list<UndoInfo *> undo_;       // info for undoing last operation
	time_t lastModTime_;               // time of last modification to file
	uid_t fileUid_;                    // last recorded user id of the file
	unsigned fileMode_;                // permissions of file being edited
	void *highlightData_;              // info for syntax highlighting
	void *macroCmdData_;               // same for macro commands
	void *shellCmdData_;               // when a shell command is executing, info. about it, otherwise, nullptr
	void *smartIndentData_;            // compiled macros for smart indent
};

#endif