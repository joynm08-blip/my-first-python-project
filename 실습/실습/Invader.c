#include "main.h"
UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score, hiscore = 2000, killnum;
char* Aboom[8];

void main(void)
{
	UPOINT        ptend;
	int	loop = 1;

	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;
	while (loop)
	{
		DWORD         thisTickCount = GetTickCount();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		play();

		for (;;)
		{
			if (timeflag == FALSE)
			{
				thisTickCount = GetTickCount();

				if (thisTickCount - bcount > 100)
				{
					gotoxy(ptthisMypos);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //  ���߽� ���� ���������� ����
					printf("%s", Aboom[bp]);
					bp++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ٽ� ���������� ����
					if (bp > 7)
						break;
					bcount = thisTickCount;
				}
			}
			else
				break;
		}

		gotoxy(ptend);
		printf("����� ������ �ı��Ǿ����ϴ�.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("�ٽ� �ұ��? (y/n)\n");

		if (_getch() == 'y')
		{
			ClearScreen();
			bp = 0;
			killnum = 0;
			timeflag = 0;
			ptend.y = 12;
			loop = 1;
		}
		else
			loop = 0;
	}
}

void  play()
{
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
	DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore, pthi;
	int           juckspeed = 500;

	InitConsole();
	InitMyship();
	Initenemyship();

	ptthisMypos.x = ptMyoldpos.x = MYSHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MYSHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x = 2;
	pthi.y = 1;


	while (TRUE)
	{
		gthisTickCount = GetTickCount();

		if (_kbhit())
		{
			switch (_getch())
			{
			case ' ': //  ������ �����̽��� �ٲ�
				if (gthisTickCount - bulletcount > 300) // ���ݼӵ���  0.5�ʿ��� 0.3�ʷ� ����
				{
					MyBulletshot(ptthisMypos);
					bulletcount = gthisTickCount;
				}
				break;
			case 75: // ������ȯ �� ����Ű <- �κ��� 
				int speed = 2; // ������ �ӵ� ����
				ptMyoldpos.x = ptthisMypos.x;
				ptthisMypos.x -= speed;

				if (ptthisMypos.x < 1)ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break; 
			case 77: // ������ȯ�� ����Ű -> �� ����
				speed = -2; // ������ �ӵ� ����
				ptMyoldpos.x = ptthisMypos.x;
				ptthisMypos.x -= speed;
				if (ptthisMypos.x > 75)ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			case 72: // ��
				speed = 2; // ������ �ӵ� ����
				ptMyoldpos.y = ptthisMypos.y;
				ptthisMypos.y -= speed;
				if (ptthisMypos.y < 1) ptthisMypos.y = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			case 80: // ��
				speed = -2; // ������ �ӵ� ����
				ptMyoldpos.y = ptthisMypos.y;
				ptthisMypos.y -= speed;
				if (ptthisMypos.y > 25) ptthisMypos.y = 25; //
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;

			}
		}

		if (gthisTickCount - Count > 150)
		{

			if (CheckMybullet(ptthisMypos) == 0)
			{
				if (score > 2000)
					hiscore = score;
				break;
			}
			CheckenemyBullet(enemyship);
			DrawMyBullet();
			DrawMyship(&ptthisMypos, &ptMyoldpos);
			gotoxy(ptscore);

			if (killnum < 14)
				printf("���� : %d", score);

			else
			{
				timeflag = TRUE;
				break;
			}

			if (killnum > 5) // <- 5���� ������ �ӵ� ��b
				juckspeed = 200;

			if (killnum > 10) // <- 10���� ������ �ӵ� ��
				juckspeed = 50;

			gotoxy(pthi);

			Count = gthisTickCount;
		}

		if (gthisTickCount - gCount > juckspeed)
		{
			Bulletshot();
			DrawBullet();
			CalenemyshipPos();
			Drawenemyship();
			if (Checkenemypos() == 1)
				break;
			gCount = gthisTickCount;
		}
	}

}
