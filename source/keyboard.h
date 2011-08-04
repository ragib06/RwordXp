/*manages characters from keybord for the pop ups*/
void subCharacter(unsigned char ikey)
{
	if (fsave || fOpen)
	{
		subTemp[strlen(subTemp)] = ikey;
		subTemp[strlen(subTemp)+1] = '\0';
		if (strlen(subTemp)>33)
			r++;
		else
			x += 8;
	}
}

/*manages characters from keybord in the main string*/
void character(unsigned char ikey)
{
	int l;
	if (j == charMax-1)		//cursor in the end of a full line
	{
		for (int k = j; k != 0 && str[i*charMax*sizeof(char) + (k-1)] != ' '; k--)
		;
		j = (k)?k:j;
		enter();
		j = strlen(str+i*charMax*sizeof(char));
		x = j*charSpace;
	}
	if (!insert)		//insert mode is off
	{
		if (str[i*charMax*sizeof(char)+j] == '\0')		//no more character followed in the line
			{
				str[i*charMax*sizeof(char) + (j++)] = ikey;
				str[i*charMax*sizeof(char)+j] = '\0';
				x = x+charSpace;
			}
		else						//more characters followed by
		{
			if ((k=strlen(str+i*charMax*sizeof(char)))!= charMax-1)		//the line is not full
			{
				for (;  k>=j; k--)		
				{
					//move them right
					str[i*charMax*sizeof(char)+k+1] = str[i*charMax*sizeof(char)+k];	
				}
				str[i*charMax*sizeof(char)+(j++)] = ikey;		//put the char
				x = x+charSpace;
			}
			else				//the line is full
			{
				for (l=i+1; strlen(str+l*charMax*sizeof(char)) ==(unsigned)charMax-1; l++ )				//find an unfilled line
				;
				if (l>imax)			//no unfull line next
				{
					imax++;
					reAlloc(imax+1);
					if (imax>lineMax-1)			//crosses the screen limit
					{
						scrollOn();						//turn on scrollbar
					}
				}
				//move right by 1 char
				for ( k = strlen(str+l*charMax*sizeof(char)); k>=0; k--)			
				{
					str[l*charMax*sizeof(char)+k+1] = str[l*charMax*sizeof(char)+k];
				}
				l--;
				for (; l>i; l-- )
				{
					str[(l+1)*charMax*sizeof(char)] = str[l*charMax*sizeof(char)+charMax-2];
					//move right by 1 char
					for ( k = strlen(str+l*charMax*sizeof(char))-2; k>=0; k--)		
					{
						str[l*charMax*sizeof(char)+k+1] = str[l*charMax*sizeof(char)+k];
					}
				}
				str[(l+1)*charMax*sizeof(char)] = str[l*charMax*sizeof(char)+charMax-2];
				for (l = strlen(str+i*charMax*sizeof(char))-2; l>= j; l--)
				{
					// copy contents
					str[i*charMax*sizeof(char)+l+1] = str[i*charMax*sizeof(char)+l];	
				}
				str[i*charMax*sizeof(char)+(j++)] = ikey;							//put the char
				x = x+charSpace;																//shift cursor
			}
		}
	}
	else			//insert mode is on
	{
		str[i*charMax*sizeof(char) + (j++)] = ikey;
		x = x+charSpace;
	}
}


/*Left Arrow key function*/
void leftarrow()
{
	if (x == 0)									//if in the first of the line
		{
			if (i != 0)					//if not on the top
			{
				if (i==s)
				{
					scrollUp(1);
				}
				x = charSpace*strlen(str+(i-1)*charMax*sizeof(char));
				y = y + lineSpace;								//place cursor
				i--;
				j = x/charSpace;								//fix index
			}
			else
				printf("\a");
		}
		else														//if not in the first
		{
			x = x - charSpace;									//shift cursor
			j--;
		}
}


/*Right Arrow key function*/
void rightarrow()
{
	j = x/ charSpace;
	if (str[i*charMax*sizeof(char)+j] != '\0')					//if end of line
	{
		x = x + charSpace;
		y = y;
		j++;
	}
	else																		//if not the end of line
	{
		if (i<imax)
		{
			if (i == s+lineMax-1)
			{
				scrollDown(1);
			}
			i++;
			j = 0;
			x = 0;
			y = height-17-lineSpace - (i-s)*lineSpace;
		}
	}
}


/*Up Arrow key function*/
void uparrow()
{
	if (i != 0)									//not the top
	{
		if (i==s)
		{
			scrollUp(1);
		}
		i--;
		y = y + lineSpace;

		if (!upArrow)
		{
			upArrow = x;												//fix the x-coordinate
		}

		if ((unsigned)upArrow >= strlen(str+i*charMax*sizeof(char))*charSpace)
		{
			x = strlen(str+i*charMax*sizeof(char))*charSpace;
			j = x/charSpace;
		}
		else
		{
			x = upArrow;
		}
	}
}


/*Down Arrow key function*/
void downarrow()
{
	if(!downArrow)
	{
		downArrow = x;
	}
	if (i<imax)										//there is more lines
	{
		if (i==s+lineMax-1)
		{
			scrollDown(1);
		}
		i++;
		y = height-15-lineSpace - (i-s)*lineSpace;
		if ((unsigned)downArrow > strlen(str+i*charMax*sizeof(char))*charSpace)
		{
			x = strlen(str+i*charMax*sizeof(char))*charSpace;
		}
		else
		{
			x = downArrow;
		}
	}
}

/*controls page up operation*/
void pageUp()
{
	if (s>lineMax-1)			//one screenfull left on the up
	{
		scrollUp(lineMax);		//move up the scroller max line numbers up
		i = i-lineMax;
		if ((unsigned)j>strlen(str+i*charMax*sizeof(char)))
		{
			j = strlen(str+i*charMax*sizeof(char));
		}
		y = height - 17 - (i+1-s)*lineSpace;
		x = charSpace*j;			//set the index & cursor position
	}
	else		//less than one screenfull on the up
	{
		scrY = height-16-16-scrHeight;
		i = i-s;
		s = 0;		//starting position
		if ((unsigned)j>strlen(str+i*charMax*sizeof(char)))
			j = strlen(str+i*charMax*sizeof(char));
		y = height - 17 - (i+1-s)*lineSpace;
		x = charSpace*j;
	}
}


/*controls page down operation*/
void pageDown()
{
	if (s+lineMax-1<imax-lineMax)		//one screenfull left down
	{
		scrollDown(lineMax);				//move down the scroller max line numbers up
		i = i+lineMax;
		if ((unsigned)j>strlen(str+i*charMax*sizeof(char)))
			j = strlen(str+i*charMax*sizeof(char));
		y = height - 17 - (i+1-s)*lineSpace;
		x = charSpace*j;					//set the index & cursor position
	}
	else if (s+lineMax-1 != imax)		//less than one screenfull left down
	{
		i = i+imax-lineMax-1-s;
		s = imax-lineMax+1;
		scrY = 18;
		if ((unsigned)j>strlen(str+i*charMax*sizeof(char)))
			j = strlen(str+i*charMax*sizeof(char));
		y = height - 17 - (i+1-s)*lineSpace;
		x = charSpace*j;
	}
}


/*subfunction of backspace*/
void backCopy()
{
	int m,l;
	if (strlen(str+i*charMax*sizeof(char))<=(unsigned)charMax-strlen(str+(i-1)*charMax*sizeof(char)))
	{
		i--;
		x = strlen(str+i*charMax*sizeof(char))*charSpace;
		y = y+lineSpace;

		strcat(str+i*charMax*sizeof(char)+j, str+(i+1)*charMax*sizeof(char));
		if (strlen(str+i*charMax*sizeof(char)))
		{
			j = strlen(str+i*charMax*sizeof(char));
		}
		for (k=i+1;k<imax; k++)		//copies the lines downward
		{
			strcpy(str+k*charMax*sizeof(char), str+(k+1)*charMax*sizeof(char));
		}
		reAlloc(imax);
		imax--;
		if (imax>=lineMax-1)
		{
			if (s>0)
			{
				scrHeight = scrHeight*1.020408;
				s--;
				y = height-17-(i+1-s)*lineSpace;
			}
			else
			{
				scrHeight = scrHeight*1.020408;
				scrY -= scrHeight*0.020408;
				y = height-17-(i+1-s)*lineSpace;
			}
		}
		else
			hsflag = 0;
	}
	else if (strlen(str+i*charMax*sizeof(char)) < (unsigned)charMax-1) 
	{
		i--;
		x = strlen(str+i*charMax*sizeof(char))*charSpace;
		y = y+lineSpace;

		j = strlen(str+i*charMax*sizeof(char));

		for(k=0,l=j;k<charMax-j-1;l++,k++)
		{
			str[i*charMax*sizeof(char)+l] = str[(i+1)*charMax*sizeof(char)+k];
		}
		str[i*charMax*sizeof(char)+charMax-1] = '\0';

		for (l=0; (unsigned)k<=strlen(str+(i+1)*charMax*sizeof(char));k++,l++)
		{
			str[(i+1)*charMax*sizeof(char)+l] = str[(i+1)*charMax*sizeof(char)+k];
		}
	}
	else
	{
		i--;
		x = strlen(str+i*charMax*sizeof(char))*charSpace;
		y = y+lineSpace;
		j = strlen(str+i*charMax*sizeof(char));
		k=i;
		do
		{
			k++;
			for (l=j,m=0;l<charMax-1;l++,m++)
			{
				str[(k-1)*charMax*sizeof(char)+l] = str[k*charMax*sizeof(char)+m];
			}
			if ((unsigned)m>strlen(str+k*charMax*sizeof(char)))
			{
				str[k*charMax*sizeof(char)] = '\0';
			}
			else
			{
				for (l=0;(unsigned)m<=strlen(str+k*charMax*sizeof(char));l++,m++)
				{
					str[k*charMax*sizeof(char)+l] = str[k*charMax*sizeof(char)+m];
				}
			}
		
		}while(strlen(str+k*charMax*sizeof(char))==(unsigned)j);

		if (strlen(str+k*charMax*sizeof(char))==0)
		{
			for (k=i+1;k<imax; k++)		//copies the lines downward
			{
				strcpy(str+k*charMax*sizeof(char), str+(k+1)*charMax*sizeof(char));
			}
			reAlloc(imax);
			imax--;
			if (imax>=lineMax-1)
			{
				if (s>0)
				{
					scrHeight = scrHeight*1.020408;
					s--;
					y = height-17-(i+1-s)*lineSpace;
				}
				else
				{
					scrHeight = scrHeight*1.020408;
					scrY -= scrHeight*0.020408;
					y = height-17-(i+1-s)*lineSpace;
				}
			}
			else
				hsflag = 0;
		}
		x = charSpace*j;
		y = height-16-(i+1-s)*lineSpace;
		
	}
}


/*backspace key function*/
void backspace(void)
{
	if (j!=0 || i!=0)		//not in the initial position
	{
		if (j == 0)			//from a line's beginning
		{
			backCopy();
		}
		else			//otherwise
		{
			//line is not full
			if (strlen(str+i*charMax*sizeof(char)) != (unsigned)charMax-1)
			{
				for (k=j; (unsigned)k<=strlen(str+i*charMax*sizeof(char)); k++)
				{
					str[i*charMax*sizeof(char)+k-1] = str[i*charMax*sizeof(char)+k];
				}
				x = x - charSpace;
				j--;
			}
			else		//line full
			{
				j--;
				del();
				x= j*charSpace;
			}
		}
	}
	else			//initial position, ring the bell
	{
		printf("\a");		
	}
}

/*maintains delete operation*/
void del(void)
{
	int l;
	if (str[i*charMax*sizeof(char)+j] != '\0')
	{
		if (strlen(str+i*charMax*sizeof(char)) != (unsigned)charMax-1)
		{
			for (k= j+1; (unsigned)k<=strlen(str+i*charMax*sizeof(char));k++)
			{
				str[i*charMax*sizeof(char)+k-1] = str[i*charMax*sizeof(char)+k];
			}
		}
		else
		{
			for (k=j; k<=charMax-2;k++)
			{
				str[i*charMax*sizeof(char)+k] = str[i*charMax*sizeof(char)+k+1];
			}
			k=i;
			do 
			{
				k++;
				if (k<=imax)
				{
					str[(k-1)*charMax*sizeof(char)+charMax-2] = str[k*charMax*sizeof(char)];
					for (l=1; (unsigned)l<=strlen(str+k*charMax*sizeof(char));l++)
					{
						str[k*charMax*sizeof(char)+l-1] = str[k*charMax*sizeof(char)+l];
					}
				}
			}while (strlen(str+k*charMax*sizeof(char))==(unsigned)charMax-2);
			if (strlen(str+k*charMax*sizeof(char))==0)
			{
				for (k=i+1;k<imax; k++)		//copies the lines downward
				{
					strcpy(str+k*charMax*sizeof(char), str+(k+1)*charMax*sizeof(char));
				}
				reAlloc(imax);
				imax--;
				if (imax>=lineMax-1)
				{
					if (s>0)
					{
						scrHeight = scrHeight*1.020408;
						s--;
						y = height-17-(i+1-s)*lineSpace;
					}
					else
					{
						scrHeight = scrHeight*1.020408;
						scrY -= scrHeight*0.020408;
						y = height-17-(i+1-s)*lineSpace;
					}
				}
				else
					hsflag = 0;
			}
		}
	}
	else if (i+1<=imax)
	{
		int tempI = i,tempJ = j, tempX = x, tempY = y;
		i++;
		j=0;
		x=0;
		y -= lineSpace;
		backCopy();
		i = tempI;
		j = tempJ;
		x = tempX;
		y = tempY;
	}
}

/*maintains enter operations*/
void enter()
{
	char *temp;
	int k,l,flag=0;
	
	if (str[i*charMax*sizeof(char)+j] != '\0')
	{
		if (strlen(str+i*charMax*sizeof(char))!=(unsigned)charMax-1)
		{
			imax++;
			reAlloc(imax+1);
			l=0;
			for (k=imax;k>i+1;k--)
			{
				strcpy(str+k*charMax*sizeof(char), str+(k-1)*charMax*sizeof(char));
			}
			temp = (char*)malloc((int)strlen(str+i*charMax*sizeof(char))-j);
			for (k=j; (unsigned)k<=strlen(str+i*charMax*sizeof(char)) ; k++)
			{
				temp[l++] = str[i*charMax*sizeof(char)+k];
			}
			str[i*charMax*sizeof(char)+j] = '\0';
			for (l=0; (unsigned)l <= strlen(temp); l++)
			{
				str[(i+1)*charMax*sizeof(char)+l] = temp[l];
			}
			
		}
		else
		{
			l=0;
			temp = (char*)malloc((int)strlen(str+i*charMax*sizeof(char))-j);
			for (k=j; (unsigned)k<=strlen(str+i*charMax*sizeof(char)) ; k++)
			{
				temp[l++] = str[i*charMax*sizeof(char)+k];
			}
			str[i*charMax*sizeof(char)+j] = '\0';

			enter();
			for(l=0; (unsigned)l <strlen(temp); l++)
			{
				character(temp[l]);
			}
			j=0;
			x=0;
			flag = 1;
		}
	}
	else
	{
		imax++;
		reAlloc(imax+1);
		for (k=imax; k>i+1; k--)
		{
			strcpy(str+k*charMax*sizeof(char), str+(k-1)*charMax*sizeof(char));
		}
		for (l=0; (unsigned)l<=strlen(str+(i+1)*charMax*sizeof(char)); l++)
		{
			str[(i+1)*charMax*sizeof(char)+l] = '\0';
		}
	}
	
	if (flag != 1)
	{
		i++;
		j = 0;
		x = 0;
		if((i-1)!=(s+lineMax-1))
		{
			y-=lineSpace;
		}
		if (imax>lineMax-1)
		{ 
			scrollOn();
		}
	}
}

/*for tab operation*/
void tab()
{
	if (j<=charMax-1-5)
	{
		for (k=strlen(str+i*charMax*sizeof(char)); k>=j; k--)
		{
			str[i*charMax*sizeof(char)+k+5] = str[i*charMax*sizeof(char)+k];
		}
		for (k=j;k<j+5;k++)
		{
			str[i*charMax*sizeof(char)+k] = ' ';
		}
		x += charSpace*5;
	}
}