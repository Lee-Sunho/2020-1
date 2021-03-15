#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
typedef struct{
	char name[20];
	char address[100];
	char phone[20];
} member;
//함수 원형을 사용해 뒤에 나올 함수들의 인자목록을 알려줌 
void menu();
void printall(member *parr,int num);
void enroll(member *parr,int *pnum);
void search(member *parr,int num);
void revise(member *parr, int num);
void del(member*parr,int *pnum);
void loadfile(member*parr,int*pnum);
void storefile(member*parr,int num);

int main(void)
{
	int func;
	member perarr[100];//구조체 배열 
	int pernum=0;//회원 수 
	
	loadfile(perarr,&pernum);//스플럭 명단관리.txt를 읽는다. 
	menu();//메뉴 함수 실행 
	while(1){
		printf("선택할 기능을 입력하세요: ");
		scanf("%d",&func);
		getchar();
		printf("=============================\n");
			
		switch (func)
		{
		case 1:
			printall(perarr,pernum);
			break;
		case 2:
			enroll(perarr,&pernum);
			break;
		
		case 3:
			search(perarr,pernum);
			break;
		
		case 4:
			revise(perarr,pernum);
			break;
		
		case 5:
			del(perarr,&pernum);
			break;
		case 6:
			storefile(perarr,pernum);
			printf("프로그램을 종료합니다.\n");
			exit(0);
		default:
			printf("잘못된 입력입니다.\n");
			printf("=============================\n");
			break;
		}
	}
 } 

void menu()//메뉴를 출력하는 함수 
{
	printf("\n                     ==메뉴==                       ");
	printf("\n1. 모든 주소록 정보 출력\n");
	printf("2. 회원 등록\n");
	printf("3. 회원 정보 검색\n");
	printf("4. 회원 정보 수정\n");
	printf("5. 회원 삭제\n");
	printf("6. 프로그램 종료\n");
	printf("\n");
	printf("\n");
	printf("=============================\n");

}

void printall(member *parr,int num)//회원 목록을 전체 출력하는 함수 
{
	int i;
	for(i=0;i<num;i++)
	{
	char name[20];//이름 순 정렬을 할 때 잠시 이름을 저장할 배열 
	char address[100];//이름 순 정렬을 할 때 잠시 주소를 저장할 배열  
	char phone[100];//이름 순 정렬을 할 때 잠시 전화번호를 저장할 배열 
	for(int k=0;k<num;k++)//이름 순 정렬 
		for(int j=num-1;j>k;j--){
			if(strcmp(parr[j-1].name,parr[j].name)>0){
				strcpy(name,parr[j-1].name);
				strcpy(parr[j-1].name,parr[j].name);
				strcpy(parr[j].name,name);
				strcpy(address,parr[j-1].address);
				strcpy(parr[j-1].address,parr[j].address);
				strcpy(parr[j].address,address);
				strcpy(phone,parr[j-1].phone);
				strcpy(parr[j-1].phone,parr[j].phone);
				strcpy(parr[j].phone,phone);
			}
		}
		printf("#%d\n",i+1);
		printf("이름:%s\n",parr[i].name);
		printf("주소:%s\n",parr[i].address);
		printf("전화번호:%s\n",parr[i].phone);
		printf("=============================\n");
	}
}

void enroll(member *parr,int *pnum)//회원 등록 함수 
{
	member *p;
	p=(member*)malloc(sizeof(member));//동적 메모리 할당 
	if(p==NULL)
	{
		printf("동적메모리 할당에 실패했습니다.\n");
		exit(1);
	}
	printf("이름:");
	scanf("%[^\n]s",p->name);//scanf로 공백을 포함해서 입력받기 위해 [^\n]사용 
	getchar();
	strcpy(parr[*pnum].name,p->name);//입력받은 이름을 배열에 저장 
	printf("주소:");
	scanf("%[^\n]s",p->address);
	getchar();
	strcpy(parr[*pnum].address,p->address);//입력받은 주소를 배열에 저장 
	printf("전화번호:");
	scanf("%[^\n]s",p->phone);
	getchar(); 
	strcpy(parr[*pnum].phone,p->phone);//입력받은 전화번호를 배열에 저장 
	(*pnum)++;//등록된 회원 수를 1 증가시킨다 
	free(p);
	printf("추가되었습니다.\n");
	printf("=============================\n");
}

void search(member *parr,int num)//회원을 검색하는 함수 
{
	int found=0;//등록된 회원이 있는지 판별하는 변수 
	char info[100];//입력받은 정보를 잠시 저장할 배열 
	printf("찾으실 회원의 이름이나 주소 혹은 전화번호를 입력하세요:");
	scanf("%[^\n]s",info);
	getchar();
	for(int i=0;i<num;i++)
	{
		char *name=strstr(parr[i].name,info);//문자열 탐색 함수 strstr사용:info의 문자열이 parr[i].name에 있으면 해당위치의 포인터반환, 없으면 NULL포인터 반환	
		if(name!=NULL){//strstr이 반환한 포인터가 NULL이 아닐 시 , 즉 info와 일치하는 문자열이 있을 시 해당 회원의 정보 출력  
			printf("이름:%s\n",parr[i].name);
			printf("주소:%s\n",parr[i].address);
			printf("전화번호:%s\n",parr[i].phone);
			found++;//회원을 찾았음을 나타냄 
			printf("=============================\n");
		}
		else{
			char *address=strstr(parr[i].address,info);
			if(address!=NULL){
				printf("이름:%s\n",parr[i].name);
				printf("주소:%s\n",parr[i].address);
				printf("전화번호:%s\n",parr[i].phone);
				found++;
				printf("=============================\n");
			}
			else{
				char *phone=strstr(parr[i].phone,info);
				if(phone!=NULL){
					printf("이름:%s\n",parr[i].name);
				printf("주소:%s\n",parr[i].address);
				printf("전화번호:%s\n",parr[i].phone);
				found++; 
				printf("=============================\n");
				}
			}
		}	
	}
	if(found==0){//해당 정보와 일치하는 회원이 없을 시 
		printf("회원이 존재하지 않습니다.\n");
		printf("=============================\n");
	}
}

void revise(member *parr, int num)//회원 정보를 수정하는 함수 
{
	int found=0;//등록된 회원이 있는지 판별하는 변수 
	char namebefore[20];//수정할 회원의 이름을 입력받아 저장하는 배열 
	char nameafter[20];//수정 후의 이름을 저장하는 배열 
	char addressafter[100];//수정 후의 주소를 저장하는 배열 
	char phoneafter[100];//수정 후의 전화번호를 저장하는 배열 
	char save;//저장 여부를 판별하는 변수 
	printf("수정할 회원의 이름을 입력하세요: ");
	scanf("%[^\n]s",namebefore);
	getchar();
	for(int i=0;i<num;i++)
	{
		if(strcmp(parr[i].name,namebefore)==0)//수정할 회원을 찾은 경우 정보를 재입력받는다 
		{
			printf("이름:");
			scanf("%[^\n]s",nameafter);
			getchar();
			printf("주소:");
			scanf("%[^\n]s",addressafter);
			getchar();
			printf("전화번호:");
			scanf("%[^\n]s",phoneafter);
			getchar();
			
			found++;//회원을 찾았음을 나타냄 
			printf("저장하시겠습니까?(Y/N)");
			scanf("%c",&save);
			if(save=='Y'||save=='y'){
				strcpy(parr[i].name,nameafter);
				strcpy(parr[i].address,addressafter);
				strcpy(parr[i].phone,phoneafter);
				printf("정보가 수정되었습니다.\n");
				printf("=============================\n");
			}
			else if(save=='N'||save=='n'){
				printf("취소되었습니다.\n");
				printf("=============================\n");
				break;
			}
			else{
				printf("잘못된 입력입니다.\n");
				printf("=============================\n");
				break;
			}
				
				
		}
	 } 
	 if(found==0){//해당 정보와 일치하는 회원이 없을 시 
	 	printf("회원이 존재하지 않습니다.\n");
	 	printf("=============================\n");
	 }
}

void del(member*parr,int *pnum)//회원을 삭제하는 함수 
{
	int found=0;//등록된 회원이 있는지 판별하는 변수 
	char name[20];//삭제할 회원의 이름을 입력받아 저장하는 배열
	printf("삭제할 회원의 이름을 입력하세요: ");
	scanf("%[^\n]s",name);
	for(int i=0;i<*pnum;i++)
	{
		if(strcmp(parr[i].name,name)==0)
		{
			for(int j=i+1;j<*pnum;j++)//회원을 삭제하면서 빈 배열을 없애기 위해 다시 정렬한다 
			{
				strcpy(parr[j-1].name,parr[j].name);
				strcpy(parr[j-1].address,parr[j].address);
				strcpy(parr[j-1].phone,parr[j].phone);
			}
			found++;//회원을 찾았음을 나타냄 
			(*pnum)--;//등록된 회원 수를 1 감소시킨다 
			printf("삭제가 완료되었습니다.\n");
			printf("=============================\n");
		}
	}
	if(found==0){//해당 정보와 일치하는 회원이 없을 시 
		printf("회원이 존재하지 않습니다.\n");
		printf("=============================\n");
	}
}

void loadfile(member*parr,int*pnum)
{
	FILE *fp=fopen("스플럭 명단관리.txt","rt");//텍스트를 읽기전용으로 연다. 
	if(fp==NULL)//파일 개방 예외처리 
	{
		return;
	}
	while(1)
	{
		char ch[100];//파일을 읽을 때 사용할 임시 배열 
		fgets(ch,sizeof(ch),fp);//파일을 한줄 읽어 ch에 저장 
		ch[strlen(ch) - 1] = '\0';//fgets함수의 개행문자 제거 
		strcpy(parr[*pnum].name,ch); //ch의 내용을 구조체 배열에 저장 
		fgets(ch,sizeof(ch),fp);
		ch[strlen(ch) - 1] = '\0';
		strcpy(parr[*pnum].address,ch); 
		fgets(ch,sizeof(ch),fp);
		ch[strlen(ch) - 1] = '\0';
		strcpy(parr[*pnum].phone,ch); 

		if(feof(fp)!=0)//파일의 끝에 도달 시 0이 아닌 값을 리턴한다. 파일 끝에 도달하면 종료한다. 
			break;
		(*pnum)++;//회원 수 증가 
	}
	fclose(fp);
}

void storefile(member*parr,int num)
{
	FILE*fp=fopen("스플럭 명단관리.txt","wt");//텍스트를 쓰기전용으로 연다. 
	if(fp==NULL) //파일 개방 예외처리 
	{
		printf("file open error!\n");
		return;
	}
	char name[20];//이름 순 정렬을 할 때 잠시 이름을 저장할 배열 
	char address[100];//이름 순 정렬을 할 때 잠시 주소를 저장할 배열  
	char phone[100];//이름 순 정렬을 할 때 잠시 전화번호를 저장할 배열
	for(int i=0;i<num;i++)//이름 순 배열 
		for(int j=num-1;j>i;j--){
			if(strcmp(parr[j-1].name,parr[j].name)>0){
				strcpy(name,parr[j-1].name);
				strcpy(parr[j-1].name,parr[j].name);
				strcpy(parr[j].name,name);
				strcpy(address,parr[j-1].address);
				strcpy(parr[j-1].address,parr[j].address);
				strcpy(parr[j].address,address);
				strcpy(phone,parr[j-1].phone);
				strcpy(parr[j-1].phone,parr[j].phone);
				strcpy(parr[j].phone,phone);
			}
		}
	for(int i=0;i<num;i++)//파일에 저장 
		fprintf(fp,"%s\n%s\n%s\n",parr[i].name,parr[i].address,parr[i].phone);
	fclose(fp);
}
