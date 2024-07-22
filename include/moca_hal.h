/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/**********************************************************************

    module: moca_hal.h

        For CCSP Component:  MoCA_Provisioning_and_management

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and
        structure definitions used for the RDK-Broadband
        MoCA hardware abstraction layer

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support MoCA drivers
        through an open API.  The current implementation created
        below this HAL supports MoCA.
        Changes may be needed to support other MoCA enviornments.

         @file moca_hal.h
         @brief RDK-Broadband MoCA Hardware Abstraction Layer
         This header file defines function prototypes, structures, and constants used
         for interfacing with the MoCA hardware through a standardized API.
         @details The current implementation is tailored for a specific MoCA environment
         (MoCA specification version?). Adaptations may be needed for other MoCA environments or
         different versions of the MoCA specification.
         @component MoCA_Provisioning_and_management

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

#ifndef __MOCA_HAL_H__
#define __MOCA_HAL_H__
// TODO: Remove these common types and include them from a common makefile.

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS     0
#endif

#ifndef STATUS_FAILURE
#define STATUS_FAILURE     -1
#endif

#ifndef STATUS_NOT_AVAILABLE
#define STATUS_NOT_AVAILABLE     -2
#endif

/**
 * @defgroup MOCA_HAL MoCA Hardware Abstraction Layer (HAL)
 *
 * This group encompasses functions, data types, and constants that provide an abstraction layer for interacting with
 * MoCA hardware devices. The MoCA HAL facilitates communication between higher-level software components and the
 * underlying MoCA driver, enabling operations like configuration, status retrieval, and statistics collection.
 *
 * @ingroup Network_Interfaces
 * @{
 */

/**
 * @defgroup MOCA_HAL_TYPES MoCA HAL Data Types
 *
 * This subgroup defines the data structures used within the MoCA HAL to represent MoCA configurations, statistics,
 * and other relevant information.
 *
 * @ingroup MOCA_HAL
 * @{
 */

/**
 * @defgroup MOCA_HAL_APIS MoCA HAL APIs
 *
 * This subgroup contains the function prototypes for the MoCA HAL API, which allows applications to control and
 * monitor MoCA devices through a standardized interface.
 *
 * @ingroup MOCA_HAL
 * @{
 */

/**
 * @addtogroup MOCA_HAL_TYPES
 * @{
 */

/**
 * @brief Maximum number of CPE (Customer Premises Equipment) devices in a MoCA network.
 */
#define kMoca_MaxCpeList 256

/**
 * @brief Maximum number of MoCA nodes allowed in a network.
 */
#define kMoca_MaxMocaNodes 16

/**
 * @brief Number of padding bytes added to a 6-byte MAC address to make it 18 bytes long. 
 *        This is required on platforms that handle MAC addresses as 18 bytes, while RDKB uses 6-byte MACs.
 */
#define MAC_PADDING 12

#define STATUS_INPROGRESS -1             /**< Status code: ACA process is in progress */
#define STATUS_NO_NODE -2                /**< Status code: Specified MoCA node does not exist */
#define STATUS_INVALID_PROBE -3          /**< Status code: HAL API called with invalid probe type */
#define STATUS_INVALID_CHAN -4           /**< Status code: HAL API called with invalid channel */
// TODO: Replace these status codes with strongly typed enums for better type safety and readability.

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
#ifndef MOCA_VAR

/**
 * @brief Possible states of a MoCA interface.
 */
typedef enum
{
    IF_STATUS_Up = 1,                /**< Interface is up and operational */
    IF_STATUS_Down = 2,              /**< Interface is down (not operational) */
    IF_STATUS_Unknown = 3,           /**< Interface status is unknown */
    IF_STATUS_Dormant = 4,           /**< Interface is dormant (temporarily inactive) */
    IF_STATUS_NotPresent = 5,        /**< Interface is not physically present */
    IF_STATUS_LowerLayerDown = 6,    /**< Lower layer of the interface is down */
    IF_STATUS_Error = 7             /**< Interface is in an error state */
} moca_if_status_t;

#endif

typedef enum
{
    PROBE_QUITE = 0, /**< Quiet probe (no signal transmission) */
    PROBE_EVM   = 1   /**< EVM (Error Vector Magnitude) probe (transmits signal to measure signal quality) */
}PROBE_TYPE;

#if 0
typedef enum
{
    STAT_SUCCESS =0,         /**< ACA Status is Success. */
    STAT_FAIL_BADCHANNEL =1, /**< ACA Status is Badchannel. */
    STAT_FAIL_NOEVMPROBE =2, /**< ACA Status is NoEVMProbe. */
    STAT_FAIL =3,            /**< ACA Status is fail. */
    STAT_INPROGRESS =4       /**< ACA Status is Inprogress. */
}ACA_STATUS;
#endif
/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**
 * @brief Configuration parameters for a MoCA interface.
 */
typedef struct
{
    ULONG InstanceNumber;      /**< Instance number (0 for single interface, 1-256 for multiple) */

    CHAR Alias[64];            /**< Vendor-specific alias name for the interface (max 64 characters) */
    BOOL bEnabled;             /**< Flag: TRUE if the interface is enabled, FALSE otherwise */
    BOOL bPreferredNC;         /**< Flag: TRUE if the node prefers to be Network Coordinator, FALSE otherwise */
    BOOL PrivacyEnabledSetting;/**< Flag: TRUE if link privacy is enabled, FALSE otherwise */

    UCHAR FreqCurrentMaskSetting[128];    /**< Bitmask indicating the set of frequencies to use for network formation (vendor-specific) */
    CHAR KeyPassphrase[18];    /**< Privacy password (valid only if privacy is enabled) (max 18 characters) */

    INT TxPowerLimit;          /**< Maximum allowed transmission power (signed integer, range: -(2^31) to (2^31)-1) */
    ULONG AutoPowerControlPhyRate;   /**< Target PHY rate for automatic power control (unsigned long, range: 0 to (2^32)-1) */
    ULONG BeaconPowerLimit;    /**< Maximum allowed transmission power for beacons (unsigned long, range: 0 to (2^32)-1) */

    ULONG MaxIngressBWThreshold; /**< Maximum ingress bandwidth threshold (unsigned long, range: 0 to (2^32)-1) */
    ULONG MaxEgressBWThreshold;  /**< Maximum egress bandwidth threshold (unsigned long, range: 0 to (2^32)-1) */

    BOOL Reset;                /**< Flag: TRUE to reset MoCA configuration parameters to defaults, FALSE otherwise */
    BOOL MixedMode;            /**< Flag: TRUE to enable mixed mode (1.0/1.1/2.0) operation, FALSE otherwise */
    BOOL ChannelScanning;      /**< Flag: TRUE to enable channel scanning mode, FALSE for single frequency mode */
    BOOL AutoPowerControlEnable;   /**< Flag: TRUE to enable automatic power control, FALSE otherwise */

    BOOL EnableTabooBit;       /**< Flag: TRUE to enable support for taboo mask, FALSE otherwise */
    UCHAR NodeTabooMask[128];   /**< Bitmask indicating frequencies to avoid (taboo mask) (vendor-specific) */
    UCHAR ChannelScanMask[128]; /**< Bitmask indicating frequencies to scan for beacons (vendor-specific) */
} moca_cfg_t;

/**
 * @brief Static information about a MoCA interface.
 */
typedef struct
{
    CHAR Name[64];                      /**< Unique interface name (e.g., "moca0", "nmoca0") (max 64 characters) */
    UCHAR MacAddress[6 + MAC_PADDING];   /**< MAC address of the local node (format: AA:BB:CC:DD:EE:FF) */
    CHAR FirmwareVersion[64];            /**< MoCA firmware version (vendor-specific) (max 64 characters) */
    ULONG MaxBitRate;                   /**< Maximum PHY rate supported by the node (unsigned long, range: 0 to (2^32)-1) */
    CHAR HighestVersion[64];            /**< Highest MoCA protocol version supported by the node (e.g., "1.0", "1.1", "2.0") (vendor-specific) (max 64 characters) */

    UCHAR FreqCapabilityMask[8];       /**< Bitmask indicating frequencies supported by the local node (vendor-specific) */
    UCHAR NetworkTabooMask[128];       /**< Bitmask indicating frequencies not supported by the local node (vendor-specific) */

    ULONG TxBcastPowerReduction;       /**< Beacon backoff in dB (unsigned long, range: 0 to (2^32)-1) */
    BOOL QAM256Capable;                /**< Flag: TRUE if the node is QAM-256 capable, FALSE otherwise */
    BOOL PacketAggregationCapability;  /**< Flag: TRUE if the node can aggregate Ethernet packets, FALSE otherwise */
} moca_static_info_t;

#ifndef MOCA_VAR
/**
 * @brief Dynamic information about a MoCA interface.
 */
typedef struct
{
    moca_if_status_t Status;             /**< Current status of the local interface (see moca_if_status_t enum) */
    ULONG LastChange;                   /**< Timestamp of the last link status change (in seconds since epoch) */
    ULONG MaxIngressBW;                 /**< Maximum ingress bandwidth reached (bits per second) */
    ULONG MaxEgressBW;                  /**< Maximum egress bandwidth reached (bits per second) */
    CHAR CurrentVersion[64];            /**< Current MoCA protocol version (e.g., "1.0", "1.1", "2.0") */
    ULONG NetworkCoordinator;          /**< Node ID of the Network Coordinator (0-7 for MoCA 1.0, 0-15 for 1.1/2.0) */
    ULONG NodeID;                      /**< Node ID of the local node (0-7 for MoCA 1.0, 0-15 for 1.1/2.0) */
    ULONG BackupNC;                    /**< Node ID of the backup Network Coordinator (0-7 for MoCA 1.0, 0-15 for 1.1/2.0) */
    BOOL PrivacyEnabled;               /**< Flag: TRUE if privacy is enabled on the network, FALSE otherwise */
    UCHAR FreqCurrentMask[8];           /**< Bitmask indicating the currently used frequencies (vendor-specific) */
    ULONG CurrentOperFreq;              /**< Current operating frequency of the node (vendor-specific) */
    ULONG LastOperFreq;                 /**< Last operating frequency of the node before the current one (vendor-specific) */
    ULONG TxBcastRate;                 /**< Transmission broadcast rate */
    BOOL MaxIngressBWThresholdReached;  /**< Flag: TRUE if the maximum ingress bandwidth threshold has been reached, FALSE otherwise */
    BOOL MaxEgressBWThresholdReached;   /**< Flag: TRUE if the maximum egress bandwidth threshold has been reached, FALSE otherwise */
    ULONG NumberOfConnectedClients;     /**< Number of nodes connected to the MoCA network (0-256) */
    CHAR NetworkCoordinatorMACAddress[18]; /**< MAC address of the Network Coordinator (format: AA:BB:CC:DD:EE:FF) */
    ULONG LinkUpTime;                   /**< Duration (in seconds) the node has been connected to the MoCA network with at least one other node */
} moca_dynamic_info_t;

#endif

/**
 * @brief Statistics for a MoCA interface.
 */
typedef struct
{
    ULONG BytesSent;              /**< Total number of bytes sent */
    ULONG BytesReceived;          /**< Total number of bytes received */
    ULONG PacketsSent;            /**< Total number of packets sent */
    ULONG PacketsReceived;        /**< Total number of packets received */
    ULONG ErrorsSent;             /**< Number of errors in sent packets */
    ULONG ErrorsReceived;         /**< Number of errors in received packets */
    ULONG UnicastPacketsSent;     /**< Number of unicast packets sent */
    ULONG UnicastPacketsReceived; /**< Number of unicast packets received */
    ULONG DiscardPacketsSent;     /**< Number of packets discarded on the transmit (Tx) side */
    ULONG DiscardPacketsReceived; /**< Number of packets discarded on the receive (Rx) side */
    ULONG MulticastPacketsSent;   /**< Number of multicast packets sent */
    ULONG MulticastPacketsReceived; /**< Number of multicast packets received */
    ULONG BroadcastPacketsSent;   /**< Number of broadcast packets sent */
    ULONG BroadcastPacketsReceived; /**< Number of broadcast packets received */
    ULONG UnknownProtoPacketsReceived; /**< Number of packets received with unknown protocols */
    ULONG ExtAggrAverageTx;       /**< Aggregate average of transmitted packet counts (vendor-specific) */
    ULONG ExtAggrAverageRx;       /**< Aggregate average of received packet counts (vendor-specific) */
} moca_stats_t;

/**
 * @brief Counters for various MoCA MAC-layer packets.
 */
typedef struct
{
    ULONG Map;   /**< Number of MAP (MoCA Access Protocol) packets received */
    ULONG Rsrv;  /**< Number of reservation request packets received */
    ULONG Lc;    /**< Number of link control packets received */
    ULONG Adm;   /**< Number of admission request packets received */
    ULONG Probe; /**< Number of probe packets received */
    ULONG Async; /**< Number of asynchronous (beacon) packets received */
} moca_mac_counters_t;

/**
 * @brief Aggregate counters for transmitted and received MoCA payload data units (PDUs).
 */
typedef struct
{
    ULONG Tx;  /**< Total number of transmitted payload data units (PDUs), excluding MoCA control packets */
    ULONG Rx;  /**< Total number of received payload data units (PDUs), excluding MoCA control packets */
} moca_aggregate_counters_t;

/**
 * @brief Represents a MoCA Customer Premises Equipment (CPE) node.
 */
typedef struct
{
    CHAR mac_addr[6];  /**< MAC address of the CPE node (format: AA:BB:CC:DD:EE:FF) */
} moca_cpe_t;

/**
 * @brief Information about a device associated with the MoCA network.
 */
typedef struct
{
    UCHAR MACAddress[6 + MAC_PADDING];   /**< MAC address of the associated device (format: AA:BB:CC:DD:EE:FF) */
    ULONG NodeID;                      /**< Node ID of the associated device (vendor-specific) */
    BOOL PreferredNC;                  /**< Flag: TRUE if the device prefers to be Network Coordinator, FALSE otherwise */
    CHAR HighestVersion[64];            /**< Highest MoCA protocol version supported by the device (e.g., "1.0", "1.1", "2.0") */
    ULONG PHYTxRate;                   /**< Transmit PHY rate of the device */
    ULONG PHYRxRate;                   /**< Receive PHY rate of the device */
    ULONG TxPowerControlReduction;     /**< Transmit power reduction applied by the device (in dB) */
    INT RxPowerLevel;                  /**< Received power level measured by the device (dBm) */
    ULONG TxBcastRate;                 /**< Transmit broadcast PHY rate of the device */
    INT RxBcastPowerLevel;             /**< Received broadcast power level measured by the device (dBm) */
    ULONG TxPackets;                   /**< Number of packets transmitted by the device */
    ULONG RxPackets;                   /**< Number of packets received by the device */
    ULONG RxErroredAndMissedPackets;   /**< Number of errored or missed packets received by the device */
    BOOL QAM256Capable;                /**< Flag: TRUE if the device is QAM-256 capable, FALSE otherwise */
    BOOL PacketAggregationCapability;  /**< Flag: TRUE if the device supports packet aggregation, FALSE otherwise */
    ULONG RxSNR;                       /**< Receive Signal-to-Noise Ratio (SNR) measured by the device */
    BOOL Active;                      /**< Flag: TRUE if the device is active on the network, FALSE otherwise */
    ULONG RxBcastRate;                 /**< Receive broadcast PHY rate of the device */
    ULONG NumberOfClients;             /**< Number of clients connected to this device (if it's a node) */
} moca_associated_device_t;

#ifndef MOCA_VAR
/**
 * @brief Represents an entry in the MoCA mesh PHY rate table.
 *
 * This table stores the unicast transmit PHY rates between all pairs of nodes in the MoCA network.
 */
typedef struct
{
    ULONG RxNodeID;     /**< Receiving node ID (used as one index in the table) */
    ULONG TxNodeID;     /**< Transmitting node ID (used as another index in the table) */
    ULONG TxRate;       /**< Transmit PHY rate from TxNodeID to RxNodeID (in Mbps) */
    ULONG TxRateNper;   /**< MoCA 2.x: Transmit PHY rate for NPER (Network Performance Enhancement Rate) (in Mbps) */
    ULONG TxRateVlper;  /**< MoCA 2.x: Transmit PHY rate for VLPER (Very Low Packet Error Rate) (in Mbps) */
} moca_mesh_table_t;
#endif

/**
 * @brief Represents an entry in the MoCA interface flow statistics table.
 *
 * This table provides statistics about ingress PQoS (Priority Quality of Service) flows in a MoCA interface.
 */
typedef struct
{
    ULONG FlowID;              /**< Flow ID of the PQoS flow */
    ULONG IngressNodeID;       /**< Node ID where the PQoS flow enters the MoCA network */
    ULONG EgressNodeID;        /**< Node ID where the PQoS flow leaves the MoCA network */
    ULONG FlowTimeLeft;        /**< Remaining lease time of the PQoS flow */
    char DestinationMACAddress[18];   /**< Destination MAC address of Ethernet packets in the PQoS flow */
    ULONG PacketSize;          /**< Number of MoCA aggregated frames in the PQoS flow */
    ULONG PeakDataRate;        /**< Peak data rate of the PQoS flow (in bits per second) */
    ULONG BurstSize;           /**< Burst size of the PQoS flow (in bytes) */
    ULONG FlowTag;            /**< Application-specific flow tag of the PQoS flow */
    ULONG LeaseTime;           /**< Initial lease time of the PQoS flow (in seconds) */
} moca_flow_table_t;

/**
 * @brief Callback function type for MoCA associated device events.
 *
 * This callback is invoked when a MoCA client is activated or deactivated on the network.
 * 
 * @param ifIndex The index of the MoCA interface where the event occurred.
 * @param moca_dev Pointer to a `moca_associated_device_t` structure containing information about the associated device. 
 *                 The `Active` member of this structure indicates whether the device has been activated (TRUE) or deactivated (FALSE).
 *
 * @return INT A status code indicating the result of handling the event.
 */
typedef INT (*moca_associatedDevice_callback)(ULONG ifIndex, moca_associated_device_t *moca_dev);

/**
 * @brief Information about a MoCA node's preferred network coordinator (NC) status.
 */
typedef struct moca_assoc_pnc_info
{
    ULONG mocaNodeIndex;      /**< The index (or ID) of the MoCA node */
    BOOL  mocaNodePreferredNC; /**< Flag: TRUE if the node is a preferred network coordinator (NC), FALSE otherwise */
    ULONG mocaNodeMocaversion; /**< MoCA version supported by the node (e.g., 10 for MoCA 1.0, 11 for MoCA 1.1, 20 for MoCA 2.0) */
} moca_assoc_pnc_info_t;

/**
 * @brief Subcarrier modulation statistics for a MoCA link between two nodes.
 */
typedef struct
{
    INT TxNode;    /**< Transmitting MoCA node ID */
    INT RxNode;    /**< Receiving MoCA node ID */
    INT Channel;   /**< Channel used for the NPER and VLPER calculations (primary or secondary) */

    UCHAR Mod[512];   /**< Modulation scheme used for each subcarrier (512 elements, each 0 to (2^32)-1) */
    UCHAR Nper[512];  /**< NPER (Network Performance Enhancement Rate) for each subcarrier on the channel (512 elements, each 0 to (2^32)-1) */
    UCHAR Vlper[512]; /**< VLPER (Very Low Packet Error Rate) for each subcarrier on the channel (512 elements, each 0 to (2^32)-1) */
} moca_scmod_stat_t;

/**
 * @brief Configuration parameters for initiating an ACA (Automatic Channel Adaptation) test.
 */
typedef struct
{
    UINT NodeID;      /**< Node ID where the ACA test should start */
    PROBE_TYPE Type;  /**< Type of probe to use during the ACA test (PROBE_QUITE or PROBE_EVM) */
    UINT Channel;    /**< Channel on which the ACA test should start */
    UINT ReportNodes; /**< Bitmask indicating which MoCA nodes should be included in the assessment (LSB = Node 0) */
    BOOL ACAStart;    /**< Flag to start the ACA process: TRUE to start, FALSE for no action */
} moca_aca_cfg_t;

/**
 * @brief Status and results of an ACA (Automatic Channel Adaptation) test.
 */
typedef struct
{
    moca_aca_cfg_t acaCfg;      /**< Configuration used for the ACA test (see moca_aca_cfg_t) */
    INT stat;                  /**< Status of the ACA process: 0 (SUCCESS), 1 (FAIL_BADCHANNEL), 2 (FAIL_NOEVMPROBE), 3 (FAIL), or 4 (IN_PROGRESS) */
    INT RxPower;               /**< Total received power (dBm) */
    INT ACAPowProfile[512];     /**< Power profile for each channel (dBm), where each element represents a channel and the value is the power level */
    BOOL ACATrapCompleted;     /**< Flag: TRUE if the power profile is ready, FALSE otherwise */
} moca_aca_stat_t;

/** @} */  //END OF GROUP MOCA_HAL_TYPES

/**
 * @brief Registers a callback function to be invoked on MoCA associated device events.
 *
 * This function allows you to register a callback function that will be called whenever a MoCA client is
 * activated or deactivated on the network.
 *
 * @param callback_proc Pointer to the callback function of type `moca_associatedDevice_callback`. 
 *                      This function will be called with the interface index and associated device information.
 */
void moca_associatedDevice_callback_register(moca_associatedDevice_callback callback_proc); 

/**
 * @addtogroup MOCA_HAL_APIS
 * @{
 */
/**********************************************************************************
 *
 *  MoCA Subsystem level function prototypes
 *
**********************************************************************************/

/* TODO:
 * 1. Extend the return codes by listing out the possible reasons of failure, to improve the interface in the future.
 *    This was reported during the review for header file migration to opensource github.
 */ 

/**
* @brief Gets the MoCA Configuration Parameters that were previously set.
*
* @param[in] ifIndex Index of the MoCA Interface.
* @param[out] pmoca_config A pointer to structure of type moca_cfg_t for configuration parameters.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS - if successful.
* @retval STATUS_FAILURE - if any error is detected.
*/
INT moca_GetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/**
 * @brief Sets the MoCA Configuration Parameters.
 *
 * @param[in] ifIndex Index of the MoCA Interface.
 * @param[in] pmoca_config A pointer to structure of type moca_cfg_t for configuration parameters.
 *
 * @return The status of the operation.
 * @retval STATUS_SUCCESS - if successful.
 * @retval STATUS_FAILURE - if any error is detected.
 */
INT moca_SetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/**
 * @brief Gets the dynamic status information of a MoCA interface and its associated network.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pmoca_dynamic_info Pointer to a `moca_dynamic_info_t` structure to store the retrieved dynamic information.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_IfGetDynamicInfo(ULONG ifIndex, moca_dynamic_info_t *pmoca_dynamic_info);

/**
 * @brief Retrieves static information about a MoCA interface.
 *
 * This function fetches static information (e.g., firmware version, MAC address, protocol capabilities) 
 * from the specified MoCA interface. The retrieved information is populated into the provided
 * `moca_static_info_t` structure.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pmoca_static_info Pointer to a `moca_static_info_t` structure to store the retrieved static information.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_IfGetStaticInfo(ULONG ifIndex, moca_static_info_t *pmoca_static_info);

/**
 * @brief Retrieves network layer statistics for a MoCA interface.
 *
 * This function fetches statistics related to the network layer operation of a specified MoCA interface. 
 * The retrieved statistics are populated into the provided `moca_stats_t` structure.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pmoca_stats Pointer to a `moca_stats_t` structure to store the retrieved statistics.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_IfGetStats(ULONG ifIndex, moca_stats_t *pmoca_stats);

/**
 * @brief Retrieves the number of associated devices on a MoCA network.
 *
 * This function returns the count of devices connected to the MoCA network associated with the specified interface.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pulCount Pointer to an unsigned long integer to store the retrieved number of associated devices.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_GetNumAssociatedDevices(ULONG ifIndex, ULONG *pulCount);

/* moca_IfGetExtCounter() function */
/**
 * @brief Retrieves MoCA MAC layer statistics for an interface.
 *
 * This function fetches statistical counters related to the MoCA MAC layer for the specified interface.
 * The retrieved counters are populated into the provided `moca_mac_counters_t` structure.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pmoca_mac_counters Pointer to a `moca_mac_counters_t` structure to store the retrieved MAC layer statistics.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_IfGetExtCounter(ULONG ifIndex, moca_mac_counters_t *pmoca_mac_counters);

/**
 * @brief Retrieves aggregate transmit and receive data unit counters for a MoCA interface.
 *
 * This function fetches the aggregate counts of transmitted and received data units (excluding MoCA control packets) 
 * for the specified MoCA interface. The retrieved counters are populated into the provided `moca_aggregate_counters_t` structure.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pmoca_aggregate_counts Pointer to a `moca_aggregate_counters_t` structure to store the retrieved counters.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_IfGetExtAggrCounter(ULONG ifIndex, moca_aggregate_counters_t *pmoca_aggregate_counts);

/**
 * @brief Retrieves the MAC addresses of all MoCA nodes on the network.
 *
 * This function fetches the MAC addresses of all MoCA Customer Premises Equipment (CPE) nodes 
 * connected to the MoCA network associated with the specified interface. The retrieved MAC 
 * addresses are stored in the provided `cpes` array, and the count of nodes is returned in `pnum_cpes`.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] cpes Array of `moca_cpe_t` structures to store the retrieved MAC addresses. 
 *                  The array should be pre-allocated with enough space for `kMoca_MaxCpeList` (256) entries.
 * @param[out] pnum_cpes Pointer to an integer variable to store the number of MoCA nodes found on the network.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_GetMocaCPEs(ULONG ifIndex, moca_cpe_t *cpes, INT *pnum_cpes);

/**
 * @brief Retrieves information about all associated devices on the MoCA network.
 *
 * This function fetches detailed information about each MoCA device connected to the network associated with the specified interface. 
 * The retrieved data includes MAC addresses, node IDs, PHY rates, power levels, and more.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] ppdevice_array Pointer to a pointer that will be populated with an array of `moca_associated_device_t` structures. 
 *                            Each structure in the array contains information about a single associated device. 
 *                            The caller is responsible for allocating memory for this array.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_GetAssociatedDevices(ULONG ifIndex, moca_associated_device_t **ppdevice_array);

/**
 * @brief Converts a frequency mask to a frequency value.
 *
 * This utility function takes a bit mask representing a set of frequencies 
 * and returns the corresponding frequency value. The specific interpretation
 * of the mask and the resulting frequency value may be vendor-specific.
 *
 * @param mask Pointer to an array of bytes (`UCHAR`) representing the frequency mask.
 *             The buffer size should be at least 16 bytes and is vendor-dependent.
 *
 * @return Frequency value corresponding to the given mask if successful, otherwise STATUS_FAILURE.
 *
 * @note The interpretation of the frequency mask and the range of valid output values may be vendor-specific.
 */
INT moca_FreqMaskToValue(UCHAR *mask);

/**
 * @brief Checks if MoCA hardware is equipped and available.
 *
 * This function determines whether MoCA hardware is present and correctly configured on the system.
 *
 * @return TRUE if MoCA hardware is equipped and available, FALSE otherwise.
 */
BOOL moca_HardwareEquipped(void);

#ifndef MOCA_VAR
/**
 * @brief Retrieves MoCA full mesh PHY rates.
 *
 * This function fetches the complete mesh PHY (physical layer) rates between all pairs of MoCA nodes on the network associated with the specified interface.
 * The retrieved rates are stored in the provided `pDeviceArray`, and the number of entries in the array is returned in `pulCount`.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pDeviceArray Pointer to a `moca_mesh_table_t` array to store the retrieved mesh PHY rate table. 
 *                          The caller must allocate enough memory for this array to hold entries for all possible node pairs.
 * @param[out] pulCount Pointer to an unsigned long integer to store the number of entries written to the `pDeviceArray`.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 *
 * @note This function is only available when the `MOCA_VAR` macro is not defined.
 */
INT moca_GetFullMeshRates(ULONG ifIndex, moca_mesh_table_t *pDeviceArray, ULONG *pulCount);
#endif

/**
 * @brief Retrieves MoCA flow statistics.
 *
 * This function fetches the entries in the MoCA flow table, which contains statistics for
 * ingress PQoS (Priority Quality of Service) flows on the specified MoCA interface.
 *
 * @param ifIndex The index of the MoCA interface (0 for a single interface, 1-256 for multiple interfaces).
 * @param[out] pDeviceArray Pointer to a `moca_flow_table_t` array to store the retrieved flow table entries. 
 *                          The caller must allocate enough memory for this array to hold all entries.
 * @param[out] pulCount Pointer to an unsigned long integer to store the number of entries written to the `pDeviceArray`.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_GetFlowStatistics(ULONG ifIndex, moca_flow_table_t *pDeviceArray, ULONG *pulCount);

/**
 * @brief Retrieves the MoCA reset count.
 *
 * This function fetches the number of times the MoCA module has been reset.
 * If the operation fails, the value pointed to by `resetcnt` remains unchanged.
 *
 * @param[out] resetcnt Pointer to an unsigned long integer where the reset count will be stored.
 *
 * @return Status of the operation.
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
INT moca_GetResetCount(ULONG *resetcnt);

/**
 * @brief Initiates the MoCA Automatic Channel Adaptation (ACA) process.
 *
 * This function configures and potentially starts the ACA process on the specified MoCA interface. The ACA process
 * automatically selects the best operating channel for the MoCA network.
 *
 * @param interfaceIndex The index of the MoCA interface.
 * @param[in] acaCfg Configuration parameters for the ACA process (see `moca_aca_cfg_t`). 
 *                   Setting the `ACAStart` member to `TRUE` will trigger the ACA process.
 *
 * @return Status of the operation:
 * @retval STATUS_SUCCESS  - The ACA process was successfully configured and started (if `ACAStart` was TRUE).
 * @retval STATUS_FAILURE  - An error occurred during configuration or initialization.
 * @retval STATUS_INPROGRESS - An ACA process is already running on the interface.
 *
 * @note
 *    * If the `ACAStart` flag in `acaCfg` is set to `TRUE`, the ACA process will begin immediately.
 *    * If `ACAStart` is `FALSE`, only the configuration parameters will be set, and the ACA process won't start.
 *    * If an ACA process is already in progress on the interface, this function will return `STATUS_INPROGRESS`
 *      and will not start a new ACA process.
 */
int moca_setIfAcaConfig(int interfaceIndex, moca_aca_cfg_t acaCfg);

/**
 * @brief Retrieves the current MoCA ACA configuration parameters.
 *
 * This function fetches the configuration parameters that were set for the Automatic Channel Adaptation (ACA) process on the
 * specified MoCA interface. The retrieved configuration is stored in the provided `acaCfg` structure.
 *
 * @param interfaceIndex The index of the MoCA interface.
 * @param[out] acaCfg Pointer to a `moca_aca_cfg_t` structure to store the retrieved ACA configuration parameters.
 *
 * @return Status of the operation:
 * @retval STATUS_SUCCESS - The operation was successful.
 * @retval STATUS_FAILURE - An error occurred during the operation.
 */
int moca_getIfAcaConfig(int interfaceIndex, moca_aca_cfg_t *acaCfg);

/**
 * @brief Cancels an ongoing MoCA Automatic Channel Adaptation (ACA) process.
 *
 * This function terminates a currently running ACA process on the specified MoCA interface. 
 * If no ACA process is active, it has no effect.
 *
 * @param interfaceIndex The index of the MoCA interface where the ACA process is running.
 *
 * @return Status of the operation:
 * @retval STATUS_SUCCESS - The ACA process was successfully cancelled or was not running.
 * @retval STATUS_FAILURE - An error occurred while attempting to cancel the ACA process.
 */
int moca_cancelIfAca(int interfaceIndex);


/**
 * @brief Retrieves the status and results of a MoCA Automatic Channel Adaptation (ACA) process.
 *
 * This function fetches the current status, results, and configuration details of an ongoing or completed ACA process 
 * on the specified MoCA interface. The retrieved information is stored in the provided `moca_aca_stat_t` structure.
 *
 * @param interfaceIndex The index of the MoCA interface.
 * @param[out] pacaStat Pointer to a `moca_aca_stat_t` structure to store the retrieved ACA status and results.
 *
 * @return Status of the operation:
 * @retval STATUS_SUCCESS - The operation was successful, and ACA status and results were retrieved.
 * @retval STATUS_FAILURE - An error occurred during the operation, and no valid ACA information was obtained.
 */
int moca_getIfAcaStatus(int interfaceIndex,moca_aca_stat_t *pacaStat);

/**
 * @brief Retrieves MoCA Subcarrier Modulation (SCMOD) statistics after an ACA process.
 *
 * This function fetches the SCMOD statistics collected after an Automatic Channel Adaptation (ACA) process on the specified MoCA interface. 
 * These statistics provide detailed information about the modulation schemes and error rates for each subcarrier on the MoCA channel.
 *
 * @param interfaceIndex The index of the MoCA interface.
 * @param[out] pnumOfEntries Pointer to an integer that will be filled with the number of entries in the `ppscmodStat` array.
 * @param[out] ppscmodStat Pointer to a pointer that will be populated with an array of `moca_scmod_stat_t` structures. 
 *                         Each structure contains SCMOD statistics for a pair of nodes on the MoCA network. 
 *                         The caller is responsible for allocating memory for this array.
 *
 * @return Status of the operation:
 * @retval STATUS_SUCCESS - The operation was successful, and SCMOD statistics were retrieved.
 * @retval STATUS_FAILURE - An error occurred during the operation, and no valid SCMOD information was obtained.
 */
int moca_getIfScmod(int interfaceIndex,int *pnumOfEntries,moca_scmod_stat_t **ppscmodStat);

/** @} */  //END OF GROUP MOCA_HAL_APIS
#endif

