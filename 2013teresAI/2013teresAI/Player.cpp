/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"

/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void PlayerInit(AI_T &myAi)
{
	myAi.Graph = LoadGraph("AI_image\\player.png");  //�摜�̐ݒ�
	strcpy_s(myAi.name, "Player");  //������AI�̖��O�ݒ�
}


/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
Action Player(int view[2*VISIBLE+1][2*VISIBLE+1])
{
	if(CheckHitKey(KEY_INPUT_UP)==1)return N;
	if(CheckHitKey(KEY_INPUT_RIGHT)==1)return E;
	if(CheckHitKey(KEY_INPUT_DOWN)==1)return S;
	if(CheckHitKey(KEY_INPUT_LEFT)==1)return W;
	return STOP;
}
