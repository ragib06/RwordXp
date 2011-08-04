/*draws loading window*/
void loading()
{
	iSetcolor(.5,.5,.5);
	iFilledRectangle(0,0,width,height);							//load background

	iSetcolor(.5,.7,.9);
	iFilledRectangle((width-15)/2-200,(height-19)/2-50,400,250);		//load window background

	iSetcolor(0,0,0);
	iRectangle((width-15)/2-200,(height-19)/2-50,400,250);					//load window border

	iSetcolor(0,0,.7);
	iText((width-15)/2-65,(height-19)/2+130, "Rword 2008",GLUT_BITMAP_TIMES_ROMAN_24);

	iSetcolor(.3,.2,.1);
	iText((width-15)/2-110,(height-19)/2+80, "A Word Processor by Ragib Ahsan",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.8,.8,0);
	iText((width-15)/2-40,(height-19)/2+30, "Loading . . .",GLUT_BITMAP_HELVETICA_18);

	iSetcolor(.2,.3,1);
	iFilledRectangle((width-15)/2-105,(height-19)/2,ldbar,15);			//load bar

	iSetcolor(.1,.1,.1);
	iRectangle((width-15)/2-105,(height-19)/2,200,15);					//load box
}

/*Increases loadbar*/
void loadbar()
{
	ldbar += 5;
}

/*terminates the loading*/
void loadoff()
{
	load = 0;
}

/*maintains cursor blinking*/
void curblink()
{
	blink = -blink;
}

/*draws cursor*/
void cursor()
{
	if (blink==1)
	{
		iSetcolor(0, 0, 0);
		iText(x,y-1,"|",font);
	}
}


/*maintains cursor position after left mouse button click*/
void cursorOnClick()
{
	if (mouseY < (height-17-lineSpace + lineSpace/2))		//in the text field
	{
		if (((height-17-mouseY)%lineSpace) >= lineSpace/2)			//line down
			y = mouseY - lineSpace + (height-17-mouseY)%lineSpace;
		else if (((height-17-mouseY)%lineSpace) < lineSpace/2)		//line up
			y = mouseY + (height-17-mouseY)%lineSpace;
		else																				//on the line
			y = mouseY;
		i = (height-17-lineSpace-y)/lineSpace+s;

		if (i<=imax)									//in the text region
		{
			if ((unsigned)mouseX/charSpace <= strlen(str+i*charMax*sizeof(char)))
				x = mouseX - mouseX%(int)charSpace;
			else
				x = charSpace*strlen(str+i*charMax*sizeof(char));
			j = x/charSpace;
		}
		else											//out of the text region
		{
			if ((unsigned)mouseX/charSpace <= strlen(str+imax*charMax*sizeof(char)))
				x = mouseX - mouseX%(int)charSpace;
			else
				x = charSpace*strlen(str+imax*charMax*sizeof(char));
			y = height-17-lineSpace*(imax+1);
			j = x/charSpace;
		}

	}
	menuflag = 0;
	fontflag = 0;
	selflag = 0;
}


/*draws file menu*/
void fileMenu()
{
	iSetcolor(0,0,1);
	iFilledRectangle(0,height-15,40,15);			//selection indicator blue rectangle
		
	iSetcolor(1,1,1);
	iText(5,height-12,"File",GLUT_BITMAP_HELVETICA_12);							
	iSetcolor(.95,.95,.95);
	iFilledRectangle(3,height-16,130,-105);		//drop down rectangle	

	iSetcolor(.5,.1,.8);
	iRectangle(3,height-16,130,-105);				//drop down rectangle boundary

	iSetcolor(.5,.4,.3);
	iLine(3,height-122,134,height-122);				//horizontal shadow
	iLine(134,height-122,134,height-19);			//vertical shadow

	iSetcolor(0,0,0);
	iText(7,height-30,"Open           Ctrl+O",GLUT_BITMAP_HELVETICA_12);			

	iSetcolor(.9,.9,.98);
	iLine(5,height-37,127,height-37);					//topic seperator

	iSetcolor(0,0,0);
	iText(7,height-51,"Save            Ctrl+S",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(7,height-72,"Save as...  ",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.9,.9,.98);
	iLine(5,height-79,127,height-79);					//topic seperator

	iSetcolor(0,0,0);
	iText(7,height-93,"Print             Ctrl+P",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(7,height-114,"Exit              Alt+F4",GLUT_BITMAP_HELVETICA_12);
}

/*draws file open pop up*/
void fileopen()
{
	iSetcolor(.92,.93,.99);		//window background
	iFilledRectangle((width-15)/2-150,(height-19)/2,300,150);

	iSetcolor(.1,.1,.9);		//title bar
	iFilledRectangle((width-15)/2-150,(height-19)/2+130,300,20);

	iSetcolor(1,1,.5);			//title tag
	iText((width-15)/2-145,(height-19)/2+136, "Open file",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,.5,0);			//instruction
	iText((width-15)/2-140,(height-19)/2+106, "Directory: ..\\Programme files\\Rword\\saved_files\\",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.1,.1);		//input tag
	iText((width-15)/2-140,(height-19)/2+80, "Enter file name: (with extension)",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(1,1,1);			//text box
	iFilledRectangle((width-15)/2-140,(height-19)/2+55,280,20);

	iSetcolor(.5,.4,.3);		//text box boundary
	iRectangle((width-15)/2-140,(height-19)/2+55,280,20);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-150+248,(height-19)/2+16, "Open",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-214+248,(height-19)/2+16, "Cancel",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,.9);			//window boundary
	iRectangle((width-15)/2-150,(height-19)/2,300,150);
}

/*draws file save as pop up*/
void filesave()
{
	iSetcolor(.92,.93,.99);		//window background
	iFilledRectangle((width-15)/2-150,(height-19)/2,300,150);

	iSetcolor(.1,.1,.9);		//title bar
	iFilledRectangle((width-15)/2-150,(height-19)/2+130,300,20);

	iSetcolor(1,1,.5);			//title tag
	iText((width-15)/2-145,(height-19)/2+136, "Save as",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,.5,0);			//instruction
	iText((width-15)/2-140,(height-19)/2+106, "Directory: ..\\Programme files\\Rword\\saved_files\\",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.1,.1);		//input tag
	iText((width-15)/2-140,(height-19)/2+80, "Enter file name: (with extension) ",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(1,1,1);			//text box
	iFilledRectangle((width-15)/2-140,(height-19)/2+55,280,20);

	iSetcolor(.5,.4,.3);		//text box boundary
	iRectangle((width-15)/2-140,(height-19)/2+55,280,20);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-150+248,(height-19)/2+16, "Save",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-215+248,(height-19)/2+16, "Cancel",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,.9);			//window boundary
	iRectangle((width-15)/2-150,(height-19)/2,300,150);
}

void saveMessage()
{
	iSetcolor(.99,.99,.99);		//window background
	iFilledRectangle((width-15)/2-150,(height-19)/2,300,150);

	iSetcolor(.5,.5,.9);		//title bar
	iFilledRectangle((width-15)/2-150,(height-19)/2+130,300,20);

	iSetcolor(.2,0,.1);			//title tag
	iText((width-15)/2-145,(height-19)/2+136, "Save Message",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.1,.1);		//input tag
	iText((width-15)/2-140,(height-19)/2+80, "Do you want to save the changes?",GLUT_BITMAP_HELVETICA_18);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-150+254,(height-19)/2+16, "Yes",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-150+240,(height-19)/2+10,50,20);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-215+258,(height-19)/2+16, "No",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-210+240,(height-19)/2+10,50,20);

	iSetcolor(0,0,.9);			//window boundary
	iRectangle((width-15)/2-150,(height-19)/2,300,150);
}

/*draws edit menu*/
void editMenu()
{
	iSetcolor(0,0,1);
	iFilledRectangle(40,height-15,40,15);					//selection indicator blue rectangle
		
	iSetcolor(1,1,1);
	iText(45,height-12,"Edit", GLUT_BITMAP_HELVETICA_12);
	iSetcolor(.95,.95,.95);
	iFilledRectangle(43,height-16,130,-124);				//drop down rectangle

	iSetcolor(.5,.1,.8);
	iRectangle(43,height-16,130,-124);					//drop down rectangle boundary

	iSetcolor(.5,.4,.3);
	iLine(43,height-141,174,height-141);				//horizontal shadow
	iLine(174,height-141,174,height-19);				//vertical shadow

	if (!selection)
	{
		iSetcolor(.2,.5,.2);
		iText(47,height-30,"Select               F3",GLUT_BITMAP_HELVETICA_12);
	}
	else
	{
		iSetcolor(1,.5,.5);
		iText(47,height-30,"Select               F3",GLUT_BITMAP_HELVETICA_12);
	}

	iSetcolor(0,0,0);
	iText(47,height-49,"Select All     Ctrl+A",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.9,.9,.98);
	iLine(45,height-55,167,height-55);				//topic seperator

	iSetcolor(0,0,0);
	iText(47,height-68,"Copy           Ctrl+C",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(47,height-90,"Cut              Ctrl+X",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.9,.9,.98);
	iLine(45,height-97,147,height-97);				//topic seperator

	iSetcolor(0,0,0);
	iText(47,height-111,"Paste           Ctrl+V",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(47,height-132,"Clear All         ",GLUT_BITMAP_HELVETICA_12);
}

/*draws format menu*/
void formatMenu()
{
	double upArrX[]={205,205,210}; 
	double upArrY[]={height-30,height-22,height-26};

	iSetcolor(0,0,1);
	iFilledRectangle(80,height-15,55,15);					//selection indicator blue rectangle
		
	iSetcolor(1,1,1);
	iText(85,height-12,"Format",GLUT_BITMAP_HELVETICA_12);
	iSetcolor(.95,.95,.95);
	iFilledRectangle(83,height-16,130,-21);				//drop down rectangle

	iSetcolor(.5,.1,.8);
	iRectangle(83,height-16,130,-21);					//drop down rectangle boundary

	iSetcolor(.5,.4,.3);
	iLine(83,height-38,214,height-38);				//horizontal shadow
	iLine(214,height-38,214,height-19);				//vertical shadow

	iSetcolor(0,0,0);
	iText(87,height-30,"Font",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iFilledPolygon(upArrX,upArrY,3);

}

void fontlist()
{
	iSetcolor(.95,.95,.95);
	iFilledRectangle(215,height-16,130,-42);
	
	iSetcolor(.5,.1,.8);
	iRectangle(215,height-16,130,-42);

	iSetcolor(0,0,0);
	iText(218,height-31,"8 by 13",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,0);
	iText(218,height-52,"9 by 15",GLUT_BITMAP_HELVETICA_12);
}

/*draws help menu*/
void helpMenu()
{
	iSetcolor(0,0,1);
	iFilledRectangle(136,height-15,40,15);					//selection indicator blue rectangle
		
	iSetcolor(1,1,1);
	iText(141,height-12,"Help",GLUT_BITMAP_HELVETICA_12);
	iSetcolor(.95,.95,.95);
	iFilledRectangle(136,height-16,130,-42);				//drop down rectangle

	iSetcolor(.5,.1,.8);
	iRectangle(136,height-16,130,-42);					//drop down rectangle boundary

	iSetcolor(.5,.4,.3);
	iLine(136,height-59,267,height-59);				//horizontal shadow
	iLine(267,height-59,267,height-19);				//vertical shadow

	iSetcolor(0,0,0);
	iText(140,height-30,"Help                  F1",GLUT_BITMAP_HELVETICA_12);

	iText(140,height-51,"About Rword",GLUT_BITMAP_HELVETICA_12);

}

void aboutRword()
{
	char cName[50], uName[50];
	unsigned long size = 50;
	GetComputerName(cName, &size);
	GetUserName(uName, &size);

	iSetcolor(.92,.93,.99);		//window background
	iFilledRectangle((width-15)/2-150,(height-19)/2+50,300,160);

	iSetcolor(0,0,.5);			//text
	iText((width-15)/2-140,(height-19)/2+50+135, "Copyright 2008-2009: Rword",GLUT_BITMAP_HELVETICA_12);
	iSetcolor(0,0,0);
	iText((width-15)/2-140,(height-19)/2+50+120, "Ragib Ahsan",GLUT_BITMAP_HELVETICA_12);
	iText((width-15)/2-140,(height-19)/2+50+105, "Version 2.2.0",GLUT_BITMAP_HELVETICA_12);
	iText((width-15)/2-140,(height-19)/2+50+90, "Release Date: April 30, 2008",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(0,0,1);	
	iText((width-15)/2-140,(height-19)/2+50+65, "This product is Licensed to:",GLUT_BITMAP_HELVETICA_12);
	iSetcolor(1,0,0);
	iText((width-15)/2-140,(height-19)/2+50+45, cName,GLUT_BITMAP_HELVETICA_12);
	iText((width-15)/2-140,(height-19)/2+50+30, uName,GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.9,.9,.9);		//button 
	iFilledRectangle((width-15)/2-150+240,(height-19)/2+10+50,50,20);

	iSetcolor(0,0,0);			//button tag
	iText((width-15)/2-150+248,(height-19)/2+16+50, "  Ok",GLUT_BITMAP_HELVETICA_12);

	iSetcolor(.1,.5,.2);		//button boundary
	iRectangle((width-15)/2-150+240,(height-19)/2+10+50,50,20);

	iSetcolor(0,0,.9);			//window boundary
	iRectangle((width-15)/2-150,(height-19)/2+50,300,160);
}


/*draws the scrollbar*/
void scrollbar()
{
	double upArrX[]={width-7.5,width-3,width-12},    upArrY[]={height-16-3,height-16-12,height-16-12};
	double lowArrX[]={width-7.5,width-3,width-12},   lowArrY[]={5,14,14};
	iSetcolor(.9,.9,.98);
	iFilledRectangle(width-15,0,15,height-17);		//scroll background
	iSetcolor(0.8,0.8,1);
	iFilledRectangle(width-15,2,15,15);				//lower arrow rectangle
	iSetcolor(0.1,0.1,0.1);
	iRectangle(width-15,2,15,15);					//lower arrow rectangle border
	iSetcolor(0.8,0.8,1);
	iFilledRectangle(width-15,height-16-15,15,14);	//upper arrow rectangle
	iSetcolor(.1,.1,.1);
	iRectangle(width-15,height-16-15,15,14);		//upper arrow rectangle border
	iSetcolor(0,0,0);
	iFilledPolygon(upArrX,upArrY,3);			//upper arrow
	iSetcolor(0,0,0);
	iFilledPolygon(lowArrX,lowArrY,3);			//lower arrow
	if (hsflag)
	{
		iSetcolor(0.3,0.3,.7);
		iFilledRectangle(width-15,scrY,15,scrHeight);		//scrollbar
		iSetcolor(0,0,0);
		iRectangle(width-15,scrY,15,scrHeight);				//scrollbar border
	}
}

/*sets on the scrollbar*/
void scrollOn()
{
	hsflag = 1;
	if (i<s+lineMax)
	{
		scrY += scrHeight*0.02;
		//y = y - lineSpace;
	}
	else
	{
		s++;
	}
	scrHeight = scrHeight*0.98;
}

/*moves up the scrollbar*/
void scrollUp(int nLine)
{
	scrY += nLine*(height-17-15-scrHeight-scrY)/s;
	s -= nLine;
	y = height-17-(i+1-s)*lineSpace;
}

/*moves down the scrollbar*/
void scrollDown(int nLine)
{
	scrY -= nLine*(scrY-18)/(imax-s-lineMax+1);
	s += nLine;
	y = height-17-(i+1-s)*lineSpace;
}

