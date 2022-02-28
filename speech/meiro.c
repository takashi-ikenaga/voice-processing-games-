
#include <stdio.h>
#define STAGE       2      //���ơ�����
#define MAZE_ROW    5      //��ϩ�ιԿ�
#define MAZE_COLUMN 5      //��ϩ�����
#define MAXCHR 120
//�ץ쥤�䡼
typedef struct
{
  int row;        //�ץ쥤�䡼����(��)
  int column;     //�ץ쥤�䡼����(��)
}MazePlayer;

//��ϩ�ΰ�֥�å�
enum MazeKind {PATH, WALL, START, GOAL};    //�֥�å��μ���(ƻ���ɡ��������ȡ�������)
enum MazeFlag {FALSE, TRUE};                //�֥�å���Ƚ�����Ƥ��뤫�ɤ���

typedef struct
{
  enum MazeKind kind;            //����(ƻ���ɡ��������ȡ�������)
  enum MazeFlag flag;            //�֥�å���Ƚ�����Ƥ��뤫�ɤ���
} MazeBlock;

//�ץ쥤�䡼�����
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW ; i++) //��
  {
    for(j = 0;  j < MAZE_COLUMN; j++) //��
    {
      if(maze[i][j].kind == START) //�������������ʤ�Хץ쥤�䡼�ΰ��֤����ꤹ��
      {
        *playerRow    = i;
        *playerColumn = j;
        return 0; //�ؿ���λ(�ץ쥤�䡼������Ǥ���лĤ�ν�����ɬ�פʤ�)
      }
    }
  }

  //���������������ʤ���С��ץ쥤�䡼������Ǥ��������ޤǤ���
printf("�������Ȥ�����ޤ���\n");
  return -1;
}

//��ϩɽ��
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW; i++) //��
  {
    for(j = 0; j < MAZE_COLUMN; j++ ) //��
    {
     if(i == playerRow && j == playerColumn) //�ץ쥤�䡼����
      {
        printf("��");
      }
      else if(maze[i][j].flag == FALSE) //�֥�å���Ƚ�����Ƥ��ʤ����
      {
        printf("��");
      }
      else
      {
        switch(maze[i][j].kind)
        {
        case WALL:
          printf("��"); break; //��
        case GOAL:
          printf("��"); break; //������
        default:
          printf("��"); break; //����¾(ƻ����������)
        }
      }
    }
    printf("\n");
  }
}



//����
enum MazeDirection{UP, DOWN, LEFT, RIGHT, Invalid}; 

//�ץ쥤�䡼��ư
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN], enum MazeDirection direction1)
{

  switch(direction1){
    //���ư
  case UP:
  {
    if(*playerRow - 1 >= 0) //��ϩ���ϰϳ��Ǥʤ����Ȥ��ǧ
    {
      maze[*playerRow - 1][*playerColumn].flag = TRUE; //�֥�å��μ��बȽ��

      if(maze[*playerRow - 1][*playerColumn].kind != WALL) //�ɤ��ɤ�����ǧ
      {
        *playerRow -= 1; //��ư
        printf("\n��˰�ư���ޤ�����\n");
      }
      else
      {
        printf("\n�ɤǤ���\n");
      }
    }
    else
    {
      printf("\n�ϰϳ��Ǥ�\n");

    }
  }
  break;

  //����ư
  case DOWN:
  {
    if(*playerRow + 1 < MAZE_ROW)
    {
      maze[*playerRow + 1][*playerColumn].flag = TRUE;

      if(maze[*playerRow + 1][*playerColumn].kind != WALL)
      {
        *playerRow += 1;
        printf("\n���˰�ư���ޤ�����\n");
      }
      else
      {
        printf("\n�ɤǤ���\n");
      }
    }
    else
    {
      printf("\n�ϰϳ��Ǥ�\n");

    }
  }
  break;

  //����ư
  case LEFT:
  {
    if(*playerColumn - 1 >= 0)
    {
      maze[*playerRow][*playerColumn - 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn - 1].kind != WALL)
      {
        *playerColumn -= 1;
        printf("\n���˰�ư���ޤ�����\n");
      }
      else
      {
        printf("\n�ɤǤ���\n");
      }
    }
    else
    {
      printf("\n�ϰϳ��Ǥ�\n");

    }
  }
  break;

  //����ư
  case RIGHT:
  {
    if(*playerColumn + 1 < MAZE_COLUMN)
    {
      maze[*playerRow][*playerColumn + 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn + 1].kind != WALL)
      {
        *playerColumn += 1;
        printf("\n���˰�ư���ޤ�����\n");
      }
      else
      {
        printf("\n�ɤǤ���\n");
      }
    }
    else
    {
      printf("\n�ϰϳ��Ǥ�\n");

    }
  }
  break;
  }
}


//������Ƚ��
int MazeGoalCheck(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  if(maze[*playerRow][*playerColumn].kind == GOAL ) //�ץ쥤�䡼���֤�������������������
  {
     printf("������!\n");
    return 1;
  }
  return 0;
}

void MazeGame(int stage)
{
  enum MazeDirection direction;
  //�ץ쥤�䡼
  MazePlayer player;

  //��ϩ
  MazeBlock maze[STAGE][MAZE_ROW][MAZE_COLUMN] = 
    {
      { //STAGE0
        { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
        { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
        { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
        { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
        { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
      },

      { //STAGE1
        { {PATH , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
        { {PATH , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {PATH , FALSE} },
        { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {GOAL , TRUE } },
        { {PATH , FALSE} , {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
        { {PATH , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      }
    };


//�ץ쥤�䡼�����
  if(MazePlayerInit(&player.row, &player.column, maze[stage]) == -1)
  {
    //�ؿ�MazePlayerInit��-1���֤��Ȥ�������˼��Ԥ��Ƥ���
    //��äơ����λ����ǥץ�����λ������ϩ��ɽ���ϹԤ�ʤ�
    return ;
  }
 
  char input[MAXCHR], s1[MAXCHR], s2[MAXCHR], s3[MAXCHR];
  //enum MazeDirection direction;
 printf("�����ϩɽ��\n");
  MazeDraw(player.row, player.column, maze[stage]);
    //�ץ쥤�䡼��ư
  printf("%d:��\n", UP);
  printf("%d:��\n", DOWN);
  printf("%d:��\n", LEFT);
  printf("%d:��\n", RIGHT);
  printf("���������Ϥ��Ƥ�����������\n");
  for(;;)
    {      
        if( MazeGoalCheck(&player.row, &player.column, maze[stage]) == 1)
	      {
	       MazeDraw(player.row, player.column, maze[stage]);
	      break;
	       }
        fgets(input,MAXCHR,stdin);
        sscanf(input,"%s%s%s",s1,s2,s3);
	 if (!strcmp(s1,"sentence1:")) 
	   {
            printf(" ǧ����̤� %s �Ǥ���\n",s3);
	    
	     if( MazeGoalCheck(&player.row, &player.column, maze[stage]) == 1)
	      {
	       MazeDraw(player.row, player.column, maze[stage]);
	      break;
	       }
	     else if(strcmp(s3,"��")==0){
	      direction=UP;
	      //�ץ쥤�䡼��ư
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:��\n", UP);
	       printf("%d:��\n", DOWN);
	       printf("%d:��\n", LEFT);
	       printf("%d:��\n", RIGHT);
	       printf("���������Ϥ��Ƥ�����������\n");
	      } 
	    else if(strcmp(s3,"��")==0){
	      direction=DOWN;
	      //�ץ쥤�䡼��ư
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	       MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:��\n", UP);
	       printf("%d:��\n", DOWN);
	       printf("%d:��\n", LEFT);
	       printf("%d:��\n", RIGHT);
	       printf("���������Ϥ��Ƥ�����������\n");
	      }
	    else if(strcmp(s3,"��")==0){
	      direction=LEFT;
	      //�ץ쥤�䡼��ư
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	       printf("%d:��\n", UP);
	       printf("%d:��\n", DOWN);
	       printf("%d:��\n", LEFT);
	       printf("%d:��\n", RIGHT);
	       printf("���������Ϥ��Ƥ�����������\n");
	      } 
	    else if(strcmp(s3,"��")==0){
	      direction=RIGHT;
	       //�ץ쥤�䡼��ư
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:��\n", UP);
	       printf("%d:��\n", DOWN);
	       printf("%d:��\n", LEFT);
	       printf("%d:��\n", RIGHT);
	       printf("���������Ϥ��Ƥ�����������\n");
	      }

	     // else if( MazeGoalCheck(player.row, player.column, maze[stage]) == 1)
	     // {
	     // MazeDraw(player.row, player.column, maze[stage]);
	     // printf("������!\n");
	     // break;
	     // }
	    else
	      { printf("�ʤߤޤ���\n\n");
		  MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:��\n", UP);
	       printf("%d:��\n", DOWN);
	       printf("%d:��\n", LEFT);
	       printf("%d:��\n", RIGHT);
	       printf("���������Ϥ��Ƥ�����������\n");
	      }
	   }//if
    }//for(;;)
 
}

enum MazeMenu {STAGE0,STAGE1, EXIT};

//�����ȥ�
int MazeTitle()
{
 char input[MAXCHR], s1[MAXCHR], s2[MAXCHR], s3[MAXCHR];
  int menu = -1;

  printf("\n\n��������ϩ�����������\n\n");

  printf("��˥塼\n");
  printf("%d:���ơ���0\n", STAGE0);
  printf("%d:���ơ���1\n", STAGE1);
  printf("%d:��λ\n", EXIT);

  printf("��˥塼������ǲ��������Ϥ��Ƥ���������\n");

 for(;;)
    {      
        fgets(input,MAXCHR,stdin);
        sscanf(input,"%s%s%s",s1,s2,s3);
	 if (!strcmp(s1,"sentence1:")) 
	   { 
	     printf(" ǧ����̤� %s �Ǥ���\n",s3);
	     if(strcmp(s3,"��")==0){
	      menu=0; 
	      break;
	     }
	     else if(strcmp(s3,"��")==0){
	      menu=1;
	      break;
	     }
	   }
    }
 printf(" �ѥ�����%s��ɽ�����ޤ���\n",s3);
   return menu;
}

int main(void)
{
  int stage;
  while(1) 
    {
    stage= MazeTitle();
    printf("gamestart\n");
    if(stage == EXIT) //EXIT�ʤ�while�롼�פ�ȴ���ƽ�λ
    {
      break;
    }
    //��ϩ������
    MazeGame(stage);
     printf("gameend\n");
    }
  return 0;
}
