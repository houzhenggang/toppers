#ifdef TARGET_KERNEL_ASP
#include <kernel.h>
#include "kernel_cfg.h"
#endif
#ifdef TARGET_KERNEL_JSP
#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#endif
#include "tinet_id.h"
#include <tinet_defs.h>
#include <tinet_config.h>
#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net_buf.h>
#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/udp_var.h>

#include "config.h"

#define TNUM_TCP_REPID	1

const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);

T_TCP4_REP tcp_rep[TNUM_TCP_REPID] = {
	{
		0,
		{ IPV4_ADDRANY, 23 },
#if defined(TCP_CFG_EXTENTIONS)
		TCP_REP_FLG_VALID,
		SEM_TCP_REP_LOCK1,
#endif
		},
	};

#define TNUM_TCP_CEPID	1

const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);

T_TCP4_CEP tcp_cep[TNUM_TCP_CEPID] = {
	{
		0,
		(void*)tcp_telnet_srv_swbuf,
		( TCP_MSS ),
		(void*)tcp_telnet_srv_rwbuf,
		( TCP_MSS ),
		(t_tcp_callback)( FP ) callback_nblk_tcp_telnet_srv,
		TCP_CEP_FLG_VALID,
		SEM_TCP_CEP_LOCK1,
		FLG_TCP_CEP_EST1,
		FLG_TCP_CEP_SND1,
		FLG_TCP_CEP_RCV1,
		},
	};

#define TNUM_UDP_CEPID	1

const ID tmax_udp_cepid = (TMIN_UDP_CEPID + TNUM_UDP_CEPID - 1);

T_UDP4_CEP udp_cep[TNUM_UDP_CEPID] = {
	{
		0,
		{ IPV4_ADDRANY, 68 },
		(t_udp_callback)NULL,
		UDP_CEP_FLG_VALID,
		SEM_UDP_CEP_LOCK1,
		TA_NULL,
		TA_NULL,
		DTQ_UDP_RCVQ1,
		},
	};

