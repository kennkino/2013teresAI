#include "Data.h"

void update_stage(int Stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger[],Takara takara){
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(i==0 || j==0 || i==WIDTH-1 || j==HEIGHT-1){
				Stage[i][j]=1;
			}
			if(Stage[i][j]!=1)Stage[i][j]=0;
		}
	}
	if(takara.drop==0&&takara.muteki==0)
		Stage[takara.x][takara.y]=4;

	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1&&ai[i].muteki==0){
			Stage[ai[i].x][ai[i].y]=2;
			if(ai[i].x==takara.x&&ai[i].y==takara.y&&takara.drop==0)
				Stage[ai[i].x][ai[i].y]=6;
		}
		else 
			Stage[ai[i].x][ai[i].y]=0;
			
	}

	for(int i=0;i<TAGGER_NUM;i++){
		Stage[tagger[i].x][tagger[i].y]=3;
	}

	
	Stage[1][HEIGHT-2]=5;Stage[1][HEIGHT-3]=5;Stage[2][HEIGHT-2]=5;Stage[2][HEIGHT-3]=5;
}