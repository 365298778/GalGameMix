/*
 * Mix_render.c
 *
 *  Created on: 2015年5月1日
 *      Author: yami
 */


/**
 * @file		Mix_render.c
 * @author		yami
 * @date		2015-05-01 16:18:54
 * @brief
 * 这个是处理游戏渲染的
 * 类似与模版
 * 你可以添加类似很多功能在里面
 */


#include	"Mix_Render.h"




void	 		Mixsprite_inifunc(MixRenderFunc*func){
	func->Init		=	(void*)MixSprite_init;
	func->Clean		=	(void*)MixSprite_clean;
	func->Render	=	(void*)MixSprite_render;
}





 	MixSprite*		MixSpriteLoadFile(GGMix*c,const char*filename){
	MixSprite			*mixsprite;
	MixRenderFunc		*renderfunc;
	renderfunc		=	calloc(1,sizeof(*renderfunc));
	mixsprite		=	calloc(1,sizeof(*mixsprite));
	if(!mixsprite||!renderfunc){
		if(mixsprite)
			free(mixsprite);
		if(renderfunc)
			free(renderfunc);
		return 0;
	}
	mixsprite->func			=	renderfunc;

	/*
	 *
	 * 可能用户会修改file_name,所以
	 * */
	//mixsprite->file_name	=	filename;
	mixsprite->file_name	=	calloc(1,strlen(filename)+1);
	strcpy(mixsprite->file_name,filename);
	mixsprite->ggmix		=	c;

	//初始化函数
	Mixsprite_inifunc(renderfunc);

	//这个会加载文件到纹理,或者软处理
	if(mixsprite->func->Init)
		mixsprite->func->Init(mixsprite);

	return mixsprite;
}


 	void			MixSpriteSetUpdate(MixSprite*sprite,int (*update_func)(MixSprite*)){
	if(sprite){
		if(sprite->func){
			sprite->func->Update	=	(void*)update_func;
		}
	}
}


 	void			MixSpriteRender(MixSprite*sprite){
	if(sprite){
		if(sprite->func)
		{
			if(sprite->func->Render){
				sprite->func->Render(sprite);
			}
		}
	}
}


	void			MixSpriteUpdate(MixSprite*sprite){
	if(sprite){
		if(sprite->func)
		{
			if(sprite->func->Update){
				sprite->func->Update(sprite);
			}
		}
	}
}


	void			MixSpritePtrRender(MixSprite**spritePtr,int count){
	MixSprite		*sprite;
	if(spritePtr){
		while(count-->0)
		{
			sprite		=	*spritePtr++;
			if(sprite){
				if(sprite->func)
				{
					if(sprite->func->Render){
						sprite->func->Render(sprite);
					}
				}
			}
		}
	}
}


	void			MixSpritePriorityPtrRender(MixSprite**spritePtr,int *prio,int count){
//	MixSprite		*sprite;
//	MixSprite		**base;
//	MixSprite		**current;
	int				index;
	int				i;
	//比较复杂,不好掌握
	if(spritePtr){
//		base	=	spritePtr;
		index	=	0;

		for(index = 0;index<count;index++){
			if(prio[index]>100){
				MixSprite_render(spritePtr[index]);
			}
		}
		for(i=100;i>=0;i--){

			for(index = 0;index<count;index++){
				if(prio[index]<=100){

					if(prio[index]==i){
						MixSprite_render(spritePtr[index]);
					}
					else{
						//非此优先权,跳过
					}
				}
			}
		}


	}
}



	void			MixSpritePtrUpdate(MixSprite**spritePtr,int count){
	MixSprite		*sprite;
	if(spritePtr){
		while(count-->0){
			sprite	=	*spritePtr++;
			if(sprite){
				if(sprite->func)
				{
					if(sprite->func->Update){
						sprite->func->Update(sprite);
					}
				}
			}
		}
	}
}


void			MixSpritesRender(MixSprite*sprites,int count){
	while(count-->0){
		if(sprites){
			if(sprites->func)
			{
				if(sprites->func->Render){
					sprites->func->Render(sprites);
				}
			}
		}
		sprites++;
	}
}

void			MixSpritesUpdate(MixSprite*sprites,int count){
	while(count-->0){
		if(sprites){
			if(sprites->func)
			{
				if(sprites->func->Update){
					sprites->func->Update(sprites);
				}
			}
		}
	}
}


void			MixSpriteSetAlpha(MixSprite*sprite,u8 alpha){
	CBMP_SetAlpha(sprite->bmp,alpha);
}



void			MixSpriteFree(MixSprite*sprite){
	if(sprite){
		//Init(),和Clean()是对应的
		if(sprite->func->Clean)
			sprite->func->Clean(sprite);
		if(sprite->func)
			free(sprite->func);
		if(sprite->file_name)
			free(sprite->file_name);
		free(sprite);
	}
}
