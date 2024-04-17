#include<cstdio>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<cstring>
#include<cstdlib>
#include<time.h>

#define WIDTH 540
#define HEIGHT 920
FILE* dataFile;
ExMessage msg;
const clock_t FPS = 1000 / 60;
const int award = 100;

int startTime;
int freamTime;

int menuStatue = 0; //0为初始页面 1为登录页面 2为注册页面
int logORegStatue = 0; //0为初始 1为输入账号状态 2为输入密码状态 3为输入完成状态
int userStatue = 0; //0为未登录 1为登录成功 2为登录失败 3为注册成功
int heartCnt = 10; //生命数

int steveModle = 2;
int jumpFlag = 0; // 1 jumping;

int hurtStatue = 0;
int awardGoldStatue = 0;
char Points[128];

struct imageLocate
{
	int x;
	int y;
	imageLocate(int x, int y) : x(x), y(y) {}
};

struct item
{
	int x;
	int y;
	int centerX;
	int centerY;
	int speed;
	int modle; //为出现在第几列 1 2 3
	IMAGE img;
	item* next;
	item(IMAGE img) :img(img), x((WIDTH - img.getwidth()) / 2), y((HEIGHT - img.getheight()) / 2), centerX((x + img.getwidth()) / 2), centerY((y + img.getheight()) / 2),speed(0),next(NULL),modle(0){}

};

struct newUser
{
	char name[21];
	char password[21];
	int score;
	newUser* next;
	newUser() : name("\0"),password("\0"),score(0),next(NULL) {}
};

newUser* head=NULL;
newUser* user=(newUser*)malloc(sizeof(newUser));

void menuPage();
bool imageButtonDetect(imageLocate& locate, IMAGE& image);
void loginAndRegisterPage(IMAGE& page);
newUser* readUserInfo();
bool cheackUser(newUser* target);
void headText();
void gamePage();
void steveMove(imageLocate& steveLocate);
void steveJump(imageLocate& steveLocate);
item* createItem(item*,IMAGE&,int,int&);
item* itemUpdate(item* barrierGold, IMAGE gold[2],int& cnt,int category);
void heartUpdate(IMAGE heart[2], int heartCnt);
void pointsUpdate();


int main()
{
	initgraph(WIDTH, HEIGHT);
	while (true)
	{
		menuPage();
		gamePage();
		fclose(dataFile);
	}
	
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
	
	int loginOrRegisterPageFlag = 0; // 0为主界面 1为登录界面 2为注册界面
	bool loginOrRegisterPasswordFlag = 0;
	bool loginFlag = 0; //1为结束输入
	int loginStatu = 0; //0为初始状况，1为登录成功，2为登录失败，3为注册成功

	
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


		if (imageButtonDetect(startLocate,start))
		{
			if (msg.message == WM_LBUTTONDOWN && (userStatue == 1||userStatue==3))
				break;
			putimage(startLocate.x, startLocate.y, &lStart_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &lStart, SRCPAINT);
		}
		else
		{
			putimage(startLocate.x, startLocate.y, &start_1, SRCAND);
			putimage(startLocate.x, startLocate.y, &start, SRCPAINT);
		}
		if (imageButtonDetect(loginLocate, login))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				menuStatue = 1;
				logORegStatue = 1;
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
		if (imageButtonDetect(registerLocate, register1))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				logORegStatue = 1;
				menuStatue = 2;
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
		if (menuStatue==1)
		{
			
			loginAndRegisterPage(loginPage);
			if (logORegStatue ==3)
			{
				if (cheackUser(user))
					userStatue = 1;
				else
					userStatue = 2;
			}
		}
		else if (menuStatue == 2)
		{
			loginAndRegisterPage(registerPage);
			if (logORegStatue == 3)
			{
				userStatue = 3;
			}
		}
		if (userStatue == 1 || userStatue == 3)
			fclose(dataFile);
			

		headText();

		
		FlushBatchDraw();

		freamTime = clock() - startTime;
		if (freamTime > 0)
			Sleep(FPS - freamTime);

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

	if (logORegStatue==1)
	{
		putimage(loginPageLocate.x, loginPageLocate.y, &page);
		if (msg.message == WM_KEYDOWN)
		{

			ch[0] = msg.vkcode;
			printf("%d", ch[0]);
			if (ch[0] == 8 && strlen(user->name) > 0)
			{
				user->name[strlen(user->name) - 1] = '\0';
			}
			else if (ch[0] == 13)
			{
				logORegStatue = 2;
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
	else if (logORegStatue==2)
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
				logORegStatue = 3;
				if (menuStatue == 2)  //当为注册时
				{
					fprintf(dataFile, "%s\n", user->name);
					fprintf(dataFile, "%s\n", user->password);
					fprintf(dataFile, "%d\n", user->score);
					userStatue = 3;
				}
				menuStatue = 0;
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

bool cheackUser(newUser *target)
{
	newUser* temp = head;
	while (temp)
	{
		if (!strcmp(temp->name, target->name) && !strcmp(temp->password, target->password))
			return 1;
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
	switch (userStatue)
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

void gamePage()
{

	int goldCnt = 0;
	int arrowCnt = 0;
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	const int steveNum = 14;
	const int railNum = 4;
	const int backgroundNum = 17;
	const int skyNum = 24;

	char file_name[128];
	char file_name1[128];

	IMAGE gold[2];
	IMAGE arrow[2];
	IMAGE steve[steveNum];
	IMAGE steve1[steveNum];
	IMAGE rail[railNum];
	IMAGE rail1[railNum];
	IMAGE background[backgroundNum];
	IMAGE sky[skyNum];
	IMAGE heart[2];
	IMAGE red;

	imageLocate steveLocate(0, 0);
	imageLocate railLocate(-90, -200);

	loadimage(&red,"../image/red.png");
	loadimage(&gold[0], "../image/star/gold1.png");
	loadimage(&gold[1], "../image/star/gold.png");
	loadimage(&arrow[0], "../image/arrow/arrow1.png");
	loadimage(&arrow[1], "../image/arrow/arrow.png");
	loadimage(&heart[0], "../image/heart/heart.png", 50, 50, true);
	loadimage(&heart[1], "../image/heart/heart1.png", 50, 50, true);
	

	for (i = 0; i < steveNum; i++)
	{
		sprintf_s(file_name, "../image/steve/steve%02d.jpg", i);
		sprintf_s(file_name1, "../image/steve1/steve101%02d.jpg", i);
		//printf(file_name);
		loadimage(&steve[i], file_name);
		loadimage(&steve1[i], file_name1);

	}
	for (j = 0; j < railNum; j++)
	{
		sprintf_s(file_name, "../image/rail/rail%d.jpg", j);
		sprintf_s(file_name1, "../image/rail1/rail1%d.jpg", j);
		loadimage(&rail[j], file_name,720,1280,true);
		loadimage(&rail1[j], file_name1, 720, 1280, true);
	}
	for (m = 0; m < backgroundNum; m++)
	{
		sprintf_s(file_name, "../image/background/background%02d.jpg", m);
		loadimage(&background[m], file_name);
	}
	for (n = 0; n < skyNum; n++)
	{
		sprintf_s(file_name, "../image/sky/sky%02d.jpg", n);
		loadimage(&sky[n], file_name);
	}
	i = 0;	
	j = 0;
	m = 0;
	n = 1100;
	item* barrierGold = NULL;
	item* barrierArrow = NULL;
	srand((unsigned int)time(0));
	//MyClass* obj = new MyClass(args);

	setbkmode(TRANSPARENT);
	settextcolor(WHITE);

	BeginBatchDraw();

	while (true)
	{
		startTime = clock();

		cleardevice();
		peekmessage(&msg);

		steveMove(steveLocate);
		steveJump(steveLocate);
		
		
	
		int rand_nuber = rand() % 100 + 1;
		if (goldCnt <= 5 && rand_nuber < 10)
		{
			rand_nuber = rand_nuber % 3 + 1;
			barrierGold = createItem(barrierGold, gold[0], rand_nuber , goldCnt);
		}
		else if (arrowCnt <= 2&&rand_nuber<15)
		{
			rand_nuber = rand_nuber % 3 + 1;
			barrierArrow = createItem(barrierArrow, arrow[0], rand_nuber, arrowCnt);
		}
			
		putimage(0, -50, &sky[n/100]);
		n++;
		if (n == skyNum*100)
			n = 0;

		putimage(0, 225, &background[m]);
		m++;
		if (m == backgroundNum)
			m = 0;

		

		putimage(railLocate.x, railLocate.y,&rail1[j], SRCAND);
		putimage(railLocate.x, railLocate.y,&rail[j], SRCPAINT);
		j++;
		if (j == railNum)
			j = 0;

		barrierGold = itemUpdate(barrierGold, gold,goldCnt,1);
		barrierArrow = itemUpdate(barrierArrow, arrow, arrowCnt,2);
		putimage(steveLocate.x, steveLocate.y, &steve1[i], SRCAND);
		putimage(steveLocate.x,steveLocate.y, &steve[i], SRCPAINT);
		if (hurtStatue != 0)
		{
			putimage(0, 0, &red, SRCAND);
			hurtStatue++;
			if (hurtStatue == 6)
				hurtStatue = 0;
		}
	
		i++;
		if (i == steveNum)
			i = 0;
		
		pointsUpdate();
		heartUpdate(heart, heartCnt);

		if (heartCnt == 0)
		{
			setbkcolor(BLACK);
			cleardevice();
			RECT r = { 0, 0, WIDTH, HEIGHT };
			drawtext(_T("GameOver"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			FlushBatchDraw();
			heartCnt = 10;
			Sleep(1000);
			break;
		}

		freamTime = clock() - startTime;
		if (FPS - freamTime > 0)
			Sleep(FPS - freamTime);
		FlushBatchDraw();
		
	}
	EndBatchDraw();
}

void steveMove(imageLocate& steveLocate)
{
	static int  steveMoveFlag = 0; //-1为向左移动 1为向右移动 0为不动
	int steveSpeed = 10; //速度应可以整除150
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

item* createItem(item* head,IMAGE &gold,int modle,int& cnt)
{
	cnt++;
	item* p = new item(gold);
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

item* itemUpdate(item* barrierItem, IMAGE image[2],int& cnt,int category) //category 1为金币 2为箭头
{
	if (barrierItem!=NULL && barrierItem->y > HEIGHT)
	{
		item* toDelete = barrierItem;
		barrierItem = barrierItem->next;
		free(toDelete);
		cnt--;
			
	}

	if (barrierItem != NULL && barrierItem->y >= 750 && barrierItem->y <= 800 && barrierItem->modle == steveModle&&jumpFlag==0)
	{
		item* toDelete = barrierItem;
		barrierItem = barrierItem->next;
		free(toDelete);
		cnt--;
		if (category == 1)
		{
			user->score += award;
			awardGoldStatue = 1;
		}
		if (category == 2)
		{
			heartCnt--;
			hurtStatue = 1;
		}
			
	}

	item* head = barrierItem;
	int size;
	while (head)
	{
		
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
					user->score += award;
					awardGoldStatue = 1;
				}
				
				if (category == 2)
				{
					heartCnt--;
					hurtStatue = 1;
				}
			}
		}


		head->y += head->speed;
		
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

		if (category == 1)
		{
			loadimage(&image[0], "../image/star/gold1.png", size, size, true);
			loadimage(&image[1], "../image/star/gold.png", size, size, true);
		}
		else if (category == 2)
		{
			loadimage(&image[0], "../image/arrow/arrow1.png", size, size, true);
			loadimage(&image[1], "../image/arrow/arrow.png", size, size, true);
		}

		putimage(head->x, head->y, &image[0], SRCAND);
		putimage(head->x, head->y, &image[1], SRCPAINT);

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
	if (awardGoldStatue == 1)
	{
		y = 90;
	}
	sprintf_s(Points, "Points:%04d", user->score);
	settextstyle(35, 0, _T("Consolas"));
	outtextxy(300, 50, _T(Points));
	if (awardGoldStatue != 0)
	{
		outtextxy(410, y, _T("+100"));
		awardGoldStatue++;
		y--;
	}
	if (awardGoldStatue == 20)
	{
		awardGoldStatue=0;
	}
	
	user->score++;
}