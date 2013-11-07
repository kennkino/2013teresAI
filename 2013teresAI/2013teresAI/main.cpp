#include "Data.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	//SetMouseDispFlag(TRUE);
	SetMainWindowText("調布祭AI対戦2013") ;
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetScreenMemToVramFlag(FALSE);
	SetAlwaysRunFlag(TRUE);
	SetDrawScreen( DX_SCREEN_BACK);
	if(DxLib_Init()==-1)		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

	//デバック用にコンソールを出現させる
	/*
	AllocConsole();
	freopen("CONOUT$","w",stdout);
	freopen("CONIN$","r",stdin);z
	*/

	Mode gamemode=OPENING;
	AI_T ai[AI_NUM];
	Takara takara;
	int death[AI_NUM]={0};
	Tagger tagger[TAGGER_NUM];
	int tagger_num = 0;
	int STAGE[WIDTH][HEIGHT]={0};
	int round=0;
	int start=0;
	int end=0;
	int StartTime,TimeLimit;

	for(int i=0;i<AI_NUM;i++){
		ai[i].entry=0;
	}

	while(ProcessMessage()!=-1){
		int speed=0;
		switch(gamemode){
		case OPENING:
			start=intro(ai,takara);
			if(start==1)gamemode=SETTING;
			break;
		case SETTING:
			make_Stage(STAGE,takara);//マップ構成
			do{
			takara.x=GetRand(WIDTH/2-2)+WIDTH/2;
			takara.y=GetRand(HEIGHT/2-1)+1;
			}while(STAGE[takara.x][takara.y]==1);
			takara.ich=0;
			takara.drop=0;
			takara.muteki=0;
			init_Tagger(tagger,STAGE,takara);//鬼の初期化 //tagger_numは鬼の要素番号

			init_Ai(ai,STAGE);

			round++;
			TimeLimit=TIME_LIMIT*60*79;//ゲーム開始時の時刻に合わせる
			gamemode=RUNNING;

			break;
		case RUNNING:
			TimeLimit-=79;
			if(TimeLimit<0)TimeLimit=0;
			for(int i=0;i<TAGGER_NUM;i++){
				if(tagger[i].step==0){
					//tagger[tagger_num].act=next_Tagger(tagger[tagger_num],STAGE,ai);
					tagger[i].act=tagger[i].moveFunc(tagger[i].x,tagger[i].y,STAGE,takara); //AIと一緒で、moveFunc使う
				}
			}
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].step == 0 && ai[i].entry==1){
					setview_Ai(&ai[i],STAGE);
					//ai[i].act=next_Ai(ai[i].view); //henteko : 下のmoveFunc()を使うためコメントアウト
					ai[i].act = ai[i].moveFunc(ai[i].view,takara.ich);
				}
			}
			/*if(TimeLimit>TIME_LIMIT*45*79)speed=0;
			else if(TimeLimit>TIME_LIMIT*30*79)speed=1;
			else if(TimeLimit>TIME_LIMIT*15*79)speed=1;
			else speed=3;*/
			for(int i=0;i<TAGGER_NUM;i++){
				update_Tagger(&tagger[i],STAGE);
			}
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].entry==1){
					update_Ai(&ai[i],STAGE,&takara,speed);
					if(ai[i].life==1){//捕まった場合
						ai[i].x=1;
						ai[i].y=HEIGHT-2;
						ai[i].s_x=(ai[i].x+0.5)*BOX;
						ai[i].s_y=(ai[i].y+0.5)*BOX;
						ai[i].act=STOP;
						ai[i].step=0;
						STAGE[ai[i].x][ai[i].y]=2;
						TimeLimit-=1000;//時間ペナルティ
						ai[i].score-=100;//点数ペナルティ
						ai[i].muteki=60;//捕まって数ターンは敵に見つからない
						ai[i].life=0;
					}
				}
			}
			update_stage(STAGE,ai,tagger,takara);
			
			ClearDrawScreen();
			draw(STAGE,ai,tagger,takara);
			DrawFormatString(30,30,GetColor(0,255,255),"ROUND%d",round);
			
			DrawFormatString(500,15,GetColor(0,255,0),"TIME %d",TimeLimit);
			
			if(1){
				for(int i=0;i<AI_NUM;i++){
					for(int j=0;j<TAGGER_NUM;j++){
						if(death_Ai(ai[i],tagger[j])==1 && ai[i].entry==1){
							death[i]++;
							DrawBox(0,230,640,260,GetColor(0,0,0),1);
							DrawBox(-1,230,642,260,GetColor(255,0,0),0);
							DrawFormatString(100,240,GetColor(255,0,0),"%sがつかまりました",ai[i].name);// 8/3 zero追記:AI捕獲の宣言をまとめた。


							
							if(ai[i].takara_flag==1){//宝を持っていた時
								takara.x=ai[i].x;
								takara.y=ai[i].y;
								takara.drop=0;
								takara.muteki=60*AI_NUM;
								ai[i].takara_flag=0;
								ai[i].score-=400;
							}
							ai[i].life=1;
						}
					}
					if(ai[i].takara_flag==1&&STAGE[ai[i].x][ai[i].y]==5/*&&ai[i].x<3&&ai[i].y>HEIGHT-4*/){//クリア判定
						ai[i].score+=1000;
						WaitTimer(3000);
						if(round>=ROUND_MAX){
							gamemode=ENDING;
						}else{
							gamemode=SETTING;
						}
						break;
					}
				}
			}
			if(TimeLimit<=0){// 8/3 zero追記:タイムアップを設定
				//round--;
				DrawString(100,240,"時間切れです",GetColor(255,0,0));
				WaitTimer(3000);
				if(round>=ROUND_MAX){
					gamemode=ENDING;
				}
				else{
					gamemode=SETTING;
				}
				break;
			}
			if(CheckHitKey(KEY_INPUT_R)==1){
				gamemode=SETTING;
			}
			break;
		case ENDING:
			end=ranking(ai,death);
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