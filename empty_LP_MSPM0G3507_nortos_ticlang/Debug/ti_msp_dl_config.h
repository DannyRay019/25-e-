/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_28
#define GPIO_PWM_0_C0_IOMUX                                       (IOMUX_PINCM3)
#define GPIO_PWM_0_C0_IOMUX_FUNC                      IOMUX_PINCM3_PF_TIMA1_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_31
#define GPIO_PWM_0_C1_IOMUX                                       (IOMUX_PINCM6)
#define GPIO_PWM_0_C1_IOMUX_FUNC                      IOMUX_PINCM6_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX

/* Defines for PWM_1 */
#define PWM_1_INST                                                         TIMA0
#define PWM_1_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_1_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_1_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_1_C0_PORT                                                 GPIOA
#define GPIO_PWM_1_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_PWM_1_C0_IOMUX                                      (IOMUX_PINCM19)
#define GPIO_PWM_1_C0_IOMUX_FUNC                     IOMUX_PINCM19_PF_TIMA0_CCP0
#define GPIO_PWM_1_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_1_C1_PORT                                                 GPIOA
#define GPIO_PWM_1_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_PWM_1_C1_IOMUX                                      (IOMUX_PINCM20)
#define GPIO_PWM_1_C1_IOMUX_FUNC                     IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_PWM_1_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (12499U)




/* Defines for I2C_1 */
#define I2C_1_INST                                                          I2C1
#define I2C_1_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_1_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_1_BUS_SPEED_HZ                                                100000
#define GPIO_I2C_1_SDA_PORT                                                GPIOB
#define GPIO_I2C_1_SDA_PIN                                         DL_GPIO_PIN_3
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM16)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOB
#define GPIO_I2C_1_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)





/* Port definition for Pin Group CIN */
#define CIN_PORT                                                         (GPIOA)

/* Defines for CIN1: GPIOA.24 with pinCMx 54 on package pin 25 */
#define CIN_CIN1_PIN                                            (DL_GPIO_PIN_24)
#define CIN_CIN1_IOMUX                                           (IOMUX_PINCM54)
/* Defines for CIN2: GPIOA.26 with pinCMx 59 on package pin 30 */
#define CIN_CIN2_PIN                                            (DL_GPIO_PIN_26)
#define CIN_CIN2_IOMUX                                           (IOMUX_PINCM59)
/* Port definition for Pin Group DIN */
#define DIN_PORT                                                         (GPIOB)

/* Defines for DIN1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define DIN_DIN1_PIN                                            (DL_GPIO_PIN_24)
#define DIN_DIN1_IOMUX                                           (IOMUX_PINCM52)
/* Defines for DIN2: GPIOB.20 with pinCMx 48 on package pin 19 */
#define DIN_DIN2_PIN                                            (DL_GPIO_PIN_20)
#define DIN_DIN2_IOMUX                                           (IOMUX_PINCM48)
/* Port definition for Pin Group AIN */
#define AIN_PORT                                                         (GPIOA)

/* Defines for AIN1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define AIN_AIN1_PIN                                            (DL_GPIO_PIN_12)
#define AIN_AIN1_IOMUX                                           (IOMUX_PINCM34)
/* Defines for AIN2: GPIOA.7 with pinCMx 14 on package pin 49 */
#define AIN_AIN2_PIN                                             (DL_GPIO_PIN_7)
#define AIN_AIN2_IOMUX                                           (IOMUX_PINCM14)
/* Port definition for Pin Group BIN */
#define BIN_PORT                                                         (GPIOB)

/* Defines for BIN1: GPIOB.16 with pinCMx 33 on package pin 4 */
#define BIN_BIN1_PIN                                            (DL_GPIO_PIN_16)
#define BIN_BIN1_IOMUX                                           (IOMUX_PINCM33)
/* Defines for BIN2: GPIOB.17 with pinCMx 43 on package pin 14 */
#define BIN_BIN2_PIN                                            (DL_GPIO_PIN_17)
#define BIN_BIN2_IOMUX                                           (IOMUX_PINCM43)
/* Port definition for Pin Group ENCODERA */
#define ENCODERA_PORT                                                    (GPIOA)

/* Defines for E1A: GPIOA.13 with pinCMx 35 on package pin 6 */
// pins affected by this interrupt request:["E1A","E1B"]
#define ENCODERA_INT_IRQN                                       (GPIOA_INT_IRQn)
#define ENCODERA_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define ENCODERA_E1A_IIDX                                   (DL_GPIO_IIDX_DIO13)
#define ENCODERA_E1A_PIN                                        (DL_GPIO_PIN_13)
#define ENCODERA_E1A_IOMUX                                       (IOMUX_PINCM35)
/* Defines for E1B: GPIOA.14 with pinCMx 36 on package pin 7 */
#define ENCODERA_E1B_IIDX                                   (DL_GPIO_IIDX_DIO14)
#define ENCODERA_E1B_PIN                                        (DL_GPIO_PIN_14)
#define ENCODERA_E1B_IOMUX                                       (IOMUX_PINCM36)
/* Port definition for Pin Group ENCODERC */
#define ENCODERC_PORT                                                    (GPIOB)

/* Defines for E3A: GPIOB.7 with pinCMx 24 on package pin 59 */
// pins affected by this interrupt request:["E3A","E3B"]
#define ENCODERC_INT_IRQN                                       (GPIOB_INT_IRQn)
#define ENCODERC_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define ENCODERC_E3A_IIDX                                    (DL_GPIO_IIDX_DIO7)
#define ENCODERC_E3A_PIN                                         (DL_GPIO_PIN_7)
#define ENCODERC_E3A_IOMUX                                       (IOMUX_PINCM24)
/* Defines for E3B: GPIOB.6 with pinCMx 23 on package pin 58 */
#define ENCODERC_E3B_IIDX                                    (DL_GPIO_IIDX_DIO6)
#define ENCODERC_E3B_PIN                                         (DL_GPIO_PIN_6)
#define ENCODERC_E3B_IOMUX                                       (IOMUX_PINCM23)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOA)

/* Defines for OLED_SCL: GPIOA.1 with pinCMx 2 on package pin 34 */
#define OLED_OLED_SCL_PIN                                        (DL_GPIO_PIN_1)
#define OLED_OLED_SCL_IOMUX                                       (IOMUX_PINCM2)
/* Defines for OLED_SDA: GPIOA.25 with pinCMx 55 on package pin 26 */
#define OLED_OLED_SDA_PIN                                       (DL_GPIO_PIN_25)
#define OLED_OLED_SDA_IOMUX                                      (IOMUX_PINCM55)
/* Port definition for Pin Group IR_DH */
#define IR_DH_PORT                                                       (GPIOA)

/* Defines for PIN_0: GPIOA.15 with pinCMx 37 on package pin 8 */
#define IR_DH_PIN_0_PIN                                         (DL_GPIO_PIN_15)
#define IR_DH_PIN_0_IOMUX                                        (IOMUX_PINCM37)
/* Defines for PIN_1: GPIOA.22 with pinCMx 47 on package pin 18 */
#define IR_DH_PIN_1_PIN                                         (DL_GPIO_PIN_22)
#define IR_DH_PIN_1_IOMUX                                        (IOMUX_PINCM47)
/* Defines for PIN_2: GPIOA.16 with pinCMx 38 on package pin 9 */
#define IR_DH_PIN_2_PIN                                         (DL_GPIO_PIN_16)
#define IR_DH_PIN_2_IOMUX                                        (IOMUX_PINCM38)
/* Defines for PIN_3: GPIOA.17 with pinCMx 39 on package pin 10 */
#define IR_DH_PIN_3_PIN                                         (DL_GPIO_PIN_17)
#define IR_DH_PIN_3_IOMUX                                        (IOMUX_PINCM39)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_1_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_UART_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
