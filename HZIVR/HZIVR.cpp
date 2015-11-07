// HZIVR.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <STDIO.H>
#include "..\\SDK\\ServiceLogicSDK.h"

#define HZPDU_HDR_LEN 8

enum
{
	FSMSTATE_IDLE,								// ����
	FSMSTATE_READYFORWELCOMEWORDTXT,			// ׼��������ʾ�ʵ�TXT����
	FSMSTATE_PLAYINGWELCOMEWORDTXT,				// ���ڲ�����ʾ�ʵ�TXT����
	FSMSTATE_READYFORRECORDMARK,				// ׼������ "�"
	FSMSTATE_PLAYINGRECORDMARK,					// ���ڲ��� "�"
	FSMSTATE_READYFORRECORD,					// ׼��¼��
	FSMSTATE_RECORDING,							// ����¼��
	FSMSTATE_READYFORRECEIVEDTXT,				// ׼�����Ŵӷ������յ���TXT
	FSMSTATE_PLAYINGRECEIVEDTXT,				// ���ڲ��Ŵӷ������յ���TXT
	FSMSTATE_LIMIT
};
//-----------------------------------------------------------------------------------------------------------------------
//	��ʶ�������֮�����Ϣ�����
//-----------------------------------------------------------------------------------------------------------------------
enum EGPRAppType
{
	EGPRAppType_rev=0,								/* ���� */
	EGPRAppType_heartbeat,							/* ���� */
	EGPRAppType_ctrl,								/* ���Ʊ��� */
	EGPRAppType_transfer,							/* ת�ӱ��� */
	EGPRAppType_audio,								/* ��Ƶ���� */
	EGPRAppType_Text,								/* �ı����� */
};

enum 
{
	FSMWELCOMESTATE_IDLE,
	FSMWELCOMESTATE_FOUND,
	FSMWELCOMESTATE_LOST,
};

enum ERecordMode
{
	ERecordMode_RECORD,			/* ¼�� */	
	ERecordMode_STOPRECORD,		/* ��¼�� */	
	ERecordMode_RECDTMF,		/* ���� */	
}
//-----------------------------------------------------------------------------------------------------------------------
//	��ĳ�������������Ӷ���
//-----------------------------------------------------------------------------------------------------------------------
struct CTCPConnection
{
	int  m_ConnId;								// ���Ӻţ��� socket ����
	char m_Buffer[0x4000];							// ���ջ�����
	int  m_Pos;									// ���ջ������е��ֽ���
	int  m_Timer;								// ��ʱ��

	int InitConnection();
	int SetConnId(int nConnId);
	int OnScannIPSConnection(int nTimerUnit);					// ɨ���� IPS �������
	int OnScanningVoiceSvrConnection(int nTimerUnit);				// ɨ����ʶ�������������
	int OnIPSPDUArrived(char * s,int sLen);					// �������� IPS ����Ϣ
	int GetHZVoiceOnePDULen();							// ȡ����ʶ���������Ϣ�ĳ��ȣ���ͷ���֣�
	int OnHZVoiceSvrPDUArrived(char * s,int sLen);				// ��������ʶ�����������Ϣ
	int SendFormattedPacket(const char * Format,...);				// �� IPS �巢�͸�ʽ��Ϣ
	int SendVoiceDataToHZServer(int nPid,char * sVoiceData,int nVoiceLen);
};

//-----------------------------------------------------------------------------------------------------------------------
//	ҵ����ƿ飨FSM��
//-----------------------------------------------------------------------------------------------------------------------
#define HZIVR_TXTBUF_MAX 0x500
struct CHZIVRFSMItem
{
	int  m_Pid;
	int  m_State;								// FSMSTATE_xxxx
	int  m_Timer;
	char m_TextBuffer[HZIVR_TXTBUF_MAX];							// Ҫ�����ı��Ļ�����
	int  m_ReadPos;								// ��ָ��
	int  m_WritePos;								// дָ��
	int  m_RecordFlag;
	int  m_WelcomeState;
	int  m_RecordDelay;
	bool m_proctime;
	ERecordMode  m_RecordMode;					/* ��ivr��ȡ����ģʽ */

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
//	ȫ�������������� FSM ����
//-----------------------------------------------------------------------------------------------------------------------
struct GLBWORKDATA
{
	CTCPConnection m_Conn_To_IPS;						// �� IPS ���Ӷ���
	CTCPConnection m_Conn_From_VoiceSvr;					// ��ʶ����������Ӷ���
	int            m_ListenConnId;						// �����ţ��� socket ���ƣ�
	int            m_ListenPort;						// �����˿ں�

	int InitWorkData();
	int OnScanning(int nTimerUnitInMiliseconds);
} glbWorkData;

//-----------------------------------------------------------------------------------------------------------------------
//	ȫ����������ʼ��
//-----------------------------------------------------------------------------------------------------------------------
int GLBWORKDATA::InitWorkData()
{
	m_Conn_To_IPS.InitConnection();						// �� IPS ���Ӷ���
	m_Conn_From_VoiceSvr.InitConnection();					// ��ʶ����������Ӷ���
	m_ListenConnId=-1;								// �����ţ��� socket ���ƣ�
	m_ListenPort=-1;								// �����˿ں�
	return 0;
}
#if 0
int _getcurrentms()
{
	SYSTEMTIME st;
	GetLocalTime(&st); 
	return st.wMilliseconds;  // ����ʱ��
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

	va_start(marker,Format);							// �ӵ�һ��������ʼ
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
	va_start(logmaker,Format);							// �ӵ�һ��������ʼ
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
	Log("FSMx[%d][%lu] ���� %s\r\n",fsm, _getcurrentms(), text);
	long ts=GetTickCount();
	// _log_mutex(true);
	glbOpenTTS(0,text);	// �� TTS

	for (;;)
	{
		memset(sVoiceData,0,sizeof(sVoiceData));
		k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// ȡ������
		//Log("FSMx[%d] playts spend=%d k=%d \r\n",fsm,GetTickCount()-ts,k);
		if (k<1) break;							// ȡ�꣬�˳�ѭ��
		glbPlayVoiceData(0,sVoiceData,k);				// ����
		ntot+=k;							// ���ŵ����ֽ���
		if (GetTickCount()-ts>TTS_TIMEOUT)
		{
			Log("FSMx[%d] timeout\r\n",fsm);
			break;
		}
	}
	glbCloseTTS(0);							// �ر� TTS
	Log("FSMx[%d][%lu] ���� %d finish\r\n",fsm, _getcurrentms(), ntot);
	// _log_mutex(false);
	return ntot;
}
//-----------------------------------------------------------------------------------------------------------------------
//	ȫ�����ݵ�ɨ�躯��
//-----------------------------------------------------------------------------------------------------------------------
int GLBWORKDATA::OnScanning(int nTimerUnitInMiliseconds)
{
	if (m_ListenPort>0)								// ��������� TCP ����
	{
		int k=glbTCPAcceptConnection(m_ListenPort);				// ������������

		if (k>=0)								// ���ɳɹ�
		{
			m_Conn_From_VoiceSvr.SetConnId(k);					// �洢�������
			Log("���մ�ʶ�������������� ID=%d\r\n",k);
		}
	}

	m_Conn_To_IPS.OnScannIPSConnection(nTimerUnitInMiliseconds);		// ά���� IPS ������
	m_Conn_From_VoiceSvr.OnScanningVoiceSvrConnection(nTimerUnitInMiliseconds);	// ά����ʶ�������������
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	ȫ�ֳ�ʼ������
//	����ģ��װ��ʱ����ϵͳ����
//	�ڸú�������Զ�ȫ�����ݽ��г�ʼ����
//	��νȫ��������ָ�洢�� FSM������״̬����ʵ��֮������ݣ������������ݡ�
//-----------------------------------------------------------------------------------------------------------------------
int OnServiceModuleLoaded()
{
	CCfgData p;									// �����ļ�����

	glbWorkData.InitWorkData();							// ��ȫ���������ÿ�
	p.ReadFromFile("HZIVR.INI");						// �������ļ� HZIVR.INI
	char * sIPSIP=p.GetValue("IPSIP");						// ȡ�� IPS �� IP ��ַ
	char * sIPSPort=p.GetValue("IPSPORT");					// ȡ�� IPS ��¼���˿ں�
	char * sTCPSvrPort=p.GetValue("TCPSVRPORT");				// ȡ��ʶ��������Ķ˿ں�

	if (sIPSIP!=NULL && sIPSPort!=NULL)						// ���ָ���� IPS ��
	{
		glbWorkData.m_Conn_To_IPS.m_ConnId=glbTCPConnectToServer(sIPSIP,glbAtoi(sIPSPort));	// �ͽ����� IPS ������
	}

	if (sTCPSvrPort!=NULL)							// ���ָ���������˿ں�
	{
		glbWorkData.m_ListenPort=glbAtoi(sTCPSvrPort);				// ��¼�˿ں�
		glbWorkData.m_ListenConnId=glbTCPStartListen(glbWorkData.m_ListenPort);	// ��ʼ����
	}
//	memset(g_fsm_pids,0,sizeof(g_fsm_pids));
	Log("OnServiceModuleLoaded\r\n");
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	����ģ����
//	��Ϊ�Ǳ�����ģ��
//	���ر��к��루ҵ���룩
//	��Ҫ�����·�ɱ�� CALLEDDNMODE ���Ӧ
//	��� CALLEDDNMODE Ϊ�գ�ҵ�������ԭʼ�ı��к���
//	��� CALLEDDNMODE ���գ�ҵ������Ǳ任��ı��к���
//-----------------------------------------------------------------------------------------------------------------------
char * glbServiceLogicFun_GetServiceName()
{
	return "68179479";
}

//-----------------------------------------------------------------------------------------------------------------------
//	����ĺ�������ܵ���
//	Ŀǰ����
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_EventProcess(char * s,int sLen)
{
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	���� FSM ʵ����С
//	������Ҫ����ҵ���߼�FSMʵ��ʱ�������ȵ���
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
	Log("�Ự���� pid=%d, obj=0x%x\r\n",m_Pid,(int)this);
}
//-----------------------------------------------------------------------------------------------------------------------
//	FSM ��ʼ��
//-----------------------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::InitFSMData(int nPid,char * sParaBlock,int nParaLen)
{
	m_Pid=nPid;
	m_ReadPos=0;								// ���������
	m_WritePos=0;								//
	m_RecordFlag=0;
	m_State=FSMSTATE_IDLE;						// ��ʼ״̬�ǣ����Դ�¼��/������
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
	Log("�Ự��ʼ�� pid=%d, obj=0x%x\r\n",nPid,(int)this);

	return 0;
}

//-----------------------------------------------------------------------------------------------------------
//	��Ϣ������
//-----------------------------------------------------------------------------------------------------------
int CHZIVRFSMItem::OnMsgArrived(int nReqCode,char * s,int sLen)
{
	CCommonParameter p;
	int nPartyid,nVoiceLen;
	char * sVoiceData;

	p.BindString(s,sLen,0);
	switch(nReqCode)
	{
	case VOICEPLATFORMCMDCODE_SERVICEISARRIVED:					// ҵ�񵽴�, �û������˸�ҵ��
		break;

	case VOICEPLATFORMCMDCODE_SERVICEISLEAVE:					// ҵ�����
		return -1;

	case VOICEPLATFORMCMDCODE_DTMF_NUMBER:					// DTMF
		break;

	case VOICEPLATFORMCMDCODE_CALLED_STATE:					// ����״̬
		break;

	case VOICEPLATFORMCMDCODE_CALLED_ANSWER:					//
		break;

	case VOICEPLATFORMCMDCODE_CALLED_BACKRELEASE:				//
		break;

	case VOICEPLATFORMCMDCODE_CALLED_HOOK_ON:					//
		break;

	case VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED:				// �������Ž���
		Log("FSM[%d] VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED flag=%d state=%d\r\n",m_Pid,m_RecordFlag,m_State);
		if (m_State==FSMSTATE_PLAYINGWELCOMEWORDTXT)						// ���״̬Ҳ�ǡ����ڲ��š�
		{
			m_State=FSMSTATE_READYFORRECORDMARK;						// ״̬�ص����ȴ��ı���״̬
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

	case VOICEPLATFORMCMDCODE_PLAYVOICENEEDMOREDATA:				// ��ҪҪ���ŵ�����
		break;

	case VOICEPLATFORMCMDCODE_RECORDVOICE:					// ¼������
		nPartyid=p.GetBYTE();							// ��һ���� 0����Ϊֻ�����˶����з���¼��
		nVoiceLen=p.GetDWORD();							// ¼�����ݳ��ȣ��ֽ�����
		sVoiceData=p.GetBinDataBlock(nVoiceLen);				// ¼������
		if (m_RecordFlag==1)
		{
			glbWorkData.m_Conn_From_VoiceSvr.SendVoiceDataToHZServer(m_Pid,sVoiceData,nVoiceLen);
		}
		else if (m_State != FSMSTATE_PLAYINGRECEIVEDTXT)
		{
			Log("FSM[%d] VOICEPLATFORMCMDCODE_RECORDVOICE flag=%d state=%d\r\n",m_Pid,m_RecordFlag,m_State);
		}
		break;

	case VOICEPLATFORMCMDCODE_RECORDIDSTRING:					// ¼����
		break;

	case VOICEPLATFORMCMDCODE_REGSMS_ARRIVED:
		break;
	}
	return 0;
}
/*
	FSMSTATE_IDLE,								// ����
	FSMSTATE_READYFORWELCOMEWORDTXT,			// ׼��������ʾ�ʵ�TXT����
	FSMSTATE_PLAYINGWELCOMEWORDTXT,				// ���ڲ�����ʾ�ʵ�TXT����
	FSMSTATE_PLAYINGRECORDMARK,					// ���ڲ��� "�"
	FSMSTATE_READYFORRECORD,					// ׼��¼��
	FSMSTATE_RECORDING,							// ����¼��
	FSMSTATE_READYFORRECEIVEDTXT,				// ׼�����Ŵӷ������յ���TXT
	FSMSTATE_PLAYINGRECEIVEDTXT,				// ���ڲ��Ŵӷ������յ���TXT
	FSMSTATE_LIMIT
 */
//-----------------------------------------------------------------------------------------------------------
//	FSM �Ķ��ڴ�����
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
		//	glbStartRecordVoice(0);							// ��ʼ������¼��
		m_RecordFlag=0;
		glbStopRecordVoice(0);
		glbStartPlayVoice(0,"SILENCE");						// ��ʼ�����в���
		m_State=FSMSTATE_READYFORWELCOMEWORDTXT;						// ״̬�ǡ��ȴ��ı���״̬
//		AppendText("��ӭʹ�ù�Ʊ��������ϵͳ,���ڵε�һ���󽲻�,����ʱ������ͨ��,лл.",-1);	// ������ʾ��
		break;

		//	int glbPlayStoredVoiceData(int nChid,char * sTagname)
		//	int glbStopPlayVoice(int nChid)

	case FSMSTATE_READYFORWELCOMEWORDTXT:							// ���״̬�ǡ��ȴ��ı���
//		n=GetText(sText,sizeof(sText)-4);
//		if (n>0)								// �������ı�
		{
			switch(m_WelcomeState)
			{
				case FSMWELCOMESTATE_FOUND:
				{
					#if 0
					#if TTS_USE_MUTEX
						ntot = _play_tts(m_Pid,"�����ѯ������Ʊ�������ڵε�һ���󽲳���Ʊ����.");
					#else
						Log("FSM[%d] ���� %s\r\n",m_Pid,"�����ѯ������Ʊ�������ڵε�һ���󽲳���Ʊ����.");
			//			glbOpenTTS(0,sText);						// �� TTS
						glbOpenTTS(0,"�����ѯ������Ʊ�������ڵε�һ���󽲳���Ʊ����.");	// �� TTS
						ntot=0;
						for (;;)
						{
							memset(sVoiceData,0,sizeof(sVoiceData));
							k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// ȡ������
							if (k<1) break;							// ȡ�꣬�˳�ѭ��
							glbPlayVoiceData(0,sVoiceData,k);				// ����
							ntot+=k;							// ���ŵ����ֽ���
						}
						glbCloseTTS(0);							// �ر� TTS
					#endif
					if (ntot>0)
					{
						m_State=FSMSTATE_PLAYINGWELCOMEWORDTXT;					// ״̬תΪ������״̬��
						m_Timer=0;
						m_RecordDelay=1;
					}
					m_RecordFlag = 0;
					#else
					Log("FSM[%d] ���� %s\r\n",m_Pid,"û��ѯ����Ʊ");
					glbPlayStoredVoiceData(0,"RECORDTAG");
					m_State=FSMSTATE_PLAYINGRECORDMARK;
					m_Timer=0;
					m_WelcomeState=4;
					#endif
				}
				m_WelcomeState=FSMWELCOMESTATE_FOUND;
				break;

				case FSMWELCOMESTATE_LOST:
					Log("FSM[%d] ���� %s\r\n",m_Pid,"û��ѯ����Ʊ");
					glbPlayStoredVoiceData(0,"RECORDTAG");
					m_State=FSMSTATE_PLAYINGRECORDMARK;
					m_Timer=0;
					m_WelcomeState=4;
					break;

				case FSMWELCOMESTATE_IDLE:
				{
					#if TTS_USE_MUTEX
						ntot = _play_tts(m_Pid,"��ӭʹ���㽭���ź������ͨ��Ʊ�Զ�������ѯϵͳ�����ڡ�������һ��������ͨ��������Ҫ��ѯ�Ĺ�Ʊ���ƣ���Ҫ����Ʊ����.лл.");
					#else
						Log("FSM[%d] ���� %s\r\n",m_Pid,"��ӭʹ�ù�Ʊ�Զ�������ѯϵͳ�����ڵε�һ��������ͨ��������Ҫ��ѯ�Ĺ�Ʊ���ƣ���Ҫ����Ʊ����,лл");
			//			glbOpenTTS(0,sText);						// �� TTS
						glbOpenTTS(0,"��ӭʹ�ù�Ʊ�Զ�������ѯϵͳ�����ڵε�һ��������ͨ��������Ҫ��ѯ�Ĺ�Ʊ���ƣ���Ҫ����Ʊ����,лл.");	// �� TTS
						ntot=0;
						for (;;)
						{
							memset(sVoiceData,0,sizeof(sVoiceData));
							k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// ȡ������
							if (k<1) break;							// ȡ�꣬�˳�ѭ��
							glbPlayVoiceData(0,sVoiceData,k);				// ����
							ntot+=k;							// ���ŵ����ֽ���
						}
						glbCloseTTS(0);							// �ر� TTS
					#endif
					if (ntot>0)
					{
						m_State=FSMSTATE_PLAYINGWELCOMEWORDTXT;					// ״̬תΪ������״̬��
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

	case FSMSTATE_PLAYINGWELCOMEWORDTXT:							// ���ڲ���
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=180000)							// �ѹ� 2 ����
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
		if (m_Timer>=30000)							// ���30��
		{
			m_State=FSMSTATE_READYFORRECORD;
		}
		break;

	case FSMSTATE_READYFORRECORD:
		switch(m_RecordFlag)
		{
			case 0:
				glbStartRecordVoice(0);							// ��ʼ������¼��
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
		if (m_Timer>=120000)							// �ѹ� 2 ����
		{
			m_State=FSMSTATE_IDLE;
		}
*/
		m_State=FSMSTATE_READYFORRECEIVEDTXT;
		break;

	case FSMSTATE_READYFORRECEIVEDTXT:
		n=GetText(sText,sizeof(sText)-4);
		if (n>0)								// �������ı�
		{
			#if TTS_USE_MUTEX
				ntot = _play_tts(m_Pid,sText);
			#else
				Log("FSM[%d][%lu] ���� %s\r\n",m_Pid,_getcurrentms(),sText);
				glbOpenTTS(0,sText);						// �� TTS
				ntot=0;
				for (;;)
				{
					memset(sVoiceData, 0, sizeof(sVoiceData));
					k=glbReadTTSPCMData(0,sVoiceData,sizeof(sVoiceData)-4);		// ȡ������
					if (k<1) break;							// ȡ�꣬�˳�ѭ��
					glbPlayVoiceData(0,sVoiceData,k);				// ����
					ntot+=k;							// ���ŵ����ֽ���
				}
				glbCloseTTS(0);							// �ر� TTS
			#endif
			if (ntot>0)
			{
				if (memcmp(sText,"�Բ���",strlen("�Բ���")) ==0 )
				{
					m_WelcomeState = FSMWELCOMESTATE_LOST;
				}
				else
				{
					m_WelcomeState = FSMWELCOMESTATE_FOUND;	
				}
				m_State=FSMSTATE_PLAYINGRECEIVEDTXT;					// ״̬תΪ������״̬��
				m_Timer=0;
				m_RecordFlag = 0;
			}
		}
		break;
	case FSMSTATE_PLAYINGRECEIVEDTXT:
		m_Timer+=nTimerUnitInMiliseconds;
		if (m_Timer>=120000)							// �ѹ� 2 ����
		{
			m_State=FSMSTATE_IDLE;
		}
		break;
	}
	m_proctime = false;
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	���ı�д���ı�������
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
//	�ӻ�������ȡ��һ���ı�
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

	if (IsHalfHz)								// ����ǰ������
	{
		n--;									// ����һ���ַ�
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
//	FSM ��ʼ��
//	�����ܷ���ȡ����FSMռ�õ��ڴ��С�󣬽������ڴ棬Ȼ����øú���
//	����	pObj ��������Ϊ��FSM������ڴ��ַ��
//		nPid �ǽ���һ��Ľ��̱��;
//		sParaBlock �Ǵ���Ĳ�����
//		nParaLen �ǲ������ֽ�����
//		ע�����е�ҵ���߼������������Ŷӻ��д������̣����������д���ҵ���߼���
//	����ʱ������-1����ʾ�ܾ�����ҵ���߼���������������ʣ���
//		���� 0��ʾ�������룬�����ɹ���
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_InitFSMObj(void * pObj,int nPid,char * sParaBlock,int nParaLen)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->InitFSMData(nPid,sParaBlock,nParaLen);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM ��Ϣ������
//	��FSM�����ɹ������ܷ���һ���յ���������������Ϣ�������øú���
//	���У�pObj ��FSM�ĵ�ַ��
//	nReqCode ����Ϣ���룻
//	s ����Ϣ������
//	sLen �ǲ����ֽ�����
//	nReqCode �ı��뼰������ʽ���£�
//	VOICEPLATFORMCMDCODE_SERVICEISARRIVED��������ʹ�ã�ҵ����벻����;
//	VOICEPLATFORMCMDCODE_SERVICEISLEAVE, ������ʹ�ã�ҵ����벻��������
//	VOICEPLATFORMCMDCODE_HANDSHAKEREQ, ������ʹ�ã�ҵ����벻��������
//	VOICEPLATFORMCMDCODE_DTMF_NUMBER, �������յ���DTMF����������ʽ��
//	����0��ʾ��������
//	����-1����ʾ��Ҫ��ֹ��ǰFSM�������ͷŵ�ǰFSMռ�õ��ڴ棬�ͷŸ�FSM��
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_OnMsgArrived(void * pObj,int nReqCode,char * s,int sLen)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->OnMsgArrived(nReqCode,s,sLen);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM ��ʱ������
//	FSM�����ɹ������ܷ��񽫶��ڵص��øú���
//	����0��ʾ��������
//	����-1����ʾ��Ҫ��ֹ��ǰFSM�������ͷŵ�ǰFSMռ�õ��ڴ棬�ͷŸ�FSM��
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_OnTimer(void * pObj,int nTimerUnitInMiliseconds)
{
	CHZIVRFSMItem * p=(CHZIVRFSMItem *)pObj;

	return p->ProcessTimer(nTimerUnitInMiliseconds);
}

//-----------------------------------------------------------------------------------------------------------------------
//	FSM ��ֹ����
//	ÿ��FSM��ֹʱ�����ܽ����øú���
//	���У�pObj ָ��FSMʵ����
//	ҵ���߼����ڴ˺����д���ɨβ������
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

	Log("�Ự���� pid=%d,obj=0x%x\r\n",p->m_Pid, (int)pObj);
#endif
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	ģ�鼶����ɨ�躯��
//	����FSMʵ������������ܷ����Ҫ���ڵ��øú���
//	���У�nTimerUnit�Ǳ��ε��þ��ϴε��õĺ�������
//	ҵ���߼����ڴ˺����н���ģ�鼶�ģ��� FSM �޹أ���ɨ�蹤����
//-----------------------------------------------------------------------------------------------------------------------
int glbServiceLogicFun_ModuleScanning(int nTimerUnit)
{
	glbWorkData.OnScanning(nTimerUnit);
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	ģ��ж������
//	ÿ��DLLģ�鱻ж��ʱ��ϵͳ�����øú���
//	ҵ���߼�������ڴ˺����н���ģ�鼶��ɨβ������
//-----------------------------------------------------------------------------------------------------------------------
int OnServiceModuleUnLoaded()
{
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	TCP ���ӳ�ʼ������
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::InitConnection()
{
	m_ConnId=-1;								// ���Ӻ��ÿգ��� socket ����
	m_Pos=0;									// ���ջ������е��ֽ����� 0
	m_Timer=0;									// ��ʱ��
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	�������Ӻ�
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SetConnId(int nConnId)
{
	if (m_ConnId>=0)								// �����������
	{
		glbTCPCloseConnect(m_ConnId);						// �ر���
	}
	m_Pos=0;									// ������յ�������
	m_ConnId=nConnId;								// ��¼�����Ӻ�
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	IPS ��Ϣ������
//	��ʱ������
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
	case TCPIP_MSG_LINKTEST:							// ������Ϣ
		x=p.GetWORD();
		if (x==0)								// ��������
		{
			SendFormattedPacket("WW",TCPIP_MSG_LINKTEST,1);			// ������֤ʵ
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
//	ά�� IPS ����
//	��ʱ������
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
//	ȡʶ������������ϵ���Ϣ���ܳ���
//	��ͷ���� 10 ���ֽ�
//	���� 0 ��ʾ��Ϣ��ȫ
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
//	Log("�յ��������� len=%d pos=%d\r\n",k,m_Pos);
	if (m_Pos>=k+HZPDU_HDR_LEN)
	{
		return k+HZPDU_HDR_LEN;
	}
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//	���� IPS ��ʽ����Ϣ
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SendFormattedPacket(const char * Format,...)
{
	va_list marker;
	int m;
	char ss[0x4000];

	va_start(marker,Format);							// �ӵ�һ��������ʼ
	m=subCommonPack(0,Format,marker,ss,sizeof(ss),NULL);
	va_end(marker);

	int n=glbEncloseToPkt(ss,m);
	return glbTCPSendData(m_ConnId,ss,n);
}

//-----------------------------------------------------------------------------------------------------------------------
//	��ʶ���������һ������
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::SendVoiceDataToHZServer(int nPid,char * sVoiceData,int nVoiceLen)
{
	char ss[2000];
	int i,k;
	CCommonParameter p;
	static int s_prtcnt=0;

	if (m_ConnId>=0)								// ������Ӵ���
	{
		if ((s_prtcnt%30)==0)
			Log("FSM[%d]��ʶ�������������:LEN=%d\r\n",nPid,nVoiceLen);
		for (i=0;i<nVoiceLen;i+=k)						// �ֿ鷢
		{
			k=nVoiceLen-i;
			if (k>1000) k=1000;							// ÿ����� 1000 �ֽ�
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
		Log("*****��û�������޷�����ʶ�������������:PID=%d LEN=%d\r\n",nPid,nVoiceLen);
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
//	����һ��ʶ���������������Ϣ
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

//	Log("�յ�����ʶ�����������Ϣ LEN=%d SIG1=%d SIG2=%d type=%d\r\n",sLen,cc1,cc2,tappType);

	if (cc1=='G' && cc2=='L')
	{
		switch(tappType)
		{
		case EGPRAppType_rev:							/* ���� */
			break;

		case EGPRAppType_heartbeat:						/* ���� */
			break;

		case EGPRAppType_ctrl:							/* ���Ʊ��� */
			break;

		case EGPRAppType_transfer:						/* ת�ӱ��� */
			break;

		case EGPRAppType_audio:							/* ��Ƶ���� */
			break;

		case EGPRAppType_Text:							/* �ı�����, ��ʽ��PID(4B) �ı�(nB)*/
			p.BindString(payloadBody,payloadLen,1);
			nPid=p.GetDWORD();							// ȡ�� PID
			p.GetDWORD();							// sn
#if 0
			{
				int VoiceLen;
				char * VoiceData;
				char tempbuffer[2000];
				VoiceData=p.GetRemainBinBlock(&VoiceLen);			// �� TXT ���뻺����
				char temp[2000];
				memcpy(temp,VoiceData, VoiceLen);
				temp[VoiceLen]='\0';
				Utf8ToGB2312(temp, tempbuffer);
				tempbuffer[VoiceLen] = '\0';
				Log("�յ�����ʶ�������������������Ϣ nPid=%d msg=%s\r\n",nPid,tempbuffer);
			
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
			CountOfFSM=glbGetAllFSMObjs(a,2000);				// ȡ����ģ�������е� FSM
			for (i=0;i<CountOfFSM;i++)						// ����Щ FSM �в���
			{
				CHZIVRFSMItem * pFSM;

				pFSM=(CHZIVRFSMItem *)a[i];
				Log("FSM pid=%d\r\n",pFSM->m_Pid);
				if (pFSM->m_Pid==nPid)						// �ҵ�
				{
					int VoiceLen;
					char * VoiceData;
					char tempbuffer[2000];
					VoiceData=p.GetRemainBinBlock(&VoiceLen);			// �� TXT ���뻺����
					
					char temp[2000];
					memcpy(temp,VoiceData, VoiceLen);
					temp[VoiceLen]='\0';
					Utf8ToGB2312(temp, tempbuffer);
					tempbuffer[VoiceLen] = '\0';
					pFSM->AppendText(tempbuffer,VoiceLen);
					Log("FSM[%d][%d]�յ�����ʶ���������TXT����[%d][%d]:%s \r\n",nPid,_getcurrentms(),VoiceLen,payloadLen,tempbuffer);

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
//	ɨ��ʶ�������������
//-----------------------------------------------------------------------------------------------------------------------
int CTCPConnection::OnScanningVoiceSvrConnection(int nTimerUnit)
{
	if (m_ConnId<0)
	{
		return 0;
	}
	int k=glbTCPRecvData(m_ConnId,&m_Buffer[m_Pos],sizeof(m_Buffer)-m_Pos);	// ������
	if (k<0)									// ������Ӷ�ʧ
	{
		glbTCPCloseConnect(m_ConnId);						// �ر�����
		m_ConnId=-1;
		return 0;
	}

	if (k>0)
	{
		m_Pos+=k;								//
//		Log("11��ʶ��������յ����� k=%d pos=%d \r\n",k,m_Pos);
		while ((k=GetHZVoiceOnePDULen())>0)						// �������һ����Ϣ
		{
			OnHZVoiceSvrPDUArrived(m_Buffer,k);					// ������
//		Log("pdu finished k=%d pos=%d \r\n",k,m_Pos);
			if (k>=m_Pos) m_Pos=0;							// ���û��ʣ�µ��ֽڣ� �Ͱ� POS �� 0
			else
			{
				memcpy(m_Buffer,&m_Buffer[k],m_Pos-k);				// ��ʣ�µ�����
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
