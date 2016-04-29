
#ifndef _BCMNETLINK_H
#define _BCMNETLINK_H

#include<linux/netlink.h>

#ifdef AEI_WECB
#define NETLINK_MONITOR 26 // WECB
#else
#define NETLINK_MONITOR 25 // OpenWRT
#endif

/* message types exchanged using NETLINK_BRCM_MONITOR */
#define MSG_NETLINK_BRCM_WAKEUP_MONITOR_TASK	0X1000
#define MSG_NETLINK_BRCM_LINK_STATUS_CHANGED	0X2000
#define MSG_NETLINK_RESET_STATUS_CHANGE			0x4000
#define MSG_NETLINK_DAD_FAILURE					0x8000
#define MSG_NETLINK_WPS_STATUS_CHANGE			0xa000



#define BTN_STAT_RELEASED 0x0
#define BTN_STAT_PRESSED  0x1
#define BTN_STAT_PRESSED_ON_BOOT 0x2


#endif /*_BCMNETLINK_H */
