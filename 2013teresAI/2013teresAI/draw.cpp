#include "Data.h"

void draw(int stage[WIDTH][HEIGHT],AI_T ai[AI_NUM],Tagger tagger[TAGGER_NUM],Takara takara){
	int view=0;
	if(CheckHitKey(KEY_INPUT_V))view=1;// 8/19 zero:V�L�[�������Ă���ƕ`�惂�[�h���ς��܂��B
	static int stageGraph = LoadGraph("Stage_image\\kabe0.png"); //�ǂ̉摜�ǂݍ���
	//����stage�ɂ��������ă}�b�v�̕`��
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(view==0)SetDrawBright(150,150,150);// 8/19 zero: ���Â��`�ʂ���悤�ݒ�
			for(int k=0;k<AI_NUM;k++){// 8/19 zero: AI�̎��E�̂ݖ��邭�Ȃ�悤��
				if(i>=ai[k].x-VISIBLE && i<=ai[k].x+VISIBLE && j>=ai[k].y-VISIBLE && j<=ai[k].y+VISIBLE && ai[k].entry==1){
					SetDrawBright(255,255,255);
				}
			}
			if(i==WIDTH/2 || j==HEIGHT/2){//7/27 zero: �\����L��`���Ă�����Ƃ�������
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(100,100,250),0);
			}
			if(stage[i][j]==1){//�ǂ����ɔ��������`�Ƃ��Ă��܂��B//�y�̕ǂɂ��܂����B
//				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);//�l�p�̕`��
				DrawRotaGraph((20*i)+10,(20*j)+10,1.0,0.0,stageGraph,FALSE,FALSE);//�ǂݍ��񂾕ǉ摜�\��
			}
			if(stage[i][j]==4&&takara.drop==0){
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);//��̕`��
			}
			if(stage[i][j]==5){//�h���{�E�w�n�̕`��
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);
			}
		}
	}
	//AI�̕`��
	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1){
			SetDrawBright(255,255,255);
			DrawRotaGraph(ai[i].s_x,ai[i].s_y,1,0,ai[i].Graph,TRUE,FALSE);//�ǂݍ��񂾉摜�\��
			//DrawCircle(ai[i].s_x,ai[i].s_y,5,GetColor(255,0,0),1);//�_�\��
			if(view==1){
				DrawBox(BOX*ai[i].x,BOX*ai[i].y,BOX*(ai[i].x+1),BOX*(ai[i].y+1),GetColor(255,0,0),0);
				DrawBox(BOX*(ai[i].x-VISIBLE),BOX*(ai[i].y-VISIBLE),BOX*(ai[i].x+VISIBLE+1),BOX*(ai[i].y+VISIBLE+1),GetColor(255,255,255),0);//AI�̎��E�i�m�F�p�j
			}
		}
	}
	//�S�̕`��
	for(int i=0;i<TAGGER_NUM;i++){
	DrawRotaGraph(tagger[i].s_x,tagger[i].s_y,0.75,0,tagger[i].Graph,TRUE,FALSE);//�ǂݍ��񂾉摜�\�� //���͐S���o�Ă��ĕ|������R�����g�A�E�g
	//DrawCircle(tagger.s_x,tagger.s_y,20,GetColor(0,0,255),1);
	if(view==1)DrawBox(BOX*tagger[i].x,BOX*tagger[i].y,BOX*(tagger[i].x+1),BOX*(tagger[i].y+1),GetColor(255,0,0),0);
	}
	
	//AI���̕`��

	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1){
			static int flash=0;
			int cr;
			flash++;
			cr=GetColor(255,255*(flash%3),255*(flash%4));
			DrawFormatString(ai[i].s_x,ai[i].s_y,cr,ai[i].name);
		}
	}
	
	//�}�b�v�f�[�^�\��
	while(CheckHitKey(KEY_INPUT_P)==1){
		int ai_x[AI_NUM],ai_y[AI_NUM],ai_num=0;
		DrawBox(0,0,640,480,GetColor(0,0,0),1);
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<HEIGHT;j++){
				int cr;
				switch(stage[i][j]){
				case 1:
					cr=GetColor(100,50,0);
					break;
				case 2:
					cr=GetColor(255,0,0);
					ai_x[ai_num]=i;
					ai_y[ai_num]=j;
					ai_num++;
					break;
				case 3:
					cr=GetColor(0,0,100);
					break;
				default:
					cr=GetColor(0,0,0);
					break;
				}
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),cr,1);
				cr=GetColor(255,255,255);
				//DrawBox(20*i,20*j,20*(i+1),20*(j+1),cr,0);
				DrawFormatString(i*20+5,j*20+5,cr,"%d",stage[i][j]);
				
			}
		}
		for(int i=0;i<AI_NUM;i++){
			DrawBox(20*(ai_x[i]-10),20*(ai_y[i]-10),20*(ai_x[i]+10),20*(ai_y[i]+10),GetColor(255,255,0),0);
		}
		/*
		for(int i=0;i<AI_NUM;i++){
			for(int w=0;w<2*VISIBLE+1;w++){
				for(int h=0;h<2*VISIBLE+1;h++){
					int cx=20*ai[i].x+(w-VISIBLE)*20,cy=20*ai[i].y+(h-VISIBLE)*20;
					DrawFormatString(cx,cy,GetColor(255,255,255),"%d",ai[i].view[w][h]);
				}
			}
		}*/
		WaitTimer(100);
	}
	
	//�S���蓮���������\��
    char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;
	/*if( Buf[ KEY_INPUT_A ] == 1 ) {
		const char* str = strcat(tagger.name , "�S�蓮���[�h"); //������A��
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}else {
		const char* str = strcat(tagger.name , "�SAI���[�h"); //������A��
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}*/
}