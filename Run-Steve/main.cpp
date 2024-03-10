#include<cstdio>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<cstring>
#include<cstdlib>

#define WIDTH 540
#define HEIGHT 920
FILE* dataFile;
int menuStatu = 0; //0为初始页面 1为登录页面 2为注册页面
int logORegStatu = 0; //0为初始 1为输入账号状态 2为输入密码状态 3为输入完成状态
int userStatu = 0; //0为未登录 1为登录成功 2为登录失败 3为注册成功

const clock_t FPS = 1000 / 120;

struct imageLocate
{
	int x;
	int y;
	imageLocate(int x, int y) : x(x), y(y) {}
};

struct newUser
{
	char name[21];
	char password[21];
	int score;
	newUser* next;
	newUser() : name("\0"),password("\0"),score(0),next(NULL) {}
};


void menuPage();
bool imageButtonDetect(imageLocate& locate, IMAGE& image, ExMessage& msg);
void loginAndRegisterPage(IMAGE& page, ExMessage& msg, newUser& user);
newUser* readUserInfo();
bool cheackUser(newUser* head, newUser target);
void headText(newUser& user);

int main()
{
	initgraph(WIDTH, HEIGHT);
	menuPage();

	fclose(dataFile);
	system("pause");
}

void menuPage()
{
	const int menuPageVideoNum = 897;
	imageLocate runSteveLovate(12, 100);
	imageLocate startLocate(132, 433);
	imageLocate loginLocate(110, 580);
	imageLocate registerLocate(21, 700);


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
	
	fopen_s(&dataFile, "../data/data.txt", "a+");
	newUser* head;
	head = readUserInfo();
	char file_name[128];
	IMAGE menuPageVideoImage[menuPageVideoNum];

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

	int num = 0;
	ExMessage msg;
	int loginOrRegisterPageFlag = 0; // 0为主界面 1为登录界面 2为注册界面
	bool loginOrRegisterPasswordFlag = 0;
	bool loginFlag = 0; //1为结束输入
	int loginStatu = 0; //0为初始状况，1为登录成功，2为登录失败，3为注册成功
	int startTime;
	int freamTime;
	newUser user;
	
	settextstyle(35, 0, _T("Consolas"));
	settextcolor(BLACK);
	setbkcolor(WHITE);

	BeginBatchDraw();

	while (true)
	{
		startTime = clock();
		cleardevice();
		peekmessage(&msg);

		

		putimage(0, 0, &menuPageVideoImage[num]);
		num++;
		if (num == menuPageVideoNum-1)
			num = 0;


		if (imageButtonDetect(startLocate,start,msg))
		{
			putimage(startLocate.x, startLocate.y, &lStart_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &lStart, SRCPAINT);
		}
		else
		{
			putimage(startLocate.x, startLocate.y, &start_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &start, SRCPAINT);
		}
		if (imageButtonDetect(loginLocate, login, msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				menuStatu = 1;
				logORegStatu = 1;
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
		if (imageButtonDetect(registerLocate, register1, msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				logORegStatu = 1;
				menuStatu = 2;
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
		if (menuStatu==1)
		{
			
			loginAndRegisterPage(loginPage, msg, user);
			if (logORegStatu ==3)
			{
				if (cheackUser(head, user))
					userStatu = 1;
				else
					userStatu = 2;
			}
		}
		else if (menuStatu == 2)
		{
			loginAndRegisterPage(registerPage, msg, user);
			if (logORegStatu == 3)
			{
				userStatu = 3;
			}
		}
		if (userStatu == 1 || userStatu == 3)
			fclose(dataFile);
			

		headText(user);

		
		FlushBatchDraw();

		freamTime = clock() - startTime;
		printf("%d\n ", freamTime);
		if (freamTime > 0)
			Sleep(FPS - freamTime);

	}

	EndBatchDraw();
}

bool imageButtonDetect(imageLocate& locate, IMAGE& image, ExMessage& msg)
{
	if (msg.x >= locate.x && msg.x <= locate.x + image.getwidth() && msg.y >= locate.y && msg.y <= locate.y + image.getheight())
		return 1;
	else
		return 0;
}

void loginAndRegisterPage(IMAGE& page, ExMessage& msg, newUser& user)
{

	imageLocate loginPageLocate(44, 360);
	imageLocate userLocate(255, 415);
	imageLocate passwordLocate(255, 484);
	char ch[2];
	ch[1] = '\0';

	if (logORegStatu==1)
	{
		putimage(loginPageLocate.x, loginPageLocate.y, &page);
		if (msg.message == WM_KEYDOWN)
		{

			ch[0] = msg.vkcode;
			printf("%d", ch[0]);
			if (ch[0] == 8 && strlen(user.name) > 0)
			{
				user.name[strlen(user.name) - 1] = '\0';
			}
			else if (ch[0] == 13)
			{
				logORegStatu = 2;
			}
			else
			{
				if (ch[0] != 8 && strlen(user.name) < 15)
					strcat_s(user.name, ch);
			}
		}
		outtextxy(userLocate.x, userLocate.y, user.name);
	}
	else if (logORegStatu==2)
	{
		putimage(loginPageLocate.x, loginPageLocate.y, &page);
		if (msg.message == WM_KEYDOWN)
		{

			ch[0] = msg.vkcode;
			if (ch[0] == 8 && strlen(user.password) > 0)
			{
				user.password[strlen(user.password) - 1] = '\0';
			}
			else if (ch[0] == 13)
			{
				logORegStatu = 3;
				if (menuStatu == 2)  //当为注册时
				{
					fprintf(dataFile, "%s\n", user.name);
					fprintf(dataFile, "%s\n", user.password);
					userStatu = 3;
				}
				menuStatu = 0;
			}
			else
			{
				if (ch[0] != 8 && strlen(user.password) < 15)
					strcat_s(user.password, ch);
			}
		}
		outtextxy(userLocate.x, userLocate.y, user.name);
		outtextxy(passwordLocate.x, passwordLocate.y, user.password);
	}

}

newUser* readUserInfo()
{
	newUser* head = NULL;
	while (!feof(dataFile))
	{
		newUser* p = (newUser*)malloc(sizeof(newUser));
		fgets(p->name, sizeof(p->name), dataFile);
		fgets(p->password, sizeof(p->password), dataFile);
		p->name[strcspn(p->name,"\n")]='\0';
		p->password[strcspn(p->password,"\n")]= '\0';
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
	return head;
}

bool cheackUser(newUser* head, newUser target)
{
	newUser* temp = head;
	while (temp)
	{
		if (!strcmp(temp->name, target.name) && !strcmp(temp->password, target.password))
			return 1;
		temp = temp->next;
	}
	return 0;
}

void headText(newUser& user)
{
	char s[50]="";
	char s2[50] = "Login failed, Please try again";
	char s3[50] = "";
	char s4[50] = "Account not logged in";
	switch (userStatu)
	{
	case 0:
		outtextxy((WIDTH - textwidth(s4)) / 2, 200, s4);
		break;
	case 1:
		sprintf_s(s, "Login successful,Welcome %s", user.name);
		outtextxy((WIDTH-textwidth(s))/2, 200, s);
		break;
	case 2:
		outtextxy((WIDTH - textwidth(s2)) / 2, 200, s2);
		break;
	case 3:
		sprintf_s(s3, "Register successful,Welcome %s", user.name);
		outtextxy((WIDTH - textwidth(s3)) / 2, 200, s3);
		break;
	default:
		break;
	}
}