$FILE "fmp_mig.res"$
{$NL$
$TAB$"TimeScale" :"us",$NL$
$TAB$"TimeRadix" :10,$NL$
$TAB$"ConvertRules"   :["fmp_mig"],$NL$
$TAB$"VisualizeRules" :["toppers","fmp_mig","fmp_mig_core$+TNUM_PRCID$"],$NL$
$TAB$"ResourceHeaders":["fmp"],$NL$
$TAB$"Resources":$NL$
$TAB${$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
    $TAB$$TAB$"CurrentContext_PRC$prcid$":{$NL$
    $TAB$$TAB$$TAB$"Type":"Context",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"name"    : "PRC$prcid$_LOGTASK$prcid$"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
    $JOINEACH tskid TSK.ORDER_LIST ",\n"$
        $TAB$$TAB$"PRC$prcid$_$tskid$":{$NL$
        $TAB$$TAB$$TAB$"Type":"Task",$NL$
        $TAB$$TAB$$TAB$"Attributes":$NL$
        $TAB$$TAB$$TAB${$NL$
        $TAB$$TAB$$TAB$$TAB$"prcId" :$+prcid$,$NL$
        $TAB$$TAB$$TAB$$TAB$"id"    :$+tskid$,$NL$
        $TAB$$TAB$$TAB$$TAB$"atr"   :"$TSK.TSKATR[tskid]$",$NL$
        $TAB$$TAB$$TAB$$TAB$"pri"   :$+TSK.ITSKPRI[tskid]$,$NL$
        $TAB$$TAB$$TAB$$TAB$"exinf" :"$TSK.EXINF[tskid]$",$NL$
        $TAB$$TAB$$TAB$$TAB$"task"  :"$TSK.TASK[tskid]$",$NL$
        $TAB$$TAB$$TAB$$TAB$"stksz" :$+TSK.STKSZ[tskid]$,$NL$
        $TAB$$TAB$$TAB$$TAB$"stk"   :"NULL",$NL$
        $TAB$$TAB$$TAB$$TAB$"state" :
            $IF TSK.TSKATR[tskid] == TA_ACT && prcid == CLASS_AFFINITY_INI[TSK.CLASS[tskid]]$
                "RUNNABLE"$NL$
            $ELSE$
                $IF prcid == CLASS_AFFINITY_INI[TSK.CLASS[tskid]]$
                    "DORMANT"$NL$
                $ELSE$
                    "NONEXISTENT"$NL$
                $END$
            $END$
        $TAB$$TAB$$TAB$}$NL$
        $TAB$$TAB$}
    $END$
$END$,
$NL$
$JOINEACH inhno INH.ORDER_LIST ",\n"$
    $TAB$$TAB$"INH_$INH.INHNO[inhno]$_$INH.INTHDR[inhno]$":{$NL$
    $TAB$$TAB$$TAB$"Type":"InterruptHandler",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdI" :$CLASS_AFFINITY_INI[INH.CLASS[inhno]]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"id"    :$+INH.INHNO[inhno]-(0x10000)*(CLASS_AFFINITY_INI[INH.CLASS[inhno]])$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH order ISR.ORDER_LIST ",\n"$
    $TAB$$TAB$"ISR_$ISR.INTNO[order]$_$ISR.ISR[order]$_$ISR.EXINF[order]$":{$NL$
    $TAB$$TAB$$TAB$"Type":"InterruptServiceRoutine",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdR" :$CLASS_AFFINITY_INI[ISR.CLASS[order]]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"id"    :$+ISR.INTNO[order]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH cycid CYC.ORDER_LIST ",\n"$
    $TAB$$TAB$"$cycid$":{$NL$
    $TAB$$TAB$$TAB$"Type":"CyclicHandler",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdC" :$CLASS_AFFINITY_INI[CYC.CLASS[cycid]]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"id"    :$+cycid$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH almid ALM.ORDER_LIST ",\n"$
    $TAB$$TAB$"$almid$":{$NL$
    $TAB$$TAB$$TAB$"Type":"AlarmHandler",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdA" :$CLASS_AFFINITY_INI[ALM.CLASS[almid]]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"id"    :$+almid$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH excno EXC.ORDER_LIST ",\n"$
    $TAB$$TAB$"$EXC.EXCNO[excno]$":{$NL$
    $TAB$$TAB$$TAB$"Type":"CPUExceptionHandler",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdE" :$CLASS_AFFINITY_INI[EXC.CLASS[excno]]$,$NL$
    $TAB$$TAB$$TAB$$TAB$"id"    :$+EXC.EXCNO[excno]-(0x10000)*(CLASS_AFFINITY_INI[EXC.CLASS[excno]])$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$,
$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
    $TAB$$TAB$"TASK_TEX_PRC$prcid$":{$NL$
    $TAB$$TAB$$TAB$"Type":"TaskExceptionRoutine",$NL$
    $TAB$$TAB$$TAB$"Attributes":$NL$
    $TAB$$TAB$$TAB${$NL$
    $TAB$$TAB$$TAB$$TAB$"prcIdX" :$prcid$,$NL$
    $TAB$$TAB$$TAB$$TAB$"state"    : "DORMANT"$NL$
    $TAB$$TAB$$TAB$}$NL$
    $TAB$$TAB$}
$END$
$NL$
$TAB$}$NL$
}$NL$
$FILE "kernel_cfg.c"$
