#include<cstdio>
#include<graphics.h>
#include<time.h>

#define WIDTH 540
#define HEIGHT 920

const clock_t FPS = 1000 / 60;
int startTime;
int freamTime;

struct imageLocate
{
	int x;
	int y;
	imageLocate(int x, int y) : x(x), y(y) {}
};


void menuPage();
bool imageButtonDetect(imageLocate&, IMAGE&, ExMessage&);

int main()
{
	initgraph(WIDTH, HEIGHT);
	menuPage();


	system("pause");
}

void menuPage()
{
	const int menuPageVideoNum = 897;
	imageLocate runSteveLovate(12, 100);
	imageLocate startLocate(132, 433);
	imageLocate loginLocate(110, 580);
	imageLocate registerLocate(21, 700);
	imageLocate loginPageLocate(44, 360);
	imageLocate userLocate(255, 411);
	imageLocate passwordLocate(255, 486);

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

	int num = 0;
	ExMessage msg;
	bool loginPageFlag = 0;

	while (true)
	{
		startTime = clock();
		cleardevice();
		

		BeginBatchDraw();

		putimage(0, 0, &menuPageVideoImage[num]);
		num++;
		if (num == menuPageVideoNum)
			num = 0;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (imageButtonDetect(startLocate, start, msg))
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
					loginPageFlag = 1;
				}
				else
				{
					putimage(loginLocate.x, loginLocate.y, &lLogin_1, SRCAND);
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
				putimage(registerLocate.x, registerLocate.y, &lRegister_1, SRCAND);
				putimage(registerLocate.x, registerLocate.y, &lRegister, SRCPAINT);
			}
			else
			{
				putimage(registerLocate.x, registerLocate.y, &register_1, SRCAND);
				putimage(registerLocate.x, registerLocate.y, &register1, SRCPAINT);
			}
			putimage(runSteveLovate.x, runSteveLovate.y, &runSteve_1, SRCAND);
			putimage(runSteveLovate.x, runSteveLovate.y, &runSteve, SRCPAINT);
		}
		
		if (loginPageFlag)
		{
			putimage(loginPageLocate.x, loginPageLocate.y, &loginPage);
		}


		EndBatchDraw();

		freamTime = clock() - startTime;
		//	printf("%d\n ", freamTime);
		/*if (freamTime > 0)
			Sleep(FPS - freamTime);*/
	}
}

bool imageButtonDetect(imageLocate& locate, IMAGE& image, ExMessage& msg)
{
	if (msg.x >= locate.x && msg.x <= locate.x + image.getwidth() && msg.y >= locate.y && msg.y <= locate.y + image.getheight())
		return 1;
	else
		return 0;
}
