#ifndef _BT_3DS_H_
#define _BT_3DS_H_
#include "..\..\includes\types.h"
#define	BASE_BT_3DS_PTR	\
		((HW_BT_3DS*)0x00f00800)
typedef union HW_3DS_PWMU{
	uint32 d[3];
	struct{
		uint32 _3dg_start:22;
		uint32 :10;
		uint32 _3dg_mid:22;
		uint32 :10;
		uint32 _3dg_end:22;
		uint32 :10;
	};
}HW_3DS_PWMU;
typedef struct HW_BT_3DS{
	union{
		uint32 REG_0x0;
		struct{
			uint32 bt_3dd_en:1;
			// 3D displayer (Tx) synchronizer enable
			uint32 bt_3dg_en:1;
			// 3D glass (Rx) PWM function enable
			uint32 :1;
			uint32 tsync_acc_cal:1;
			//Frame Tsync accumulating calculation enable
			uint32 frame_cap_int_ena:1;
			// 3DD frame sync captured interrupt enable
			uint32 frame_acc_int_ena:1;
			// 3DD frame sync period accumated interrupt enable
			uint32 tsync_cin_int_ena:1;
			// 3DG frame period fraction carry-in interrupt enable
			uint32 frame_pwm_int_ena:1;
			//Reserved
			uint32 pwm0_en:1;
			//PWM0 enable
			uint32 pwm1_en:1;
			//PWM1 enable
			uint32 pwm2_en:1;
			//PWM2 enable
			uint32 pwm3_en:1;
			//PWM3 enable
			uint32 pwm0_start_set:1;
			//PWM0 wave start level set. 0=Low level. 1=High level.
			uint32 pwm1_start_set:1;
			//PWM1 wave start level set. 0=Low level. 1=High level.
			uint32 pwm2_start_set:1;
			//PWM2 wave start level set. 0=Low level. 1=High level.
			uint32 pwm3_start_set:1;
			//PWM3 wave start level set. 0=Low level. 1=High level.
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 frame_cap_int:1;
			//Frame Sync Capture Interrupt Status. Write 1 to clear.
			uint32 frame_acc_int:1;
			//Frame Accumulation Interrupt Status. Write 1 to clear.
			uint32 tsync_cin_int:1;
			//Tsync Carry-In Interrupt Status. Write 1 to clear.
			uint32 frame_pwm_int:1;
			//Frame PWM Tsync Arriving Interrupt Status. Write 1 to clear.
			uint32 :28;
		};
	};
	union{
		uint32 REG_0x2;
		struct{
			uint32 frame_sync_btclk:4;
			//No description
			uint32 :28;
		};
	};
	union{
		uint32 REG_0x3;
		struct{
			uint32 frame_sync_phase:16;
			//No description
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x4;
		struct{
			uint32 frame_sync_neg:22;
			//No description
			uint32 :10;
		};
	};
	union{
		uint32 REG_0x5;
		struct{
			uint32 frame_tsync_acc:27;
			//No description
			uint32 :5;
		};
	};
	union{
		uint32 REG_0x6;
		struct{
			uint32 frame_tsync_tx:22;
			//No description
			uint32 :10;
		};
	};
	uint32 REG_0x7;
	uint32 REG_0x8;
	uint32 REG_0x9;
	uint32 REG_0xA;
	uint32 REG_0xB;
	uint32 REG_0xC;
	uint32 REG_0xD;
	uint32 REG_0xE;
	uint32 REG_0xF;
	union{
		uint32 REG_0x10;
		struct{
			uint32 reg_3dg_frame_btclk:28;
			//No description
			uint32 :4;
		};
	};
	union{
		uint32 REG_0x11;
		struct{
			uint32 reg_3dg_frame_phase:16;
			//No description
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x12;
		struct{
			uint32 reg_3dg_frame_tsync:16;
			//No description
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x13;
		struct{
			uint32 reg_3dg_frame_frac:8;
			//No description
			uint32 :24;
		};
	};
	HW_3DS_PWMU pwms[4];
}HW_BT_3DS;

#endif
