#include "Data.h"

void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]){
	//8/3 zero追記:鬼の移動速度をTAGGER_SPEEDで定義した
	tagger->step+=TAGGER_SPEED;
	switch(tagger->act){//(1,-2)(1,-3)(2,-2)(2,-3)
	case N:
		tagger->s_y-=TAGGER_SPEED;
		break;
	case E:
		tagger->s_x+=TAGGER_SPEED;
		break;
	case S:
		tagger->s_y+=TAGGER_SPEED;
		break;
	case W:
		tagger->s_x-=TAGGER_SPEED;
		break;
	case STOP:
		tagger->act=STOP; //	toshi : AIに止まるという選択肢がなかったので追加
	default:
		break;
	}
	tagger->x=tagger->s_x/BOX;
	tagger->y=tagger->s_y/BOX;
	
	if(Stage[tagger->x][tagger->y]==1||Stage[tagger->x][tagger->y]==5/*||Stage[tagger->x][tagger->y]==4*/){
		switch(tagger->act){//7/27 zero:衝突後の座標を進行方向で決定するように修正
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