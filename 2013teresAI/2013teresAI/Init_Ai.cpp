/*AI������������֐��ł��B*/

#include "Data.h"


//8/19�ǉ�tao31�S������͈͓��Ȃ�J��Ԃ�
int distans_tag_ai(int x, int y){

	if(WIDTH/4<x&&x<(WIDTH - WIDTH/4)){
		if(HEIGHT/4<y&&y<(HEIGHT - HEIGHT/4)){
			return 0;
		}
	}
	else return 1;

}

void init_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]){

	AI_T *init_ai = ai;

	// AI��ύX����Ƃ��ɂ�����ꏊ

	//	�e���v��
	//	extern void !�������֐���!(AI_T &myAi);
	//	!�������֐���!(ai[!ai�̔ԍ�!]);
	//	extern Action !�ړ��֐���!(int view[2*VISIBLE+1][2*VISIBLE+1]);
	//	init_ai->moveFunc = !�ړ��֐���!;
	//!!![�d�v]!!!!��ԏ���(aiSample)�ȊO�A�ŏ���init_ai++;������!!!!!!!!!!
	//�֐����Ȃǂ����Ƒʖڂł��@���O�͑����ҏ�����(��{�����̃n���h���l�[��)
	
	/*
	// AI0 (aiSample)
	extern void aiSampleInit(AI_T &myAi);
	aiSampleInit(*init_ai);
	extern Action aiSample(int view[2*VISIBLE+1][2*VISIBLE+1]);
	init_ai->moveFunc = aiSample;
	// AI0

	// AI1 (aiTest)
	init_ai++;
	extern void aiTestInit(AI_T &myAi);
	aiTestInit(*init_ai);
	extern Action aiTest(int view[2*VISIBLE+1][2*VISIBLE+1]);
	init_ai->moveFunc = aiTest;
	// AI1
	*/



	//�ʒu�Ȃǂ̌���
	for(int i=0;i<AI_NUM;i++,ai++){//AI�̏�����

		do{//AI���ǂɏd�Ȃ�Ȃ��悤�ɔz�u
			ai->x=GetRand(WIDTH);
			ai->y=GetRand(HEIGHT);
		}while(Stage[ai->x][ai->y]==1 || ai->x<0 || ai->x>=WIDTH || ai->y<0 || ai->y>=HEIGHT || !distans_tag_ai(ai->x,ai->y));//7/27 zero:��ʊO�ɏo�������ꍇ���l��
		
		ai->takara_flag=0;
		//ai->x=i+1;
		//ai->y=HEIGHT-i-2;

		ai->s_x=(ai->x+0.5)*BOX;
		ai->s_y=(ai->y+0.5)*BOX;
		ai->act=STOP;
		ai->step=0;
		ai->life=1;
		ai->takara_time=0;
		ai->score=0;
		ai->score_t=0;


		if(ai->entry==1)Stage[ai->x][ai->y]=2;
	}
}