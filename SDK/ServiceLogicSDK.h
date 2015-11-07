typedef int (*INTPROC_charPtr_int)(char * s,int sLen);
typedef int (*INTPROC_int_charPtr)(int n,char * s);
typedef int (*INTPROC_int_charPtr_int)(int n,char * s,int m);
typedef int (*INTPROC_int)(int n);
typedef int (*INTPROC_marklist_constcharPtr)(va_list mark,const char * Format);
typedef int (*INTPROC_charPtr)(char * s);
typedef int (*INTPROC_charPtr_charPtr)(char * s,char * p);
typedef int (*INTPROC_int_charPtr_charPtr)(int Index,char * s,char * p);
typedef int (*INTPROC_int_int_int)(int Index,int nRow,int nCol);
typedef int (*INTPROC_int_int)(int nId,int nVol);
typedef int (*INTPROC_intPtr)(int * a);
typedef int (*INTPROC_charPtr_int_charPtr_charPtr_int)(char *,int,char *,char *,int);
typedef int (*INTPROC_charPtr_int_int_charPtr_int)(char *,int,int,char *,int);
typedef int (*INTPROC_charPtr_int_int_int_charPtr_int)(char *,int,int,int,char *,int);
typedef int (*INTPROC_charPtr_int_int_charPtr_charPtr_int)(char *,int,int,char *,char *,int);
typedef int (*INTPROC_charPtr_int_int_int)(char *,int,int,int);
typedef int (*INTPROC_int_charPtr_charPtr)(int,char *,char *);
typedef int (*INTPROC_intPtr_int)(int *,int);


int * glbAPIFun;

enum
{
    FUNID_PRINTF,
    FUNID_ATOI,
    FUNID_SENDMSGTOSW,
    FUNID_OPENTTS,
    FUNID_READTTS,
    FUNID_CLOSETTS,
    FUNID_OPENWAVEFILE,
    FUNID_READWAVEFILE,
    FUNID_CLOSEWAVEFILE,
    FUNID_CREATEWAVEFILE,
    FUNID_WRITEWAVEFILE,
    FUNID_EXECUTESQLCMD,
    FUNID_EXECUTESQLSELECTCMD,
    FUNID_GETDBRECORDCOLVALUE,
    FUNID_ALLOCATEMEMORY,
    FUNID_FREEMEMORY,
    FUNID_GETSYSTEMTIME,
    FUNID_INVOKENEWSERVICELOGIC,
    FUNID_BROADCASTALLDESK,
    FUNID_SENDFIRSTDESKINHALL,
    FUNID_SENDTODESKINHALLVIANUMBER,
    FUNID_SENDTODESKINHALLVIAAGENT,
    FUNID_SENDSMS,
    FUNID_OPENVOICERECDID,
    FUNID_READVOICERECDID,
    FUNID_CLOSEVOICERECDID,
    FUNID_GENFREQUENCYINALAW,
    FUNID_EXECUTEGLOBALSQLSELECTCMD,
    FUNID_GETGLOBALDBRECORDCOLVALUE,
    FUNID_REGSMSRECVING,
    FUNID_TCP_CONNECT_TO_SERVER,
    FUNID_TCP_CLOSE_CONNECTION,
    FUNID_TCP_START_LISTEN,
    FUNID_TCP_STOP_LISTEN,
    FUNID_TCP_ACCEPT_CONNECTION,
    FUNID_TCP_SEND_DATA,
    FUNID_TCP_RECV_DATA,
    FUNID_TCP_IS_CONNECTED,
    FUNID_GET_ALL_FSMOBJS,
    FUNID_LIMIT,
};

//---------------------------------------------------------------------------
//	定义工作台属性比特
//---------------------------------------------------------------------------
#define STATION_110			0x01
#define STATION_CK			0x02
#define STATION_GPSS			0x04
#define STATION_GPSC			0x08

enum
{
    CALLEDSTATE_IDLE,							// 被叫状态 空闲
    CALLEDSTATE_BUSY,							// 被叫状态 忙
    CALLEDSTATE_NOT_FOUND,						// 被叫状态 空号
    CALLEDSTATE_BLOCKED,						// 被叫状态 阻塞
    CALLEDSTATE_DONTDISTURB,						// 被叫状态 免打扰
    CALLEDSTATE_ABSENCESERVICE,						// 被叫状态 缺席服务
    CALLEDSTATE_UNKOWN=10,						// 被叫状态 正在处理中, 未知
};

enum
{
    SLOTKIND_BYPARTYID,
    SLOTKIND_BYSIGTONEID,
    SLOTKIND_BYDN,
    SLOTKIND_BYTHREEPARTYCONF,
    SLOTKIND_BYMULTIPARTYCONF
};
		

//-----------------------------------------------------------------------------------------
//	端口类型
//-----------------------------------------------------------------------------------------
enum
{
    PORTKINDCODE_NULL,							// 空端口
    PORTKINDCODE_LOCAL_USER,						// 用户端口
    PORTKINDCODE_LOCAL_CO,						// CO 端口
    PORTKINDCODE_LOCAL_EM_DTMF,						// E/M 端口 DTMF
    PORTKINDCODE_LOCAL_EM_MFC,						// E/M 端口 MFC
    PORTKINDCODE_LOCAL_EMPTY,						// 本地空端口

    PORTKINDCODE_RMT_USER,						// 用户端口
    PORTKINDCODE_RMT_CO,						// CO 端口
    PORTKINDCODE_RMT_EM_DTMF,						// E/M 端口 DTMF
    PORTKINDCODE_RMT_EM_MFC,						// E/M 端口 MFC
    PORTKINDCODE_RMT_EMPTY,						// 远端空端口

    PORTKINDCODE_R2,							// 中国一号信令
    PORTKINDCODE_TUP,							// 中国七号信令 TUP
    PORTKINDCODE_ISUP,							// 中国七号信令 ISUP
    PORTKINDCODE_Q931,							// Q.931
    PORTKINDCODE_V5_SLOT,						// V5 的时隙(E1)
    PORTKINDCODE_REMOTE_SLOT,						// 远端端口时隙(E1)
    PORTKINDCODE_HIGHWAY_SLOT,						// 模块间话路
    PORTKINDCODE_E1_EMPTY,						// 未定义的 E1

    PORTKINDCODE_V5_CTL,						// V5 控制端口
    PORTKINDCODE_V5_EMPTY,						// 空 V5 端口

    PORTKINDCODE_TAIHE,							// 泰和
    PORTKINDCODE_WANGE,							// 万格

    PORTKINDCODE_RESOURCE,						// 资源
    PORTKINDCODE_HIGHWAY_CTL,						// 模块间 PCM 控制
    PORTKINDCODE_VOTCP_HIWAY_CTL,					// VoTCP HIGHWAY 控制
    PORTKINDCODE_VOTCP_TRUNK_CTL,					// VoTCP TRUNK 控制
    PORTKINDCODE_VOTCP_PHONE_CTL,					// VoTCP PHONE 控制
    PORTKINDCODE_SIP_PHONE_CTL,						// SIP PHONE 控制
    PORTKINDCODE_VOICENOTE_CTL,						// 录音播放 控制
    PORTKINDCODE_EASYCONF_CTL,						// 简单会议 控制
    PORTKINDCODE_CTIRELAY_CTL,						// CTI 转接(信令转换) 控制
    PORTKINDCODE_DYNAMIC,						// 动态分配

    PORTKINDCODE_LIMIT
};


//-----------------------------------------------------------------------------------------
//	信号音的编码
//-----------------------------------------------------------------------------------------
enum
{
    SIGTONE_DIAL,							// 普通拨号音
    SIGTONE_RINGBACK,							// 回铃音
    SIGTONE_BUSY,							// 忙音
    SIGTONE_CONJEST,							// 拥塞音
    SIGTONE_SPECIALDIAL,						// 特殊拨号音
    SIGTONE_EMPTY,							// 空号音
    SIGTONE_LONGTOLL,							// 长途通知音
    SIGTONE_PROVE,							// 证实音
    SIGTONE_CALLWAIT,							// 呼入待待音
    SIGTONE_SILENCE,							// 静音
    SIGTONE_VOICEPROMPT,						// 语音提示
    SIGTONE_LIMIT							// 信号音的总个数
};

//-------------------------------------------------------------------------------------------
//	交换机(SW)==>网管服务器(NMS)
//-------------------------------------------------------------------------------------------
enum
{
    VOICEPLATFORMCMDCODE_SERVICEISARRIVED=1,				// 业务到达, 用户拨打了该业务
    VOICEPLATFORMCMDCODE_SERVICEISLEAVE,				// 业务结束
    VOICEPLATFORMCMDCODE_HANDSHAKEREQ,					// 握手请求
    VOICEPLATFORMCMDCODE_DTMF_NUMBER,					// DTMF
    VOICEPLATFORMCMDCODE_CALLED_STATE,					//
    VOICEPLATFORMCMDCODE_CALLED_ANSWER,					//
    VOICEPLATFORMCMDCODE_CALLED_BACKRELEASE,					//
    VOICEPLATFORMCMDCODE_CALLED_HOOK_ON,				//
    VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED,				//
    VOICEPLATFORMCMDCODE_PLAYVOICENEEDMOREDATA,				//
    VOICEPLATFORMCMDCODE_RECORDVOICE,					//
    VOICEPLATFORMCMDCODE_RECORDIDSTRING,				// 录音号

    VOICEPLATFORMCMDCODE_REGSMS_ARRIVED=0x400,				//
};

//-------------------------------------------------------------------------------------------
//	网管服务器(NMS)==>交换机
//-------------------------------------------------------------------------------------------
enum
{
    VOICEPLATFORMACKCODE_SERVICEISACCEPTED=1,				// 业务被接受
    VOICEPLATFORMACKCODE_SERVICEISREJECTED,				// 业务被拒绝
    VOICEPLATFORMACKCODE_HANDSHAKEACK,					// 握手证实
    VOICEPLATFORMACKCODE_MAKECALL,					// 呼叫
    VOICEPLATFORMACKCODE_CANCELCALL,					// 中止呼叫
    VOICEPLATFORMACKCODE_BUILDCONNECT,					// 时隙搭接

    VOICEPLATFORMACKCODE_STARTPLAYVOICE,				// 开始播放语音
    VOICEPLATFORMACKCODE_PLAYVOICEDATA,					// 语音数据块
    VOICEPLATFORMACKCODE_PLAYDATAINSW,					// 播放交换机内存已加载的语音
    VOICEPLATFORMACKCODE_STOPPLAYVOICE,					// 停止播放语音

    VOICEPLATFORMACKCODE_STARTRECVDTMF,					// 开始收号
    VOICEPLATFORMACKCODE_STOPRECVDTMF,					// 停止收号

    VOICEPLATFORMACKCODE_STARTRECORDVOICE,				// 开始录音
    VOICEPLATFORMACKCODE_STOPRECORDVOICE,				// 停止录音

    VOICEPLATFORMACKCODE_SERVICEISEND,					// 业务中止
};

//---------------------------------------------------------------------------
//	TCP/IP 报文种别码
//---------------------------------------------------------------------------
enum
{
    TCPIP_MSG_NULL,			// 不用			0
    TCPIP_MSG_PHONE_STATE,		// 汇报话机状态		1
    TCPIP_MSG_ONOFF_STATE,		// 读取上/下岗状态	2
    TCPIP_MSG_QUEUE_TAB,		// 排队信息		3
    TCPIP_MSG_CK_DIGIT,			// CK 报警码		4
    TCPIP_MSG_CONFERENCE_BOOK,		// 会议号码表		5
    TCPIP_MSG_CONFERENCE_STATE,		// 与会者状态		6
    TCPIP_MSG_CHAIRMAN_STATE,		// 主席状态		7
    TCPIP_MSG_TURN_TO_THIRD,		//			8
    TCPIP_MSG_OUTGOING_CALL,		//			9
    TCPIP_MSG_LINKTEST,			//			10
    TCPIP_MSG_SYSRESET,			//			11
    TCPIP_MSG_RASOPROTOCOL,		//			12
    TCPIP_MSG_RECD_RECORD_ID=16,
    TCPIP_MSG_GEN_RECD_DATAFILE,	// 产生 PCM 文件        17
    TCPIP_MSG_OPENFILEFORREAD,		// 以读方式打开文件	18
    TCPIP_MSG_READFILEDATA,		// 读文件内容		19
    TCPIP_MSG_CLOSEFILE,		// 关闭文件		20
    TCPIP_MSG_GEN_RECD_INDEXFILE,	// 产生录音索引文件	21
    TCPIP_MSG_DEL_RECD_RECORD,		// 删除某条录音记录	22
    TCPIP_MSG_GET_RECD_PORT_STATE,	// 取录音端口状态	23
    TCPIP_MSG_SET_RECD_PORT_MASK,	// 置录音端口屏幕码     24
    TCPIP_MSG_GET_BLACKLISTENABLE,	// 取黑名单使能		25
    TCPIP_MSG_SET_BLACKLISTENABLE,	// 置黑名音使能		26
    TCPIP_MSG_SET_CALLINGDIGITS,	// 置主叫号码		27
    TCPIP_MSG_SET_RECDSUPERVISION,	// 置监听状态		28
    TCPIP_MSG_REPORT_VOICEDATA,		// 监听语音数据		29
    TCPIP_MSG_TALKWITHSOMEONEINCONF,	// 与指定的某一与会者通话	30
    TCPIP_MSG_FORCEDISCARDCONF,		// 强制散会		31
    TCPIP_MSG_3PARTYWITHCOBUILD,	// 与 CO 某个端口开三方会议	32
    TCPIP_MSG_3PARTYWITHCODESTROY,	// 与 CO 某个端口三方会议散会	33
    TCPIP_MSG_TRANSLATETHISRECORDID,	// 把某个录音号翻译成文件名和初始位置 34
    TCPIP_MSG_SEEKFILEPOSITION,		// 移动文件指针		35
    TCPIP_MSG_RECDDATASRVCTL,		// 录音数据服务器连接/断开消息	36
    TCPIP_MSG_RECDPORTREPORT,		// 录音端口状态报告	37
    TCPIP_MSG_SET_BLACKLISTITEM,	// 置黑名单号码         38
    TCPIP_MSG_SET_CK1PHONENUMBERITEM,	// 置CK1（110收号）主叫号码  39
    TCPIP_MSG_SET_CK2PHONENUMBERITEM,	// 置CK2（110不收号）主叫号码  40
    TCPIP_MSG_SET_FRIENDPHONENUMBERITEM,// 置友好用户主叫号码  41
    TCPIP_MSG_APPENDONEALARMRECORD,	// 生成一个接警记录    42
    TCPIP_MSG_EXECCOMMAND,		// 执行一条命令  43
    TCPIP_MSG_GET_SYSTEMINFORMATION,	// 取系统信息    44
    TCPIP_MSG_NOTEPCSALARMRECORD,	// 网络派单      45
    TCPIP_MSG_SINGLEAUDIENCECONTROL,	// 单个听从控制 46
    TCPIP_MSG_FETCHLOCALRINGCTLBIT,	// 近端信息台向服务器询问 119 是否允许远端控制警铃     47
    TCPIP_MSG_REPORTLOCALRINGCTLBIT,	// 汇报控制比特 48
    TCPIP_MSG_WRITERINGCONTROLBIT,	// 近端控制向远端台写警铃控制字 49
    TCPIP_MSG_SENDSMSREQ,		// 发送短信请求 50
    TCPIP_MSG_NOTEHOOKONWHILEQUEING,	// 通知排队时挂机 51
    TCPIP_MSG_NOTE3RDCALLEDSTATE,	// 通知第 3 方状态 52
    TCPIP_MSG_SETAUTOENTER3PARTMODE,	// 置自动方式 53
    TCPIP_MSG_SETCURRENTDATEANDTIME,	// 置日期/时间 54
    TCPIP_MSG_SETSVRCURRENTDATEANDTIME,	// 置日期/时间 55
    TCPIP_MSG_ACKFORNOTEPCSALARMRECORD,	// 回执
    TCPIP_MSG_REQFORALLSTATIONSTATE,	// 索要所有接警台的状态 提问
    TCPIP_MSG_ACKFORALLSTATIONSTATE,	// 索要所有接警台的状态 回答
    TCPIP_MSG_PREPOSTFORALLSTATIONSTATE,// 索要所有接警台的状态 回答
    TCPIP_MSG_REFRESHSMSRECORDLIST,	// 刷新短信记录表
    TCPIP_MSG_SETRECORDERPORTSTATE,	// 刷新录音端口状态
    TCPIP_MSG_SETLISTENPRESENTWORD,	// 设置监听标志字
    TCPIP_MSG_PLAYRECORDEDVOICETOCALLER,// 向主叫播放录音
    TCPIP_MSG_GPSPKTARRIVE,		// 从 UDP 上收到一个 GPS 报文
    TCPIP_MSG_SENDGPSPKTREQ,		// 发送GPS报文请求
    TCPIP_MSG_RELOADGPSMSBOOK,		// 重新装入 GPS 的 MS 号码
    TCPIP_MSG_E1BOARDSTATE,		// E1 系统状态
    TCPIP_MSG_MTP3LINKSTATE,		// 七号链路状态
    TCPIP_MSG_PLAYTELDNDIGITS,		// 播放号码
    TCPIP_MSG_STARTPLAYVOICETOPCS,	// 向派出所喊话
    TCPIP_MSG_OPENPLAYERDEVICE,		// 打开播放设备
    TCPIP_MSG_CLOSEPLAYERDEVICE,	// 关闭播放设备
    TCPIP_MSG_VOICEDATATOSTATION,	// 录音数据
    TCPIP_MSG_NOTECK2CALLINGDN,		// CK2 主叫号码
    TCPIP_MSG_HOTQUEUINGPHONE,		// 排队电话号码
    TCPIP_MSG_NOTESLAVEDB,		// 通知备用数据库
    TCPIP_MSG_BUILDMULTYPARTYTALKING,	// 建议多方会议
    TCPIP_MSG_IPPHONEPKT,		// IP Phone 报文
    TCPIP_MSG_GETRECORDIDFULLINFO,	// 取录音号完整信息
    TCPIP_MSG_GETLOCKEDONDTDNLIST,	// 由中继封锁的用户列表
    TCPIP_MSG_PLAYTHISRECDVIAPHONE,	// 用接警话机播放录音
    TCPIP_MSG_GPSLINKTESTING,		// 收到一个 GPS 发来的链路测试报文
    TCPIP_MSG_SETDS300PAIDANSTATE,	// 设置警务平台上单子的状态
    TCPIP_MSG_OPERATION_FEICHENG_JW_DB,	// 操作肥城的警务平台数据库
    TCPIP_MSG_OPERATION_VOICENOTE,	// 进行语音通知控制
    TCPIP_MSG_RECALLSTATION,		// 重新呼叫接警台
    TCPIP_MSG_COMBINEDCALLINFO,		// 一打两振信息
    TCPIP_MSG_ALARMFORRPTHOOKON,	// 催挂消息
    TCPIP_MSG_JINTANLIKE_JWPTINFO,	// 金坛类型的警务对接消息
    TCPIP_MSG_GPSRAWPKTDATAARRIVE,	// GPS 原始数据报文到达
    TCPIP_MSG_GETTTSOFTHISTEXT,		// 把指定的串变成语音文件
    TCPIP_MSG_TTSOFTHISTEXTISDONE,	// TTS 已经生成
    TCPIP_MSG_FETCHTTSSPEACHDATA_REQ,	// 取TTS语音数据
    TCPIP_MSG_FETCHTTSSPEACHDATA_ACK,	// 取TTS语音数据
    TCPIP_MSG_RECDSIM_PHONE_STATE,	// 由录音客户端转交的话机状态汇报话机状态
    TCPIP_MSG_ONEJIEJINGDANISBORND,	// 一张接警单已经生成,需要在屏幕上显示出来
    TCPIP_MSG_SETLOGICALPHONESTATE,	// 设置话机的逻辑状态
    TCPIP_MSG_GEN_ALARMETITEM_REQ,	// 在派出所产生新警单 请求
    TCPIP_MSG_GEN_ALARMETITEM_ACK,	// 在派出所产生新警单 应答
    TCPIP_MSG_ASY_GETPCSNAMELIST_REQ,	// 索要已上岗的派出所的名称列表
    TCPIP_MSG_ASY_GETPCSNAMELIST_ACK,	// 索要已上岗的派出所的名称列表的应答
    TCPIP_MSG_ASY_REFRESH_DIAODU_LIST,	// 更新单位号码表
    TCPIP_MSG_DIAODU_CALLEDSTATE,	// 自动调度时,被叫的状态
    TCPIP_MSG_APPENDALARMCONTENTS,	// 增加报警内容
    TCPIP_MSG_SETBRIEFPROMPTINFO_REQ,	// 设置简要内容, 班长台->服务器
    TCPIP_MSG_SETBRIEFPROMPTINFO_CMD,	// 设置简要内容, 服务器->班长台
    TCPIP_MSG_GPSCARNODETRACKRATIOARRIVE,// 定位率到达
    TCPIP_MSG_FETCHDESKVERION_REQ,	// 取最新版本号,请求
    TCPIP_MSG_FETCHDESKVERION_ACK,	// 取最新版本号,应答
    TCPIP_MSG_SETNEWALARMSETIDNUMBER,	// 设置新生成的警单号
    TCPIP_MSG_SETSENDINGVOICEDATATOME,	// 设置索要本台录音
    TCPIP_MSG_VOICEDATABLOCKFORSAVE,	// 本地要存储的录音数据
    TCPIP_MSG_WRITETOSHENGTING_HUNCHUEN,// 向省厅报告数据(珲春)
    TCPIP_MSG_SETHOTALARMRECORDID,	// 设置刚刚生成的警单号
    TCPIP_MSG_MSPHONELOCATIONINFO,	// 手机定位数据到达
    TCPIP_MSG_GPSCARPHOTOTAKEN,		// 已拍了一张照片
    TCPIP_MSG_GPSCARPHOTOPAGEDATA,	// 照片数据
    TCPIP_MSG_DELETEJUSTBORNALARMRECORD,// 删除刚刚生成的接警记录
    TCPIP_MSG_JS110JWPT_JDINQUEUE,	// 新警单已形成
    TCPIP_MSG_JS110JWPT_SENDTOTIANCHENG,// 向天成公司派单
    TCPIP_MSG_WRITESMSRECORDLIST,	// 请接警台向库写短信单
    TCPIP_MSG_SMSNOTEFORALARM,		// 短信报警消息
    TCPIP_MSG_FETCHSMSNODENAMES_CMD,	// 取短信服务器的名字 命令
    TCPIP_MSG_FETCHSMSNODENAMES_ACK,	// 取短信服务器的名字 结果
    TCPIP_MSG_REASSIGNPHONEZONENAME_CMD,// 重置手机所在区域名
    TCPIP_MSG_DESKINSORLISTENTOPHONE,	// 强插或监听
    TCPIP_MSG_FETCHALLSTATIONIDARRAY_CMD,	// 取已登录的台子号及类型
    TCPIP_MSG_FETCHALLSTATIONIDARRAY_ACK,	// 取已登录的台子号及类型
    TCPIP_MSG_FORCEQUITTOSYSTEM,	// 令客户端强行退出
    TCPIP_MSG_SQ_FETCHLOGINGORMATION,		// 宿迁：取登录信息
    TCPIP_MSG_SMSMSDN_FEEDBACKREG,	// 短信回发台子登记
    TCPIP_MSG_REGSTERREDSMSARRIVED,	// 登记的回发短信到达
    TCPIP_MSG_AUTOSTATISTICJOB_CMD,	// 自动统计命令
    TCPIP_MSG_RELOADSYSCONFIGDATA,	// 重新从库中取配置
    TCPIP_MSG_TRYPINGJINGONTHISJJDBH,	// 试着对此警单评警
    TCPIP_MSG_GETGEOLOCATIONXY,		// 试着对此警定位
    TCPIP_MSG_FKDBHASFILLEDVIAPCS,	// 派出所已填写了反馈单
    TCPIP_MSG_LIYANG_GETCARINFO_REQ,	// 取溧阳GPS车辆注册信息 请求
    TCPIP_MSG_LIYANG_GETCARINFO_ACK,	// 取溧阳GPS车辆注册信息 应答
    TCPIP_MSG_LIYANG_GETCARXY_REQ,	// 取溧阳GPS车辆历史位置 请求
    TCPIP_MSG_LIYANG_GETCARXY_ACK,	// 取溧阳GPS车辆历史位置 请求
    TCPIP_MSG_LYG_FETCHNEXTHOTELSMS_REQ,	// 连云港
    TCPIP_MSG_LYG_FETCHNEXTHOTELSMS_ACK,	// 连云港
    TCPIP_MSG_JINING_WEBACTION_REQ,	// 济宁
    TCPIP_MSG_JINING_WEBACTION_ACK,	// 济宁
    TCPIP_MSG_YINGTAN_EXTERN_CKINFO_RPT,	// 鹰潭
    TCPIP_MSG_YINGTAN_EXTERN_CKINFO_CMD,	// 鹰潭
    TCPIP_MSG_YINGTAN_FETCH_KEYINFOONJJDB_REQ,	// 鹰潭
    TCPIP_MSG_YINGTAN_FETCH_KEYINFOONJJDB_ACK,	// 鹰潭
    TCPIP_MSG_YINGTAN_SET_KEYINFOONJJDB_CMD,	// 鹰潭
    TCPIP_MSG_TIMERSERVICE_REQ,			// 定时服务请求
    TCPIP_MSG_TIMERSERVICE_ACK,			// 定时服务应答
    TCPIP_MSG_DESKRINGINGINFOBROADCAST,			// 接警台振铃消息广播，主要是溧阳接口
    TCPIP_MSG_FETCHSVRINFOMATION_REQ,			// 信息索要请求
    TCPIP_MSG_FETCHSVRINFOMATION_ANS,			// 信息索要请求
    TCPIP_MSG_CSTALINKSTATE,			// CSTA Link State 状态改变了
    TCPIP_MSG_CSTAAGENTSTATE,			// CSTA Agent State 状态改变了
    TCPIP_MSG_JJDINFOSHOWTOLEDSYS,
    TCPIP_MSG_INKFECTHSPECIALDNLIST,			// 引发索要 CK1 CK2 黑名单 友好用户列表
    TCPIP_MSG_LOADSPECIALDNLISTTOSW,			// 引发索要 CK1 CK2 黑名单 友好用户列表
    TCPIP_MSG_CSTAAGENTSTATEANDSTATIONSTATE,
    TCPIP_MSG_PHONE_EXT_STATE,
    TCPIP_MSG_FETCHDATASVREXTNAMES,
    TCPIP_MSG_Q921LINKSTATE,
    TCPIP_MSG_MARKIMPORTANTRECORDID,
    TCPIP_MSG_ANSWERCALLFORCSTA,
    TCPIP_MSG_CSTAAGENTCONTROL_SETBUSYSTATE,
    TCPIP_MSG_CSTAAGENTCONTROL_STATEREPORT,
    TCPIP_MSG_RECDCONTROL_STATEREPORT,
    TCPIP_MSG_CSTAFUNGROUPINFO,
    TCPIP_MSG_NOTETOPCSFORWATCHING,					// 收到派单消息后,向监控台发的通知消息
    TCPIP_MSG_SENDJDTOXIAOFANGVIAUDP_CMD,
    TCPIP_MSG_SENDJDTOXIAOFANGVIAUDP_ACK,
    TCPIP_MSG_SETAGENT_NUMBER,
    TCPIP_MSG_UNANSWEREDLIST,
    TCPIP_MSG_OPERATERKAOQINGINFO,
    TCPIP_MSG_PT_STARTADVSERVICE,
    TCPIP_MSG_PT_LETCALLINGENTVOICEPLATFORM,
    TCPIP_MSG_CALLBILLNODEARRIVED,
    TCPIP_MSG_JJY_ANSWERSPEEDREPORT,
    TCPIP_MSG_CELLPHONE_LOCFAILUREREPORT,
    TCPIP_MSG_FETCH_CELLPHONELOCATEREULT,
    TCPIP_MSG_ASSIGN_CELLPHONELOCATEREULT,
    TCPIP_MSG_FETCH_CARINFORMATION,
    TCPIP_MSG_SETCHUJINGTAIMAPDATA,
    TCPIP_MSG_SETJJDGISXYBYWEBMAP,
    TCPIP_MSG_SETGISDATAFORWEBCLIENT,
    TCPIP_MSG_UNANSWERLISTCTL,
    TCPIP_MSG_HOLDCALLCTL,
    TCPIP_MSG_REMOTEDBOPERATION_EXECITESQLCMD,
    TCPIP_MSG_REMOTEDBOPERATION_SELECT,
    TCPIP_MSG_RELAYTOWEBDESK,						// 接警台消息转发，主要是溧阳接口
    TCPIP_MSG_FETCHALLAGENTINFO,					// 索要所有席位状态数据
    TCPIP_MSG_RECDIDONRECDPORT,						//
    TCPIP_MSG_LIMIT
};


//--------------------------------------------------------------------
//	打/解包器
//--------------------------------------------------------------------
class CCommonParameter
{
    BYTE * m_s;
    int    m_Limit;
    int    m_IsBigEndian;
    int    m_WritePos;								// 打包指针
public:
    int    m_lstBinDataLen;
    int    BindString(char * s,int Len,int IsBigEndian);
    int    IsEOF();
    BYTE   GetBYTE();
    WORD   GetWORD();
    DWORD  GetDWORD();
    float  GetFloat();
    double GetDouble();
    char * GetASCIIZString();
    char * GetBinDataBlock(int Vol);
    char * GetRemainBinBlock(int * Vol);

    int    PutBYTE(BYTE c);
    int    PutWORD(WORD x);
    int    PutDWORD(DWORD x);
    int    PutASCIIZString(const char * s);
    int    PutBinDataBlock(const char * s,int Len);
    int    PutBinDataFillZeroBlock(const char * s,int Len,int WidthLen);
    char * GetCurrentWriteBuf();
    int    GetCurrentWritePos();
    char * GetPackedPacket(int * Len);
};

//----------------------------------------------------------------------------------
//	一天内的秒数
//----------------------------------------------------------------------------------
#define NSECONDSINDAY   (24*3600)
#define glbIsLeapYear(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

//----------------------------------------------------------------------------------
//	时间差
//----------------------------------------------------------------------------------
struct CTimeDet
{
    int m_IsNeg;								// 0 非负   1 负
    int m_Days;									// 天数绝对值
    int m_Seconds;								// 天内秒数绝对值
};

//----------------------------------------------------------------------------------
//	日期/时间结构
//----------------------------------------------------------------------------------
struct CDateAndTime
{
    int  m_Year;
    BYTE m_Month;
    BYTE m_Day;
    BYTE m_DayOfWeek;
    BYTE m_Hour;
    BYTE m_Minute;
    BYTE m_Second;
    WORD m_Milisecond;

    int    IsLeapYear();							// 判断是不是闰年   1 是  0 否
    char * FormASCIIString(char * s);						// 把日期变成 yyyy/mm/dd hh:mm:ss.mmmm 格式
    int    SetValueByASCIIString(char * s);					// 把yyyy/mm/dd hh:mm:ss.mmmm 格式的时间置到结构内
    int    GetAbsDay();								// 计算从 1/1/1 到 指定日期的天数
    int    SetAbsDay(int nDay);							// 根据1/1/1 到 指定日期的天数置结构内的成员
    int    GetSecondsInDay();							// 计算天内秒数
    int    SetSecondsInDay(int nSeconds);					// 根据天内秒数置时 分 秒
    int    CompareTo(CDateAndTime * pDst);					// 比较两个时间的先后
    int    GetDetTo(CDateAndTime * pDst,CTimeDet * pDet);			// 计算两个时间的差
    int    AddDet(CTimeDet * pDet);						// 时间前移
    int    SubDet(CTimeDet * pDet);						// 时间后移
    int    AddDaysAndSeconds(int nDays,int nSeconds);				// 时间前移
    int    SubDaysAndSeconds(int nDays,int nSeconds);				// 时间后移
    int    GetDayInWeek();							// 计算星期 0 星期日  1-6 星期 1-6
    int    AdjustTime();
    int    ClearTime();
    int    IsValideDate();
    int    ToIntArray(int a[]);
    int    FromIntArray(int a[]);
    int    GetHash();
    char * FormOralceDate(char * s);
};

//---------------------------------------------------------------------------
//	配置文件控制
//---------------------------------------------------------------------------
struct CCfgData
{
    CCfgData();
    ~CCfgData();
    int     ReadFromFile(char * sFilename);					// 从文件读取配置数据
    int     WriteToFile(char * sFilename);					// 写入配置文件
    char *  GetValue(LPCSTR sTagName);						// 取配置值
    int     SetValue(LPCSTR sTagName,LPCSTR sTagValue);				// 置配置值
    int     ClearAllData();							// 清除所有配置值
protected:
    char *  StoreString(const char * s);
    char * m_Tagnames[256];
    char * m_Tagvalues[256];
    int    m_Count;

    char   m_Pool[0x4000];
    int    m_AlcPos;
};

char * glbDelAllNonDNDigits(char * s)
{
    int i,n;
    BYTE c;

    n=0;
    for (i=0;c=s[i];i++)
    if (c=='*' || c=='#' || (c>='0' && c<='9'))
    {
	s[n]=c;
	n++;
    }
    s[n]=0;
    return s;
}

//---------------------------------------------------------------------------------------
//	把一个串变成一个整数数组
//	返回取到的元素个数
//---------------------------------------------------------------------------------------
int glbGetIntegerValueByASCIIString(int a[],int nLimit,const char * s)
{
    int           i,State,n,nBase,d;
    unsigned char c;

    if (s==NULL) return 0;							// 如果是空串，返回 0
    State=0;									// 状态 0 过滤空格
    n=0;									// 整数个数开始为 0
    for (i=0;c=s[i];i++)
    switch(State)
    {
    case 0:									// 正在过滤空格（非数字）
	if (c>='0' && c<='9')							// 遇到数字
	{
	    a[n]=c-'0';
	    if (n<nLimit) n++;							// 数字个数加 1
	    State=1;								// 进入状态 1
	    if (s[i+1]=='x' || s[i+1]=='X')					// 以 0x 开头是 16 进制
	    {
		nBase=16;
		i++;
	    }
	    else
	    {
		nBase=10;							// 否则是 10 进制
	    }
	}
	break;

    case 1:									// 正在读数字
	if (c>='0' && c<='9')							// 若仍然是数字
	{
	    d=c-'0';								// 计算二进制值
	}
	else
	if (nBase!=16)
	{
	    d=-1;
	}
	else
	if (c>='A' && c<='F')
	{
	    d=c-'A'+10;
	}
	else
	if (c>='a' && c<='f')
	{
	    d=c-'a'+10;
	}
	else d=-1;

	if (d>=0)								// 如果有值
	{
	    a[n-1]=a[n-1]*nBase+d;						// 计入数组
	}
	else State=0;								// 如果遇到非数字，回到状态 0
	break;
    }
    return n;									// 返回整数个数
}

//-----------------------------------------------------------------------------------------------------
//	取指定年份指定月份的天数
//-----------------------------------------------------------------------------------------------------
int glbGetDaysInMonth(int nYear,int Month)
{
    switch(Month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
	return 31;

    case 2:
	if (glbIsLeapYear(nYear)) return 29;
	return 28;
    }

    return 30;
}

//---------------------------------------------------------------------------
//	准备解码
//---------------------------------------------------------------------------
int CCommonParameter::BindString(char * s,int Len,int IsBigEndian)
{
    m_s=(BYTE *)s;								// 记录传入的首地址
    m_Limit=Len;								// 长度
    m_IsBigEndian=IsBigEndian;							// 双字格式,低位在先或高位在先
    m_WritePos=0;								// 写指针置 0
    return 0;
}

//---------------------------------------------------------------------------
//	是否遇到末尾
//---------------------------------------------------------------------------
int CCommonParameter::IsEOF()
{
    return (m_Limit<1) ? 1 : 0;							// Limit 为0,表示遇到末尾
}

//---------------------------------------------------------------------------
//	取一个字节
//---------------------------------------------------------------------------
BYTE CCommonParameter::GetBYTE()
{
    BYTE c=0;

    if (m_Limit>=1)								// 若还剩下至少一个字节
    {
	c=m_s[0];								// 取它
	m_Limit--;
	m_s++;
    }
    return c;
}

//---------------------------------------------------------------------------
//	取一个字 16 比特
//---------------------------------------------------------------------------
WORD CCommonParameter::GetWORD()
{
    WORD x=0;

    if (m_Limit>=2)								// 若还剩下至少二个字节
    {
	if (m_IsBigEndian)							// 若是大端模式
	{
	    x=(m_s[0]<<8);							// 高位在先
	    x+=m_s[1];
	}
	else									// 若是小端模式
	{
	    x=(m_s[1]<<8);							// 高位在后
	    x+=m_s[0];
	}
	m_s+=2;
	m_Limit-=2;
    }
    return x;
}

//---------------------------------------------------------------------------
//	取一个双字 32 比特
//---------------------------------------------------------------------------
DWORD CCommonParameter::GetDWORD()
{
    DWORD x=0;

    if (m_Limit>=4)								// 若至少还剩 4 个字节
    {
	if (m_IsBigEndian)							// 若是大端模式
	{
	    x=(m_s[0]<<24);							// 高位在先
	    x+=(m_s[1]<<16);
	    x+=(m_s[2]<<8);
	    x+=m_s[3];
	}
	else									// 若是小端模式
	{
	    x=(m_s[3]<<24);							// 高位在后
	    x+=(m_s[2]<<16);
	    x+=(m_s[1]<<8);
	    x+=m_s[0];
	}
	m_s+=4;
	m_Limit-=4;
    }
    return x;
}

//---------------------------------------------------------------------------
//	取一个单精度浮点
//---------------------------------------------------------------------------
float CCommonParameter::GetFloat()
{
    float xValue;
    BYTE * Dst=NULL;
    int i;

    if (m_Limit>=sizeof(xValue))
    {
	Dst=(BYTE *)&xValue;
	for (i=0;i<sizeof(xValue);i++) Dst[i]=m_s[i];
	m_s+=sizeof(xValue);
	m_Limit-=sizeof(xValue);
    }
    return (Dst==NULL) ? 0 : xValue;
}

//---------------------------------------------------------------------------
//	取一个双精度数
//---------------------------------------------------------------------------
double CCommonParameter::GetDouble()
{
    double xValue;
    BYTE * Dst=NULL;
    int i;

    if (m_Limit>=sizeof(xValue))
    {
	Dst=(BYTE *)&xValue;
	for (i=0;i<sizeof(xValue);i++) Dst[i]=m_s[i];
	m_s+=sizeof(xValue);
	m_Limit-=sizeof(xValue);
    }
    return (Dst==NULL) ? 0 : xValue;
}

//---------------------------------------------------------------------------
//	取一个 ASCIIZ 串
//---------------------------------------------------------------------------
char * CCommonParameter::GetASCIIZString()
{
    char * s="";
    int k;

    if (m_Limit>=1)								// 若还剩至少一个字节
    {
	s=(char *)m_s;								// 让 s 指向当前内容
	k=strlen(s)+1;								// 计算串长,含尾部的 0
	m_s+=k;									// 跳过该 ASCIIZ 串
	m_Limit-=k;
    }
    return s;									// 返回取到的串
}

//---------------------------------------------------------------------------
//	取一个二进制字节组
//---------------------------------------------------------------------------
char * CCommonParameter::GetBinDataBlock(int Vol)
{
    char * s="";

    if (Vol>m_Limit)
    {
	Vol=m_Limit;
    }
    s=(char *)m_s;
    m_s+=Vol;
    m_Limit-=Vol;

    m_lstBinDataLen=Vol;
    return s;
}

//---------------------------------------------------------------------------
//	取剩下的字节
//---------------------------------------------------------------------------
char * CCommonParameter::GetRemainBinBlock(int * Vol)
{
    if (Vol) Vol[0]=m_Limit;							// 若要返回剩下的字节数,就置回去
    return (char *)m_s;								// 返回地址
}

//---------------------------------------------------------------------------
//	取打包之后的内容
//---------------------------------------------------------------------------
char * CCommonParameter::GetPackedPacket(int * Len)
{
    if (Len) *Len=m_WritePos;							// 若要返回串长,就返回
    return (char *)m_s;								// 返回包体地址
}

//---------------------------------------------------------------------------
//	返回当前打包地址
//---------------------------------------------------------------------------
char * CCommonParameter::GetCurrentWriteBuf()
{
    return (char *)m_s+m_WritePos;
}

//---------------------------------------------------------------------------
//	打一个字节
//---------------------------------------------------------------------------
int CCommonParameter::PutBYTE(BYTE c)
{
    if (m_WritePos<m_Limit)							// 若没有越界
    {
	m_s[m_WritePos]=c;							// 写入
	m_WritePos++;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	打入一个字 16 比特
//---------------------------------------------------------------------------
int CCommonParameter::PutWORD(WORD x)
{
    if (m_Limit-m_WritePos>=2)							// 至少有 2 个空格
    {
	if (m_IsBigEndian)							// 若是大端
	{
	    PutBYTE((BYTE)(x>>8));						// 先放高位
	    PutBYTE((BYTE)x);
	}
	else									// 若是小端
	{
	    PutBYTE((BYTE)x);							// 先放低位
	    PutBYTE((BYTE)(x>>8));
	}
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	打入一个双字 32 比特
//---------------------------------------------------------------------------
int CCommonParameter::PutDWORD(DWORD x)
{
    if (m_Limit-m_WritePos>=4)							// 至少有 4 个空格
    {
	if (m_IsBigEndian)							// 若是大端模式
	{
	    PutBYTE((BYTE)(x>>24));						// 先打入最高位
	    PutBYTE((BYTE)(x>>16));
	    PutBYTE((BYTE)(x>>8));
	    PutBYTE((BYTE)x);
	}
	else									// 若是小端
	{
	    PutBYTE((BYTE)x);							// 先打入最低位
	    PutBYTE((BYTE)(x>>8));
	    PutBYTE((BYTE)(x>>16));
	    PutBYTE((BYTE)(x>>24));
	}
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	打入一个 ASCII 串
//---------------------------------------------------------------------------
int CCommonParameter::PutASCIIZString(const char * s)
{
    return (s==NULL) ? PutBYTE(0) : PutBinDataBlock(s,strlen(s)+1);					// 连最后的 0 也打入
}

//---------------------------------------------------------------------------
//	打入一个字节组
//---------------------------------------------------------------------------
int CCommonParameter::PutBinDataBlock(const char * s,int Len)
{
    if (Len>m_Limit-m_WritePos)
    {
	Len=m_Limit-m_WritePos;
    }
    if (Len>0)// && m_WritePos+Len<=m_Limit)					// 若组不空,且能打得下
    {
	memcpy(m_s+m_WritePos,s,Len);						// 整体写入
	m_WritePos+=Len;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	把 s 中 Len 个字节打入,占用 WidthLen 字节,以 0 补充
//---------------------------------------------------------------------------
int CCommonParameter::PutBinDataFillZeroBlock(const char * s,int Len,int WidthLen)
{
    int k;

    if (m_WritePos+WidthLen<=m_Limit)						// 若能放得下
    {
	if (Len<0) Len=strlen(s);						// Len 小于 0,表示 s 是 ASCIIZ 串
	memcpy(m_s+m_WritePos,s,Len);						// 整体拷入
	k=WidthLen-Len;								// 计算右侧的空格数
	if (k>0) memset(m_s+m_WritePos+Len,0,k);				// 若有,则补 0
	m_WritePos+=WidthLen;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	取当前打包指针
//---------------------------------------------------------------------------
int CCommonParameter::GetCurrentWritePos()
{
    return m_WritePos;
}

//-----------------------------------------------------------------------------------------------------
//	判断是不是闰年
//	返回 1 是
//	返回 0 否
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::IsLeapYear()
{
    return glbIsLeapYear(m_Year);
}

//-----------------------------------------------------------------------------------------------------
//	把时间变成 yyyy/mm/dd hh:mm:ss.xxx 格式
//-----------------------------------------------------------------------------------------------------
char * CDateAndTime::FormASCIIString(char * s)
{
    sprintf(s,"%d/%02d/%02d %02d:%02d:%02d.%03d",
	m_Year,m_Month,m_Day,m_Hour,m_Minute,m_Second,m_Milisecond);
    return s;
}

//-----------------------------------------------------------------------------------------------------
//	把 yyyy/mm/dd hh:mm:ss.xxx 格式的时间写入结构
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SetValueByASCIIString(char * s)
{
    int a[8];
    int n;

    n=glbGetIntegerValueByASCIIString(a,8,s);					// 把数写入数组
    m_Year=(n>=1) ? a[0] : 0;							// 写入结构
    m_Month=(n>=2) ? a[1] : 0;
    m_Day=(n>=3) ? a[2] : 0;
    m_Hour=(n>=4) ? a[3] : 0;
    m_Minute=(n>=5) ? a[4] : 0;
    m_Second=(n>=6) ? a[5] : 0;
    m_Milisecond=(n>=7) ? a[6] : 0;
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	计算从 0001/1/1 到该类指定日期的天数
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetAbsDay()
{
    int y=m_Year-1;								// 前一年
    int Days=y/4-y/100+y/400+y*365;						// 从 1/1/1 到 y/12/31 的天数
    int i;

    for (i=1;i<m_Month && i<12;i++) Days+=glbGetDaysInMonth(m_Year,i);		// 把月前的天数加进来
    return Days+m_Day;
}

//-----------------------------------------------------------------------------------------------------
//	根据与 0001/1/1 的相对天数置日期
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SetAbsDay(int nDay)
{
    int y,x;

    m_Month=1;
    m_Day=1;
    for(y=nDay/365+2;y>0;y--)							// nDay/365+2 是年的估计值
    {
	m_Year=y;								// 从 y/1/1 开始验证
	x=GetAbsDay();								// 计算 y/1/1 的绝对天数
	if (nDay>=x) break;							// 如果 nDay 在 [y/1/1 , 无穷) 当中，退出循环
    }
    m_Day+=nDay-x;								// 计算 m_Day
    while (m_Day>(y=glbGetDaysInMonth(m_Year,m_Month)))				// 若 m_Day 太大
    {
	m_Day-=y;								// 后移一个月
	m_Month++;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	计算天内秒数
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetSecondsInDay()
{
    return m_Hour*3600+m_Minute*60+m_Second;
}

//-----------------------------------------------------------------------------------------------------
//	根据天内秒数置 时 分 秒
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SetSecondsInDay(int nSeconds)
{
    m_Hour=nSeconds/3600;
    nSeconds-=m_Hour*3600;

    m_Minute=nSeconds/60;
    m_Second=nSeconds-m_Minute*60;
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	时间比较
//	返回 -1 this 小
//	返回  0 相等
//	返回  1 this 大
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::CompareTo(CDateAndTime * pDst)
{
    if (m_Year<pDst->m_Year) return -1;
    if (m_Year>pDst->m_Year) return  1;

    if (m_Month<pDst->m_Month) return -1;
    if (m_Month>pDst->m_Month) return  1;

    if (m_Day<pDst->m_Day) return -1;
    if (m_Day>pDst->m_Day) return  1;

    if (m_Hour<pDst->m_Hour) return -1;
    if (m_Hour>pDst->m_Hour) return  1;

    if (m_Minute<pDst->m_Minute) return -1;
    if (m_Minute>pDst->m_Minute) return  1;

    if (m_Second<pDst->m_Second) return -1;
    if (m_Second>pDst->m_Second) return  1;

    if (m_Milisecond<pDst->m_Milisecond) return -1;
    if (m_Milisecond>pDst->m_Milisecond) return  1;

    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	计算时间差,即 this-pDst
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetDetTo(CDateAndTime * pDst,CTimeDet * pDet)
{
    int x=GetAbsDay();
    int a=GetSecondsInDay();
    int y=pDst->GetAbsDay();
    int b=pDst->GetSecondsInDay();

    pDet->m_IsNeg=0;
    pDet->m_Days=0;
    pDet->m_Seconds=0;
    if (x==y)									// 天数相等
    {
	if (a>=b) pDet->m_Seconds=a-b;						// 计算天内秒差
	else
	{
	    pDet->m_IsNeg=1;
	    pDet->m_Seconds=b-a;
	}
	return 0;								// 返回
    }
    if (x<y)									// 如果 this 小
    {
	int z;

	z=x;									// 把 this 与 pDst 对换
	x=y;
	y=z;

	z=a;
	a=b;
	b=z;

	pDet->m_IsNeg=1;							// 是负数
    }

    if (a<b)									// 如果被减数天内秒小
    {
	x--;									// 借一天
	a+=NSECONDSINDAY;
    }
    pDet->m_Days=x-y;								// 计算天数差
    pDet->m_Seconds=a-b;							// 计算天内秒差
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	加上时间差
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AddDet(CTimeDet * pDet)
{
    int Days;
    int Seconds;

    if (pDet->m_Days==0 && pDet->m_Seconds==0) return 0;			// 如果时间差为 0，直接返回
    if (pDet->m_Seconds>=NSECONDSINDAY)						// 若天内秒数太大
    {
	pDet->m_Days+=pDet->m_Seconds/NSECONDSINDAY;				// 换算到天数上
	pDet->m_Seconds %= NSECONDSINDAY;
    }
    Seconds=GetSecondsInDay();							// 计算天内秒数
    if (pDet->m_IsNeg) Seconds-=pDet->m_Seconds;				// 调整天内秒数
    else Seconds+=pDet->m_Seconds;
    
    if (pDet->m_Days==0 && Seconds>=0 && Seconds<NSECONDSINDAY)			// 如果不需要调整天
    {
	return SetSecondsInDay(Seconds);					// 直接调整时分秒
    }

    Days=GetAbsDay();								// 取绝对天数
    if (pDet->m_IsNeg)
    {
	Days-=pDet->m_Days;							// 调整绝对天数
    }
    else
    {
	Days+=pDet->m_Days;
    }

    if (Seconds<0)								// 如果天内秒数小于 0
    {
	Seconds+=NSECONDSINDAY;							// 借一天
	Days--;
    }

    if (Seconds>=NSECONDSINDAY)							// 如果天内秒数太大
    {
	Days+=Seconds/NSECONDSINDAY;						// 把天加加到天上
	Seconds %= NSECONDSINDAY;
    }
    SetAbsDay(Days);								// 设置年月日
    SetSecondsInDay(Seconds);							// 设置时分秒
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	减掉时间差
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SubDet(CTimeDet * pDet)
{
    CTimeDet p=pDet[0];

    if (p.m_IsNeg) p.m_IsNeg=0;							// 变换符号
    else p.m_IsNeg=1;

    return AddDet(&p);								// 加上时间差
}

//-----------------------------------------------------------------------------------------------------
//	加上时间差
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AddDaysAndSeconds(int nDays,int nSeconds)
{
    CTimeDet p;

    p.m_IsNeg=0;								// 构造一个正时间差
    p.m_Days=nDays;
    p.m_Seconds=nSeconds;
    return AddDet(&p);								// 加上时间差
}

//-----------------------------------------------------------------------------------------------------
//	减掉时间差
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SubDaysAndSeconds(int nDays,int nSeconds)
{
    CTimeDet p;

    p.m_IsNeg=1;								// 构造一个负时间差
    p.m_Days=nDays;
    p.m_Seconds=nSeconds;
    return AddDet(&p);								// 加上时间差
}

//-----------------------------------------------------------------------------------------------------
//	计算星期
//	0 星期天
//	1 星期一
//	6 星期六
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetDayInWeek()
{
    int nDays=GetAbsDay();							// 计算绝对天数

    return (nDays+0) % 7;							// 返回星期
}

//-----------------------------------------------------------------------------------------------------
//	调整时间
//	返回 0 表示没有调整
//	返回 1 表示调整
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AdjustTime()
{
    if (m_Milisecond<1000) return 0;						// 如果毫秒部分不到 1000, 就不用调整
    m_Milisecond-=1000;								// 毫秒部分减 1000
    m_Second++;									// 秒加 1
    if (m_Second<60) return 0;							// 不到 60, 也返回
    m_Second=0;									// 秒置 0
    m_Minute++;									// 分加 1
    if (m_Minute<60) return 0;							// 分不到 60, 也返回
    m_Minute=0;									// 分置 0
    m_Hour++;									// 小时加 1
    if (m_Hour<24) return 0;							// 小时不到 24,返回
    m_Hour=0;									// 小时置 0
    m_Day++;									// 天加 1
    m_DayOfWeek++;								// 星期加 1
    if (m_DayOfWeek>=7) m_DayOfWeek=0;						// 星期的有效范围是 0-6
    if (m_Day<=glbGetDaysInMonth(m_Year,m_Month)) return 0;			// 如果 天 不超过该月的天数,也返回
    m_Day=1;									// 天从 1 开始
    m_Month++;									// 月份加 1
    if (m_Month<=12) return 0;							// 月份不到 12 也返回
    m_Month=1;									// 从 1 月份开始
    m_Year++;									// 年加 1
    return 0;
}

int CDateAndTime::ClearTime()
{
    m_Year=0;
    m_Month=0;
    m_Day=0;
    m_DayOfWeek=0;
    m_Hour=0;
    m_Minute=0;
    m_Second=0;
    m_Milisecond=0;
    return 0;
}

int CDateAndTime::IsValideDate()
{
    if (m_Month<1 || m_Month>12) return 0;
    if (m_Day<1 || m_Day>31) return 0;
    if (m_Hour<0 || m_Hour>23) return 0;
    if (m_Minute<0 || m_Minute>59) return 0;
    if (m_Second<0 || m_Second>59) return 0;
    return 1;
}

int CDateAndTime::ToIntArray(int a[])
{
    a[0]=m_Year;
    a[1]=m_Month;
    a[2]=m_Day;
    a[3]=m_DayOfWeek;
    a[4]=m_Hour;
    a[5]=m_Minute;
    a[6]=m_Second;
    a[7]=m_Milisecond;
    return 0;
}

int CDateAndTime::FromIntArray(int a[])
{
    m_Year=a[0];
    m_Month=a[1];
    m_Day=a[2];
    m_DayOfWeek=GetDayInWeek();
    m_Hour=a[4];
    m_Minute=a[5];
    m_Second=a[6];
    m_Milisecond=a[7];
    return 0;
}

int CDateAndTime::GetHash()
{
    return m_Year+m_Month+m_Day+m_DayOfWeek+m_Hour+m_Minute+m_Second+m_Milisecond;
}

char * CDateAndTime::FormOralceDate(char * s)
{
    sprintf(s,"to_date('%d-%d-%d %02d:%02d:%02d','yyyy-mm-dd hh24:mi:ss')",
	m_Year,
	m_Month,
	m_Day,
	m_Hour,
	m_Minute,
	m_Second);
    return s;
}


//----------------------------------------------------------------------------------------------------
//	配置文件控制构造
//----------------------------------------------------------------------------------------------------
CCfgData::CCfgData()
{
    ClearAllData();								// 配置项目个数为 0
}

//----------------------------------------------------------------------------------------------------
//	配置文件控制析构
//----------------------------------------------------------------------------------------------------
CCfgData::~CCfgData()
{
    ClearAllData();								// 清除所有配置项目
}

//----------------------------------------------------------------------------------------------------
//	把一串的前导空格和后续空格删除
//----------------------------------------------------------------------------------------------------
char * glbPackString(char * s)
{
    int i;
    BYTE c;

    for (i=strlen(s)-1;i>=0;i--)						// 删除后续空格
    if ((BYTE)s[i]<=' ') s[i]=0;
    else break;

    for (i=0;c=s[i];i++)							// 删除前导空格
    if (c>' ') break;

    return &s[i];
}

//----------------------------------------------------------------------------------------------------
//	从文件读取配置数据
//	原有的配置不清除
//----------------------------------------------------------------------------------------------------
int CCfgData::ReadFromFile(char * sFilename)
{
    FILE * fd;
    char sBuffer[0x1000];
    int i;
    BYTE c;

    fd=fopen(sFilename,"r");							// 打开文件
    if (fd==NULL)
    {
	return -1;								// 打开失败,返回 -1
    }
    while (fgets(sBuffer,sizeof(sBuffer),fd))					// 从文件读一行
    {
	for (i=0;c=sBuffer[i];i++)						// 在该行中寻找首次出现的 '='
	if (c=='=')
	{
	    sBuffer[i]=0;
	    SetValue(glbPackString(&sBuffer[0]),glbPackString(&sBuffer[i+1]));	// 存储该项目
	    break;
	}
    }
    fclose(fd);									// 关闭文件
    return 0;
}

//----------------------------------------------------------------------------------------------------
//	把配置数据写入文件
//----------------------------------------------------------------------------------------------------
int CCfgData::WriteToFile(char * sFilename)
{
    FILE * fd;
    int i;

    fd=fopen(sFilename,"w");
    if (fd)
    {
	for (i=0;i<m_Count;i++)
	{
	    fprintf(fd,"%s=%s\n",m_Tagnames[i],m_Tagvalues[i]);
	}
	fclose(fd);
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------
//	取指定的值
//	如果不存在,返回 NULL
//----------------------------------------------------------------------------------------------------
char * CCfgData::GetValue(LPCSTR sTagName)
{
    int i;

    for (i=0;i<m_Count;i++)
    if (strcmp(m_Tagnames[i],sTagName)==0)
    {
	return m_Tagvalues[i];
    }
    return NULL;
}

char * CCfgData::StoreString(const char * s)
{
    if (s==NULL)
    {
	return NULL;
    }
    int n=strlen(s);

    if (n+m_AlcPos>=sizeof(m_Pool))
    {
	return NULL;
    }
    char * Buf=&m_Pool[m_AlcPos];
    memcpy(Buf,s,n+1);
    m_AlcPos+=n+1;
    return Buf;
}

//----------------------------------------------------------------------------------------------------
//	置值
//----------------------------------------------------------------------------------------------------
int CCfgData::SetValue(LPCSTR sTagName,LPCSTR sTagValue)
{
    int i;

    for (i=0;i<m_Count;i++)
    if (strcmp(m_Tagnames[i],sTagName)==0)					// 如果该项已存在
    {
//	free(m_Tagvalues[i]);							// 删除老值
	m_Tagvalues[i]=StoreString(sTagValue);					// 存入新值
	return i;
    }
    i=m_Count;									// 如果是新项
    m_Count++;
    m_Tagnames[i]=StoreString(sTagName);					// 名字
    m_Tagvalues[i]=StoreString(sTagValue);					// 值都要存储
    return i;
}

//----------------------------------------------------------------------------------------------------
//	清除所有的项目
//----------------------------------------------------------------------------------------------------
int CCfgData::ClearAllData()
{
    m_Count=0;
    m_AlcPos=0;

    return 0;
}



extern int OnServiceModuleLoaded();
extern int OnServiceModuleUnLoaded();

int glbServiceLogicFun_OnDLLLoaded(int APIFun[],int n)
{
    glbAPIFun=APIFun;

    OnServiceModuleLoaded();
    return 0;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch(ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	break;

    case DLL_THREAD_ATTACH:
	break;

    case DLL_THREAD_DETACH:
	OnServiceModuleUnLoaded();
	break;

    case DLL_PROCESS_DETACH:
	break;
    }

    return TRUE;
}

//----------------------------------------------------------------------------------------------
//	把一个报文的尾部加上 0D
//	中间要进行 0D==>0E 02
//		   0E==>0E 01
//                 变换
//	返回含 0D 的长度
//----------------------------------------------------------------------------------------------
int glbEncloseToPkt(char * s,int sLen)
{
    int i,det,j;

    det=0;
    for (i=0;i<sLen;i++)
    if (s[i]==0x0d || s[i]==0x0e) det++;
    if (det>0)
    {
	for (i=sLen-1,j=i+det;i>=0 && i!=j;i--)
	if (s[i]==0x0d || s[i]==0x0e)
	{
	    s[j]=(s[i]==0x0d) ? 0x02 : 0x01;
	    j--;
	    s[j]=0x0e;
	    j--;
	}
	else
	{
	    s[j]=s[i];
	    j--;
	}
	sLen+=det;
    }
    s[sLen]=0x0d;
    return sLen+1;
}

//----------------------------------------------------------------------------------------------
//	把报文中 0E 02==>0D
//		 0E 01==>0E
//	返回变换后的长度
//----------------------------------------------------------------------------------------------
int glbDecloseFromPkt(char * s,int sLen)
{
    int i,State,j;
    BYTE c;

    j=0;
    State=0;
    for (i=0;i<sLen;i++)
    {
	c=s[i];
	switch(State)
	{
	case 0:
	    if (c==0x0e) State=1;
	    else s[j++]=c;
	    break;

	case 1:
	    s[j]=(c==0x01) ? 0x0e : 0x0d;
	    j++;
	    State=0;
	    break;
	}
    }
    return j;
}

int subCommonPack(int IsBigEndian,const char * Format,va_list marker,char * ss,int ssLen,va_list * retValist)
{
    CCommonParameter z;
    BYTE             c;
    DWORD            x,n,pktLen;
    char * ascII;

    if (Format==NULL) return 0;
    if (ss) z.BindString(ss,ssLen,IsBigEndian);
    pktLen=0;
    while (c=*Format++)
    switch(c)
    {
    case 'D':
    case 'd':
	x=va_arg( marker, int);
	if (ss)
	    z.PutDWORD(x);
	else
	    pktLen+=sizeof(int);
	break;

    case 'W':
    case 'w':
	x=va_arg( marker, short);
	if (ss)
	    z.PutWORD((WORD)x);
	else
	    pktLen+=sizeof(short);
	break;

    case 'B':
    case 'b':
	x=va_arg( marker, char);
	if (ss)
	    z.PutBYTE((BYTE)x);
	else
	    pktLen+=sizeof(char);
	break;

    case 'S':
    case 's':
	n=va_arg( marker, int);
	ascII=va_arg( marker, char *);
	if (ss)
	    z.PutBinDataBlock(ascII,n);
	else
	    pktLen+=n;
	break;

    case 'A':
    case 'a':
	ascII=va_arg( marker, char *);
	if (ss)
	    z.PutASCIIZString(ascII);
	else
	    pktLen+=strlen(ascII)+1;
	break;
    }
    if (retValist)
    {
	*retValist=marker;
    }
    return (ss!=NULL) ? z.GetCurrentWritePos() : pktLen;
}

int glbPrintf(const char * Format,...)
{
    va_list marker;
    INTPROC_marklist_constcharPtr p;

    va_start(marker,Format);							// 从第一个参数开始
    p=(INTPROC_marklist_constcharPtr)glbAPIFun[FUNID_PRINTF];
    (*p)(marker,Format);
    va_end(marker);

    return 0;
}

int glbAtoi(char * s)
{
    INTPROC_charPtr p;

    p=(INTPROC_charPtr)glbAPIFun[FUNID_ATOI];
    return (*p)(s);
}

int glbCommonPackAndSend(const char * Format,...)
{
    va_list marker;
    int m;
    char ss[0x4000];
    INTPROC_charPtr_int p;

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int)glbAPIFun[FUNID_SENDMSGTOSW];
    return (*p)(ss,m);
}

int glbAcceptService()
{
    return glbCommonPackAndSend("BD",
	VOICEPLATFORMACKCODE_SERVICEISACCEPTED,
	0);
}

int glbRejectService()
{
    return glbCommonPackAndSend("BD",
	VOICEPLATFORMACKCODE_SERVICEISREJECTED,
	0);
}

int glbMakeCall(int nIdx,int nDigitAnalysetableid,char * sCalled,char * sCalling)
{
    return glbCommonPackAndSend("BBBSS",
	VOICEPLATFORMACKCODE_MAKECALL,
	nIdx,
	nDigitAnalysetableid,
	strlen(sCalled)+1,sCalled,
	strlen(sCalling)+1,sCalling);
}

int glbCancelCall(int nIdx)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_CANCELCALL,
	nIdx);
}

int glbBuidNetConnection(int nSrcKind,int nSrcPin,int nDstKind,int nDstPin)
{
    return glbCommonPackAndSend("BBDBD",
	VOICEPLATFORMACKCODE_BUILDCONNECT,
	nSrcKind,nSrcPin,
	nDstKind,nDstPin);
}

int glbStartPlayVoice(int nChid,char * sTagname)
{
    return glbCommonPackAndSend("BBS",
	VOICEPLATFORMACKCODE_STARTPLAYVOICE,
	nChid,
	strlen(sTagname)+1,sTagname);
}

int glbPlayStoredVoiceData(int nChid,char * sTagname)
{
    return glbCommonPackAndSend("BBS",
	VOICEPLATFORMACKCODE_PLAYDATAINSW,
	nChid,
	strlen(sTagname)+1,sTagname);
}

int glbPlayVoiceData(int nChid,char * sVoice,int sLen)
{
    return glbCommonPackAndSend("BBDS",
	VOICEPLATFORMACKCODE_PLAYVOICEDATA,
	nChid,
	sLen,
	sLen,sVoice);
}

int glbStopPlayVoice(int nChid)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STOPPLAYVOICE,
	nChid);
}

int glbStartRecvDTMF(int nChid)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STARTRECVDTMF,
	nChid);
}

int glbStopRecvDTMF(int nChid)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STOPRECVDTMF,
	nChid);
}

int glbStartRecordVoice(int nChid)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STARTRECORDVOICE,
	nChid);
}

int glbStopRecordVoice(int nChid)
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STOPRECORDVOICE,
	nChid);
}


int glbStartMergeRecordVoice(int nChid1,int nChid2,char * sCallingDN,char * sCalledDN)
{
    return glbCommonPackAndSend("BBBBSS",
	VOICEPLATFORMACKCODE_STARTRECORDVOICE,
	120,
	nChid1,
	nChid2,
	strlen(sCallingDN)+1,sCallingDN,
	strlen(sCalledDN)+1,sCalledDN);
}

int glbStopMergeRecordVoice()
{
    return glbCommonPackAndSend("BB",
	VOICEPLATFORMACKCODE_STOPRECORDVOICE,
	120);
}




int glbEndService()
{
    return glbCommonPackAndSend("B",
	VOICEPLATFORMACKCODE_SERVICEISEND);
}

int glbOpenTTS(int nPartyid,char * sText)
{
    INTPROC_int_charPtr p;

    p=(INTPROC_int_charPtr)glbAPIFun[FUNID_OPENTTS];
    return (*p)(nPartyid,sText);
}

int glbReadTTSPCMData(int nPartyid,char * s,int sLimit)
{
    INTPROC_int_charPtr_int p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_READTTS];
    return (*p)(nPartyid,s,sLimit);
}

int glbCloseTTS(int nPartyid)
{
    INTPROC_int p;

    p=(INTPROC_int)glbAPIFun[FUNID_CLOSETTS];
    return (*p)(nPartyid);
}

int glbOpenWaveFile(int nPartyid,char * sFilename)
{
    INTPROC_int_charPtr p;

    p=(INTPROC_int_charPtr)glbAPIFun[FUNID_OPENWAVEFILE];
    return (*p)(nPartyid,sFilename);
}

int glbReadWaveFile(int nPartyid,char * s,int sLimit)
{
    INTPROC_int_charPtr_int p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_READWAVEFILE];
    return (*p)(nPartyid,s,sLimit);
}

int glbCloseWaveFile(int nPartyid)
{
    INTPROC_int p;

    p=(INTPROC_int)glbAPIFun[FUNID_CLOSEWAVEFILE];
    return (*p)(nPartyid);
}

int glbCreateWaveFile(int nPartyid,char * sFilename)
{
    INTPROC_int_charPtr p;

    p=(INTPROC_int_charPtr)glbAPIFun[FUNID_CREATEWAVEFILE];
    return (*p)(nPartyid,sFilename);
}

int glbWriteWaveFile(int nPartyid,char * s,int sLimit)
{
    INTPROC_int_charPtr_int p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_WRITEWAVEFILE];
    return (*p)(nPartyid,s,sLimit);
}

int glbExecuteSQLCommand(char * sConnectString,const char * Format,...)
{
    INTPROC_charPtr_charPtr p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=vsprintf(ss,Format,marker);				// 写入缓冲区
    va_end(marker);

    p=(INTPROC_charPtr_charPtr)glbAPIFun[FUNID_EXECUTESQLCMD];
    return (*p)(sConnectString,ss);
}

int glbExecuteSQLSelectCommand(int nIndex,char * sConnectString,const char * Format,...)
{
    INTPROC_int_charPtr_charPtr  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=vsprintf(ss,Format,marker);				// 写入缓冲区
    va_end(marker);

    p=(INTPROC_int_charPtr_charPtr)glbAPIFun[FUNID_EXECUTESQLSELECTCMD];
    return (*p)(nIndex,sConnectString,ss);
}

char * glbGetDBRecordColl(int nIndex,int nRow,int nCol)
{
    INTPROC_int_int_int  p;

    p=(INTPROC_int_int_int)glbAPIFun[FUNID_GETDBRECORDCOLVALUE];
    return (char *)((*p)(nIndex,nRow,nCol));
}

char * glbAllocateMemoryBlock(int nVol)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_ALLOCATEMEMORY];
    return (char *)((*p)(nVol));
}

int glbFreeMemoryBlock(void * s)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_FREEMEMORY];
    return (*p)((int)s);
}

int glbGetSystemTime(CDateAndTime * pTime)
{
    int a[16];
    INTPROC_intPtr  p;

    p=(INTPROC_intPtr)glbAPIFun[FUNID_GETSYSTEMTIME];
    (*p)(a);

    pTime->m_Year=a[0];
    pTime->m_Month=a[1];
    pTime->m_Day=a[2];
    pTime->m_DayOfWeek=a[3];
    pTime->m_Hour=a[4];
    pTime->m_Minute=a[5];
    pTime->m_Second=a[6];
    pTime->m_Milisecond=a[7];

    return 0;
}

int glbInvokeNewServiceLogic(char * sModuleName,int nModuleId,char * sServiceName,const char * Format,...)
{
    INTPROC_charPtr_int_charPtr_charPtr_int  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int_charPtr_charPtr_int)glbAPIFun[FUNID_INVOKENEWSERVICELOGIC];
    return (*p)(sModuleName,nModuleId,sServiceName,ss,m);
}

int glbBroadcastToAllDesk(char * sModulename,int nModuleId,int nStationClass,const char * Format,...)
{
    INTPROC_charPtr_int_int_charPtr_int  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int_int_charPtr_int)glbAPIFun[FUNID_BROADCASTALLDESK];
    return (*p)(sModulename,nModuleId,nStationClass,ss,m);
}

int glbSendToFirsDeskInHall(char * sModulename,int nModuleId,int nStationClass,const char * Format,...)
{
    INTPROC_charPtr_int_int_charPtr_int  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int_int_charPtr_int)glbAPIFun[FUNID_SENDFIRSTDESKINHALL];
    return (*p)(sModulename,nModuleId,nStationClass,ss,m);
}

int glbSendToThisNumberDesk(char * sModulename,int nModuleId,int nStationClass,int nStationNumber,const char * Format,...)
{
    INTPROC_charPtr_int_int_int_charPtr_int  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int_int_int_charPtr_int)glbAPIFun[FUNID_SENDTODESKINHALLVIANUMBER];
    return (*p)(sModulename,nModuleId,nStationClass,nStationNumber,ss,m);
}

int glbSendToThisAgentDesk(char * sModulename,int nModuleId,int nStationClass,char * sAgent,const char * Format,...)
{
    INTPROC_charPtr_int_int_charPtr_charPtr_int  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
    va_end(marker);

    p=(INTPROC_charPtr_int_int_charPtr_charPtr_int)glbAPIFun[FUNID_SENDTODESKINHALLVIAAGENT];
    return (*p)(sModulename,nModuleId,nStationClass,sAgent,ss,m);
}

int glbSendSMS(char * sCalledDNs,const char * Format,...)
{
    INTPROC_charPtr_charPtr  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=vsprintf(ss,Format,marker);				// 写入缓冲区
    va_end(marker);

    p=(INTPROC_charPtr_charPtr)glbAPIFun[FUNID_SENDSMS];
    return (*p)(sCalledDNs,ss);
}

int glbOpenVoiceRecord(int nId,char * sRecordid)
{
    INTPROC_int_charPtr  p;

    p=(INTPROC_int_charPtr)glbAPIFun[FUNID_OPENVOICERECDID];
    return (*p)(nId,sRecordid);
}

int glbReadVoiceRecord(int nId,char * s,int sLimit)
{
    INTPROC_int_charPtr_int  p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_READVOICERECDID];
    return (*p)(nId,s,sLimit);
}

int glbCloseVoiceRecord(int nId)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_CLOSEVOICERECDID];
    return (*p)(nId);
}

int glbGenFrequencyInALaw(char * s,int sLimit,int nFrequency,int nPeak)
{
    INTPROC_charPtr_int_int_int  p;

    p=(INTPROC_charPtr_int_int_int)glbAPIFun[FUNID_GENFREQUENCYINALAW];
    return (*p)(s,sLimit,nFrequency,nPeak);
}

int glbExecuteGlobalSQLSelectCommand(int nIndex,char * sConnectStr,const char * Format,...)
{
    INTPROC_int_charPtr_charPtr  p;
    va_list marker;
    int m;
    char ss[0x1000];

    va_start(marker,Format);							// 从第一个参数开始
    m=vsprintf(ss,Format,marker);				// 写入缓冲区
    va_end(marker);

    p=(INTPROC_int_charPtr_charPtr)glbAPIFun[FUNID_EXECUTEGLOBALSQLSELECTCMD];
    return (*p)(nIndex,sConnectStr,ss);
}

char * glbGetGlobalDBRecordColl(int nIndex,int nRow,int nCol)
{
    INTPROC_int_int_int  p;

    p=(INTPROC_int_int_int)glbAPIFun[FUNID_GETGLOBALDBRECORDCOLVALUE];
    return (char *)((*p)(nIndex,nRow,nCol));
}

int glbRegistSMSRecving(int nSubMsgID,char * sMobilePhoneNumber,char * ServiceKey)
{
    INTPROC_int_charPtr_charPtr  p;

    p=(INTPROC_int_charPtr_charPtr)glbAPIFun[FUNID_REGSMSRECVING];
    return (*p)(nSubMsgID,sMobilePhoneNumber,ServiceKey);
}

int glbTCPConnectToServer(char * sServerIP,int nServerPort)
{
    INTPROC_charPtr_int  p;

    p=(INTPROC_charPtr_int)glbAPIFun[FUNID_TCP_CONNECT_TO_SERVER];
    return (*p)(sServerIP,nServerPort);
}

int glbTCPCloseConnect(int nConnId)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_TCP_CLOSE_CONNECTION];
    return (*p)(nConnId);
}

int glbTCPStartListen(int nPortNum)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_TCP_START_LISTEN];
    return (*p)(nPortNum);
}

int glbTCPStopListen(int nPortNum)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_TCP_STOP_LISTEN];
    return (*p)(nPortNum);
}

int glbTCPAcceptConnection(int nPortNum)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_TCP_ACCEPT_CONNECTION];
    return (*p)(nPortNum);
}

int glbTCPSendData(int nConnId,char * s,int sLen)
{
    INTPROC_int_charPtr_int  p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_TCP_SEND_DATA];
    return (*p)(nConnId,s,sLen);
}

int glbTCPRecvData(int nConnId,char * s,int sLen)
{
    INTPROC_int_charPtr_int  p;

    p=(INTPROC_int_charPtr_int)glbAPIFun[FUNID_TCP_RECV_DATA];
    return (*p)(nConnId,s,sLen);
}

int glbTCPConnectionIsConnected(int nPortNum)
{
    INTPROC_int  p;

    p=(INTPROC_int)glbAPIFun[FUNID_TCP_IS_CONNECTED];
    return (*p)(nPortNum);
}

int glbGetAllFSMObjs(int a[],int nLimit)
{
    INTPROC_intPtr_int  p;

    p=(INTPROC_intPtr_int)glbAPIFun[FUNID_GET_ALL_FSMOBJS];
    return (*p)(a,nLimit);
}
