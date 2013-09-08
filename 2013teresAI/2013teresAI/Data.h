#pragma once

#include "DxLib.h"
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;

#define AI_NUM 3
#define TAGGER_NUM 2
#define ROUND_MAX 100
#define TIME_LIMIT 20
//�X�e�[�W�̋K��
#define WIDTH 32
#define HEIGHT 24
//1�}�X�̑傫��
#define BOX (640/WIDTH)
//AI�̎��E#
#define VISIBLE 10
#define CENTER VISIBLE
//AI�̈ړ����x
#define AI_SPEED 4
//AI�̕�����������̑��x
#define AI_TAKARA_SPEED 2
//�S�̈ړ����x
#define TAGGER_SPEED 3
typedef enum{
	OPENING,
	SETTING,
	RUNNING,
	ENDING,
} Mode;

typedef enum{
	N,
	E,
	S,
	W,
	STOP,
	DROP,
	PICK,
} Action;

typedef struct{
	char name[100];//���O
	int Graph;//AI�̉摜
	Action (*moveFunc)(int view[2*VISIBLE+1][2*VISIBLE+1]);		// �s����Ԃ��֐�
	int x;//���Wx
	int y;//���Wy
	int s_x;//�h�b�g���x���̍��W(���炩�ȓ����j
	int s_y;//�h�b�g���x���̍��W(���炩�ȓ����j
	int step;//�����ړ�������
	Action act;//AI�̍s��
	int life;//
	int view[2*VISIBLE+1][2*VISIBLE+1];//
	int entry;
	int takara_flag;//��������Ă��邩
	int takara_time;//���ێ����Ă�������
} AI_T;

typedef struct{
	char name[100];//���O
	int Graph;
	Action (*moveFunc)(int tagger_x , int tagger_y,int Stage[WIDTH][HEIGHT]);		// �s����Ԃ��֐�
	int x;
	int y;
	int s_x;
	int s_y;
	int step;
	Action act;
} Tagger;

typedef struct{
	int x;
	int y;
	int drop;
}Takara;

#define STACK_MAX 100
typedef struct{
	Action a[STACK_MAX];
	unsigned int count;
}stack;

void push(stack *s, Action dir);
Action pop(stack *s);




int intro(AI_T *ai);
void make_Stage(int Stage[WIDTH][HEIGHT],Takara takara);
void init_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]);
void init_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
void draw(int stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger[],Takara takara);
Action next_Ai(int view[2*VISIBLE+1][2*VISIBLE+1]);
Action next_Tagger(Tagger tagger,int Stage[WIDTH][HEIGHT],AI_T ai[]);//toshi:����AI_T ai[]�ǉ�
void update_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT],Takara *takara,int speed);
void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]);
void setview_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
int death_Ai(AI_T ai,Tagger tagger);
void result(AI_T ai[],int death[]);
void update_stage(int Stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger[],Takara takara);
int ranking(AI_T ai[],int deth[]);//7/23 tao31 �ǉ�