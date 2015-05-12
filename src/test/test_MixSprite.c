/*
 * test_MixSprite.c
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */

/**
 * @file		test_MixSprite.c
 * @author		yami
 * @date		2015-05-01 19:42:14
 * @brief
 * 测试MixSprite.c的源码
 */



#include	"Test.h"
#include	"../render/Mix_Render.h"

#include	<stdio.h>
#include	<stdlib.h>

#ifdef		TEST_2_

static		int			inited	=	0;
static		MixSprite	*sprite	=	0;

typedef	struct{
	cRect		srcRects[40*30];		//20x20		XxY
	cRect		dstRects[40*30];		//20x20		XxY
	int			wait;
}Test_internal;

/**
 * 清理函数
 */
int			test_cleaning(MixSprite*sender){
	if(sender->Internal){
		free(sender->Internal);
	}
	return 0;
}


int			test_update_effect(MixSprite*sender){
	int				w;
	int				x,y;
	Test_internal	*ti;
	w		=	sender->dstRect[0].w;
	ti		=	sender->Internal;
	if(ti->wait--<0)
		ti->wait=3;
	if(!ti->wait)
	{
		if(w<20){
			w++;
			for(y=0;y<30;y++)
				for(x=0;x<40;x++){
					sender->dstRect[y*40+x].w	=	w;
					sender->dstRect[y*40+x].h	=	w;

					sender->srcRect[y*40+x].w	=	w;
					sender->srcRect[y*40+x].h	=	w;
				}
		}
	}
	return 0;
}


int			test_render_update(GGMix*sender){
	if(!inited){
		Test_internal		*ti;
		int					x,y;
		sprite	=	MixSpriteLoadFile(sender,"BG001.bmp");
		sprite->func->Cleaning	=	(void*)test_cleaning;
		ti						=	calloc(1,sizeof(Test_internal));
		sprite->Internal		=	ti;
		sprite->rectsCount		=	40*30;
		sprite->srcRect			=	ti->srcRects;
		sprite->dstRect			=	ti->dstRects;
		sprite->func->Update	=	(void*)test_update_effect;

		MixSpriteSetAlpha(sprite,0x80);

		for(y=0;y<30;y++)
			for(x=0;x<40;x++){
				sprite->dstRect[y*40+x].x	=	x*20;
				sprite->dstRect[y*40+x].y	=	y*20;

				sprite->srcRect[y*40+x].x	=	x*20;
				sprite->srcRect[y*40+x].y	=	y*20;
			}


		inited	=	1;
	}
	MixSpriteRender(sprite);
	return 0;
}


int			test_update(GGMix*sender){
	MixSpriteUpdate(sprite);
	return 0;
}
int			test_closing(GGMix*sender){
	if(sprite)
	{
		MixSprite_clean(sprite);
		sprite	=	0;
	}
	return 0;
}

#endif	/*TEST_2_*/
