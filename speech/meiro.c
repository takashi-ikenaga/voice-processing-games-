
#include <stdio.h>
#define STAGE       2      //ステージ数
#define MAZE_ROW    5      //迷路の行数
#define MAZE_COLUMN 5      //迷路の列数
#define MAXCHR 120
//プレイヤー
typedef struct
{
  int row;        //プレイヤー位置(行)
  int column;     //プレイヤー位置(列)
}MazePlayer;

//迷路の一ブロック
enum MazeKind {PATH, WALL, START, GOAL};    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag {FALSE, TRUE};                //ブロックが判明しているかどうか

typedef struct
{
  enum MazeKind kind;            //種類(道、壁、スタート、ゴール)
  enum MazeFlag flag;            //ブロックが判明しているかどうか
} MazeBlock;

//プレイヤー初期化
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW ; i++) //行
  {
    for(j = 0;  j < MAZE_COLUMN; j++) //列
    {
      if(maze[i][j].kind == START) //スタート地点ならばプレイヤーの位置に設定する
      {
        *playerRow    = i;
        *playerColumn = j;
        return 0; //関数終了(プレイヤーを設定できれば残りの処理は必要ない)
      }
    }
  }

  //スタート地点がなければ、プレイヤーを設定できずここまでくる
printf("スタートがありません\n");
  return -1;
}

//迷路表示
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  int i, j;

  for(i = 0; i < MAZE_ROW; i++) //行
  {
    for(j = 0; j < MAZE_COLUMN; j++ ) //列
    {
     if(i == playerRow && j == playerColumn) //プレイヤー位置
      {
        printf("Ｐ");
      }
      else if(maze[i][j].flag == FALSE) //ブロックが判明していない場合
      {
        printf("？");
      }
      else
      {
        switch(maze[i][j].kind)
        {
        case WALL:
          printf("口"); break; //壁
        case GOAL:
          printf("Ｇ"); break; //ゴール
        default:
          printf("　"); break; //その他(道、スタート)
        }
      }
    }
    printf("\n");
  }
}



//方向
enum MazeDirection{UP, DOWN, LEFT, RIGHT, Invalid}; 

//プレイヤー移動
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN], enum MazeDirection direction1)
{

  switch(direction1){
    //上移動
  case UP:
  {
    if(*playerRow - 1 >= 0) //迷路の範囲外でないことを確認
    {
      maze[*playerRow - 1][*playerColumn].flag = TRUE; //ブロックの種類が判明

      if(maze[*playerRow - 1][*playerColumn].kind != WALL) //壁かどうか確認
      {
        *playerRow -= 1; //移動
        printf("\n上に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //下移動
  case DOWN:
  {
    if(*playerRow + 1 < MAZE_ROW)
    {
      maze[*playerRow + 1][*playerColumn].flag = TRUE;

      if(maze[*playerRow + 1][*playerColumn].kind != WALL)
      {
        *playerRow += 1;
        printf("\n下に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //左移動
  case LEFT:
  {
    if(*playerColumn - 1 >= 0)
    {
      maze[*playerRow][*playerColumn - 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn - 1].kind != WALL)
      {
        *playerColumn -= 1;
        printf("\n左に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;

  //右移動
  case RIGHT:
  {
    if(*playerColumn + 1 < MAZE_COLUMN)
    {
      maze[*playerRow][*playerColumn + 1].flag = TRUE;

      if(maze[*playerRow][*playerColumn + 1].kind != WALL)
      {
        *playerColumn += 1;
        printf("\n右に移動しました。\n");
      }
      else
      {
        printf("\n壁です。\n");
      }
    }
    else
    {
      printf("\n範囲外です\n");

    }
  }
  break;
  }
}


//ゴール判定
int MazeGoalCheck(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN])
{
  if(maze[*playerRow][*playerColumn].kind == GOAL ) //プレイヤー位置がゴール地点に等しい
  {
     printf("ゴール!\n");
    return 1;
  }
  return 0;
}

void MazeGame(int stage)
{
  enum MazeDirection direction;
  //プレイヤー
  MazePlayer player;

  //迷路
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


//プレイヤー初期化
  if(MazePlayerInit(&player.row, &player.column, maze[stage]) == -1)
  {
    //関数MazePlayerInitが-1を返すとき初期化に失敗している
    //よって、この時点でプログラムを終了し、迷路の表示は行わない
    return ;
  }
 
  char input[MAXCHR], s1[MAXCHR], s2[MAXCHR], s3[MAXCHR];
  //enum MazeDirection direction;
 printf("初期迷路表示\n");
  MazeDraw(player.row, player.column, maze[stage]);
    //プレイヤー移動
  printf("%d:上\n", UP);
  printf("%d:下\n", DOWN);
  printf("%d:左\n", LEFT);
  printf("%d:右\n", RIGHT);
  printf("音声を入力してください。：\n");
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
            printf(" 認識結果は %s です。\n",s3);
	    
	     if( MazeGoalCheck(&player.row, &player.column, maze[stage]) == 1)
	      {
	       MazeDraw(player.row, player.column, maze[stage]);
	      break;
	       }
	     else if(strcmp(s3,"上")==0){
	      direction=UP;
	      //プレイヤー移動
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:上\n", UP);
	       printf("%d:下\n", DOWN);
	       printf("%d:左\n", LEFT);
	       printf("%d:右\n", RIGHT);
	       printf("音声を入力してください。：\n");
	      } 
	    else if(strcmp(s3,"下")==0){
	      direction=DOWN;
	      //プレイヤー移動
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	       MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:上\n", UP);
	       printf("%d:下\n", DOWN);
	       printf("%d:左\n", LEFT);
	       printf("%d:右\n", RIGHT);
	       printf("音声を入力してください。：\n");
	      }
	    else if(strcmp(s3,"左")==0){
	      direction=LEFT;
	      //プレイヤー移動
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	       printf("%d:上\n", UP);
	       printf("%d:下\n", DOWN);
	       printf("%d:左\n", LEFT);
	       printf("%d:右\n", RIGHT);
	       printf("音声を入力してください。：\n");
	      } 
	    else if(strcmp(s3,"右")==0){
	      direction=RIGHT;
	       //プレイヤー移動
	      MazePlayerMove(&player.row, &player.column, maze[stage],direction);
	      MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:上\n", UP);
	       printf("%d:下\n", DOWN);
	       printf("%d:左\n", LEFT);
	       printf("%d:右\n", RIGHT);
	       printf("音声を入力してください。：\n");
	      }

	     // else if( MazeGoalCheck(player.row, player.column, maze[stage]) == 1)
	     // {
	     // MazeDraw(player.row, player.column, maze[stage]);
	     // printf("ゴール!\n");
	     // break;
	     // }
	    else
	      { printf("進みません\n\n");
		  MazeDraw(player.row, player.column, maze[stage]);
	        printf("%d:上\n", UP);
	       printf("%d:下\n", DOWN);
	       printf("%d:左\n", LEFT);
	       printf("%d:右\n", RIGHT);
	       printf("音声を入力してください。：\n");
	      }
	   }//if
    }//for(;;)
 
}

enum MazeMenu {STAGE0,STAGE1, EXIT};

//タイトル
int MazeTitle()
{
 char input[MAXCHR], s1[MAXCHR], s2[MAXCHR], s3[MAXCHR];
  int menu = -1;

  printf("\n\n＊＊＊迷路ゲーム＊＊＊\n\n");

  printf("メニュー\n");
  printf("%d:ステージ0\n", STAGE0);
  printf("%d:ステージ1\n", STAGE1);
  printf("%d:終了\n", EXIT);

  printf("メニューを選んで音声で入力してください。\n");

 for(;;)
    {      
        fgets(input,MAXCHR,stdin);
        sscanf(input,"%s%s%s",s1,s2,s3);
	 if (!strcmp(s1,"sentence1:")) 
	   { 
	     printf(" 認識結果は %s です。\n",s3);
	     if(strcmp(s3,"０")==0){
	      menu=0; 
	      break;
	     }
	     else if(strcmp(s3,"１")==0){
	      menu=1;
	      break;
	     }
	   }
    }
 printf(" パターン%sを表示します。\n",s3);
   return menu;
}

int main(void)
{
  int stage;
  while(1) 
    {
    stage= MazeTitle();
    printf("gamestart\n");
    if(stage == EXIT) //EXITならwhileループを抜けて終了
    {
      break;
    }
    //迷路ゲーム
    MazeGame(stage);
     printf("gameend\n");
    }
  return 0;
}
