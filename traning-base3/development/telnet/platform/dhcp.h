#define IP_ADDR_LEN               4
#define DOMAIN_NAME_LEN          30
#define MAC_ADDR_LEN              6

#define TIMEOUT                2000

#define BROADCAST_ADDR   0xffffffff
#define BROADCAST_PORT           67
#define TRANSACTION_ID   0x12345678  /* DHCPトランザクションID */

#define DHCP_DISCOVER             1
#define DHCP_OFFER                2
#define DHCP_REQUEST              3
#define DHCP_PACK                 5
#define DHCP_PNAK                 6
#define DHCP_RELEASE              7


typedef struct DHCP_STRUCTURE {
    UB ipaddr[IP_ADDR_LEN];      /* IPアドレス */
    UB maskaddr[IP_ADDR_LEN];    /* サブネット・マスク */
    UB gwaddr[IP_ADDR_LEN];      /* ゲートウェイ・アドレス */
    UB dnsaddr[IP_ADDR_LEN];     /* DNSアドレス */
    UB dhcpsrvaddr[IP_ADDR_LEN]; /* DHCPサーバ・アドレス */
    B  domain[DOMAIN_NAME_LEN];  /* ドメイン名 */
    UB macaddr[MAC_ADDR_LEN];    /* MACアドレス */
} DHCP;


/* DHCPオプションフレーム */
typedef struct DHCP_VENDOR_OPTIONS {
    UB magic_cookie[4];
    UB message_type1[2];
    UB message_type2;
    UB client_id1[2];
    UB client_id2;
    UB client_mac[6];
    UB dummy[296];    /* DHCPオプションはMAX 312 byte */
} DV_OPTIONS;


/* DHCPフレーム */
typedef struct DHCP_packet {
    UB opecode;
    UB hard_addr;
    UB hard_addr_len;
    UB hop_count;
    UW transaction_id;
    UH second;
    UH dummy;
    UB client_ip[4];
    UB user_ip[4];
    UB server_ip[4];
    UB gateway_ip[4];
    UB client_hard_addr[16];
    UB server_host_name[64];
    UB file_name[128];
    DV_OPTIONS options;
} DHCP_PACKET;


extern ER   dhcp_open(T_IF_SOFTC  *ic);
/* extern void dhcp_close(void); */
