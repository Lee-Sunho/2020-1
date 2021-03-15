#include <stdio.h>
#include <string.h>
int main(void)
{
	int lotto[5][6]={{1,2,3,4,5,6},{10,15,25,35,40,42},{1,9,11,22,23,25},{9,28,31,34,35,36},{1,9,23,28,33,35}};
	int thisweek[6];
	int bonus;
	char grade[5][10];
	int bonuspoint=0;
	int i,j,k,a,sum;
	printf("금주의 로또 번호를 입력하세요-> ");
	for(i=0;i<6;i++)
		scanf("%d",&thisweek[i]);
	printf("보너스 번호를 입력하세요-> ");
	scanf("%d",&bonus);
	for(i=0;i<5;i++){
		sum=0;
        for(j=0;j<6;j++){
			for(k=0;k<6;k++){
				if(lotto[i][j]==thisweek[k]){
					sum++;
				}
				else if(lotto[i][j]==bonus){
					bonuspoint=1;
				}
			}
		}
    	if(sum<3)
            strcpy(grade[i],"꽝");
		else if(sum==3)
            strcpy(grade[i],"5등");
        else if(sum==4)
            strcpy(grade[i],"4등");
        else if(sum==5 && bonuspoint==0)
            strcpy(grade[i],"3등");
        else if(sum==5 && bonuspoint==1)
            strcpy(grade[i],"2등");
        else if(sum==6)
            strcpy(grade[i],"1등");
	}
    printf("홍길동님의 로또 당첨 결과는 다음과 같습니다.\n");
	for(i=0;i<5;i++){
		printf("%d세트 번호<",i+1);
		for(j=0;j<6;j++)
			printf("%-3d",lotto[i][j]);
		printf("> ->");
		for(j=0;j<6;j++){
			int a;
			for(k=0;k<6;k++){
				if(lotto[i][j]!=thisweek[k]){
					a=0;
					if(lotto[i][j]==bonus){
						a=1;
						break;
					}
				}
				else if(lotto[i][j]==thisweek[k]){
					a=2;
					break;
				}
			}
			if(a==2)
				printf("%-3d",lotto[i][j]);
			else if(a==1 && strcmp(grade[i],"2등")==0)
				printf("%-3d",lotto[i][j]);
			else 
				printf("%-3c",'X');
		}
		printf("<%s>",grade[i]);
		printf("\n");
	}
}
	

