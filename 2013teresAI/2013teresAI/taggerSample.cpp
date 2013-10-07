/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"

/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void taggerSampleInit(Tagger &myTagger)
{
	myTagger.Graph = LoadGraph("Tagger_image\\chaser.png");  //�摜�̐ݒ�
	strcpy_s(myTagger.name, "Chaser");  //������AI�̖��O�ݒ�
}
/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
Action taggerSample(int tagger_x,int tagger_y,int Stage[WIDTH][HEIGHT],Takara takara)
{

	//�󕨂͈̔͂ɓ����Ă��܂����ꍇ
	if(takara.drop==0){
		if(tagger_x==takara.x&&tagger_y==takara.y-1){//�󕨂̏�
			if(Stage[tagger_x][tagger_y-1]!=1)
				return N;
			else if(Stage[tagger_x-1][tagger_y]!=1)
				return W;
			else if(Stage[tagger_x+1][tagger_y]!=1)
				return E;
			else
				return STOP;
		}
		if(tagger_x==takara.x&&tagger_y==takara.y+1){//�󕨂̉�
			if(Stage[tagger_x][tagger_y+1]!=1)
				return S;
			else if(Stage[tagger_x-1][tagger_y]!=1)
				return W;
			else if(Stage[tagger_x+1][tagger_y]!=1)
				return E;
			else
				return STOP;
		}
		if(tagger_x==takara.x-1&&tagger_y==takara.y){//�󕨂̍�
			if(Stage[tagger_x-1][tagger_y]!=1)
				return W;
			else if(Stage[tagger_x][tagger_y-1]!=1)
				return N;
			else if(Stage[tagger_x][tagger_y+1]!=1)
				return S;
			else
				return STOP;
		}
		if(tagger_x==takara.x+1&&tagger_y==takara.y){//�󕨂̉E
			if(Stage[tagger_x+1][tagger_y]!=1)
				return E;
			else if(Stage[tagger_x][tagger_y-1]!=1)
				return N;
			else if(Stage[tagger_x][tagger_y+1]!=1)
				return S;
			else
				return STOP;
		}
	}

	
	//�L�[��������Ă��邩�ǂ���
	char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;

	if( Buf[ KEY_INPUT_A ] == 0 ){//A��������Ă��Ȃ�
		int stage_cp[WIDTH][HEIGHT];
		int ai_x[AI_NUM],ai_y[AI_NUM],ai_n=0;
		int target_x,target_y;
		
		static stack *st = (stack*)malloc(sizeof(stack));
		static int stackInitFlag = 1;

		if(stackInitFlag){
			stackInitFlag = 0;
			st->count = 0;
		}

		// �����ʒu�ɂ��� �� �Q�[���J�n���i��������Ȃ��j
		if(tagger_x == WIDTH/2 && tagger_y == HEIGHT/2)
		{
			//DrawString( 50, 100, "Center", 0xffffff);
			//WaitTimer(500);
			st->count = 0; // �X�^�b�N����ɂ���
		}
		if(st->count > 0)return pop(st);

		for(int i=0;i<AI_NUM;i++){
			ai_x[i]=0;
			ai_y[i]=0;
		}

		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<HEIGHT;j++){
				if(Stage[i][j]==0){
					stage_cp[i][j]=0;
				}
				if(Stage[i][j]==1){
					stage_cp[i][j]=-1;
				}
				if(Stage[i][j]==2){
					ai_x[ai_n]=i;
					ai_y[ai_n]=j;
					ai_n++;
					stage_cp[i][j]=0;
				}
				if(Stage[i][j]==3){
					stage_cp[i][j]=1;
				}
				if(Stage[i][j]==4){
					stage_cp[i][j]=2;
				}
				if(Stage[i][j]==5){
					stage_cp[i][j]=3;
				}
			}
		}
		int step=1;
		if(ai_n == 0) return STOP;
		do{
			for(int i=0;i<WIDTH;i++){
				for(int j=0;j<HEIGHT;j++){
					if(stage_cp[i][j]==step){
						if(stage_cp[i-1][j]==0)stage_cp[i-1][j]=step+1;
						if(stage_cp[i+1][j]==0)stage_cp[i+1][j]=step+1;
						if(stage_cp[i][j-1]==0)stage_cp[i][j-1]=step+1;
						if(stage_cp[i][j+1]==0)stage_cp[i][j+1]=step+1;
					}
				}
			}
			int flag=0;
			for(int i=0;i<AI_NUM;i++){
				if(stage_cp[ai_x[i]][ai_y[i]]>0){
					target_x=ai_x[i];
					target_y=ai_y[i];
					flag=1;
				}
			}
			step++;
			if(flag==1)break;
		}while(1);
		
		int rand=GetRand(5)+4;
		for(; step>1; step--){
			if(stage_cp[target_x-1][target_y]==step-1){
				if(step<rand)
					push(st,E);
				target_x--;
			}
			else if(stage_cp[target_x+1][target_y]==step-1){
				if(step<rand)
					push(st,W);
				target_x++;
			}
			else if(stage_cp[target_x][target_y+1]==step-1){
				if(step<rand)
					push(st,N);
				target_y++;
			}
			else if(stage_cp[target_x][target_y-1]==step-1){
				if(step<rand)
					push(st,S);
				target_y--;
			}
			else {
				st->count = 0;
				return STOP;
			}
		}		
		return pop(st);
	}
	else{//A��������Ă���
		if( Buf[ KEY_INPUT_UP ] == 1 || Buf[ KEY_INPUT_N ] == 1 )//N������������Ă���
			return N;
		else if( Buf[ KEY_INPUT_RIGHT ] == 1 || Buf[ KEY_INPUT_E ] == 1 )//�d�������������Ă���
			return E;
		else if( Buf[ KEY_INPUT_DOWN ] == 1 || Buf[ KEY_INPUT_S ] == 1 )//S������������Ă���
			return S;
		else if( Buf[ KEY_INPUT_LEFT ] == 1 || Buf[ KEY_INPUT_W ] == 1 )//W������������Ă���
			return W;
		else 
			return STOP;//����������Ă��Ȃ�
	}
	return STOP;

}
