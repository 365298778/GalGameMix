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
}Clannad_state;






typedef struct{
	u8			show_state;
	u8			show_game_time;
	u8			show_frame;
}Clannad_config;


typedef	struct Clannad{
	Clannad_state		state;
	Clannad_config		config;
	void				*Internal;
	int					(*Init)();
	int					(*Close)();
	int					(*Closing)(struct Clannad *sender);
	int					(*Loop)(struct Clannad *sender);
	int					(*DrawBMPFile)(struct Clannad *render,const char*,int,int,int,int);
	int					(*Update)(struct Clannad *sender);
	int					(*RenderUpdate)(struct Clannad *sender);
}Clannad;


typedef struct{
	void*		(*Init)();
	void*		(*InitFile)(Clannad*,const char*);
	int			(*DrawBMP)(Clannad*,void*bmp,int,int,int,int,int,int,int,int);
	int			(*DrawBMPAlpha)(Clannad*,void*bmp,int,int,int,int,int,int,int,int,u8);
	int			(*DrawBMPfile)(Clannad*,const char*fname,int,int,int,int);
	void		(*Free)(void*bmp);
}BMP_func;


typedef struct{
	BMP_func	bmp_func;
	int			(*DrawSprite)(Clannad*,void*sprite);
}Sprite_func;
//============================================================================================================================


//============================================================================================================================
//申明一些外部变量
extern		Clannad			*clannad;
extern 		BMP_func		bmp_func;
extern		Sprite_func	sprite_func;

//============================================================================================================================


#endif /* SRC_SUBSYSTEM_H_ */
