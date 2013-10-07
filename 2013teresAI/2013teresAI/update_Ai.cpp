//�P�}�X�Q�O��(�h�b�g)�[���O�ɍX�V
#include "Data.h"

void update_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT],Takara *takara,int speed){
	//8/3 zero�ǋL:AI�̈ړ����x��AI_SPEED�Œ�`����
	if(ai->takara_flag==1)//��������Ă����瑬�x�������邠��
		speed=AI_TAKARA_SPEED;
	else
		speed=AI_SPEED;
	ai->step+=speed;
	
	switch(ai->act){
	case N:
		ai->s_y-=speed;
		break;
	case E:
		ai->s_x+=speed;
		break;
	case S:
		ai->s_y+=speed;
		break;
	case W:
		ai->s_x-=speed;
		break;
	case DROP:
		if(ai->takara_flag==1){
			takara->x=ai->x;
			takara->y=ai->y;
			takara->drop=0;
			ai->takara_flag=0;
			ai->act=STOP;
			ai->step=0;
		}
		break;
	case PICK:
		if(ai->x==takara->x&&ai->y==takara->y&&ai->takara_flag==0){
			ai->takara_flag=1;
			takara->drop=1;
		}
		break;
	default:
		break;
	}
	ai->x=ai->s_x/BOX;
	ai->y=ai->s_y/BOX;
	//�ǂɏՓ�
	if(Stage[ai->x][ai->y]==1){
		switch(ai->act){//7/27 zero:�Փˌ�̍��W��i�s�����Ō��肷��悤�ɏC��
		case N:
			ai->y++;
			break;
		case E:
			ai->x--;
			break;
		case S:
			ai->y--;
			break;
		case W:
			ai->x++;
			break;
		case STOP:
			ai->x=GetRand(WIDTH);
			ai->y=GetRand(HEIGHT);
			break;
		}
		ai->act=STOP;
		ai->s_x=(ai->x+0.5)*BOX;
		ai->s_y=(ai->y+0.5)*BOX;
	}

	if(ai->step==BOX){
		ai->act=STOP;
		ai->step=0;
	}
	if(ai->takara_flag==1){
		takara->x=ai->x;
		takara->y=ai->y;
		ai->takara_time++;
		ai->score++;
	}

}