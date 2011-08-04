# include "iGraphics.h"
# include <string.h>
# include <stdlib.h>
# include "prototype.h"
# include "draw.h"
# include "menu.h"
# include "keyboard.h"

void iDraw()
{
	int m,n;
	iClear();
	iSetcolor(1,1,1);
	iFilledRectangle(1,1,width-19,height-18);		//draw text box
	iSetcolor(0,0,0);
	iRectangle(1,1,width-19,height-19);				//draw text boundary

	if (selflag)
	{
		for (int l=selSI; l<=selEI; l++)
		{
			int sx = (l==selSI)?( (selSJ==0)?3:selSJ*charSpace) : 3;
			int sy = height - 17 - (l+1-s)*lineSpace - 5;
			int w;
			if (l==selSI)
				w = (selSI == selEI) ? selEJ-selSJ : strlen(str+l*charMax*sizeof(char))-selSJ;
			else if (l==selEI)
				w = selEJ;
			else
				w = (strlen(str+l*charMax*sizeof(char))==0)?1:strlen(str+l*charMax*sizeof(char));

			iSetcolor(.8,.8,.9);
			iFilledRectangle(sx,sy,w*charSpace,lineSpace);
		}
	}

	iSetcolor(0,0,0);
	for (m=height-17-lineSpace, n=s; n<=imax; m-=lineSpace, n++)
	{
		iText(3, m, str+n*charMax*sizeof(char),font);		//print text
	}

	if (fOpen)
	{
		fileopen();
		iSetcolor(0,0,0);
		iText((width-15)/2-135,(height-19)/2+62,subTemp+r);		//print file open text
	}
	else if (fsave)
	{
		filesave();
		iSetcolor(0,0,0);
		iText((width-15)/2-135,(height-19)/2+62,subTemp+r);	//print file save as text
	}
	else if (aboutR)
	{
		aboutRword();
	}

	cursor();							//draw cursor		

	iSetcolor(.9,.9,.9);
	iFilledRectangle(3,height-17,width-19,17);

	iSetcolor(0,0,0);
	iLine(2,height-18,width-19,height-18);

	iSetcolor(0,0,0);
	iText(5,height-12,"File",GLUT_BITMAP_HELVETICA_12);			

	iSetcolor(0,0,0);
	iText(45,height-12,"Edit",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(85,height-12,"Format",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(141,height-12,"Help",GLUT_BITMAP_HELVETICA_12);		//draw menus
		
	if (menuflag == 1)
	{
		fileMenu();					//draw file drop down menu
	}
	else if (menuflag == 2)
	{
		editMenu();					//draw edit drop down menu
	}
	else if (menuflag == 3)
	{
		formatMenu();				//draw format drop down menu
	}
	else if (menuflag == 4)
	{
		helpMenu();					//draw help drop down menu
	}


	if (fontflag)
	{
		fontlist();						//draw font list
	}
	else if (saveM)
	{
		saveMessage();			//message box while exitting
	}

	scrollbar();                  // draw scrollbar



	if (load)
		loading();				//load window
}

void iMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	mouseX = mx;
	mouseY = my;
	upArrow=0;
	downArrow=0;		//set arrow flags off

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	
		mouseLeft();					//mouse left button function
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		menuflag = 0;
		fOpen = 0;
		fsave = 0;			//sets off the flags
	}	
}

void iKeyboard(unsigned char key)
{
	upArrow = 0;
	downArrow=0;		//set arrow flags off

	//retrieve charactre index in terms of cursor position
	j = x/ charSpace;
	i = ((height-15-lineSpace - y)/lineSpace) + s;		


	if (glutGetModifiers() == GLUT_ACTIVE_CTRL)				//ALT key operations
	{
		if (key == 1)							//select all
		{
			selectAll();
		}
		else if (key == 3 )				//copy
		{
			copy();
		}
		else if (key==15)			//file open	
		{
			fOpen =1;
			subTemp = (char *)calloc(60,sizeof(char));
			x = (width-15)/2-135;
			y = (height-19)/2+61;
			menuflag = 0;
		}
		else if (key==16)			//file save as
		{
			save();
			char tempfile[80];
			strcpy(tempfile, syspath);
			strcat(tempfile, ":\\Program Files\\Rword\\saved_files\\");
			strcat(tempfile, filename);
			ShellExecute(NULL, "print", tempfile, NULL, NULL, NULL);		//print document
			menuflag = 0;
		}
		else if (key==19)			//file save
		{
			save();
			menuflag = 0;
		}
		else if (copyFlag &&  key==22)		//paste
		{
			paste();
		}
		else if (key == 24 )			//cut
		{
			cut();
		}
	}
	else if(key >31 && key <127)		//character input
	{
		
		if (fOpen || fsave)
		{
			subCharacter(key);				//for popups
		}
		else
		{
			if (selflag)
				seldel();
			character(key);							// main character input
		}
	}
	else if (key == '\b')				//backspace
	{
		
		if (fOpen || fsave)				//popup
		{
			if (strlen(subTemp))
			{
				subTemp[strlen(subTemp)-1] = '\0';
				if (strlen(subTemp)>33)
					r--;
				else
					x -= 8;
			}
		}
		else
		{
			if (selflag)
				seldel();
			else
				backspace();				//main
		}
	}	
	else if (key == 127)			//del
	{
		if (selflag)
			seldel();
		else
			del();
	}
	else if (key == '\r')			//enter operations
	{	
		if (fOpen)					
		{
			if (selflag)
				seldel();

			open();
		}
		else if (fsave)
		{
			saveas();				//popups
		}
		else
		{
			if (selflag)
				seldel();
			else
				enter();				//main
		}
	}
	else if (key == '\t')			//incomplete
	{
		selflag = 0;
		tab();
	}
}

void iSpecialKeyboard(unsigned char key)
{
	selflag = 0;
	//retrieve charactre index in terms of cursor position
	j = x/ charSpace;
	i = ((height-15-lineSpace - y)/lineSpace) + s;

	if (glutGetModifiers() == GLUT_ACTIVE_ALT && key == GLUT_KEY_F4 )
	{
		FILE *fp;
		char tempfile[80];
		strcpy(tempfile, syspath);
		strcat(tempfile, ":\\Program Files\\Rword\\settings.dat");
		fp = fopen(tempfile, "wb");
		fwrite(&flebel, sizeof(int), 1, fp);
		fclose(fp);

		free(str);
		exit(0);			//exit action
	}
	else if(key == GLUT_KEY_LEFT)			//aroow keys
	{
		upArrow=0;
		downArrow=0;
		leftarrow();
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		upArrow=0;
		downArrow=0;
		rightarrow();
	}

	else if(key == GLUT_KEY_UP)
	{
		uparrow();
	}

	else if (key == GLUT_KEY_DOWN)
	{
		downarrow();
	}
	else if (key == GLUT_KEY_F1)			//help option
	{
		char tempfile[80];
		strcpy(tempfile, syspath);
		strcat(tempfile, ":\\Program Files\\Rword\\Rhelp.chm");
		ShellExecute(NULL,"open", tempfile, NULL,NULL, SW_SHOW);
		menuflag =0;
	}
	else if (key == GLUT_KEY_F3)			//selection shortcut
	{
		selectText();
	}
	
	else if (key == GLUT_KEY_PAGE_UP)		//page keys
	{
		pageUp();
	}

	else if (key == GLUT_KEY_PAGE_DOWN)
	{
		pageDown();
	}

	else if (key == GLUT_KEY_HOME)
	{
			j = 0;
			x = 0;
	}

	else if (key == GLUT_KEY_END)
	{
		j = strlen(str+i*charMax*sizeof(char));
		x = j*charSpace;
	}

	else if (key == GLUT_KEY_INSERT)
	{
		insert = (insert)?0:1;
	}
}

int main()
{
	FILE *fp;
	int getfont;
	char tempfile[80];

	GetSystemDirectory(syspath, 50);
	syspath[1] = '\0';
	str =(char *) calloc(1, charMax*sizeof(char));

	strcpy(tempfile, syspath);
	strcat(tempfile, ":\\Program Files\\Rword\\settings.dat");

	fp = fopen(tempfile, "rb");
	fread(&getfont, sizeof(int), 1, fp);
	fontchange(getfont);
	fclose(fp);

	iSettimer(500, curblink);
	iSettimer(50, loadbar);
	iSettimer(2000, loadoff);

	iInitialize(width, height, "Rword2008");

	return 0;
}	