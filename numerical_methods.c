#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define malloc_f(p,n,type)\
	p=(type *)malloc(sizeof(type));\
	if(p==NULL)\
	{\
	printf("Insufficient Memory\n");\
	exit(0);\
	}
#define COMPARE(x,y)((x==y)?0:(x>y)?1:-1)
FILE *fp;

struct node{
	long double coeff;
	int expon;
	struct node *link;
};
typedef struct node *NODE;

void display(NODE head)
{
	NODE temp;
	if(head->link==head)
	{
		printf("List empty,Polynomial does not exist\n");
		exit(0);
	}
	temp=head->link;
	while(temp!=head)
	{
		if(temp->coeff<0){
			printf("%.2Lfx^%d",temp->coeff,temp->expon);
			fprintf(fp,"%.2Lfx^%d",temp->coeff,temp->expon);}
		else{
			printf("+%.2Lfx^%d",temp->coeff,temp->expon);
			fprintf(fp,"+%.2Lfx^%d",temp->coeff,temp->expon);}
		temp=temp->link;
	}
	printf("\n");
	fprintf(fp,"\n");
}

NODE attach(int coeff,int expon,NODE head)
{
	NODE temp,cur;
	malloc_f(temp,1,struct node);
	temp->coeff=coeff;
	temp->expon=expon;
	cur=head->link;
	while(cur->link!=head)
	{
		cur=cur->link;
	}
	cur->link=temp;
	temp->link=head;
	return head;
}

NODE read_poly(NODE head)
{
	int i=1,coeff,expon;
	printf("Enter the coefficients and -999 to end\n");
	while(1)
	{
		printf("Enter the %d term\n",i++);
		printf("Coeff= ");
		scanf("%d",&coeff);
		if(coeff==-999)break;
		printf("Pow x = ");
		scanf("%d",&expon);
		head=attach(coeff,expon,head);
	}
	return head;
}

double f(double n,NODE head)
{
	double sum=0;
	NODE cur;
	cur=head->link;
	while(cur!=head)
	{
		sum=sum+(cur->coeff*pow(n,cur->expon));
		cur=cur->link;
	}
	return sum;
}

NODE diff(NODE head1,NODE head2)
{
	NODE cur;
	double coef,exp;
	cur=head1->link;
	while(cur!=head1)
	{
		coef=cur->coeff*cur->expon;
		exp=cur->expon-1;
		if(coef!=0)
			head2=attach(coef,exp,head2);
		cur=cur->link;
	}
	return head2;
}

int main()
{
	fp = fopen("log.txt", "w+");
	NODE head1,head2;
	long double temp1,temp2,temp3,tempf,tempdiff,a,b,x=0,x1=0;
	int iter,i,j,flag,method,m=1;
	malloc_f(head1,1,struct node);
	malloc_f(head2,1,struct node);
	head1->link=head1;
	head2->link=head2;
	printf("Enter the polynomial\n");
	read_poly(head1);
	printf("The entered polynomial is\n");
	fprintf(fp,"The entered polynomial is\n");
	display(head1);
	printf("Enter [1] to perform regula-falsi method\n      [2] to perform Newton's ralphson's method..");
	scanf("%d",&method);
	if(method==1)goto begin1;
	if(method==2)goto begin2;

	begin1:
	printf("Enter the interval[a,b] ");
	scanf("%Lf%Lf",&a,&b);
	printf("The entered interval is [ %Lf , %Lf ]\n",a,b);
	fprintf(fp,"The entered interval is [ %Lf , %Lf ]\n",a,b);
	begin:
	printf("Enter the number of iterations you want to perform: ");
	scanf("%d",&iter);
	for(i=0;i<iter;i++)
	{
		temp1=f(a,head1);
		temp2=f(b,head1);
		x=((a*temp2)-(b*temp1))/(temp2-temp1);
		temp3=f(x,head1);
		if(temp1>0&&temp3<0){b=x;}
		if(temp1<0&&temp3>0){b=x;}
		if(temp2>0&&temp3<0){a=x;}
		if(temp2<0&&temp3>0){a=x;}
		for(j=0;j<4.4*pow(10,7);j++){}
		printf("Iteration %d\t\t X=%Lf\n",m++,x);
		fprintf(fp,"Iteration %d\t\t X=%Lf\n",m,x);
	}
	printf("Answer: %Lf\n",x);
	printf("Do you want to perform more iterations?[1=yes/0=no].... ");
	scanf("%d",&flag);
	if(flag)goto begin;
	fprintf(fp,"Answer: %Lf\n",x);
	exit(0);
	begin2:
	head2=diff(head1,head2);
	printf("Enter the initial assumption to the root Xo = ");
	fprintf(fp,"Enter the initial assumption to the root Xo = ");
	scanf("%Lf",&x);
	begin3:
	printf("Enter the number of iterations you want to perform: ");
	scanf("%d",&iter);
	for(i=0;i<iter;i++)
	{
		tempf=f(x,head1);
		tempdiff=f(x,head2);
		x1=x-(tempf/tempdiff);
		x=x1;
		for(j=0;j<4.4*pow(10,7);j++){}
		printf("Iteration %d\t\t X=%Lf\n",m++,x);
		fprintf(fp,"Iteration %d\t\t X=%Lf\n",m,x);
	}
	printf("Answer: %Lf\n",x);
	printf("Do you want to perform more iterations?[1=yes/0=no].... ");
	scanf("%d",&flag);
	if(flag)goto begin3;
	fprintf(fp,"Answer: %Lf\n",x);
	return 0;
}
