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
		"TASK2":{
			"Type":"Task",
			"Attributes":
			{
				"prcId" :2,
				"id"    :3,
				"atr"   :"TA_ACT",
				"pri"   :8,
				"exinf" :"2",
				"task"  :"task",
				"stksz" :386,
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
		"CYC_HANDLER":{
			"Type":"CyclicHandler",
			"Attributes":
			{
				"prcIdC" :1,
				"id"    :1,
				"state"    : "DORMANT"
			}
		},
,
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

