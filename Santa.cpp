#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")


void print();
void begin();//载入背景音乐
void printstone();
void santa();//控制Santa上升和下降
void judgement();
void scoleprint();
void endorretry();
void maxscore();
void choose();

int santa_x=150,santa_y=300,i=0,k=0;//Santa左下坐标
int scole=0,max=0,t=0,diff=-1;
int stone_x1,stone_y1;//上柱子左下坐标
int stone_x2,stone_y2;//上柱子左下坐标
IMAGE background,santa1[4],santa2[4],scole1[10],scole2[10],stone_up1,stone_up2,stone_down1,stone_down2
,stone_up3,stone_up4,stone_down3,stone_down4;//图片储存变量

MOUSEMSG m;		// 定义鼠标消息



int main()
{
	


	if(t==0)
	{
		begin();
		t++;
	}	
	if(t)
	{	
		print();
	}


	getch();  //空格开始
	//santa_y=300;santa_x=150;i=0;k=0;
	scole=0;	
	while(1)
	{
		santa();
		print();
		judgement();
		
	}
	closegraph();
	system("pause");
	return 0;
}






void print()
{
	putimage(0, 0, &background);//背景图像
	printstone();//画柱子
	putimage(santa_x, santa_y,&santa1[i%3],NOTSRCERASE);
	putimage(santa_x, santa_y,&santa2[i%3],SRCINVERT);
	if(k%5==0)
		i++;
	k++;
	scoleprint();
	FlushBatchDraw();		// 绘制
}



void printstone()//柱子的移动规律
{
	if(diff==1)
		Sleep(45);
	else if(diff==2)
		Sleep(35);
	if(stone_x1>210)//此时画面存在两根柱子
	{
		//三光栅操作
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);  //掩码图
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);	//精灵图
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		putimage(stone_x2, stone_y2, &stone_up4,NOTSRCERASE);
		putimage(stone_x2, stone_y2, &stone_up3,SRCINVERT);
		putimage(stone_x2, stone_y2+750, &stone_down4,NOTSRCERASE);
		putimage(stone_x2, stone_y2+750, &stone_down3,SRCINVERT);
		stone_x1-=5;stone_x2-=5;
	}
	else if(stone_x1==210)//左柱子消失，同时右柱子由2被赋为1
	{
		stone_x2=stone_x1;
		stone_y2=stone_y1;
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1-=5;
		stone_x2-=5;
	}
	else if(stone_x1<210&&stone_x1>0)//画面只存在一个柱子的情况
	{
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1-=5;
		stone_x2-=5;	 
	}
	if(stone_x1==0)//左柱子碰到左端同时，右柱子生成
	{	  
		stone_y1=rand()%290-510;
		stone_x1=350;
		putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
		putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
		putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
		putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
		stone_x1-=5;
		stone_x2-=5;
	}
}



void begin()
{
	//
	PlaySound("000.wav", NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
	initgraph(350,600);
	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	//设置窗口标题文字
	SetWindowText(hwnd, "Flappy Santa!");
	IMAGE beforegame;
	loadimage(&beforegame,"flappysanta\\source\\beforegame.jpg");
	putimage(0,0,&beforegame);
	Sleep(1000);
	choose();//getch();
	BeginBatchDraw();// 开启批量绘图模式
	loadimage(&background, "flappysanta\\source\\bkgroundfb.jpg");//载入背景图片
	//Santa
	loadimage(&santa2[0], "flappysanta\\source\\santa1-2.gif");
	loadimage(&santa1[0], "flappysanta\\source\\santa1-1.gif");
	loadimage(&santa2[1], "flappysanta\\source\\santa2-2.gif");
	loadimage(&santa1[1], "flappysanta\\source\\santa2-1.gif");
	loadimage(&santa2[2], "flappysanta\\source\\santa3-2.gif");
	loadimage(&santa1[2], "flappysanta\\source\\santa3-1.gif");
	loadimage(&santa2[3], "flappysanta\\source\\santa4-2.gif");
	loadimage(&santa1[3], "flappysanta\\source\\santa4-1.gif");
	//柱子
	loadimage(&stone_up1,"flappysanta\\source\\stone_up1.gif");
	loadimage(&stone_up2,"flappysanta\\source\\stone_up2.gif");
	loadimage(&stone_down1,"flappysanta\\source\\stone_down1.gif");
	loadimage(&stone_down2,"flappysanta\\source\\stone_down2.gif");
	loadimage(&stone_up3,"flappysanta\\source\\stone_up1.gif");
	loadimage(&stone_up4,"flappysanta\\source\\stone_up2.gif");
	loadimage(&stone_down3,"flappysanta\\source\\stone_down1.gif");
	loadimage(&stone_down4,"flappysanta\\source\\stone_down2.gif");
	//数字
	loadimage(&scole1[0],"flappysanta\\source\\0_1.jpg");
	loadimage(&scole2[0],"flappysanta\\source\\0_2.jpg");
	loadimage(&scole1[1],"flappysanta\\source\\1_1.jpg");
	loadimage(&scole2[1],"flappysanta\\source\\1_2.jpg");
	loadimage(&scole1[2],"flappysanta\\source\\2_1.jpg");
	loadimage(&scole2[2],"flappysanta\\source\\2_2.jpg");
	loadimage(&scole1[3],"flappysanta\\source\\3_1.jpg");
	loadimage(&scole2[3],"flappysanta\\source\\3_2.jpg");
	loadimage(&scole1[4],"flappysanta\\source\\4_1.jpg");
	loadimage(&scole2[4],"flappysanta\\source\\4_2.jpg");
	loadimage(&scole1[5],"flappysanta\\source\\5_1.jpg");
	loadimage(&scole2[5],"flappysanta\\source\\5_2.jpg");
	loadimage(&scole1[6],"flappysanta\\source\\6_1.jpg");
	loadimage(&scole2[6],"flappysanta\\source\\6_2.jpg");
	loadimage(&scole1[7],"flappysanta\\source\\7_1.jpg");
	loadimage(&scole2[7],"flappysanta\\source\\7_2.jpg");
	loadimage(&scole1[8],"flappysanta\\source\\8_1.jpg");
	loadimage(&scole2[8],"flappysanta\\source\\8_2.jpg");
	loadimage(&scole1[9],"flappysanta\\source\\9_1.jpg");
	loadimage(&scole2[9],"flappysanta\\source\\9_2.jpg");
	srand(time(0));	//初始化种子
	//print();
	//第一根柱子初始化
	stone_y1=rand()%10-280;

	stone_x1=350;
	stone_x2=stone_y2=-9999;	//避免一开始就显示两根柱子
}



void santa()
{
	char space;
	int n;
	
	if(kbhit())	//检测按键
	{
		space=getch();
		if(space==' ')	//检测空格
		{
				santa_y-=45;
		}
		else if(space==27)  //ESC
		{	
			getch();
		}
	}
	else
	{
		santa_y+=7;
	}
	
}



void judgement()
{
	if((stone_x1>10 && stone_x1<20)||(stone_x1>174&&stone_x1<184))
	{
		if(((santa_y+20)>(stone_y1+576)&&(santa_y+20)<(stone_y1+600))||(((santa_y+20)>(stone_y1+726))&&(santa_y+20)<(stone_y1+750)))
		{
			endorretry();//结束游戏
		}
	}
	else if(stone_x1>=20 && stone_x1<=174)
	{
		if(!(santa_y>(stone_y1+600)&&santa_y+20<(stone_y1+726)))
		{
			endorretry();	//结束游戏
		}
	}
	if(santa_y>576)
	{
		endorretry();//结束游戏
	}
	if(stone_x1==150)
	{	
		scole++;
	}
}



void endorretry()
{
	if(santa_y<550 && stone_x1>160)
	{	
		while(santa_y<550)
		{
			putimage(0, 0, &background);//背景图像
			putimage(stone_x1, stone_y1, &stone_up2,NOTSRCERASE);
			putimage(stone_x1, stone_y1, &stone_up1,SRCINVERT);
			putimage(stone_x1, stone_y1+750, &stone_down2,NOTSRCERASE);
			putimage(stone_x1, stone_y1+750, &stone_down1,SRCINVERT);
			putimage(stone_x2, stone_y2, &stone_up4,NOTSRCERASE);
			putimage(stone_x2, stone_y2, &stone_up3,SRCINVERT);
			putimage(stone_x2, stone_y2+750, &stone_down4,NOTSRCERASE);
			putimage(stone_x2, stone_y2+750, &stone_down3,SRCINVERT);
			putimage(santa_x, santa_y,&santa1[3],NOTSRCERASE);
			putimage(santa_x, santa_y,&santa2[3],SRCINVERT);
			FlushBatchDraw();
			santa_y++;
		}
	}
	IMAGE gameover1,gameover2,record1,record2,atlast;
	loadimage(&gameover1, "flappysanta\\source\\gameover1.gif");
	loadimage(&gameover2, "flappysanta\\source\\gameover2.gif");
	loadimage(&record1, "flappysanta\\source\\record1.gif");
	loadimage(&record2, "flappysanta\\source\\record2.gif");
	putimage(80, 200, &gameover1,NOTSRCERASE);
	putimage(80, 200, &gameover2,SRCINVERT);
	putimage(100, 293, &record1,NOTSRCERASE);
	putimage(100, 293, &record2,SRCINVERT);
	scoleprint(); 
	maxscore();
	FlushBatchDraw();
	Sleep(1000);
	getch();
	loadimage(&atlast, "flappysanta\\source\\atlast.jpg");
	putimage(0,0,&atlast);
	scoleprint(); 
	FlushBatchDraw();
	
	//第Ì¨²一°?根¨´柱¨´子Á¨®
	stone_y1=rand()%10-280;
	stone_x1=350;
	stone_x2=stone_y2=-9999;
	santa_y=300;
	scole=0;
	main();	
	
}



void scoleprint()
{
	IMAGE *fen1[6],*fen2[6];
	int he,weishu=1,i=0,sdsf=scole;
	if(sdsf==0)
	{
		putimage(255,50,&scole1[0],NOTSRCERASE);
		putimage(255,50,&scole2[0],SRCINVERT);
		
	}
	while(sdsf>0)
	{
		he=sdsf%10;
		fen1[i]=&scole1[he];
		fen2[i]=&scole2[he]; 
		putimage(280-25*weishu,50,fen1[i],NOTSRCERASE);
		putimage(280-25*weishu,50,fen2[i],SRCINVERT);
		sdsf/=10;
		i++;
		weishu++;
	}

}

void maxscore()
{
	if(scole>max)
		max=scole;
	IMAGE *wen1[6],*wen2[6];
	int he,weishu=1,i=0,M=max;
	if(M==0)
	{
		putimage(230,300,&scole1[0],NOTSRCERASE);
		putimage(230,300,&scole2[0],SRCINVERT);
		
	}
	while(M>0)
	{
		he=M%10;
		wen1[i]=&scole1[he];
		wen2[i]=&scole2[he]; 
		putimage(255-25*weishu,300,wen1[i],NOTSRCERASE);
		putimage(255-25*weishu,300,wen2[i],SRCINVERT);
		M/=10;
		i++;
		weishu++;
	}
}

void choose()
{
	int choo=0;
	while(1)
	{
		while(MouseHit())
		{
			// 获取一条鼠标信息
			m = GetMouseMsg();
			if(m.uMsg==WM_LBUTTONDOWN&&m.x>=70&&m.x<=130&&m.y>=240&&m.y<=350)
			{
				diff=1;
				choo=1;
			}
			else if(m.uMsg==WM_LBUTTONDOWN&&m.x>=220&&m.x<=280&&m.y>=240&&m.y<=350)
			{
				diff=2;
				choo=1;
			}

		}
		if(choo==1)
		{
			break;		
		}
	}
}


