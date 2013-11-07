/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"


/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void aiTestInit(AI_T &myAi)
{
	myAi.Graph = LoadGraph("AI_image\\red.png");
	strcpy_s(myAi.name, "aiTest");
}


/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
Action aiTest(int view[2*VISIBLE+1][2*VISIBLE+1],int takara_flag)//����m�F�p
{
	int takara_x=-1,takara_y=-1,takara=0;//takara=0(�󌩂��Ȃ�),1(�󌩂��Ă�),2(�󎝂��Ă�)
	int tagger_x = -1, tagger_y = -1;
	int sub_x, sub_y;
	int i, j;
	int danger=0;//danger=0(�S�������Ȃ�),1(�S�������Ă�)
	static int p_move=-1;//E=0S=1W=2N=3

	if(view[VISIBLE][VISIBLE]==6){
		return PICK;
	}

	for(i=0; i<2*VISIBLE+1; i++){
		for(j=0; j<2*VISIBLE+1; j++) {
			if(view[i][j] == 3) {
				tagger_x = i;
				tagger_y = j;
				danger=1;
			}
			if(view[i][j]==4){
				takara_x=i;
				takara_y=j;
				takara=1;
			}
		}
	}

	if(takara_flag==1){//��������Ă���ꍇ
		if(view[VISIBLE-1][VISIBLE]!=1&&p_move!=0)
			return W;
		else if(view[VISIBLE][VISIBLE+1]!=1&&p_move!=3)
			return S;
		else if(view[VISIBLE][VISIBLE-1]!=1){
			p_move=3;
			return N;
		}else{
			p_move=0;
			return E;
		}
		
	}else if(takara==1){//�󂪌����Ă���ꍇ
		sub_x=takara_x-VISIBLE;
		sub_y=takara_y-VISIBLE;
		if(abs(sub_x)<abs(sub_y)){
			if(sub_y>0){
				if(view[VISIBLE][VISIBLE+1]!=1)
					return S;
				else if(sub_x>0){
					if(view[VISIBLE+1][VISIBLE]!=1)
						return E;
				}else
					return W;
			}else{
				if(view[VISIBLE][VISIBLE-1]!=1)
					return N;
				else if(sub_x>0){
					if(view[VISIBLE+1][VISIBLE]!=1)
						return E;
				}else
					return W;
			}
		}else{
			if(sub_x>0)
				if(view[VISIBLE+1][VISIBLE]!=1)
					return E;
				else if(sub_y>0){
					if(view[VISIBLE][VISIBLE+1]!=1)
						return S;
				}else
					return N;
			else{
				if(view[VISIBLE-1][VISIBLE]!=1)
					return W;
				else if(sub_x>0){
					if(view[VISIBLE+1][VISIBLE]!=1)
						return E;
				}else
					return W;
			}
		}
	}else if(takara==0){
		if(danger==0){//�󂪌����ĂȂ��āA�S�������ĂȂ��ꍇ
			if(view[VISIBLE+1][VISIBLE]!=1&&p_move!=2)
				return E;
			else if(view[VISIBLE][VISIBLE-1]!=1&&p_move!=1)
				return N;
			else if(view[VISIBLE-1][VISIBLE]!=1){
				p_move=2;
				return W;
			}else{
				p_move=1;
				return S;
			}
		}

		sub_x = VISIBLE - tagger_x;
		sub_y = VISIBLE - tagger_y;
		
		if(abs(sub_x) < abs(sub_y)) {
			if(sub_x > 0)
				return E;
			else
				return W;
		} else {
			if(sub_y > 0)
				return S;
			else
				return N;
		}
	}

	return STOP;

	/*sub_x = VISIBLE - tagger_x;
	sub_y = VISIBLE - tagger_y;

	if(abs(sub_x) < abs(sub_y)) {
		if(sub_x > 0)
			return E;
		else
			return W;
	} else {
		if(sub_y > 0)
			return S;
		else
			return N;
	}*/
	
		/*
	int r;
	int cx=VISIBLE,cy=VISIBLE;
	int danger=0;
	double direct;
	double  PI=3.141592;
	int tx,ty;
	static Action go;

	for(int i=0;i<2*VISIBLE+1;i++){
		for(int j=0;j<2*VISIBLE+1;j++){
			if(view[i][j]==3){
				tx=i;
				ty=j;
				danger=1;
				int dx=cx-i;
				int dy=cy-j;
				if(dx==0){
					if(dy>=0){
						direct=90;
					}else{
						direct=-90;
					}
				}
				else{
					double t=dy/dx;
					if(dx>0){
						direct=atan(t)/PI*180;
					}
					else{
						direct=atan(t)/PI*180+180;
					}
				}
			}
		}
	}

	if(danger==0){
		int r=GetRand(4);
		switch(r%4){
		case 0:
			if(view[cx][cy-1]!=1)
			return N;
			break;
		case 1:
			if(view[cx+1][cy]!=1)
			return E;
			break;
		case 2:
			if(view[cx][cy+1]!=1)
			return S;
			break;
		case 3:
			if(view[cx-1][cy]!=1)
			return W;
			break;
		}
	}
	else{
		if(direct<-45){
			if(view[cx][cy-1]!=1)
				return N;
			else{
				if(view[cx+1][cy]!=1){
					return E;
				}
				else if(view[cx-1][cy]!=1){
					return W;
				}else{
					return S;
				}
			}
		}
		else if(direct<45){
			if(view[cx+1][cy]!=1)
				return E;
			else{
				if(view[cx][cy+1]!=1){
					return S;
				}
				else if(view[cx][cy-1]!=1){
					return N;
				}else{
					return W;
				}
			}
		}
		else if(direct<135){
			if(view[cx][cy+1]!=1)
				return S;
			else{
				if(view[cx-1][cy]!=1){
					return W;
				}
				else if(view[cx+1][cy]!=1){
					return E;
				}else{
					return N;
				}
			}
		}
		else if(direct<225){
			if(view[cx-1][cy]!=1)
				return W;
			else{
				if(view[cx][cy-1]!=1){
					return N;
				}
				else if(view[cx][cy+1]!=1){
					return S;
				}else{
					return E;
				}
			}
		}
		else{
			if(view[cx][cy-1]!=1)
				return N;
			else{
				if(view[cx+1][cy]!=1){
					return E;
				}
				else if(view[cx-1][cy]!=1){
					return W;
				}else{
					return S;
				}
			}
		}
		return STOP;
	}
	*/
}
