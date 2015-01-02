#include <stdio.h>    
#include <string.h>    
#include <stdlib.h>   
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>


//初始化光源
GLfloat lightPos[] = { 1.0f, 0.0f, -1.0f, 0.5f };
GLfloat  specular[] = { 1.0f, 0.8f, 0.4f, 0.5f};
GLfloat  specref[] =  { 1.0f, 1.0f, 0.3f, 0.1f };
GLfloat  diffuse[] = { 0.6f, 0.8f, 0.2f, 0.5f};

//当前窗口的宽高
int curw;
int curh;
int swingLeft = 0;
int swingRight = 0;
bool isSwingForward = false;
bool isLighting = false;
int curTurn=180 ;//当前面向角度
int maxAngel = 0;//最大摆动角
int stepDis = 0;//大腿摆动速度
float speed = 0;//前进速度
bool isStand = true;
float curDistanceX=0 , curDistanceZ=0;//当前距离
float legDis = 0 ;


void display(void)  
{  
	glClear (GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	//画背景
	glBegin(GL_QUADS);

	glColor3ub(255,255,255);
	glVertex3f(-8.0f, -3.0f, 4.0f);
	glVertex3f(8.0f, -3.0f, 4.0f);
	glColor3ub(33,33,33);
	glVertex3f(8.0f, -3.0f, -4.0f);
	glVertex3f(-8.0f, -3.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(33,33,33);
	glVertex3f(-8.0f, -3.0f, -4.0f);
	glVertex3f(8.0f, -3.0f, -4.0f);
	glColor3ub(156,66,180);
	glVertex3f(8.0f, 8.0f, -4.0f);
	glVertex3f(-8.0f, 8.0f, -4.0f);
	glEnd();

	//入栈，画右下半身
	glPushMatrix();

	//对坐标系平移与旋转
	glTranslatef (curDistanceX,0.0,curDistanceZ); //前进  
	glRotatef ((GLfloat) curTurn, 0.0, 1.0, 0.0);//转向

	//右调坐标系，定位旋转中心
	glTranslatef (0.375,0.0, 0.0);
	//是否提起右大腿
	glRotatef ((GLfloat) swingRight, 1.0, 0.0, 0.0);
	//下调坐标系，准备画右大腿
	glTranslatef (0.0, -0.5, 0.0);   
	glColor3f(0.5,0.8,0.3);
	//画右大腿
	glPushMatrix();
	glScalef (0.4, 1.0, 0.4);
	glutSolidCube(1.0);  
	glPopMatrix();

	//下调坐标系，定位旋转中心
	glTranslatef (0.0, -0.5, 0.0);
	//是否提起右小腿   
	glRotatef ((GLfloat) legDis, 1.0, 0.0, 0.0);
	//下调坐标系，准备画右小腿
	glTranslatef (0.0, -0.5, 0.0);  
	glColor3f(0.1,0.5,0.5);
	//画右小腿
	glPushMatrix();  
	glScalef (0.3, 1.0, 0.3);  
	glutSolidCube(1.0);  
	glPopMatrix();

	//下调坐标系，准备画右脚
	glTranslatef (0.0, -0.5, -0.1); 
	glColor3f(0.8,0.8,0.2);    
	//画右脚
	glPushMatrix();  
	glScalef (0.5, 0.1, 0.7);  
	glutSolidCube(1.0);  
	glPopMatrix();

	glPopMatrix ();
	//出栈
   
	//入栈，画左下半身
	glPushMatrix();
	//对坐标系平移与旋转
	glTranslatef (curDistanceX,0.0,curDistanceZ);//前进
	glRotatef ((GLfloat) curTurn, 0.0, 1.0, 0.0);//转向
   
	//同理处理左大腿
	glTranslatef (-0.375, 0.0, 0.0);   
	glRotatef ((GLfloat) swingLeft, 1.0, 0.0, 0.0);  
	glTranslatef (0.0, -0.5, 0.0);   
	glColor3f(0.5,0.8,0.3);   
	glPushMatrix();  
	glScalef (0.4, 1.0, 0.4);  
	glutSolidCube(1.0);  
	glPopMatrix();   
	//同理处理左小腿
	glTranslatef (0.0, -0.5, 0.0);   
	glRotatef ((GLfloat) legDis, 1.0, 0.0, 0.0);  
	glTranslatef (0.0, -0.5, 0.0);  
	glColor3f(0.1,0.5,0.5);   
	glPushMatrix();  
	glScalef (0.3, 1.0, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	//同理处理左脚
	glTranslatef (0.0, -0.5, -0.1);
	glColor3f(0.8,0.8,0.2);   
	glPushMatrix();  
	glScalef (0.5, 0.1, 0.7);  
	glutSolidCube(1.0);  
	glPopMatrix();   
	glPopMatrix();   
	//出栈

	//入栈，画胸部与头部
	glPushMatrix(); 
	glTranslatef (curDistanceX,0.0,curDistanceZ);   
	glRotatef ((GLfloat) curTurn, 0.0, 1.0, 0.0);  
	//胸部
	glTranslatef (0.0, 1.0,  0.0);
	glColor3f(1.0,0.7,0.1);   
	glPushMatrix();  
	glScalef (1.4, 2.0, 0.5);  
	glutSolidCube(1.0);  
	glPopMatrix();   
	//头部
	glTranslatef (0.0, 1.25, 0.0);
	glColor3f(0.9,0.9,0.9);   
	glPushMatrix();  
	glScalef (0.5, 0.5, 0.5);  
	glutSolidCube(1.0);  
	glPopMatrix();

	//眼睛
	glTranslatef (0.125, 0.1, -0.25);
	glColor3f(0.2,0.2,0.2);   
	glPushMatrix();  
	glScalef (0.1, 0.1, 0.1);  
	glutSolidCube(1.0);  
	glPopMatrix();

	glTranslatef (-0.25, 0.0, 0.0);
	glColor3f(0.2,0.2,0.2);   
	glPushMatrix();  
	glScalef (0.1, 0.1, 0.1);  
	glutSolidCube(1.0);  
	glPopMatrix();

	//嘴巴
	glTranslatef (0.125, -0.25, 0.0);
	glColor3f(0.8,0.2,0.2);   
	glPushMatrix();  
	glScalef (0.3, 0.1, 0.1);  
	glutSolidCube(1.0);  
	glPopMatrix();



	glPopMatrix();
	//出栈

	//入栈，画右臂部分
	glPushMatrix();   
	glTranslatef (curDistanceX,0.0,curDistanceZ);   
	glRotatef ((GLfloat) curTurn, 0.0, 1.0, 0.0);  
	//右臂
	glTranslatef (0.85, 1.75, 0.0); 
	glRotatef ((GLfloat) swingLeft, 1.0, 0.0, 0.0);  
	glTranslatef (0.0, -0.5, 0.0);  
	glColor3f(0.8,0.4,0.5);     
	glPushMatrix();  
	glScalef (0.3, 1.6, 0.4);  
	glutSolidCube(1.0);  
	glPopMatrix();   
	glPopMatrix();
	//出栈

	//入栈，画左臂部分
	glPushMatrix();   
	glTranslatef (curDistanceX,0.0,curDistanceZ);   
	glRotatef ((GLfloat) curTurn, 0.0, 1.0, 0.0);  
	//左臂 
	glTranslatef (-0.85, 1.75, 0.0);  
	glRotatef ((GLfloat) swingRight, 1.0, 0.0, 0.0);  
	glTranslatef (0.0, -0.5, 0.0);  
	glColor3f(0.8,0.4,0.5);     
	glPushMatrix();  
	glScalef (0.3, 1.6, 0.4);  
	glutSolidCube(1.0);  
	glPopMatrix();   
	glPopMatrix();
	//出栈

	glutSwapBuffers();  
}     

 
 /**
	当窗口大小改变时
 **/
void reshape (int w, int h)  
{   
   curw=w;   
   curh=h;  
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);   
   glMatrixMode (GL_PROJECTION);  
   glLoadIdentity ();  
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);  
   glMatrixMode(GL_MODELVIEW);  
   glLoadIdentity();  
   glTranslatef (0.0, 0.0, -8.0);  
}  
  
void keyEvent(unsigned char key, int x, int y)  
{  
   switch (key) {  
	  case 'c'://开关灯
		 if(isLighting){
			 glDisable(GL_LIGHTING);
			 isLighting = false;
			 glutPostRedisplay();
		 }
		 else{
			 glEnable(GL_LIGHTING);
			 isLighting = true;
			 glutPostRedisplay();
		 }
         break;
      case 'x'://右转
         curTurn = (curTurn - 5) % 360;  
         glutPostRedisplay(); 
         break;  
      case 'z'://左转
         curTurn = (curTurn + 5) % 360;  
         glutPostRedisplay();
         break;  
      case 27:  
         exit(0);  
         break;  
      default:  
         break;  
   }  
}


//时间函数,定时刷新
void timer(int value)
{	
	int tempTurn=curTurn;  
    curDistanceX = curDistanceX - speed*sin((GLfloat)tempTurn/360*3.14*2);  
    curDistanceZ=curDistanceZ- speed*cos((GLfloat)tempTurn/360*3.14*2);  
    if(!isSwingForward){  
        swingLeft = (swingLeft + stepDis);  
        swingRight = (swingRight - stepDis);  
        if(swingLeft>0){legDis=legDis - stepDis*1.2;}  
        else{legDis=legDis + stepDis*1.2;}  
    }  
    else  
    {  
        swingLeft = (swingLeft - stepDis);  
        swingRight = (swingRight + stepDis);  
        if(swingLeft<0){legDis=legDis - stepDis*1.2;}  
        else{legDis=legDis + stepDis*1.2;}  
    }
    if(swingLeft>maxAngel){  
        isSwingForward = true;  
    }  
    if(swingLeft<maxAngel*-1){  
        isSwingForward = false;  
    } 
	display();
	glutPostRedisplay();
	if(!isStand) glutTimerFunc(value ,timer, value);
}

void stand(){
	swingLeft = 0;
	swingRight = 0;
	isSwingForward = false;
	legDis = 0 ;
}



/*主菜单*/
void MenuFunc(int data)
{
	switch(data){
	case 1:
		isStand = true;
		stand();
		break;
	case 2:
		stand();
		maxAngel = 20;
		stepDis = 1;
		speed = 0.02;
		//避免呼叫Timer两次
		if(isStand) glutTimerFunc(20 ,timer, 20);
		isStand = false;
		break;
	case 3:
		stand();
		maxAngel = 55;
		stepDis = 5;
		speed = 0.04;
		//避免呼叫Timer两次
		if(isStand) glutTimerFunc(10 ,timer, 10);
		isStand = false;
		break;

	}
}

//初始化背景等参数设置
void init(void)  
{
	//光源

	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, diffuse);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,30.0f);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,20.0f);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT, GL_SHININESS,8);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	/*创建主菜单并加入菜单条目及子菜单*/
	glutCreateMenu(MenuFunc);
	glutAddMenuEntry("站立",1);
	glutAddMenuEntry("走动",2);
	glutAddMenuEntry("奔跑",3);
	glutAddMenuEntry("z,x控制左右转，c开关灯",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glEnable(GL_CULL_FACE); // 开启剪裁
	glCullFace(GL_BACK); // 裁掉背面

}  
  

//主函数
int main(int argc, char** argv)  
{  
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
   glutInitWindowSize (800, 700);   
   glutInitWindowPosition (100, 100);  
   glutCreateWindow("简易机器人(z,x控制左右转，c开关灯)");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);  
   glutKeyboardFunc(keyEvent);

   glutMainLoop();  
   return 0;  
}  