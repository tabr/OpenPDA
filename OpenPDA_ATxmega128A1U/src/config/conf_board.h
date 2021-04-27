/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

//! Configuration using On-Chip RC oscillator at 48MHz
//! The RC oscillator is calibrated via USB Start Of Frame
//! Clk USB     = 48MHz (used by USB)
//! Clk sys     = 48MHz
//! Clk cpu/per = 12MHz
#define CONFIG_USBCLK_SOURCE     USBCLK_SRC_RCOSC
#define CONFIG_OSC_RC32_CAL      48000000UL

#define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  OSC_ID_USBSOF

//#define CONFIG_SYSCLK_SOURCE     SYSCLK_SRC_RC32MHZ
//#define CONFIG_SYSCLK_PSADIV     SYSCLK_PSADIV_2
//#define CONFIG_SYSCLK_PSBCDIV    SYSCLK_PSBCDIV_1_2

/*
//! Use external board OSC (8MHz)
//! Clk pll     = 48MHz (used by USB)
//! Clk sys     = 48MHz
//! Clk cpu/per = 12MHz

#define CONFIG_PLL0_SOURCE       PLL_SRC_XOSC
#define CONFIG_PLL0_MUL          6
#define CONFIG_PLL0_DIV          1

#define CONFIG_USBCLK_SOURCE     USBCLK_SRC_PLL

#define CONFIG_SYSCLK_SOURCE     SYSCLK_SRC_PLL
#define CONFIG_SYSCLK_PSADIV     SYSCLK_PSADIV_2
#define CONFIG_SYSCLK_PSBCDIV    SYSCLK_PSBCDIV_1_2
*/

#endif // CONF_BOARD_H
