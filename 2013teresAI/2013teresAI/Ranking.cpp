//AIの最終結果を出力する
//7/23 tao31 新規追加
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
	int j,hoge,Cr,score=0;
	int rank[AI_ENTRY]={-1};
	static int drawX=500;
	if(drawX==500){
		for(int i=0;i<AI_NUM;i++){
			j=i;
			//rank[i]=-1;
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
	for(int i=0;i<AI_ENTRY;i++)
		rank[i]=-1;

	for(int i=0,j=0;i<AI_NUM;i++,j++){
		for(int k=0;k<AI_NUM;k++){
			if(ai[i].score==ai[k].score_t&&ai[k].entry==1){
				if(i>0&&ai[i].score==ai[i-1].score&&rank[k]>0){
					j--;
					continue;
				}
				rank[j]=k;
				break;
			}
		}
	}


	ClearDrawScreen();

	for(int i=0,j=0;i<AI_NUM;i++,j++){
		if(ai[i].entry==0){
			j--;
			continue;
		}
		Cr = colswitch(i+1);
		DrawFormatString(100+drawX,50+j*100,Cr,"%d 位 %d pt",j+1,ai[i].score);
		DrawString(250+drawX,50+j*100,ai[rank[j]].name,GetColor(255,0,0));
		DrawRotaGraph(400+drawX,50+j*100,1,0,ai[rank[j]].Graph,TRUE,0);
		score+=ai[i].score;
	}
	if(drawX<=0)
		DrawFormatString(100+drawX,50+4*100,GetColor(255,255,255),"総合得点 %d pt",score);

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
			//main関数よりdeth[]を引数に取り、小さい順に並び替え
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
					DrawFormatString(100+drawX*space,50+space*35,Cr,"%d 位 %d 回",i+1,deth[i]);
					DrawString(250+drawX*space,50+space*35,ai[k].name,GetColor(255,0,0));
					DrawRotaGraph(400+drawX*space,50+space*35,1,0,ai[k].Graph,TRUE,0);
					space++;
				}
			}
		}
	}
	return 0;
}*/