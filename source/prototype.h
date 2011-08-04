int width=800, height=600;					//window parameter
int lineSpace=18;								//character spacing & linespacing
int lineMax=(height-15)/lineSpace;		// maximum number of lines in height
int i=0,imax=0,j=0, k, s=0, r=0;				//indexes
int selection = 0, menuflag = 0,hsflag=0,blink=1,copyFlag=0,load=1, saveM=0;	//flags
int fOpen=0,fsave=0,insert=0, upArrow=0, downArrow=0,fontflag=0,aboutR=0;	//flags														//flags
int mouseX,mouseY;		//holding mouse pointer position		
int selSI=0,selSJ=0,selEI=0,selEJ=0 , copylen=0, selflag = 0;					//selection & copy
char *str, *copyTemp, *subTemp, filename[34] = "Rword.txt";		//strings 
double scrY=18, scrHeight=height-19-30;										// scrollbar postion & height
double charSpace = 9;										//character spacing & max character
int charMax = (int)(width/charSpace)-1;
int x=0, y =  height-17-lineSpace;											//cursor position coordinate
void *font = GLUT_BITMAP_9_BY_15;								//default font
int ldbar=45, flebel=2;														//loading bar & font lebel

/*for managing loading window*/
void loading();								//draws loading window 
void laodbar();								//increases loadbar
void loadoff();								//stops the loading with iSettimer

/*editing*/
void selectText();							//selects text
void selectAll();							//select all text
void cut();										//cut selected text
void copy();								//copies selected text
void paste();								//pastes selected text
void clearAll();							//clears the text field
void seldel();								//deletes selected portion

/*formatting*/
void fontchange(int);					//manages font change

/*file operations*/
void save();								//saves file with current filename
void saveas();								//saves file with given filename
void saveMessage();						//asks about save whil exitting
void open();								//opens file 

/*memory allocation*/
void reAlloc(int);							//re-allocates memory keeping the elements

/*managing cursor*/
void cursor();								//draws the cursor
void curblink();							//manages blinking by iSettimer
void cursorOnClick();					//manages position of cursor on mouseclick

/*drawing menu items*/
void fileMenu();							//draws the filemenu
void fileopen();							//draws the fileopen popup
void filesave();							//draws the file save as popup
void editMenu();						//draws the edit menu
void formatMenu();						//draws the format menu
void fontlist();							//draws font list
void helpMenu();						//draws the help menu
void aboutRword();					//draws the about Rword window

/*drawing & managing scrollbar*/
void scrollbar();							//draws the scrollbar
void scrollOn();							//turns on the scrolling
void scrollUp(int);							//moves scrollbar up by number of line as parameter
void scrollDown(int);					//moves scrollbar down by number of line as parameter

/*managing left click on mouse*/
void mouseLeft();							//manages all mouse click operations (left)

/*key text editing*/
void character(unsigned char);			//puts input character in the string
void subCharacter(unsigned char);	//manages character in the popups
void backspace();							//manages backspace operations
void backCopy();							//subfunction of backspace 
void del();										//manages deleting
void enter();									//manages enter key functions
void tab();										//manages tab key functions

/*managing arrow keys*/
void leftarrow();							//manages left arrow key functions
void rightarrow();							//manages right arrow key functions
void uparrow();							//manages up arrow key functions
void downarrow();						//manages down arrow key functions

/*managing page keys*/
void pageUp();							//manages page up key functions
void pageDown();					//manages page down key functions
