#include<cstdio>
#include<graphics.h>
#include<time.h>

#define WIDTH 540
#define HEIGHT 920

const clock_t FPS = 1000 / 60;
int startTime;
int freamTime;


void MenuPage();
void RegisterPage();

int main()
{
	initgraph(WIDTH, HEIGHT);
	MenuPage();




	system("pause");
}

void MenuPage()
{
	const int menuPageVideoNum = 897;

	IMAGE Menu;
	IMAGE Login;
	IMAGE Register;
	IMAGE Start;
	IMAGE RunSteve;
	IMAGE Menu_1;
	IMAGE Login_1;
	IMAGE Register_1;
	IMAGE Start_1;
	IMAGE RunSteve_1;
	IMAGE lLogin;
	IMAGE lRegister;
	IMAGE lStart;
	IMAGE lLogin_1;
	IMAGE lRegister_1;
	IMAGE lStart_1;

	char file_name[128];
	IMAGE menuPageVideoImage[menuPageVideoNum];

	for (int i = 0; i < menuPageVideoNum - 1; i++)
	{
		sprintf_s(file_name, "../image/menupagevideo/page%03d.jpg", i);
		printf(file_name);
		loadimage(&menuPageVideoImage[i], file_name);
	}
	loadimage(&Login, _T("../image/title/login.png"));
	loadimage(&Register, _T("../image/title/register.png"));
	loadimage(&Start, _T("../image/title/start.png"));
	loadimage(&RunSteve, _T("../image/title/Runsteve.png"));
	loadimage(&Login_1, _T("../image/title/login_1.png"));
	loadimage(&Register_1, _T("../image/title/register_1.png"));
	loadimage(&Start_1, _T("../image/title/start_1.png"));
	loadimage(&RunSteve_1, _T("../image/title/Runsteve_1.png"));
	loadimage(&lLogin, _T("../image/title/llogin.png"));
	loadimage(&lRegister, _T("../image/title/lregister.png"));
	loadimage(&lStart, _T("../image/title/lstart.png"));
	loadimage(&lLogin_1, _T("../image/title/llogin_1.png"));
	loadimage(&lRegister_1, _T("../image/title/lregister_1.png"));
	loadimage(&lStart_1, _T("../image/title/lstart_1.png"));

	int num = 0;
	ExMessage msg;
	bool StartFlag = 1;
	bool LoginFlag = 1;
	bool RegisterFlag = 1;
	while (true)
	{
		startTime = clock();
		cleardevice();

		if (peekmessage(&msg))
		{
			if (msg.x >= 132 && msg.x <= 132 + Start.getwidth() && msg.y >= 433 && msg.y <= 433 + Start.getheight())
				StartFlag = 0;
			else
				StartFlag = 1;
			if (msg.x >= 110 && msg.x <= 110 + Login.getwidth() && msg.y >= 580 && msg.y <= 580 + Login.getheight())
				LoginFlag = 0;
			else
				LoginFlag = 1;
			if (msg.x >= 21 && msg.x <= 21 + Register.getwidth() && msg.y >= 700 && msg.y <= 700 + Register.getheight())
			{
				RegisterFlag = 0;
				if (msg.message == WM_LBUTTONDOWN)
					RegisterPage();
			}

			else
				RegisterFlag = 1;
		}


		BeginBatchDraw();
		putimage(0, 0, &menuPageVideoImage[num]);
		num++;
		if (num == menuPageVideoNum)
			num = 0;
		if (StartFlag)
		{
			putimage(132, 433, &Start_1, SRCAND);
			putimage(132, 433, &Start, SRCPAINT);
		}
		else
		{
			putimage(132, 433, &lStart_1, SRCAND);
			putimage(132, 433, &lStart, SRCPAINT);
		}
		if (LoginFlag)
		{
			putimage(110, 580, &Login_1, SRCAND);
			putimage(110, 580, &Login, SRCPAINT);
		}
		else
		{
			putimage(110, 580, &lLogin_1, SRCAND);
			putimage(110, 580, &lLogin, SRCPAINT);
		}
		if (RegisterFlag)
		{
			putimage(21, 700, &Register_1, SRCAND);
			putimage(21, 700, &Register, SRCPAINT);
		}
		else
		{
			putimage(21, 700, &lRegister_1, SRCAND);
			putimage(21, 700, &lRegister, SRCPAINT);
		}
		putimage(12, 100, &RunSteve_1, SRCAND);
		putimage(12, 100, &RunSteve, SRCPAINT);
		EndBatchDraw();

		freamTime = clock() - startTime;
		//	printf("%d\n ", freamTime);
		if (freamTime > 0)
		{
			Sleep(FPS - freamTime);
		}
	}


}

void RegisterPage()
{

}