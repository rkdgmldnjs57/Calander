/*
��������б� 10101 �����
'�޷� �����'
2019/08/15~2019/08/19
*/


#include<stdio.h>
#include<Windows.h>
#include<time.h>

#define STRLEN 20

//1�� 1�� 1���� ������ 
//��0 ��1 ȭ2 ��3 ��4 ��5 ��6 

void IniPage();//�ʱ� ���ȭ�� 
void START();//����ȭ�� ���� 
void CalendarPage();//�޷�ȭ�� 
void SchedulemakePage();//������ ����� ȭ�� 
void SchedulelistPage();//������ ����Ʈ ȭ�� 
void FileExport();//�����ٳ������� 
void FileImport();//�����ٺҷ����� 

int leap_year(int year);//���� �Ǵ� �Լ� 
int days_of_month(int year, int month);//�� �� ���� ��ȯ�ϴ� �Լ� 
int get_start(int year, int month);//1��1��1�Ϻ����� �� ���� 7�� ������ ���ϰ��� �ϴ� ���� 1�� ������ ��ȯ�ϴ� �Լ� 
void draw_calendar(int start, int year, int month);//�޷±׸��� �Լ� 
int anniversary(int year, int month, int day);//�޷��� �׸� �� �ش��ϴ� �޿� �������� �ִ��� Ȯ���ϰ� �װ� ���° ���������� �ٸ� �迭�� �����ϴ� �Լ� 
void ScheduleList_sort();//�����ٸ���Ʈ ���� �Լ� 
void arr_interchange(int *arr, int a, int b);//���Ľ� �� �迭�� �� ������ ���ڵ��� �ٲٴ� �Լ� 
void Title_interchange(int a, int b);//���Ľ� �� �迭�� �� ������ ���ڿ�(������ ����)�� �ٲٴ� �Լ� 

int ScheduleList_year[1000]={0, };//�������� �⵵ ���� 
int ScheduleList_month[1000]={0, };//�������� �� ���� 
int ScheduleList_day[1000]={0, };//�������� �� ���� 
char ScheduleList_Title[1000][STRLEN]={0, };//�������� ���� ���� 

int S_cnt=0;//������ ���� 
int anniversary_rec[1000]={0, };//�޷� �׸� �� ScheduleList_? �� ���° ���Ұ� �̹� �޿� ���ԵǴ� ����� �迭 
int ann_cnt=0;//�̹��� ������ ���� 

const time_t t = time(NULL);
struct tm tm = *localtime(&t);//���� ��¥ Ȯ�ο� 

int main() {
	IniPage();
	START();
	return 0;
}

void IniPage() {
	printf(" .o88b.  .d8b.  db      d88888b d8b   db d8888b.  .d8b.  d8888b. \n");
	printf("d8P  Y8 d8' `8b 88      88'     888o  88 88  `8D d8' `8b 88  `8D \n");
	printf("8P      88ooo88 88      88ooooo 88V8o 88 88   88 88ooo88 88oobY' \n");
	printf("8b      88   88 88      88~~~~~ 88 V8o88 88   88 88   88 88`8b   \n");
	printf("Y8b  d8 88   88 88booo. 88.     88  V888 88  .8D 88   88 88 `88. \n");
	printf(" `Y88P' YP   YP Y88888P Y88888P VP   V8P Y8888D' YP   YP 88   YD \n");
	printf("                                                  By 10101 �����\n") ;
	Sleep(500);
	system("pause");
}

void START() {
	int select;
	while(1) {
		system("cls");
		printf("             ���������������������������������\n");
		printf("             ���������������Calendar���������������\n");
		printf("             ��������������10101 �������������������\n");
		printf("             ���������������������������������\n");
		printf("1.Calendar || 2.Make a new Schedule || 3.Schedule List || 4.Export || 5. Import || 0. Exit\n"); 
		scanf("%d", &select);
		switch(select) {
			case 1 : 
				CalendarPage();
				break;
			case 2 : 
				SchedulemakePage();
				break;
			case 3 : 
				SchedulelistPage();
				break;
			case 4 : 
				FileExport();
				break;
			case 5: 
				FileImport();
				break;
			case 0 : 
				return ;
			default : 
				break;
		}
	}
}

void CalendarPage() {
	int year, month;
	draw_calendar(get_start(1900+tm.tm_year, 1+tm.tm_mon), 1900+tm.tm_year, 1+tm.tm_mon);//���� ���Ե� �� �޷� �׸��� 
	while(1) {
		printf("\nYear & Month : YYYY/DD   (Home:0/0)\n");
		scanf("%d/%d", &year, &month);
		getchar();
		if(year==0&&month==0) break;
		if(year<1||month<1||month>12) { 
			printf("\nError\n\n"); 
			Sleep(1000);
			continue;
		}
		draw_calendar(get_start(year, month), year, month);//�Էµ� �� �޷� �׸��� 
	}
}

void SchedulemakePage() {
	printf("\nWhich date?(YYYY/MM/DD)\n");
	scanf("%d/%d/%d", &ScheduleList_year[S_cnt], &ScheduleList_month[S_cnt], &ScheduleList_day[S_cnt]);//������ ��¥ �Է� 
	getchar();
	printf("\nSchedule Title?\n");
	scanf("%[^\n]s", ScheduleList_Title[S_cnt]);//������ �̸� �Է� 
	getchar();
	S_cnt++;
	ScheduleList_sort();//������ ����Ʈ ���� 
}

void SchedulelistPage() {
	int i, home;
	
	if(!S_cnt) printf("There is no schedule\n");
	for(i=0;i<S_cnt;i++) {
		printf("[%d] %d/%d/%d : %s\n", i+1, ScheduleList_year[i], ScheduleList_month[i], ScheduleList_day[i], ScheduleList_Title[i]);//������ ����Ʈ ��� 
	}
	printf("\nHome : ENTER\n");
	scanf("%c", &home);
	getchar();
	if (!home==' ') ;  
}

void FileExport() {
	int i;
	FILE *file_pointer;
	file_pointer=fopen("schudule.txt", "wt");
	if(file_pointer==NULL) {
		printf("Error");
		Sleep(1000);
		return ;
	}
	fprintf(file_pointer,"%d\n", S_cnt);//������ ���� ��� 
	for(i=0;i<S_cnt;i++) {
		fprintf(file_pointer, "%d/%d/%d : %s\n", ScheduleList_year[i], ScheduleList_month[i], ScheduleList_day[i], ScheduleList_Title[i]);//������ ��,��,��,���� ��� 
	}
	fclose(file_pointer);
	printf("Schedule File is successfully exported.");
	Sleep(1000);
}

void FileImport() {
	int i;
	FILE *file_pointer;
	file_pointer=fopen("schudule.txt", "rt");
	if(file_pointer==NULL) {
		printf("Error");
		Sleep(1000);
		return ;
	}
	fscanf(file_pointer, "%d\n", &S_cnt);//������ ���� �Է� 
	for(i=0;i<S_cnt;i++) {
		fscanf(file_pointer, "%d/%d/%d : %[^\n]s\n", &ScheduleList_year[i], &ScheduleList_month[i], &ScheduleList_day[i], ScheduleList_Title[i]);//������ ��/��/�� �Է� 
	}
	fclose(file_pointer);
	printf("Schedule File is successfully imported.");
	Sleep(1000);
}


int leap_year(int year) {
	if ((year%4==0 && year%100!=0)||year%400==0) {
		return 1;
	}
	return 0;
}

int days_of_month(int year, int month) {
	int arr[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	
	if(leap_year(year)==1 && month==2) return 29;
	else return arr[month-1];
}

int get_start(int year, int month) {  
	int i, interval=0;//interval�� 1��1��1�Ϻ����� ��¥ ���� 
	
	for(i=1;i<year;i++) {
		if(leap_year(i)) interval+=366;
		else interval+=365;
	}
	for(i=1;i<month;i++) {
		interval+=days_of_month(year, i); 
	}
	return (interval+1)%7;//1���� ���� ��ȯ 
}

void draw_calendar(int start, int year, int month) {
	int i, cnt=1, todayis=0;
	ann_cnt=0;
	
	for(i=0;i<1000;i++) anniversary_rec[i]=0;
	system("cls");
	printf("<<<<----------%4d/%2d---------->>>>\n", year, month);
	printf(" Sun  Mon  Tue  Wed  Thu  Fri  Sat \n");
	for(i=0;cnt<=days_of_month(year, month); i++) {
		if(i<start) printf("     "); 
		else if(i>=start) {
			if(1900+tm.tm_year==year && 1+tm.tm_mon==month && tm.tm_mday==cnt) {//�̹��޿� ������ ǥ���Ǿ������� 
				todayis++;
				anniversary(year, month, cnt);//���� ������ �ִ����� üũ 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 2);//�ʷϻ����� ���� �޷³�¥ �� �ٲٱ� 
				printf(" %2d  ", cnt++); //�޷� ��¥ ��� 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
			}
			else if(anniversary(year, month, cnt)) {//�̹��޿� �������� ������ 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 6);//��Ȳ������ ���� �޷³�¥ �� �ٲٱ� 
				printf(" %2d  ", cnt++); //�޷� ��¥ ���
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
			}
			else printf(" %2d  ", cnt++); //�޷� ��¥ ���
		}
		if((i+1)%7==0 && i!=0 && cnt+start!=i) printf("\n");//�޷� ������ ����� ���� 
	}
	printf("\n-----------------------------------\n");
	if(todayis) {
		printf("[%d] : Today\n", tm.tm_mday);//���� ��¥ ��� 
		printf("-----------------------------------\n");
	}
	for(i=0;i<ann_cnt;i++) {
		printf("[%d] : %s\n", ScheduleList_day[anniversary_rec[i]], ScheduleList_Title[anniversary_rec[i]]);//�����ٸ���Ʈ ��� 
	}
}

int anniversary(int year, int month, int day) {
	int i, cnt=0;
	
	for(i=0;i<S_cnt;i++) {
		if(ScheduleList_year[i]==year && ScheduleList_month[i]==month && ScheduleList_day[i]==day) {//�־��� ��¥�� �������� ������ 
			anniversary_rec[ann_cnt++]=i;//����� ���������� �迭�� �ְ� 
			cnt++;//������ ���� ���� 
		}
	}
	if(cnt) return 1;//�������� ������ 1��ȯ 
	return 0;//������ 0 
}

void ScheduleList_sort() {
	int i=S_cnt-1;
	//���� �ֱٿ� �߰��� �����ٸ� �ǵڿ� �־ ������ �ȵǾ� �ֱ� ������ �� �� �����ٸ� ���� ������ ��ġ�� �̵��մϴ� 
	while(i>=1 && (ScheduleList_year[i]<ScheduleList_year[i-1]) || (ScheduleList_year[i]==ScheduleList_year[i-1] && ScheduleList_month[i]<ScheduleList_month[i-1]) || (ScheduleList_year[i]==ScheduleList_year[i-1] && ScheduleList_month[i]==ScheduleList_month[i-1] && ScheduleList_day[i]<ScheduleList_day[i-1] )) {
		arr_interchange(ScheduleList_year, i, i-1);
		arr_interchange(ScheduleList_month, i, i-1);
		arr_interchange(ScheduleList_day, i, i-1);
		Title_interchange(i, i-1);
		i--;
	}
}

void arr_interchange(int *arr, int a, int b) {//�ι迭�� Ư���� ���� ���� �ٲٱ� 
	int temp;
	temp=arr[a];
	arr[a]=arr[b];
	arr[b]=temp;
}
void Title_interchange(int a, int b) {//�� �迭�� ���ڿ� ���� �ٲٱ� 
	char temp[STRLEN];
	strcpy(temp, ScheduleList_Title[a]);
	strcpy(ScheduleList_Title[a], ScheduleList_Title[b]);
	strcpy(ScheduleList_Title[b], temp);	
}

