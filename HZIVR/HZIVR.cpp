// HZIVR.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <STDIO.H>
#include "..\\SDK\\ServiceLogicSDK.h"

#define HZPDU_HDR_LEN 8

enum
{
	FSMSTATE_IDLE,								// 空闲
	FSMSTATE_READYFORWELCOMEWORDTXT,			// 准备播放提示词的TXT部分
	FSMSTATE_PLAYINGWELCOMEWORDTXT,				// 正在播放提示词的TXT部分
	FSMSTATE_READYFORRECORDMARK,				// 准备播放 "嘟"
	FSMSTATE_PLAYINGRECORDMARK,					// 正在播放 "嘟"
	FSMSTATE_READYFORRECORD,					// 准备录音
	FSMSTATE_RECORDING,							// 正在录音
	FSMSTATE_READYFORRECEIVEDTXT,				// 准备播放从服务器收到的TXT
	FSMSTATE_PLAYINGRECEIVEDTXT,				// 正在播放从服务器收到的TXT
	FSMSTATE_LIMIT
};
//-----------------------------------------------------------------------------------------------------------------------
//	与识别服务器之间的消息类别码
//-----------------------------------------------------------------------------------------------------------------------
enum EGPRAppType
{
	EGPRAppType_rev=0,								/* 保留 */
	EGPRAppType_heartbeat,							/* 心跳 */
	EGPRAppType_ctrl,								/* 控制报文 */
	EGPRAppType_transfer,							/* 转接报文 */
	EGPRAppType_audio,								/* 音频数据 */
	EGPRAppType_Text,								/* 文本数据 */
};

enum 
{
	FSMWELCOMESTATE_IDLE,
	FSMWELCOMESTATE_FOUND,
	FSMWELCOMESTATE_LOST,
};

enum ERecordMode
{
	ERecordMode_RECORD,			/* 录音 */	
	ERecordMode_STOPRECORD,		/* 不录音 */	
	ERecordMode_RECDTMF,		/* 按键 */	
}
//-----------------------------------------------------------------------------------------------------------------------
//	与某个服务器的连接对象
//-----------------------------------------------------------------------------------------------------------------------
struct CTCPConnection
{
	int  m_ConnId;								// 连接号，与 socket 类似
	char m_Buffer[0x4000];							// 接收缓冲区
	int  m_Pos;									// 接收缓冲区中的字节数
	int  m_Timer;								// 定时器

	int InitConnection();
	int SetConnId(int nConnId);
	int OnScannIPSConnection(int nTimerUnit);					// 扫描与 IPS 板的连接
	int OnScanningVoiceSvrConnection(int nTimerUnit);				// 扫描与识别服务器的连接
	int OnIPSPDUArrived(char * s,int sLen);					// 处理来自 IPS 的消息
	int GetHZVoiceOnePDULen();							// 取来自识别服务器消息的长度（含头部分）
	int OnHZVoiceSvrPDUArrived(char * s,int sLen);				// 处理来自识别服务器的消息
	int SendFormattedPacket(const char * Format,...);				// 向 IPS 板发送格式消息
	int SendVoiceDataToHZServer(int nPid,char * sVoiceData,int nVoiceLen);
};

//-----------------------------------------------------------------------------------------------------------------------
//	业务控制块（FSM）
//-----------------------------------------------------------------------------------------------------------------------
#define HZIVR_TXTBUF_MAX 0x500
struct CHZIVRFSMItem
{
	int  m_Pid;
	int  m_State;								// FSMSTATE_xxxx
	int  m_Timer;
	char m_TextBuffer[HZIVR_TXTBUF_MAX];							// 要播放文本的缓冲区
	int  m_ReadPos;								// 读指针
	int  m_WritePos;								// 写指针
	int  m_RecordFlag;
	int  m_WelcomeState;
	int  m_RecordDelay;
	bool m_proctime;
	ERecordMode  m_RecordMode;					/* 从ivr获取处理模式 */

	int InitFSMData(int nPid,char * sParaBlock,int nParaLen);
	int OnMsgArrived(int nReqCode,char * s,int sLen);
	int ProcessTimer(int nTimerUnitInMiliseconds);
	int AppendText(char * s,int sLen);
	int GetText(char * s,int sLimit);
	CHZIVRFSMItem(){m_Pid=-1;};
	~CHZIVRFSMItem();
};

//#define FSM_PID_MAX 64
//CHZIVRFSMItem* g_fsmhandle=NULL;
//CHZIVRFSMItem* g_fsm_pids[FSM_PID_MAX];

//-----------------------------------------------------------------------------------------------------------------------
//	全局数据区（所有 FSM 共享）
//-----------------------------------------------------------------------------------------------------------------------
struct GLBWORKDATA
{
	CTCPConnection m_Conn_To_IPS;						// 与 IPS 连接对象
	CTCPConnection m_Conn_From_VoiceSvr;					// 与识别服务器连接对象
	int            m_ListenConnId;						// 侦听号（与 socket 类似）
	int            m_ListenPort;						// 侦听端口号

	int InitWorkData();
	int OnScanning(int nTimerUnitInMiliseconds);
} glbWorkData;

//-----------------------------------------------------------------------------------------------------------------------
//	全局数据区初始化
//-----------------------------------------------------------------------------------------------------------------------
int GLBWORKDATA::InitWorkData()
{
	m_Conn_To_IPS.InitConnection();						// 与 IPS 连接对象
	m_Conn_From_VoiceSvr.InitConnection();					// 与识别服务器连接对象
	m_ListenConnId=-1;								// 侦听号（与 socket 类似）
	m_ListenPort=-1;								// 侦听端口号
	return 0;
}
#if 0
int _getcurrentms()
{
	SYSTEMTIME st;
	GetLocalTime(&st); 
	return st.wMilliseconds;  // 毫秒时间
}
#endif

#define _getcurrentms GetTickCount
#include <time.h> 
FILE* _openlogFile()
{
	static FILE* s_logFile=NULL;
	static time_t s_lasttime=0;

	time_t t = time(0); 
	struct tm* _tm=localtime(&t);
	if (s_logFile==NULL || t-s_lasttime>3600*24)
	{
		if (s_logFile!=NULL)
		{
			fclose(s_logFile);
			s_logFile=NULL;
		}
		char tmp[256]; 
		strftime( tmp, sizeof(tmp), "d:\\log\\%Y-%m-%d-%H-%M-%d.log", _tm);
		s_logFile=fopen(tmp,"a+t");
		s_lasttime=t;
	}
	static time_t flushtm=0;
	if (t-s_lasttime>60*5 && s_logFile)
	{
		fflush(s_logFile);
		flushtm=t;
	}
	
	return s_logFile;
}

void _log_mutex(bool lock)
{
	static CRITICAL_SECTION m;
	static bool created=false;
	if (created == false)
	{
		created = true;
		InitializeCriticalSection(&m);
	}
	if (lock)
	{
		EnterCriticalSection(&m);
	}
	else
	{
		LeaveCriticalSection(&m);
	}
	
	
}
void Log(const char * Format,...)
{
	va_list marker;
	INTPROC_marklist_constcharPtr p;

	va_start(marker,Format);							// 从第一个参数开始
	p=(INTPROC_marklist_constcharPtr)glbAPIFun[FUNID_PRINTF];
	(*p)(marker,Format);
	va_end(marker);

	FILE* f=_openlogFile();
	if (f==NULL)
	{
		return;
	}
	
	_log_mutex(true);
	va_list logmaker;
	va_start(logmaker,Format);							// 从第一个参数开始
	vfprintf(f, Format, logmaker);
	va_end(logmaker);
	_log_mutex(false);
}
#define TTS_USE_MUTEX 1

#define TTS_TIMEOUT 10000
int _play_tts(int fsm, char* text)
{
	char sVoiceData[2000];
	int ntot=0;
	int k=0;
	Log("FSMx[%d][%lu] 播放 %s\r\n",fsm, _getcurrentms(), text);
	long ts=GetTickCount();
	// _log_mutex(true);
	glbOpenTTS(0,text);	// 打开 TTS

	for (;;)
	{
		memset(sVoiceData,0,sizeof(sVoiceData));
		k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// 取出语音
		//Log("FSMx[%d] playts spend=%d k=%d \r\n",fsm,GetTickCount()-ts,k);
		if (k<1) break;							// 取完，退出循环
		glbPlayVoiceData(0,sVoiceData,k);				// 播放
		ntot+=k;							// 播放的总字节数
		if (GetTickCount()-ts>TTS_TIMEOUT)
		{
			Log("FSMx[%d] timeout\r\n",fsm);
			break;
		}
	}
	glbCloseTTS(0);							// 关闭 TTS
	Log("FSMx[%d][%lu] 播放 %d finish\r\n",fsm, _getcurrentms(), ntot);
	// _log_mutex(false);
	return ntot;
}
//-----------------------------------------------------------------------------------------------------------------------
//	全局数据的扫描函数
//-----------------------------------------------------------------------------------------------------------------------
int GLBWORKDATA::OnScanning(int nTimerUnitInMiliseconds)
{
	if (m_ListenPort>0)								// 如果开启了 TCP 侦听
	{
		int k=glbTCPAcceptConnection(m_ListenPort);				// 接纳连接请求

		if (k>=0)								// 接纳成功
		{
			m_Conn_From_VoiceSvr.SetConnId(k);					// 存储这个连接
			Log("接收从识别器发来的连接 ID=%d\r\n",k);
		}
	}

	m_Conn_To_IPS.OnScannIPSConnection(nTimerUnitInMiliseconds);		// 维护到 IPS 的连接
	m_Conn_From_VoiceSvr.OnScanningVoiceSvrConnection(nTimerUnitInMiliseconds);	// 维护到识别服务器的连接
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	全局初始化函数
//	当该模块装入时，由系统调用
//	在该函数里，可以对全局数据进行初始化。
//	所谓全局数据是指存储在 FSM（有限状态机）实例之外的数据，比如配置数据。
//-----------------------------------------------------------------------------------------------------------------------
int OnServiceModuleLoaded()
{
	CCfgData p;									// 配置文件控制

	glbWorkData.InitWorkData();							// 把全局数据区置空
	p.ReadFromFile("HZIVR.INI");						// 打开配置文件 HZIVR.INI
	char * sIPSIP=p.GetValue("IPSIP");						// 取出 IPS 的 IP 地址
	char * sIPSPort=p.GetValue("IPSPORT");					// 取出 IPS 的录音端口号
	char * sTCPSvrPort=p.GetValue("TCPSVRPORT");				// 取出识别服务器的端口号

	if (sIPSIP!=NULL && sIPSPort!=NULL)						// 如果指定了 IPS 板
	{
		glbWorkData.m_Conn_To_IPS.m_ConnId=glbTCPConnectToServer(sIPSIP,glbAtoi(sIPSPort));	// 就建立与 IPS 的连接
	}

	if (sTCPSvrPort!=NULL)							// 如果指定了侦听端口号
	{
		glbWorkData.m_ListenPort=glbAtoi(sTCPSvrPort);				// 记录端口号
		glbWorkData.m_ListenConnId=glbTCPStartListen(glbWorkData.m_ListenPort);	// 开始侦听
	}
//	memset(g_fsm_pids,0,sizeof(g_fsm_pids));
	Log("OnServiceModuleLoaded\r\n");
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	返回模块名
//	因为是被动型模块
//	返回被叫号码（业务码）
//	它要与呼叫路由表的 CALLEDDNMODE 相呼应
//	如果 CALLEDDNMODE 为空，业务码就是原始的被叫号码
//	如果 CALLEDDNMODE 不空，业务码就是变换后的被叫号码
//-----------------------------------------------------------------------------------------------------------------------
char * glbServiceLogicFun_GetServiceName()
{
	return "68179479";
}

//-----------------------------------------------------------------------------------------------------------------------
//	下面的函数被框架调用
//	目前不用
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_EventProcess(char * s,int sLen)
{
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	返回 FSM 实例大小
//	当网管要创建业务逻辑FSM实例时，它将先调用
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_GetFSMObjVol()
{
	return sizeof(CHZIVRFSMItem);
}

CHZIVRFSMItem::~CHZIVRFSMItem()
{
	/*
	if (m_Pid>=FSM_PID_MAX || m_Pid<0) 
	{
		if (m_Pid!=-1)
		{
			g_fsmhandle=NULL;
		}
	}
	else
	{
		g_fsm_pids[m_Pid]=NULL;
	}
	*/
	Log("会话销毁 pid=%d, obj=0x%x\r\n",m_Pid,(int)this);
}
//-----------------------------------------------------------------------------------------------------------------------
//	FSM 初始化
//-----------------------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::InitFSMData(int nPid,char * sParaBlock,int nParaLen)
{
	m_Pid=nPid;
	m_ReadPos=0;								// 缓冲区清空
	m_WritePos=0;								//
	m_RecordFlag=0;
	m_State=FSMSTATE_IDLE;						// 初始状态是：可以打开录音/放音器
	m_WelcomeState=FSMWELCOMESTATE_IDLE;
	m_RecordDelay=0;
	m_proctime = false;
/*
	if (nPid>=FSM_PID_MAX || nPid<0) 
	{
		g_fsmhandle=this;
	}
	else
	{
		g_fsm_pids[nPid]=this;
	}
	*/
	Log("会话初始化 pid=%d, obj=0x%x\r\n",nPid,(int)this);

	return 0;
}

//-----------------------------------------------------------------------------------------------------------
//	消息处理函数
//-----------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::OnMsgArrived(int nReqCode,char * s,int sLen)
{
	CCommonParameter p;
	int nPartyid,nVoiceLen;
	char * sVoiceData;

	p.BindString(s,sLen,0);
	switch(nReqCode)
	{
	case VOICEPLATFORMCMDCODE_SERVICEISARRIVED:					// 业务到达, 用户拨打了该业务
		break;

	case VOICEPLATFORMCMDCODE_SERVICEISLEAVE:					// 业务结束
		return -1;

	case VOICEPLATFORMCMDCODE_DTMF_NUMBER:					// DTMF
		break;

	case VOICEPLATFORMCMDCODE_CALLED_STATE:					// 被叫状态
		break;

	case VOICEPLATFORMCMDCODE_CALLED_ANSWER:					//
		break;

	case VOICEPLATFORMCMDCODE_CALLED_BACKRELEASE:				//
		break;

	case VOICEPLATFORMCMDCODE_CALLED_HOOK_ON:					//
		break;

	case VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED:				// 语音播放结束
		Log("FSM[%d] VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED flag=%d state=%d\r\n",m_Pid,m_RecordFlag,m_State);
		if (m_State==FSMSTATE_PLAYINGWELCOMEWORDTXT)						// 如果状态也是“正在播放”
		{
			m_State=FSMSTATE_READYFORRECORDMARK;						// 状态回到“等待文本”状态
		}
		else if(m_State==FSMSTATE_PLAYINGRECORDMARK)
		{
			m_State=FSMSTATE_READYFORRECORD;
		}
		else if(m_State==FSMSTATE_PLAYINGRECEIVEDTXT)
		{
			m_State=FSMSTATE_IDLE;
		}
		break;

	case VOICEPLATFORMCMDCODE_PLAYVOICENEEDMOREDATA:				// 索要要播放的语音
		break;

	case VOICEPLATFORMCMDCODE_RECORDVOICE:					// 录音数据
		nPartyid=p.GetBYTE();							// 它一定是 0，因为只开启了对主叫方的录音
		nVoiceLen=p.GetDWORD();							// 录音数据长度（字节数）
		sVoiceData=p.GetBinDataBlock(nVoiceLen);				// 录音数据
		if (m_RecordFlag==1)
		{
			glbWorkData.m_Conn_From_VoiceSvr.SendVoiceDataToHZServer(m_Pid,sVoiceData,nVoiceLen);
		}
		else if (m_State != FSMSTATE_PLAYINGRECEIVEDTXT)
		{
			Log("FSM[%d] VOICEPLATFORMCMDCODE_RECORDVOICE flag=%d state=%d\r\n",m_Pid,m_RecordFlag,m_State);
		}
		break;

	case VOICEPLATFORMCMDCODE_RECORDIDSTRING:					// 录音号
		break;

	case VOICEPLATFORMCMDCODE_REGSMS_ARRIVED:
		break;
	}
	return 0;
}
/*
	FSMSTATE_IDLE,								// 空闲
	FSMSTATE_READYFORWELCOMEWORDTXT,			// 准备播放提示词的TXT部分
	FSMSTATE_PLAYINGWELCOMEWORDTXT,				// 正在播放提示词的TXT部分
	FSMSTATE_PLAYINGRECORDMARK,					// 正在播放 "嘟"
	FSMSTATE_READYFORRECORD,					// 准备录音
	FSMSTATE_RECORDING,							// 正在录音
	FSMSTATE_READYFORRECEIVEDTXT,				// 准备播放从服务器收到的TXT
	FSMSTATE_PLAYINGRECEIVEDTXT,				// 正在播放从服务器收到的TXT
	FSMSTATE_LIMIT
 */
//-----------------------------------------------------------------------------------------------------------
//	FSM 的定期处理函数
//-----------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::ProcessTimer(int nTimerUnitInMiliseconds)
{
	char sText[1024];
	int  n,k,ntot;
	char sVoiceData[2000];
	if (m_proctime)
	{
		return 0;
	}
	m_proctime=true;
	

	switch(m_State)
	{
	case FSMSTATE_IDLE:
		//	glbStartRecordVoice(0);							// 开始对主叫录音
		m_RecordFlag=0;
		glbStopRecordVoice(0);
		glbStartPlayVoice(0,"SILENCE");						// 开始向主叫播音
		m_State=FSMSTATE_READYFORWELCOMEWORDTXT;						// 状态是“等待文本”状态
//		AppendText("欢迎使用股票语音服务系统,请在滴的一声后讲话,讲话时请用普通话,谢谢.",-1);	// 播放提示词
		break;

		//	int glbPlayStoredVoiceData(int nChid,char * sTagname)
		//	int glbStopPlayVoice(int nChid)

	case FSMSTATE_READYFORWELCOMEWORDTXT:							// 如果状态是“等待文本”
//		n=GetText(sText,sizeof(sText)-4);
//		if (n>0)								// 若已有文本
		{
			switch(m_WelcomeState)
			{
				case FSMWELCOMESTATE_FOUND:
				{
					#if 0
					#if TTS_USE_MUTEX
						ntot = _play_tts(m_Pid,"如需查询其他股票，请您在滴的一声后讲出股票名称.");
					#else
						Log("FSM[%d] 播放 %s\r\n",m_Pid,"如需查询其他股票，请您在滴的一声后讲出股票名称.");
			//			glbOpenTTS(0,sText);						// 打开 TTS
						glbOpenTTS(0,"如需查询其他股票，请您在滴的一声后讲出股票名称.");	// 打开 TTS
						ntot=0;
						for (;;)
						{
							memset(sVoiceData,0,sizeof(sVoiceData));
							k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// 取出语音
							if (k<1) break;							// 取完，退出循环
							glbPlayVoiceData(0,sVoiceData,k);				// 播放
							ntot+=k;							// 播放的总字节数
						}
						glbCloseTTS(0);							// 关闭 TTS
					#endif
					if (ntot>0)
					{
						m_State=FSMSTATE_PLAYINGWELCOMEWORDTXT;					// 状态转为“播放状态”
						m_Timer=0;
						m_RecordDelay=1;
					}
					m_RecordFlag = 0;
					#else
					Log("FSM[%d] 播放 %s\r\n",m_Pid,"没查询到股票");
					glbPlayStoredVoiceData(0,"RECORDTAG");
					m_State=FSMSTATE_PLAYINGRECORDMARK;
					m_Timer=0;
					m_WelcomeState=4;
					#endif
				}
				m_WelcomeState=FSMWELCOMESTATE_FOUND;
				break;

				case FSMWELCOMESTATE_LOST:
					Log("FSM[%d] 播放 %s\r\n",m_Pid,"没查询到股票");
					glbPlayStoredVoiceData(0,"RECORDTAG");
					m_State=FSMSTATE_PLAYINGRECORDMARK;
					m_Timer=0;
					m_WelcomeState=4;
					break;

				case FSMWELCOMESTATE_IDLE:
				{
					#if TTS_USE_MUTEX
						ntot = _play_tts(m_Pid,"欢迎使用浙江电信号码百事通股票自动语音查询系统，请在“都”的一声后用普通话讲出您要查询的股票名称，不要讲股票代码.谢谢.");
					#else
						Log("FSM[%d] 播放 %s\r\n",m_Pid,"欢迎使用股票自动语音查询系统，请在滴的一声后用普通话讲出您要查询的股票名称，不要讲股票代码,谢谢");
			//			glbOpenTTS(0,sText);						// 打开 TTS
						glbOpenTTS(0,"欢迎使用股票自动语音查询系统，请在滴的一声后用普通话讲出您要查询的股票名称，不要讲股票代码,谢谢.");	// 打开 TTS
						ntot=0;
						for (;;)
						{
							memset(sVoiceData,0,sizeof(sVoiceData));
							k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// 取出语音
							if (k<1) break;							// 取完，退出循环
							glbPlayVoiceData(0,sVoiceData,k);				// 播放
							ntot+=k;							// 播放的总字节数
						}
						glbCloseTTS(0);							// 关闭 TTS
					#endif
					if (ntot>0)
					{
						m_State=FSMSTATE_PLAYINGWELCOMEWORDTXT;					// 状态转为“播放状态”
						m_Timer=0;
						m_RecordDelay=1;
					}
					m_RecordFlag = 0;
				}
				m_WelcomeState=FSMWELCOMESTATE_FOUND;
				break;
			
			default:
				m_State=FSMSTATE_PLAYINGRECORDMARK;
				break;

			}
		}
		break;

	case FSMSTATE_PLAYINGWELCOMEWORDTXT:							// 正在播放
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=180000)							// 已过 2 分钟
		{
			m_State=FSMSTATE_READYFORWELCOMEWORDTXT;
		}
		break;

	case FSMSTATE_READYFORRECORDMARK:
		if (m_RecordDelay<=0)
		{
			glbPlayStoredVoiceData(0,"RECORDTAG");
			m_State=FSMSTATE_PLAYINGRECORDMARK;
			m_Timer=0;
		}
		else
		{
			m_RecordDelay--;
		}
		break;

	case FSMSTATE_PLAYINGRECORDMARK:
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=30000)							// 最多30秒
		{
			m_State=FSMSTATE_READYFORRECORD;
		}
		break;

	case FSMSTATE_READYFORRECORD:
		switch(m_RecordFlag)
		{
			case 0:
				glbStartRecordVoice(0);							// 开始对主叫录音
				m_RecordFlag=1;
				break;
			case 1:
				break;
			default:
				m_RecordFlag=1;
		}
		m_State=FSMSTATE_RECORDING;
		m_Timer=0;
		break;

	case FSMSTATE_RECORDING:
/*
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=120000)							// 已过 2 分钟
		{
			m_State=FSMSTATE_IDLE;
		}
*/
		m_State=FSMSTATE_READYFORRECEIVEDTXT;
		break;

	case FSMSTATE_READYFORRECEIVEDTXT:
		n=GetText(sText,sizeof(sText)-4);
		if (n>0)								// 若已有文本
		{
			#if TTS_USE_MUTEX
				ntot = _play_tts(m_Pid,sText);
			#else
				Log("FSM[%d][%lu] 播放 %s\r\n",m_Pid,_getcurrentms(),sText);
				glbOpenTTS(0,sText);						// 打开 TTS
				ntot=0;
				for (;;)
				{
					memset(sVoiceData, 0, sizeof(sVoiceData));
					k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// 取出语音
					if (k<1) break;							// 取完，退出循环
					glbPlayVoiceData(0,sVoiceData,k);				// 播放
					ntot+=k;							// 播放的总字节数
				}
				glbCloseTTS(0);							// 关闭 TTS
			#endif
			if (ntot>0)
			{
				if (memcmp(sText,"对不起",strlen("对不起")) ==0 )
				{
					m_WelcomeState = FSMWELCOMESTATE_LOST;
				}
				else
				{
					m_WelcomeState = FSMWELCOMESTATE_FOUND;	
				}
				m_State=FSMSTATE_PLAYINGRECEIVEDTXT;					// 状态转为“播放状态”
				m_Timer=0;
				m_RecordFlag = 0;
			}
		}
		break;
	case FSMSTATE_PLAYINGRECEIVEDTXT:
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=120000)							// 已过 2 分钟
		{
			m_State=FSMSTATE_IDLE;
		}
		break;
	}
	m_proctime = false;
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	把文本写入文本缓冲区
//-----------------------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::AppendText(char * s,int sLen)
{
	int i,IsHalfHz;
	IsHalfHz=0;

	if (sLen<0) sLen=strlen(s);
	// m_RecordFlag=2;

	for (i=0;i<sLen;i++)
	{
		m_TextBuffer[m_WritePos]=s[i];
		if (IsHalfHz)
		{
			IsHalfHz = 0;
		}
		else
		{
			if ((s[i]&0x80) != 0)
			{
				IsHalfHz = 1;
			}
		}

		m_WritePos++;
		if (m_WritePos>=HZIVR_TXTBUF_MAX)
		{
			m_WritePos=0;
		}
	}
	if(IsHalfHz!=0)
	{
		m_WritePos--;
		if (m_WritePos<0)
		{
			m_WritePos = HZIVR_TXTBUF_MAX-1;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	从缓冲区中取出一个文本
//-----------------------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::GetText(char * s,int sLimit)
{
	BYTE c;
	int n,IsHalfHz;

	n=0;
	IsHalfHz=0;
	while (m_ReadPos!=m_WritePos && n<sLimit-4)
	{
		c=m_TextBuffer[m_ReadPos];
		m_ReadPos++;
		if (m_ReadPos>=HZIVR_TXTBUF_MAX)
		{
			m_ReadPos=0;
		} 
		s[n]=c;
		n++;
		if (IsHalfHz)
		{
			IsHalfHz=0;
		}
		else
		{
			if ((c&0x80) != 0)
			{
				IsHalfHz=1;
			}
		}
	}

	if (IsHalfHz)								// 如果是半个汉字
	{
		n--;									// 回退一个字符
		m_ReadPos--;
		if (m_ReadPos<0)
		{
			m_ReadPos=HZIVR_TXTBUF_MAX-1;
		}
	}
	s[n]=0;
	if (n>10)
	{
		Log("FSM[%d][%lu]get text %s\r\n",m_Pid,_getcurrentms(),s);
	}
	return n;
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM 初始化
//	当网管服务取得了FSM占用的内存大小后，将申请内存，然后调用该函数
//	其中	pObj 是内网管为该FSM申请的内存地址；
//		nPid 是交换一侧的进程编号;
//		sParaBlock 是传入的参数；
//		nParaLen 是参数的字节数。
//		注：所有的业务逻辑，总是先在排队机中创建进程，后在网管中创建业务逻辑。
//	返回时，返回-1，表示拒绝创建业务逻辑（比如参数不合适），
//		返回 0表示接收申请，创建成功。
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_InitFSMObj(void * pObj,int nPid,char * sParaBlock,int nParaLen)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->InitFSMData(nPid,sParaBlock,nParaLen);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM 消息处理函数
//	当FSM创建成功后，网管服务一旦收到交换机发来的消息，将调用该函数
//	其中，pObj 是FSM的地址；
//	nReqCode 是消息编码；
//	s 是消息参数；
//	sLen 是参数字节数。
//	nReqCode 的编码及参数格式如下：
//	VOICEPLATFORMCMDCODE_SERVICEISARRIVED，由网管使用，业务代码不处理;
//	VOICEPLATFORMCMDCODE_SERVICEISLEAVE, 由网管使用，业务代码不处理它；
//	VOICEPLATFORMCMDCODE_HANDSHAKEREQ, 由网管使用，业务代码不处理它；
//	VOICEPLATFORMCMDCODE_DTMF_NUMBER, 交换机收到了DTMF串，参数格式：
//	返回0表示处理正常
//	返回-1，表示需要终止当前FSM，网管释放当前FSM占用的内存，释放该FSM。
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_OnMsgArrived(void * pObj,int nReqCode,char * s,int sLen)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->OnMsgArrived(nReqCode,s,sLen);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM 定时处理函数
//	FSM创建成功后，网管服务将定期地调用该函数
//	返回0表示处理正常
//	返回-1，表示需要终止当前FSM，网管释放当前FSM占用的内存，释放该FSM。
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_OnTimer(void * pObj,int nTimerUnitInMiliseconds)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->ProcessTimer(nTimerUnitInMiliseconds);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM 终止函数
//	每当FSM终止时，网管将调用该函数
//	其中，pObj 指向FSM实例；
//	业务逻辑可在此函数中处理扫尾工作。
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_OnDestroy(void * pObj)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;
#if 0
	if (p->m_Pid>=FSM_PID_MAX || p->m_Pid<0) 
	{
		g_fsmhandle=NULL;
	}
	else
	{
		g_fsm_pids[p->m_Pid]=NULL;
	}

	Log("会话销毁 pid=%d,obj=0x%x\r\n",p->m_Pid, (int)pObj);
#endif
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	模块级定期扫描函数
//	无论FSM实例创建与否，网管服务均要定期调用该函数
//	其中，nTimerUnit是本次调用距上次调用的毫秒数。
//	业务逻辑可在此函数中进行模块级的（与 FSM 无关）的扫描工作。
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_ModuleScanning(int nTimerUnit)
{
	glbWorkData.OnScanning(nTimerUnit);
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	模块卸出函数
//	每当DLL模块被卸出时，系统将调用该函数
//	业务逻辑代码可在此函数中进行模块级的扫尾工作。
//-----------------------------------------------------------------------------------------------------------------------
int OnServiceModuleUnLoaded()
{
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	TCP 连接初始化函数
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::InitConnection()
{
	m_ConnId=-1;								// 连接号置空，与 socket 类似
	m_Pos=0;									// 接收缓冲区中的字节数置 0
	m_Timer=0;									// 定时器
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	更改连接号
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SetConnId(int nConnId)
{
	if (m_ConnId>=0)								// 如果已有连接
	{
		glbTCPCloseConnect(m_ConnId);						// 关闭它
	}
	m_Pos=0;									// 清除已收到的内容
	m_ConnId=nConnId;								// 记录新连接号
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	IPS 消息处理函数
//	暂时不处理
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::OnIPSPDUArrived(char * s,int sLen)
{
	int n=glbDecloseFromPkt(s,sLen);
	CCommonParameter p;
	int nMsgCode,x;

	p.BindString(s,n,0);
	nMsgCode=p.GetWORD();
	switch(nMsgCode)
	{
	case TCPIP_MSG_LINKTEST:							// 测试消息
		x=p.GetWORD();
		if (x==0)								// 测试请求
		{
			SendFormattedPacket("WW",TCPIP_MSG_LINKTEST,1);			// 发测试证实
		}
		break;

	case TCPIP_MSG_RECDPORTREPORT:
		/*	    glbCallControlAreaPtr->SWRecdBinFun_BroadcastRecordCommandToAllClients("WWWWDSS",
		TCPIP_MSG_RECDPORTREPORT,
		m_recd_Port,
		1,

		m_recd_RingFlag,
		m_recd_DeskNum,

		strlen(m_strCallingDN)+1,m_strCallingDN,
		strlen(m_CalledDataItems[0].m_strCalledDN)+1,m_CalledDataItems[0].m_strCalledDN);
		*/
		break;

	case TCPIP_MSG_REPORT_VOICEDATA:
		/*	    glbCallControlAreaPtr->SWRecdBinFun_BroadcastRecordCommandToAllClients("WWWS",
		TCPIP_MSG_REPORT_VOICEDATA,
		m_recd_Port,
		m_recd_VoicePos,
		m_recd_VoicePos,m_recd_VoiceBuffer);
		*/
		break;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	维护 IPS 连接
//	暂时不处理
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::OnScannIPSConnection(int nTimerUnit)
{
	if (m_ConnId<0)
	{
		return 0;
	}
	int k=glbTCPRecvData(m_ConnId,&m_Buffer[m_Pos],sizeof(m_Buffer)-m_Pos);
	if (k>0) m_Pos+=k;
	int i,j;

	j=0;
	for (i=0;i<m_Pos;i++)
		if (m_Buffer[i]==0x0d)
		{
			OnIPSPDUArrived(&m_Buffer[j],i-j);
			j=i+1;
		}
		if (j>=m_Pos) m_Pos=0;
		else
			if (j>0)
			{
				memcpy(m_Buffer,&m_Buffer[j],m_Pos-j);
				m_Pos-=j;
			}

			m_Timer+=nTimerUnit;
			if (m_Timer>=30000)
			{
				m_Timer=0;
			}
			return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	取识别服务器连接上的消息的总长度
//	含头部的 10 个字节
//	返回 0 表示消息不全
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::GetHZVoiceOnePDULen()
{
	CCommonParameter p;

	if (m_Pos<HZPDU_HDR_LEN)
	{
		return 0;
	}
	p.BindString(m_Buffer,m_Pos,1);
	p.GetWORD();
	p.GetBYTE();
	p.GetBYTE();
	int k=p.GetDWORD();
//	Log("收到语音数据 len=%d pos=%d\r\n",k,m_Pos);
	if (m_Pos>=k+HZPDU_HDR_LEN)
	{
		return k+HZPDU_HDR_LEN;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	发送 IPS 格式的消息
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SendFormattedPacket(const char * Format,...)
{
	va_list marker;
	int m;
	char ss[0x4000];

	va_start(marker,Format);							// 从第一个参数开始
	m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
	va_end(marker);

	int n=glbEncloseToPkt(ss,m);
	return glbTCPSendData(m_ConnId,ss,n);
}

//-----------------------------------------------------------------------------------------------------------------------
//	向识别服务器发一段语音
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SendVoiceDataToHZServer(int nPid,char * sVoiceData,int nVoiceLen)
{
	char ss[2000];
	int i,k;
	CCommonParameter p;
	static int s_prtcnt=0;

	if (m_ConnId>=0)								// 如果连接存在
	{
		if ((s_prtcnt%30)==0)
			Log("FSM[%d]向识别服务器发语音:LEN=%d\r\n",nPid,nVoiceLen);
		for (i=0;i<nVoiceLen;i+=k)						// 分块发
		{
			k=nVoiceLen-i;
			if (k>1000) k=1000;							// 每块最多 1000 字节
			p.BindString(ss,sizeof(ss),1);
			p.PutBYTE('G');
			p.PutBYTE('L');
			p.PutBYTE(0);							// version
			p.PutBYTE(EGPRAppType_audio);			// app Type
			p.PutDWORD(k+HZPDU_HDR_LEN);						// payLoad Size
			p.PutDWORD(nPid);						// Pid
			p.PutDWORD(0);							// SN
			p.PutBinDataBlock(sVoiceData+i,k);
			glbTCPSendData(m_ConnId,ss,p.GetCurrentWritePos());
		}
		s_prtcnt++;
	}
	else
	{
		s_prtcnt=0;
		Log("*****因没有连接无法向向识别服务器发语音:PID=%d LEN=%d\r\n",nPid,nVoiceLen);
	}
	return 0;
}
static int GB2312ToUtf8(const char* gb2312, char* utf8)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return len;
}

static int Utf8ToGB2312(const char* utf8, char* gb2312)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, gb2312, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return len;
}

//-----------------------------------------------------------------------------------------------------------------------
//	处理一条识别服务器发来的消息
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::OnHZVoiceSvrPDUArrived(char * s,int sLen)
{
	CCommonParameter p;
	int nPid,CountOfFSM,i;
	int a[2000];

	p.BindString(s,sLen,1);

	char cc1=p.GetBYTE();
	char cc2=p.GetBYTE();
	int tversion=p.GetBYTE();
	int tappType=p.GetBYTE();
	int payloadLen=p.GetDWORD();
	char * payloadBody=p.GetBinDataBlock(payloadLen);

//	Log("收到来自识别服务器的消息 LEN=%d SIG1=%d SIG2=%d type=%d\r\n",sLen,cc1,cc2,tappType);

	if (cc1=='G' && cc2=='L')
	{
		switch(tappType)
		{
		case EGPRAppType_rev:							/* 保留 */
			break;

		case EGPRAppType_heartbeat:						/* 心跳 */
			break;

		case EGPRAppType_ctrl:							/* 控制报文 */
			break;

		case EGPRAppType_transfer:						/* 转接报文 */
			break;

		case EGPRAppType_audio:							/* 音频数据 */
			break;

		case EGPRAppType_Text:							/* 文本数据, 格式：PID(4B) 文本(nB)*/
			p.BindString(payloadBody,payloadLen,1);
			nPid=p.GetDWORD();							// 取出 PID
			p.GetDWORD();							// sn
#if 0
			{
				int VoiceLen;
				char * VoiceData;
				char tempbuffer[2000];
				VoiceData=p.GetRemainBinBlock(&VoiceLen);			// 把 TXT 放入缓冲区
				char temp[2000];
				memcpy(temp,VoiceData, VoiceLen);
				temp[VoiceLen]='\0';
				Utf8ToGB2312(temp, tempbuffer);
				tempbuffer[VoiceLen] = '\0';
				Log("收到来自识别服务器的语音数据消息 nPid=%d msg=%s\r\n",nPid,tempbuffer);
			
				if (nPid>=FSM_PID_MAX || nPid<0) 
				{
					if (g_fsmhandle!=NULL)
					{
						g_fsmhandle->AppendText(tempbuffer, VoiceLen);
					}
					else
					{
						Log("WARNING:illegal fsm machatine pid=%d\r\n",nPid);
					}
				}
				else
				{
					if (g_fsm_pids[nPid]!=NULL)
					{
						g_fsm_pids[nPid]->AppendText(tempbuffer, VoiceLen);
					}
					else
					{
						Log("WARNING:illegal fsm machatine pid(pid)=%d\r\n",nPid);
					}
				}

			}
#endif
#if 1
			CountOfFSM=glbGetAllFSMObjs(a,2000);				// 取出该模块下所有的 FSM
			for (i=0;i<CountOfFSM;i++)						// 在这些 FSM 中查找
			{
				CHZIVRFSMItem * pFSM;

				pFSM=(CHZIVRFSMItem *)a[i];
				Log("FSM pid=%d\r\n",pFSM->m_Pid);
				if (pFSM->m_Pid==nPid)						// 找到
				{
					int VoiceLen;
					char * VoiceData;
					char tempbuffer[2000];
					VoiceData=p.GetRemainBinBlock(&VoiceLen);			// 把 TXT 放入缓冲区
					
					char temp[2000];
					memcpy(temp,VoiceData, VoiceLen);
					temp[VoiceLen]='\0';
					Utf8ToGB2312(temp, tempbuffer);
					tempbuffer[VoiceLen] = '\0';
					pFSM->AppendText(tempbuffer,VoiceLen);
					Log("FSM[%d][%d]收到来自识别服务器的TXT发往[%d][%d]:%s \r\n",nPid,_getcurrentms(),VoiceLen,payloadLen,tempbuffer);

					break;
				}
			}
#endif
			break;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	扫描识别服务器的连接
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::OnScanningVoiceSvrConnection(int nTimerUnit)
{
	if (m_ConnId<0)
	{
		return 0;
	}
	int k=glbTCPRecvData(m_ConnId,&m_Buffer[m_Pos],sizeof(m_Buffer)-m_Pos);	// 读数据
	if (k<0)									// 如果连接丢失
	{
		glbTCPCloseConnect(m_ConnId);						// 关闭连接
		m_ConnId=-1;
		return 0;
	}

	if (k>0)
	{
		m_Pos+=k;								//
//		Log("11从识别服务器收到数据 k=%d pos=%d \r\n",k,m_Pos);
		while ((k=GetHZVoiceOnePDULen())>0)						// 如果发现一条消息
		{
			OnHZVoiceSvrPDUArrived(m_Buffer,k);					// 处理它
//		Log("pdu finished k=%d pos=%d \r\n",k,m_Pos);
			if (k>=m_Pos) m_Pos=0;							// 如果没有剩下的字节， 就把 POS 置 0
			else
			{
				memcpy(m_Buffer,&m_Buffer[k],m_Pos-k);				// 把剩下的左移
				m_Pos-=k;
			}
		}
	}

	m_Timer+=nTimerUnit;
	if (m_Timer>=30000)
	{
		m_Timer=0;
	}
	return 0;
}
