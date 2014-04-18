#ifndef D_CONFIG_H
#define D_CONFIG_H

/* Enable debug output. */
//#define CONFIG_DEBUG

/* System components *********************************************************/

/* Enable filesystem support. */
//#define CONFIG_FS

/* Enable the basic co-operative scheduler. */
#define CONFIG_SCHED

/* Maximum number of tasks. */
#define CONFIG_SCHED_NTASKS 8

/* Hardware support **********************************************************/

/* Configure 16-bit timer1 to tick every n Number of miliseconds */
#define CONFIG_TIMER1_TICK_MS 4

/* Enable support for I2C peripherals. */
//#define CONFIG_I2C

/* Enable support for ADC peripherals. */
//#define CONFIG_ADC

/* Applications **************************************************************/

/* Maximum lengh of a command line. */
#define CONFIG_LSH_GETLINE_NCHARS 80

#endif /* D_CONFIG_H */
