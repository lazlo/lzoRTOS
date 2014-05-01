#ifndef D_CONFIG_H
#define D_CONFIG_H

/* Enable debug output. */
//#define CONFIG_DEBUG

/* System components *********************************************************/

/* Enable filesystem support. */
//#define CONFIG_FS

/* Enable netwoking support. */
//#define CONFIG_NET

/* Enable the basic co-operative scheduler. */
#define CONFIG_SCHED

/* Maximum number of tasks. */
#define CONFIG_SCHED_NTASKS 8

/* Hardware support **********************************************************/

/* Configure 16-bit timer1 to tick every n Number of miliseconds */
#define CONFIG_TIMER1_TICK_MS 1

/* Enable support for SPI peripherals. */
#define CONFIG_SPI

/* Enable support for I2C peripherals. */
//#define CONFIG_I2C

/* Enable support for ADC peripherals. */
//#define CONFIG_ADC

/* Applications **************************************************************/

/* Maximum lengh of a command line. */
#define CONFIG_LSH_GETLINE_NCHARS 80

/* LSH Commands */

//#define CONFIG_CMD_ARP
//#define CONFIG_CMD_CAT
//#define CONFIG_CMD_CD
//#define CONFIG_CMD_CP
//#define CONFIG_CMD_DD
//#define CONFIG_CMD_DU
//#define CONFIG_CMD_DF
//#define CONFIG_CMD_ECHO
//#define CONFIG_CMD_ETHTOOL
//#define CONFIG_CMD_ENV
//#define CONFIG_CMD_FREE
//#define CONFIG_CMD_GREP
//#define CONFIG_CMD_HALT
//#define CONFIG_CMD_HEAD
//#define CONFIG_CMD_HOSTNAME
//#define CONFIG_CMD_HWCLOCK
//#define CONFIG_CMD_I2C
//#define CONFIG_CMD_IFCONFIG
#define CONFIG_CMD_KILL
//#define CONFIG_CMD_LESS
//#define CONFIG_CMD_LS
//#define CONFIG_CMD_MIITOOL
//#define CONFIG_CMD_MOUNT
//#define CONFIG_CMD_MKDIR
//#define CONFIG_CMD_MV
//#define CONFIG_CMD_NETSTAT
//#define CONFIG_CMD_NETCAT
//#define CONFIG_CMD_PING
#define CONFIG_CMD_PS
//#define CONFIG_CMD_PWD
//#define CONFIG_CMD_RM
//#define CONFIG_CMD_RMDIR
//#define CONFIG_CMD_ROUTE
//#define CONFIG_CMD_SS
#define CONFIG_CMD_SPI
//#define CONFIG_CMD_STRINGS
//#define CONFIG_CMD_TAIL
//#define CONFIG_CMD_TCPDUMP
//#define CONFIG_CMD_TELNET
//#define CONFIG_CMD_TOUCH
//#define CONFIG_CMD_TTY
//#define CONFIG_CMD_TRACEROUTE
//#define CONFIG_CMD_UPTIME
//#define CONFIG_CMD_UMOUNT
//#define CONFIG_CMD_UNAME
//#define CONFIG_CMD_WGET
//#define CONFIG_CMD_XD
//#define CONFIG_CMD_MB
//#define CONFIG_CMD_MH
//#define CONFIG_CMD_MW

#endif /* D_CONFIG_H */
