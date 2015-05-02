/*
 * ClannadMix.c
 *
 *  Created on: 2015骞�鏈�9鏃�
 *      Author: yami
 */

/**
 * @file		ClannadMix.c
 * @author		yami
 * @date		2015-04-29 03:07:49
 * @brief
 * 杩欎釜鏄富绋嬪簭
 */

//#include	<SDL.h>
#include <stdio.h>

//int		test()
//{
//	//鏂板缓涓�釜绐楀彛
//	SDL_Window		*window;
//	SDL_Renderer	*renderer;	//绐楀彛鐨勬覆鏌撳櫒
//	SDL_Texture	*texture;	//绾圭悊,杩欎釜鏄‖浠跺姞閫熺殑
//	SDL_Surface	*surface;	//鍔犺浇鍥惧舰鏂囦欢鐨勮鍥�
//	int				i;
//
//	window		=	SDL_CreateWindow(
//			"ClannadMix",			//鏍囬
//			100,						//鍦ㄥ睆骞曠殑x鍧愭爣
//			100,					//鍦ㄥ睆骞曠殑Y鍧愭爣
//			800,					//绐楀彛瀹藉害
//			600,					//绐楀彛楂樺害
//			SDL_WINDOW_SHOWN		//鏄剧ず绐楀彛
//			);
//
//	//缁戝畾娓叉煋鍣�
//	renderer	=	SDL_CreateRenderer(
//			window,						//绐楀彛
//			0,							//绱㈠紩
//			SDL_RENDERER_ACCELERATED	//缁戝畾绫诲瀷
//			);
//
//	//鍔犺浇鍥惧舰瑙嗗浘
//	surface		=	SDL_LoadBMP("BG001.bmp");
//
//	//寰楀埌绾圭悊
//	texture		=	SDL_CreateTextureFromSurface(
//			renderer,			//娓叉煋鍣�
//			surface				//鍥惧舰瑙嗗浘
//			);
//
//	i = 30;
//	//寰幆30娆�
//	while(i){
//		//澶勭悊鍏朵粬浜嬩欢
//		SDL_Event	e;
//		SDL_PollEvent(&e);
//		//娓呭睆
//		SDL_RenderClear(renderer);
//		//鎶婄汗鐞嗙粯鍒跺埌娓叉煋鍣ㄤ腑
//		SDL_RenderCopy(renderer,texture,NULL,NULL);
//		//鎶婃覆鏌撳櫒鏇存柊
//		SDL_RenderPresent(renderer);
//
//		//绛夊緟0.1s
//		SDL_Delay(100);
//	}
//
//	//娓呯悊
//	//
//	SDL_FreeSurface(surface);
//	//閲婃斁绾圭悊
//	SDL_DestroyTexture(texture);
//	//閲婃斁娓叉煋鍣�
//	SDL_DestroyRenderer(renderer);
//	//閲婃斁绐楀彛
//	SDL_DestroyWindow(window);
//
//	return 0;
//}

#include	"Subsystem.h"

#ifdef	TEST_

extern int MouseV[800][600];
int inited = 0;
int w = 0;
int wv = 1;
int s = 0;
void* bmp;
static int render_update() {
	if(!inited) {
		bmp = bmp_func.InitFile(clannad,"BG001.bmp");
		inited = 1;
	}
	//clannad->DrawBMPFile(clannad,"BG001.bmp",0,0,800,600);
//	w+=wv;
//	if(w<0)
//		if(wv<0)
//			wv = 10;
//
//	if(w>800-10)
//		if(wv>0)
//			wv=-10;

//bmp_func.DrawBMPAlpha(clannad,bmp,0,0,w,600,0,0,w,600,0x80);
	int y;
	int x;

	if(w<0)
	if(wv<0)
	wv = 1;

	if(w>=20)
	if(wv>0)
	wv = -1;

	if(s>2)
	{
		w+=wv;
		s=0;
	}
	else {
		s++;
	}

	w = 2;

	for(y=0;y<30;y++) {
		for(x=0;x<40;x++) {
			int mx,my;
			int v;
			v = 0;
			for(my=0;my<20;my++) {
				for(mx=0;mx<20;mx++) {
					if(MouseV[mx+x*20][my+y*20]>0)
					if(s>1) {
						MouseV[mx+x*20][my+y*20]--;
					}
					if(MouseV[mx+x*20][my+y*20]>v)
					v = MouseV[mx+x*20][my+y*20];
				}
			}

			if(v>2)
			w = v;
			else
			w = 0;

			bmp_func.DrawBMPAlpha(
					clannad,
					bmp,
					x*20,
					y*20,
					20,
					20,
					x*20,
					y*20,
					w,
					w,
					0x80
			);
		}
	}

	return 0;
}

static int closing(void*sender) {
	bmp_func.Free(bmp);
	return 0;
}

#endif	/*TEST_*/

#ifdef		DEBUG_TEST_
//娴嬭瘯澶存枃浠�
#include	"test/Test.h"
#endif

int main(int c, char**v) {
	//test();
	clannad->Init();
#ifdef		TEST_
	clannad->RenderUpdate = render_update;		//娓叉煋鏇存柊
	clannad->Closing = (void*)closing;//鍏抽棴鏃堕棿
#else
#ifdef		DEBUG_TEST_
	clannad->RenderUpdate = test_render_update;
	clannad->Closing = test_closing;
	clannad->Update = test_update;
#endif
#endif		/*TEST_*/

	clannad->Loop(clannad);
	clannad->Close();
	return 0;
}
