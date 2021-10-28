#ifndef VS1053_TYPES_H_
#define VS1053_TYPES_H_

#include <stdio.h>

#define OPCODE_RD   0x03
#define OPCODE_WR   0x02

typedef unsigned int uint16_t;

/** VS1053b data */
typedef struct{
    sci_mode_t sci_mode;
    sci_status_t sci_status;
    sci_bass_t sci_bass;
    sci_clockf_t sci_clockf;
}vs1053_t;

/** SCI REGISTERS */
typedef enum{
    SCI_RW_MODE = 0,    /**< Mode control                   */
    SCI_RW_STATUS,      /**< Status of VS1053b              */
    SCI_RW_BASS,        /**< Built-in bass/treble control   */
    SCI_RW_CLOCKF,      /**< Clock freq + multiplier        */
    SCI_RW_DECODE_TIME, /**< Decode time in seconds         */
    SCI_RW_AUDATA,      /**< Misc. audio data               */
    SCI_RW_WRAM,        /**< RAM WR/RD value                */
    SCI_RW_WRAMADDR,    /**< Base @ for RAM WR/RD           */
    SCI_R_HDAT0,        /**< Stream header data 0           */
    SCI_R_HDAT1,        /**< Stream header data 1           */
    SCI_RW_AIADDR,      /**< Start address of application   */
    SCI_RW_VOL,         /**< Volume control                 */
    SCI_RW_AIADDR0,     /**< Application control register 0 */
    SCI_RW_AIADDR1,     /**< Application control register 1 */
    SCI_RW_AIADDR2,     /**< Application control register 2 */
    SCI_RW_AIADDR3      /**< Application control register 3 */
}sci_registers_t;


/** SCI_MODE values */
#define SM_DIFF_NORMAL          0
#define SM_DIFF_LEFT_INVERTED   1
#define SM_LAYER12_ALLOW        1
#define SM_RESET_ON             1
#define SM_CANCEL_ON            1
#define SM_EARSPEAKER_LO_ON     1
#define SM_TESTS_ALLOW          1
#define SM_STREAM_MODE          1
#define SM_EARSPEAKER_HI_ON     1
#define SM_DACT_EDGE_RISING     0
#define SM_DACT_EDGE_FALLING    1
#define SM_SDIORD_MSB_FIRST     0
#define SM_SDIORD_MSB_LAST      1
#define SM_SDISHARE_SPI         1
#define SM_SDINEW_VS1002_NATIVE 1
#define SM_ADPCM_REC_ACTIVE     1
#define SM_LINE1_MIC            0
#define SM_LINE1_LINE1          1
#define SM_CLK_RANGE_12_13      0
#define SM_CLK_RANGE_24_26      1
/** SCI_MODE bitfield */
typedef union{
    struct{
        uint16_t SM_DIFF : 1;           /**< Diferential : 0 normal, 1 left channel inverted    */
        uint16_t SM_LAYER12 : 1;        /**< allow MPEG layers 1 & 2 : 0 no, 1 yes              */
        uint16_t SM_RESET : 1;          /**< Soft reset : 0 no reset, 1 yes                     */
        uint16_t SM_CANCEL : 1;         /**< Cancel decoding : 0 no, 1 yes                      */
        uint16_t SM_EARSPEAKER_LO : 1;  /**< EarSpeaker low : 0 off, 1 active                   */
        uint16_t SM_TESTS : 1;          /**< Allow SDI tests : 0 not allowed, 1 allowed         */
        uint16_t SM_STREAM : 1;         /**< Stream mode : 0 no, 1 yes                          */    
        uint16_t SM_EARSPEAKER_HI : 1;  /**< EarSpeaker high : 0 off, 1 active                  */
        uint16_t SM_DACT : 1;           /**< DCLK active edge : 0 rising, 1 falling             */
        uint16_t SM_SDIORD : 1;         /**< SDI bit order : 0 MSb first, MSb last              */
        uint16_t SM_SDISHARE : 1;       /**< Share SPI chip select : 0 no, 1 yes                */
        uint16_t SM_SDINEW : 1;         /**< VS1002 native SPI modes : 0 no, 1 yes              */
        uint16_t SM_ADPCM : 1;          /**< PCM/ADPCM recording active, 0 no, 1 yes            */
        uint16_t reserved :1;           /**< reserved */
        uint16_t SM_LINE1:1;            /**< MIC/LINE1 slector : 0 MICP, 1 LINE1                */
        uint16_t SM_CLK_RANGE:1;        /**< Input clock range : 0 12..13MHZ, 1 24..26MHZ       */
    }field;
    uint16_t reg;
}sci_mode_t;

/** SCI_STATUS values */
#define SS_REF_SEL_1_23_V   0
#define SS_REF_SEL_1_65_V   1
#define SS_AD_CLOCK_6_MHZ   0
#define SS_AD_CLOCK_3_MHZ   1
#define SS_SWING_0_DB       0
#define SS_SWING_05_DB      1    
#define SS_SWING_1_DB       2
#define SS_SWING_15_DB      3
#define SS_SWING_2_DB       4
#define SS_SWING_25_DB      5
#define SS_SWING_3_DB       6
#define SS_SWING_35_DB      7
/** SCI_STATUS bitfield */
typedef union{
    struct{
        uint16_t SS_REF_SEL : 1;
        uint16_t SS_AD_CLOCK : 1;
        uint16_t SS_APDOWN1 : 1;
        uint16_t SS_APDOWN2 : 1;
        uint16_t SS_VER : 4;
        uint16_t reserved : 2;
        uint16_t SS_VCM_DISABLE : 1;
        uint16_t SS_VCM_OVERLOAD : 1;
        uint16_t SS_SWING : 3;
        uint16_t SS_DO_NOT_JUMP : 1;
    }field;
    uint16_t reg;
}sci_status_t;

/** SCI_BASS register */
typedef union{
    struct{
        uint16_t SB_FREQLIMIT : 4;
        uint16_t SB_AMPLITUDE : 4;
        uint16_t ST_FREQLIMIT : 4;
        uint16_t ST_AMPLITUDE : 4;
    }field;
    uint16_t reg;
}sci_bass_t;


/** SC_MULT values */
#define SC_MULT_XTALI       0
#define SC_MULT_XTALI_20    1
#define SC_MULT_XTALI_25    2
#define SC_MULT_XTALI_30    3
#define SC_MULT_XTALI_35    4
#define SC_MULT_XTALI_40    5
#define SC_MULT_XTALI_45    6
#define SC_MULT_XTALI_50    7
/** SC_ADD values */
#define SC_ADD_NONE         0
#define SC_ADD_XTALI_10     1
#define SC_ADD_XTALI_15     2
#define SC_ADD_XTALI_20     3
/** SCI_CLOCKF */
typedef union{
    struct{
        uint16_t SC_FREQ : 11;
        uint16_t SC_ADD : 2;
        uint16_t SC_MULT : 3;
    }field;
    uint16_t _reg;
}sci_clockf_t;


#endif /* VS1053_TYPES_H_ */