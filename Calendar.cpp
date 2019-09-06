/*
세종고등학교 10101 강희원
'달력 만들기'
2019/08/15~2019/08/19
*/


#include<stdio.h>
#include<Windows.h>
#include<time.h>

#define STRLEN 20

//1년 1월 1일은 월요일 
//일0 월1 화2 수3 목4 금5 토6 

void IniPage();//초기 배경화면 
void START();//선택화면 시작 
void CalendarPage();//달력화면 
void SchedulemakePage();//스케줄 만들기 화면 
void SchedulelistPage();//스케줄 리스트 화면 
void FileExport();//스케줄내보내기 
void FileImport();//스케줄불러오기 

int leap_year(int year);//윤년 판단 함수 
int days_of_month(int year, int month);//달 일 수를 반환하는 함수 
int get_start(int year, int month);//1년1월1일부터의 일 수를 7로 나누어 구하고자 하는 달의 1일 요일을 반환하는 함수 
void draw_calendar(int start, int year, int month);//달력그리기 함수 
int anniversary(int year, int month, int day);//달력을 그릴 때 해당하는 달에 스케줄이 있는지 확인하고 그게 몇번째 원소인지를 다른 배열에 저장하는 함수 
void ScheduleList_sort();//스케줄리스트 정렬 함수 
void arr_interchange(int *arr, int a, int b);//정렬시 두 배열의 두 원소의 숫자들을 바꾸는 함수 
void Title_interchange(int a, int b);//정렬시 두 배열의 두 원소의 문자열(스케줄 제목)을 바꾸는 함수 

int ScheduleList_year[1000]={0, };//스케줄의 년도 저장 
int ScheduleList_month[1000]={0, };//스케줄의 달 저장 
int ScheduleList_day[1000]={0, };//스케줄의 일 저장 
char ScheduleList_Title[1000][STRLEN]={0, };//스케줄의 제목 저장 

int S_cnt=0;//스케줄 개수 
int anniversary_rec[1000]={0, };//달력 그릴 때 ScheduleList_? 의 몇번째 원소가 이번 달에 포함되는 기록한 배열 
int ann_cnt=0;//이번달 스케줄 개수 

const time_t t = time(NULL);
struct tm tm = *localtime(&t);//오늘 날짜 확인용 

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
	printf("                                                  By 10101 강희원\n") ;
	Sleep(500);
	system("pause");
}

void START() {
	int select;
	while(1) {
		system("cls");
		printf("             □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
		printf("             □□□□□□□□□□□□□□Calendar□□□□□□□□□□□□□□\n");
		printf("             □□□□□□□□□□□□□10101 강희원□□□□□□□□□□□□□\n");
		printf("             □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
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
	draw_calendar(get_start(1900+tm.tm_year, 1+tm.tm_mon), 1900+tm.tm_year, 1+tm.tm_mon);//오늘 포함된 달 달력 그리기 
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
		draw_calendar(get_start(year, month), year, month);//입력된 달 달력 그리기 
	}
}

void SchedulemakePage() {
	printf("\nWhich date?(YYYY/MM/DD)\n");
	scanf("%d/%d/%d", &ScheduleList_year[S_cnt], &ScheduleList_month[S_cnt], &ScheduleList_day[S_cnt]);//스케줄 날짜 입력 
	getchar();
	printf("\nSchedule Title?\n");
	scanf("%[^\n]s", ScheduleList_Title[S_cnt]);//스케줄 이름 입력 
	getchar();
	S_cnt++;
	ScheduleList_sort();//스케줄 리스트 정렬 
}

void SchedulelistPage() {
	int i, home;
	
	if(!S_cnt) printf("There is no schedule\n");
	for(i=0;i<S_cnt;i++) {
		printf("[%d] %d/%d/%d : %s\n", i+1, ScheduleList_year[i], ScheduleList_month[i], ScheduleList_day[i], ScheduleList_Title[i]);//스케줄 리스트 출력 
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
	fprintf(file_pointer,"%d\n", S_cnt);//스케줄 개수 출력 
	for(i=0;i<S_cnt;i++) {
		fprintf(file_pointer, "%d/%d/%d : %s\n", ScheduleList_year[i], ScheduleList_month[i], ScheduleList_day[i], ScheduleList_Title[i]);//스케줄 년,달,일,제목 출력 
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
	fscanf(file_pointer, "%d\n", &S_cnt);//스케줄 개수 입력 
	for(i=0;i<S_cnt;i++) {
		fscanf(file_pointer, "%d/%d/%d : %[^\n]s\n", &ScheduleList_year[i], &ScheduleList_month[i], &ScheduleList_day[i], ScheduleList_Title[i]);//스케줄 년/달/일 입력 
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
	int i, interval=0;//interval이 1년1월1일부터의 날짜 차이 
	
	for(i=1;i<year;i++) {
		if(leap_year(i)) interval+=366;
		else interval+=365;
	}
	for(i=1;i<month;i++) {
		interval+=days_of_month(year, i); 
	}
	return (interval+1)%7;//1일의 요일 반환 
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
			if(1900+tm.tm_year==year && 1+tm.tm_mon==month && tm.tm_mday==cnt) {//이번달에 오늘이 표현되어있으면 
				todayis++;
				anniversary(year, month, cnt);//오늘 스케줄 있는지도 체크 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 2);//초록색으로 오늘 달력날짜 색 바꾸기 
				printf(" %2d  ", cnt++); //달력 날짜 출력 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
			}
			else if(anniversary(year, month, cnt)) {//이번달에 스케줄이 있으면 
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 6);//주황색으로 오늘 달력날짜 색 바꾸기 
				printf(" %2d  ", cnt++); //달력 날짜 출력
				SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
			}
			else printf(" %2d  ", cnt++); //달력 날짜 출력
		}
		if((i+1)%7==0 && i!=0 && cnt+start!=i) printf("\n");//달력 끝까지 출력후 개행 
	}
	printf("\n-----------------------------------\n");
	if(todayis) {
		printf("[%d] : Today\n", tm.tm_mday);//오늘 날짜 출력 
		printf("-----------------------------------\n");
	}
	for(i=0;i<ann_cnt;i++) {
		printf("[%d] : %s\n", ScheduleList_day[anniversary_rec[i]], ScheduleList_Title[anniversary_rec[i]]);//스케줄리스트 출력 
	}
}

int anniversary(int year, int month, int day) {
	int i, cnt=0;
	
	for(i=0;i<S_cnt;i++) {
		if(ScheduleList_year[i]==year && ScheduleList_month[i]==month && ScheduleList_day[i]==day) {//주어진 날짜에 스케줄이 있으면 
			anniversary_rec[ann_cnt++]=i;//몇번쨰 스케줄인지 배열에 넣고 
			cnt++;//스케줄 개수 증가 
		}
	}
	if(cnt) return 1;//스케줄이 있으면 1반환 
	return 0;//없으면 0 
}

void ScheduleList_sort() {
	int i=S_cnt-1;
	//가장 최근에 추가한 스케줄만 맨뒤에 있어서 정렬이 안되어 있기 때문에 맨 뒤 스케줄만 앞의 적절한 위치로 이동합니다 
	while(i>=1 && (ScheduleList_year[i]<ScheduleList_year[i-1]) || (ScheduleList_year[i]==ScheduleList_year[i-1] && ScheduleList_month[i]<ScheduleList_month[i-1]) || (ScheduleList_year[i]==ScheduleList_year[i-1] && ScheduleList_month[i]==ScheduleList_month[i-1] && ScheduleList_day[i]<ScheduleList_day[i-1] )) {
		arr_interchange(ScheduleList_year, i, i-1);
		arr_interchange(ScheduleList_month, i, i-1);
		arr_interchange(ScheduleList_day, i, i-1);
		Title_interchange(i, i-1);
		i--;
	}
}

void arr_interchange(int *arr, int a, int b) {//두배열의 특정한 원소 서로 바꾸기 
	int temp;
	temp=arr[a];
	arr[a]=arr[b];
	arr[b]=temp;
}
void Title_interchange(int a, int b) {//두 배열의 문자열 서로 바꾸기 
	char temp[STRLEN];
	strcpy(temp, ScheduleList_Title[a]);
	strcpy(ScheduleList_Title[a], ScheduleList_Title[b]);
	strcpy(ScheduleList_Title[b], temp);	
}

