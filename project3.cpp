
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <math.h>


typedef struct ball
{
    double x;      
    double y;		
	double z;       
    double r;		
}Ball;


typedef struct ballList
{
    struct ballList * next;
    Ball ball;
}BallList;

void insert(Ball ball);						
double distance(Ball b1, Ball b2);          
double abs(double num);					    
int judge(Ball b);							
void putBall();								
void putPoint(double x, double y,double z);			

BallList *head = NULL;
double step = 0.01;							
int num = 0;                              
double sumr = 0;							

int main()
{
    int n, pointNum, i;

    printf("请输入空间内所要放置的气球数量: ");
    scanf("%d",&n);
     printf("请输入空间内点的数量: ");
    scanf("%d",&pointNum);
    for(i = 0; i < pointNum; i ++)
    {
        printf("请输入第%d个点的坐标(其间用空格隔开)：",i+1);
        double x, y,z;
        scanf("%lf %lf%lf", &x, &y,&z);
        putPoint(x, y,z);
    }
   

    printf("\nx坐标\t y坐标\tz坐标\t 半径\n");
    for(i = 0; i < n; i ++)
    {
        putBall();
    }
    ballList *tmp = head,*kz = head;
   for(i = 0; i < pointNum; i ++)
   {kz=kz->next;
   }
    while(kz)
    {
        Ball ball = tmp->ball;
         printf("%.3lf\t %.3lf\t %.3lf\t %.3lf \n",  ball.x, ball.y,ball.z ,ball.r);
        tmp = tmp->next;
        kz=kz->next;
    }
    printf("\nr^2之和为:\t %lf\n", sumr);
    sleep(3);
    return 0;
}

void putPoint(double x, double y,double z)
{
    Ball ball = {x, y, z,0};
    insert(ball);
}

void insert(Ball ball)
{
    ballList * newBall = (ballList *)malloc(sizeof(ballList));
    newBall->ball = ball;
    newBall->next = head;
    head = newBall;
}

void putBall()
{
    Ball ball = {-1 + step, -1 + step,-1+step, 0};
    Ball maxBall = ball;
    int i, j,k;
    for (i = 0; ball.x < 1; ++i)
    {
        ball.x += step;
        ball.y = -1 + step;
		ball.z=-1+step;
        for (j = 0; ball.y < 1; ++j)
        {
            ball.y += step;
			ball.z=-1+step;
			for(k=0;ball.z<1;++k){
				ball.z+=step;
            ball.r = 0;
            double rstep = 0.1;
            while(rstep > 0.00001)
            {
                if(ball.r > maxBall.r)
                {
                    maxBall = ball;
                }
                ball.r += rstep;
                if(!judge(ball))
                {
                    ball.r -= rstep;
                    rstep /= 10;
                }
            }
          }
		}
    }
    if(judge(maxBall))
    {
        insert(maxBall);
        num++;
        sumr += maxBall.r * maxBall.r;
      
    }
}

int judge(Ball b)
{
    if((abs(b.x) + b.r) > 1 || (abs(b.y) + b.r) > 1||(abs(b.z)+b.r)>1)
    {
        return false;
    }
    ballList *tmp = head;
    while(tmp)
    {
        Ball ball = tmp->ball;
        if(distance(b, ball) < b.r + ball.r )
        {
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}

double abs(double num)
{
    if(num > 0)
        return num;
    return 0 - num;
}

double distance(Ball b1, Ball b2)
{
    double x1 = b1.x;
    double y1 = b1.y;
	double z1=b1.z;
    double x2 = b2.x;
    double y2 = b2.y;
	double z2=b2.z;
    return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)+(z1-z2)*(z1-z2), 0.5);
}

