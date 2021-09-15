
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<string.h>

#define MAX 10
int k=0;
typedef struct circle
{
	GLfloat x;	//x 
	GLfloat y;	//y 
	GLfloat r;	// radius
}circle;
int q=0,size=0;
circle c[MAX];	//array c of user defined data type circle
int a[MAX];		
int initial[MAX];
GLfloat initial_x1,initial_x2,initial_y1,initial_y2,initial_r1,initial_r2;
int aa,bb,cc;	
GLfloat temp1,temp2;
int global_i = 0, global_j = 0;	//i and j values for selection sort
int swapping = 0;	//flag to check if circle are being swapped or its being swapped
int sorting = 0;	
void initialise()
{   int i;
	global_i = global_j = swapping = 0; 
	for (i=0;i<size;i++)
	{
		a[i] = initial[i];	
		c[i].r = a[i]*4.0;	
		c[i].y = 300.0;		//vertical center of window
		if (i == 0)
			c[i].x = 45.0;
		else
			c[i].x = c[i-1].x + 90.0;///radius of circle based  onprevius array value
		printf("%f - %f - %f\n",c[i].x,c[i].y,c[i].r); 
	}
}
void initialise2()
{   int i;
	global_i = global_j = swapping = 0; 
	for (i=0;i<size;i++)
	{
		
		c[i].r = a[i]*4.0;	
		c[i].y = 300.0;		
		if (i == 0)
			c[i].x = 45.0;	
		else
			c[i].x = c[i-1].x + 90.0;
		printf("%f - %f - %f\n",c[i].x,c[i].y,c[i].r); 
	}
}
//display text on screen 
void bitmap_output(int x, int y, char *string, void *font)
{
  int len, i;

  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

//function to integer to string
void int_str(int rad,char r[])
{
	switch(rad)
	{
		case 1 : strcpy(r, "1"); break;
		case 2 : strcpy(r, "2"); break;
		case 3 : strcpy(r, "3"); break;
		case 4 : strcpy(r, "4"); break;
		case 5 : strcpy(r, "5"); break;
		case 6 : strcpy(r, "6"); break;
		case 7 : strcpy(r, "7"); break;
		case 8 : strcpy(r, "8"); break;
		case 9 : strcpy(r, "9"); break;
		case 10 : strcpy(r, "10"); break;
	}
	
}

//drawing circle triangle fans(so that circle will be 2D 
void circle_draw(circle c)
{
	float i;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(c.x, c.y);	
	for (i=0;i<360;i+=1)
		glVertex2f(c.x + sin(i) * c.r, c.y + cos(i) * c.r);
	glEnd();

	//display the value of circle below
	int x = c.x-2;
	int y = c.y-(c.r+25);
	int rad = c.r / 4;
	char r[3] = "";
	int_str(rad,r);
	glColor3f(0.0,0.0,0.0);
	bitmap_output(x, y, r, GLUT_BITMAP_HELVETICA_18);
	
}


void swap_circles(circle *cc1,circle *cc2)
{   //swap_circles(&c[bb],&c[m]);

     if (swapping == 0)	// for the first time .... saving the attribute values
	{   
		initial_x1 = cc1->x; 
		initial_x2 = cc2->x; 
		initial_y1 = cc1->y; 
		initial_y2 = cc2->y;
		initial_r1 = cc1->r; 
		initial_r2 = cc2->r;
		swapping = 1;	
		temp1=initial_r1 ;
		temp2=initial_r2;
	}

	if (initial_x1 <= initial_x2)	//decrease the center of circle in right till its = center of left circle
		cc1->x += 0.1;		//speed of animation
       	
    //if (initial_x2 >= initial_x1)//increase the center of circle in left till its < center of right circle
	//cc2->x -= 1.0;
	
	
   /*	printf(" circle 1 initial1 %f  struct x %f\n",initial_x1,cc1->x);
	printf("circle 2 initial2 %f  struct x %f\n",initial_x2,cc2->x);
    printf(" circle 1 rad initial1%f  structr %f\n",initial_r1,cc1->r);
	printf("circle 2  rad initial2 %f  struct r %f\n",initial_r2,cc2->r);*/

	// when circle in left reaches the smallest circle in the left
	if (cc1->x>=initial_x2)  
	{
		
		swapping = 0;
	    cc2->x=initial_x1 ;
	    cc2->r=initial_r1 ;
	
	    cc1->r=temp2 ;
	    initialise2();
		glutSwapBuffers();
		
	}
	
}




void sort()	//selection sort sort algo
{   int m,w;
	if (!swapping) //if not in process of swappin 2 circles only then get 2 new circles to swap
	{
		while (global_i < size)
		{   
		    m=global_i;
			global_j = global_i+1;
			while (global_j <=size-1)
			{
				if (a[global_j] < a[m])
				{
					m=global_j;
					
				}
				global_j ++;
			}
			
		    if(a[m] < a[global_i])
			{      aa=a[global_i];
			       bb=global_i;
			       cc=a[m];
		            printf("%d %d\n",a[global_i],a[m]);
					int temp = a[global_i];
					a[global_i] = a[m];
					a[m] = temp;	
					global_i ++;
					
					bitmap_output(10, 400, "iteration",GLUT_BITMAP_9_BY_15);
	
		    goto swap;	
			}
			
				bitmap_output(10, 400, "iteration",GLUT_BITMAP_9_BY_15);	
			global_i ++;
		}
	}
	swap:
	printf("swapping --> %d - %d\n",aa,cc);
	bitmap_output(10, 375, "Swapping ->",GLUT_BITMAP_9_BY_15);
	
	char r[3]="";
	int_str(aa,r);
	bitmap_output(150, 375, r,GLUT_BITMAP_9_BY_15);
	int_str(cc,r);
	bitmap_output(175, 375, r,GLUT_BITMAP_9_BY_15);
    //printf("*************************************calling swap**********\n");
    q=q+1;
    printf("%d\n",q);
    //bitmap_output(10, 75, "iteration phase",GLUT_BITMAP_9_BY_15);
    //int_str(global_i,r);
	//bitmap_output(10, 65, r,GLUT_BITMAP_9_BY_15);
	swap_circles(&c[bb],&c[m]);
    
}

void display_text()
{   
        glBegin(GL_POLYGON);//top blue rectangle
        glColor3f(0,0.7,1);
        glVertex2f(0,0);
        
        glVertex2f(900,0);
        glColor3f(1,0.8,1);
        glVertex2f(900,600);
        glColor3f(1,0.8,1);
        glVertex2f(0,600);
    glEnd();
    glColor3f(1,0.2,0.5);
	bitmap_output(350, 530,"SELECTION SORT ",GLUT_BITMAP_HELVETICA_18);//title larger font
	glBegin(GL_LINE_LOOP); //to underline the title
		glVertex2f(280, 525);
		glVertex2f(650, 525);
	glEnd();
	
	
    bitmap_output(10, 495, "Illustrating selection sort swapping using circles with varying radius",GLUT_BITMAP_HELVETICA_18);
   

	
	if (sorting == 0)//if not sorting display menu
	{
		bitmap_output(10, 455, "WELCOME",GLUT_BITMAP_HELVETICA_18);
		bitmap_output(10, 435, "Press s to START sorting or RESUME sorting",GLUT_BITMAP_HELVETICA_18);
		bitmap_output(10, 415, "Press t to pause sorting",GLUT_BITMAP_HELVETICA_18);
		bitmap_output(10, 395, "Press r to  see the sorting again",GLUT_BITMAP_HELVETICA_18);
		bitmap_output(10, 378, "Press Esc to close ",GLUT_BITMAP_HELVETICA_18);
	}
	else if (sorting == 1)
	{
		glColor3f(0.5,0.5,0.5);
		bitmap_output(10, 455, "Sorting in progress...",GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 435, "Please do not quit",GLUT_BITMAP_9_BY_15);
		glColor3f(0.0,0.0,0.0);
	}
	
}

void front()
{   glColor3f(0.0,0.0,1.0);

	    glBegin(GL_POLYGON);//top blue rectangle
        glColor3f(0,0.7,1);
        glVertex2f(0,0);
        
        glVertex2f(900,0);
        glColor3f(1,0.8,1);
        glVertex2f(900,600);
        glColor3f(1,0.8,1);
        glVertex2f(0,600);
    glEnd();
		
		
	glColor3f(0.0,0.0,1.0);
	bitmap_output(300, 495, "SELECTION SORT",GLUT_BITMAP_HELVETICA_18);
	glBegin(GL_LINE_LOOP); 
		glVertex2f(250, 490);
		glVertex2f(500, 490);
	glEnd();
	bitmap_output(200,300, "NAME AND USN : ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(435,300, "Sharal Lenet Pinto - 4MT18CS084 : ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(435,270, "Poojary Shreya Jaya - 4MT18CS061 ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(200,240, "Under Guidance Of : ",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(435,220, "Ms. Aishwarya M Bhat",GLUT_BITMAP_HELVETICA_18);
	bitmap_output(435,200, "Ms. Sunitha N V ",GLUT_BITMAP_HELVETICA_18);

	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
	  	  glVertex2f(594,120.0);
		  glVertex2f(594,145);
		  glVertex2f(836,145);
		  glVertex2f(836,120.0);
    glEnd();
	glColor3f(0.0,1.0,0.0);
	bitmap_output(600, 125, "Press Enter to continue.......",GLUT_BITMAP_HELVETICA_18);
		
}

void display(void)
{   int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);

	if (k==0)
    front();
	else
	{
	
	display_text();
	
	glPointSize(2.0);
	for (i=0;i<MAX;i++)
	{
		glColor3f(1.0,0.0,0.0);
		circle_draw(c[i]);
	}
	if (global_i< size && sorting == 1) // sorting value is one when key 's' is pressed
		sort();
	else
		sorting = 0;
	}
	
	glFlush();
	glutSwapBuffers();

}

void keyboard (unsigned char key, int x, int y) 
{
	if(key==13)
		k=1;
	if (k==1)
	{
	switch (key)
	{
		case 27 : exit (0); //27 is the ascii code for the ESC key
		case 's' : sorting = 1; break;
		case 't'  : sorting = 0; break;
		case 'r' : initialise(); break;//reset everything
	}
	}
}



void init(void)
{
		glClearColor(1.0,1.0,1.0,0.0);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0,900.0,0.0,600.0);
}

void main(int argc, char ** argv)
{       int q;
		glutInit(&argc,argv);
		printf("ENTER THE TOTAL NUBER OF ELEMENTS (between 1 to 11)");
        scanf("%d",&size);
        if(size>1 && size<=MAX)
        {
        	printf("enter the array values");
	     	for(q=0;q<size;q++)
		    {
		    scanf("%d",&initial[q]);
		    }
		    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
		    glutInitWindowPosition(50,50);
		    glutInitWindowSize(900,600);
		    glutCreateWindow("selection sort");
		    init();
		    initialise();		
		    glutDisplayFunc(display);
	    	glutIdleFunc (display);
	    	glutKeyboardFunc (keyboard);
		     
		}
		else
		{
		printf("YOU HAVE ENTERED THE ARRAY SIZE ");	
		printf("EITHER LESS THAN 2 OR GREATER THAN 10");
		}
		
		glutMainLoop();
}



