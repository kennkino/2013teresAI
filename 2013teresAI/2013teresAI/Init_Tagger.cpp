/*�S������������֐��ł��B*/
#include "Data.h"

void init_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]){


	Tagger *init_tagger = tagger;
	/***************************************
	*�{�ԂŁA�N���S����邩�����_���Ō��肷��
	***************************************/
	/*int tagger_num = 0;
	do{
		tagger_num = GetRand(TAGGER_NUM); //�{�Ԃ̋S�̗v�f�ԍ�

	}while(tagger_num == TAGGER_NUM); //TAGGER_NUM�̔ԍ����I�΂�Ȃ��悤��*/

	// Tagger��ύX����Ƃ��ɂ�����ꏊ

	//	�e���v��
	//	extern void !�������֐���!(Tagger &myTagger);
	//	!�������֐���!(tagger[!tagger�̔ԍ�!]);
	//	extern Action !�ړ��֐���!(Tagger tagger,int Stage[WIDTH][HEIGHT],AI_T ai[]);
	//	init_tagger->moveFunc = !�ړ��֐���!;
	//!!![�d�v]!!!!��ԏ���(taggerSample)�ȊO�A�ŏ���init_tagger++;������!!!!!!!!!!
	//�֐����Ȃǂ����Ƒʖڂł��@���O�͑����ҏ�����(��{�����̃n���h���l�[��)
	
	// Tagger0 (taggerSample)
	extern void taggerSampleInit(Tagger &myTagger);
	taggerSampleInit(*init_tagger);
	extern Action taggerSample(int tagger_x,int tagger_y,int Stage[WIDTH][HEIGHT]);
	init_tagger->moveFunc = taggerSample;
	// Tagger0

	init_tagger++;  //���̐l�p�ɃC���N�������g

	// Tagger1 (taggerTest)
	extern void taggerTestInit(Tagger &myTagger);
	taggerTestInit(*init_tagger);
	extern Action taggerTest(int tagger_x,int tagger_y,int Stage[WIDTH][HEIGHT]);
	init_tagger->moveFunc = taggerTest;
	// Tagger1

	init_tagger++;  //���̐l�p�ɃC���N�������g

	


	/**********************************
	*�S�̈ʒu�Ȃǂ�����������
	**********************************/
	//tagger += tagger_num; //tagger_num�𑫂����ƂŁA�S�Ɏw�����ꂽ�l�̂ݏ��������܂�

	for(int i=0;i<TAGGER_NUM;i++,tagger++){

	tagger->x=WIDTH/2;
	tagger->y=HEIGHT/2;
	tagger->s_x=tagger->x*BOX+BOX/2;
	tagger->s_y=tagger->y*BOX+BOX/2;
	tagger->act=STOP;
	tagger->step=0;
	Stage[tagger->x][tagger->y]=3;
	}
	
	//return tagger_num; //�S�̗v�f�ԍ���Ԃ�
}