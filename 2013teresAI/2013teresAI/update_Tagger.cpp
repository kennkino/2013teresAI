#include "Data.h"

void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT],int speed){
	//8/3 zero�ǋL:�S�̈ړ����x��TAGGER_SPEED�Œ�`����
	tagger->step+=TAGGER_SPEED+speed;
	switch(tagger->act){
	case N:
		tagger->s_y-=TAGGER_SPEED+speed;
		break;
	case E:
		tagger->s_x+=TAGGER_SPEED+speed;
		break;
	case S:
		tagger->s_y+=TAGGER_SPEED+speed;
		break;
	case W:
		tagger->s_x-=TAGGER_SPEED+speed;
		break;
	case STOP:
		tagger->act=STOP; //	toshi : AI�Ɏ~�܂�Ƃ����I�������Ȃ������̂Œǉ�
	default:
		break;
	}
	tagger->x=tagger->s_x/BOX;
	tagger->y=tagger->s_y/BOX;
	
	if(Stage[tagger->x][tagger->y]==1){
		switch(tagger->act){//7/27 zero:�Փˌ�̍��W��i�s�����Ō��肷��悤�ɏC��
		case N:
			tagger->y++;
			break;
		case E:
			tagger->x--;
			break;
		case S:
			tagger->y--;
			break;
		case W:
			tagger->x++;
			break;
		default:
			break;
		}
		tagger->act=STOP;
		tagger->s_x=(tagger->x+0.5)*BOX;
		tagger->s_y=(tagger->y+0.5)*BOX;
	}

	if(tagger->step>=BOX){
		tagger->s_x=(tagger->x)*BOX+10;
		tagger->s_y=(tagger->y)*BOX+10;
		tagger->act=STOP;
		tagger->step=0;

	}

}