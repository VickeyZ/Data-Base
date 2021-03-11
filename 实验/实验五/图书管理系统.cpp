#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#include <math.h>
#pragma comment(lib,"libmysql.lib")
//库名为  borrow
//库存信息表为book
//借阅信息表为borrowbook
//读者信息表为reader
//mysql中密码要设定为123456
	MYSQL mysql,*sock;    // 定义数据库连接的句柄，它被用于几乎所有的 MySQL 函数
	MYSQL_RES *res;       // 查询结果集，结构类型
	MYSQL_FIELD *fd ;     // 包含字段信息的结构
	MYSQL_ROW row ;       // 存放一行查询结果的字符串数组
	char  qbuf[256];
typedef struct{
 int booknumber;
 char bookname[50];
 char bookauthor[50];
 char bookpulisher[50];
 char bookdate[50];
 int  bookmoney;
 char booktype[50];
 int  booksumnumber;
 int  booknownumber;
 int  bookborrownumber;

}SSM;//库存信息结构体

typedef struct{
int Number;
  char Name[50];
  int Money;
  int IDCard;
  int  date;
  int  fine;
 int  DueDate;



}SSG;//定义借阅结构体
typedef struct{

int sno;
char name[50];
char classroom[50];
int  number; //学号
char  type[50];
int  time;
int  borrownumber;


}SSN;//定义学生结构体


void SSM_Init()//库存初始化
{
	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}
int i=0,j;
 SSM MY[50];
 printf("请输入库存总数目");
 scanf("%d",&j);
for(i=0;i<j;i++)
	{
     printf("请输入图书编号");
	 scanf("%d",&MY[i].booknumber);
     printf("请输入图书书名");
     scanf("%s",&MY[i].bookname);
	 printf("请输入图书作者");
	 scanf("%s",&MY[i].bookauthor);
	 printf("请输入图书出版社");
	 scanf("%s",&MY[i].bookpulisher);
	 printf("请输入图书出版日期(格式为：年.月.日)");
	 scanf("%s",&MY[i].bookdate);
	 printf("请输入图书金额");
	 scanf("%d",&MY[i].bookmoney);
	 printf("请输入图书类别(报刊、书籍、期刊)");
	 scanf("%s",&MY[i].booktype);
	 printf("请输入图书总入库数量");
	 scanf("%d",&MY[i].booksumnumber);
	 printf("请输入图书当前库存量");
	 scanf("%d",&MY[i].booknownumber);
     MY[i].bookborrownumber=MY[i].booksumnumber-MY[i].booknownumber;
     sprintf(qbuf, "insert into book (booknumber,bookname,bookauthor,bookpulisher,bookdate,bookmoney,booktype,booksumnumber,booknownumber,bookborrownumber)values (%d,'%s','%s','%s','%s',%d,'%s',%d,%d,%d);",MY[i].booknumber,MY[i].bookname,MY[i].bookauthor,MY[i].bookpulisher,MY[i].bookdate,MY[i].bookmoney,MY[i].booktype,MY[i].booksumnumber,MY[i].booknownumber,MY[i].bookborrownumber);
           mysql_query(&mysql, qbuf);
		   printf("库存信息写入成功！");
 }
	// field number

}
void SSN_Init()//读者信息初始化
{
	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}

   int i=0,j;
  SSN SM[50];
   printf("请输入总数：");
   scanf("%d",&j);
  for(i=0;i<j;i++)
{
	printf("请输入借书证号：");
	scanf("%d",&SM[i].sno);
	printf("请输入姓名：");
	scanf("%s",&SM[i].name);
	printf("请输入班级：");
	scanf("%s",&SM[i].classroom);
	printf("请输入学号：");
	scanf("%d",&SM[i].number);
	printf("请输入类型（学生或教师）");
	scanf("%s",&SM[i].type);
	printf("请输入借书数量");
	scanf("%d",&SM[i].borrownumber);
	printf("请输入借阅时间");
	scanf("%d",&SM[i].time);
   sprintf(qbuf,"insert into reader(sno,name,classroom,number,type,borrownumber,time) values(%d,'%s','%s',%d,'%s',%d,%d);",SM[i].sno,SM[i].name,SM[i].classroom,SM[i].number,SM[i].type,SM[i].borrownumber,SM[i].time);
    mysql_query(&mysql, qbuf);
	printf("读者信息写入成功！");
  }



}
void SSM_DO()//借阅信息的操作
{
	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","10251025","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}
     char k;
     SSM MY[50];
   	sprintf(qbuf,"select * from book group by booktype ");

if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
		printf("图书编号=%s, 图书书名=%s,图书作者=%s,图书出版社=%s，图书出版日期=%s，图书金额=%s，图书类别=%s，图书总入库数量=%s，图书当前数量=%s,图书借书证号=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
	}

	  printf("按类别分类完成！");
   printf("请输入需要进行操作的类型（W为添加，T为删除，Y为修改，N为查询）");
   scanf("%s",&k);
   if(k=='W')
   {
   int i=0,j;
   printf("请输入添加图书数目");
   scanf("%d",&j);
  for(i=0;i<j;i++)
	{
     printf("请输入添加图书编号");
	 scanf("%d",&MY[i].booknumber);
     printf("请输入添加图书书名");
     scanf("%s",&MY[i].bookname);
	 printf("请输入添加图书作者");
	 scanf("%s",&MY[i].bookauthor);
	 printf("请输入添加图书出版社");
	 scanf("%s",&MY[i].bookpulisher);
	 printf("请输入添加图书出版日期");
	 scanf("%s",&MY[i].bookdate);
	 printf("请输入添加图书金额");
	 scanf("%d",&MY[i].bookmoney);
	 printf("请输入添加图书类别(报刊、书籍、期刊)");
	 scanf("%s",&MY[i].booktype);
	 printf("请输入添加图书总入库数量");
	 scanf("%d",&MY[i].booksumnumber);
	 printf("请输入添加图书当前库存量");
	 scanf("%d",&MY[i].booknownumber);
     MY[i].bookborrownumber=MY[i].booksumnumber-MY[i].booknownumber;
     sprintf(qbuf, "insert into book (booknumber,bookname,bookauthor,bookpulisher,bookdate,bookmoney,booktype,booksumnumber,booknownumber,bookborrownumber)values (%d,'%s','%s','%s','%s',%d,'%s',%d,%d,%d);",MY[i].booknumber,MY[i].bookname,MY[i].bookauthor,MY[i].bookpulisher,MY[i].bookdate,MY[i].bookmoney,MY[i].booktype,MY[i].booksumnumber,MY[i].booknownumber,MY[i].bookborrownumber);
    mysql_query(&mysql, qbuf);
	printf("添加成功！");

   }
}
   if(k=='T')
   {  int i;
   printf("输入删除图书的编号");
   scanf("%d",&i);
   sprintf(qbuf,"delete from book where booknumber=%d;",i);
   mysql_query(&mysql, qbuf);
   printf("删除成功！");



   }
   if(k=='Y')
   {
     int i;
	 SSM MY;
	 printf("输入要修改图书的编号");
	 scanf("%d",&i);
      printf("请修改添加图书编号");
	 scanf("%d",&MY.booknumber);
     printf("请修改添加图书书名");
     scanf("%s",&MY.bookname);
	 printf("请修改添加图书作者");
	 scanf("%s",&MY.bookauthor);
	 printf("请修改添加图书出版社");
	 scanf("%s",&MY.bookpulisher);
	 printf("请修改添加图书出版日期");
	 scanf("%s",&MY.bookdate);
	 printf("请修改添加图书金额");
	 scanf("%d",&MY.bookmoney);
	 printf("请修改添加图书类别(报刊、书籍、期刊)");
	 scanf("%s",&MY.booktype);
	 printf("请修改添加图书总入库数量");
	 scanf("%d",&MY.booksumnumber);
	 printf("请修改添加图书当前库存量");
	 scanf("%d",&MY.booknownumber);
     MY.bookborrownumber=MY.booksumnumber-MY.booknownumber;
     sprintf(qbuf, "update book set booknumber=%d,bookname='%s',bookauthor='%s',bookpulisher='%s',bookdate='%s',bookmoney=%d,booktype='%s',booksumnumber=%d,booknownumber=%d,bookborrownumber=%d;",MY.booknumber,MY.bookname,MY.bookauthor,MY.bookpulisher,MY.bookdate,MY.bookmoney,MY.booktype,MY.booksumnumber,MY.booknownumber,MY.bookborrownumber);
   mysql_query(&mysql, qbuf);
   printf("更新成功！");




   }
   if(k=='N')
   {
    int i;

    printf("请输入要查询的图书编号");
    scanf("%d",&i);
    sprintf(qbuf,"select * from book where booknumber=%d;",i);
   if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
	printf("图书编号=%s, 图书书名=%s,图书作者=%s,图书出版社=%s，图书出版日期=%s，图书金额=%s，图书类别=%s，图书总入库数量=%s，图书当前数量=%s,图书借书证号=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
	}

	mysql_free_result(res);
	mysql_close(sock);

}

}
void  borrow_out()
{
		mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}


char k;
SSG MY;
printf("选择借阅的操作（Y为借出操作，N为还书操作，H为续借处理）");
scanf("%s",&k);

if(k=='Y')
{
printf("输入借阅的编号");
scanf("%d",&MY.Number);
printf("输入借阅的书名");
scanf("%s",&MY.Name);
printf("输入借阅的金额");
scanf("%d",&MY.Money);
printf("输入借阅的借书证号");
scanf("%d",&MY.IDCard);
printf("输入借阅的借阅日期");
scanf("%d",&MY.date);
printf("输入到期的罚款");
scanf("%d",&MY.fine);
printf("输入借阅的到期日期");
scanf("%d",&MY.DueDate);
sprintf(qbuf,"insert into borrowbook values(%d,'%s',%d,%d,%d,%d,%d);",MY.Number,MY.Name,MY.Money,MY.IDCard,MY.date,MY.fine,MY.DueDate);

mysql_query(&mysql, qbuf);


sprintf(qbuf,"update book set booknownumber=booknownumber-1, bookborrownumber=bookborrownumber+1 where booknumber=%d;",MY.Number);
mysql_query(&mysql, qbuf);

printf("录入成功 ！");


}
if(k=='N')
{int i=0;
int m,n;
printf("请输入还书的编号");
scanf("%d",&i);
printf("请输入日期");
scanf("%d",&m);
printf("请输入读者编号");
scanf("%d",&n);
	sprintf(qbuf,"select number,name,fine，duedate from borrowbook where IDCard=%d AND duedate=%d;",n,m);
	if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
	{printf("图书编号=%s,书名=%s,罚款=%s,到期时间=%s\n", row[0],row[1],row[2],row[3]);}
	}

sprintf(qbuf,"delete from borrowbook where number=%d;",i);
mysql_query(&mysql, qbuf);
sprintf(qbuf,"update book set booknownumber=booknownumber+1, bookborrownumber=bookborrownumber-1 where booknumber=%d;",MY.Number);
mysql_query(&mysql, qbuf);
printf("还书成功！");
}


if(k=='H')
{ int i,j;
printf("请输入续借天数：");
scanf("%d",&i);
printf("请输入图书编号:");
scanf("%d",&j);
sprintf(qbuf,"update borrowbook set duedate=duedate+%d where number=%d;",i,j);
mysql_query(&mysql, qbuf);


printf("续借成功！");
}
}
void reader()
{
	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}

   SSN_Init();
sprintf(qbuf,"select * from reader group by type;");
if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
		printf("借书证号=%s, 姓名=%s,班级=%s,学号=%s,类型=%s,借阅时间=%s,借书数量=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

char k;
printf("选择下列操作（Y为注销，N为查询）");
scanf("%s",&k);
if(k=='Y')
{
int i;
printf("请输入要注销的学号");
scanf("%d",&i);

sprintf(qbuf,"delete from reader where number=%d;",i);
mysql_query(&mysql, qbuf);
printf("注销成功！");

}
if(k=='N')
{int i;
printf("请输入要查找的学号");
scanf("%d",&i);

sprintf(qbuf,"select* from reader where number=%d;",i);
if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
		printf("借书证号=%s, 姓名=%s,班级=%s,学号=%s,类型=%s,借阅时间=%s,借书数量=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

}

}
void sum()
{  char k;
printf("请输入需要进行的操作（Y为查看借阅排行榜、N查看所有人的借书信息、Z显示所有至当日内到期未还书信息）");
  scanf("%s",&k);
  if(k=='Y')
  {	mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}
  sprintf(qbuf,"select* from book order by  bookborrownumber;");
if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
			printf("图书编号=%s, 图书书名=%s,图书作者=%s,图书出版社=%s，图书出版日期=%s，图书金额=%s，图书类别=%s，图书总入库数量=%s，图书当前数量=%s,图书借书证号=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
	}

  }

  if(k=='N')
  {
  mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}
	 sprintf(qbuf,"select* from reader ;");
if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
	printf("借书证号=%s, 姓名=%s,班级=%s,学号=%s,类型=%s,借阅时间=%s,借书数量=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

  }

if(k=='Z')
{ int i;
printf("请输入时间");
scanf("%d",&i);
mysql_init(&mysql);
	if (!(sock = mysql_real_connect(&mysql,"localhost","root","123456","Borrow",0,NULL,0)))
	{
		fprintf(stderr,"Couldn't connect to engine!/n%s/n/n", mysql_error(&mysql));
		perror("");
		exit(1);
	}
	 sprintf(qbuf,"select* from borrowbook duedate='%d';",i);;
if(mysql_query(sock,qbuf))
	{
		fprintf(stderr,"Query failed (%s)/n",mysql_error(sock));
		exit(1);
	}

	if (!(res = mysql_store_result(sock))) {
		fprintf(stderr,"Couldn't get result from %s/n", mysql_error(sock));
		exit(1);
	}

	printf("number of fields returned: %d\n", mysql_num_fields(res));	// field number

	while (row = mysql_fetch_row(res))
	{
		printf("借书证号=%s, 姓名=%s,班级=%s,学号=%s,类型=%s,借书数量=%s,借书时间=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}



}


}
int  meau()
{  int  i;
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| 菜单 |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (1)  录入库存信息 |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (2)   读者管理|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (3)  借阅资料管理|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (4)  借阅管理 |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (5)  统计分析|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (0) 退出系统 |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\n\t\t请选择(0-5):");
scanf("%d",&i);
return i;
}

void  main()
{ char m;
  do{ int k;
   k=meau();
if(k==1)
    SSM_Init();//库存信息初始化
  if(k==2)
  	reader();
  	if(k==3) //读者信息
    SSM_DO();
    if(k==4)
	 borrow_out();
  if(k==5)
	sum();
  if(k==0)
   break;
   printf("是否继续 Y（继续）N （退出)");
   scanf("%s",&m);
  } while(m=='Y');
}