#include"Data.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	//SetMouseDispFlag(TRUE);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetScreenMemToVramFlag(FALSE);
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen( DX_SCREEN_BACK);
	if(DxLib_Init()==-1)		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

	Mode gamemode=OPENING;
	AI_T ai[AI_NUM];
	int death[AI_NUM]={0};
	Tagger tagger[TAGGER_NUM];
	int tagger_num = 0;
	int STAGE[WIDTH][HEIGHT]={0};
	int round=0;
	int start=0;
	int end=0;
	int StartTime,TimeLimit;

	for(int i=0;i<AI_NUM;i++){
		ai[i].entry=1;
	}
	ai[0].entry=0;


	while(ProcessMessage()!=-1){
		switch(gamemode){
		case OPENING:
			start=intro(ai);
			if(start==1)gamemode=SETTING;
			break;
		case SETTING:
			make_Stage(STAGE);//マップ構成

			gamemode=RUNNING;
			break;
		case RUNNING:
			ClearDrawScreen();
			draw(STAGE,ai,tagger[tagger_num]);
			break;
		case ENDING:
			break;
		default:
			break;
		}
		if(end==1 || CheckHitKey(KEY_INPUT_ESCAPE))break;
		ScreenFlip();
	}

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}