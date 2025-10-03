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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //  폭발시 색갈 빨간생으로 변경
					printf("%s", Aboom[bp]);
					bp++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 다시 검은색으로 변경
					if (bp > 7)
						break;
					bcount = thisTickCount;
				}
			}
			else
				break;
		}

		gotoxy(ptend);
		printf("당신의 비행기는 파괴되었습니다.");
		ptend.y += 1;
		gotoxy(ptend);
		printf("다시 할까요? (y/n)\n");

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
			case ' ': //  공격을 스페이스로 바꿈
				if (gthisTickCount - bulletcount > 300) // 공격속도를  0.5초에서 0.3초로 변경
				{
					MyBulletshot(ptthisMypos);
					bulletcount = gthisTickCount;
				}
				break;
			case 75: // 방향전환 을 방향키 <- 로변경 
				int speed = 2; // 움직임 속도 증가
				ptMyoldpos.x = ptthisMypos.x;
				ptthisMypos.x -= speed;

				if (ptthisMypos.x < 1)ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break; 
			case 77: // 방향전환을 방향키 -> 로 변경
				speed = -2; // 움직임 속도 증가
				ptMyoldpos.x = ptthisMypos.x;
				ptthisMypos.x -= speed;
				if (ptthisMypos.x > 75)ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			case 72: // ↑
				speed = 2; // 움직임 속도 증가
				ptMyoldpos.y = ptthisMypos.y;
				ptthisMypos.y -= speed;
				if (ptthisMypos.y < 1) ptthisMypos.y = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			case 80: // ↓
				speed = -2; // 움직임 속도 증가
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
				printf("점수 : %d", score);

			else
			{
				timeflag = TRUE;
				break;
			}

			if (killnum > 5) // <- 5마리 잡으면 속도 업b
				juckspeed = 200;

			if (killnum > 10) // <- 10마리 잡으면 속도 업
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
