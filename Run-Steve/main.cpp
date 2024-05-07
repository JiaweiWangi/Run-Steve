#include<cstdio>
#include<graphics.h>
#include<conio.h>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#define WIDTH 540
#define HEIGHT 920
FILE* dataFile; // �����û����ݵ��ļ�
ExMessage msg;
clock_t fpsMenu = 1000 / 165; // ��ҳÿһ֡��ʱ��
clock_t fpsGame = 1000 / 60;  // ��Ϸҳ��ÿһ֡��ʱ��

//Ĭ��SETTINGS��ֵ
const int AWARDPOINS = 100; // ��������
const int HEARTCNT = 5; //������

// SETTINGS ��ʱ������ �������Ի���� ���Ѷ�����ͬʱ������������
int award = AWARDPOINS; // ����������׼
int heartCnt = HEARTCNT; //������
double goldRate = 0.001; //������ɸ���/ÿ��ÿ֡
double arrowRate = 0.001; //�����ɸ���/ÿ��ÿ֡
double zombieRate = 0.001; //��ʬ���ɸ���/ÿ��ÿ֡
double goldAppleRate = 0.0003; //�޵м��ٵ��ߣ���ƻ�������ɸ���/ÿ��ÿ֡
double heartRate = 0.0003; //��Ѫ�������ɸ���/ÿ��ÿ֡

// �����ȶ�֡��
int startTime; // ĳһ֡�Ŀ�ʼʱ��
int freamTime; // ����ĳһ֡�����ѵ�ʱ��

int menuStatus; //0Ϊ��ʼҳ�� 1Ϊ��¼ҳ�� 2Ϊע��ҳ��
int logORegStatus; //0Ϊ��ʼ 1Ϊ�����˺�״̬ 2Ϊ��������״̬ 3Ϊ�������״̬
int userStatus; //0Ϊδ��¼ 1Ϊ��¼�ɹ� 2Ϊ��¼ʧ�� 3Ϊע��ɹ�

int steveModle = 2; // steve��ǰ�����Ĺ�� 1 2 3����������)
int jumpFlag = 0; // 1 jumping;
int attackFlag = 0; // 1 attacking
int invincibleFlag = 0; // �Ƿ����޵�״̬
int invincibleStartTime; // �޵�ʱ��

int zombieImgCnt = 0; // ��ǰ���Ž�ʬ�ĵ�x֡
const int zombieNum = 14; // ��ʬ����֡��

int hurtStatus=0;
int awardGoldStatus=0;
int awardZombieStatue=0;
char Points[128];

// ��Ϸ������Ʒ��������֡ͼƬ
// ����loadimage����ͼƬЧ�ʹ���
// ���ڲ��Ŷ���ʱ���� �����ɿ���
// �ʶ��Ȱ��������غ�
// ���ڴ滻ʱ�� ʵ��ռ���ڴ治��
// ������ ��ȫ�ֱ��������� 
IMAGE frameWiseGold[120];
IMAGE frameWiseGold1[120];
IMAGE frameWiseArrow[120];
IMAGE frameWiseArrow1[120];
IMAGE frameWiseZombie[120];
IMAGE frameWiseZombie1[120];
IMAGE frameWiseGoldApple[120];
IMAGE frameWiseGoldApple1[120];
IMAGE frameWiseHeart[120];
IMAGE frameWiseHeart1[120];


struct imageLocate
{
	int x;
	int y;
	imageLocate(int x, int y) : x(x), y(y) {}
};  // ���ڴ��澲̬������Ҫ�Ŵ�ģ�ͼ������

struct item
{
	int x;
	int y;
	int speed;
	int modle; //Ϊ�����ڵڼ��� 1 2 3
	item* next;
}; //��������������Ϸ������

struct newUser
{
	char name[21];
	char password[21];
	int score; //��ʷ��߷�
	int points; //��ǰ����
	newUser* next; 
	newUser() : name("\0"),password("\0"),score(0),points(0),next(NULL) {}
}; // �����������û���Ϣ

newUser* head=NULL; // �����û���Ϣ������
newUser* user; // ��ǰ��¼���û�

// ��ǰ������������ʼ��
int goldCnt = 0;
int arrowCnt = 0;
int zombieCnt = 0;
int goldAppleCnt = 0;
int heartItemCnt = 0;

// ��ʼ������������
item* itemGold = NULL;
item* itemArrow = NULL;
item* itemZombie = NULL;
item* itemGoldApple = NULL;
item* itemHeart = NULL;

void menuPage(); // ������ѭ��
bool imageButtonDetect(imageLocate& locate, IMAGE& image); // ��������λ���Ƿ���ĳ��ͼ����
void loginAndRegisterPage(IMAGE& page);  // ��¼��ע��ҳ��
newUser* readUserInfo(); // �������û��浵��Ϣ��ȡ������
void updateUserFile(); // ����Ϸ�ɼ���Ϣ�洢������
bool cheackUser(); // ��¼ʱ���������˻��뱾�ش洢���˻��Ƿ�һ��
void headText(); // ��������ʾ��¼״̬
void gamePage(); // ��Ϸ����ѭ��
void steveMove(imageLocate& steveLocate); // ʷ�ٷ��ƶ�/����״̬���
void steveJump(imageLocate& steveLocate); // ʷ�ٷ���Ծ���
void creatAllItem(); // ����������Ĵ���
void updateAllItem(); // ����������ĸ���
item* createItem(item*,int,int&); // ��������������
item* itemUpdate(item* itemGold,int& cnt,int category); // �������������� ������putimage
void heartUpdate(IMAGE heart[2], int heartCnt); // ���Ѫ������
void pointsUpdate(); // ��ҷ�������
void drawRanking(); // ��Ϸ���а����


int main()
{
	initgraph(WIDTH, HEIGHT);
	while (true)
	{
		menuPage();
		gamePage();
	}
}

void menuPage()
{
	//�û���Ϣ��ʼ��
	user = (newUser*)malloc(sizeof(newUser));
	user->name[0] = '\0';
	user->password[0] = '\0';
	user->points = 0;
	head = readUserInfo();

	//״̬��ʼ��
	menuStatus = 0; 
	logORegStatus = 0; 
	userStatus = 0; 
	steveModle = 2;
	jumpFlag = 0;
	attackFlag = 0;
	invincibleFlag = 0;

	//�涨һЩ��̬ͼƬ��λ��
	imageLocate runSteveLovate(12, 100);
	imageLocate startLocate(132, 433);
	imageLocate loginLocate(110, 580);
	imageLocate registerLocate(21, 700);

	// ������ͼƬ�������������������Ϸ����ͼƬ�϶࣬ʵ��Easy�м���ͼƬ���ޣ��ʶ����þֲ�������
	IMAGE menu;
	IMAGE login;
	IMAGE register1;
	IMAGE start;
	IMAGE runSteve;
	IMAGE menu_1;
	IMAGE login_1;
	IMAGE register_1;
	IMAGE start_1;
	IMAGE runSteve_1;
	IMAGE lLogin;
	IMAGE lRegister;
	IMAGE lStart;
	IMAGE lLogin_1;
	IMAGE lRegister_1;
	IMAGE lStart_1;
	IMAGE loginPage;
	IMAGE registerPage;
	char file_name[128];
	const int menuPageVideoNum = 240;
	IMAGE menuPageVideoImage[menuPageVideoNum];

	// ������ͼƬ����
	for (int i = 0; i < menuPageVideoNum - 1; i++)
	{
		sprintf_s(file_name, "../image/menupagevideo/page%03d.jpg", i);
		//printf(file_name);
		loadimage(&menuPageVideoImage[i], file_name);
	}
	loadimage(&login, _T("../image/title/login.png"));
	loadimage(&register1, _T("../image/title/register.png"));
	loadimage(&start, _T("../image/title/start.png"));
	loadimage(&runSteve, _T("../image/title/Runsteve.png"));
	loadimage(&login_1, _T("../image/title/login_1.png"));
	loadimage(&register_1, _T("../image/title/register_1.png"));
	loadimage(&start_1, _T("../image/title/start_1.png"));
	loadimage(&runSteve_1, _T("../image/title/Runsteve_1.png"));
	loadimage(&lLogin, _T("../image/title/llogin.png"));
	loadimage(&lRegister, _T("../image/title/lregister.png"));
	loadimage(&lStart, _T("../image/title/lstart.png"));
	loadimage(&lLogin_1, _T("../image/title/llogin_1.png"));
	loadimage(&lRegister_1, _T("../image/title/lregister_1.png"));
	loadimage(&lStart_1, _T("../image/title/lstart_1.png"));
	loadimage(&loginPage, _T("../image/title/loginpage.png"));
	loadimage(&registerPage, _T("../image/title/registerpage.png"));
	int videoNum = 0; // ��������Ƶ���ŵ�x֡��

	settextstyle(35, 0, _T("Consolas"));
	settextcolor(BLACK);
	setbkcolor(WHITE);

	// �������ֲ���
	mciSendString("open ../songs/C418.wav alias MySong", NULL, 0, NULL);
	mciSendString("play MySong", NULL, 0, NULL);

	BeginBatchDraw();

	while (true)
	{
		startTime = clock();
		cleardevice();
		peekmessage(&msg);

		// ������Ƶ����
		putimage(0, 0, &menuPageVideoImage[videoNum/2]);
		videoNum++;
		if (videoNum == 2*(menuPageVideoNum-1))
			videoNum = 0;

		if (imageButtonDetect(startLocate,start)) // �Ƿ�����start
		{
			
			if (msg.message == WM_LBUTTONDOWN && (userStatus == 1 || userStatus == 3))
			{
				PlaySound("../songs/button.wav", NULL, SND_ASYNC);
				break;
			}
				
			putimage(startLocate.x, startLocate.y, &lStart_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &lStart, SRCPAINT);
		}
		else
		{
			putimage(startLocate.x, startLocate.y, &start_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &start, SRCPAINT);
		}
		if (imageButtonDetect(loginLocate, login)) // �Ƿ�����login
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				menuStatus = 1;
				logORegStatus = 1;
				PlaySound("../songs/button.wav", NULL, SND_ASYNC);
			}
			else
			{
				putimage(loginLocate.x , loginLocate.y, &lLogin_1, SRCAND);
				putimage(loginLocate.x, loginLocate.y, &lLogin, SRCPAINT);
			}
			
		}
		else
		{
			putimage(loginLocate.x, loginLocate.y, &login_1, SRCAND);
			putimage(loginLocate.x, loginLocate.y, &login, SRCPAINT);
			
		}
		if (imageButtonDetect(registerLocate, register1)) // �Ƿ�����register
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				logORegStatus = 1;
				menuStatus = 2;
				PlaySound("../songs/button.wav", NULL, SND_ASYNC);
			}
			else
			{
				putimage(registerLocate.x, registerLocate.y, &lRegister_1, SRCAND);
				putimage(registerLocate.x, registerLocate.y, &lRegister, SRCPAINT);
			}
		}
		else
		{
			putimage(registerLocate.x, registerLocate.y, &register_1, SRCAND);
			putimage(registerLocate.x, registerLocate.y, &register1, SRCPAINT);
		}
		putimage(runSteveLovate.x, runSteveLovate.y, &runSteve_1, SRCAND);
		putimage(runSteveLovate.x, runSteveLovate.y, &runSteve, SRCPAINT);
		
		// ҳ�����
		if (menuStatus==1)
		{
			
			loginAndRegisterPage(loginPage);
			if (logORegStatus ==3)
			{
				if (cheackUser())
					userStatus = 1;
				else
					userStatus = 2;
			}
		}
		else if (menuStatus == 2)
		{
			loginAndRegisterPage(registerPage);
			if (logORegStatus == 3)
			{
				userStatus = 3;
			}
		}

		headText();	
		FlushBatchDraw();

		// ֡�ʿ���
		freamTime = clock() - startTime;
		if (fpsMenu - freamTime > 0)
			Sleep(fpsMenu - freamTime);

	}

	EndBatchDraw();
}

bool imageButtonDetect(imageLocate& locate, IMAGE& image)
{
	if (msg.x >= locate.x && msg.x <= locate.x + image.getwidth() && msg.y >= locate.y && msg.y <= locate.y + image.getheight())
		return 1;
	else
		return 0;
}

void loginAndRegisterPage(IMAGE& page)
{

	imageLocate loginPageLocate(44, 360);
	imageLocate userLocate(255, 415);
	imageLocate passwordLocate(255, 484);
	char ch[2];
	ch[1] = '\0';

	if (logORegStatus==1)
	{
		putimage(loginPageLocate.x, loginPageLocate.y, &page);
		if (msg.message == WM_KEYDOWN)
		{

			ch[0] = msg.vkcode;
			//printf("%d", ch[0]);
			if (ch[0] == 8 && strlen(user->name) > 0)
			{
				user->name[strlen(user->name) - 1] = '\0';
			}
			else if (ch[0] == 13)
			{
				logORegStatus = 2;
			}
			else
			{
				if (ch[0] != 8 && strlen(user->name) < 15)
					strcat_s(user->name, ch);
			}
		}
		settextstyle(35, 15, _T("Consolas"));
		static int n = 0;
		if (n < 10)
		{
			n++;
			outtextxy(userLocate.x+15*strlen(user->name)-5, userLocate.y, "|");
		}
		else if(n>=10&&n<20)
		{
			n++;
			
		}
		else
		{
			n = 0;
		}
		outtextxy(userLocate.x, userLocate.y, user->name);
	}
	else if (logORegStatus==2)
	{
		putimage(loginPageLocate.x, loginPageLocate.y, &page);
		if (msg.message == WM_KEYDOWN)
		{

			ch[0] = msg.vkcode;
			if (ch[0] == 8 && strlen(user->password) > 0)
			{
				user->password[strlen(user->password) - 1] = '\0';
			}
			else if (ch[0] == 13)
			{
				logORegStatus = 3;
				if (menuStatus == 2) 
				{
					userStatus = 3;
				}
				menuStatus = 0;
			}
			else
			{
				if (ch[0] != 8 && strlen(user->password) < 15)
					strcat_s(user->password, ch);
			}
		}
		settextstyle(35, 15, _T("Consolas"));
		static int n = 0;
		if (n < 10)
		{
			n++;
			outtextxy(passwordLocate.x + 15 * strlen(user->password) - 5, passwordLocate.y, "|");
		}
		else if (n >= 10 && n < 20)
		{
			n++;

		}
		else
		{
			n = 0;
		}
		outtextxy(userLocate.x, userLocate.y, user->name);
		outtextxy(passwordLocate.x, passwordLocate.y, user->password);
	}

}

newUser* readUserInfo()
{
	head = NULL;
	fopen_s(&dataFile, "../data/data.txt", "r");

	while (!feof(dataFile))
	{
		newUser* p = (newUser*)malloc(sizeof(newUser));
		
		if (fgets(p->name, sizeof(p->name), dataFile) != NULL)  // ���ļ����
		{ 
		}
		else {
			break;
		}
		char temp[21];
		fgets(p->password, sizeof(p->password), dataFile);
		fgets(temp, sizeof(temp), dataFile);
		sscanf_s(temp, "%d", &p->score);
		p->name[strcspn(p->name,"\n")]='\0';
		p->password[strcspn(p->password,"\n")]= '\0';
		p->points = 0;
		//printf("%s\n%s\n", p->name, p->password);
		p->next = NULL;
		newUser* last = head;
		if (last)
		{
			while (last->next)
			{
				last = last->next;
			}
			last->next = p;
		}
		else
		{
			head = p;
		}
	}
	fclose(dataFile);
	return head;
}

void updateUserFile()
{
	if (!cheackUser())
	{
		//��user��������
		if (head == NULL)
		{
			head = user;
			user->next = NULL;
		}
		else
		{
			newUser* temp = head;
			while (temp->next!=NULL)
			{
				temp = temp->next;
			}
			temp->next = user;
			user->next = NULL;
		}
	}
	//������score����
	newUser* i, * j;
	char tempName[21];
	char tempPassword[21];
	int tempScore;
	for (i = head; i != NULL; i = i->next)
	{
		for (j = i; j != NULL; j = j->next)
		{
			if (j->score > i->score)
			{
				//temp = min->score;
				tempScore = i->score;
				strcpy_s(tempName, i->name);
				strcpy_s(tempPassword, i->password);
				//min->data = j->data;
				i->score = j->score;
				strcpy_s(i->name, j->name);
				strcpy_s(i->password, j->password);
				//j->data = temp;
				j->score = tempScore;
				strcpy_s(j->name, tempName);
				strcpy_s(j->password, tempPassword);
				user = j;
			}
		}
	}
	//���ź��������д���ļ�
	newUser* temp = head;
	fopen_s(&dataFile, "../data/data.txt", "w");
	while (temp != NULL)
	{
		fprintf(dataFile, "%s\n", temp->name);
		fprintf(dataFile, "%s\n", temp->password);
		fprintf(dataFile, "%d\n", temp->score);
		temp = temp->next;
	}
	fclose(dataFile);

}

bool cheackUser()
{
	newUser* temp = head;
	while (temp)
	{
		if (!strcmp(temp->name, user->name) && !strcmp(temp->password, user->password))
		{
			if(user->score>temp->score)
				temp->score = user->score;
			user = temp;
			return 1;
		}
			
		temp = temp->next;
	}
	return 0;
}

void headText() 
{
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Consolas"));
	char s[50]="";
	char s2[50] = "Login failed, Please try again";
	char s3[50] = "";
	char s4[50] = "Account not logged in";
	switch (userStatus)
	{
	case 0:
		outtextxy((WIDTH - textwidth(s4)) / 2, 200, s4);
		break;
	case 1:
		sprintf_s(s, "Login successful,Welcome %s", user->name);
		outtextxy((WIDTH-textwidth(s))/2, 200, s);
		break;
	case 2:
		outtextxy((WIDTH - textwidth(s2)) / 2, 200, s2);
		break;
	case 3:
		sprintf_s(s3, "Register successful,Welcome %s", user->name);
		outtextxy((WIDTH - textwidth(s3)) / 2, 200, s3);
		break;
	default:
		break;
	}
}

//��Ϸѭ��
void gamePage()
{
	// ��ǰӦ�ò��ŵ�x֡
	int steveImageNum = 0;
	int railImageNum = 0;
	int backgroundImagNum = 0;
	int skyImageNum = 0;
	int attackImgCnt = 0;

	// �����ܹ�֡��
	const int steveNum = 14;
	const int railNum = 4;
	const int backgroundNum = 17;
	const int skyNum = 24;
	const int attackNum = 15;

	// ��̬������Ҫ�Ŵ�ͼƬλ��
	imageLocate steveLocate(0, 0);
	imageLocate railLocate(-90, -200);

	// ͼƬ����
	IMAGE gold[2];
	IMAGE arrow[2];
	IMAGE steve[steveNum];
	IMAGE steve1[steveNum];
	IMAGE attack[attackNum];
	IMAGE attack1[attackNum];
	IMAGE zomebie[2][zombieNum];
	IMAGE rail[railNum];
	IMAGE rail1[railNum];
	IMAGE background[backgroundNum];
	IMAGE sky[skyNum];
	IMAGE heart[2];
	IMAGE red;

	// ��λ�ñ仯��ͼƬ�ļ��� ��α3D��
	int size;
	int y = 200;
	char file_name[128];
	char file_name1[128];
	for (int i = 0; i < 120;i++)
	{
		size = (int)((y * 0.1));
		loadimage(&frameWiseGold[i], "../image/star/gold1.png", size, size, true);
		loadimage(&frameWiseGold1[i], "../image/star/gold.png", size, size, true);
		loadimage(&frameWiseArrow[i], "../image/arrow/arrow1.png", size, size, true);
		loadimage(&frameWiseArrow1[i], "../image/arrow/arrow.png", size, size, true);
		loadimage(&frameWiseGoldApple[i], "../image/props/goldApple1.png", size, size, true);
		loadimage(&frameWiseGoldApple1[i], "../image/props/goldApple.png", size, size, true);
		loadimage(&frameWiseHeart[i], "../image/heart/heart1.png", size, size, true);
		loadimage(&frameWiseHeart1[i], "../image/heart/heart.png", size, size, true);
		sprintf_s(file_name, "../image/zombie/zombie%02d.jpg", zombieImgCnt);
		sprintf_s(file_name1, "../image/zombie1/zombie1%02d.jpg", zombieImgCnt);
		zombieImgCnt++;
		if (zombieImgCnt == zombieNum)
			zombieImgCnt = 0;
		loadimage(&frameWiseZombie[i], file_name1, size * 3, size * 3, true);
		loadimage(&frameWiseZombie1[i], file_name, size * 3, size * 3, true);
		y += 6;
	}
	loadimage(&red,"../image/red.png");
	loadimage(&gold[0], "../image/star/gold1.png");
	loadimage(&gold[1], "../image/star/gold.png");
	loadimage(&arrow[0], "../image/arrow/arrow1.png");
	loadimage(&arrow[1], "../image/arrow/arrow.png");
	loadimage(&heart[0], "../image/heart/heart.png", 50, 50, true);
	loadimage(&heart[1], "../image/heart/heart1.png", 50, 50, true);
	for (steveImageNum = 0; steveImageNum < steveNum; steveImageNum++)
	{
		sprintf_s(file_name, "../image/steve/steve%02d.jpg", steveImageNum);
		sprintf_s(file_name1, "../image/steve1/steve101%02d.jpg", steveImageNum);
		//printf(file_name);
		loadimage(&steve[steveImageNum], file_name);
		loadimage(&steve1[steveImageNum], file_name1);

	}
	for (railImageNum = 0; railImageNum < railNum; railImageNum++)
	{
		sprintf_s(file_name, "../image/rail/rail%d.jpg", railImageNum);
		sprintf_s(file_name1, "../image/rail1/rail1%d.jpg", railImageNum);
		loadimage(&rail[railImageNum], file_name,720,1280,true);
		loadimage(&rail1[railImageNum], file_name1, 720, 1280, true);
	}
	for (backgroundImagNum = 0; backgroundImagNum < backgroundNum; backgroundImagNum++)
	{
		sprintf_s(file_name, "../image/background/background%02d.jpg", backgroundImagNum);
		loadimage(&background[backgroundImagNum], file_name);
	}
	for (skyImageNum = 0; skyImageNum < skyNum; skyImageNum++)
	{
		sprintf_s(file_name, "../image/sky/sky%02d.jpg", skyImageNum);
		loadimage(&sky[skyImageNum], file_name);
	}
	for (attackImgCnt = 0; attackImgCnt < attackNum; attackImgCnt++)
	{
		sprintf_s(file_name, "../image/attack/attack%02d.jpg", attackImgCnt);
		sprintf_s(file_name1, "../image/attack1/attack1%02d.jpg", attackImgCnt);
		//printf(file_name);
		loadimage(&attack[attackImgCnt], file_name);
		loadimage(&attack1[attackImgCnt], file_name1);
	}
	for (zombieImgCnt = 0; zombieImgCnt < zombieNum; zombieImgCnt++)
	{
		sprintf_s(file_name, "../image/zombie/zombie%02d.jpg", zombieImgCnt);
		sprintf_s(file_name1, "../image/zombie1/zombie1%02d.jpg", zombieImgCnt);
		//printf(file_name);
		loadimage(&zomebie[0][zombieImgCnt], file_name);
		loadimage(&zomebie[1][zombieImgCnt], file_name1);
	}

	// ��ǰ���ŵ�x֡ ����
	attackImgCnt = 0;
	zombieImgCnt = 0;
	steveImageNum = 0;	
	railImageNum = 0;
	backgroundImagNum = 0;
	skyImageNum = 1100;

	setbkmode(TRANSPARENT);
	settextcolor(WHITE);

	BeginBatchDraw();

	while (true)
	{
		startTime = clock();
		cleardevice();
		peekmessage(&msg);

		//ʷ�ٷ�״̬���
		steveMove(steveLocate);
		steveJump(steveLocate);
		
		//����ͼƬ����
		putimage(0, -50, &sky[skyImageNum / 100]);
		skyImageNum++;
		if (skyImageNum == skyNum * 100)
			skyImageNum = 0;
		putimage(0, 225, &background[backgroundImagNum]);
		backgroundImagNum++;
		if (backgroundImagNum == backgroundNum)
			backgroundImagNum = 0;
		putimage(railLocate.x, railLocate.y, &rail1[railImageNum], SRCAND);
		putimage(railLocate.x, railLocate.y, &rail[railImageNum], SRCPAINT);
		railImageNum++;
		if (railImageNum == railNum)
			railImageNum = 0;

		// ���������
		creatAllItem();
		updateAllItem();
	
		// ʷ�ٷ򶯻�����
		if (!attackFlag)
		{
			putimage(steveLocate.x, steveLocate.y, &steve1[steveImageNum], SRCAND);
			putimage(steveLocate.x, steveLocate.y, &steve[steveImageNum], SRCPAINT);
			steveImageNum++;
			if (steveImageNum == steveNum)
				steveImageNum = 0;
		}
		else
		{
			putimage(steveLocate.x, steveLocate.y, &attack1[attackImgCnt], SRCAND);
			putimage(steveLocate.x, steveLocate.y, &attack[attackImgCnt], SRCPAINT);
			attackImgCnt++;
			if (attackImgCnt == attackNum)
			{
				attackImgCnt = 0;
				attackFlag = 0;
			}
		}

		//�ܻ���������
		if (hurtStatus != 0)
		{
			putimage(0, 0, &red, SRCAND);
			hurtStatus++;
			if (hurtStatus == 6)
				hurtStatus = 0;
		}
		
		pointsUpdate();
		heartUpdate(heart, heartCnt);

		// �������ֵΪ0 ִ����Ϸ����
		if (heartCnt == 0)
		{
			setbkcolor(BLACK);
			cleardevice();
			heartCnt = HEARTCNT;
			if (user->points > user->score)
				user->score = user->points;
			updateUserFile();
			drawRanking();
			break;
		}

		// ֡�ʿ��� �� �޵м��٣�ͨ��������֡����ʵ�ּ���Ч����
		if (!invincibleFlag)
		{
			freamTime = clock() - startTime;
			if (fpsGame - freamTime > 0)
				Sleep(fpsGame - freamTime);
		}
		else
		{
			if (clock() - invincibleStartTime > 3000)
			{
				invincibleFlag = 0;
			}
		}
		
		FlushBatchDraw();
		
	}
	EndBatchDraw();
}

void steveMove(imageLocate& steveLocate)
{
	static int  steveMoveFlag = 0; //-1Ϊ�����ƶ� 1Ϊ�����ƶ� 0Ϊ����
	int steveSpeed = 10; //�ٶ�Ӧ��������150
	const int steveLeft = -180;
	const int steveRight = 180;
	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == 0x25)
		{
			steveMoveFlag = -1;
		}
		if (msg.vkcode == 0x27)
		{
			steveMoveFlag = 1;
		}
		if (msg.vkcode == 0x28)
		{
			attackFlag = 1;
		}
	}

	if (steveMoveFlag == -1 && steveLocate.x > steveLeft)
		steveLocate.x -= steveSpeed;
	else if (steveMoveFlag == 1 && steveLocate.x < steveRight)
		steveLocate.x += steveSpeed;
	if (steveLocate.x == steveLeft || steveLocate.x == steveRight || steveLocate.x == 0)
	{
		steveMoveFlag = 0;
		if (steveLocate.x == steveLeft)
			steveModle = 1;
		if (steveLocate.x == steveRight)
			steveModle = 3;
		if (steveLocate.x == 0)
			steveModle = 2;
	}
		
}

void steveJump(imageLocate& steveLocate)
{
	static int v0 = 26;
	static int gravity = 2;

	if (msg.message == WM_KEYDOWN)
	{
		if (msg.vkcode == 0x26)
			jumpFlag = 1;
	}
	if (jumpFlag == 1)
	{
		steveLocate.y -= v0;
		v0 -= gravity;
	}
	
	if (steveLocate.y == 0)
	{
		v0 = 26;
		jumpFlag = 0;
	}
	
}

void creatAllItem()
{
	//srand((unsigned int)time(0));
	int rand_number = rand() % 100000 + 1;

	//�ѶȺͽ�������������Ӷ�����
	goldRate = 0.001 + user->points * 0.000001;
	arrowRate = 0.001 + user->points * 0.000001;
	zombieRate = 0.001 + user->points * 0.000001;

	if (rand_number < goldRate * 3 * 100000)
	{
		rand_number = rand_number % 3 + 1;
		itemGold = createItem(itemGold, rand_number, goldCnt);
	}
	else if (rand_number < arrowRate * 3 * 100000 + goldRate * 3 * 100000)
	{
		rand_number = rand_number % 3 + 1;
		itemArrow = createItem(itemArrow, rand_number, arrowCnt);
	}
	else if (rand_number < zombieRate * 3 * 100000 + arrowRate * 3 * 100000 + goldRate * 3 * 100000)
	{
		rand_number = rand_number % 3 + 1;
		itemZombie = createItem(itemZombie, rand_number, zombieCnt);
	}
	else if (goldAppleCnt <= 1 && rand_number < goldAppleRate * 3 * 100000 + zombieRate * 3 * 100000 + arrowRate * 3 * 100000 + goldRate * 3 * 100000)
	{
		rand_number = rand_number % 3 + 1;
		itemGoldApple = createItem(itemGoldApple, rand_number, goldAppleCnt);
	}
	else if (heartItemCnt <= 1 && rand_number < heartRate * 3 * 100000 + goldAppleRate * 3 * 100000 + zombieRate * 3 * 100000 + arrowRate * 3 * 100000 + goldRate * 3 * 100000)
	{
		rand_number = rand_number % 3 + 1;
		itemHeart = createItem(itemHeart, rand_number, heartItemCnt);
	}
}

void updateAllItem()
{
	itemGold = itemUpdate(itemGold, goldCnt, 1);
	itemZombie = itemUpdate(itemZombie, zombieCnt, 3);
	itemArrow = itemUpdate(itemArrow, arrowCnt, 2);
	itemGoldApple = itemUpdate(itemGoldApple, goldAppleCnt, 4);
	itemHeart = itemUpdate(itemHeart, heartItemCnt, 5);
}

item* createItem(item* head,int modle,int& cnt)
{
	cnt++;
	item* p = new item();
	p->next = NULL;
	p->speed = 6;
	p->y = 200;
	p->modle = modle;

	if (modle == 1)
		p->x = 170;
	else if (modle == 2)
		p->x = 250;
	else if (modle == 3)
		p->x = 340;

	item* last = head;
	if (last)
	{
		while (last->next)
		{
			last = last->next;
		}
		last->next = p;
	}
	else
	{
		head = p;
	}
	return head;
}

item* itemUpdate(item* barrierItem,int& cnt,int category) //category 1Ϊ��� 2Ϊ��ͷ 3Ϊ��ʬ
{
	IMAGE image[2];
	if (barrierItem!=NULL && barrierItem->y > HEIGHT)
	{
		item* toDelete = barrierItem;
		barrierItem = barrierItem->next;
		free(toDelete);
		cnt--;	
	}
	if (category==3&&barrierItem != NULL && barrierItem->y >= 600 && barrierItem->y <= 750 && barrierItem->modle == steveModle && attackFlag == 1)
	{
		item* toDelete = barrierItem;
		barrierItem = barrierItem->next;
		free(toDelete);
		cnt--;
		awardZombieStatue = 1;
		user->points += award * 2;
		PlaySound("../songs/zombieDied.wav", NULL, SND_ASYNC);
	}
	if (barrierItem != NULL && barrierItem->y >= 750 && barrierItem->y <= 800 && barrierItem->modle == steveModle&&jumpFlag==0)
	{
		item* toDelete = barrierItem;
		barrierItem = barrierItem->next;
		free(toDelete);
		cnt--;
		if (category == 1)
		{
			user->points += award;
			awardGoldStatus = 1;
			PlaySound("../songs/getGold.wav", NULL, SND_ASYNC);
		}
		if ((category == 2||category==3)&&!invincibleFlag)
		{
			heartCnt--;
			hurtStatus = 1;
			PlaySound("../songs/hurt.wav", NULL, SND_ASYNC);
		}	
		if (category == 4&& !invincibleFlag)
		{
			invincibleStartTime = clock();
			invincibleFlag = 1;
			PlaySound("../songs/goldApple.wav", NULL, SND_ASYNC);
		}
		if (category == 5)
		{
			PlaySound("../songs/getGold.wav", NULL, SND_ASYNC);
			heartCnt++;
		}
	}
	item* head = barrierItem;
	int size;
	while (head)
	{
		if (category ==3&&head->next != NULL && head->next->modle == steveModle && attackFlag == 1)
		{
			if (head->next->y >= 600 && head->next->y <= 750)
			{
				item* toDelete = head->next;
				head->next = head->next->next;
				free(toDelete);
				cnt--;
				awardZombieStatue = 3;
				user->points += award * 2;
				PlaySound("../songs/zombieDied.wav", NULL, SND_ASYNC);
			}
		}
		if (head->next != NULL && head->next->modle == steveModle&&jumpFlag == 0)
		{
			if (head->next->y >= 750 && head->next->y <= 800)
			{
				item* toDelete = head->next;
				head->next = head->next->next;
				free(toDelete);
				cnt--;
				if (category == 1)
				{
					user->points += award;
					awardGoldStatus = 1;
					PlaySound("../songs/getGold.wav", NULL, SND_ASYNC);
				}
				
				if ((category == 2 || category == 3) && !invincibleFlag)
				{
					heartCnt--;
					hurtStatus = 1;
					PlaySound("../songs/hurt.wav", NULL, SND_ASYNC);
				}
				if (category == 4&&!invincibleFlag)
				{
					invincibleStartTime = clock();
					invincibleFlag = 1;
					PlaySound("../songs/goldApple.wav", NULL, SND_ASYNC);
				}
				if (category == 5)
				{
					PlaySound("../songs/getGold.wav", NULL, SND_ASYNC);
					heartCnt++;
				}
			}
		}

		head->y += head->y*0.015;
		//printf("%d\n", head -> speed);

		if (head->modle == 1)
		{
			head->x = (int)(-0.224 * head->y +220);
		}
		else if (head->modle == 2)
		{
			head->x = (int)(-0.05 * head->y+270);
		}
		else if (head->modle == 3)
		{
			head->x = (int)(0.13*head->y+320);
		}


		size = (int)((head->y * 0.1));
		int imageCnt = (head->y - 200) / 6;
		if (category == 1)
		{
			putimage(head->x, head->y, &frameWiseGold[imageCnt], SRCAND);
			putimage(head->x, head->y, &frameWiseGold1[imageCnt], SRCPAINT);
		}
		else if (category == 2)
		{
	
			putimage(head->x, head->y, &frameWiseArrow[imageCnt], SRCAND);
			putimage(head->x, head->y, &frameWiseArrow1[imageCnt], SRCPAINT);
		}
		else if (category == 3)
		{
			
			putimage(head->x-size, head->y, &frameWiseZombie[imageCnt], SRCAND);
			putimage(head->x -size, head->y, &frameWiseZombie1[imageCnt], SRCPAINT);
		}
		else if (category == 4)
		{
			putimage(head->x , head->y, &frameWiseGoldApple[imageCnt], SRCAND);
			putimage(head->x , head->y, &frameWiseGoldApple1[imageCnt], SRCPAINT);
		}
		else if(category==5)
		{
			putimage(head->x, head->y, &frameWiseHeart[imageCnt], SRCAND);
			putimage(head->x, head->y, &frameWiseHeart1[imageCnt], SRCPAINT);
		}
		head = head->next;
	}
	return barrierItem;
}

void heartUpdate(IMAGE heart[2], int heartCnt)
{
	imageLocate heartLocate(0, 0);
	for (int i = 0; i < heartCnt;i++)
	{
		putimage(heartLocate.x, heartLocate.y, &heart[1], SRCAND);
		putimage(heartLocate.x, heartLocate.y, &heart[0], SRCPAINT);
		heartLocate.x += 50;
	}
}

void pointsUpdate() 
{
	static int y = 90;
	char addPoints[20];
	if (awardGoldStatus == 1|| awardZombieStatue==1)
	{
		y = 90;
	}
	sprintf_s(Points, "Points:%04d", user->points);
	if (awardGoldStatus != 0)
		sprintf_s(addPoints, "+%d", award);
	else if (awardZombieStatue!=0)
		sprintf_s(addPoints, "+%d", award*2);
	settextstyle(35, 0, _T("Consolas"));
	outtextxy(300, 50, _T(Points));
	if (awardGoldStatus != 0)
	{
		outtextxy(410, y, addPoints);
		awardGoldStatus++;
		y--;
	}
	if (awardZombieStatue != 0)
	{
		outtextxy(410, y, addPoints);
		awardZombieStatue++;
		y--;
	}
	if (awardGoldStatus == 20)
	{
		awardGoldStatus=0;
	}
	if (awardZombieStatue == 20)
	{
		awardZombieStatue = 0;
	}
	user->points++;
}

void drawRanking()
{
	const int recRight = 50;
	const int recLeft = WIDTH - 50;
	const int recHigh = 50;
	const int recTop = 100;
	RECT r[15];
	newUser* temp = head;
	for (int i = 0; i < 15; i++)
	{
		r[i] = {recRight,(recTop + recHigh * i),recLeft,(recTop + recHigh * (i + 1))};
		if (i == 0)
		{
			drawtext(_T("GameOver"), &r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (i == 1)
		{
			drawtext(_T("TOP POINTS"), &r[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(_T("NAME"), &r[i], DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		else if(i>1&&i<12)
		{
			if (temp == NULL)
				continue;
			if (temp == user)
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(recRight, (recTop + recHigh * i), recLeft, (recTop + recHigh * (i + 1)));
			}
			char score[21] = "";
			char name[21] = "";
			sprintf_s(score, "%d", temp->score);
			sprintf_s(name, "%d: %s", i-1, temp->name);
			drawtext(score, &r[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(name, &r[i], DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			temp = temp->next;
		}
		else if (i == 12)
		{
			drawtext(_T("YOUR POINTS"), &r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (i == 13)
		{
			char score[21] = "";
			char name[21] = "";
			sprintf_s(score, "%d", user->points);
			sprintf_s(name, "%s", user->name);
			drawtext(score, &r[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			drawtext(name, &r[i], DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
	}
	FlushBatchDraw();
	Sleep(5000);
}