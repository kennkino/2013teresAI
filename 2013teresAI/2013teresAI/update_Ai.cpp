//１マス２０歩(ドット)ー＞０に更新
#include "Data.h"

void update_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT],Takara *takara,int speed){
	//8/3 zero追記:AIの移動速度をAI_SPEEDで定義した
	if(ai->takara_flag==1)//宝をもっていたら速度が落ちるああ
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
			takara->muteki=60*AI_NUM;
			ai->takara_flag=0;
			ai->act=STOP;
			ai->step=0;
		}
		break;
	case PICK:
		if(ai->x==takara->x&&ai->y==takara->y&&ai->takara_flag==0&&ai->muteki==0&&takara->muteki==0&&takara->drop==0){
			ai->takara_flag=1;
			takara->drop=1;
		}
		break;
	default:
		break;
	}
	ai->x=ai->s_x/BOX;
	ai->y=ai->s_y/BOX;
	//壁に衝突
	if(Stage[ai->x][ai->y]==1){
		switch(ai->act){//7/27 zero:衝突後の座標を進行方向で決定するように修正
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

	if(ai->step >= BOX){
		ai->s_x=(ai->x)*BOX+10;
		ai->s_y=(ai->y)*BOX+10;
		ai->act=STOP;
		ai->step=0;
	}
	if(ai->takara_flag==1){//宝を持っていた場合宝の場所を更新
		takara->x=ai->x;
		takara->y=ai->y;
		ai->takara_time++;
		ai->score++;
	}
	if(ai->muteki>0)
		ai->muteki--;
	if(takara->muteki>0)
		takara->muteki--;

	if((takara->x*2/WIDTH)<1){
		if((takara->y*2/HEIGHT)<1)
			takara->ich=2;
		else
			takara->ich=3;
	}else{
		if((takara->y*2/HEIGHT)<1)
			takara->ich=1;
		else
			takara->ich=4;
	}
}