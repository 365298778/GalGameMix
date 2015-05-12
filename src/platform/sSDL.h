/*
 * sSDL.h
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */


/**
 * @file		sSDL.h
 * @date		2015-05-01 15:13:13
 * @author		yami
 * @brief
 * 这是一些内部定义
 */




#ifndef SRC_PLATFORM_SSDL_H_
#define SRC_PLATFORM_SSDL_H_

#include	"../version.h"
#include	"../types.h"
#include	"../def.h"

#ifdef USE_SDL_

#include	<SDL.h>


typedef	struct{
	SDL_Texture		*texture;
	SDL_Surface		*surface;
}CBMP_Internal;

typedef	struct{
	SDL_Window			*window;			//只能存在一个
	SDL_Renderer		*renderer;		//只能存在一个
}GGMix_Internal;





#endif	/*USE_SDL_*/
#endif /* SRC_PLATFORM_SSDL_H_ */
