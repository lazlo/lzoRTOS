#ifndef D_CONFIG_H
#define D_CONFIG_H

/* Enable debug output. */
//#define CONFIG_DEBUG

/* System components *********************************************************/

/* Enable filesystem support. */
//#define CONFIG_FS

/* Enable the basic co-operative scheduler. */
#define CONFIG_SCHED

/* Hardware support **********************************************************/

/* Enable support for I2C peripherals. */
//#define CONFIG_I2C

/* Enable support for ADC peripherals. */
//#define CONFIG_ADC

/* Applications **************************************************************/

/* Maximum lengh of a command line. */
#define CONFIG_LSH_GETLINE_NCHARS 80

#endif /* D_CONFIG_H */
