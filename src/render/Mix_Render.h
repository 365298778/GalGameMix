/*
 * Mix_Render.h
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */


/**
 * @file		Mix_Render.h
 * @author		yami
 * @date		2015-05-01 17:07:01
 * @brief
 * 头声明
 */


#ifndef SRC_RENDER_MIX_RENDER_H_
#define SRC_RENDER_MIX_RENDER_H_

#include	"../types.h"
#include	"../version.h"
#include	"../def.h"
#include	"../Subsystem.h"


//系统自带的库
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>


typedef	struct{
	int		(*Init)		(void*sender);
	int		(*Clean)	(void*sender);
	int		(*Cleaning)	(void*sender);
	int		(*Render)	(void*sender);
	int		(*Update)	(void*sender);
}MixRenderFunc;


typedef	struct{
	MixRenderFunc		*func;
	char				*file_name;			//这个不是很必要的,但对于新手来说,很好用
	GGMix				*ggmix;
	CBMP				*bmp;
	//int					priority;			//默认是0,当值越大,远离角色越远,(0在最高端)
	void*				Internal;
	int					rectsCount;			//绘制矩形的个数,如果是0,
	cRect				*srcRect;
	cRect				*dstRect;
}MixSprite;


//============================================================================================


extern		int		MixSprite_clean	(MixSprite*sprite);
extern		int		MixSprite_render	(MixSprite*sprite);
extern		int		MixSprite_init		(MixSprite*sprite);

extern	void	 		Mixsprite_inifunc		(MixRenderFunc*func);
extern	MixSprite*		MixSpriteLoadFile		(GGMix*c,const char*filename);
extern	void			MixSpriteSetUpdate	(MixSprite*sprite,int (*update_func)(MixSprite*));
extern	void			MixSpriteRender		(MixSprite*sprite);
extern	void			MixSpriteUpdate		(MixSprite*sprite);
extern	void			MixSpritePtrRender	(MixSprite**spritePtr,int count);
extern	void			MixSpritePriorityPtrRender(MixSprite**spritePtr,int *prio,int count);
extern	void			MixSpritePtrUpdate	(MixSprite**spritePtr,int count);
extern	void			MixSpritesRender		(MixSprite*sprites,int count);
extern	void			MixSpritesUpdate		(MixSprite*sprites,int count);
extern	void			MixSpriteFree			(MixSprite*sprite);
extern 	void			MixSpriteSetAlpha		(MixSprite*sprite,u8 alpha);


//============================================================================================



//================================





#endif /* SRC_RENDER_MIX_RENDER_H_ */
