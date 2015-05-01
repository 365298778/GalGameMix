/*
 * MixSprite.c
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */


/**
 * @file		MixSprite.c
 * @author		yami
 * @date		2015-05-01 17:05:47
 * @brief
 * MixSprite的函数具体实现
 */


#include	"Mix_Render.h"


int		MixSprite_init(MixSprite*sprite){
	if(sprite){
		if(sprite->file_name){
			if(sprite->bmp)
				CBMP_Free(sprite->bmp);
			sprite->bmp		=	CBMP_Load(sprite->clannad,sprite->file_name);
			if(!sprite->bmp)
				return -1;
		}
		else{
			return -1;
		}
	}
	return 0;
}


/**
 *
 * @param sprite
 * @return
 */
int		MixSprite_render(MixSprite*sprite){
	int		result;
	result	=	1;
	if(sprite){
		if(sprite->rectsCount)
		{
			result	=	CBMP_Draws(sprite->bmp,sprite->clannad,sprite->srcRect,sprite->dstRect,sprite->rectsCount);
		}
		else{
			result	=	CBMP_Draw(sprite->bmp,sprite->clannad,sprite->srcRect,sprite->dstRect);
		}
	}
	return	result;
}



int		MixSprite_clean(MixSprite*sprite)
{
	if(sprite){
		if(sprite->func->Cleaning)
			sprite->func->Cleaning(sprite);
		if(sprite->file_name)
			free(sprite->file_name);
		if(sprite->bmp)
			CBMP_Free(sprite->bmp);
		free(sprite);
	}
	return 0;
}
