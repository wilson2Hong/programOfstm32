#ifndef _XVR_3231S_H_
#define _XVR_3231S_H_
#include "..\..\includes\types.h"

#define	BASE_XVR_3231S_PTR	\
		((HW_XVR_3231S*)0x00f10000)

//XVR
#define BK2471_XVR_REG_0x00		        REG32(BK2471_XVR_BASE_ADDR+0x00)
#define BK2471_XVR_REG_0x01		        REG32(BK2471_XVR_BASE_ADDR+0x04)
#define BK2471_XVR_REG_0x02		        REG32(BK2471_XVR_BASE_ADDR+0x08)
#define BK2471_XVR_REG_0x03		        REG32(BK2471_XVR_BASE_ADDR+0x0C)
#define BK2471_XVR_REG_0x04		        REG32(BK2471_XVR_BASE_ADDR+0x10)
#define BK2471_XVR_REG_0x05		        REG32(BK2471_XVR_BASE_ADDR+0x14)
#define BK2471_XVR_REG_0x06		        REG32(BK2471_XVR_BASE_ADDR+0x18)
#define BK2471_XVR_REG_0x07		        REG32(BK2471_XVR_BASE_ADDR+0x1C)
#define BK2471_XVR_REG_0x08		        REG32(BK2471_XVR_BASE_ADDR+0x20)
#define BK2471_XVR_REG_0x09		        REG32(BK2471_XVR_BASE_ADDR+0x24)
#define BK2471_XVR_REG_0x0A		        REG32(BK2471_XVR_BASE_ADDR+0x28)
#define BK2471_XVR_REG_0x0B		        REG32(BK2471_XVR_BASE_ADDR+0x2C)
#define BK2471_XVR_REG_0x0C		        REG32(BK2471_XVR_BASE_ADDR+0x30)
#define BK2471_XVR_REG_0x0D		        REG32(BK2471_XVR_BASE_ADDR+0x34)
#define BK2471_XVR_REG_0x0E		        REG32(BK2471_XVR_BASE_ADDR+0x38)
#define BK2471_XVR_REG_0x0F		        REG32(BK2471_XVR_BASE_ADDR+0x3C)
#define BK2471_XVR_REG_0x10		        REG32(BK2471_XVR_BASE_ADDR+0x40)
#define BK2471_XVR_REG_0x11		        REG32(BK2471_XVR_BASE_ADDR+0x44)
#define BK2471_XVR_REG_0x12		        REG32(BK2471_XVR_BASE_ADDR+0x48)
#define BK2471_XVR_REG_0x13		        REG32(BK2471_XVR_BASE_ADDR+0x4C)
#define BK2471_XVR_REG_0x14		        REG32(BK2471_XVR_BASE_ADDR+0x50)
#define BK2471_XVR_REG_0x15		        REG32(BK2471_XVR_BASE_ADDR+0x54)
#define BK2471_XVR_REG_0x16		        REG32(BK2471_XVR_BASE_ADDR+0x58)
#define BK2471_XVR_REG_0x17		        REG32(BK2471_XVR_BASE_ADDR+0x5C)
#define BK2471_XVR_REG_0x18		        REG32(BK2471_XVR_BASE_ADDR+0x60)
#define BK2471_XVR_REG_0x19		        REG32(BK2471_XVR_BASE_ADDR+0x64)
#define BK2471_XVR_REG_0x1A		        REG32(BK2471_XVR_BASE_ADDR+0x68)
#define BK2471_XVR_REG_0x1B		        REG32(BK2471_XVR_BASE_ADDR+0x6C)
#define BK2471_XVR_REG_0x1C		        REG32(BK2471_XVR_BASE_ADDR+0x70)
#define BK2471_XVR_REG_0x1D		        REG32(BK2471_XVR_BASE_ADDR+0x74)
#define BK2471_XVR_REG_0x1E		        REG32(BK2471_XVR_BASE_ADDR+0x78)
#define BK2471_XVR_REG_0x1F		        REG32(BK2471_XVR_BASE_ADDR+0x7C)
#define BK2471_XVR_REG_0x20		        REG32(BK2471_XVR_BASE_ADDR+0x80)
#define BK2471_XVR_REG_0x21		        REG32(BK2471_XVR_BASE_ADDR+0x84)
#define BK2471_XVR_REG_0x22		        REG32(BK2471_XVR_BASE_ADDR+0x88)
#define BK2471_XVR_REG_0x23		        REG32(BK2471_XVR_BASE_ADDR+0x8C)
#define BK2471_XVR_REG_0x24		        REG32(BK2471_XVR_BASE_ADDR+0x90)
#define BK2471_XVR_REG_0x25		        REG32(BK2471_XVR_BASE_ADDR+0x94)
#define BK2471_XVR_REG_0x26		        REG32(BK2471_XVR_BASE_ADDR+0x98)
#define BK2471_XVR_REG_0x27		        REG32(BK2471_XVR_BASE_ADDR+0x9C)
#define BK2471_XVR_REG_0x28		        REG32(BK2471_XVR_BASE_ADDR+0xA0)
#define BK2471_XVR_REG_0x29		        REG32(BK2471_XVR_BASE_ADDR+0xA4)
#define BK2471_XVR_REG_0x2A		        REG32(BK2471_XVR_BASE_ADDR+0xA8)
#define BK2471_XVR_REG_0x2B		        REG32(BK2471_XVR_BASE_ADDR+0xAC)
#define BK2471_XVR_REG_0x2C		        REG32(BK2471_XVR_BASE_ADDR+0xB0)
#define BK2471_XVR_REG_0x2D		        REG32(BK2471_XVR_BASE_ADDR+0xB4)
#define BK2471_XVR_REG_0x2E		        REG32(BK2471_XVR_BASE_ADDR+0xB8)
#define BK2471_XVR_REG_0x2F		        REG32(BK2471_XVR_BASE_ADDR+0xBC)
#define BK2471_XVR_REG_0x30		        REG32(BK2471_XVR_BASE_ADDR+0xC0)
#define BK2471_XVR_REG_0x31		        REG32(BK2471_XVR_BASE_ADDR+0xC4)
#define BK2471_XVR_REG_0x32		        REG32(BK2471_XVR_BASE_ADDR+0xC8)
#define BK2471_XVR_REG_0x33		        REG32(BK2471_XVR_BASE_ADDR+0xCC)
#define BK2471_XVR_REG_0x34		        REG32(BK2471_XVR_BASE_ADDR+0xD0)
#define BK2471_XVR_REG_0x35		        REG32(BK2471_XVR_BASE_ADDR+0xD4)
#define BK2471_XVR_REG_0x36		        REG32(BK2471_XVR_BASE_ADDR+0xD8)
#define BK2471_XVR_REG_0x37		        REG32(BK2471_XVR_BASE_ADDR+0xDC)
#define BK2471_XVR_REG_0x38		        REG32(BK2471_XVR_BASE_ADDR+0xE0)
#define BK2471_XVR_REG_0x39		        REG32(BK2471_XVR_BASE_ADDR+0xE4)
#define BK2471_XVR_REG_0x3A		        REG32(BK2471_XVR_BASE_ADDR+0xE8)
#define BK2471_XVR_REG_0x3B		        REG32(BK2471_XVR_BASE_ADDR+0xEC)
#define BK2471_XVR_REG_0x3C		        REG32(BK2471_XVR_BASE_ADDR+0xF0)
#define BK2471_XVR_REG_0x3D		        REG32(BK2471_XVR_BASE_ADDR+0xF4)
#define BK2471_XVR_REG_0x3E		        REG32(BK2471_XVR_BASE_ADDR+0xF8)
#define BK2471_XVR_REG_0x3F		        REG32(BK2471_XVR_BASE_ADDR+0xFC)
#define BK2471_XVR_REG_0x40		        REG32(BK2471_XVR_BASE_ADDR+0x100)
#define BK2471_XVR_REG_0x41		        REG32(BK2471_XVR_BASE_ADDR+0x104)
#define BK2471_XVR_REG_0x42		        REG32(BK2471_XVR_BASE_ADDR+0x108)
#define BK2471_XVR_REG_0x43		        REG32(BK2471_XVR_BASE_ADDR+0x10C)
#define BK2471_XVR_REG_0x44		        REG32(BK2471_XVR_BASE_ADDR+0x110)
#define BK2471_XVR_REG_0x45		        REG32(BK2471_XVR_BASE_ADDR+0x114)
#define BK2471_XVR_REG_0x46		        REG32(BK2471_XVR_BASE_ADDR+0x118)
#define BK2471_XVR_REG_0x47		        REG32(BK2471_XVR_BASE_ADDR+0x11C)
#define BK2471_XVR_REG_0x48		        REG32(BK2471_XVR_BASE_ADDR+0x120)
#define BK2471_XVR_REG_0x49		        REG32(BK2471_XVR_BASE_ADDR+0x124)
#define BK2471_XVR_REG_0x4A		        REG32(BK2471_XVR_BASE_ADDR+0x128)
#define BK2471_XVR_REG_0x4B		        REG32(BK2471_XVR_BASE_ADDR+0x12C)
#define BK2471_XVR_REG_0x4C		        REG32(BK2471_XVR_BASE_ADDR+0x130)
#define BK2471_XVR_REG_0x4D		        REG32(BK2471_XVR_BASE_ADDR+0x134)
#define BK2471_XVR_REG_0x4E		        REG32(BK2471_XVR_BASE_ADDR+0x138)
#define BK2471_XVR_REG_0x4F		        REG32(BK2471_XVR_BASE_ADDR+0x13C)
#define BK2471_XVR_REG_0x50		        REG32(BK2471_XVR_BASE_ADDR+0x140)
#define BK2471_XVR_REG_0x51		        REG32(BK2471_XVR_BASE_ADDR+0x144)
#define BK2471_XVR_REG_0x52		        REG32(BK2471_XVR_BASE_ADDR+0x148)
#define BK2471_XVR_REG_0x53		        REG32(BK2471_XVR_BASE_ADDR+0x14C)


#define BK2471_XVR_REG_0x58		        REG32(BK2471_XVR_BASE_ADDR+0x160)
#define BK2471_XVR_REG_0x59		        REG32(BK2471_XVR_BASE_ADDR+0x164)
#define BK2471_XVR_REG(n)				REG32(BK2471_XVR_BASE_ADDR+(n)*4)
#pragma anon_unions
typedef struct HW_XVR_3231S{
	union{
		WO uint32 REG_0x0;
		WO struct{
			uint32 closeloopen_sel:1;
			//selection of the signal closeloopEn source
			uint32 channel_range_en_tx:1;
			//Aditional cap on VCO n/p line to wider VCO tuning range
			uint32 channel_range_en_rx:1;
			//Aditional cap on VCO n/p line to wider VCO tuning range
			uint32 Itune_double_en_tx:1;
			// 1->ennable VCO ib doubled ; 0->normal VCO ib;no use in BK3231S
			uint32 Itune_double_en_rx:1;
			// 1->ennable VCO ib doubled ; 0->normal VCO ib;no use in BK3231S
			uint32 en_ampdet_tx:1;
			//Enable auto AMP detector at TX VCO
			uint32 en_ampdet_rx:1;
			//Enable auto AMP detector at RX VCO
			uint32 N_in:13;
			//The N counter value in manual control mode
			uint32 R_tx:6;
			//TX PLL Ref CLK divider ratio
			uint32 R_rx:6;
			//RX PLL Ref CLK divider ratio
		};
	};
	union{
		WO uint32 REG_0x1;
		WO struct{
			uint32 cken_spi:1;
			// 1-> disable ref to PLL; 0 -> normal operation
			uint32 tristate_spi:1;
			//PFD tristate enable
			uint32 cphalf_en:1;
			//charge pump output connected to vdd/2 during transmitter.
			uint32 lvref:2;
			//PLL unlock detection narrow voltage range control;11-00: (0.55/0.45/0.35/0.25)V,default=0.35
			uint32 hvref:2;
			//PLL unlock detection wide voltage range control;11-00: (1.25/1.15/1.05/0.95)V,default=1.15
			uint32 errdet_spien:1;
			//unlock detection enable
			uint32 NWvco_tx:3;
			//TX VCO nwell bias voltage control
			uint32 Itune_cp:2;
			//ib control of charge pump
			uint32 bypass_cphalf:1;
			//charge pump output connected to vdd/2 during transmitter.
			uint32 Rvco_tx:3;
			//RX VCO bias current control
			uint32 Rvco_rx:3;
			//TX VCO bias current control
			uint32 bwswen_tx:1;
			//Tx loop banWidth auto switch enable
			uint32 bwswen_rx:1;
			//Rx loop banWidth auto switch enable
			uint32 bypass_closeloopenEn:1;
			//bypass the closeloop controlling come from the digital part by spi
			uint32 Icp_rxn:3;
			//RX PLL  charge pump current control with narrow loop banWidth;000-111: 40/80/160/320uA(ibias=20uA,Icpdouble=0);000-111: 80/160/320/640uA(ibias=20uA,Icpdouble=0)
			uint32 Icp_rxw:3;
			//RX PLL  charge pump current control with wide loop banWidth;000-111: 40/80/160/320uA(ibias=20uA,Icpdouble=0);100-111: 80/160/320/640uA(ibias=20uA,Icpdouble=1)
			uint32 Icp_txn:3;
			//TX PLL charge pump current control;000-111: 40/80/160/320uA(ibias=20uA,Icpdouble=0);000-111: 80/160/320/640uA(ibias=20uA,Icpdouble=1)
		};
	};
	union{
		WO uint32 REG_0x2;
		WO struct{
			uint32 :1;
			//no use
			uint32 band_manual:1;
			// 1-> manual VCO bandcali; 0-> auto VCO bandcali
			uint32 spi_reset:1;
			//Reset spi of SDM in PLL
			uint32 Rx_fsel:1;
			//0-> 8/7 LO; 1->16/15 LO in Rx mode
			uint32 itune_vco_tx:4;
			//ib TxVCO tuning 0000(min), F(max)
			uint32 itune_vco_rx:4;
			//ib RxVCO tuning 0000(min), F(max)
			uint32 Ioffsetctrl:2;
			//charge pump offset current control
			uint32 Upoffseten:1;
			//charge pump source current offset enable
			uint32 Dnoffseten:1;
			//charge pump sink current offset enable
			uint32 PArampdly_ctrl:1;
			//PA buffer power on timing control.(BK3431 NC)
			uint32 TXENSPI:1;
			//TX PLL spi power on enable
			uint32 RXENSPI:1;
			//RX PLL spi power on enable
			uint32 Nrsten:1;
			//N counter reset enable during PLL power on
			uint32 selvcopol:1;
			//PFD polarity control
			uint32 :1;
			//no use
			uint32 reset:1;
			//PLL reset(0->1->0)
			uint32 bandm:8;
			//VCO band manual control (bandm<3:0>  is shared with loopRzctx<2:0>)
			uint32 manual:1;
			//VCO band manual control enable
		};
	};
	union{
		WO uint32 REG_0x3;
		WO struct{
			uint32 rxsw_vco:3;
			//band cap switch ctr word of rx vco
			uint32 Icpdouble:1;
			//control the ICP of RFPLL
			uint32 halfdelay_zero:2;
			//PFD reset delay of RFPLL
			uint32 :4;
			//no use
			uint32 txsw_vco:3;
			//band cap switch ctr word of tx vco
			uint32 :5;
			//no use
			uint32 calcken:1;
			//cut the clock to the bandcal of RFPLL,'0' is active
			uint32 bwswcken:1;
			//cut the clock to the counter of BWSW,'0' is active
			uint32 closeloopen_bypass:1;
			//not used (NC)
			uint32 rx_intmod:1;
			//RX loop intmod enable
			uint32 tx_intmod:1;
			//TX loop intmod enable
			uint32 icp_txw:3;
			//TX PLL  charge pump current control with wide loop banWidth;000-111: 40/80/160/320uA(ibias=20uA,Icpdouble=0);000-111: 80/160/320/640uA(ibias=20uA,Icpdouble=0)
			uint32 tdsel_rx:2;
			//transit time of fast lock and slow lock in rx mode
			uint32 tdsel_tx:2;
			//transit time of fast lock and slow lock in tx mode
			uint32 fbdivtst_en:1;
			//feed back divider test enable via test MUX(looptest)
			uint32 kcalien_spi:1;
			//Enable Kmod calibration via spi
		};
	};
	union{
		WO uint32 REG_0x4;
		WO struct{
			uint32 ForceOnPABuf1:1;
			//force on the first stage buffer of PA,[0]
			uint32 ForceOnTxLOBuf:1;
			//force on the Tx Lo buffer,
			uint32 DVthL_RSSIIF:3;
			//IF RSSI controlling
			uint32 DVthH_RSSIIF:3;
			//IF RSSI controlling
			uint32 vcovbgfastenb:1;
			//enable the faster settling of vbg to VCO ldo,[8]
			uint32 TrxLOVldoVsel:2;
			//Tx/Rx LO buffer ldo vout selection: 11->00 (1.6/1.5/1.4/1.4)V
			uint32 TrxVcoldoVsel:2;
			//VCO LDO vout selection:11->00 (1.6/1.5/1.4/1.4)V
			uint32 PAbufldoVsel:2;
			//PAbuf LDO vout selection: 11->00 (1.6/1.5/1.4/1.4)V
			uint32 PAldoVsel:2;
			//PA LDO vout selection:11->00 (1.7/1.6/1.5/1.4)V
			uint32 PAHqEn:1;
			//Enable cross MOS to enahace Q of balun,[17]
			uint32 PAvbnSel:3;
			//PA nMOS bias voltage selection
			uint32 PAvbpSel:3;
			//PA pMOS bias voltage selection
			uint32 gPAspi:5;
			//Controlling gain of PA, from -20dBm pout to +4dBm,[24]
			uint32 gPAdspEn:1;
			//Enable gain ctr from dsp: 0=spi.1=dsp
			uint32 gPAbuf:1;
			//gPAbuf=1: 0dBm pout level; 0: -20dBm pout level
			uint32 PAbuframpEn:1;
			//Enable ramping PA buffer gain step
		};
	};
	union{
		WO uint32 REG_0x5;
		WO struct{
			uint32 :3;
			//no use
			uint32 :1;
			//no use
			uint32 aLoopldoVsel:2;
			//anaLoop in RFPLL LDO vout selection:(11->00)1.6/1.5/1.4/1.4V
			uint32 dLoopldoVsel:2;
			//digLoop in RFPLL LDO vout selection:(11->00)1.6/1.5/1.4/1.4V
			uint32 MixlodVsel:2;
			//Mixer LDO vout selection:(11->00)1.6/1.5/1.4/1.4V
			uint32 LNAldoVsel:2;
			//LNA LDO vout selection:(11->00)1.6/1.5/1.4/1.4V
			uint32 bypass_txflt:1;
			//bypass the filter of txif,replace by RC filter
			uint32 :1;
			//no use
			uint32 NWMODn:3;
			//Modn varactor NWELL voltage adjusting
			uint32 NWMODp:3;
			//Modp varactor NWELL voltage adjusting
			uint32 txif_vcm:3;
			//vcm voltage of txif
			uint32 txif_modCtr:4;
			//controlling the output range of the DAC in the TXIF(by controlling resistor array)
			uint32 txif_modT10:1;
			//Under TxIF test mode: 0 (din of DAC<7:0>=0); 1 (din of DAC<7:0>=1);
			uint32 txif_modTen:1;
			// 1->enable test TxIF; 0->disable test TxIF
			uint32 txif_modinv:1;
			//switch Ioutp/n of DAC in TXIF
			uint32 txif_atsten:1;
			//enable test output of TXIF via TestMux
			uint32 spi_triger:1;
			//spi triger toggling bwtween 1 and 0 to calibrate RFPLL to the relative frequency
		};
	};
	union{
		WO uint32 REG_0x6;
		WO struct{
			uint32 regamp:4;
			//amp controlling of 16M crystal oscillator
			uint32 pwdIFADC1V_Q_spi:1;
			//pwd controlling of IF ADC Q path by spi
			uint32 pwdIFADC1V_I_spi:1;
			//pwd controlling of IF ADC I path by spi
			uint32 ifadcpwd_bypass_I:1;
			//bypass the pwd form the digital of I path in the IF ADC,'1'active
			uint32 ifadcpwd_bypass_Q:1;
			//bypass the pwd form the digital of Q path in the IF ADC,'1'active
			uint32 Mix2ldoVsel:2;
			//sel the ldo output voltage of the second stage mixer
			uint32 dgn3dBI2V:1;
			//decrease the gain of I2V by 3dB
			uint32 dhghar:1;
			//controlling the gain of LNA
			uint32 dqhLNA:1;
			//enhance the Q of the output of LNA
			uint32 dvth1:2;
			//controlling the voltage bias of the first stage mixer
			uint32 dvth2:2;
			//controlling the voltage bias of the second stage mixer
			uint32 dvcmTIA:1;
			//controlling the VCM of TIA in the RxFE
			uint32 dibTIA:3;
			//controlling the bias current of TIA in the RxFE
			uint32 diRxGm:2;
			//controlling the bias current of Gm in the RxFE
			uint32 diRxLNA:3;
			//controlling the bias current of LNA
			uint32 gI2Vspi:2;
			//I2V gain(default:max, step:6dB)
			uint32 gPLNAspi:2;
			//LNA gain(default:max, step:6dB)
			uint32 RxRFAGCEn:1;
			//Enable RxRF gain ctr: 0=spi, 1=dsp
			uint32 I2VtstEn:1;
			//Enable I2V test: 1=enable, 0=disable
		};
	};
	union{
		WO uint32 REG_0x7;
		WO struct{
			uint32 TstldoVsel:2;
			//Test Mux ldo Vout selection: 11->00 (1.6/1.5/1.4/1.4V)
			uint32 SARADCldoVsel:2;
			//SARADC ldo Vout selection: 11->00 (1.6/1.5/1.4/1.4V)
			uint32 ChAtten:3;
			//set relative attenuation at SAR ADC input
			uint32 EnAtt:1;
			//enable attenuation at SAR ADC input
			uint32 SARADCBufEn:1;
			//bypass the buffer(follower) at input of ADC,'0' active
			uint32 DVthL_RSSIRF:3;
			//controlling the reference voltage in the RSSI
			uint32 DVthH_RSSIRF:3;
			//controlling the reference voltage in the RSSI
			uint32 :3;
			//NC
			uint32 pwdfCaliEn:1;
			//filter calibration command
			uint32 trim:5;
			//calibrated filter ctr word
			uint32 fTrimMode:1;
			//filter calibration command
			uint32 fCaliPwd:1;
			//filter calibration command
			uint32 fcaliStart:1;
			//filter calibration command
			uint32 atSel:3;
			//Under analog test mode: 000 (0: RxIF_Qn/p);  011 (3: RxIF_In/p); 010 (2: TxIFp/n); 001 (1: I2VTst_Ip/n); 100 (4: I2VTst Qp/n)
			uint32 digtstSel:1;
			//under digital test mode: 0->clk32KXtal/32KRC = ATON/P; 1-> ckTst48M/looptst = ATON/P
			uint32 digtstEn:1;
			//0-> analog test mode; 1->digital test mode
		};
	};
	union{
		WO uint32 REG_0x8;
		WO struct{
			uint32 :2;
			//NC
			uint32 IFADCldoVsel:2;
			//IFADC ldo Vout selection: 11->00 (1.6/1.5/1.4/1.4V)
			uint32 TrxIFldoVsel:2;
			//Trx IF ldo Vout selection: 11->00 (1.6/1.5/1.4/1.4V)
			uint32 IFADC_ModeSel:5;
			//ADC mode status switch in spi mode
			uint32 IFADC_ModeEn:1;
			// 1->spi mode; 0->auto mode
			uint32 ItuneIFADC:2;
			//IF ADC bias current selection
			uint32 ItuneDCoffOPA:2;
			//DC-offset cancellation OPA bias current selection
			uint32 ItuneFltOPA:3;
			//RxIF filter OPA bias current selection
			uint32 vcmRxIF:3;
			//Rx IF chain vcm selection
			uint32 gPGA:2;
			//gain ctr of PGA: 11->00 (18/12/6/0 dB)
			uint32 gFlt3rd:1;
			//gain ctr of 3rd stage of IF filter: 1/0 (6/0 dB)
			uint32 gFlt2nd:1;
			//gain ctr of 2nd stage of IF filter: 1/0 (6/0 dB)
			uint32 gFlt1st:1;
			//gain ctr of 1st stage of IF filter: 1/0 (6/0 dB)
			uint32 RxIFAGCEn:1;
			//Enable gain ctr of RxIF from dsp: 0=spi, 1=dsp
			uint32 qPGAEnb:1;
			//Turn off q-path PGA: 1=off, 0=on
			uint32 DCoffsetEnb:1;
			//Enalbe DC-offset cancellation circuit
			uint32 RxIFtstSel:1;
			//RxIF test source selecetion: 1/0 = filter/PGA output
			uint32 RxIFtstEn:1;
			//Enalbe test of RxIF
		};
	};
	union{
		WO uint32 REG_0x9;
		WO struct{
			uint32 SpipwdCKpllbuf:1;
			//soft ware controlling the clk buffer in the 16M crystal oscillator when autopwdCKpllbuf=0
			uint32 autopwdCKpllbuf:1;
			//auto controlling the clk buffer in the 16M crystal oscillator,'1' is active
			uint32 XtalAmp:3;
			//16MXtal swing selection
			uint32 digpll_spirst:1;
			//reset logic circuits in digPLL
			uint32 lock_spi48M:1;
			// 1->CK48M==1; 0->Normal output
			uint32 openloop_digpll_en:1;
			//Open loop of digPLL
			uint32 clk16Mto32K_sel:1;
			//choose the 32K from the 16M crystal oscillator,'1' is active
			uint32 digpll_pwd_spi:1;
			//enable the digital pll from spi
			uint32 pwd_digpll_pfd:1;
			//enable the PFD in the digital pll when digpll_pwd_spi=1
			uint32 pwd_digpll_cp:1;
			//enable the charge pump in the digital pll when digpll_pwd_spi=1
			uint32 pwd_digpll_vco:1;
			//enable the vco in the digital pll when digpll_pwd_spi=1
			uint32 digpll_ictrcp:4;
			//ib of  cp in dig48MPLL: 0-150uA step=10uA
			uint32 digpll_cp:2;
			//adjust the charge pump current in the 48M digital pll
			uint32 digpll_R1_pr:3;
			//controlling bits of the resistor of zero point of the loop filter in the 48M digital pll
			uint32 ck48MtstEn:1;
			//Enable test 48M PLL output
			uint32 halfBand32kRC:1;
			// 1->switch on additional 1LSB cap at 32KRC
			uint32 tsten32kRC:1;
			//Enable test 32KRC
			uint32 tsten32kXtal:1;
			//Enable test 32KXtal
			uint32 clk32kSel:1;
			// 1->clk32KXtal; 0->clk32KRC(def)
			uint32 pwd32kXtalspi:1;
			//pwd of 32K Xtal from spi
			uint32 ib32kXtal:2;
			//ib control of 32K Xtal
			uint32 clk32kXtalext_En:1;
			//enable the external clock input in the 32k crystal oscillator,'1' active
			uint32 xtal16MEn2:1;
			//enable the high PSRR mode in the 16M crystal oscillator
		};
	};
	union{
		WO uint32 REG_0xA;
		WO struct{
			uint32 clk16M_sel:1;
			//sel the 16M clock source, it is 16M xtal or DCO, default=0, clock is from 16M xtal
			uint32 dco_trigger:1;
			//calibrate the dco frequency to 16M by toggling from 0 to 1, then to 0
			uint32 dco_manual:1;
			//set the dco to manual mode
			uint32 dcospi:7;
			//controlling the frequency of DCO by spi
			uint32 boostvsel:3;
			//set the boost output voltage from 3.0 to 3.6,111 is no use
			uint32 boostfsel:1;
			//set the working frequency of boost
			uint32 clktst32k_sel:1;
			//sel the testing signal of 32k,1 output rc 32k,0 output xtal 32k
			uint32 clktsten_16mdco:1;
			//enable the testing output in the 16M DCO
			uint32 pwd_digldobuf:1;
			//controlling the test buffer in the digital ldo
			uint32 digldo_sel:1;
			//set the digital ldo output,1 output 1.5V,0 output 1.2V
			uint32 boostinvsel:2;
			//input voltage controlling in the boost
			uint32 :12;
			//NC
		};
	};
	union{
		uint32 REG_0xB;
		struct{
			uint32 Analog_CfgB:32;
			//模拟SPI寄存器配置11
		};
	};
	union{
		uint32 REG_0xC;
		struct{
			uint32 Analog_CfgC:32;
			//模拟SPI寄存器配置12
		};
	};
	union{
		uint32 REG_0xD;
		struct{
			uint32 Analog_CfgD:32;
			//模拟SPI寄存器配置13
		};
	};
	union{
		uint32 REG_0xE;
		struct{
			uint32 Analog_CfgE:32;
			//模拟SPI寄存器配置14
		};
	};
	union{
		uint32 REG_0xF;
		struct{
			uint32 Analog_CfgF:32;
			//模拟SPI寄存器配置15
		};
	};
	union{
		RO uint32 REG_0x10;
		RO struct{
			uint32 chip_id:16;
			//Beken Chip ID
			uint32 fCaliCap:5;
			//Analog Read Back
			uint32 :11;
		};
	};
	union{
		RO uint32 REG_0x11;
		struct{
			uint32 device_id:32;
			//Beken Device ID
		};
	};
	union{
		RO uint32 REG_0x12;
		RO struct{
			uint32 rssi_o:8;
			//RSSI 输出
			uint32 adc_rssi_o:5;
			//ADC RSSI 输出
			uint32 :3;
			uint32 vco_kcal_o:13;
			//VCO_K 校准输出
			uint32 :3;
		};
	};
	union{
		RO uint32 REG_0x13;
		RO struct{
			uint32 pre_dc_o:12;
			//前导码频偏计算输出
			uint32 :4;
			uint32 sync_dc_o:12;
			//同步码频偏计算输出
			uint32 :4;
		};
	};
	union{
		RO uint32 REG_0x14;
		RO struct{
			uint32 tailer_dc_o:12;
			//Tailer频偏计算输出
			uint32 :4;
			uint32 cdyn_val:4;
			//vco cdyn 输出
			uint32 :3;
			uint32 tail_mode:1;
			//tail 模式
			uint32 match_phase_gfsk:3;
			//同步码匹配相位个数
			uint32 :1;
			uint32 unlock_status:1;
			//vco失锁状态标志
			uint32 :3;
		};
	};
	union{
		RO uint32 REG_0x15;
		RO struct{
			uint32 ber_bit_count:32;
			//BER total Bits Counter
		};
	};
	union{
		RO uint32 REG_0x16;
		RO struct{
			uint32 ber_err_count:32;
			//BER Error Bits Counter
		};
	};
	union{
		RO uint32 REG_0x17;
		RO struct{
			uint32 sync_err_bits:6;
			//同步码匹配时出错的bits数
			uint32 :26;
		};
	};
	union{
		RO uint32 REG_0x18;
		RO struct{
			uint32 rx_gain:9;
			//AGC计算出的RX Gain
			uint32 flt3_rssi_vld:1;
			//AGC 工作条件之一。必须为低
			uint32 lna_rssi_hvld:1;
			//AGC 工作条件之一。必须为高
			uint32 :21;
		};
	};
	RO uint32 REG_0x19;
	RO uint32 REG_0x1A;
	RO uint32 REG_0x1B;
	RO uint32 REG_0x1C;
	RO uint32 REG_0x1D;
	RO uint32 REG_0x1E;
	RO uint32 REG_0x1F;
	union{
		uint32 REG_0x20;
		struct{
			uint32 syncwordl:32;
			//配置的同步码低32位
		};
	};
	union{
		uint32 REG_0x21;
		struct{
			uint32 syncwordh:32;
			//配置的同步码高32位
		};
	};
	union{
		uint32 REG_0x22;
		struct{
			uint32 tx_freq_offset:32;
			//Sigma-Delta Modulation Tx Frequency Offset
		};
	};
	union{
		uint32 REG_0x23;
		struct{
			uint32 rx_freq_offset:32;
			//Sigma-Delta Modulation Rx Frequency Offset.;8/7 and 16/15 modulation are both available.
		};
	};
	union{
		uint32 REG_0x24;
		struct{
			uint32 cur_cfg_chn:7;
			//当前配置的频道数
			uint32 cur_cfg_pwr:4;
			//当前配置的输出功率值
			uint32 cur_cfg_win:5;
			//当前配置的同步窗口
			uint32 cur_cfg_agc:1;
			//当前配置的AGC允许位
			uint32 :15;
		};
	};
	union{
		uint32 REG_0x25;
		struct{
			uint32 test_pattern:8;
			//Test Pattern for Radio TX Testing
			uint32 test_pattern_en:1;
			//Test Pattern Enable
			uint32 pn9_hold_en:1;
			//PN9 Hold Enable （for Reading）
			uint32 pn9_recv_en:1;
			//PN9 Receive Mode
			uint32 pn9_send_en:1;
			//PN9 Send Mode
			uint32 test_tx_mode:1;
			//Radio In TX Mode
			uint32 test_radio:1;
			//Test Radio Enable
			uint32 test_edr2:1;
			//Test Radio in EDR2 Mode
			uint32 test_edr3:1;
			//Test Radio in EDR3 Mode
			uint32 vco_kcal_en:1;
			//VCO Kcal Enable bits
			uint32 rssi_cal_en:1;
			//Rssi Cal Enable bits(连续模式）
			uint32 :2;
			uint32 auto_syncword:1;
			//同步码选择;0:用XVR Reg0x20~21配置的同步码;1:用CEVA或者BK24传输过来的同步码
			uint32 lpo_clk_div:1;
			//CEVA IP 32kHz low-power clock division enable.;0：LPO=32kHz;1：LPO=3.2kHz
			uint32 tx_fracn_div2:1;
			//Sigma-Delta Modulation Tx output division enable;0: No division. Same as previous BK3231/3431.;1: Divided by 2
			uint32 rx_fracn_78:1;
			//Sigma-Delta Modulation Rx selection:;0: 16/15. Default for BK3231S.;1: 8/7. Same as previous BK3231, reserved.
			uint32 pn9_sync_sel:1;
			//SyncFind selection in PN9 Rx Test;0: Use syncfind.v and Reg0x20 to generate sync-find.;1: Use constant 24'h0295e5 to search sync-find.
			uint32 tx_div_auto:1;
			//Open-loop Tx moulation deviation auto-selection;0: Use the tx_div_cfg configuration;1: Auto-use the 160k/250k in BR/BLE/BK24 transmitte.
			uint32 tx_div_cfg:1;
			//Open-loop Tx moulation deviation selection;0: Use 160k deviation;1: Use 250k deviation
			uint32 bp_errdet_en:1;
			//Bypass PLL error detection enable;0: Detect PLL error when Tx is valid;1: Bypass the PLL error detection
			uint32 :4;
		};
	};
	union{
		uint32 REG_0x26;
		struct{
			uint32 mod_coefficient:10;
			//TX调制系数（+/-0.5），二进制补码
			uint32 rx_bit_phase:1;
			//接收序列的顺序：0-{0 1 2}，1-{ 2 1 0}
			uint32 tx_bit_phase:1;
			//发送序列的顺序：0-{0 1 2}，1-{2 1 0}
			uint32 pn25ena_cfg:1;
			//在PLL的N值上加入PN25的序列
			uint32 txb_reverse:1;
			//发送比特相位取反
			uint32 buf_latency:2;
			//收发数据的缓冲深度
			uint32 chn_compensate:11;
			//频点调制补偿系数（手动）
			uint32 sdm3bit_cfg:1;
			//VCO用分频SDM的选择：0.选择2阶SDM，1.选择3阶SDM
			uint32 clksel_cfg:1;
			//Fraction_N的时钟输出相位选择
			uint32 dac_reverse:1;
			// 2点调制（Polar调制）的DAC取反选择
			uint32 rx_if_select:1;
			//接收中频+/-选择
			uint32 syncdet_phase:1;
			//在参考时钟输出edr_sync：0:上升沿，1:下降沿
		};
	};
	union{
		uint32 REG_0x27;
		struct{
			uint32 compcoe_cfg:11;
			//噪声补偿的系数
			uint32 compdly_cfg:3;
			//噪声补偿的延迟控制
			uint32 res3bit_cfg:1;
			//噪声补偿是否选用3阶的SDM
			uint32 compena_cfg:1;
			//PLL的SDM是否使能噪声补偿
			uint32 accuena_cfg:1;
			//PLL噪声补偿时是否加入积分器
			uint32 sdm_sel_64m:1;
			//PLL的SDM是选择64M还是32M
			uint32 div2sel_cfg:1;
			//PLL的参考时钟是否需要除2
			uint32 if1m:1;
			//中频选择， 0：500K， 1：1M
			uint32 tbfalcon_reset:1;
			//tbfalcon_mod模块手动reset
			uint32 :11;
		};
	};
	union{
		uint32 REG_0x28;
		struct{
			uint32 Tdly_PLLms:8;
			//Delay Time from Posedge radio_on to pll_ms
			uint32 Tdly_PLLfs:8;
			//Delay Time from Posedge radio_on to pll_fs
			uint32 Tdly_PLLen:8;
			//Delay Time from Posedge radio_on to pll_en
			uint32 Tdly_VCOen:8;
			//Delay time from Posedge radio_on to vco_en
		};
	};
	union{
		uint32 REG_0x29;
		struct{
			uint32 State_index:9;
			//Delay time from Posedge slot_ctrl to Latch Analog Status
			uint32 tdly_errdet:6;
			//Delay time from Posedge slot_ctrl to assert errdet_en
			uint32 tdly_openlp:6;
			//Delay time from Posedge slot_ctrl to Clear txpll_lock
			uint32 :11;
		};
	};
	union{
		uint32 REG_0x2A;
		struct{
			uint32 rxslot_time:8;
			//The timing to assert slot_ctrl in rx Slot
			uint32 txslot_time:8;
			//The timing to assert slot_ctrl in tx Slot
			uint32 radion_time:8;
			//The timing to assert radio_on
			uint32 tdly_rxblkon:8;
			//Delay timer for RF Rx Block power-on after radio_on
		};
	};
	union{
		uint32 REG_0x2B;
		struct{
			uint32 rxslot_time_bk24:8;
			//The timing to assert slot_ctrl in rx Slot
			uint32 txslot_time_bk24:8;
			//The timing to assert slot_ctrl in tx Slot
			uint32 radion_time_bk24:8;
			//The timing to assert radio_on
			uint32 :8;
		};
	};
	uint32 REG_0x2C;
	union{
		uint32 REG_0x2D;
		struct{
			uint32 tdly_pa0fdn:5;
			//Delay time from negedge slot_ctrl to ramp_down
			uint32 tdly_pa0rup:5;
			//Delay time from posedge slot_ctrl to ramp_up
			uint32 pa0_dnslope:3;
			//PA0 Ramp_Down Slope Configure
			uint32 pa0_upslope:3;
			//PA0 Ramp_Up Slope Configure
			uint32 tdly_pa0off:5;
			//Delay time from negedge slot_ctrl to pa_off
			uint32 tdly_pa0on:5;
			//Delay time from posedge slot_ctrl to pa_on
			uint32 :6;
		};
	};
	uint32 REG_0x2E;
	uint32 REG_0x2F;
	union{
		uint32 REG_0x30;
		struct{
			uint32 :4;
			uint32 mod2dac_delay:4;
			//TX Freq调制到VCO DAC的延迟
			uint32 mod2sdm_delay:4;
			//TX Freq调制到PLL SDM的延迟
			uint32 fm_kmod_set:9;
			//TX调制Q的延迟（对于I/Q调制)
			uint32 fm_gain:9;
			//TX调制I的延迟（对于I/Q调制)
			uint32 bp_kmod:1;
			//Bypass Kmod calibration
			uint32 :1;
		};
	};
	union{
		uint32 REG_0x31;
		struct{
			uint32 tx_iq_switch:1;
			//PSK I/Q Switch in TX Polar modulation;;GFSK I/Q switch in TX IQ modulation
			uint32 gauss_gain:2;
			//GFSK deviation in Polar Modulation;0:10/64;1:11/64(default);2:12/64;3:13/64
			uint32 gauss_bt:2;
			//Gauss BT coffeicient selection;0 : No Filter(FSK);1 : BT = 0.5;2 : Reserved;3 : BT = 1.0
			uint32 freq_dly_opt:2;
			//Freq_dly_opt, 2~5 us
			uint32 :1;
			uint32 amp_gain:2;
			//PSK AMP amplitude gain in TX Polar Modulation ;0 : 0.5                                                      1 : 0.75                                                 2 : 1(default)                   3 : 1.25
			uint32 tx_freq_dir:1;
			//GFSK Direction of Freq in TX Polar Modulation
			uint32 :21;
		};
	};
	union{
		uint32 REG_0x32;
		struct{
			uint32 mod_q_dcset:8;
			//TX Mod Q DC offset Setted
			uint32 mod_i_dcset:8;
			//TX Mod I DC offset Setted
			uint32 mod_q_coef:8;
			//TX Mod Q Coefficient for mismatch
			uint32 mod_i_coef:8;
			//TX Mod I Coefficient for mismatch
		};
	};
	union{
		uint32 REG_0x33;
		struct{
			uint32 tx_8m_dly_num:3;
			//TX delay N in 8M domain
			uint32 tx_1m_dly_num:3;
			//TX delay N in 1M domain
			uint32 gfsk_latency:2;
			//Compensate TX GFSK and EDR23 Filter delays
			uint32 TX_rrc_select:1;
			//TX Chain RRC select;0: normal;1: wide mode
			uint32 :23;
		};
	};
	uint32 REG_0x34;
	uint32 REG_0x35;
	uint32 REG_0x36;
	uint32 REG_0x37;
	union{
		uint32 REG_0x38;
		struct{
			uint32 ble_ini_gain:9;
			//No description
			uint32 :3;
			uint32 ble_mix_g_st:2;
			//No description
			uint32 ble_lna_g_st:2;
			//No description
			uint32 :13;
			uint32 rx_freq_dir:1;
			//GFSK Direction of Freq in RX mode
			uint32 bit_reverse:1;
			//RX bit reverse
			uint32 iq_reverse:1;
			//RX I/Q Reverse
		};
	};
	union{
		uint32 REG_0x39;
		struct{
			uint32 :8;
			uint32 bp_dcflt:1;
			//dc filter bypass signal
			uint32 adc_gain:3;
			//adc_gain 1:0.5, 2:1 3:1.5 4:2 5:2.5 6:3, 7:3.5
			uint32 :4;
			uint32 eq_coef_ini:10;
			//No description
			uint32 eq_coef_set:1;
			//No description
			uint32 :5;
		};
	};
	union{
		uint32 REG_0x3A;
		struct{
			uint32 pre_dc_in:12;
			//preamble DC Manual setted value
			uint32 pre_dc_manual:1;
			//enable pre_dc_in
			uint32 pre_dc_bps:1;
			//Bypass preamble DC
			uint32 :2;
			uint32 tailer_dc_in:12;
			//tailer DC Manual setted value
			uint32 tailer_dc_manual:1;
			//enable tailer_dc_in
			uint32 tailer_dc_bps:1;
			//Bypass tailer DC
			uint32 :2;
		};
	};
	union{
		uint32 REG_0x3B;
		struct{
			uint32 :3;
			uint32 sel_bk24_sync:1;
			//Search for BK24 baseband sync-find in syncfind.v
			uint32 bp_eq:1;
			//Bypass equalizer
			uint32 auto_sync_mode:1;
			//force syncfind auto sync mode
			uint32 m0_phase_thrd:3;
			//GFSK M0 Phase Threshold
			uint32 m0_bits_thrd:3;
			//GFSK M0 Bits Threshold
			uint32 m_mode:1;
			//0 : 16 bits Syncword ;1 : 24 bits Syncword
			uint32 syncwd_order:1;
			//syncword order
			uint32 tail_sync_mode:1;
			//force syncfind tail_mode
			uint32 bps_demod:1;
			//直接解调输出，不做频偏校准
			uint32 pre_phase_thrd:3;
			//No description
			uint32 pre_sync_bps:1;
			//No description
			uint32 sync_err_thrd:4;
			//Max +/-7
			uint32 slot_delay:5;
			//used to compensate Slot start time
			uint32 dc_set_en:1;
			//0: dc_comp use dc_cal;1: dc_comp use dc_set
			uint32 samp_sel:1;
			//0：ADC 在上升沿采样;1：ADC 在下降沿采样
			uint32 test_bus_ena:1;
			//Test bus output enable
		};
	};
	union{
		uint32 REG_0x3C;
		struct{
			uint32 :1;
			uint32 lna_agc_0_tbl:4;
			//table 0 of lna agc
			uint32 agc_edtm:7;
			//agc end time
			uint32 agc_method:2;
			//agc method
			uint32 adc_agc_enable:1;
			//If agc_work=1, ADC AGC is controlled by adc_agc_enable.;If agc_work=0, ADC AGC is disable.
			uint32 lna_agc_enable:1;
			//If agc_work=1, LNA AGC is controlled by lna_agc_enable.;If agc_work=0, LNA AGC is disable.
			uint32 :2;
			uint32 lna_agc_2_tbl:7;
			//table 2 of lna agc
			uint32 lna_agc_1_tbl:7;
			//table 1 of lna agc
		};
	};
	union{
		uint32 REG_0x3D;
		struct{
			uint32 :2;
			uint32 lna_agc_4_tbl:7;
			//table 4 of lna agc
			uint32 lna_agc_3_tbl:7;
			//table 3 of lna agc
			uint32 :1;
			uint32 ini_rssi_time:3;
			//initial time of rssi settling
			uint32 pga_agc_0_tbl:5;
			//table 0 of pga agc
			uint32 lna_agc_5_tbl:7;
			//table 5 of lna agc
		};
	};
	union{
		uint32 REG_0x3E;
		struct{
			uint32 pga_agc_2_tbl:8;
			//table 2 of pga agc
			uint32 pga_agc_1_tbl:8;
			//table 1 of pga agc
			uint32 pga_agc_4_tbl:8;
			//table 4 of pga agc
			uint32 pga_agc_3_tbl:8;
			//table 3 of pga agc
		};
	};
	union{
		uint32 REG_0x3F;
		struct{
			uint32 adc_rssi_thrd:8;
			//adc rssi thrd
			uint32 pga_agc_5_tbl:8;
			//table 5 of pga agc
			uint32 bp_agc:1;
			//Bypass AGC
			uint32 ble_agc_mode:1;
			//AGC mode selection;0: BR AGC mode as previous BK3231;0: BLE AGC mode as BK3431
			uint32 agc_mthd:1;
			//No description
			uint32 :5;
			uint32 agc_stm:6;
			//No description
			uint32 :2;
		};
	};
    uint32 PA_RampTable[0x10];	//RF PA Ramp Up/Down的表格
}HW_XVR_3231S;

#endif
