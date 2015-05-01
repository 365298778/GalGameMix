/*
 * Subsystem.c
 *
 *  Created on: 2015年4月29日
 *      Author: yami
 */


/**
 * @file		Subsystem.c
 * @date		2015-04-29 11:33:45
 * @date		2015-04-29 11:34:19
 * @brief
 * 对于一些某些平台
 */




#include "Subsystem.h"

#ifdef	USE_SDL_
//SDL为了跨大部分的平台
#include		<SDL.h>

#include		<stdio.h>
#include		<stdlib.h>



typedef	struct{
	SDL_Window			*window;			//只能存在一个
	SDL_Renderer		*renderer;		//只能存在一个
}Clannad_Internal;



int		Clannad_Init();
int		Clannad_Loop();
int		Clannad_Close();
int		Clannad_DrawBMPfile();

Clannad		_clannad	=	{
		//state
		{
				0,
				.frame_wait_ticks	=	16,
		},
		//config
		{
				.show_state			=	1,		//显示状态,这个必须非0,才能使用下列显示
				.show_frame			=	1,		//显示帧数
				.show_game_time		=	1,		//显示游戏时间
		},
		0,			//internal
		.Init	=	Clannad_Init,			//初始化处理
		.Close	=	Clannad_Close,			//关闭处理
		.Loop	=	Clannad_Loop,			//循环
		.DrawBMPFile	=	Clannad_DrawBMPfile,		//绘制文件
		.Update	=	NULL,					//更新事件,只要把这个设置为自己的更新函数就行了

};

Clannad		*clannad	=	&_clannad;


int		Clannad_Init(){
	//因为只有一个窗体,只能绑定一个渲染器
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	//初始化SDL引擎
	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
		return 1;
	}
	window		=	SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	//如果内部是空,则申请内存,并初始化
	if(!clannad->Internal){
		clannad->Internal	=	SDL_calloc(
				1,
				sizeof(Clannad_Internal)
				);
		//初始化失败
		if(!clannad->Internal){
			return 1;
		}
	}


	if(!window){
		return 1;
	}


	//创建渲染器
	renderer	=	SDL_CreateRenderer(
			window,
			0,
			SDL_RENDERER_ACCELERATED
			);

	if(!renderer)
	{
		return 1;
	}

	//正确返回
	((Clannad_Internal*)(clannad->Internal))->window
			=	window;
	((Clannad_Internal*)(clannad->Internal))->renderer
			=	renderer;

	return 0;
}


int		Clannad_Close(){
	Clannad_Internal	*internal;
	internal	=	clannad->Internal;
	clannad->state.end_flag		=	1;
	if(clannad->Closing)
		clannad->Closing(clannad);
	if(internal){
		if(internal->renderer)
			SDL_DestroyRenderer(internal->renderer);
		if(internal->window)
			SDL_DestroyWindow(internal->window);
		SDL_free(internal);
		clannad->Internal	=	NULL;
	}
	return 0;
}


#ifdef TEST_
int		test_render(SDL_Renderer*renderer){
	SDL_Rect	rect;
	rect.x	=
			rect.y
			=	0;
	rect.w	=
			rect.h
			=	30;
	SDL_RenderDrawRect(renderer,&rect);
	SDL_RenderDrawLine(renderer,0,0,30,30);
	return 0;
}

int		MouseV[800][600] = {0};

#endif


int		Clannad_Loop(Clannad *clannad_data){
	Clannad_Internal	*internal;
	Clannad_state		*state;
	internal	=	clannad_data->Internal;
	if(internal){
		state	=	&clannad_data->state;
		while(!state->end_flag){
			//如果不是退出标识,则循环
			SDL_Event	e;
			u32			c_ticks;
			if(SDL_PollEvent(&e)){
				if(e.type==SDL_QUIT){
					state->end_flag	=	1;
				}
			}

			//处理更新函数
			if(clannad_data->Update)
				clannad_data->Update(clannad_data);

			c_ticks		=	SDL_GetTicks();		//获得时钟


			if(
					(c_ticks-state->last_ticks)>state->frame_wait_ticks
					){
				//记录现在帧时钟
				state->last_ticks		=	c_ticks;
				//为了加快速度而牺牲一些存储
				state->current_ticks	=	c_ticks;
			}
			else{
				//等待时钟
				u32		wait_ticks;
				wait_ticks				=	(state->last_ticks+state->frame_wait_ticks)
												-	c_ticks;

#ifdef	TEST_
				while(1){
					SDL_PollEvent(&e);
					if(e.type == SDL_MOUSEMOTION){
						//titleptr	+=	sprintf(titleptr,"X:%04d|Y:%04d",e.motion.x,e.motion.y);
						MouseV[e.motion.x][e.motion.y]	=	20;
					}
					SDL_Delay(2);
					if(wait_ticks>2)
						wait_ticks -= 2;
					else
						break;
				}
#endif

				//SDL_Delay(wait_ticks);
				//为了加快速度而牺牲一些存储
				state->current_ticks	=	SDL_GetTicks();
				state->last_ticks		=	state->current_ticks;

			}

			state->fcs	++;	//当前秒帧计数
			state->fc	++;	//帧计数

			if(clannad_data->config.show_state)
			{
				char	title[0x50];
				char	*titleptr;
				titleptr	=	title;
				titleptr	+=	sprintf(title,"%-20s",WINDOW_TITLE);
				if(clannad_data->config.show_frame)
				{
					titleptr	+=	sprintf(titleptr,"fps:%04d%5s",state->fps,"");
				}

				if(clannad_data->config.show_game_time){
					titleptr	+=	sprintf(titleptr,"game time:%04d",state->second);
				}

#ifdef	TEST_
				if(e.type == SDL_MOUSEMOTION){
					titleptr	+=	sprintf(titleptr,"X:%04d|Y:%04d",e.motion.x,e.motion.y);
					MouseV[e.motion.x][e.motion.y]	=	20;
				}

#endif

				SDL_SetWindowTitle(internal->window,title);
			}

			if(state->current_ticks-state->last_second_ticks>1000){
				//秒计数

				state->second	++;
				state->last_second_ticks	=	state->current_ticks;
				state->fps					=	state->fcs;
				state->fcs					=	0;
			}
			SDL_RenderClear(internal->renderer);

			//处理更新函数
			if(clannad_data->RenderUpdate)
				clannad_data->RenderUpdate(clannad_data);

			SDL_SetRenderDrawColor(internal->renderer,0xff,0,0,0xff);
#ifdef	TEST_
			test_render(internal->renderer);
#endif
			//这是以黑屏为背景
			SDL_SetRenderDrawColor(internal->renderer,0x0,0,0,0);


			SDL_RenderPresent(internal->renderer);

		}
	}
	else{
		return 1;
	}
	return 0;
}






int		Clannad_DrawBMPfile(Clannad *clannad_data,const char *filename,int x,int y,int w,int h){
	SDL_Texture		*texture;
	SDL_Surface		*surface;
	Clannad_Internal	*internal;
	SDL_Rect			rect;
	internal	=	clannad_data->Internal;
	if(!internal)
		return -1;
	if(!internal->renderer)
		return -1;
	surface		=	SDL_LoadBMP(filename);
	if(!surface){
		return 1;
	}
	texture		=	SDL_CreateTextureFromSurface(internal->renderer,surface);
	if(!texture)
		return 1;
	rect.x		=	x;
	rect.y		=	y;
	rect.w		=	w;
	rect.h		=	h;



	SDL_RenderCopy(internal->renderer,texture,NULL,&rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return 0;
}




//====================================================================================
//一些函数

typedef		struct{
	SDL_Surface		*surface;
	SDL_Texture		*texture;
}Clannad_BMP;

typedef		struct{
	int		x,y;
	int		w,h;
}cRect;

typedef		struct{
	Clannad_BMP		bmp;
	cRect				srcRect;
	cRect				dstRect;
}Clannad_Sprite;


void		*CLoadBMP(Clannad*c,Clannad_BMP*bmp,const char*filename){
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	Clannad_Internal	*internal;
	internal	=	c->Internal;
	if(internal||internal->renderer){
		return NULL;
	}
	if(!bmp)
		return NULL;
	//加载文件
	surface		=	SDL_LoadBMP(filename);
	if(!surface){
		return NULL;
	}
	texture		=	SDL_CreateTextureFromSurface(internal->renderer,surface);
	if(!texture){
		SDL_FreeSurface(surface);
		return NULL;
	}

	//透明值
	SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);

	bmp->surface	=	surface;
	bmp->texture	=	texture;
	return bmp;
}

void		*CInitBMP(){
	Clannad_BMP		*bmp;
	bmp		=	SDL_calloc(1,sizeof(*bmp));
	return bmp;
}

void		*CInitBMPFile(Clannad*c,const char*filename){
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	Clannad_Internal	*internal;
	Clannad_BMP		*bmp;

	internal	=	c->Internal;
	if(!internal||!internal->renderer){
		return NULL;
	}
	//加载文件
	surface		=	SDL_LoadBMP(filename);
	if(!surface){
		return NULL;
	}
	texture		=	SDL_CreateTextureFromSurface(internal->renderer,surface);
	if(!texture){
		SDL_FreeSurface(surface);
		return NULL;
	}

	//透明值
	SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);

	bmp	=	(Clannad_BMP*)SDL_calloc(1,sizeof(Clannad_BMP));
	bmp->surface	=	surface;
	bmp->texture	=	texture;
	return bmp;
}



static SDL_Texture		*getTexture(Clannad_BMP*bmp){
	if(bmp){
		return bmp->texture;
	}
	else
		return NULL;
}

static	SDL_Renderer	*getRenderer(Clannad_Internal*c){
	if(c){
		return c->renderer;
	}
	else
		return NULL;
}


int			CDrawBMP(Clannad*c,void*bmp,int srcx,int srcy,int srcw,int srch,int dstx,int dsty,int dstw,int dsth){
	if(bmp){
		SDL_Rect	src;
		SDL_Rect	dst;
		src.x	=	srcx;
		src.y	=	srcy;
		src.w	=	srcw;
		src.h	=	srch;

		dst.x	=	dstx;
		dst.y	=	dsty;
		dst.w	=	dstw;
		dst.h	=	dsth;
		return SDL_RenderCopy(
				getRenderer(c->Internal),
				getTexture(bmp),
				&src,
				&dst
				);

	}
	return 0;
}

int			CDrawBMPAlpha(Clannad*c,void*bmp,int srcx,int srcy,int srcw,int srch,int dstx,int dsty,int dstw,int dsth,u8 alpha){
	if(bmp){
		SDL_Rect	src;
		SDL_Rect	dst;
		src.x	=	srcx;
		src.y	=	srcy;
		src.w	=	srcw;
		src.h	=	srch;

		dst.x	=	dstx;
		dst.y	=	dsty;
		dst.w	=	dstw;
		dst.h	=	dsth;
		SDL_SetTextureAlphaMod(
				getTexture(bmp),
				alpha
				);
		return SDL_RenderCopy(
				getRenderer(c->Internal),
				getTexture(bmp),
				&src,
				&dst
				);

	}
	return 0;
}






void		CFreeBMP(void*bmp){
	if(bmp){
		Clannad_BMP	*b;
		b	=	bmp;
		if(b->surface)
			SDL_FreeSurface(b->surface);
		if(b->texture)
			SDL_DestroyTexture(b->texture);
		SDL_free(b);
	}
}

void		CmFreeBMP(void*bmp){
	if(bmp){
		Clannad_BMP	*b;
		b	=	bmp;
		if(b->surface)
			SDL_FreeSurface(b->surface);
		if(b->texture)
			SDL_DestroyTexture(b->texture);
	}
}


int			CDrawSprite(Clannad*c,Clannad_Sprite*sprinte){
	if(sprinte){
		return SDL_RenderCopy(
				getRenderer(c->Internal),
				//其实不用sprite.bmp,强制转换就行了
				getTexture(&sprinte->bmp),
				(SDL_Rect*)&sprinte->srcRect,
				(SDL_Rect*)&sprinte->dstRect
				);
	}
	return 1;
}

void		*CSpriteInit(){
	Clannad_Sprite		*sprite;
	sprite	=	SDL_calloc(1,sizeof(*sprite));
	return sprite;
}


void		*CSpriteInitFile(Clannad*c,const char*fname){
	Clannad_Sprite		*sprite;
	sprite	=	CSpriteInit();
	return	CLoadBMP(c,&sprite->bmp,fname);
}

void		CSpriteFree(void*sprite){
	if(sprite){
		Clannad_Sprite		*s;
		s	=	sprite;
		CmFreeBMP(&s->bmp);
		SDL_free(sprite);
	}
}


//把问题复杂化了,不是很喜欢
BMP_func	bmp_func	=	{
		.Init		=	CInitBMP,
		.InitFile	=	CInitBMPFile,
		.DrawBMP	=	CDrawBMP,
		.DrawBMPfile	=	Clannad_DrawBMPfile,
		.Free		=	CFreeBMP,
		.DrawBMPAlpha	=	CDrawBMPAlpha,
};

Sprite_func	sprite_func		=	{
		{
				.Init		=	CSpriteInit,
				.InitFile	=	CSpriteInitFile,
				.DrawBMP	=	CDrawBMP,
				.DrawBMPfile	=	Clannad_DrawBMPfile,
				.Free		=	CSpriteFree,
				.DrawBMPAlpha	=	CDrawBMPAlpha
		},
		.DrawSprite		=	(void*)CDrawSprite,
};


#endif	//end USE_SDL_
