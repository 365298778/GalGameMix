/*
 * Subsystem.h
 *
 *  Created on: 2015年4月29日
 *      Author: yami
 */

/**
 * @file		Subsystem.h
 * @date		2015-04-29 12:48:26
 * @author		yami
 * @brief
 * 这个子系统的声明
 */

#ifndef SRC_SUBSYSTEM_H_
#define SRC_SUBSYSTEM_H_


#include		"types.h"
#include		"version.h"
#include		"def.h"

//============================================================================================================================
//类型定义


typedef		struct{
	int		x,y;
	int		w,h;
}cRect;

typedef	struct{
	u32			end_flag;
	u32			current_ticks;
	u32			last_ticks;
	u32			frame_wait_ticks;
	u32			fps;
	u32			fcs;
	u32			fc;
	u32			last_second_ticks;
	u32			second;
}GGMix_state;






typedef struct{
	u8			show_state;
	u8			show_game_time;
	u8			show_frame;
}GGMix_config;


typedef	struct GGMix{
	GGMix_state		state;
	GGMix_config		config;
	void				*Internal;
	int					(*Init)();
	int					(*Close)();
	int					(*Closing)(struct GGMix *sender);
	int					(*Loop)(struct GGMix *sender);
	int					(*DrawBMPFile)(struct GGMix *render,const char*,int,int,int,int);
	int					(*Update)(struct GGMix *sender);
	int					(*RenderUpdate)(struct GGMix *sender);
}GGMix;



typedef	struct{
	void		*internal;
	void		*dataptr;
	int			w;
	int			h;
}CBMP;


typedef struct{
	void*		(*Init)();
	void*		(*InitFile)(GGMix*,const char*);
	int			(*DrawBMP)(GGMix*,void*bmp,int,int,int,int,int,int,int,int);
	int			(*DrawBMPAlpha)(GGMix*,void*bmp,int,int,int,int,int,int,int,int,u8);
	int			(*DrawBMPfile)(GGMix*,const char*fname,int,int,int,int);
	void		(*Free)(void*bmp);
}BMP_func;



typedef struct{
	BMP_func	bmp_func;
	int			(*DrawSprite)(GGMix*,void*sprite);
}Sprite_func;
//============================================================================================================================


//============================================================================================================================
//声明一些外部变量
extern		GGMix			*ggmix;
extern 		BMP_func		bmp_func;
extern		Sprite_func	sprite_func;

//============================================================================================================================



//============================================================================================================================
//声明一些外部函数
CBMP		*CBMP_Load		(GGMix*c,const char*filename);
void		CBMP_Free		(CBMP*cbmp);
int			CBMP_Draw		(CBMP*cbmp,GGMix*c,cRect *src_rect,cRect *dst_rect);
int			CBMP_Draws		(CBMP*cbmp,GGMix*c,cRect*src_rect,cRect*dst_rect,int count);
int			CBMP_DrawsEx	(CBMP*cbmp,GGMix*c,cRect**src_rect,cRect**dst_rect,int count);
int			CBMP_SetAlpha	(CBMP*cbmp,u8 alpha);

#endif /* SRC_SUBSYSTEM_H_ */
