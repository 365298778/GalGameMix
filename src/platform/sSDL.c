/*
 * sSDL.c
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */


/**
 * @file		sSDL.c
 * @date		2015-05-01 14:41:40
 * @author		yami
 * @brief
 * subSystem_SDL
 * 子系统SDL的源码
 */


#include	"../Subsystem.h"
#include	"sSDL.h"

#ifdef	USE_SDL_


void	CBMP_Free(CBMP*cbmp){
	if(cbmp){
		CBMP_Internal	*i;
		if((i =cbmp->internal)){
			if(i->surface)
				SDL_FreeSurface(i->surface);
			if(i->texture)
				SDL_DestroyTexture(i->texture);
			SDL_free(cbmp->internal);
			cbmp->internal	=	0;
		}
		SDL_free(cbmp);
	}

}

CBMP	*CBMP_Load(GGMix*c,const char*filename){
	CBMP				*cbmp;
	CBMP_Internal		*internal;
	GGMix_Internal	*ci;
	cbmp				=	SDL_calloc(1,sizeof(*cbmp));
	internal			=	SDL_calloc(1,sizeof(*internal));
	if(!cbmp||!internal){
		if(cbmp)
			SDL_free(cbmp);
		if(internal)
			SDL_free(internal);
		return NULL;
	}
	cbmp->internal		=	internal;

	internal->surface	=	SDL_LoadBMP(filename);
	if(!internal->surface)
	{
		//释放
		CBMP_Free(cbmp);
		cbmp			=	NULL;
	}

	ci					=	c->Internal;
	if(!ci){
		CBMP_Free(cbmp);
		cbmp			=	NULL;
	}

	internal->texture	=	SDL_CreateTextureFromSurface(
			ci->renderer,
			internal->surface
			);

	//
	if(!internal->texture)
	{
		CBMP_Free(cbmp);
		cbmp			=	NULL;
	}
	cbmp->w				=	internal->surface->w;
	cbmp->h				=	internal->surface->h;
	//透明绑定
	SDL_SetTextureBlendMode(internal->texture,SDL_BLENDMODE_BLEND);
	return		cbmp;
}

int		CBMP_Draw(CBMP*cbmp,GGMix*c,cRect *src_rect,cRect *dst_rect){
	GGMix_Internal	*ci;
	CBMP_Internal		*cbmpi;
	ci		=	c->Internal;
	cbmpi	=	cbmp->internal;
	if(ci&&cbmpi){
		if(ci->renderer&&cbmpi->texture){
			return SDL_RenderCopy(
					ci->renderer,
					cbmpi->texture,
					(SDL_Rect*)src_rect,
					(SDL_Rect*)dst_rect
					);

		}
	}
	return 1;
}


int		CBMP_Draws(CBMP*cbmp,GGMix*c,cRect*src_rects,cRect*dst_rects,int count){
	int		result;
	GGMix_Internal	*ci;
	CBMP_Internal		*cbmpi;
	result	=	0;
	if(!c&&!c->Internal)
		return 1;
	if(!cbmp&&!cbmp->internal)
		return 1;
	ci		=	c->Internal;
	cbmpi	=	cbmp->internal;
	while(count-->0){
		if(SDL_RenderCopy(
				ci->renderer,
				cbmpi->texture,
				(void*)src_rects,
				(void*)dst_rects
				))
		{
			//出现错误
			result--;
		}
		//如果是NULL,默认是不自加
		if(src_rects)
			src_rects++;
		if(dst_rects)
			dst_rects++;
	}
	return result;		//返回以绝对值返回错误个数
}


int		CBMP_DrawsEx(CBMP*cbmp,GGMix*c,cRect**src_rects_ptr,cRect**dst_rects_ptr,int count){
	int		result;
	GGMix_Internal	*ci;
	CBMP_Internal		*cbmpi;
	result	=	0;
	if(!c&&!c->Internal)
		return 1;
	if(!cbmp&&!cbmp->internal)
		return 1;
	ci		=	c->Internal;
	cbmpi	=	cbmp->internal;
	while(count-->0){
		cRect 		*src_;
		cRect		*dst_;
		if(src_rects_ptr)
			src_	=	*src_rects_ptr++;
		else
			src_	=	NULL;

		if(dst_rects_ptr)
			dst_	=	*dst_rects_ptr++;
		else
			dst_	=	NULL;


		if(SDL_RenderCopy(
				ci->renderer,
				cbmpi->texture,
				(void*)src_,
				(void*)dst_
				)){
			//出现错误
			result--;
		}


//		//如果是NULL,默认是不自加
//		if(src_rects_ptr)
//			src_rects_ptr++;
//		if(dst_rects_ptr)
//			dst_rects_ptr++;
	}
	return result;		//返回以绝对值返回错误个数
}


int		CBMP_SetAlpha(CBMP*cbmp,u8 alpha){
	CBMP_Internal		*cbmpi;
	if(!cbmp&&!(cbmp->internal))
		return 1;
	cbmpi = cbmp->internal;
	return	SDL_SetTextureAlphaMod(cbmpi->texture,alpha);
}



#endif		/*USE_SDL_*/
