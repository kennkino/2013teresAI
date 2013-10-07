//AI�̍ŏI���ʂ��o�͂���
//7/23 tao31 �V�K�ǉ�
#include "Data.h"


int colswitch(int c){
	int Cr;
	switch(c){
	case 1: Cr = GetColor(238,185,15);
		break;
	case 2:Cr = GetColor(165,165,165);
		break;
	case 3: Cr = GetColor(202,176,55);
		break;
	default: Cr = GetColor(100,100,100);
		break;
	}
	return Cr;
}

int ranking(AI_T ai[],int deth[]){
	int j,hoge,Cr;
	static int drawX=500;
	if(drawX==500){
		for(int i=0;i<AI_NUM;i++){
			j=i;
			ai[i].score_t=ai[i].score;
			while(j>0){
				if(ai[j].score>ai[j-1].score){
					hoge=ai[j-1].score;
					ai[j-1].score=ai[j].score;
					ai[j].score=hoge;
				}
				j--;
			}
		}
	}
	
	if(drawX>0)drawX-=10;

	ClearDrawScreen();

	for(int i=0;i<AI_NUM;i++){
		for(int j=0;j<AI_NUM;j++){
			if(ai[i].score==ai[j].score_t){
				if(i>0 && ai[i-1].score==ai[i].score)continue;
				Cr = colswitch(i+1);
				DrawFormatString(100+drawX,50+i*100,Cr,"%d �� %d pt",i+1,ai[i].score);
				DrawString(250+drawX,50+i*100,ai[j].name,GetColor(255,0,0));
				DrawRotaGraph(400+drawX,50+i*100,1,0,ai[j].Graph,TRUE,0);
			}
		}
	}

	if(GetMouseInput()==1){
		return 1;
	}
	
	return 0;
}

/*int ranking(AI_T ai[],int deth[]){
	int hoge,Cr;
	int j ;
	int space=0;
	static int drawX=500,time=100;
	if(drawX==500){
		for(int i=0;i<AI_NUM;i++){
			if(ai[i].entry==0)deth[i]=ROUND_MAX+1;
			ai[i].life = deth[i];
			j=i;
			//main�֐����deth[]�������Ɏ��A���������ɕ��ёւ�
			while(j>0&&deth[j-1]>deth[j]){
				hoge = deth[j-1];
				deth[j-1] = deth[j];
				deth[j] = hoge;
				j--;
			}
		}
	}
	space=1;
	
	if(drawX>0)drawX-=10;

	if(drawX<=0){
		if(time>0)time--;
		if(GetMouseInput()==1 && time<=0){
			return 1;
		}
	}
	ClearDrawScreen();

	for(int i = 0;i<AI_NUM;i++){
		for(int k=0;k<AI_NUM;k++){
			if(ai[k].life==deth[i]){
				if(i>0 && deth[i-1]==deth[i])continue;
				if(deth[i]<=ROUND_MAX){
					Cr = colswitch(i+1);
					DrawFormatString(100+drawX*space,50+space*35,Cr,"%d �� %d ��",i+1,deth[i]);
					DrawString(250+drawX*space,50+space*35,ai[k].name,GetColor(255,0,0));
					DrawRotaGraph(400+drawX*space,50+space*35,1,0,ai[k].Graph,TRUE,0);
					space++;
				}
			}
		}
	}
	return 0;
}*/