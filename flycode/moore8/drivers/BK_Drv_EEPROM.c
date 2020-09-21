#include<string.h>
#include "board.h"
#include "BK_Drv_EEPROM.h"

#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\flash\flash.h"
#include "..\bk2471\drivers\uart\uart.h"

// #include "BK_Param.h"

/************************************************************************
* EEPROM ���䷽ʽ��
*	1���ܶ�λ���򣺶�λ��FALSH���һ��sector��4KB
*	2����������䣺������n��������Ҫ����:V1��V2��...��Vn������ÿ������
*		д���Ƶ�ȣ�Ϊ������Ӧ�Ŀռ䡣����2��������V1(16B)��V2(8B)��V1д��Ƶ��һЩ
*		V2�Ƚϲ�Ƶ����ΪV1����3.5KB(214��)��ΪV2����0.5KB(64��)��ÿ��������Ϊ�����ģ�
*		������֮����Բ�������
*	3���趨����Э�����������������趨Э���������������ӣ�
*		Э���{ADDR_LAST_SEC,(1024*3+512)>>2,16}
*				{ADDR_LAST_SEC+(1024*3+512),(512)>>2,8}
************************************************************************/
typedef struct TFlashMapProtocol{
	UI32 addr;//����ʼ��ַ
	UI16 sz;//�γ���,4BΪ1��λ
	UI16 uSz;//���ݵ�Ԫ����
}TFlashMapProtocol;
#define NUM_FLASH_MAPPROTOCOL		1
#define MAX_UNIT_SIZE				(sizeof(int))
const TFlashMapProtocol tFlashDataMap[NUM_FLASH_MAPPROTOCOL]={
	//{0x4000,(0x2000>>2),4},
	{EEPROM_START_ADDRESS,(FLASH_SECTOR_SIZE>>2),sizeof(int)/*����bk_param.h��CSysInfo�趨*/},
};

/*
 *������:
 *	SearchInSeg
 *����:
 *	��flash������Ա������Ķ���һ�οռ�
 *����:
 *	1.segIdx:���Ա�����
 *����:
 *	NULL:û���㹻�ռ䱣������.����:�ѵ��ĵ�ַ
 *����:
 *	��
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
 *������:
 *	SearchDataInSeg
 *����:
 *	��flash������Ա������Ķ��ұ��ε�����
 *����:
 *	1.segIdx:���Ա�����
 *����:
 *	NULL:û���ҵ�����.����:����ָ��
 *����:
 *	��
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
 *������:
 *	SearchSegIdx
 *����:
 *	���Ҹ�����ַ�Ķ�����
 *����:
 *	1.addr:������ַ
 *����:
 *	���Ա�����
 *����:
 *	��
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
 *������:
 *	WriteFlashUnitProtocol
 *����:
 *	�����ݵ�Ԫ�������ݵ�flash����
 *����:
 *	1.addr:flash��ַ
 *	2.buf:���ݻ�����
 *	3.len:���ݳ���
 *����:
 *	��
 *����:
 *	��
*/
void WriteFlashUnitProtocol(UI32 addr,void*buf,UI32 len){
	int i;
	//������
	i=SearchSegIdx(addr);
	//�ڷ��������һ���㹻��Ŀռ�
	char*ptr=SearchInSeg(i);
	//����ҵ�,ֱ�ӱ���
	if(ptr>0){
		Flash_Write((UI32)ptr,buf,len);
		return;
	}
	//���δ�ҵ�,�����ݶδ���
	int j,k=0;	
	
	//�����ж��ٸ���Ԫ��������Ҫ����
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		if(j!=i)k++;//��ǰ��Ԫ������,�����Ѿ���buf��
	}
	//����ָ��ռ䱣�浥Ԫ����ָ��
// 	PUI8 *pBuf=(PUI8*)malloc(k*sizeof(PUI8));//��mallocδ��֧��ȡ��
// 	memset(pBuf,0,k*sizeof(PUI8));//��mallocδ��֧��ȡ��
	//��Ϊkeil��֧��malloc�����Ը�Ϊ��̬����
	UI8 pBuf[NUM_FLASH_MAPPROTOCOL][MAX_UNIT_SIZE];
	memset(pBuf,0,sizeof(pBuf));
	UI8*tptr;
	//����Ҫ����ĵ�Ԫ���ݶ���������
	int t=0;
	int sz;
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		if(j!=i)continue;//��ǰ��Ԫ������,�����Ѿ���buf��
		sz=tFlashDataMap[j].uSz;
		tptr=(UI8*)SearchDataInSeg(j);
		if(tptr!=NULL){
			//pBuf[t]=(char*)malloc(sz);//��mallocδ��֧��ȡ��
			//memset(pBuf[t],0xff,sz);
			//memcpy(pBuf[t],tptr,sz);
			Flash_Read((uint32)tptr,pBuf[t],sz);
		}else{
			//pBuf[t]=NULL;//��mallocδ��֧��ȡ��
			memset(pBuf[t],0xff,sz);
		}
		t++;
	}
	//�������ݶ�flash
	Flash_Erase(EEPROM_START_ADDRESS,0);
	
	//�����е�Ԫ�����ݶ�����
	for(j=0;j<sizeof(tFlashDataMap)/sizeof(TFlashMapProtocol);j++){
		sz=tFlashDataMap[j].uSz;
		tptr=(UI8*)tFlashDataMap[j].addr;
		if(j!=i){
			Flash_Write((UI32)tptr,buf,sz);
			continue;//��ǰ��Ԫ������,�����Ѿ���buf��
		}		
		/*if(pBuf[t]!=NULL)*/{
			Flash_Write((UI32)tptr,pBuf[t],sz);
		}
		t++;
	}

// 	//�ͷŶ�̬������ڴ�
// 	for(j=0;j<k;j++){
// 		if(pBuf[j])free(pBuf[j]);
// 	}
// 	free(pBuf);
}

/*
 *������:
 *	ReadFlashUnitProtocol
 *����:
 *	��flashָ����ַ�����ݵ�Ԫ��������
 *����:
 *	1.addr:flash��ַ
 *	2.buf:���ݻ�����
 *	3.len:���ݳ���
 *����:
 *	1=��������,0=���ݲ�����
 *����:
 *	��
*/
int ReadFlashUnitProtocol(UI32 addr,void*buf,UI32 len){
	int i;
	//������
	i=SearchSegIdx(addr);
	//�ڷ��������һ���㹻��Ŀռ�
	char*ptr=SearchDataInSeg(i);
	//����ҵ�,ֱ�ӱ���
	if(ptr>0){
		//��Ҫ�ĳ�flash read
		Flash_Read((uint32)ptr,buf,len);
		//memcpy(buf,ptr,len);
		return(1);
	}
	return(0);
}

/*
 *������:
 *	GetFlashUnitProtocol
 *����:
 *	��flashָ����ַ�����ݵ�Ԫ��ȡ����ָ��
 *����:
 *	1.addr:flash��ַ
 *����:
 *	NULL=���ݲ�����,��NULL=����ָ��,
 *����:
 *	��
*/
char* GetFlashUnitProtocol(UI32 addr){
	int i;
	//������
	i=SearchSegIdx(addr);
	//�ڷ��������һ���㹻��Ŀռ�
	char*ptr=SearchDataInSeg(i);
	//����ҵ�,ֱ�ӱ���
	return(ptr);
}
