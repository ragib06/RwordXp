/*System functions*/
/*---------------------------------------------------------------------------------------------------*/

/*re allocates text field with num_size lines of text*/
void reAlloc(int num_size)
{
	char *str_temp;
	str_temp = (char*)calloc(imax,charMax*sizeof(char));
	str_temp = (char*)memcpy(str_temp,str, imax*charMax*sizeof(char));
	free(str);
	str = (char*)calloc(num_size, charMax*sizeof(char));
	str = (char*)memcpy(str,str_temp, imax*charMax*sizeof(char));
	free(str_temp);
}


/*File menu functions*/
/*---------------------------------------------------------------------------------------------------*/

/*saves the file with "filename"*/
void save()
{
	FILE *fp;
	int m;

	char tempfile[80];
	strcpy(tempfile,syspath);
	strcat(tempfile, ":\\Program Files\\Rword\\saved_files\\");
	strcat(tempfile, filename);							//create path

	if ((fp = fopen(tempfile, "w"))==NULL)
	{
		printf("Error\n");
		free(str);
		exit(1);
	}


	for (m=0;m<=imax;m++)
	{
		for(int n=0; (unsigned)n<=strlen(str+m*charMax*sizeof(char));n++)
		{
			if (str[m*charMax*sizeof(char)+n]=='\0' && n != charMax-1)
			{
				fputc('\n',fp);									//put '\n' in place of '\0'
			}
			else if (n != charMax-1)
			{
				fputc(str[m*charMax*sizeof(char)+n],fp);
			}
		}
	}
	fclose(fp);
}

/*save a copy as*/
void saveas()
{
	strcpy(filename,subTemp);			
	save();
	fsave=0;
	strcpy(filename,subTemp);				//create path
	free(subTemp);
	x = 0;
	y = height - 17- lineSpace;
	menuflag = 0;
}

/*opens a file*/
void open()
{
	char ch;
	FILE *fp;

	free(str);
	str =(char *) calloc(1, charMax*sizeof(char));

	i=0;
	imax=0;
	j=0;
	x=0;

	char tempfile[80];
	strcpy(filename,subTemp);
	strcpy(tempfile,syspath);
	strcat(tempfile, ":\\Program Files\\Rword\\saved_files\\");
	strcat(tempfile,filename);												//create path

	if ((fp = fopen(tempfile, "r"))==NULL)
	{
		printf("File not found !\n");
		fOpen = 0;
		return ;
	}

	imax = 0;

	for(int k=0;(ch = fgetc(fp)) != EOF ; k++)
	{
		if(ch=='\n')
		{
			enter();								//call enter in place of '\n'
		}
		else if (ch=='\t')							//put spaces in place of tab
		{
			for (int m=0; m<5; m++)
				character(' ');
		}
		else
		{
			character(ch);						//call character otherwise
		}
	}

	fclose(fp);
	fOpen=0;
	free(subTemp);
	if (imax>lineMax-1)						//put the scrollbar on the top
	{
		scrollUp(imax-lineMax+1);
	}
	backspace();
	x = 0;
	y = height - 17- lineSpace;
	i=0;
	j=0;										//set the cursor at the beginning
	menuflag = 0;
	
}

/*Edit menu functions*/
/*---------------------------------------------------------------------------------------------------*/

/*text selection operation*/
void selectText()
{
	int temp;
	selection = selection?0:1;							//flag on/off

	if (selection)
	{
		selSI = i;
		selSJ = j;											//get the starting position
	}
	else
	{
		selEI = i;											//end position
		selEJ = j;	
		
		if (selSI>selEI)							//make SI staring & EI ending
		{
			temp = selSI;
			selSI = selEI;
			selEI = temp;

			temp = selSJ;
			selSJ = selEJ;
			selEJ = temp;
		}
		else if (selEI==selSI && selSJ>selEJ)			//in the same line
		{
			temp = selSJ;
			selSJ = selEJ;
			selEJ = temp;
		}
	}

	selflag = (selection)?0:1;
}

/*copy operatioin over selected text*/
void copy()
{
	copylen = 0;
	if (selEI==selSI && selSJ==selEJ)				//void selection
		return;

	int m,n,i;

	for (i=0,m=selSI; m<=selEI; m++)
	{
		for (n=((m==selSI)?selSJ:0); ((unsigned)n<=((m==selEI)?selEJ:strlen(str+m*charMax*sizeof(char)))) && (n!=charMax-1); n++)
		{
			copylen++;
		}
	}
	copylen--;

	//allocate memory for copytemp
	copyTemp = (char *)calloc ((selEI-selSI)*charMax+selEJ-selSJ, sizeof(char));		

	if (!selection)
		{
			for (i=0,m=selSI; m<=selEI; m++)
			{
				for (n=((m==selSI)?selSJ:0); ((unsigned)n<=((m==selEI)?selEJ:strlen(str+m*charMax*sizeof(char)))) && (n!=charMax-1); n++)
				{
					copyTemp[i++] = str[m*charMax*sizeof(char)+n];			//copy in temp
				}
			}
			copyFlag = 1;
		}
}

/*cut operatioin over selected text*/
void cut ()
{
	if (copyFlag)
	{
		copy();							//copies the entire selected text
		i = selSI;
		j = selSJ;
		x = j*charSpace;
		y = height - 17 - (i+1)*lineSpace;
		for (int k = 0; k<copylen+1; k++)
		{
			del();						//deletes the area
		}
		selflag = 0;
	}
}

void seldel()
{
	int len = 0;
	i = selSI;
	j = selSJ;
	x = j*charSpace;
	y = height - 17 - (i+1)*lineSpace;

	for (int m=selSI; m<=selEI; m++)
	{
		for (int n=((m==selSI)?selSJ:0); ((unsigned)n<=((m==selEI)?selEJ:strlen(str+m*charMax*sizeof(char)))) && (n!=charMax-1); n++)
		{
			len++;
		}
	}
	len--;

	for (int k = 0; k<len; k++)
	{
		del();						//deletes the area
	}
	selflag = 0;
}

/*paste operatioin over selected text*/
void paste()
{
	if (copyFlag)
	{
		int m;
		for (m = 0; m<=copylen; m++)
		{
			if (copyTemp[m]=='\0')
			{
				enter();							//hit enter in place of '\0' occurance
			}
			else
			{
				if (j==charMax-1)
					enter();						//hit enter in the end of line
				character((unsigned char) copyTemp[m]);				//put the characters
			}
		}
	}
	backspace();
	selflag = 0;
	
}

void selectAll()
{
	selSI = selSJ = 0;
	selEI = imax;
	selEJ = strlen(str+imax*charMax*sizeof(char));
	selflag = 1;
	menuflag = 0;
}
/*clears the text field*/
void clearAll()
{
	free(str);								//clear the main string
	str =(char *) calloc(1, charMax*sizeof(char));				//allocates initial memory
	i = 0;
	imax = 0;
	s = 0;
	j = 0;
	x = 0;
	y = height - 17 - lineSpace;									//set the index & cursor on top
	if (hsflag)														//turn off scrollbar if exists
	{
		scrY = 18;
		scrHeight = height-19-30;
		hsflag = 0;
	}

	menuflag = 0;
}

/*Mouse functions*/
/*---------------------------------------------------------------------------------------------------*/

/*operations left mouse button actions*/
void mouseLeft ()
{
	if ((mouseX>=0 &&mouseX <40) && (mouseY>=height-15 && mouseY<=height))
	{
		menuflag = 1;				//drop file menu
		fontflag = 0;
	}
	else if ((mouseX>=41 &&mouseX <80) && (mouseY>=height-15 && mouseY<=height))
	{
		menuflag = 2;				//drop edit menu
		fontflag = 0;
	}
	else if ((mouseX>=81 &&mouseX <135) && (mouseY>=height-15 && mouseY<=height))
	{
		menuflag = 3;				//drop format menu
		fontflag = 0;
	}
	else if ((mouseX>=136 &&mouseX <176) && (mouseY>=height-15 && mouseY<=height))
	{
		menuflag = 4;				//drop help menu
		fontflag = 0;
	}
	else if ((mouseX>=(width-15)/2-150+240 && mouseX <(width-15)/2-150+240+50) && (mouseY>=(height-19)/2+10 && mouseY<=(height-19)/2+10+20))
	{
		if (fOpen)
			open();					//open a file
		else if (fsave)
			saveas();				//save a file
		else if (saveM)				//save while exit
		{
			save();
			free(str);
			exit(0);
		}
	}
	else if ((mouseX>=(width-15)/2-210+240 && mouseX <(width-15)/2-150+240+50) && (mouseY>=(height-19)/2+10 && mouseY<=(height-19)/2+10+20))
	{
		if (fOpen)			//cancels file open
		{
			fOpen = 0;
			menuflag = 0;
			x = j*charSpace;
			y = height - 17 - (i+1-s)*lineSpace;
		}
		else if (fsave)			//cancels save as
		{
			fsave = 0;
			menuflag = 0;
			x = j*charSpace;
			y = height - 17 - (i+1-s)*lineSpace;		
		}
		else if (saveM)			//don't save while exit
		{
			free(str);
			exit(0);
		}
	}
	else if ((mouseX>=(width-15)/2+90 && mouseX<=(width-15)/2+90+50) && (mouseY>=(height-19)/2+60 && mouseY<=(height-19)/2+60+20))
	{
		if (aboutR)					//close "aboutR" window
		{
			aboutR = 0;
		}
	}
	else if ((mouseX>=215 && mouseX<=345) && (mouseY>=height-37 && mouseY<=height-16))
	{
		if (fontflag)
		{
			fontchange(1);			//change font to 8 by 13
			menuflag = 0;
		}
		else
			cursorOnClick();
	}
	else if ((mouseX>=215 && mouseX<=345) && (mouseY>=height-58 && mouseY<=height-37))
	{
		if (fontflag)
		{
			fontchange(2);			//change font to 9 by 15
			menuflag = 0;
		}
		else
			cursorOnClick();			//otherwise put the cursor on position
	}
	else if (menuflag == 1)			//file menu-drop on
	{
		if ((mouseX>=0 && mouseX<=130) && (mouseY>=height-36 && mouseY<=height-16))
		{
			//file open
			fOpen =1;
			r = 0;
			subTemp = (char *)calloc(60,sizeof(char));
			x = (width-15)/2-135;
			y = (height-19)/2+61;
			menuflag = 0;
		}	
		else if ((mouseX>=0 && mouseX<=130) && (mouseY>=height-56 && mouseY<=height-36))
		{
			save();		//save file
			menuflag = 0;
		}
		else if ((mouseX>=0 && mouseX<=130) && (mouseY>=height-76 && mouseY<=height-56))
		{
			//save as
			fsave =1;
			r = 0;
			subTemp = (char *)calloc(34,sizeof(char));
			x = (width-15)/2-135;
			y = (height-19)/2+61;
			menuflag = 0;
		}
		else if ((mouseX>=0 && mouseX<=130) && (mouseY>=height-96 && mouseY<=height-76))
		{
			save();
			char tempfile[80];
			strcpy(tempfile, syspath);
			strcat(tempfile, ":\\Program Files\\Rword\\saved_files\\");
			strcat(tempfile, filename);
			ShellExecute(NULL, "print", tempfile, NULL, NULL, NULL);		//print document
			menuflag = 0;
		}
		else if ((mouseX>=0 && mouseX<=130) && (mouseY>=height-116 && mouseY<=height-96))
		{
			FILE *fp;
			char tempfile[80];
			strcpy(tempfile, syspath);
			strcat(tempfile, ":\\Program Files\\Rword\\settings.dat");
			fp = fopen(tempfile, "wb");
			fwrite(&flebel, sizeof(int), 1, fp);			//record the font lebel
			fclose(fp);

			menuflag = 0;
			saveM = 1;										//turn on the save message

		}
		else
		{
			cursorOnClick();		//put the cursor in position
		}
	}
	else if (menuflag == 2)		//edit menu drop on
	{
		if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-35 && mouseY<=height-16))
		{
			selectText();			//manage text selection
			menuflag = 0;
		}	
		else if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-54 && mouseY<=height-35))
		{
			//select all
			selectAll();
		}
		else if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-73 && mouseY<=height-54))
		{
			copy();						//copy selected text
			menuflag = 0;
		}
		else if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-92 && mouseY<=height-73))
		{
			cut();						//cut selected text
			menuflag = 0;
		}
		else if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-111 && mouseY<=height-92))
		{
			paste();					//paste selected text
			menuflag = 0;
		}
		else if ((mouseX>=40 && mouseX<=170) && (mouseY>=height-132 && mouseY<=height-111))
		{
			clearAll();							//clears the text field
		}
		else
		{
			cursorOnClick();			//put the cursor in position
		}
	}
	else if (menuflag == 3)			//format menu drop on
	{
		if ((mouseX>=80 && mouseX<=210) && (mouseY>=height-36 && mouseY<=height-16))
		{
			fontflag = 1;			//show font list
		}
		else
		{
			cursorOnClick();		//put the cursor in position
		}
	}
	else if (menuflag == 4)		//help menu drop on
	{
		if ((mouseX>=136 && mouseX<=266) && (mouseY>=height-36 && mouseY<=height-16))
		{
			//show help file
			char tempfile[80];
			strcpy(tempfile, syspath);
			strcat(tempfile, ":\\Program Files\\Rword\\Rhelp.chm");
			ShellExecute(NULL,"open", tempfile, NULL,NULL, SW_SHOWNA);
			menuflag =0;
		}
		else if ((mouseX>=136 && mouseX<=266) && (mouseY>=height-56 && mouseY<=height-36))
		{
			aboutR = 1;						//show aboutR
			menuflag =0;
		}
		else
		{
			cursorOnClick();				//otherwise put the cursor in position
		}
	}
	else if(mouseX>width-15 && mouseX<width && mouseY>height-16-15 && mouseY<height-16)
	{
		//scroll up button
		if (s!=0)
		{
			scrollUp(1);		//move up scroller 1 line
		}
	}
	else if(mouseX>width-15 && mouseX<width && mouseY>0 && mouseY<16)
	{
		//scroll down button
		if ((s+lineMax-1)< imax)
		{
			scrollDown(1);						//move down scroller 1 line
		}
	}
	else
	{
		cursorOnClick();						//otherwise put the cursor in position
	}
}


/*Format menu functions*/
/*---------------------------------------------------------------------------------------------------*/

/*manages font change*/
void fontchange(int lebel)
{

	char *strTemp;
	int cmtemp, len = imax*charMax+strlen(str+imax*charMax*sizeof(char));

	cmtemp = charMax;							//record current charMax

	strTemp = (char*)calloc((imax+1)*charMax,sizeof(char));		//allocate memory for temporary string
	
	for (int k=0,p=0; k<=len; k++,p++)
	{
		strTemp[p] = str[p];										//copy the entire string with '\0' s
	}

	hsflag = 0;
	i=0;
	j=0;
	imax=0;
	x=0;
	y=height - 17 - lineSpace;

	
	scrY=18;
	scrHeight=height-19-30;
	s=0;

	for (k=0; k<len; k++)
	{
		del();
	}
	
	free(str);
	

	switch(lebel)									//change the font parametre according to lebel
	{
		case 1: 
					font = GLUT_BITMAP_8_BY_13;
					charSpace = 8;
					lineSpace = 15;
					charMax = (width-15)/charSpace;
					lineMax=(height-17)/lineSpace;
					break;
		case 2:
					font = GLUT_BITMAP_9_BY_15;
					charSpace = 9;
					lineSpace = 18;
					charMax = (width-15)/charSpace;
					lineMax=(height-17)/lineSpace;
					break;
	}
	str =(char *) calloc(1, charMax*sizeof(char));

	for (k=0; k<=len; k++)
	{
		if (k == 0 || (k+1)%cmtemp)
		{
			if (*(strTemp+k) != '\0')
				character(*(strTemp+k));						//put the characters
						
			else if (k!= len)
			{
				enter();												//hit enter if '\0'
				for (; (k+1)%cmtemp; k++)				//skip the trailing '\0's
					;
				k--;
			}
		}
	}

	//free(strTemp);
	i=0;
	j=0;
	x=0;
	y = height - 17 - (i+1-s)*lineSpace;					//set the cursor 
	fontflag = 0;
	flebel = lebel;
}