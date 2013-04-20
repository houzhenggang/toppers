{
	"TimeScale" :"us",
	"TimeRadix" :10,
	"ConvertRules"   :["fmp"],
	"VisualizeRules" :["toppers","fmp","fmp_core2"],
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
		"TASK1":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :3,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"1",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :4,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"2",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK3":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :1,
				"id"    :5,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"3",
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
				"id"    :6,
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
				"id"    :7,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"1",
				"task"  :"server_task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"RUNNABLE"
			}
		},
		"TASK4":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :8,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"4",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK5":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :9,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"5",
				"task"  :"task",
				"stksz" :4096,
				"stk"   :"NULL",
				"state" :"DORMANT"
			}
		},
		"TASK6":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :10,
				"atr"   :"TA_NULL",
				"pri"   :10,
				"exinf" :"6",
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
				"id"    :11,
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
				"id"    :12,
				"atr"   :"TA_ACT",
				"pri"   :4,
				"exinf" :"2",
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
		}
	}
}

