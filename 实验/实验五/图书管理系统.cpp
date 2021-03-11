#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#include <math.h>
#pragma comment(lib,"libmysql.lib")
//����Ϊ  borrow
//�����Ϣ��Ϊbook
//������Ϣ��Ϊborrowbook
//������Ϣ��Ϊreader
//mysql������Ҫ�趨Ϊ123456
	MYSQL mysql,*sock;    // �������ݿ����ӵľ�����������ڼ������е� MySQL ����
	MYSQL_RES *res;       // ��ѯ��������ṹ����
	MYSQL_FIELD *fd ;     // �����ֶ���Ϣ�Ľṹ
	MYSQL_ROW row ;       // ���һ�в�ѯ������ַ�������
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

}SSM;//�����Ϣ�ṹ��

typedef struct{
int Number;
  char Name[50];
  int Money;
  int IDCard;
  int  date;
  int  fine;
 int  DueDate;



}SSG;//������Ľṹ��
typedef struct{

int sno;
char name[50];
char classroom[50];
int  number; //ѧ��
char  type[50];
int  time;
int  borrownumber;


}SSN;//����ѧ���ṹ��


void SSM_Init()//����ʼ��
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
 printf("������������Ŀ");
 scanf("%d",&j);
for(i=0;i<j;i++)
	{
     printf("������ͼ����");
	 scanf("%d",&MY[i].booknumber);
     printf("������ͼ������");
     scanf("%s",&MY[i].bookname);
	 printf("������ͼ������");
	 scanf("%s",&MY[i].bookauthor);
	 printf("������ͼ�������");
	 scanf("%s",&MY[i].bookpulisher);
	 printf("������ͼ���������(��ʽΪ����.��.��)");
	 scanf("%s",&MY[i].bookdate);
	 printf("������ͼ����");
	 scanf("%d",&MY[i].bookmoney);
	 printf("������ͼ�����(�������鼮���ڿ�)");
	 scanf("%s",&MY[i].booktype);
	 printf("������ͼ�����������");
	 scanf("%d",&MY[i].booksumnumber);
	 printf("������ͼ�鵱ǰ�����");
	 scanf("%d",&MY[i].booknownumber);
     MY[i].bookborrownumber=MY[i].booksumnumber-MY[i].booknownumber;
     sprintf(qbuf, "insert into book (booknumber,bookname,bookauthor,bookpulisher,bookdate,bookmoney,booktype,booksumnumber,booknownumber,bookborrownumber)values (%d,'%s','%s','%s','%s',%d,'%s',%d,%d,%d);",MY[i].booknumber,MY[i].bookname,MY[i].bookauthor,MY[i].bookpulisher,MY[i].bookdate,MY[i].bookmoney,MY[i].booktype,MY[i].booksumnumber,MY[i].booknownumber,MY[i].bookborrownumber);
           mysql_query(&mysql, qbuf);
		   printf("�����Ϣд��ɹ���");
 }
	// field number

}
void SSN_Init()//������Ϣ��ʼ��
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
   printf("������������");
   scanf("%d",&j);
  for(i=0;i<j;i++)
{
	printf("���������֤�ţ�");
	scanf("%d",&SM[i].sno);
	printf("������������");
	scanf("%s",&SM[i].name);
	printf("������༶��");
	scanf("%s",&SM[i].classroom);
	printf("������ѧ�ţ�");
	scanf("%d",&SM[i].number);
	printf("���������ͣ�ѧ�����ʦ��");
	scanf("%s",&SM[i].type);
	printf("�������������");
	scanf("%d",&SM[i].borrownumber);
	printf("���������ʱ��");
	scanf("%d",&SM[i].time);
   sprintf(qbuf,"insert into reader(sno,name,classroom,number,type,borrownumber,time) values(%d,'%s','%s',%d,'%s',%d,%d);",SM[i].sno,SM[i].name,SM[i].classroom,SM[i].number,SM[i].type,SM[i].borrownumber,SM[i].time);
    mysql_query(&mysql, qbuf);
	printf("������Ϣд��ɹ���");
  }



}
void SSM_DO()//������Ϣ�Ĳ���
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
		printf("ͼ����=%s, ͼ������=%s,ͼ������=%s,ͼ�������=%s��ͼ���������=%s��ͼ����=%s��ͼ�����=%s��ͼ�����������=%s��ͼ�鵱ǰ����=%s,ͼ�����֤��=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
	}

	  printf("����������ɣ�");
   printf("��������Ҫ���в��������ͣ�WΪ��ӣ�TΪɾ����YΪ�޸ģ�NΪ��ѯ��");
   scanf("%s",&k);
   if(k=='W')
   {
   int i=0,j;
   printf("���������ͼ����Ŀ");
   scanf("%d",&j);
  for(i=0;i<j;i++)
	{
     printf("���������ͼ����");
	 scanf("%d",&MY[i].booknumber);
     printf("���������ͼ������");
     scanf("%s",&MY[i].bookname);
	 printf("���������ͼ������");
	 scanf("%s",&MY[i].bookauthor);
	 printf("���������ͼ�������");
	 scanf("%s",&MY[i].bookpulisher);
	 printf("���������ͼ���������");
	 scanf("%s",&MY[i].bookdate);
	 printf("���������ͼ����");
	 scanf("%d",&MY[i].bookmoney);
	 printf("���������ͼ�����(�������鼮���ڿ�)");
	 scanf("%s",&MY[i].booktype);
	 printf("���������ͼ�����������");
	 scanf("%d",&MY[i].booksumnumber);
	 printf("���������ͼ�鵱ǰ�����");
	 scanf("%d",&MY[i].booknownumber);
     MY[i].bookborrownumber=MY[i].booksumnumber-MY[i].booknownumber;
     sprintf(qbuf, "insert into book (booknumber,bookname,bookauthor,bookpulisher,bookdate,bookmoney,booktype,booksumnumber,booknownumber,bookborrownumber)values (%d,'%s','%s','%s','%s',%d,'%s',%d,%d,%d);",MY[i].booknumber,MY[i].bookname,MY[i].bookauthor,MY[i].bookpulisher,MY[i].bookdate,MY[i].bookmoney,MY[i].booktype,MY[i].booksumnumber,MY[i].booknownumber,MY[i].bookborrownumber);
    mysql_query(&mysql, qbuf);
	printf("��ӳɹ���");

   }
}
   if(k=='T')
   {  int i;
   printf("����ɾ��ͼ��ı��");
   scanf("%d",&i);
   sprintf(qbuf,"delete from book where booknumber=%d;",i);
   mysql_query(&mysql, qbuf);
   printf("ɾ���ɹ���");



   }
   if(k=='Y')
   {
     int i;
	 SSM MY;
	 printf("����Ҫ�޸�ͼ��ı��");
	 scanf("%d",&i);
      printf("���޸����ͼ����");
	 scanf("%d",&MY.booknumber);
     printf("���޸����ͼ������");
     scanf("%s",&MY.bookname);
	 printf("���޸����ͼ������");
	 scanf("%s",&MY.bookauthor);
	 printf("���޸����ͼ�������");
	 scanf("%s",&MY.bookpulisher);
	 printf("���޸����ͼ���������");
	 scanf("%s",&MY.bookdate);
	 printf("���޸����ͼ����");
	 scanf("%d",&MY.bookmoney);
	 printf("���޸����ͼ�����(�������鼮���ڿ�)");
	 scanf("%s",&MY.booktype);
	 printf("���޸����ͼ�����������");
	 scanf("%d",&MY.booksumnumber);
	 printf("���޸����ͼ�鵱ǰ�����");
	 scanf("%d",&MY.booknownumber);
     MY.bookborrownumber=MY.booksumnumber-MY.booknownumber;
     sprintf(qbuf, "update book set booknumber=%d,bookname='%s',bookauthor='%s',bookpulisher='%s',bookdate='%s',bookmoney=%d,booktype='%s',booksumnumber=%d,booknownumber=%d,bookborrownumber=%d;",MY.booknumber,MY.bookname,MY.bookauthor,MY.bookpulisher,MY.bookdate,MY.bookmoney,MY.booktype,MY.booksumnumber,MY.booknownumber,MY.bookborrownumber);
   mysql_query(&mysql, qbuf);
   printf("���³ɹ���");




   }
   if(k=='N')
   {
    int i;

    printf("������Ҫ��ѯ��ͼ����");
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
	printf("ͼ����=%s, ͼ������=%s,ͼ������=%s,ͼ�������=%s��ͼ���������=%s��ͼ����=%s��ͼ�����=%s��ͼ�����������=%s��ͼ�鵱ǰ����=%s,ͼ�����֤��=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
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
printf("ѡ����ĵĲ�����YΪ���������NΪ���������HΪ���账��");
scanf("%s",&k);

if(k=='Y')
{
printf("������ĵı��");
scanf("%d",&MY.Number);
printf("������ĵ�����");
scanf("%s",&MY.Name);
printf("������ĵĽ��");
scanf("%d",&MY.Money);
printf("������ĵĽ���֤��");
scanf("%d",&MY.IDCard);
printf("������ĵĽ�������");
scanf("%d",&MY.date);
printf("���뵽�ڵķ���");
scanf("%d",&MY.fine);
printf("������ĵĵ�������");
scanf("%d",&MY.DueDate);
sprintf(qbuf,"insert into borrowbook values(%d,'%s',%d,%d,%d,%d,%d);",MY.Number,MY.Name,MY.Money,MY.IDCard,MY.date,MY.fine,MY.DueDate);

mysql_query(&mysql, qbuf);


sprintf(qbuf,"update book set booknownumber=booknownumber-1, bookborrownumber=bookborrownumber+1 where booknumber=%d;",MY.Number);
mysql_query(&mysql, qbuf);

printf("¼��ɹ� ��");


}
if(k=='N')
{int i=0;
int m,n;
printf("�����뻹��ı��");
scanf("%d",&i);
printf("����������");
scanf("%d",&m);
printf("��������߱��");
scanf("%d",&n);
	sprintf(qbuf,"select number,name,fine��duedate from borrowbook where IDCard=%d AND duedate=%d;",n,m);
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
	{printf("ͼ����=%s,����=%s,����=%s,����ʱ��=%s\n", row[0],row[1],row[2],row[3]);}
	}

sprintf(qbuf,"delete from borrowbook where number=%d;",i);
mysql_query(&mysql, qbuf);
sprintf(qbuf,"update book set booknownumber=booknownumber+1, bookborrownumber=bookborrownumber-1 where booknumber=%d;",MY.Number);
mysql_query(&mysql, qbuf);
printf("����ɹ���");
}


if(k=='H')
{ int i,j;
printf("����������������");
scanf("%d",&i);
printf("������ͼ����:");
scanf("%d",&j);
sprintf(qbuf,"update borrowbook set duedate=duedate+%d where number=%d;",i,j);
mysql_query(&mysql, qbuf);


printf("����ɹ���");
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
		printf("����֤��=%s, ����=%s,�༶=%s,ѧ��=%s,����=%s,����ʱ��=%s,��������=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

char k;
printf("ѡ�����в�����YΪע����NΪ��ѯ��");
scanf("%s",&k);
if(k=='Y')
{
int i;
printf("������Ҫע����ѧ��");
scanf("%d",&i);

sprintf(qbuf,"delete from reader where number=%d;",i);
mysql_query(&mysql, qbuf);
printf("ע���ɹ���");

}
if(k=='N')
{int i;
printf("������Ҫ���ҵ�ѧ��");
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
		printf("����֤��=%s, ����=%s,�༶=%s,ѧ��=%s,����=%s,����ʱ��=%s,��������=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

}

}
void sum()
{  char k;
printf("��������Ҫ���еĲ�����YΪ�鿴�������а�N�鿴�����˵Ľ�����Ϣ��Z��ʾ�����������ڵ���δ������Ϣ��");
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
			printf("ͼ����=%s, ͼ������=%s,ͼ������=%s,ͼ�������=%s��ͼ���������=%s��ͼ����=%s��ͼ�����=%s��ͼ�����������=%s��ͼ�鵱ǰ����=%s,ͼ�����֤��=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
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
	printf("����֤��=%s, ����=%s,�༶=%s,ѧ��=%s,����=%s,����ʱ��=%s,��������=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}

  }

if(k=='Z')
{ int i;
printf("������ʱ��");
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
		printf("����֤��=%s, ����=%s,�༶=%s,ѧ��=%s,����=%s,��������=%s,����ʱ��=%s\n", row[0], row[1],row[2],row[3],row[4],row[5],row[6]);
	}



}


}
int  meau()
{  int  i;
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| �˵� |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (1)  ¼������Ϣ |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (2)   ���߹���|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (3)  �������Ϲ���|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (4)  ���Ĺ��� |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (5)  ͳ�Ʒ���|\n");
printf("\t\t|----------------------------------------------|\n");
printf("\t\t| (0) �˳�ϵͳ |\n");
printf("\t\t|----------------------------------------------|\n");
printf("\n\t\t��ѡ��(0-5):");
scanf("%d",&i);
return i;
}

void  main()
{ char m;
  do{ int k;
   k=meau();
if(k==1)
    SSM_Init();//�����Ϣ��ʼ��
  if(k==2)
  	reader();
  	if(k==3) //������Ϣ
    SSM_DO();
    if(k==4)
	 borrow_out();
  if(k==5)
	sum();
  if(k==0)
   break;
   printf("�Ƿ���� Y��������N ���˳�)");
   scanf("%s",&m);
  } while(m=='Y');
}