/*�X�e�[�W�������_����������֐��ł��B*/
#include "Data.h"

int miti[WIDTH][HEIGHT]={1}; /*1�ŕǁA0�ŒʘH�i���ǂ���Ȃ����A�u������Ă��Ȃ��j*/

void notWall(int Stage2[WIDTH][HEIGHT]){
	
	int i=0;
	while(i<=20){
		for(int x=0;x<WIDTH;x++){
			for(int y=0;y<HEIGHT;y++){
				if(Stage2[x][y]== 0 &&( miti[x+1][y]==0 
									||  miti[x-1][y]==0
									||  miti[x][y+1]==0
									||  miti[x][y-1]==0))
								miti[x][y] = 0;
			}
		}
		for(int x=WIDTH;x>0;x--){
			for(int y=HEIGHT;y<0;y--){
				if(Stage2[x][y]== 0 &&( miti[x+1][y]==0 
									||  miti[x-1][y]==0
									||  miti[x][y+1]==0
									||  miti[x][y-1]==0))
								miti[x][y] = 0;
			}
		}
		i++;
	}
}

void make_Stage(int Stage[WIDTH][HEIGHT],Takara takara){
	for(int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			miti[x][y]=1;
			if(GetRand(3)==0){
				Stage[x][y]=1;
			}
			else{
				Stage[x][y]=0;
			}
			if(x==WIDTH/2 || y==HEIGHT/2){
				Stage[x][y]=0;
				miti[x][y]=0;
			}
			if(x==2 || y==2 || x==WIDTH-3 || y==HEIGHT-3 || (x<3&&HEIGHT-4<y) ){
				Stage[x][y]=0;
			}
			if(x==0 || y==0 || x==WIDTH-1 || y==HEIGHT-1){
				Stage[x][y]=1;
			}
			if(x==takara.x&&y==takara.y){
				Stage[x][y]=4;
				miti[x][y]=0;
			}
			//(1,-2)(1,-3)(2,-2)(2,-3)�h���{�E�w�n
		}
	}
	

	notWall(Stage); /*�ʘH����*/

	for(int x=0;x<WIDTH;x++){ /*�u�����ꂽ�Ƃ����ǂɂ���*/
		for(int y=0;y<HEIGHT;y++){
			if(Stage[x][y]==0 && miti[x][y]==1)
				Stage[x][y] = 1;
		}
	}

}