#include "Data.h"

int intro(AI_T *ai,Takara takara){
	AI_T *init_ai = ai;

	static int gametitle = LoadGraph("media\\chofu_fes2.bmp");

	static int start=0;
	if(start==0){
		start=1;
		
		//	�e���v��
		//	extern void !�������֐���!(AI_T &myAi);
		//	!�������֐���!(ai[!ai�̔ԍ�!]);
		//	extern Action !�ړ��֐���!(int view[2*VISIBLE+1][2*VISIBLE+1]);
		//	init_ai->moveFunc = !�ړ��֐���!;
		//!!![�d�v]!!!!��ԏ���(aiSample)�ȊO�A�ŏ���init_ai++;������!!!!!!!!!!
		//�֐����Ȃǂ����Ƒʖڂł��@���O�͑����ҏ�����(��{�����̃n���h���l�[��)

		// Player
		extern void PlayerInit(AI_T &myAi);
		PlayerInit(*init_ai);
		extern Action Player(int view[2*VISIBLE+1][2*VISIBLE+1],int takara_flag);
		init_ai->moveFunc = Player;
		// Player

		// AI0 (aiSample)
		init_ai++;
		extern void aiSampleInit(AI_T &myAi);
		aiSampleInit(*init_ai);
		extern Action aiSample(int view[2*VISIBLE+1][2*VISIBLE+1],int takara_flag);
		init_ai->moveFunc = aiSample;
		// AI0
	
		// AI1 (aiTest)
		init_ai++;
		extern void aiTestInit(AI_T &myAi);
		aiTestInit(*init_ai);
		extern Action aiTest(int view[2*VISIBLE+1][2*VISIBLE+1],int takara_flag);
		init_ai->moveFunc = aiTest;
		// AI1

		/*AI�ǉ���
		init_ai++;
		extern void AI��Init(AI_T &myAi);
		AI��Init(*init_ai);
		extern Action AI��(int view[2*VISIBLE+1][2*VISIBLE+1]);
		init_ai->moveFunc=AI��;
		*/
	}
	
	int entryX=320,entryY=315;
	int startX=320,startY=360;

	static int step=0,window=0,input=0,time=0,bright=255;
	int mx,my;
	int en=0;
	GetMousePoint(&mx,&my);

	time++;
	if(time>30)time=0;

	if(step==0){
		if(GetMouseInput()==1){
			step=1;
		}
	}
	if(step==1){
		if(window<230)window+=23;
		if(GetMouseInput()==1 && input==0){
			if(window>=230){
				for(int i= 0; i < AI_NUM ;i++){
					int x=51+180*(i%3),y=150+50*(int)(i/3);
					if(mx>=x && mx<=x+200 && my>=y && my<=y+50){
						if(ai[i].entry==0)ai[i].entry=1;
						else ai[i].entry=0;
					}
				}
				if(mx>=30 && my>=410 && mx<=610 && my<=460){
					step=2;
					window=0;
				}
			}
		}
	}
	if(step==2){
		bright-=10;
		if(bright<=0){
			SetDrawBright(255,255,255);
			return 1;
		}
	}
	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1)en++;
	}
	if(GetMouseInput()==1 && input==0){
		input=1;
	}
	if(GetMouseInput()==0 && input==1){
		input=0;
	}
	
	ClearDrawScreen();
	SetDrawBright(bright,bright,bright);
	DrawGraph(0,0,gametitle,FALSE);
	int cr=GetColor(125,255,205);

	if(step==0){
		if(time%30<=15){
			DrawString(240,350,"Click to start",cr,0);
		}
	}
	/*
	DrawString(entryX,entryY,"ENTRY AI",cr,0);
	DrawBox(entryX-80,entryY-20,entryX+80,entryY+20,cr,0);
	
	cr=GetColor(255,100,50);
	DrawString(startX,startY,"START!",cr,0);
	DrawBox(startX-100,startY-20,startX+100,startY+20,cr,0);
	*/
	if(step==1){
		cr=GetColor(0,0,0);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,200);
		DrawBox(10,240-window,630,240+window,cr,1);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,255);
		cr=GetColor(255,255,255);
		DrawBox(10,240-window,630,240+window,cr,0);
		if(window>=230){
			cr=GetColor(125,255,205);
			DrawString(240,30,"ENTRY AI",cr,0);
			cr=GetColor(255,255,255);
			for(int i= 0; i < AI_NUM ;i++){
				if(ai[i].entry==0)
					SetDrawBright(100,100,100);
				int x=51+180*(i%3),y=150+50*(int)(i/3);
				DrawBox(x,y,x+179,y+50,cr,0);
				DrawBox(x,y,x+50,y+50,cr,0);
				DrawString(x+50,y+25,ai[i].name,GetColor(0,255,255),0);
				DrawRotaGraph(x+25,y+25,1,0,ai[i].Graph,FALSE,0);
				SetDrawBright(255,255,255);
			}
			
			DrawBox(10,150,50,380,GetColor(255,255,255),0);
			DrawBox(591,150,630,380,GetColor(255,255,255),0);
			DrawTriangle(15,265,40,240,40,290,GetColor(255,255,255),0);
			DrawTriangle(625,265,600,240,600,290,GetColor(255,255,255),0);
			cr=GetColor(255,100,50);
			if(mx>=30 && my>=400 && mx<=610 && my<=450){
				DrawBox(30,410,610,460,cr,1);
				DrawString(240,425,"START!",GetColor(255,255,255),0);
			}else{
				DrawBox(30,410,610,460,cr,0);
				DrawString(240,425,"START!",cr,0);
			}
		}
	}
	return 0;
	//WaitKey();
	//WaitTimer(1000/60);
}