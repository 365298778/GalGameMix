/*
 * ClannadMix.c
 *
 *  Created on: 2015年4月29日
 *      Author: yami
 */


/**
 * @file		ClannadMix.c
 * @author		yami
 * @date		2015-04-29 03:07:49
 * @brief
 * 这个是主程序
 */


//#include	<SDL.h>

#include <stdio.h>




//int		test()
//{
//	//新建一个窗口
//	SDL_Window		*window;
//	SDL_Renderer	*renderer;	//窗口的渲染器
//	SDL_Texture	*texture;	//纹理,这个是硬件加速的
//	SDL_Surface	*surface;	//加载图形文件的视图
//	int				i;
//
//	window		=	SDL_CreateWindow(
//			"ClannadMix",			//标题
//			100,						//在屏幕的x坐标
//			100,					//在屏幕的Y坐标
//			800,					//窗口宽度
//			600,					//窗口高度
//			SDL_WINDOW_SHOWN		//显示窗口
//			);
//
//	//绑定渲染器
//	renderer	=	SDL_CreateRenderer(
//			window,						//窗口
//			0,							//索引
//			SDL_RENDERER_ACCELERATED	//绑定类型
//			);
//
//	//加载图形视图
//	surface		=	SDL_LoadBMP("BG001.bmp");
//
//	//得到纹理
//	texture		=	SDL_CreateTextureFromSurface(
//			renderer,			//渲染器
//			surface				//图形视图
//			);
//
//	i = 30;
//	//循环30次
//	while(i){
//		//处理其他事件
//		SDL_Event	e;
//		SDL_PollEvent(&e);
//		//清屏
//		SDL_RenderClear(renderer);
//		//把纹理绘制到渲染器中
//		SDL_RenderCopy(renderer,texture,NULL,NULL);
//		//把渲染器更新
//		SDL_RenderPresent(renderer);
//
//		//等待0.1s
//		SDL_Delay(100);
//	}
//
//	//清理
//	//
//	SDL_FreeSurface(surface);
//	//释放纹理
//	SDL_DestroyTexture(texture);
//	//释放渲染器
//	SDL_DestroyRenderer(renderer);
//	//释放窗口
//	SDL_DestroyWindow(window);
//
//	return 0;
//}


#include	"Subsystem.h"




#ifdef	TEST_

extern	int		MouseV[800][600];
int		inited	=	0;
int		w	=	0;
int		wv	=	1;
int		s	=	0;
void*	bmp;
static		int		render_update(){
	if(!inited){
		bmp		=	bmp_func.InitFile(clannad,"BG001.bmp");
		inited	=	1;
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
			wv	=	1;

	if(w>=20)
		if(wv>0)
			wv	=	-1;



	if(s>2)
	{
		w+=wv;
		s=0;
	}
	else{
		s++;
	}

	w	=	2;

	for(y=0;y<30;y++){
		for(x=0;x<40;x++){
			int	mx,my;
			int	v;
			v	=	0;
			for(my=0;my<20;my++){
				for(mx=0;mx<20;mx++){
					if(MouseV[mx+x*20][my+y*20]>0)
						if(s>1){
							MouseV[mx+x*20][my+y*20]--;
						}
					if(MouseV[mx+x*20][my+y*20]>v)
						v = MouseV[mx+x*20][my+y*20];
				}
			}

			if(v>2)
				w	=	v;
			else
				w	=	0;

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


static		int		closing(void*sender){
	bmp_func.Free(bmp);
	return 0;
}


#endif	/*TEST_*/


#ifdef		DEBUG_TEST_
//测试头文件
#include	"test/Test.h"
#endif


int		main(int c,char**v)
{
	//test();
	clannad->Init();
#ifdef		TEST_
	clannad->RenderUpdate		=	render_update;		//渲染更新
	clannad->Closing			=	(void*)closing;			//关闭时间
#else
#ifdef		DEBUG_TEST_
	clannad->RenderUpdate		=	test_render_update;
	clannad->Closing			=	test_closing;
	clannad->Update				=	test_update;
#endif
#endif		/*TEST_*/

	clannad->Loop(clannad);
	clannad->Close();
	return 0;
}
