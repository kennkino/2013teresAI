#include "Data.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	//SetMouseDispFlag(TRUE);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetScreenMemToVramFlag(FALSE);
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen( DX_SCREEN_BACK);
	if(DxLib_Init()==-1)		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	//�f�o�b�N�p�ɃR���\�[�����o��������
	/*
	AllocConsole();
	freopen("CONOUT$","w",stdout);
	freopen("CONIN$","r",stdin);z
	*/

	Mode gamemode=OPENING;
	AI_T ai[AI_NUM];
	Takara takara;
	int death[AI_NUM]={0};
	Tagger tagger[TAGGER_NUM];
	int tagger_num = 0;
	int STAGE[WIDTH][HEIGHT]={0};
	int round=0;
	int start=0;
	int end=0;
	int StartTime,TimeLimit;

	for(int i=0;i<AI_NUM;i++){
		ai[i].entry=1;
	}
	ai[0].entry=0;

	while(ProcessMessage()!=-1){
		int speed=0;
		switch(gamemode){
		case OPENING:
			start=intro(ai);
			if(start==1)gamemode=SETTING;
			break;
		case SETTING:
			takara.x=GetRand(WIDTH/2-2)+WIDTH/2;
			takara.y=GetRand(HEIGHT/2-1)+1;
			takara.drop=0;
			make_Stage(STAGE,takara);//�}�b�v�\��
			tagger_num = init_Tagger(tagger,STAGE);//�S�̏����� //tagger_num�͋S�̗v�f�ԍ�

			init_Ai(ai,STAGE);

			round++;
			TimeLimit=TIME_LIMIT*60*79;//�Q�[���J�n���̎����ɍ��킹��
			gamemode=RUNNING;

			break;
		case RUNNING:
			TimeLimit-=79;
			if(TimeLimit<0)TimeLimit=0;
			if(tagger[tagger_num].step==0){
				//tagger[tagger_num].act=next_Tagger(tagger[tagger_num],STAGE,ai);
				tagger[tagger_num].act=tagger[tagger_num].moveFunc(tagger[tagger_num].x,tagger[tagger_num].y,STAGE); //AI�ƈꏏ�ŁAmoveFunc�g��
			}
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].step==0 && ai[i].entry==1){
					setview_Ai(&ai[i],STAGE);
					//ai[i].act=next_Ai(ai[i].view); //henteko : ����moveFunc()���g�����߃R�����g�A�E�g
					ai[i].act = ai[i].moveFunc(ai[i].view);
				}
			}
			/*if(TimeLimit>TIME_LIMIT*45*79)speed=0;
			else if(TimeLimit>TIME_LIMIT*30*79)speed=1;
			else if(TimeLimit>TIME_LIMIT*15*79)speed=1;
			else speed=3;*/
			update_Tagger(&tagger[tagger_num],STAGE);
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].entry==1)
					update_Ai(&ai[i],STAGE,&takara,speed);
			}
			update_stage(STAGE,ai,tagger[tagger_num],takara);
			
			ClearDrawScreen();
			draw(STAGE,ai,tagger[tagger_num],takara);
			DrawFormatString(30,30,GetColor(0,255,255),"ROUND%d",round);
			
			DrawFormatString(500,15,GetColor(0,255,0),"TIME %d",TimeLimit);
			
			if(1){
				for(int i=0;i<AI_NUM;i++){
					if(death_Ai(ai[i],tagger[tagger_num])==1 && ai[i].entry==1){
						death[i]++;
						DrawBox(0,230,640,260,GetColor(0,0,0),1);
						DrawBox(-1,230,642,260,GetColor(255,0,0),0);
						DrawFormatString(100,240,GetColor(255,0,0),"%s�����܂�܂���",ai[i].name);// 8/3 zero�ǋL:AI�ߊl�̐錾���܂Ƃ߂��B
						
						if(ai[i].takara_flag==1){
						takara.x=ai[i].x;
						takara.y=ai[i].y;
						takara.drop=0;
						ai[i].takara_flag=0;
						}
						//���̏ꏊ�ɖ߂����
						ai[i].x=1;
						ai[i].y=HEIGHT-2;
						ai[i].s_x=(ai[i].x+0.5)*BOX;
						ai[i].s_y=(ai[i].y+0.5)*BOX;
						ai[i].act=STOP;
						ai[i].step=0;
						ai[i].life=1;
						STAGE[ai[i].x][ai[i].y]=2;
						TimeLimit-=1000;//���ԃy�i���e�B
					}
					if(ai[i].takara_flag==1&&STAGE[ai[i].x][ai[i].y]==5/*&&ai[i].x<3&&ai[i].y>HEIGHT-4*/){//�N���A����
						WaitTimer(3000);
						if(round>=ROUND_MAX){
							gamemode=ENDING;
						}else{
							gamemode=SETTING;
						}
						break;
					}
				}
			}
			if(TimeLimit<=0){// 8/3 zero�ǋL:�^�C���A�b�v��ݒ�
				//round--;
				DrawString(100,240,"���Ԑ؂�ł�",GetColor(255,0,0));
				WaitTimer(3000);
				if(round>=ROUND_MAX){
					gamemode=ENDING;
				}
				else{
					gamemode=SETTING;
				}
				break;
			}
			if(CheckHitKey(KEY_INPUT_R)==1){
				gamemode=SETTING;
			}
			break;
		case ENDING:
			end=ranking(ai,death);
			break;
		default:
			break;
		}
		if(end==1 || CheckHitKey(KEY_INPUT_ESCAPE))break;
		ScreenFlip();
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}