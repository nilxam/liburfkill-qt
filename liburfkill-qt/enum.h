#ifndef __ENUM_H
#define __ENUM_H

/**
 * UrfEnumType:
 * @URF_ENUM_TYPE_ALL: toggles all switches (requests only - not a switch type)
 * @URF_ENUM_TYPE_WLAN: switch is on a 802.11 wireless network device.
 * @URF_ENUM_TYPE_BLUETOOTH: switch is on a bluetooth device.
 * @URF_ENUM_TYPE_UWB: switch is on a ultra wideband device.
 * @URF_ENUM_TYPE_WIMAX: switch is on a WiMAX device.
 * @URF_ENUM_TYPE_WWAN: switch is on a wireless WAN device.
 * @URF_ENUM_TYPE_GPS: switch is on a GPS device.
 * @URF_ENUM_TYPE_FM: switch is on a FM radio device.
 * @URF_ENUM_TYPE_NUM: number of defined rfkill types
 *
 * The type of the rfkill device following the definition in &lt;linux/rfkill.h&gt;
 */
typedef enum {
	URF_ENUM_TYPE_ALL = 0,
	URF_ENUM_TYPE_WLAN,
	URF_ENUM_TYPE_BLUETOOTH,
	URF_ENUM_TYPE_UWB,
	URF_ENUM_TYPE_WIMAX,
	URF_ENUM_TYPE_WWAN,
	URF_ENUM_TYPE_GPS,
	URF_ENUM_TYPE_FM,
	URF_ENUM_TYPE_NUM,
} UrfEnumType;

/**
 * UrfEnumState:
 * @URF_ENUM_STATE_NO_ADAPTER: switch doesn't exist
 * @URF_ENUM_STATE_UNBLOCKED: switch is unblocked
 * @URF_ENUM_STATE_SOFT_BLOCKED: switch is soft-blocked.
 * @URF_ENUM_STATE_HARD_BLOCKED: switch is hard-blocked.
 *
 * The state of the switch
 */
typedef enum {
	URF_ENUM_STATE_NO_ADAPTER = -1,
	URF_ENUM_STATE_UNBLOCKED = 0,
	URF_ENUM_STATE_SOFT_BLOCKED,
	URF_ENUM_STATE_HARD_BLOCKED,
} UrfEnumState;

#endif
