{
	"TimeScale" :"us",
	"TimeRadix" :10,
	"ConvertRules"   :["fmp"],
	"VisualizeRules" :["toppers","fmp","fmp_core4"],
	"ResourceHeaders":["fmp"],
	"Resources":
	{
		"CurrentContext_PRC1":{
			"Type":"Context",
			"Attributes":
			{
				"name"    : "None"
			}
		},
		"CurrentContext_PRC2":{
			"Type":"Context",
			"Attributes":
			{
				"name"    : "None"
			}
		},
		"CurrentContext_PRC3":{
			"Type":"Context",
			"Attributes":
			{
				"name"    : "None"
			}
		},
		"CurrentContext_PRC4":{
			"Type":"Context",
			"Attributes":
			{
				"name"    : "None"
			}
		},
		"LOGTASK1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :1,
				"atr"   :"TA_ACT",
				"pri"   :3,
				"exinf" :"LOGTASK_PORTID_PRC1",
				"task"  :"logtask_main",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"LOGTASK2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :2,
				"atr"   :"TA_ACT",
				"pri"   :3,
				"exinf" :"LOGTASK_PORTID_PRC2",
				"task"  :"logtask_main",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"LOGTASK3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :3,
				"atr"   :"TA_ACT",
				"pri"   :3,
				"exinf" :"LOGTASK_PORTID_PRC3",
				"task"  :"logtask_main",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"LOGTASK4":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :4,
				"atr"   :"TA_ACT",
				"pri"   :3,
				"exinf" :"LOGTASK_PORTID_PRC4",
				"task"  :"logtask_main",
				"stksz" :1024,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK1_1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :5,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x10000|1",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK1_2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :6,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x10000|2",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK1_3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :7,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x10000|3",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"MAIN_TASK1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :8,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"1",
				"task"  :"main_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"SERVER_TASK1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :9,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"1",
				"task"  :"server_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK2_1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :10,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x20000|1",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK2_2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :11,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x20000|2",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK2_3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :12,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x20000|3",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"MAIN_TASK2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :13,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"2",
				"task"  :"main_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"SERVER_TASK2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :14,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"2",
				"task"  :"server_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK3_1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :15,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x30000|1",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK3_2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :16,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x30000|2",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK3_3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :17,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x30000|3",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"MAIN_TASK3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :18,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"3",
				"task"  :"main_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"SERVER_TASK3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :3,
				"id"    :19,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"3",
				"task"  :"server_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK4_1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :20,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x40000|1",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK4_2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :21,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x40000|2",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK4_3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :22,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"0x40000|3",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"MAIN_TASK4":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :23,
				"atr"   :"TA_ACT",
				"pri"   :5,
				"exinf" :"4",
				"task"  :"main_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"SERVER_TASK4":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :4,
				"id"    :24,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"4",
				"task"  :"server_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"INH_INHNO_TIMER_PRC1_target_timer_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :1,
				"id"    :5,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_TIMER_PRC2_target_timer_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :2,
				"id"    :5,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_TIMER_PRC3_target_timer_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :3,
				"id"    :-65531,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_TIMER_PRC4_target_timer_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :4,
				"id"    :-262139,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_SIO_PRC1_sio_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :1,
				"id"    :2,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_SIO_PRC2_sio_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :2,
				"id"    :2,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_SIO_PRC3_sio_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :3,
				"id"    :-65534,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_SIO_PRC4_sio_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :4,
				"id"    :-262142,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_IPI_PRC1__kernel_ipi_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :1,
				"id"    :16,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_IPI_PRC2__kernel_ipi_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :2,
				"id"    :16,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_IPI_PRC3__kernel_ipi_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :3,
				"id"    :-65520,
				"state"    : "DORMANT"
			}
		},
		"INH_INHNO_IPI_PRC4__kernel_ipi_handler":{
			"Type":"InterruptHandler",
			"Attributes":
			{
				"prcIdI" :4,
				"id"    :-262128,
				"state"    : "DORMANT"
			}
		},
,
		"CYCHDR1":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"prcIdC" :1,
				"id"    :1,
				"state"    : "DORMANT"
			}
		},
		"CYCHDR2":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"prcIdC" :2,
				"id"    :2,
				"state"    : "DORMANT"
			}
		},
		"CYCHDR3":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"prcIdC" :3,
				"id"    :3,
				"state"    : "DORMANT"
			}
		},
		"CYCHDR4":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"prcIdC" :4,
				"id"    :4,
				"state"    : "DORMANT"
			}
		},
		"ALMHDR1":{
			"Type":"AlarmHandler",
			"Attributes":
			{
				"prcIdA" :1,
				"id"    :1,
				"state"    : "DORMANT"
			}
		},
		"ALMHDR2":{
			"Type":"AlarmHandler",
			"Attributes":
			{
				"prcIdA" :2,
				"id"    :2,
				"state"    : "DORMANT"
			}
		},
		"ALMHDR3":{
			"Type":"AlarmHandler",
			"Attributes":
			{
				"prcIdA" :3,
				"id"    :3,
				"state"    : "DORMANT"
			}
		},
		"ALMHDR4":{
			"Type":"AlarmHandler",
			"Attributes":
			{
				"prcIdA" :4,
				"id"    :4,
				"state"    : "DORMANT"
			}
		},
,
		"TASK_TEX_PRC1":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"prcIdX" :1,
				"state"    : "DORMANT"
			}
		},
		"TASK_TEX_PRC2":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"prcIdX" :2,
				"state"    : "DORMANT"
			}
		},
		"TASK_TEX_PRC3":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"prcIdX" :3,
				"state"    : "DORMANT"
			}
		},
		"TASK_TEX_PRC4":{
			"Type":"TaskExceptionRoutine",
			"Attributes":
			{
				"prcIdX" :4,
				"state"    : "DORMANT"
			}
		}
	}
}

