/*
 * ds90ub9702.c - TI DS90UB9702 deserializer and DS90UB971 serializer driver
 *
 * Copyright (c) 2021, HAIP Solutions GmbH
 *
 * This program is for the DS90UB9702 FDP Link IV deserializer in connection
 * with the DS90UB971 serializer from Texas Instruments
 *
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Every Change is declared with //NEW at the right side of the code or *NEW*
 * for changes made in more than one line of code.
 * Be aware that there is no change made to the DEBUG-Sections.
 */

#ifndef I2C_DS90UB9702_H
#define I2C_DS90UB9702_H

#include <linux/i2c.h>

//Important new registers:
/*
 * TI9702_REG_FPD3_PORT_SEL 0x4C (Channel Mapping select)
 * TI9702_REG_CHANNEL_MODE 0xE4 (overall channel modes)
 * TI9702_REG_CSI_PLL_DIV 0xC9 FREQUENCY (together with POST DIVIDER)
 * TI9702_REG_IQ_DIV 0xC2 POST DIVIDER
 *
 *
 */

/*------------------------------------------------------------------------------
 * Deserializer registers
 *----------------------------------------------------------------------------*/
#define TI9702_REG_I2C_DEV_ID 0x00
#define TI9702_DES_ID         0
#define TI9702_DEVICE_ID      1

#define TI9702_REG_RESET_CTL    0x01       //NEW NAME OLD: _REG_RESET
#define TI9702_DIGITAL_RESET0   0
#define TI9702_DIGITAL_RESET1   1
#define TI9702_RESTART_AUTOLOAD 2
#define TI9702_GPIO_HOLD_B      5       //NEW


#define TI9702_REG_GENERAL_CFG           0x2
#define TI9702_FORCE_REFCLK_DET          0
#define TI9702_RX_PARITY_CHECKER_ENABLE  1
#define TI9702_OUTPUT_SLEEP_STATE_SELECT 2
#define TI9702_OUTPUT_ENABLE             3
#define TI9702_OUTPUT_EN_MODE            4
#define TI9702_I2C_MASTER_EN             5
#define TI9702_SPI_MODE_EN               6   //NEW

#define TI9702_REG_REV_MASK_ID 0x03   //NEW NAME OLD: REG_REVISION
#define TI9702_MASK_ID         0
#define TI9702_REVISION_ID     4

#define TI9702_REG_DEVICE_STS 0x04
// #define TI9702_LOCK        2
// #define TI9702_PASS        3
#define TI9702_REFCLK_VALID   4
#define TI9702_RX_PLL_LOCK    5      //NEW
#define TI9702_CFG_INIT_DONE  6
#define TI9702_CFG_CKSUM_STS  7

#define TI9702_REG_PAR_ERR_THOLD_HI 0x5
#define TI9702_PAR_ERR_THOLD_HI     0

#define TI9702_REG_PAR_ERR_THOLD_LO 0x6
#define TI9702_PAR_ERR_THOLD_LO     0

#define TI9702_REG_BCC_WD_CTL             0x07
#define TI9702_BCC_WATCHDOG_TIMER_DISABLE 0
#define TI9702_BCC_WATCHDOG_TIMER         1

#define TI9702_REG_I2C_CTL1        0x08
#define TI9702_I2C_FILTER_DEPTH    0
#define TI9702_I2C_SDA_HOLD        4
#define TI9702_LOCAL_WRITE_DISABLE 7

#define TI9702_REG_I2C_CTL2          0x09
#define TI9702_I2C_BUS_TIMER_DISABLE 0
#define TI9702_I2C_BUS_TIMER_SPEEDUP 1
#define TI9702_SDA_OUTPUT_DELAY      2
#define TI9702_SDA_OUTPUT_SETUP      4

#define TI9702_REG_SCL_HIGH_TIME 0x0a
#define TI9702_SCL_HIGH_TIME     0

#define TI9702_REG_SCL_LOW_TIME 0x0b
#define TI9702_SCL_LOW_TIME     0

#define TI9702_REG_RX_PORT_CTL 0x0c
#define TI9702_PORT0_EN        0
#define TI9702_PORT1_EN        1
// #define TI9702_LOCK_SEL        2
// #define TI9702_PASS_SEL        4
#define TI9702_PORT2_EN        2
#define TI9702_PORT3_EN        3
#define TI9702_BCC0_MAP        4
#define TI9702_BCC1_MAP        5
#define TI9702_BCC2_MAP        6
#define TI9702_BCC3_MAP        7

#define TI9702_REG_IO_CTL        0x0d
#define TI9702_IMP_CTRL          0       //NEW
#define TI9702_IO_SUPPLY_MODE    4
#define TI9702_IO_SUPPLY_MODE_OV 6
#define TI9702_SEL3P3V           7

#define TI9702_REG_GPIO_PIN_STS 0x0e
#define TI9702_GPIO_STS         0
// #define TI9702_GPIO0_STS        0
// #define TI9702_GPIO1_STS        1
// #define TI9702_GPIO2_STS        2
// #define TI9702_GPIO3_STS        3
// #define TI9702_GPIO4_STS        4
// #define TI9702_GPIO5_STS        5
// #define TI9702_GPIO6_STS        6

#define TI9702_REG_GPIO_INPUT_CTL 0x0f
// #define TI9702_GPIO_INPUT_EN      0
#define TI9702_GPIO0_INPUT_EN     0
#define TI9702_GPIO1_INPUT_EN     1
#define TI9702_GPIO2_INPUT_EN     2
#define TI9702_GPIO3_INPUT_EN     3
#define TI9702_GPIO4_INPUT_EN     4
#define TI9702_GPIO5_INPUT_EN     5
#define TI9702_GPIO6_INPUT_EN     6
#define TI9702_GPIO7_INPUT_EN     7

#define TI9702_REG_GPIO0_PIN_CTL 0x10
#define TI9702_GPIO0_OUT_EN      0
#define TI9702_GPIO0_OUT_VAL     1
#define TI9702_GPIO0_OUT_SRC     2
#define TI9702_GPIO0_OUT_SEL     5

#define TI9702_REG_GPIO1_PIN_CTL 0x11
#define TI9702_GPIO1_OUT_EN      0
#define TI9702_GPIO1_OUT_VAL     1
#define TI9702_GPIO1_OUT_SRC     2
#define TI9702_GPIO1_OUT_SEL     5

#define TI9702_REG_GPIO2_PIN_CTL 0x12
#define TI9702_GPIO2_OUT_EN      0
#define TI9702_GPIO2_OUT_VAL     1
#define TI9702_GPIO2_OUT_SRC     2
#define TI9702_GPIO2_OUT_SEL     5

#define TI9702_REG_GPIO3_PIN_CTL 0x13
#define TI9702_GPIO3_OUT_EN      0
#define TI9702_GPIO3_OUT_VAL     1
#define TI9702_GPIO3_OUT_SRC     2
#define TI9702_GPIO3_OUT_SEL     5

#define TI9702_REG_GPIO4_PIN_CTL 0x14
#define TI9702_GPIO4_OUT_EN      0
#define TI9702_GPIO4_OUT_VAL     1
#define TI9702_GPIO4_OUT_SRC     2
#define TI9702_GPIO4_OUT_SEL     5

#define TI9702_REG_GPIO5_PIN_CTL 0x15
#define TI9702_GPIO5_OUT_EN      0
#define TI9702_GPIO5_OUT_VAL     1
#define TI9702_GPIO5_OUT_SRC     2
#define TI9702_GPIO5_OUT_SEL     5

#define TI9702_REG_GPIO6_PIN_CTL 0x16
#define TI9702_GPIO6_OUT_EN      0
#define TI9702_GPIO6_OUT_VAL     1
#define TI9702_GPIO6_OUT_SRC     2
#define TI9702_GPIO6_OUT_SEL     5

#define TI9702_REG_GPIO7_PIN_CTL 0x17
#define TI9702_GPIO7_OUT_EN      0
#define TI9702_GPIO7_OUT_VAL     1
#define TI9702_GPIO7_OUT_SRC     2
#define TI9702_GPIO7_OUT_SEL     5

#define TI9702_REG_FS_CTL    0x18    //FS for FrameSync
#define TI9702_FS_GEN_ENABLE 0
#define TI9702_FS_GEN_MODE   1
#define TI9702_FS_INIT_STATE 2
#define TI9702_FS_SINGLE     3
#define TI9702_FS_MODE       4

#define TI9702_REG_FS_HIGH_TIME_1    0x19
#define TI9702_FRAMESYNC_HIGH_TIME_1 0

#define TI9702_REG_FS_HIGH_TIME_0    0x1A
#define TI9702_FRAMESYNC_HIGH_TIME_0 0

#define TI9702_REG_FS_LOW_TIME_1    0x1B
#define TI9702_FRAMESYNC_LOW_TIME_1 0

#define TI9702_REG_FS_LOW_TIME_0    0x1C
#define TI9702_FRAMESYNC_LOW_TIME_0 0

#define TI9702_REG_MAX_FRM_HI 0x1d
#define TI9702_MAX_FRAME_HI   0

#define TI9702_REG_MAX_FRM_LO 0x1e
#define TI9702_MAX_FRAME_LO   0

#define TI9702_REG_CSI_PLL_CTL 0x1f
#define TI9702_CSI_TX_SPEED    0    //CSI timing register select:Strap
#define TI9702_REF_CLK_MODE    2
#define TI9702_SEL_OSC_200M    3
#define TI9702_CSI_TX_SPEED2   4    //NEW CSI timing register select MSB Strap (S. 94)

#define TI9702_REG_FWD_CTL1  0x20
#define TI9702_RX0_MAP       0
#define TI9702_RX1_MAP       1
#define TI9702_RX2_MAP       2
#define TI9702_RX3_MAP       3
#define TI9702_FWD_PORT0_DIS 4
#define TI9702_FWD_PORT1_DIS 5
#define TI9702_FWD_PORT2_DIS 6
#define TI9702_FWD_PORT3_DIS 7

/* #define TI9702_REG_FWD_CTL2   0x21    //NEW
   #define TI9702_CSI0_RR_FWD       0
   #define TI9702_CSI1_RR_FWD       1
   #define TI9702_CSI0_SYNC_FWD     2
   #define TI9702_CSI1_SYNC_FWD     4
   #define TI9702_FWD_SYNC_AS_AVAIL 6
   #define TI9702_CSI_REPLICATE     7  */

#define TI9702_REG_FWD_STS           0x22
#define TI9702_FWD_SYNC0             0
#define TI9702_FWD_SYNC1             1
#define TI9702_FWD_SYNC_FAIL0        2
#define TI9702_FWD_SYNC_FAIL1        3
#define TI9702_CSI_REPLICATE_CSI0    4    //NEW
#define TI9702_CSI_REPLICATE_CSI1    5    //NEW

#define TI9702_REG_INTERRUPT_CTL     0x23
#define TI9702_IE_RX0                0
#define TI9702_IE_RX1                1
#define TI9702_IE_RX2                2
#define TI9702_IE_RX3                3
#define TI9702_IE_CSI_TX0            4
#define TI9702_IE_CSI_TX1            5
#define TI9702_IE_DEV                6   //NEW  Local Device Interrupt
#define TI9702_INT_EN                7

#define TI9702_REG_INTERRUPT_STS     0x24
#define TI9702_IS_RX0                0
#define TI9702_IS_RX1                1
#define TI9702_IS_RX2                2
#define TI9702_IS_RX3                3
#define TI9702_IS_CSI_TX0            4
#define TI9702_IS_CSI_TX1            5
#define TI9702_IS_DEV                6   //NEW Local Device Interrupt
#define TI9702_INT                   7

#define TI9702_REG_TS_CONFIG 0x25
#define TI9702_TS_MODE       0
#define TI9702_TS_FREERUN    1
#define TI9702_TS_AS_AVAIL   3
#define TI9702_TS_RES_CTL    4
#define TI9702_FS_POLARITY   6

#define TI9702_REG_TS_CONTROL 0x26
#define TI9702_TS_ENABLE0     0
#define TI9702_TS_ENABLE1     1
#define TI9702_TS_ENABLE2     2
#define TI9702_TS_ENABLE3     3
#define TI9702_TS_FREEZE      4

#define TS9702_TS_LINE_HI 0x27
#define TI9702_TS_LINE_HI 0

#define TI9702_REG_TS_LINE_LO 0x28
#define TI9702_TS_LINE_LO     0

#define TI9702_REG_TS_STATUS 0x29
#define TI9702_TS_VALID0     0
#define TI9702_TS_VALID1     1
#define TI9702_TS_VALID2     2
#define TI9702_TS_VALID3     3
#define TI9702_TS_READY      4

#define TI9702_REG_TIMESTAMP_P0_HI 0x2a
#define TI9702_TIMESTAMP_P0_HI     0

#define TI9702_REG_TIMESTAMP_P0_LO 0x2b
#define TI9702_TIMESTAMP_P0_LO     0

#define TI9702_REG_TIMESTAMP_P1_HI 0x2c
#define TI9702_TIMESTAMP_P1_HI     0

#define TI9702_REG_TIMESTAMP_P1_LO 0x2d
#define TI9702_TIMESTAMP_P1_LO     0

#define TI9702_REG_TIMESTAMP_P2_HI 0x2e
#define TI9702_TIMESTAMP_P2_HI     0

#define TI9702_REG_TIMESTAMP_P2_LO 0x2f
#define TI9702_TIMESTAMP_P2_LO     0

#define TI9702_REG_TIMESTAMP_P3_HI 0x30
#define TI9702_TIMESTAMP_P3_HI     0

#define TI9702_REG_TIMESTAMP_P3_LO 0x31
#define TI9702_TIMESTAMP_P3_LO     0

#define TI9702_REG_CSI_PORT_SEL    0x32
#define TI9702_TX_WRITE_PORT_0     0
#define TI9702_TX_WRITE_PORT_1     1
#define TI9702_TX_READ_PORT        4

#define TI9702_REG_CSI_CTL     0x33
#define TI9702_CSI_ENABLE      0
#define TI9702_CSI_CONTS_CLOCK 1
#define TI9702_CSI_ULP         2
#define TI9702_CSI_LANE_COUNT  4
#define TI9702_CSI_CAL_EN      6
#define TI9702_CSI_4_LANE      0
#define TI9702_CSI_3_LANE      1
#define TI9702_CSI_2_LANE      2
#define TI9702_CSI_1_LANE      3

#define TI9702_REG_CSI_CTL2     0x34
#define TI9702_CSI_CAL_PERIODIC 0
#define TI9702_CSI_CAL_SINGLE   1
#define TI9702_CSI_CAL_INV      2
#define TI9702_CSI_PASS_MODE    3
#define TI9702_CSI_CAL_LEN      4        //NEW
#define TI9702_CSI_CLK0_EN      6        //NEW
#define TI9702_CSI_CLK1_EN      7        //NEW

#define TI9702_REG_CSI_STS  0x35
#define TI9702_TX_PORT_PASS 0
#define TI9702_TX_PORT_SYNC 1
#define TI9702_TX_PORT_NUM  4

#define TI9702_REG_CSI_TX_ICR    0x36
#define TI9702_IE_CSI_PASS       0
#define TI9702_IE_CSI_PASS_ERROR 1
#define TI9702_IE_CSI_SYNC       2
#define TI9702_IE_CSI_SYNC_ERROR 3
#define TI9702_IE_RX_PORT_INT    4

#define TI9702_REG_CSI_TX_ISR     0x37
#define TI9702_IS_CSI_PASS        0
#define TI9702_IS_CSI_PASS_ERROR  1
#define TI9702_IS_CSI_SYNC        2
#define TI9702_IS_CSI_SYNC_ERROR  3
#define TI9702_IS_RX_PORT_INT     4

#define TI9702_REG_CSI_TEST_CTL   0x38    //NEW REG  (S. 104)
#define TI9702_CSI_TEST_MODE      0         //NEW
#define TI9702_FPD2CSI_TEST       4         //NEW
#define TI9702_CSI_BERT_HS        7         //NEW

#define TI9702_REG_CSI_TEST_PATT_HI   0x39    //NEW REG  (S. 105)
#define TI9702_CSI_TEST_PATT          0         //NEW

#define TI9702_REG_CSI_TEST_PATT_LO   0x3a    //NEW REG  (S. 105)
#define TI9702_CCI_TEST_PATT          0         //NEW

#define TI9702_REG_CSI_EXCLUSIVE_FWD1   0x3b    //NEW REG  (S. 105)
#define TI9702_CSI0_EXCLUSIVE_FWD       0         //NEW
#define TI9702_CSI1_EXCLUSIVE_FWD       4         //NEW

#define TI9702_REG_CSI_EXCLUSIVE_FWD2   0x3c    //NEW REG  (S. 106)
#define TI9702_REPLICATE_CSI2_SEL       6         //NEW
#define TI9702_EXCLUSIVE_FWD_EN         7         //NEW

#define TI9702_REG_REFCLK_FREQ          0x3d    //NEW REG (S. 106) (OLD: 0xa5)
#define TI9702_REFCLK_FREQ              0         //NEW

// REGISTER 0x3e - 0x40 RESERVED

/* #define TI9702_REG_SFILTER_CFG 0x41   //NEW NOT DEFINED ANYMORE
#define TI9702_SFILTER_MIN     0
#define TI9702_SFILTER_MAX     4  */

/* #define TI9702_REG_AEQ_CTL    0x42   //NEW NOT DEFINED ANYMORE
#define TI9702_AEQ_SFILTER_EN 0
#define TI9702_AEQ_OUTER_LOOP 1
#define TI9702_AEQ_2STEP_EN   2
#define TI9702_AEQ_SFIL_ORDER 3
#define TI9702_AEQ_ERR_CTL    4   */

/* #define TI9702_REG_AEQ_ERR_THOLD 0x43   //NEW NOT DEFINED ANYMORE
#define TI9702_AEQ_ERR_THRESHOLD 0 */

// REG 0x44 & REG 0x45 RESERVED

#define TI9702_REG_BCC_ERR_CTL      0x46
#define TI9702_BCC_FRAME_SEL        0
#define TI9702_FORCE_BCC_ERROR      3
#define TI9702_BCC_EN_ENH_ERROR     5
#define TI9702_BCC_EN_DATA_CHK      6
#define TI9702_BCC_ACK_REMOTE_READ  7

#define TI9702_REG_BCC_STATUS       0x47
#define TI9702_BCC_RESP_ERR         0
#define TI9702_BCC_SLAVE_TO         1
#define TI9702_BCC_SLAVE_ERR        2
#define TI9702_BCC_MASTER_TO        3
#define TI9702_BCC_MASTER_ERR       4
#define TI9702_BCC_SEQ_ERROR        5

// NEW REG 0x48 & REG 0x49 RESERVED  S. 101

#define TI9702_REG_BC_CAPABILITIES     0x4a  //NEW NAME   (S.108)
#define TI9702_ECC_CAP                 0     //NEW NAME
#define TI9702_ECC_GPIO_CAP            2     //NEW
#define TI9702_ECC_BCC_ONLY_CAP        3     //NEW
#define TI9702_DCA_CRC_CAP             4     //NEW

#define TI9702_REG_RAW_EMBED_DTYPE 0x4b
#define TI9702_EMBED_DTYPE_ID      0
#define TI9702_EMBED_DTYPE_EN      6

#define TI9702_REG_FPD3_PORT_SEL 0x4c
#define TI9702_RX_WRITE_PORT_0   0
#define TI9702_RX_WRITE_PORT_1   1
#define TI9702_RX_WRITE_PORT_2   2
#define TI9702_RX_WRITE_PORT_3   3
#define TI9702_RX_READ_PORT      4
#define TI9702_PHYS_PORT_NUM     6

#define TI9702_REG_RX_PORT_STS1 0x4d
#define TI9702_LOCK_STS         0
#define TI9702_PORT_PASS        1
#define TI9702_PARITY_ERROR     2
#define TI9702_BCC_ERROR        3
#define TI9702_LOCK_STS_CHG     4
#define TI9702_BCC_CRC_ERROR    5
#define TI9702_RX_PORT_NUM      6

#define TI9702_REG_RX_PORT_STS2  0x4e
#define TI9702_LINE_CNT_CHG      0
#define TI9702_NO_FPD3_CLK       1
#define TI9702_FREQ_STABLE       2
#define TI9702_CSI_ERROR         3
#define TI9702_BUFFER_ERROR      4
#define TI9702_FPD3_ENCODE_ERROR 5
#define TI9702_LINE_LEN_CHG      6
#define TI9702_LINE_LEN_UNSTABLE 7

#define TI9702_REG_RX_FREQ_HIGH 0x4f
#define TI9702_FREQ_CNT_HIGH    0

#define TI9702_REG_RX_FREQ_LOW 0x50
#define TI9702_FREQ_CNT_LOW    0

#define TI9702_REG_SENSOR_STS_0  0x51
#define TI9702_SENSOR_STS_0      0       //NEW (S.112)
/*#define TI9702_VOLT0_SENSE_ALARM 0
#define TI9702_VOLT1_SENSE_ALARM 1
#define TI9702_TEMP_SENSE_ALARM  2
#define TI9702_LINK_DETECT_ALARM 3
#define TI9702_BCC_ALARM         4
#define TI9702_CSI_ALARM         5 */

#define TI9702_REG_SENSOR_STS_1  0x52
#define TI9702_SENSOR_STS_1      0       //NEW (S.112)
/* #define TI9702_VOLT0_SENSE_LEVEL 0
#define TI9702_VOLT1_SENSE_LEVEL 4  */

#define TI9702_REG_SENSOR_STS_2 0x71
#define TI9702_SENSOR_STS_2     0        //NEW (S.113)
/* #define TI9702_TEMP_SENSE_LEVEL 0 */

#define TI9702_REG_SENSOR_STS_3  0x54
#define TI9702_SENSOR_STS_3      0        //NEW (S.113)
/* #define TI9702_CSI_CNTRL_ERR    0
#define TI9702_CSI_SYNC_ERR     1
#define TI9702_CSI_SOT_ERR      2
#define TI9702_CSI_CHKSUM_ERR   3
#define TI9702_CSI_ECC_2BIT_ERR 4  */

#define TI9702_REG_RX_PAR_ERR_HI 0x55
#define TI9702_PAR_ERROR_BYTE_1  0

#define TI9702_REG_RX_PAR_ERR_LO 0x56
#define TI9702_PAR_ERROR_BYTE_0  0

#define TI9702_REG_BIST_ERR_COUNT 0x57
#define TI9702_BIST_ERROR_COUNT   0

#define TI9702_REG_BCC_CONFIG          0x58
#define TI9702_BC_FREQ_SELECT          0
#define TI9702_BC_CRC_GENERATOR_ENABLE 3
#define TI9702_BC_ALWAYS_ON            4
#define TI9702_AUTO_ACK_ALL            5
#define TI9702_I2C_PASS_THROUGH        6
#define TI9702_I2C_PASS_THROUGH_ALL    7
#define TI9702_BC_FREQ_2M5             0
#define TI9702_BC_FREQ_1M              2
#define TI9702_BC_FREQ_25M             5
#define TI9702_BC_FREQ_50M             6
#define TI9702_BC_FREQ_250             7


#define TI9702_REG_DATAPATH_CTL1  0x59
#define TI9702_FC_GPIO_EN         0
#define TI9702_OVERRIDE_FC_CONFIG 7

// #define TI965_REG_DATAPATH_CTL2 0x5a

#define TI9702_REG_SER_ID       0x5b
#define TI9702_FREEZE_DEVICE_ID 0
#define TI9702_SER_ID           1

#define TI9702_REG_SER_ALIAS_ID 0x5c
#define TI9702_SER_AUTO_ACK     0
#define TI9702_SER_ALIAS_ID     1

#define TI9702_REG_SLAVE_ID0 0x5d
#define TI9702_SLAVE_ID0     1
#define TI9702_REG_SLAVE_ID1 0x5e
#define TI9702_SLAVE_ID1     1
#define TI9702_REG_SLAVE_ID2 0x5f
#define TI9702_SLAVE_ID2     1
#define TI9702_REG_SLAVE_ID3 0x60
#define TI9702_SLAVE_ID3     1
#define TI9702_REG_SLAVE_ID4 0x61
#define TI9702_SLAVE_ID4     1
#define TI9702_REG_SLAVE_ID5 0x62
#define TI9702_SLAVE_ID5     1
#define TI9702_REG_SLAVE_ID6 0x63
#define TI9702_SLAVE_ID6     1
#define TI9702_REG_SLAVE_ID7 0x64
#define TI9702_SLAVE_ID7     1

#define TI9702_REG_ALIAS_ID0    0x65
#define TI9702_SLAVE_AUTO_ACK_0 0
#define TI9702_ALIAS_ID0        1
#define TI9702_REG_ALIAS_ID1    0x66
#define TI9702_SLAVE_AUTO_ACK_1 0
#define TI9702_ALIAS_ID1        1
#define TI9702_REG_ALIAS_ID2    0x67
#define TI9702_SLAVE_AUTO_ACK_2 0
#define TI9702_ALIAS_ID2        1
#define TI9702_REG_ALIAS_ID3    0x68
#define TI9702_SLAVE_AUTO_ACK_3 0
#define TI9702_ALIAS_ID3        1
#define TI9702_REG_ALIAS_ID4    0x69
#define TI9702_SLAVE_AUTO_ACK_4 0
#define TI9702_ALIAS_ID4        1
#define TI9702_REG_ALIAS_ID5    0x6a
#define TI9702_SLAVE_AUTO_ACK_5 0
#define TI9702_ALIAS_ID5        1
#define TI9702_REG_ALIAS_ID6    0x6b
#define TI9702_SLAVE_AUTO_ACK_6 0
#define TI9702_ALIAS_ID6        1
#define TI9702_REG_ALIAS_ID7    0x6c
#define TI9702_SLAVE_AUTO_ACK_7 0
#define TI9702_ALIAS_ID7        1

#define TI9702_REG_PORT_CONFIG 0x6d
// #define TI9702_FPD3_MODE       0       //NEW RESERVED
// #define TI9702_COAX_MODE       2
#define TI9702_CSI_FWD_LEN     3
#define TI9702_CSI_FWD_ECC     4
#define TI9702_CSI_FWD_CKSUM   5
#define TI9702_CSI_WAIT_FS     6
#define TI9702_CSI_WAIT_FS1    7

#define TI9702_REG_BC_GPIO_CTL0 0x6e
#define TI9702_BC_GPIO0_SEL     0
#define TI9702_BC_GPIO1_SEL     4

#define TI9702_REG_BC_GPIO_CTL1 0x6f
#define TI9702_BC_GPIO2_SEL     0
#define TI9702_BC_GPIO3_SEL     4

#define TI9702_REG_RAW10_ID 0x70
#define TI9702_RAW10_ID     0        //NEW NAME
#define TI9702_RAW10_VC     6

#define TI9702_REG_RAW12_ID 0x71
#define TI9702_RAW12_ID     0        //NEW NAME
#define TI9702_RAW12_VC     6

/* #define TI9702_REG_CSI_VC_MAP 0x72  //NEW  see 0xa0 - 0xa7
#define TI9702_CSI_VC_MAP     0  */

#define TI9702_REG_LINE_COUNT_1  0x73
#define TI9702_LINE_COUNT_HI     0

#define TI9702_REG_LINE_COUNT_0  0x74
#define TI9702_LINE_COUNT_LO     0

#define TI9702_REG_LINE_LEN_1 0x75
#define TI9702_LINE_LEN_HI    0

#define TI9702_REG_LINE_LEN_0 0x76
#define TI9702_LINE_LEN_LO    0

#define TI9702_REG_FREQ_DET_CTL 0x77
#define TI9702_FREQ_LO_THR      0
#define TI9702_FREQ_STABLE_THR  4
#define TI9702_FREQ_HYST        6

#define TI9702_REG_MAILBOX_1 0x78      //NEW  OLD: _REG_MAILBOX_0
#define TI9702_MAILBOX_0     0

#define TI9702_REG_MAILBOX_2 0x79      //NEW  OLD: _REG_MAILBOX_1
#define TI9702_MAILBOX_1     0

#define TI9702_REG_CSI_RX_STS 0x7a
#define TI9702_ECC1_ERR       0
#define TI9702_ECC2_ERR       1
#define TI9702_CKSUM_ERR      2
#define TI9702_LENGTH_ERR     3

#define TI9702_REG_CSI_ERR_COUNTER 0x7b
#define TI9702_CSI_ERR_CNT         0

#define TI9702_REG_PORT_CONFIG2      0x7c
#define TI9702_FV_POLARITY           0
#define TI9702_LV_POLARITY           1
#define TI9702_AUTO_POLARITY         2
#define TI9702_DISCARD_ON_FRAME_SIZE 3
#define TI9702_DISCARD_ON_LINE_SIZE  4
#define TI9702_DISCARD_ON_PAR_ERR    5
#define TI9702_RAW10_8BIT_CTL        6

#define TI9702_REG_PORT_PASS_CTL 0x7d
#define TI9702_PASS_THRESHOLD    0
#define TI9702_PASS_WDOG_DIS     2
#define TI9702_PASS_PARITY_ERR   3
#define TI9702_PASS_LINE_SIZE    4
#define TI9702_PASS_LINE_CNT     5
#define TI9702_PASS_CLEAR_CNT    6
#define TI9702_PASS_DISCARD_EN   7

#define TI9702_REG_SEN_INT_RISE_CTL 0x7e
#define TI9702_SEN_INT_RISE_MASK    0

#define TI9702_REG_SEN_INT_FALL_CTL 0x7f
#define TI9702_SEN_INT_FALL_MASK    0

// REG 0x80 - 0x87 RESERVED

#define TI9702_REG_FFD_CTL               0x88 //NEW REG (S.127)
#define TI9702_FRAMEFREEZE_THRESHOLD     0
#define TI9702_FRAMEFREEZE_USE_CRC       3

#define TI9702_REG_GPIO9_PIN_CTL         0x89 //NEW REG (S.128)
#define TI9702_GPIO0_OUT_EN              0
#define TI9702_GPIO0_OUT_VAL             1
#define TI9702_GPIO0_OUT_SRC             2
#define TI9702_GPIO0_OUT_SEL             5

#define TI9702_REG_GPIO10_PIN_CTL        0x8a //NEW REG (S.128)
#define TI9702_GPIO0_OUT_EN              0
#define TI9702_GPIO0_OUT_VAL             1
#define TI9702_GPIO0_OUT_SRC             2
#define TI9702_GPIO0_OUT_SEL             5

#define TI9702_REG_GPIO_INPUT_CTL_2      0x8b //NEW REG (S.129)
#define TI9702_GPIO9_IN_EN               0
#define TI9702_GPIO10_IN_EN              1
#define TI9702_INTB_PAD_EN               2
#define TI9702_GPIO9_PD_DIS              3
#define TI9702_GPIO10_PD_DIS             4

#define TI9702_REG_REFCLK_DET_INT_CTL    0x8c //NEW REG (S.130)
#define TI9702_REFCLK_DET_INT            0
#define TI9702_REFCLK_LOST_INT           1
#define TI9702_REFCLK_NOT_IMMEDIATE      2

#define TI9702_REG_CSI0_FRAME_COUNT_HI      0x90
#define TI9702_CSI0_FRAME_COUNT_HI          0

#define TI9702_REG_CSI0_FRAME_COUNT_LO      0x91
#define TI9702_CSI0_FRAME_COUNT_LO          0

#define TI9702_REG_CSI0_FRAME_ERR_COUNT_HI  0x92
#define TI9702_CSI0_FRAME_ERR_COUNT_HI      0

#define TI9702_REG_CSI0_FRAME_ERR_COUNT_LO  0x93
#define TI9702_CSI0_FRAME_ERR_COUNT_LO      0

#define TI9702_REG_CSI0_LINE_COUNT_HI       0x94
#define TI9702_CSI0_LINE_COUNT_HI           0

#define TI9702_REG_CSI0_LINE_COUNT_LO       0x95
#define TI9702_CSI0_LINE_COUNT_LO           0

#define TI9702_REG_CSI0_LINE_ERR_COUNT_HI   0x96
#define TI9702_CSI0_LINE_ERR_COUNT_HI       0

#define TI9702_REG_CSI0_LINE_ERR_COUNT_LO   0x97
#define TI9702_CSI0_LINE_ERR_COUNT_LO       0

#define TI9702_REG_CSI1_FRAME_COUNT_HI      0x98
#define TI9702_CSI1_FRAME_COUNT_HI          0

#define TI9702_REG_CSI1_FRAME_COUNT_LO      0x99
#define TI9702_CSI1_FRAME_COUNT_LO          0

#define TI9702_REG_CSI1_FRAME_ERR_COUNT_HI  0x9a
#define TI9702_CSI1_FRAME_ERR_COUNT_HI      0

#define TI9702_REG_CSI1_FRAME_ERR_COUNT_LO  0x9b
#define TI9702_CSI1_FRAME_ERR_COUNT_LO      0

#define TI9702_REG_CSI1_LINE_COUNT_HI       0x9c
#define TI9702_CSI1_LINE_COUNT_HI           0

#define TI9702_REG_CSI1_LINE_COUNT_LO       0x9d
#define TI9702_CSI1_LINE_COUNT_LO           0

#define TI9702_REG_CSI1_LINE_ERR_COUNT_HI   0x9e
#define TI9702_CSI1_LINE_ERR_COUNT_HI       0

#define TI9702_REG_CSI1_LINE_ERR_COUNT_LO   0x9f
#define TI9702_CSI1_LINE_ERR_COUNT_LO       0

#define TI9702_REG_VC_ID_MAP_0             0xa0     //NEW REG
#define TI9702_CSI_VC_MAP_0                0

#define TI9702_REG_VC_ID_MAP_1             0xa1     //NEW REG
#define TI9702_CSI_VC_MAP_1                0

#define TI9702_REG_VC_ID_MAP_2             0xa2     //NEW REG
#define TI9702_CSI_VC_MAP_2                0

#define TI9702_REG_VC_ID_MAP_3             0xa3     //NEW REG
#define TI9702_CSI_VC_MAP_3                0

#define TI9702_REG_VC_ID_MAP_4             0xa4     //NEW REG
#define TI9702_CSI_VC_MAP_4                0

#define TI9702_REG_VC_ID_MAP_5             0xa5     //NEW REG
#define TI9702_CSI_VC_MAP_5                0

#define TI9702_REG_VC_ID_MAP_6             0xa6     //NEW REG
#define TI9702_CSI_VC_MAP_6

#define TI9702_REG_VC_ID_MAP_7             0xa7     //NEW REG
#define TI9702_CSI_VC_MAP_7                00

/* #define TI9702_REG_REFCLK_FREQ 0xa5
   #define TI9702_REFCLK_FREQ     0  */

// REG 0xa8 - 0xaf RESERVED

#define TI9702_REG_IND_ACC_CTL 0xb0
#define TI9702_IA_READ         0
#define TI9702_IA_AUTO_INC     1
#define TI9702_IA_SEL          2

#define TI9702_REG_IND_ACC_ADDR 0xb1
#define TI9702_IA_ADDR          0

#define TI9702_REG_IND_ACC_DATA 0xb2
#define TI9702_IA_DATA          0

#define TI9702_REG_BIST_CTL      0xb3  //NEW NAME OLD: BIST_CONTROL
#define TI9702_BIST_EN           0
#define TI9702_BIST_CLOCK_SOURCE 1
#define TI9702_BIST_PIN_CONFIG   3
#define TI9702_BIST_OUT_MODE     6

// REG 0xb4 - 0xb5 RESERVED

#define TI9702_REG_DIGITAL_DEBUG_2   0xb6    //NEW REG (S.137)
#define TI9702_DISABLE_SCRAMBLE      0
#define TI9702_DISABLE_DCA           1
#define TI9702_CLOCK_1_0_DISABLE     2
#define TI9702_DIS_LINKLOSS_PAR      3
#define TI9702_DIS_LINK_PAR          4
#define TI9702_PAR_ERR_CNTR_MODE     5
#define TI9702_CSI_CLK_POL_0         6
#define TI9702_CSI_CLK_POL_1         7

#define TI9702_REG_DFT_TEST_MODES    0xb7  //NEW REG (S.138)
#define TI9702_ATP_ENABLE            0
#define TI9702_DBG_MUX_MODE          1
#define TI9702_CLK_FPD3_DIVIDER      2
#define TI9702_SEL_CLK_FPD3          3
#define TI9702_EN_CLK_FPD3_TM        5
#define TI9702_SEL_PLL_EXTCLK        6
#define TI9702_BC_TEST_EN            7

#define TI9702_REG_MODE_CAD_STS      0xb8     //NEW NAME OLD: REG_MODE_IDX_STS
#define TI9702_MODE                  0
#define TI9702_MODE_DONE             3
#define TI9702_CAD                   4        //NEW NAME OLD: _IDX
#define TI9702_CAD_DONE              7        //NEW NAME OLD: _IDX

#define TI9702_REG_LINK_ERROR_COUNT  0xb9
#define TI9702_LINK_ERR_THRESH       0
#define TI9702_LINK_ERR_COUNT_EN     4
// #define TI9702_LINK_SFIL_WAIT       5  //NEW RESERVED

#define TI9702_REG_DCA_CONTROL       0xba       //NEW REG  (S.139)
#define TI9702_DCA_STATUS_WAIT_TIME  0
#define TI9702_VCO_WATCHDOG_DISABLE  4
#define TI9702_DISABLE_DCA_CRC       7
// #define TI9702_REG_FPD3_ENC_CTL    0xba
// #define TI9702_FPD3_ENC_CRC_DIS    7

#define TI9702_REG_CSI_PLL_CTL2      0xbb      //NEW REG (S.140)
#define TI9702_FWD_DIS_IMMEDIATE     7

#define TI9702_REG_FV_MIN_TIME 0xbc
#define TI9702_FRAME_VALID_MIN 0

// REG 0xbd RESERVED

#define TI9702_REG_GPIO_PD_CTL 0xbe
#define TI9702_GPIO0_PD_DIS    0
#define TI9702_GPIO1_PD_DIS    1
#define TI9702_GPIO2_PD_DIS    2
#define TI9702_GPIO3_PD_DIS    3
#define TI9702_GPIO4_PD_DIS    4
#define TI9702_GPIO5_PD_DIS    5
#define TI9702_GPIO6_PD_DIS    6
#define TI9702_GPIO7_PD_DIS    7

// REG 0xbf - 0xc1 RESERVED

#define TI9702_REG_IQ_DIV          0xc2  //NEW REG (S. 141)
#define TI9702_DIV_IQ_SEL_DIV_CH0  0
#define TI9702_DIV_IQ_SEL_DIV_CH1  2
#define TI9702_DIV_IQ_SEL_DIV_CH2  4
#define TI9702_DIV_IQ_SEL_DIV_CH3  6

// REG 0xc3 - 0xc6 RESERVED

#define TI9702_REG_CSI_PORT2_FIFO_CTRL   0xc7   //NEW REG (S.142)
#define TI9702_CSI_FIFO_OVERFLOW         0
#define TI9702_CSI_FIFO_UNDERRUN         1
#define TI9702_CSI_PORT2_EN              4
#define TI9702_CSI_CLK_POL_2             5

#define TI9702_REG_CSI_PLL_DIV       0xc9  //NEW REG (S.142)
#define TI9702_CSI_PLL_DIVIDER       0

#define TI9702_REG_LOCAL_DEV_ICR     0xca  //NEW REG (S.143)
#define TI9702_IE_LINE_FAULT         0
#define TI9702_IE_VOLT_SENSOR        1
#define TI9702_IE_TEMP_SENSOR        2
#define TI9702_IE_REFCLK_DET         3
#define TI9702_IE_EXC_FWD_STS        4
#define TI9702_IE_CSI_PORT2_FIFO     5

#define TI9702_REG_LOCAL_DEV_ISR     0xcb  //NEW REG (S.144)
#define TI9702_IS_LINE_FAULT         0
#define TI9702_IS_VOLT_SENSOR        1
#define TI9702_IS_TEMP_SENSOR        2
#define TI9702_IS_REFCLK_DET         3
#define TI9702_IS_EXC_FWD_STS        4
#define TI9702_IS_CSI_PORT2_FIFO     5

// REG 0xcc - 0xce RESERVED

#define TI9702_REG_EXCLUSIVE_FWD_STS    0xcf      //NEW REG (S.144)
#define TI9702_EXC_FWD_FIFO_UNDER_FLAG  0
#define TI9702_EXC_FWD_FIFO_OVER_FLAG   1

#define TI9702_REG_PORT_DEBUG   0xd0
#define TI9702_FORCE_1_BC_ERROR 0
#define TI9702_FORCE_BC_ERRORS  1
#define TI9702_DRIVE_BC         2      //NEW
#define TI9702_FORCE_CLK_DET    3      //NEW
#define TI9702_FPD_CLK_POL      4      //NEW
#define TI9702_SER_BIST_ACT     5

// REG 0xd1 - 0xd7 RESERVED

/* #define TI9702_REG_AEQ_CTL2            0xd2
   #define TI9702_SET_AEQ_FLOOR           2
   #define TI9702_AEQ_RESTART             3
   #define TI9702_AEQ_1ST_LOCK_MODE       4
   #define TI9702_ADAPTIVE_EQ_RELOCK_TIME 5 */

/* #define TI9702_REG_AEQ_STATUS  0xd3
   #define TI9702_EQ_STATUS_1     0
   #define TI9702_EQ_STATUS_2     3         */

/* #define TI9702_REG_ADAPTIVE_EQ_BYPASS  0xd4
   #define TI9702_ADAPTIVE_EQ_BYPASS      0
   #define TI9702_EQ_STAGE_2_SELECT_VALUE 1
   #define TI9702_AEQ_LOCK_MODE           4
   #define TI9702_EQ_STAGE_1_SELECT_VALUE 5  */

/* #define TI9702_REG_AEQ_MIN_MAX         0xd5
   #define TI9702_ADAPTIVE_EQ_FLOOR_VALUE 0
   #define TI9702_AEQ_MAX                 4 */

/* #define TI9702_REG_SFILTER_STS_0       0xd6
   #define TI9702_SFILTER_CDLY            0
   #define TI9702_SFILTER_STABLE          6
   #define TI9702_SFILTER_MAXED           7  */

/* #define TI9702_REG_SFILTER_STS_1       0xd7
   #define TI9702_SFILTER_DDLY            0
   #define TI9702_SFILTER_ERROR           6  */

#define TI9702_REG_PORT_ICR_HI  0xd8
#define TI9702_IE_BCC_CRC_ERR   0
#define TI9702_IE_BCC_SEQ_ERR   1
#define TI9702_IE_FPD3_ENC_ERR  2
#define TI9702_IE_FC_SEN_STS    3        //NEW
#define TI9702_IE_FC_GPIO       4        //NEW

#define TI9702_REG_PORT_ICR_LO     0xd9
#define TI9702_IE_LOCK_STS         0
#define TI9702_IE_PORT_PASS        1
#define TI9702_IE_FPD3_PAR_ERR     2
#define TI9702_IE_CSI_RX_ERR       3      //NEW OLD: RESERVED
#define TI9702_IE_BUFFER_ERR       4
#define TI9702_IE_LINE_CNT_CHG     5
#define TI9702_IE_LINE_LEN_CHG     6
#define TI9702_IE_FRAME_FREEZE_DET 7      //NEW

#define TI9702_REG_PORT_ISR_HI 0xda
#define TI9702_IS_BCC_CRC_ERR  0
#define TI9702_IS_BCC_SEQ_ERR  1
#define TI9702_IS_FPD3_ENC_ERR 2
#define TI9702_IS_FC_SEN_STS   3          //NEW OLD: RESERVED
#define TI9702_IE_FC_GPIO      4          //NEW OLD: RESERVED

#define TI9702_REG_PORT_ISR_LO     0xdb
#define TI9702_IS_LOCK_STS         0
#define TI9702_IS_PORT_PASS        1
#define TI9702_IS_FPD3_PAR_ERR     2
#define TI9702_IS_CSI_RX_ERR       3          //NEW OLD: RESERVED
#define TI9702_IS_BUFFER_ERR       4
#define TI9702_IS_LINE_CNT_CHG     5
#define TI9702_IS_LINE_LEN_CHG     6
#define TI9702_IS_FRAME_FREEZE_DET 7      //NEW

#define TI9702_REG_FC_GPIO_STS 0xdc
#define TI9702_FC_GPIO0_STS    0
#define TI9702_FC_GPIO1_STS    1
#define TI9702_FC_GPIO2_STS    2
#define TI9702_FC_GPIO3_STS    3
#define TI9702_GPIO0_INT_STS   4
#define TI9702_GPIO1_INT_STS   5
#define TI9702_GPIO2_INT_STS   6
#define TI9702_GPIO3_INT_STS   7

#define TI9702_REG_FC_GPIO_ICR 0xdd
#define TI9702_GPIO0_RISE_IE   0
#define TI9702_GPIO0_FALL_IE   1
#define TI9702_GPIO1_RISE_IE   2
#define TI9702_GPIO1_FALL_IE   3
#define TI9702_GPIO2_RISE_IE   4
#define TI9702_GPIO2_FALL_IE   5
#define TI9702_GPIO3_RISE_IE   6
#define TI9702_GPIO3_FALL_IE   7

#define TI9702_REG_SEN_INT_RISE_STS 0xde
#define TI9702_SEN_INT_RISE         0

#define TI9702_REG_SEN_INT_FALL_STS 0xdf
#define TI9702_SEN_INT_FALL         0

#define TI9702_REG_CML_CTRL_1       0xe0           //NEW REG (S.150)
#define TI9702_CML_DCD_ATP_ENB      0
#define TI9702_CMLR1_EN             1
#define TI9702_CMLTX_EN             6
#define TI9702_CMLTX_SER_EN         7

#define TI9702_REG_CML_CTRL_2       0xe1         //NEW REG  (S.151)
#define TI9702_CLR_FIFO_ERRORS      6
#define TI9702_CMLTX_CLK_GATE       7

// REG 0xe2 - 0xe3 RESERVED

#define TI9702_REG_CHANNEL_MODE     0xe4    //NEW REG (S. 151)
#define TI9702_REG_FPD_FUNC_MODE    0
#define TI9702_REG_PI_MODE          3

/*  #define TI9702_REG_FPD3_RX_ID0 0xf0
    #define TI9702_FPD3_RX_ID0     0
    #define TI9702_REG_FPD3_RX_ID1 0xf1
    #define TI9702_FPD3_RX_ID1     0
    #define TI9702_REG_FPD3_RX_ID2 0xf2
    #define TI9702_FPD3_RX_ID2     0
    #define TI9702_REG_FPD3_RX_ID3 0xf3
    #define TI9702_FPD3_RX_ID3     0
    #define TI9702_REG_FPD3_RX_ID4 0xf4
    #define TI9702_FPD3_RX_ID4     0
    #define TI9702_REG_FPD3_RX_ID5 0xf5
    #define TI9702_FPD3_RX_ID5     0     */


#define TI9702_RX_ID_LENGTH    6

// REG 0xf6 - 0xf7 RESERVED

/* #define TI9702_REG_I2C_RX0_ID 0xf8
   #define TI9702_RX_PORT0_ID    1

   #define TI9702_REG_I2C_RX1_ID 0xf9
   #define TI9702_RX_PORT1_ID    1

   #define TI9702_REG_I2C_RX2_ID 0xfa
   #define TI9702_RX_PORT2_ID    1

   #define TI9702_REG_I2C_RX3_ID 0xfb
   #define TI9702_RX_PORT3_ID    1      */

// REG 0xfc - 0xff RESERVED

/* Indirect Register Map Description */

#define TI9702_REG_IA_PATTERN_GEN_PAGE_BLOCK_SELECT 0x0

#define TI9702_REG_IA_PGEN_CTL 0x01
#define TI9702_PGEN_ENABLE     0

#define TI9702_REG_IA_PGEN_CFG 0x02
#define TI9702_BLOCK_SIZE      0
#define TI9702_NUM_CBARS       4
#define TI9702_PGEN_FIXED_EN   7

#define TI9702_REG_IA_PGEN_CSI_DI 0x03
#define TI9702_PGEN_CSI_DT        0
#define TI9702_PGEN_CSI_VC        6

#define TI9702_REG_IA_PGEN_LINE_SIZE1 0x04
#define TI9702_PGEN_LINE_SIZE1        0

#define TI9702_REG_IA_PGEN_LINE_SIZE0 0x05
#define TI9702_PGEN_LINE_SIZE0        0

#define TI9702_REG_IA_PGEN_BAR_SIZE1 0x06
#define TI9702_PGEN_BAR_SIZE1        0

#define TI9702_REG_IA_PGEN_BAR_SIZE0 0x07
#define TI9702_PGEN_BAR_SIZE0        0

#define TI9702_REG_IA_PGEN_ACT_LPF1 0x08
#define TI9702_PGEN_ACT_LPF1        0

#define TI9702_REG_IA_PGEN_ACT_LPF0 0x09
#define TI9702_PGEN_ACT_LPF0        0

#define TI9702_REG_IA_PGEN_TOT_LPF1 0x0a
#define TI9702_PGEN_TOT_LPF1        0

#define TI9702_REG_IA_PGEN_TOT_LPF0 0x0b
#define TI9702_PGEN_TOT_LPF0        0

#define TI9702_REG_IA_PGEN_LINE_PD1 0x0c
#define TI9702_PGEN_LINE_PD1        0

#define TI9702_REG_IA_PGEN_LINE_PD0 0x0d
#define TI9702_PGEN_LINE_PD0        0

#define TI9702_REG_IA_PGEN_VBP 0x0e
#define TI9702_PGEN_VBP        0

#define TI9702_REG_IA_PGEN_VFP 0x0f
#define TI9702_PGEN_VFP        0

#define TI9702_REG_IA_PGEN_COLOR0  0x10
#define TI9702_PGEN_COLOR0         0
#define TI9702_REG_IA_PGEN_COLOR1  0x11
#define TI9702_PGEN_COLOR1         0
#define TI9702_REG_IA_PGEN_COLOR2  0x12
#define TI9702_PGEN_COLOR2         0
#define TI9702_REG_IA_PGEN_COLOR3  0x13
#define TI9702_PGEN_COLOR3         0
#define TI9702_REG_IA_PGEN_COLOR4  0x14
#define TI9702_PGEN_COLOR4         0
#define TI9702_REG_IA_PGEN_COLOR5  0x15
#define TI9702_PGEN_COLOR5         0
#define TI9702_REG_IA_PGEN_COLOR6  0x16
#define TI9702_PGEN_COLOR6         0
#define TI9702_REG_IA_PGEN_COLOR7  0x17
#define TI9702_PGEN_COLOR7         0
#define TI9702_REG_IA_PGEN_COLOR8  0x18
#define TI9702_PGEN_COLOR8         0
#define TI9702_REG_IA_PGEN_COLOR9  0x19
#define TI9702_PGEN_COLOR9         0
#define TI9702_REG_IA_PGEN_COLOR10 0x1a
#define TI9702_PGEN_COLOR10        0
#define TI9702_REG_IA_PGEN_COLOR11 0x1b
#define TI9702_PGEN_COLOR11        0
#define TI9702_REG_IA_PGEN_COLOR12 0x1c
#define TI9702_PGEN_COLOR12        0
#define TI9702_REG_IA_PGEN_COLOR13 0x1d
#define TI9702_PGEN_COLOR13        0
#define TI9702_REG_IA_PGEN_COLOR14 0x1e
#define TI9702_PGEN_COLOR14        0
// #define TI9702_REG_IA_PGEN_COLOR15 0x1f

#define TI9702_REG_IA_CSI0_TCK_PREP 0x40
#define TI9702_MR_TCK_PREP          0
#define TI9702_MR_TCK_PREP_OV       7

#define TI9702_REG_IA_CSI0_TCK_ZERO 0x41
#define TI9702_MR_TCK_ZERO          0
#define TI9702_MR_TCK_ZERO_OV       7

#define TI9702_REG_IA_CSI0_TCK_TRAIL 0x42
#define TI9702_MR_TCK_TRAIL          0
#define TI9702_MR_TCK_TRAIL_OV       7

#define TI9702_REG_IA_CSI0_TCK_POST 0x43
#define TI9702_MR_TCK_POST          0
#define TI9702_MR_TCK_POST_OV       7

#define TI9702_REG_IA_CSI0_THS_PREP 0x44
#define TI9702_MR_THS_PREP          0
#define TI9702_MR_THS_PREP_OV       7

#define TI9702_REG_IA_CSI0_THS_ZERO 0x45
#define TI9702_MR_THS_ZERO          0
#define TI9702_MR_THS_ZERO_OV       7

#define TI9702_REG_IA_CSI0_THS_TRAIL 0x46
#define TI9702_MR_THS_TRAIL          0
#define TI9702_MR_THS_TRIAL_OV       7

#define TI9702_REG_IA_CSI0_THS_EXIT 0x47
#define TI9702_MR_THS_EXIT          0
#define TI9702_MR_THS_EXIT_OV       7

#define TI9702_REG_IA_CSI0_TPLX     0x48
#define TI9702_MR_TPLX              0
#define TI9702_MR_TPLX_OV           7

#define TI9702_REG_IA_CSI1_TCK_PREP 0x60
#define TI9702_MR_TCK_PREP          0
#define TI9702_MR_TCK_PREP_OV       7

#define TI9702_REG_IA_CSI1_TCK_ZERO 0x61
#define TI9702_MR_TCK_ZERO          0
#define TI9702_MR_TCK_ZERO_OV       7

#define TI9702_REG_IA_CSI1_TCK_TRAIL 0x62
#define TI9702_MR_TCK_TRAIL          0
#define TI9702_MR_TCK_TRAIL_OV       7

#define TI9702_REG_IA_CSI1_TCK_POST  0x63
#define TI9702_MR_TCK_POST           0
#define TI9702_MR_TCK_POST_OV        7

#define TI9702_REG_IA_CSI1_THS_PREP  0x64
#define TI9702_MR_THS_PREP           0
#define TI9702_MR_THS_PREP_OV        7

#define TI9702_REG_IA_CSI1_THS_ZERO  0x65
#define TI9702_MR_THS_ZERO           0
#define TI9702_MR_THS_ZERO_OV        7

#define TI9702_REG_IA_CSI1_THS_TRAIL 0x66
#define TI9702_MR_THS_TRAIL          0
#define TI9702_MR_THS_TRAIL_OV       7

#define TI9702_REG_IA_CSI1_THS_EXIT 0x67
#define TI9702_MR_THS_EXIT          0
#define TI9702_MR_THS_EXIT_OV       7

#define TI9702_REG_IA_CSI1_TPLX     0x68
#define TI9702_MR_TPLX              0
#define TI9702_MR_TPLX_OV           7

/* IA test and debug registers not now defined */

/*------------------------------------------------------------------------------
 * Serializer registers
 *----------------------------------------------------------------------------*/
#define TI971_REG_I2C_DEV_ID  0x00
#define TI971_SER_ID_OVERRIDE 0
#define TI971_DEVICE_ID       1

#define TI971_REG_RESET        0x01
#define TI971_DIGITAL_RESET_0  0
#define TI971_DIGITAL_RESET_1  1
#define TI971_RESTART_AUTOLOAD 2

#define TI971_REG_GENERAL_CFG   0x02
// #define TI971_I2C_STRAP_MODE    0     //NEW RESERVED
#define TI971_CRC_TX_GEN_ENABLE 1
#define TI971_CSI_LANE_SEL      4
#define TI971_CONTS_CLK         6
#define TI971_CSI_LANE_SEL1     0
#define TI971_CSI_LANE_SEL2     1
#define TI971_CSI_LANE_SEL4     3

#define TI971_REG_MODE_SEL 0x03
#define TI971_MODE         0
#define TI971_MODE_DONE    3
#define TI971_MODE_OV      4

/* #define TI971_REG_BC_MODE_SELECT  0x04
   #define TI971_DVP_MODE_OVER_EN    0
   #define TI971_MODE_OVERWRITE_75M  1
   #define TI971_MODE_OVERWRITE_100M 2    */

/* #define TI971_REG_PLLCLK_CTL 0x05
   #define TI971_OSCCLO_SEL     3
   #define TI971_CLKIN_DIV      4       */

#define TI971_REG_CLKOUT_CTRL0 0x06
#define TI971_DIV_M_VAL        0
// #define TI971_HS_CLK_DIV       5
#define TI971_HS_CLK_DIV_1     0
#define TI971_HS_CLK_DIV_2     1
#define TI971_HS_CLK_DIV_4     2
#define TI971_HS_CLK_DIV_8     3
#define TI971_HS_CLK_DIV_16    4


#define TI971_REG_CLKOUT_CTRL1 0x07
#define TI971_DIV_N_VAL        0

#define TI971_REG_BBC_WATCHDOG     0x08
#define TI971_BCC_WD_TIMER_DISABLE 0
#define TI971_BCC_WD_TIMER         1

#define TI971_REG_I2C_CONTROL1  0x09
#define TI971_I2C_FILTER_DEPTH  0
#define TI971_I2C_SDA_HOLD      4
#define TI971_LCL_WRITE_DISABLE 7

#define TI971_REG_I2C_CONTROL2      0x0a
#define TI971_I2C_BUS_TIMER_DISABLE 0
#define TI971_I2C_BUS_TIMER_SPEEDUP 1
#define TI971_SDA_OUTPUT_DELAY      2
#define TI971_SDA_OUTPUT_SETUP      4

#define TI971_REG_SCL_HIGH_TIME 0x0b
#define TI971_SCL_HIGH_TIME     0

#define TI971_REG_SCL_LOW_TIME 0x0c
#define TI971_SCL_LOW_TIME     0

#define TI971_REG_LOCAL_GPIO_DATA 0x0d
#define TI971_GPIO_OUT_SRC        0
#define TI971_GPIO_RMTEN          4

#define TI971_REG_GPIO_CTRL  0x0e
#define TI971_GPIO0_INPUT_EN 0
#define TI971_GPIO1_INPUT_EN 1
#define TI971_GPIO2_INPUT_EN 2
#define TI971_GPIO3_INPUT_EN 3
#define TI971_GPIO0_OUT_EN   4
#define TI971_GPIO1_OUT_EN   5
#define TI971_GPIO2_OUT_EN   6
#define TI971_GPIO3_OUT_EN   7

#define TI971_REG_GPIO_ATP_CTL   0x0f  //NEW REG (S. 42)
#define TI971_GPIO0_PD_DIS       4
#define TI971_GPIO1_PD_DIS       5
#define TI971_GPIO2_PD_DIS       6
#define TI971_GPIO3_PD_DIS       7

/* #define TI971_REG_DVP_CFG    0x10
   #define TI971_DVP_LV_INV     0
   #define TI971_DVP_FV_IN      1
   #define TI971_DVP_DT_YUV_EN  2
   #define TI971_DVP_DT_MATH_EN 3
   #define TI971_DVP_DT_ANY_EN  4 */

/* #define TI971_REG_DVP_DT       0x11
   #define TI971_DVP_DT_MATCH_VAL 0     */

#define TI971_REG_INTERRUPT_CTL  0x11  //NEW REG (S. 42)
#define TI971_IE_DEV             6
#define TI971_INTERRUPT_EN       7

/*  #define TI971_REG_FORCE_BIST_EN 0x13
    #define TI971_FORCE_FC_CNT      0
    #define TI971_FORCE_FC_ERR      7  */

/*  #define TI971_REG_REMOTE_BIST_CTRL 0x14
    #define TI971_REMOTE_BIST_EN       0
    #define TI971_BIST_CLOCK           1
    #define TI971_LOCAL_BIST_EN        3
    #define TI971_FORCE_ERR_CNT        4  */

/*  #define TI971_REG_SENSOR_VGAIN 0x15
    #define TI971_VOLT_GAIN        0     */

/*  #define TI971_REG_SENSOR_CTRL0 0x17
    #define TI971_SENSE_V_GPIO     0
    #define TI971_SENSOR_ENABLE    2    */

#define TI971_REG_SAR_ADC_CNTR       0x17       //NEW REG (S.42)
#define TI971_SAR_ADC_BYPASS_REG_LV  0
#define TI971_SENSE_GAIN_EN          4
#define TI971_SENSE_T_EN             5

/* #define TI971_REG_SENSOR_CTRL1 0x18
   #define TI971_SENSE_GAIN_EN    7        */

#define TI971_REG_SAR_ADC_DOUT       0x18       //NEW REG (S.43)
#define TI971_SAR_ADC_DOUT_LV        0

/* #define TI971_REG_SENSOR_V0_THRESH 0x19
   #define TI971_SENSE_V0_LO          0
   #define TI971_SENSE_V0_HI          4    */

/* #define TI971_REG_SENSOR_V1_THRESH 0x1a
   #define TI971_SENSE_V1_LO          0
   #define TI971_SENSE_V1_HI          4    */

/* #define TI971_REG_SENSOR_T_THRESH 0x1b
   #define TI971_SENSE_T_LO          0
   #define TI971_SENSE_T_HI          4     */

#define TI971_REG_LOCAL_DEV_ICR      0x1b      //NEW REG (S. 43)
#define TI971_IE_LINE_FAULT          0
#define TI971_IE_VOLT_SENSOR         1
#define TI971_IE_TEMP_SENSOR         2
#define TI971_IE_LOSS_OF_CLKIN       3
#define TI971_IE_ESD_EVENT_INTR      4

#define TI971_REG_ALARM_CSI_EN  0x1c
#define TI971_CSI_LENGTH_ERR_EN 0
#define TI971_CSI_CHKSUM_ERR_EN 1
#define TI971_CSI_ECC_2_EN      2
#define TI971_DPHY_CTRL_ERR_EN  3
#define TI971_DPHY_SYNC_ERR_EN  4           //NEW
#define TI971_CSI_NO_FV_EN      5

/* #define TI971_REG_SENSE_EN 0x1d
   #define TI971_V0_UNDER     0
   #define TI971_V0_OVER      1
   #define TI971_V1_UNSER     2
   #define TI971_V1_OVER      3
   #define TI971_T_UNDER      4
   #define TI971_T_OVER       5  */

#define TI971_REG_ALARM_BC_EN 0x1e
#define TI971_LINK_DETECT_EN  0
#define TI971_CRC_ERR_EN      1       //NEW NAME OLD: _CRC_ER_EN

#define TI971_REG_CSI_POL_SEL 0x20
#define TI971_POLARITY_D0     0
#define TI971_POLARITY_D1     1
#define TI971_POLARITY_D2     2
#define TI971_POLARITY_D3     3
#define TI971_POLARITY_CLK0   4       //NEW NAME OLD: _POLARITY_CK0

#define TI971_REG_CSI_LP_POLARITY 0x21
#define TI971_POL_LP_DATA         0
#define TI971_POL_LP_CLK0         4
#define TI971_SUPPORT_16VC        7     //NEW

/* #define TI971_REG_CSI_EN_RXTERM 0x24
   #define TI971_EN_RXTERM_D0      0
   #define TI971_EN_RXTERM_D1      1
   #define TI971_EN_RXTERM_D2      2
   #define TI971_EN_RXTERM_D3      3  */

#define TI971_REG_CSI_PKT_VCI_CTRL      0x30    //NEW REG (S. 45)
#define TI971_PKT_HDR_VCI_ENABLE        5

#define TI971_REG_CSI_PKT_HDR_TINIT_CTRL  0x31      //NEW NAME OLD: _HDR_TINT_CTRL
#define TI971_TINIT_TIME                  0
#define TI971_PKT_HDR_SEL_VC              4         //NEW OLD: HDR_VCI_ENABLE
// #define TI971_PKT_HDR_CORRECTED           5
// #define TI971_PKT_HDR_SEL_VC              6

#define TI971_REG_BCC_CONFIG           0x32
#define TI971_RX_PARITY_CHECKER_ENABLE 3
#define TI971_AUTO_ACK_ALL             5
#define TI971_I2C_PASS_THROUGH         6
#define TI971_I2C_PASS_THROUGH_ALL     7

#define TI971_REG_DATAPATH_CTL1 0x33
#define TI971_FC_GPIO_EN        0
#define TI971_DCA_CRC_EN        2

#define TI971_REG_REMOTE_PAR_CAP1  0x35 //NEW NAME OLD: REG_DES_PAR_CAP1
#define TI971_PORT_NUM             0
#define TI971_MPORT                4
#define TI971_BIST_EN              5
#define TI971_FREEZE_DES_CAP       7

#define TI971_REG_DES_ID       0x37
#define TI971_FREEZE_DEVICE_ID 0
#define TI971_DES_ID           1

#define TI971_REG_SLAVE_ID_0 0x39
#define TI971_SLAVE_ID_0     1
#define TI971_REG_SLAVE_ID_1 0x3a
#define TI971_SLAVE_ID_1     1
#define TI971_REG_SLAVE_ID_2 0x3b
#define TI971_SLAVE_ID_2     1
#define TI971_REG_SLAVE_ID_3 0x3c
#define TI971_SLAVE_ID_3     1
#define TI971_REG_SLAVE_ID_4 0x3d
#define TI971_SLAVE_ID_4     1
#define TI971_REG_SLAVE_ID_5 0x3e
#define TI971_SLAVE_ID_5     1
#define TI971_REG_SLAVE_ID_6 0x3f
#define TI971_SLAVE_ID_6     1
#define TI971_REG_SLAVE_ID_7 0x40
#define TI971_SLAVE_ID_7     1

#define TI971_REG_SLAVE_ID_ALIAS_0 0x41
#define TI971_SLAVE_AUTO_ACK_0     0     //NEW
#define TI971_SLAVE_ID_ALIAS_0     1
#define TI971_REG_SLAVE_ID_ALIAS_1 0x42
#define TI971_SLAVE_AUTO_ACK_1     0     //NEW
#define TI971_SLAVE_ID_ALIAS_1     1
#define TI971_REG_SLAVE_ID_ALIAS_2 0x43
#define TI971_SLAVE_AUTO_ACK_2     0     //NEW
#define TI971_SLAVE_ID_ALIAS_2     1
#define TI971_REG_SLAVE_ID_ALIAS_3 0x44
#define TI971_SLAVE_AUTO_ACK_3     0     //NEW
#define TI971_SLAVE_ID_ALIAS_3     1
#define TI971_REG_SLAVE_ID_ALIAS_4 0x45
#define TI971_SLAVE_AUTO_ACK_4     0     //NEW
#define TI971_SLAVE_ID_ALIAS_4     1
#define TI971_REG_SLAVE_ID_ALIAS_5 0x46
#define TI971_SLAVE_AUTO_ACK_5     0     //NEW
#define TI971_SLAVE_ID_ALIAS_5     1
#define TI971_REG_SLAVE_ID_ALIAS_6 0x47
#define TI971_SLAVE_AUTO_ACK_6     0     //NEW
#define TI971_SLAVE_ID_ALIAS_6     1
#define TI971_REG_SLAVE_ID_ALIAS_7 0x48
#define TI971_SLAVE_AUTO_ACK_7     0     //NEW
#define TI971_SLAVE_ID_ALIAS_7     1

#define TI971_REG_BC_CTRL      0x49      //NEW NAME OLD: REG_CB_CTRL
// #define TI971_LINK_DET_TIMER   0
#define TI971_CRC_ERR_CLR      3
#define TI971_BIST_CRC_ERR_CLR 5

#define TI971_REG_REV_MASK_ID 0x50
#define TI971_MASK_ID         0
#define TI971_REVISION_ID     4

#define TI971_REG_DEVICE_STS 0x51
#define TI971_CFG_INIT_DONE  6
#define TI971_CFG_CKSUM_STS  7

#define TI971_REG_GENERAL_STATUS 0x52
#define TI971_LINK_DET           0
#define TI971_CRC_ERR            1
#define TI971_HS_PLL_LOCK_VAL    2       //NEW
#define TI971_BIST_CRC_ERR       3       //NEW
#define TI971_LINK_LOST_FLAG     4       //NEW
#define TI971_RX_LOCK_DETECT     6       //NEW
#define TI971_AON_MODE_LATCHED   7       //NEW

#define TI971_REG_GPIO_PIN_STS 0x71
#define TI971_GPIO_STS         0

#define TI971_REG_BIST_ERR_CNT 0x54
#define TI971_BIST_BC_ERRCNT   0

#define TI971_REG_CRC_ERR_CNT1 0x55
#define TI971_CRC_ERR_CNT1     0

#define TI971_REG_CRC_ERR_CNT2 0x56
#define TI971_CRC_ERR_CNT2     0

/* #define TI971_REG_SENSOR_STATUS 0x57
   #define TI971_V0_SENSOR_LOW     0
   #define TI971_V0_SENOSR_HI      1
   #define TI971_V1_SENSOR_LOW     2
   #define TI971_V1_SENSOR_HI      3
   #define TI971_T_SENSOR_LOW      4
   #define TI971_T_SENSOR_HI       5   */

#define TI971_REG_INTERRUPT_STS    0x57    //NEW REG (S. 55)
#define TI971_IS_DEV               6
#define TI971_INTERRUPT            7

/*  #define TI971_REG_SENSOR_V0         0x58
    #define TI971_VOLTAGE_SENSOR_V0_MIN 0
    #define TI971_VOLTAGE_SENSOR_V0_MAX 4 */

#define TI971_REG_LOCAL_DEV_ISR         0x58  //NEW REG (S. 55)
#define TI971_IS_LINE_FAULT             0
#define TI971_IS_VOLT_SENSOR            1
#define TI971_IS_TEMP_SENSOR            2
#define TI971_IS_LOSS_OF_CLKIN          3
#define TI971_IS_ESD_EVENT_INTR         4

/*  #define TI971_REG_SENSOR_V1         0x59
    #define TI971_VOLTAGE_SENOSR_V1_MIN 0
    #define TI971_VOLTAGE_SENSOR_V1_MAX 4     */

/*  #define TI971_REG_SENSOR_T 0x5a
    #define TI971_TEMP_MIN     0
    #define TI971_TMEP_MAX     4      */

#define TI971_REG_CSI_ERR_CNT 0x5c
#define TI971_CSI_ERR_CNT     0

#define TI971_REG_CSI_ERR_STATUS 0x5d
#define TI971_ECC_1BIT_ERR       0
#define TI971_ECC_2BIT_ERR       1
#define TI971_CHKSUM_ERR         2
#define TI971_LINE_LEN_MISMATCH  3
#define TI971_ALL_LANE_SYNC2_ERR 4    //NEW

#define TI971_REG_CSI_ERR_DLANE01 0x5e
#define TI971_CNTRL_ERR_HSRQST_0  1
#define TI971_SOT_SYNC_ERROR_0    2
#define TI971_SOT_ERROR_0         3
#define TI971_CNTRL_ERR_HSRQST_1  5
#define TI971_SOT_SYNC_ERROR_1    6
#define TI971_SOT_ERROR_1         7

#define TI971_REG_CSI_ERR_DLANE23 0x5f
#define TI971_CNTRL_ERR_HSRQST_2  1
#define TI971_SOT_SYNC_ERROR_2    2
#define TI971_SOT_ERROR_2         3
#define TI971_CNTRL_ERR_HSRQST_3  5
#define TI971_SOT_SYNC_ERROR_3    6
#define TI971_SOT_ERROR_3         7

#define TI971_REG_CSI_ERR_CLK_LANE 0x60
#define TI971_CNTRL_ERR_HSRQST_CK0 1

#define TI971_REG_CSI_PKT_HDR_VC_ID 0x61
#define TI971_LONG_PKT_DATA_ID      0
// #define TI971_LONG_PKT_VCHNL_ID     6  //NEW

#define TI971_REG_PKT_HDR_WC_LSB   0x62
#define TI971_LONG_PKT_WRD_CNT_LSB 0

#define TI971_REG_PKT_HDR_WC_MSB   0x63
#define TI971_LONG_PKT_WRD_CNT_MSB 0

#define TI971_REG_CSI_ECC        0x64
#define TI971_CSI2_ECC           0
#define TI971_LINE_LENGTH_CHANGE 7

#define TI971_REG_IND_ACC_CTL 0xb0
#define TI971_IA_READ         0
#define TI971_IA_AUTO_INC     1
#define TI971_IA_SEL          2

#define TI971_REG_ANA_IA_ADDR  0xb1  //NEW NAME OLD: IND_ACC_ADDR
#define TI971_ANA_IA_ADDR      0     //NEW NAME OLD: IND_ACC_ADDR

#define TI971_REG_ANA_IA_DATA  0xb2  //NEW NAME OLD: IND_ACC_DATA
#define TI971_ANA_IA_DATA      0     //NEW NAME OLD: IND_ACC_DATA

#define TI971_REG_DIV_OSC_SEL0      0xd8  //NEW REG (S. 58)
#define TI971_DIV_M_OSC_VAL         0
#define TI971_DIV_OSC_SWITCH_EN     6
#define TI971_DIV_OSC_SWITCH_FOR_CE 7

#define TI971_REG_DIV_OSC_SEL1      0xd9  //NEW REG (S. 59)
#define TI971_DIV_N_OSC_VAL         0

#define TI971_REG_FPD3_RX_ID0 0xf0
#define TI971_FPD3_RX_ID0     0
#define TI971_REG_FPD3_RX_ID1 0xf1
#define TI971_FPD3_RX_ID1     0
#define TI971_REG_FPD3_RX_ID2 0xf2
#define TI971_FPD3_RX_ID2     0
#define TI971_REG_FPD3_RX_ID3 0xf3
#define TI971_FPD3_RX_ID3     0
#define TI971_REG_FPD3_RX_ID4 0xf4
#define TI971_FPD3_RX_ID4     0
#define TI971_REG_FPD3_RX_ID5 0xf5
#define TI971_FPD3_RX_ID5     0

#define TI971_RX_ID_LENGTH    6         //NEW

/*------------------------------------------------------------------------------
 * DEFINES
 *----------------------------------------------------------------------------*/
// GPIO
#define CAM_ENABLE 0x01   /* Assumes bit 0 of GPIO is connected to CAM_ENABLE */
#define GPIO_DEVICE_ID  XPAR_GPIO_0_DEVICE_ID
#define CAM_ENABLE_CHANNEL 1
// IIC
#define IIC_BASEADDR            XPAR_AXI_IIC_0_BASEADDR
#define IIC_DEVICE_ID           XPAR_IIC_0_DEVICE_ID
// DESERIALIZER
#define TI9702_I2C               0x30    // ID of deserializer
// SERIALIZER
#define TI971_I2C_0             0x41    // alias of serializer on port 0
#define TI971_I2C_1             0x42    // alias of serializer on port 0
// sensor
#define SENSOR_I2C_0            0x43
#define SENSOR_I2C_1            0x44
// #define SENSOR_I2C_ALIAS      	0x20
#define SENSOR_ID               0x1A //0x50
// EEPROM
#define EEPROM_ID               0x55
#define EEPROM_I2C_0            0x45
#define EEPROM_I2C_1            0x46

#define NUM_SERIALIZER 2
#define NUM_ALIAS 8

struct ds90ub971_priv {
	struct i2c_client *client;
	struct regmap *regmap;
	struct ds90ub9702_priv *parent;
	int rx_channel;
	int test_pattern;
	int i2c_address;
	int i2c_channel; //channel to use from deserializer               //NEW
	int csi_lane_count;
	int i2c_alias_num; // number of slave alias pairs
	int i2c_slave[NUM_ALIAS]; // array with the i2c slave addresses
	int i2c_alias[NUM_ALIAS]; // array with the i2c alias addresses
	int conts_clk; // continuous clock (0: discontinuous, 1: continuous)
	int i2c_pt; // i2c-pass-through-all

	int initialized;

	int gpio0_oe; // gpio0_output_enable
	int gpio1_oe; // gpio1_output_enable
	int gpio2_oe; // gpio2_output_enable
	int gpio3_oe; // gpio3_output_enable

	int gpio0_oc; // gpio0_output_control
	int gpio1_oc; // gpio1_output_control
	int gpio2_oc; // gpio2_output_control
	int gpio3_oc; // gpio3_output_control

	/* reference output clock control parameters */
	// int hs_clk_div;                                  //NEW
	int div_m_val;
	int div_n_val;
    int osc_switch;                                     //NEW
    int div_m_osc_val;                                  //NEW
    int div_n_osc_val;                                  //NEW

	int vc_map0; // virtual channel mapping 0 REG       //NEW
	int vc_map1; // virtual channel mapping 1 REG       //NEW
};


struct ds90ub9702_priv {
	struct i2c_client *client;
	struct regmap *regmap;
	struct ds90ub971_priv *ser[NUM_SERIALIZER]; //serializers
	int pass_gpio;
	int lock_gpio;
	int pdb_gpio;
	int sel_rx_port; // selected rx port
	int sel_ia_config; // selected ia configuration
	int csi_lane_count;
	int csi_lane_speed;
	int test_pattern;
	int num_ser; // number of serializers connected
	int conts_clk; // continuous clock (0: discontinuous, 1: continuous)
    int replicate;                                //NEW
    int repl_switch;                              //NEW
    int write_tx0;                                //NEW
    // int write_tx1;                                //NEW

    int gpio0_oe; // des-gpio0_output_enable
    int gpio1_oe; // des-gpio1_output_enable
    int gpio2_oe; // des-gpio2_output_enable
    int gpio3_oe; // des-gpio3_output_enable
    int gpio4_oe; // des-gpio4_output_enable
    int gpio5_oe; // des-gpio5_output_enable
    int gpio6_oe; // des-gpio6_output_enable
    int gpio7_oe; // des-gpio7_output_enable       //NEW

    int gpio0_oc; // des-gpio0_output_control
    int gpio1_oc; // des-gpio1_output_control
    int gpio2_oc; // des-gpio2_output_control
    int gpio3_oc; // des-gpio3_output_control
    int gpio4_oc; // des-gpio4_output_control
    int gpio5_oc; // des-gpio5_output_control
    int gpio6_oc; // des-gpio6_output_control
    int gpio7_oc; // des-gpio7_output_control      //NEW
};

#endif /* I2C_DS90UB9702_H */
