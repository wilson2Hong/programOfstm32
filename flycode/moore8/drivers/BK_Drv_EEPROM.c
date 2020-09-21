#include<string.h>
#include "board.h"
#include "BK_Drv_EEPROM.h"

#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\flash\flash.h"
#include "..\bk2471\drivers\uart\uart.h"

// #include "BK_Param.h"

/************************************************************************
* EEPROM 分配方式：
*	1、总定位区域：定位在FALSH最后一个sector，4KB
*	2、子区域分配：假设有n个变量需要保存:V1、V2、...、Vn，估计每个变量
*		写入的频度，为它们相应的空间。比如2个变量，V1(16B)、V2(8B)，V1写入频繁一些
*		V2比较不频繁，为V1分配3.5KB(214次)，为V2分配0.5KB(64次)，每个子区域为连续的，
*		子区域之间可以不连续。
*	3、设定访问协议表：根据子区域分配设定协议表。比如上面的例子：
*		协议表：{ADDR_LAST_SEC,(1024*3+512)>>2,16}
*				{ADDR_LAST_SEC+(1024*3+512),(512)>>2,8}
************************************************************************/
typedef struct TFlashMapProtocol{
	UI32 addr;//段起始地址
	UI16 sz;//段长度,4B为1单位
	UI16 uSz;//数据单元长度
}TFlashMapProtocol;
#define NUM_FLASH_MAPPROTOCOL		1
#define MAX_UNIT_SIZE				(sizeof(int))
const TFlashMapProtocol tFlashDataMap[NUM_FLASH_MAPPROTOCOL]={
	//{0x4000,(0x2000>>2),4},
	{EEPROM_START_ADDRESS,(FLASH_SECTOR_SIZE>>2),sizeof(int)/*根据bk_param.h里CSysInfo设定*/},
};

/*
 *函数名:
 *	SearchInSeg
 *功能:
 *	在flash分配策略表里分配的段找一段空间
 *参数:
 *	1.segIdx:策略表索引
 *返回:
 *	NULL:没有足够空间保存数据.其他:搜到的地址
 *特殊:
 *	无
*/
char*SearchInSeg(UI32 segIdx){
	int ptr=(int)tFlashDataMap[segIdx].addr;
	int i;
	UI32 r,m;
	r=tFlashDataMap[segIdx].sz;
	m=tFlashDataMap[segIdx].uSz;
	r=(r<<2)/m;
	for(i=0;i<r;i++){
		if(Flash_CheckBlankRange(ptr,m)==1){
			return((char*)ptr);
		}
		ptr+=m;
	}
	return(NULL);
}

/*
 *函数名:
 *	SearchDataInSeg
 *功能:
 *	在flash分配策略表里分配的段找本段的数据
 *参数:
 *	1.segIdx:策略表索引
 *返回:
 *	NULL:没有找到数据.其他:数据指针
 *特殊:
 *	无
*/
char*SearchDataInSeg(UI32 segIdx){
	int ptr=(int)tFlashDataMap[segIdx].addr;
	int i;
	UI32 r,m,k;
	r=tFlashDataMap[segIdx].sz;
	m=tFlashDataMap[segIdx].uSz;
	k=(r<<2)/m;
	r=ptr;
	for(i=0;i<k;i++){
		if(Flash_CheckBlankRange(ptr,m)==1){
			if(ptr==r){
				return(NULL);
			}else{
				return((char*)(ptr-m));
			}
		}
		ptr+=m;
	}
	return((char*)(ptr-m));
}

/*
 *函数名:
 *	SearchSegIdx
 *功能:
 *	查找给定地址的段索引
 *参数:
 *	1.addr:给定地址
 *返回:
 *	策略表索引
 *特殊:
 *	无
*/
int SearchSegIdx(UI32 addr){
	TFlashMapProtocol*pmap=(TFlashMapProtocol*)tFlashDataMap;
	int i;
	for(i=0;i<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);i++){
		if((addr>=pmap->addr)&&(addr<(pmap->addr+(pmap->sz<<2)))){
			return(i);
		}
		pmap++;
	}
	return(-1);
}


/*
 *函数名:
 *	WriteFlashUnitProtocol
 *功能:
 *	按数据单元保存数据到flash策略
 *参数:
 *	1.addr:flash地址
 *	2.buf:数据缓冲区
 *	3.len:数据长度
 *返回:
 *	无
 *特殊:
 *	无
*/
void WriteFlashUnitProtocol(UI32 addr,void*buf,UI32 len){
	int i;
	//找索引
	i=SearchSegIdx(addr);
	//在分配段中找一个足够大的空间
	char*ptr=SearchInSeg(i);
	//如果找到,直接保存
	if(ptr>0){
		Flash_Write((UI32)ptr,buf,len);
		return;
	}
	//如果未找到,擦数据段处理
	int j,k=0;	
	
	//计算有多少个单元的数据需要保存
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		if(j!=i)k++;//当前单元不保存,数据已经在buf里
	}
	//分配指针空间保存单元数据指针
// 	PUI8 *pBuf=(PUI8*)malloc(k*sizeof(PUI8));//因malloc未被支持取消
// 	memset(pBuf,0,k*sizeof(PUI8));//因malloc未被支持取消
	//因为keil不支持malloc，所以改为静态分配
	UI8 pBuf[NUM_FLASH_MAPPROTOCOL][MAX_UNIT_SIZE];
	memset(pBuf,0,sizeof(pBuf));
	UI8*tptr;
	//将需要保存的单元数据读出并保存
	int t=0;
	int sz;
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		if(j!=i)continue;//当前单元不保存,数据已经在buf里
		sz=tFlashDataMap[j].uSz;
		tptr=(UI8*)SearchDataInSeg(j);
		if(tptr!=NULL){
			//pBuf[t]=(char*)malloc(sz);//因malloc未被支持取消
			//memset(pBuf[t],0xff,sz);
			//memcpy(pBuf[t],tptr,sz);
			Flash_Read((uint32)tptr,pBuf[t],sz);
		}else{
			//pBuf[t]=NULL;//因malloc未被支持取消
			memset(pBuf[t],0xff,sz);
		}
		t++;
	}
	//擦除数据段flash
	Flash_Erase(EEPROM_START_ADDRESS,0);
	
	//将所有单元的数据都保存
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		sz=tFlashDataMap[j].uSz;
		tptr=(UI8*)tFlashDataMap[j].addr;
		if(j!=i){
			Flash_Write((UI32)tptr,buf,sz);
			continue;//当前单元不保存,数据已经在buf里
		}		
		/*if(pBuf[t]!=NULL)*/{
			Flash_Write((UI32)tptr,pBuf[t],sz);
		}
		t++;
	}

// 	//释放动态分配的内存
// 	for(j=0;j<k;j++){
// 		if(pBuf[j])free(pBuf[j]);
// 	}
// 	free(pBuf);
}

/*
 *函数名:
 *	ReadFlashUnitProtocol
 *功能:
 *	从flash指定地址按数据单元读出数据
 *参数:
 *	1.addr:flash地址
 *	2.buf:数据缓冲区
 *	3.len:数据长度
 *返回:
 *	1=读出数据,0=数据不存在
 *特殊:
 *	无
*/
int ReadFlashUnitProtocol(UI32 addr,void*buf,UI32 len){
	int i;
	//找索引
	i=SearchSegIdx(addr);
	//在分配段中找一个足够大的空间
	char*ptr=SearchDataInSeg(i);
	//如果找到,直接保存
	if(ptr>0){
		//需要改成flash read
		Flash_Read((uint32)ptr,buf,len);
		//memcpy(buf,ptr,len);
		return(1);
	}
	return(0);
}

/*
 *函数名:
 *	GetFlashUnitProtocol
 *功能:
 *	从flash指定地址按数据单元获取数据指针
 *参数:
 *	1.addr:flash地址
 *返回:
 *	NULL=数据不存在,非NULL=数据指针,
 *特殊:
 *	无
*/
char* GetFlashUnitProtocol(UI32 addr){
	int i;
	//找索引
	i=SearchSegIdx(addr);
	//在分配段中找一个足够大的空间
	char*ptr=SearchDataInSeg(i);
	//如果找到,直接保存
	return(ptr);
}
