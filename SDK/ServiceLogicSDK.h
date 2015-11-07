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
//	���幤��̨���Ա���
//---------------------------------------------------------------------------
#define STATION_110			0x01
#define STATION_CK			0x02
#define STATION_GPSS			0x04
#define STATION_GPSC			0x08

enum
{
    CALLEDSTATE_IDLE,							// ����״̬ ����
    CALLEDSTATE_BUSY,							// ����״̬ æ
    CALLEDSTATE_NOT_FOUND,						// ����״̬ �պ�
    CALLEDSTATE_BLOCKED,						// ����״̬ ����
    CALLEDSTATE_DONTDISTURB,						// ����״̬ �����
    CALLEDSTATE_ABSENCESERVICE,						// ����״̬ ȱϯ����
    CALLEDSTATE_UNKOWN=10,						// ����״̬ ���ڴ�����, δ֪
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
//	�˿�����
//-----------------------------------------------------------------------------------------
enum
{
    PORTKINDCODE_NULL,							// �ն˿�
    PORTKINDCODE_LOCAL_USER,						// �û��˿�
    PORTKINDCODE_LOCAL_CO,						// CO �˿�
    PORTKINDCODE_LOCAL_EM_DTMF,						// E/M �˿� DTMF
    PORTKINDCODE_LOCAL_EM_MFC,						// E/M �˿� MFC
    PORTKINDCODE_LOCAL_EMPTY,						// ���ؿն˿�

    PORTKINDCODE_RMT_USER,						// �û��˿�
    PORTKINDCODE_RMT_CO,						// CO �˿�
    PORTKINDCODE_RMT_EM_DTMF,						// E/M �˿� DTMF
    PORTKINDCODE_RMT_EM_MFC,						// E/M �˿� MFC
    PORTKINDCODE_RMT_EMPTY,						// Զ�˿ն˿�

    PORTKINDCODE_R2,							// �й�һ������
    PORTKINDCODE_TUP,							// �й��ߺ����� TUP
    PORTKINDCODE_ISUP,							// �й��ߺ����� ISUP
    PORTKINDCODE_Q931,							// Q.931
    PORTKINDCODE_V5_SLOT,						// V5 ��ʱ϶(E1)
    PORTKINDCODE_REMOTE_SLOT,						// Զ�˶˿�ʱ϶(E1)
    PORTKINDCODE_HIGHWAY_SLOT,						// ģ��仰·
    PORTKINDCODE_E1_EMPTY,						// δ����� E1

    PORTKINDCODE_V5_CTL,						// V5 ���ƶ˿�
    PORTKINDCODE_V5_EMPTY,						// �� V5 �˿�

    PORTKINDCODE_TAIHE,							// ̩��
    PORTKINDCODE_WANGE,							// ���

    PORTKINDCODE_RESOURCE,						// ��Դ
    PORTKINDCODE_HIGHWAY_CTL,						// ģ��� PCM ����
    PORTKINDCODE_VOTCP_HIWAY_CTL,					// VoTCP HIGHWAY ����
    PORTKINDCODE_VOTCP_TRUNK_CTL,					// VoTCP TRUNK ����
    PORTKINDCODE_VOTCP_PHONE_CTL,					// VoTCP PHONE ����
    PORTKINDCODE_SIP_PHONE_CTL,						// SIP PHONE ����
    PORTKINDCODE_VOICENOTE_CTL,						// ¼������ ����
    PORTKINDCODE_EASYCONF_CTL,						// �򵥻��� ����
    PORTKINDCODE_CTIRELAY_CTL,						// CTI ת��(����ת��) ����
    PORTKINDCODE_DYNAMIC,						// ��̬����

    PORTKINDCODE_LIMIT
};


//-----------------------------------------------------------------------------------------
//	�ź����ı���
//-----------------------------------------------------------------------------------------
enum
{
    SIGTONE_DIAL,							// ��ͨ������
    SIGTONE_RINGBACK,							// ������
    SIGTONE_BUSY,							// æ��
    SIGTONE_CONJEST,							// ӵ����
    SIGTONE_SPECIALDIAL,						// ���Ⲧ����
    SIGTONE_EMPTY,							// �պ���
    SIGTONE_LONGTOLL,							// ��;֪ͨ��
    SIGTONE_PROVE,							// ֤ʵ��
    SIGTONE_CALLWAIT,							// ���������
    SIGTONE_SILENCE,							// ����
    SIGTONE_VOICEPROMPT,						// ������ʾ
    SIGTONE_LIMIT							// �ź������ܸ���
};

//-------------------------------------------------------------------------------------------
//	������(SW)==>���ܷ�����(NMS)
//-------------------------------------------------------------------------------------------
enum
{
    VOICEPLATFORMCMDCODE_SERVICEISARRIVED=1,				// ҵ�񵽴�, �û������˸�ҵ��
    VOICEPLATFORMCMDCODE_SERVICEISLEAVE,				// ҵ�����
    VOICEPLATFORMCMDCODE_HANDSHAKEREQ,					// ��������
    VOICEPLATFORMCMDCODE_DTMF_NUMBER,					// DTMF
    VOICEPLATFORMCMDCODE_CALLED_STATE,					//
    VOICEPLATFORMCMDCODE_CALLED_ANSWER,					//
    VOICEPLATFORMCMDCODE_CALLED_BACKRELEASE,					//
    VOICEPLATFORMCMDCODE_CALLED_HOOK_ON,				//
    VOICEPLATFORMCMDCODE_PLAYVOICEFINISHED,				//
    VOICEPLATFORMCMDCODE_PLAYVOICENEEDMOREDATA,				//
    VOICEPLATFORMCMDCODE_RECORDVOICE,					//
    VOICEPLATFORMCMDCODE_RECORDIDSTRING,				// ¼����

    VOICEPLATFORMCMDCODE_REGSMS_ARRIVED=0x400,				//
};

//-------------------------------------------------------------------------------------------
//	���ܷ�����(NMS)==>������
//-------------------------------------------------------------------------------------------
enum
{
    VOICEPLATFORMACKCODE_SERVICEISACCEPTED=1,				// ҵ�񱻽���
    VOICEPLATFORMACKCODE_SERVICEISREJECTED,				// ҵ�񱻾ܾ�
    VOICEPLATFORMACKCODE_HANDSHAKEACK,					// ����֤ʵ
    VOICEPLATFORMACKCODE_MAKECALL,					// ����
    VOICEPLATFORMACKCODE_CANCELCALL,					// ��ֹ����
    VOICEPLATFORMACKCODE_BUILDCONNECT,					// ʱ϶���

    VOICEPLATFORMACKCODE_STARTPLAYVOICE,				// ��ʼ��������
    VOICEPLATFORMACKCODE_PLAYVOICEDATA,					// �������ݿ�
    VOICEPLATFORMACKCODE_PLAYDATAINSW,					// ���Ž������ڴ��Ѽ��ص�����
    VOICEPLATFORMACKCODE_STOPPLAYVOICE,					// ֹͣ��������

    VOICEPLATFORMACKCODE_STARTRECVDTMF,					// ��ʼ�պ�
    VOICEPLATFORMACKCODE_STOPRECVDTMF,					// ֹͣ�պ�

    VOICEPLATFORMACKCODE_STARTRECORDVOICE,				// ��ʼ¼��
    VOICEPLATFORMACKCODE_STOPRECORDVOICE,				// ֹͣ¼��

    VOICEPLATFORMACKCODE_SERVICEISEND,					// ҵ����ֹ
};

//---------------------------------------------------------------------------
//	TCP/IP �����ֱ���
//---------------------------------------------------------------------------
enum
{
    TCPIP_MSG_NULL,			// ����			0
    TCPIP_MSG_PHONE_STATE,		// �㱨����״̬		1
    TCPIP_MSG_ONOFF_STATE,		// ��ȡ��/�¸�״̬	2
    TCPIP_MSG_QUEUE_TAB,		// �Ŷ���Ϣ		3
    TCPIP_MSG_CK_DIGIT,			// CK ������		4
    TCPIP_MSG_CONFERENCE_BOOK,		// ��������		5
    TCPIP_MSG_CONFERENCE_STATE,		// �����״̬		6
    TCPIP_MSG_CHAIRMAN_STATE,		// ��ϯ״̬		7
    TCPIP_MSG_TURN_TO_THIRD,		//			8
    TCPIP_MSG_OUTGOING_CALL,		//			9
    TCPIP_MSG_LINKTEST,			//			10
    TCPIP_MSG_SYSRESET,			//			11
    TCPIP_MSG_RASOPROTOCOL,		//			12
    TCPIP_MSG_RECD_RECORD_ID=16,
    TCPIP_MSG_GEN_RECD_DATAFILE,	// ���� PCM �ļ�        17
    TCPIP_MSG_OPENFILEFORREAD,		// �Զ���ʽ���ļ�	18
    TCPIP_MSG_READFILEDATA,		// ���ļ�����		19
    TCPIP_MSG_CLOSEFILE,		// �ر��ļ�		20
    TCPIP_MSG_GEN_RECD_INDEXFILE,	// ����¼�������ļ�	21
    TCPIP_MSG_DEL_RECD_RECORD,		// ɾ��ĳ��¼����¼	22
    TCPIP_MSG_GET_RECD_PORT_STATE,	// ȡ¼���˿�״̬	23
    TCPIP_MSG_SET_RECD_PORT_MASK,	// ��¼���˿���Ļ��     24
    TCPIP_MSG_GET_BLACKLISTENABLE,	// ȡ������ʹ��		25
    TCPIP_MSG_SET_BLACKLISTENABLE,	// �ú�����ʹ��		26
    TCPIP_MSG_SET_CALLINGDIGITS,	// �����к���		27
    TCPIP_MSG_SET_RECDSUPERVISION,	// �ü���״̬		28
    TCPIP_MSG_REPORT_VOICEDATA,		// ������������		29
    TCPIP_MSG_TALKWITHSOMEONEINCONF,	// ��ָ����ĳһ�����ͨ��	30
    TCPIP_MSG_FORCEDISCARDCONF,		// ǿ��ɢ��		31
    TCPIP_MSG_3PARTYWITHCOBUILD,	// �� CO ĳ���˿ڿ���������	32
    TCPIP_MSG_3PARTYWITHCODESTROY,	// �� CO ĳ���˿���������ɢ��	33
    TCPIP_MSG_TRANSLATETHISRECORDID,	// ��ĳ��¼���ŷ�����ļ����ͳ�ʼλ�� 34
    TCPIP_MSG_SEEKFILEPOSITION,		// �ƶ��ļ�ָ��		35
    TCPIP_MSG_RECDDATASRVCTL,		// ¼�����ݷ���������/�Ͽ���Ϣ	36
    TCPIP_MSG_RECDPORTREPORT,		// ¼���˿�״̬����	37
    TCPIP_MSG_SET_BLACKLISTITEM,	// �ú���������         38
    TCPIP_MSG_SET_CK1PHONENUMBERITEM,	// ��CK1��110�պţ����к���  39
    TCPIP_MSG_SET_CK2PHONENUMBERITEM,	// ��CK2��110���պţ����к���  40
    TCPIP_MSG_SET_FRIENDPHONENUMBERITEM,// ���Ѻ��û����к���  41
    TCPIP_MSG_APPENDONEALARMRECORD,	// ����һ���Ӿ���¼    42
    TCPIP_MSG_EXECCOMMAND,		// ִ��һ������  43
    TCPIP_MSG_GET_SYSTEMINFORMATION,	// ȡϵͳ��Ϣ    44
    TCPIP_MSG_NOTEPCSALARMRECORD,	// �����ɵ�      45
    TCPIP_MSG_SINGLEAUDIENCECONTROL,	// �������ӿ��� 46
    TCPIP_MSG_FETCHLOCALRINGCTLBIT,	// ������Ϣ̨�������ѯ�� 119 �Ƿ�����Զ�˿��ƾ���     47
    TCPIP_MSG_REPORTLOCALRINGCTLBIT,	// �㱨���Ʊ��� 48
    TCPIP_MSG_WRITERINGCONTROLBIT,	// ���˿�����Զ��̨д��������� 49
    TCPIP_MSG_SENDSMSREQ,		// ���Ͷ������� 50
    TCPIP_MSG_NOTEHOOKONWHILEQUEING,	// ֪ͨ�Ŷ�ʱ�һ� 51
    TCPIP_MSG_NOTE3RDCALLEDSTATE,	// ֪ͨ�� 3 ��״̬ 52
    TCPIP_MSG_SETAUTOENTER3PARTMODE,	// ���Զ���ʽ 53
    TCPIP_MSG_SETCURRENTDATEANDTIME,	// ������/ʱ�� 54
    TCPIP_MSG_SETSVRCURRENTDATEANDTIME,	// ������/ʱ�� 55
    TCPIP_MSG_ACKFORNOTEPCSALARMRECORD,	// ��ִ
    TCPIP_MSG_REQFORALLSTATIONSTATE,	// ��Ҫ���нӾ�̨��״̬ ����
    TCPIP_MSG_ACKFORALLSTATIONSTATE,	// ��Ҫ���нӾ�̨��״̬ �ش�
    TCPIP_MSG_PREPOSTFORALLSTATIONSTATE,// ��Ҫ���нӾ�̨��״̬ �ش�
    TCPIP_MSG_REFRESHSMSRECORDLIST,	// ˢ�¶��ż�¼��
    TCPIP_MSG_SETRECORDERPORTSTATE,	// ˢ��¼���˿�״̬
    TCPIP_MSG_SETLISTENPRESENTWORD,	// ���ü�����־��
    TCPIP_MSG_PLAYRECORDEDVOICETOCALLER,// �����в���¼��
    TCPIP_MSG_GPSPKTARRIVE,		// �� UDP ���յ�һ�� GPS ����
    TCPIP_MSG_SENDGPSPKTREQ,		// ����GPS��������
    TCPIP_MSG_RELOADGPSMSBOOK,		// ����װ�� GPS �� MS ����
    TCPIP_MSG_E1BOARDSTATE,		// E1 ϵͳ״̬
    TCPIP_MSG_MTP3LINKSTATE,		// �ߺ���·״̬
    TCPIP_MSG_PLAYTELDNDIGITS,		// ���ź���
    TCPIP_MSG_STARTPLAYVOICETOPCS,	// ���ɳ�������
    TCPIP_MSG_OPENPLAYERDEVICE,		// �򿪲����豸
    TCPIP_MSG_CLOSEPLAYERDEVICE,	// �رղ����豸
    TCPIP_MSG_VOICEDATATOSTATION,	// ¼������
    TCPIP_MSG_NOTECK2CALLINGDN,		// CK2 ���к���
    TCPIP_MSG_HOTQUEUINGPHONE,		// �Ŷӵ绰����
    TCPIP_MSG_NOTESLAVEDB,		// ֪ͨ�������ݿ�
    TCPIP_MSG_BUILDMULTYPARTYTALKING,	// ����෽����
    TCPIP_MSG_IPPHONEPKT,		// IP Phone ����
    TCPIP_MSG_GETRECORDIDFULLINFO,	// ȡ¼����������Ϣ
    TCPIP_MSG_GETLOCKEDONDTDNLIST,	// ���м̷������û��б�
    TCPIP_MSG_PLAYTHISRECDVIAPHONE,	// �ýӾ���������¼��
    TCPIP_MSG_GPSLINKTESTING,		// �յ�һ�� GPS ��������·���Ա���
    TCPIP_MSG_SETDS300PAIDANSTATE,	// ���þ���ƽ̨�ϵ��ӵ�״̬
    TCPIP_MSG_OPERATION_FEICHENG_JW_DB,	// �����ʳǵľ���ƽ̨���ݿ�
    TCPIP_MSG_OPERATION_VOICENOTE,	// ��������֪ͨ����
    TCPIP_MSG_RECALLSTATION,		// ���º��нӾ�̨
    TCPIP_MSG_COMBINEDCALLINFO,		// һ��������Ϣ
    TCPIP_MSG_ALARMFORRPTHOOKON,	// �߹���Ϣ
    TCPIP_MSG_JINTANLIKE_JWPTINFO,	// ��̳���͵ľ���Խ���Ϣ
    TCPIP_MSG_GPSRAWPKTDATAARRIVE,	// GPS ԭʼ���ݱ��ĵ���
    TCPIP_MSG_GETTTSOFTHISTEXT,		// ��ָ���Ĵ���������ļ�
    TCPIP_MSG_TTSOFTHISTEXTISDONE,	// TTS �Ѿ�����
    TCPIP_MSG_FETCHTTSSPEACHDATA_REQ,	// ȡTTS��������
    TCPIP_MSG_FETCHTTSSPEACHDATA_ACK,	// ȡTTS��������
    TCPIP_MSG_RECDSIM_PHONE_STATE,	// ��¼���ͻ���ת���Ļ���״̬�㱨����״̬
    TCPIP_MSG_ONEJIEJINGDANISBORND,	// һ�ŽӾ����Ѿ�����,��Ҫ����Ļ����ʾ����
    TCPIP_MSG_SETLOGICALPHONESTATE,	// ���û������߼�״̬
    TCPIP_MSG_GEN_ALARMETITEM_REQ,	// ���ɳ��������¾��� ����
    TCPIP_MSG_GEN_ALARMETITEM_ACK,	// ���ɳ��������¾��� Ӧ��
    TCPIP_MSG_ASY_GETPCSNAMELIST_REQ,	// ��Ҫ���ϸڵ��ɳ����������б�
    TCPIP_MSG_ASY_GETPCSNAMELIST_ACK,	// ��Ҫ���ϸڵ��ɳ����������б��Ӧ��
    TCPIP_MSG_ASY_REFRESH_DIAODU_LIST,	// ���µ�λ�����
    TCPIP_MSG_DIAODU_CALLEDSTATE,	// �Զ�����ʱ,���е�״̬
    TCPIP_MSG_APPENDALARMCONTENTS,	// ���ӱ�������
    TCPIP_MSG_SETBRIEFPROMPTINFO_REQ,	// ���ü�Ҫ����, �೤̨->������
    TCPIP_MSG_SETBRIEFPROMPTINFO_CMD,	// ���ü�Ҫ����, ������->�೤̨
    TCPIP_MSG_GPSCARNODETRACKRATIOARRIVE,// ��λ�ʵ���
    TCPIP_MSG_FETCHDESKVERION_REQ,	// ȡ���°汾��,����
    TCPIP_MSG_FETCHDESKVERION_ACK,	// ȡ���°汾��,Ӧ��
    TCPIP_MSG_SETNEWALARMSETIDNUMBER,	// ���������ɵľ�����
    TCPIP_MSG_SETSENDINGVOICEDATATOME,	// ������Ҫ��̨¼��
    TCPIP_MSG_VOICEDATABLOCKFORSAVE,	// ����Ҫ�洢��¼������
    TCPIP_MSG_WRITETOSHENGTING_HUNCHUEN,// ��ʡ����������(����)
    TCPIP_MSG_SETHOTALARMRECORDID,	// ���øո����ɵľ�����
    TCPIP_MSG_MSPHONELOCATIONINFO,	// �ֻ���λ���ݵ���
    TCPIP_MSG_GPSCARPHOTOTAKEN,		// ������һ����Ƭ
    TCPIP_MSG_GPSCARPHOTOPAGEDATA,	// ��Ƭ����
    TCPIP_MSG_DELETEJUSTBORNALARMRECORD,// ɾ���ո����ɵĽӾ���¼
    TCPIP_MSG_JS110JWPT_JDINQUEUE,	// �¾������γ�
    TCPIP_MSG_JS110JWPT_SENDTOTIANCHENG,// ����ɹ�˾�ɵ�
    TCPIP_MSG_WRITESMSRECORDLIST,	// ��Ӿ�̨���д���ŵ�
    TCPIP_MSG_SMSNOTEFORALARM,		// ���ű�����Ϣ
    TCPIP_MSG_FETCHSMSNODENAMES_CMD,	// ȡ���ŷ����������� ����
    TCPIP_MSG_FETCHSMSNODENAMES_ACK,	// ȡ���ŷ����������� ���
    TCPIP_MSG_REASSIGNPHONEZONENAME_CMD,// �����ֻ�����������
    TCPIP_MSG_DESKINSORLISTENTOPHONE,	// ǿ������
    TCPIP_MSG_FETCHALLSTATIONIDARRAY_CMD,	// ȡ�ѵ�¼��̨�Ӻż�����
    TCPIP_MSG_FETCHALLSTATIONIDARRAY_ACK,	// ȡ�ѵ�¼��̨�Ӻż�����
    TCPIP_MSG_FORCEQUITTOSYSTEM,	// ��ͻ���ǿ���˳�
    TCPIP_MSG_SQ_FETCHLOGINGORMATION,		// ��Ǩ��ȡ��¼��Ϣ
    TCPIP_MSG_SMSMSDN_FEEDBACKREG,	// ���Żط�̨�ӵǼ�
    TCPIP_MSG_REGSTERREDSMSARRIVED,	// �ǼǵĻط����ŵ���
    TCPIP_MSG_AUTOSTATISTICJOB_CMD,	// �Զ�ͳ������
    TCPIP_MSG_RELOADSYSCONFIGDATA,	// ���´ӿ���ȡ����
    TCPIP_MSG_TRYPINGJINGONTHISJJDBH,	// ���ŶԴ˾�������
    TCPIP_MSG_GETGEOLOCATIONXY,		// ���ŶԴ˾���λ
    TCPIP_MSG_FKDBHASFILLEDVIAPCS,	// �ɳ�������д�˷�����
    TCPIP_MSG_LIYANG_GETCARINFO_REQ,	// ȡ����GPS����ע����Ϣ ����
    TCPIP_MSG_LIYANG_GETCARINFO_ACK,	// ȡ����GPS����ע����Ϣ Ӧ��
    TCPIP_MSG_LIYANG_GETCARXY_REQ,	// ȡ����GPS������ʷλ�� ����
    TCPIP_MSG_LIYANG_GETCARXY_ACK,	// ȡ����GPS������ʷλ�� ����
    TCPIP_MSG_LYG_FETCHNEXTHOTELSMS_REQ,	// ���Ƹ�
    TCPIP_MSG_LYG_FETCHNEXTHOTELSMS_ACK,	// ���Ƹ�
    TCPIP_MSG_JINING_WEBACTION_REQ,	// ����
    TCPIP_MSG_JINING_WEBACTION_ACK,	// ����
    TCPIP_MSG_YINGTAN_EXTERN_CKINFO_RPT,	// ӥ̶
    TCPIP_MSG_YINGTAN_EXTERN_CKINFO_CMD,	// ӥ̶
    TCPIP_MSG_YINGTAN_FETCH_KEYINFOONJJDB_REQ,	// ӥ̶
    TCPIP_MSG_YINGTAN_FETCH_KEYINFOONJJDB_ACK,	// ӥ̶
    TCPIP_MSG_YINGTAN_SET_KEYINFOONJJDB_CMD,	// ӥ̶
    TCPIP_MSG_TIMERSERVICE_REQ,			// ��ʱ��������
    TCPIP_MSG_TIMERSERVICE_ACK,			// ��ʱ����Ӧ��
    TCPIP_MSG_DESKRINGINGINFOBROADCAST,			// �Ӿ�̨������Ϣ�㲥����Ҫ�������ӿ�
    TCPIP_MSG_FETCHSVRINFOMATION_REQ,			// ��Ϣ��Ҫ����
    TCPIP_MSG_FETCHSVRINFOMATION_ANS,			// ��Ϣ��Ҫ����
    TCPIP_MSG_CSTALINKSTATE,			// CSTA Link State ״̬�ı���
    TCPIP_MSG_CSTAAGENTSTATE,			// CSTA Agent State ״̬�ı���
    TCPIP_MSG_JJDINFOSHOWTOLEDSYS,
    TCPIP_MSG_INKFECTHSPECIALDNLIST,			// ������Ҫ CK1 CK2 ������ �Ѻ��û��б�
    TCPIP_MSG_LOADSPECIALDNLISTTOSW,			// ������Ҫ CK1 CK2 ������ �Ѻ��û��б�
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
    TCPIP_MSG_NOTETOPCSFORWATCHING,					// �յ��ɵ���Ϣ��,����̨����֪ͨ��Ϣ
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
    TCPIP_MSG_RELAYTOWEBDESK,						// �Ӿ�̨��Ϣת������Ҫ�������ӿ�
    TCPIP_MSG_FETCHALLAGENTINFO,					// ��Ҫ����ϯλ״̬����
    TCPIP_MSG_RECDIDONRECDPORT,						//
    TCPIP_MSG_LIMIT
};


//--------------------------------------------------------------------
//	��/�����
//--------------------------------------------------------------------
class CCommonParameter
{
    BYTE * m_s;
    int    m_Limit;
    int    m_IsBigEndian;
    int    m_WritePos;								// ���ָ��
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
//	һ���ڵ�����
//----------------------------------------------------------------------------------
#define NSECONDSINDAY   (24*3600)
#define glbIsLeapYear(year) ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

//----------------------------------------------------------------------------------
//	ʱ���
//----------------------------------------------------------------------------------
struct CTimeDet
{
    int m_IsNeg;								// 0 �Ǹ�   1 ��
    int m_Days;									// ��������ֵ
    int m_Seconds;								// ������������ֵ
};

//----------------------------------------------------------------------------------
//	����/ʱ��ṹ
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

    int    IsLeapYear();							// �ж��ǲ�������   1 ��  0 ��
    char * FormASCIIString(char * s);						// �����ڱ�� yyyy/mm/dd hh:mm:ss.mmmm ��ʽ
    int    SetValueByASCIIString(char * s);					// ��yyyy/mm/dd hh:mm:ss.mmmm ��ʽ��ʱ���õ��ṹ��
    int    GetAbsDay();								// ����� 1/1/1 �� ָ�����ڵ�����
    int    SetAbsDay(int nDay);							// ����1/1/1 �� ָ�����ڵ������ýṹ�ڵĳ�Ա
    int    GetSecondsInDay();							// ������������
    int    SetSecondsInDay(int nSeconds);					// ��������������ʱ �� ��
    int    CompareTo(CDateAndTime * pDst);					// �Ƚ�����ʱ����Ⱥ�
    int    GetDetTo(CDateAndTime * pDst,CTimeDet * pDet);			// ��������ʱ��Ĳ�
    int    AddDet(CTimeDet * pDet);						// ʱ��ǰ��
    int    SubDet(CTimeDet * pDet);						// ʱ�����
    int    AddDaysAndSeconds(int nDays,int nSeconds);				// ʱ��ǰ��
    int    SubDaysAndSeconds(int nDays,int nSeconds);				// ʱ�����
    int    GetDayInWeek();							// �������� 0 ������  1-6 ���� 1-6
    int    AdjustTime();
    int    ClearTime();
    int    IsValideDate();
    int    ToIntArray(int a[]);
    int    FromIntArray(int a[]);
    int    GetHash();
    char * FormOralceDate(char * s);
};

//---------------------------------------------------------------------------
//	�����ļ�����
//---------------------------------------------------------------------------
struct CCfgData
{
    CCfgData();
    ~CCfgData();
    int     ReadFromFile(char * sFilename);					// ���ļ���ȡ��������
    int     WriteToFile(char * sFilename);					// д�������ļ�
    char *  GetValue(LPCSTR sTagName);						// ȡ����ֵ
    int     SetValue(LPCSTR sTagName,LPCSTR sTagValue);				// ������ֵ
    int     ClearAllData();							// �����������ֵ
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
//	��һ�������һ����������
//	����ȡ����Ԫ�ظ���
//---------------------------------------------------------------------------------------
int glbGetIntegerValueByASCIIString(int a[],int nLimit,const char * s)
{
    int           i,State,n,nBase,d;
    unsigned char c;

    if (s==NULL) return 0;							// ����ǿմ������� 0
    State=0;									// ״̬ 0 ���˿ո�
    n=0;									// ����������ʼΪ 0
    for (i=0;c=s[i];i++)
    switch(State)
    {
    case 0:									// ���ڹ��˿ո񣨷����֣�
	if (c>='0' && c<='9')							// ��������
	{
	    a[n]=c-'0';
	    if (n<nLimit) n++;							// ���ָ����� 1
	    State=1;								// ����״̬ 1
	    if (s[i+1]=='x' || s[i+1]=='X')					// �� 0x ��ͷ�� 16 ����
	    {
		nBase=16;
		i++;
	    }
	    else
	    {
		nBase=10;							// ������ 10 ����
	    }
	}
	break;

    case 1:									// ���ڶ�����
	if (c>='0' && c<='9')							// ����Ȼ������
	{
	    d=c-'0';								// ���������ֵ
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

	if (d>=0)								// �����ֵ
	{
	    a[n-1]=a[n-1]*nBase+d;						// ��������
	}
	else State=0;								// ������������֣��ص�״̬ 0
	break;
    }
    return n;									// ������������
}

//-----------------------------------------------------------------------------------------------------
//	ȡָ�����ָ���·ݵ�����
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
//	׼������
//---------------------------------------------------------------------------
int CCommonParameter::BindString(char * s,int Len,int IsBigEndian)
{
    m_s=(BYTE *)s;								// ��¼������׵�ַ
    m_Limit=Len;								// ����
    m_IsBigEndian=IsBigEndian;							// ˫�ָ�ʽ,��λ���Ȼ��λ����
    m_WritePos=0;								// дָ���� 0
    return 0;
}

//---------------------------------------------------------------------------
//	�Ƿ�����ĩβ
//---------------------------------------------------------------------------
int CCommonParameter::IsEOF()
{
    return (m_Limit<1) ? 1 : 0;							// Limit Ϊ0,��ʾ����ĩβ
}

//---------------------------------------------------------------------------
//	ȡһ���ֽ�
//---------------------------------------------------------------------------
BYTE CCommonParameter::GetBYTE()
{
    BYTE c=0;

    if (m_Limit>=1)								// ����ʣ������һ���ֽ�
    {
	c=m_s[0];								// ȡ��
	m_Limit--;
	m_s++;
    }
    return c;
}

//---------------------------------------------------------------------------
//	ȡһ���� 16 ����
//---------------------------------------------------------------------------
WORD CCommonParameter::GetWORD()
{
    WORD x=0;

    if (m_Limit>=2)								// ����ʣ�����ٶ����ֽ�
    {
	if (m_IsBigEndian)							// ���Ǵ��ģʽ
	{
	    x=(m_s[0]<<8);							// ��λ����
	    x+=m_s[1];
	}
	else									// ����С��ģʽ
	{
	    x=(m_s[1]<<8);							// ��λ�ں�
	    x+=m_s[0];
	}
	m_s+=2;
	m_Limit-=2;
    }
    return x;
}

//---------------------------------------------------------------------------
//	ȡһ��˫�� 32 ����
//---------------------------------------------------------------------------
DWORD CCommonParameter::GetDWORD()
{
    DWORD x=0;

    if (m_Limit>=4)								// �����ٻ�ʣ 4 ���ֽ�
    {
	if (m_IsBigEndian)							// ���Ǵ��ģʽ
	{
	    x=(m_s[0]<<24);							// ��λ����
	    x+=(m_s[1]<<16);
	    x+=(m_s[2]<<8);
	    x+=m_s[3];
	}
	else									// ����С��ģʽ
	{
	    x=(m_s[3]<<24);							// ��λ�ں�
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
//	ȡһ�������ȸ���
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
//	ȡһ��˫������
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
//	ȡһ�� ASCIIZ ��
//---------------------------------------------------------------------------
char * CCommonParameter::GetASCIIZString()
{
    char * s="";
    int k;

    if (m_Limit>=1)								// ����ʣ����һ���ֽ�
    {
	s=(char *)m_s;								// �� s ָ��ǰ����
	k=strlen(s)+1;								// ���㴮��,��β���� 0
	m_s+=k;									// ������ ASCIIZ ��
	m_Limit-=k;
    }
    return s;									// ����ȡ���Ĵ�
}

//---------------------------------------------------------------------------
//	ȡһ���������ֽ���
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
//	ȡʣ�µ��ֽ�
//---------------------------------------------------------------------------
char * CCommonParameter::GetRemainBinBlock(int * Vol)
{
    if (Vol) Vol[0]=m_Limit;							// ��Ҫ����ʣ�µ��ֽ���,���û�ȥ
    return (char *)m_s;								// ���ص�ַ
}

//---------------------------------------------------------------------------
//	ȡ���֮�������
//---------------------------------------------------------------------------
char * CCommonParameter::GetPackedPacket(int * Len)
{
    if (Len) *Len=m_WritePos;							// ��Ҫ���ش���,�ͷ���
    return (char *)m_s;								// ���ذ����ַ
}

//---------------------------------------------------------------------------
//	���ص�ǰ�����ַ
//---------------------------------------------------------------------------
char * CCommonParameter::GetCurrentWriteBuf()
{
    return (char *)m_s+m_WritePos;
}

//---------------------------------------------------------------------------
//	��һ���ֽ�
//---------------------------------------------------------------------------
int CCommonParameter::PutBYTE(BYTE c)
{
    if (m_WritePos<m_Limit)							// ��û��Խ��
    {
	m_s[m_WritePos]=c;							// д��
	m_WritePos++;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	����һ���� 16 ����
//---------------------------------------------------------------------------
int CCommonParameter::PutWORD(WORD x)
{
    if (m_Limit-m_WritePos>=2)							// ������ 2 ���ո�
    {
	if (m_IsBigEndian)							// ���Ǵ��
	{
	    PutBYTE((BYTE)(x>>8));						// �ȷŸ�λ
	    PutBYTE((BYTE)x);
	}
	else									// ����С��
	{
	    PutBYTE((BYTE)x);							// �ȷŵ�λ
	    PutBYTE((BYTE)(x>>8));
	}
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	����һ��˫�� 32 ����
//---------------------------------------------------------------------------
int CCommonParameter::PutDWORD(DWORD x)
{
    if (m_Limit-m_WritePos>=4)							// ������ 4 ���ո�
    {
	if (m_IsBigEndian)							// ���Ǵ��ģʽ
	{
	    PutBYTE((BYTE)(x>>24));						// �ȴ������λ
	    PutBYTE((BYTE)(x>>16));
	    PutBYTE((BYTE)(x>>8));
	    PutBYTE((BYTE)x);
	}
	else									// ����С��
	{
	    PutBYTE((BYTE)x);							// �ȴ������λ
	    PutBYTE((BYTE)(x>>8));
	    PutBYTE((BYTE)(x>>16));
	    PutBYTE((BYTE)(x>>24));
	}
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	����һ�� ASCII ��
//---------------------------------------------------------------------------
int CCommonParameter::PutASCIIZString(const char * s)
{
    return (s==NULL) ? PutBYTE(0) : PutBinDataBlock(s,strlen(s)+1);					// ������ 0 Ҳ����
}

//---------------------------------------------------------------------------
//	����һ���ֽ���
//---------------------------------------------------------------------------
int CCommonParameter::PutBinDataBlock(const char * s,int Len)
{
    if (Len>m_Limit-m_WritePos)
    {
	Len=m_Limit-m_WritePos;
    }
    if (Len>0)// && m_WritePos+Len<=m_Limit)					// ���鲻��,���ܴ����
    {
	memcpy(m_s+m_WritePos,s,Len);						// ����д��
	m_WritePos+=Len;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	�� s �� Len ���ֽڴ���,ռ�� WidthLen �ֽ�,�� 0 ����
//---------------------------------------------------------------------------
int CCommonParameter::PutBinDataFillZeroBlock(const char * s,int Len,int WidthLen)
{
    int k;

    if (m_WritePos+WidthLen<=m_Limit)						// ���ܷŵ���
    {
	if (Len<0) Len=strlen(s);						// Len С�� 0,��ʾ s �� ASCIIZ ��
	memcpy(m_s+m_WritePos,s,Len);						// ���忽��
	k=WidthLen-Len;								// �����Ҳ�Ŀո���
	if (k>0) memset(m_s+m_WritePos+Len,0,k);				// ����,�� 0
	m_WritePos+=WidthLen;
    }
    return m_WritePos;
}

//---------------------------------------------------------------------------
//	ȡ��ǰ���ָ��
//---------------------------------------------------------------------------
int CCommonParameter::GetCurrentWritePos()
{
    return m_WritePos;
}

//-----------------------------------------------------------------------------------------------------
//	�ж��ǲ�������
//	���� 1 ��
//	���� 0 ��
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::IsLeapYear()
{
    return glbIsLeapYear(m_Year);
}

//-----------------------------------------------------------------------------------------------------
//	��ʱ���� yyyy/mm/dd hh:mm:ss.xxx ��ʽ
//-----------------------------------------------------------------------------------------------------
char * CDateAndTime::FormASCIIString(char * s)
{
    sprintf(s,"%d/%02d/%02d %02d:%02d:%02d.%03d",
	m_Year,m_Month,m_Day,m_Hour,m_Minute,m_Second,m_Milisecond);
    return s;
}

//-----------------------------------------------------------------------------------------------------
//	�� yyyy/mm/dd hh:mm:ss.xxx ��ʽ��ʱ��д��ṹ
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SetValueByASCIIString(char * s)
{
    int a[8];
    int n;

    n=glbGetIntegerValueByASCIIString(a,8,s);					// ����д������
    m_Year=(n>=1) ? a[0] : 0;							// д��ṹ
    m_Month=(n>=2) ? a[1] : 0;
    m_Day=(n>=3) ? a[2] : 0;
    m_Hour=(n>=4) ? a[3] : 0;
    m_Minute=(n>=5) ? a[4] : 0;
    m_Second=(n>=6) ? a[5] : 0;
    m_Milisecond=(n>=7) ? a[6] : 0;
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	����� 0001/1/1 ������ָ�����ڵ�����
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetAbsDay()
{
    int y=m_Year-1;								// ǰһ��
    int Days=y/4-y/100+y/400+y*365;						// �� 1/1/1 �� y/12/31 ������
    int i;

    for (i=1;i<m_Month && i<12;i++) Days+=glbGetDaysInMonth(m_Year,i);		// ����ǰ�������ӽ���
    return Days+m_Day;
}

//-----------------------------------------------------------------------------------------------------
//	������ 0001/1/1 ���������������
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SetAbsDay(int nDay)
{
    int y,x;

    m_Month=1;
    m_Day=1;
    for(y=nDay/365+2;y>0;y--)							// nDay/365+2 ����Ĺ���ֵ
    {
	m_Year=y;								// �� y/1/1 ��ʼ��֤
	x=GetAbsDay();								// ���� y/1/1 �ľ�������
	if (nDay>=x) break;							// ��� nDay �� [y/1/1 , ����) ���У��˳�ѭ��
    }
    m_Day+=nDay-x;								// ���� m_Day
    while (m_Day>(y=glbGetDaysInMonth(m_Year,m_Month)))				// �� m_Day ̫��
    {
	m_Day-=y;								// ����һ����
	m_Month++;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	������������
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetSecondsInDay()
{
    return m_Hour*3600+m_Minute*60+m_Second;
}

//-----------------------------------------------------------------------------------------------------
//	�������������� ʱ �� ��
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
//	ʱ��Ƚ�
//	���� -1 this С
//	����  0 ���
//	����  1 this ��
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
//	����ʱ���,�� this-pDst
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
    if (x==y)									// �������
    {
	if (a>=b) pDet->m_Seconds=a-b;						// �����������
	else
	{
	    pDet->m_IsNeg=1;
	    pDet->m_Seconds=b-a;
	}
	return 0;								// ����
    }
    if (x<y)									// ��� this С
    {
	int z;

	z=x;									// �� this �� pDst �Ի�
	x=y;
	y=z;

	z=a;
	a=b;
	b=z;

	pDet->m_IsNeg=1;							// �Ǹ���
    }

    if (a<b)									// ���������������С
    {
	x--;									// ��һ��
	a+=NSECONDSINDAY;
    }
    pDet->m_Days=x-y;								// ����������
    pDet->m_Seconds=a-b;							// �����������
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	����ʱ���
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AddDet(CTimeDet * pDet)
{
    int Days;
    int Seconds;

    if (pDet->m_Days==0 && pDet->m_Seconds==0) return 0;			// ���ʱ���Ϊ 0��ֱ�ӷ���
    if (pDet->m_Seconds>=NSECONDSINDAY)						// ����������̫��
    {
	pDet->m_Days+=pDet->m_Seconds/NSECONDSINDAY;				// ���㵽������
	pDet->m_Seconds %= NSECONDSINDAY;
    }
    Seconds=GetSecondsInDay();							// ������������
    if (pDet->m_IsNeg) Seconds-=pDet->m_Seconds;				// ������������
    else Seconds+=pDet->m_Seconds;
    
    if (pDet->m_Days==0 && Seconds>=0 && Seconds<NSECONDSINDAY)			// �������Ҫ������
    {
	return SetSecondsInDay(Seconds);					// ֱ�ӵ���ʱ����
    }

    Days=GetAbsDay();								// ȡ��������
    if (pDet->m_IsNeg)
    {
	Days-=pDet->m_Days;							// ������������
    }
    else
    {
	Days+=pDet->m_Days;
    }

    if (Seconds<0)								// �����������С�� 0
    {
	Seconds+=NSECONDSINDAY;							// ��һ��
	Days--;
    }

    if (Seconds>=NSECONDSINDAY)							// �����������̫��
    {
	Days+=Seconds/NSECONDSINDAY;						// ����Ӽӵ�����
	Seconds %= NSECONDSINDAY;
    }
    SetAbsDay(Days);								// ����������
    SetSecondsInDay(Seconds);							// ����ʱ����
    return 0;
}

//-----------------------------------------------------------------------------------------------------
//	����ʱ���
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SubDet(CTimeDet * pDet)
{
    CTimeDet p=pDet[0];

    if (p.m_IsNeg) p.m_IsNeg=0;							// �任����
    else p.m_IsNeg=1;

    return AddDet(&p);								// ����ʱ���
}

//-----------------------------------------------------------------------------------------------------
//	����ʱ���
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AddDaysAndSeconds(int nDays,int nSeconds)
{
    CTimeDet p;

    p.m_IsNeg=0;								// ����һ����ʱ���
    p.m_Days=nDays;
    p.m_Seconds=nSeconds;
    return AddDet(&p);								// ����ʱ���
}

//-----------------------------------------------------------------------------------------------------
//	����ʱ���
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::SubDaysAndSeconds(int nDays,int nSeconds)
{
    CTimeDet p;

    p.m_IsNeg=1;								// ����һ����ʱ���
    p.m_Days=nDays;
    p.m_Seconds=nSeconds;
    return AddDet(&p);								// ����ʱ���
}

//-----------------------------------------------------------------------------------------------------
//	��������
//	0 ������
//	1 ����һ
//	6 ������
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::GetDayInWeek()
{
    int nDays=GetAbsDay();							// �����������

    return (nDays+0) % 7;							// ��������
}

//-----------------------------------------------------------------------------------------------------
//	����ʱ��
//	���� 0 ��ʾû�е���
//	���� 1 ��ʾ����
//-----------------------------------------------------------------------------------------------------
int CDateAndTime::AdjustTime()
{
    if (m_Milisecond<1000) return 0;						// ������벿�ֲ��� 1000, �Ͳ��õ���
    m_Milisecond-=1000;								// ���벿�ּ� 1000
    m_Second++;									// ��� 1
    if (m_Second<60) return 0;							// ���� 60, Ҳ����
    m_Second=0;									// ���� 0
    m_Minute++;									// �ּ� 1
    if (m_Minute<60) return 0;							// �ֲ��� 60, Ҳ����
    m_Minute=0;									// ���� 0
    m_Hour++;									// Сʱ�� 1
    if (m_Hour<24) return 0;							// Сʱ���� 24,����
    m_Hour=0;									// Сʱ�� 0
    m_Day++;									// ��� 1
    m_DayOfWeek++;								// ���ڼ� 1
    if (m_DayOfWeek>=7) m_DayOfWeek=0;						// ���ڵ���Ч��Χ�� 0-6
    if (m_Day<=glbGetDaysInMonth(m_Year,m_Month)) return 0;			// ��� �� ���������µ�����,Ҳ����
    m_Day=1;									// ��� 1 ��ʼ
    m_Month++;									// �·ݼ� 1
    if (m_Month<=12) return 0;							// �·ݲ��� 12 Ҳ����
    m_Month=1;									// �� 1 �·ݿ�ʼ
    m_Year++;									// ��� 1
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
//	�����ļ����ƹ���
//----------------------------------------------------------------------------------------------------
CCfgData::CCfgData()
{
    ClearAllData();								// ������Ŀ����Ϊ 0
}

//----------------------------------------------------------------------------------------------------
//	�����ļ���������
//----------------------------------------------------------------------------------------------------
CCfgData::~CCfgData()
{
    ClearAllData();								// �������������Ŀ
}

//----------------------------------------------------------------------------------------------------
//	��һ����ǰ���ո�ͺ����ո�ɾ��
//----------------------------------------------------------------------------------------------------
char * glbPackString(char * s)
{
    int i;
    BYTE c;

    for (i=strlen(s)-1;i>=0;i--)						// ɾ�������ո�
    if ((BYTE)s[i]<=' ') s[i]=0;
    else break;

    for (i=0;c=s[i];i++)							// ɾ��ǰ���ո�
    if (c>' ') break;

    return &s[i];
}

//----------------------------------------------------------------------------------------------------
//	���ļ���ȡ��������
//	ԭ�е����ò����
//----------------------------------------------------------------------------------------------------
int CCfgData::ReadFromFile(char * sFilename)
{
    FILE * fd;
    char sBuffer[0x1000];
    int i;
    BYTE c;

    fd=fopen(sFilename,"r");							// ���ļ�
    if (fd==NULL)
    {
	return -1;								// ��ʧ��,���� -1
    }
    while (fgets(sBuffer,sizeof(sBuffer),fd))					// ���ļ���һ��
    {
	for (i=0;c=sBuffer[i];i++)						// �ڸ�����Ѱ���״γ��ֵ� '='
	if (c=='=')
	{
	    sBuffer[i]=0;
	    SetValue(glbPackString(&sBuffer[0]),glbPackString(&sBuffer[i+1]));	// �洢����Ŀ
	    break;
	}
    }
    fclose(fd);									// �ر��ļ�
    return 0;
}

//----------------------------------------------------------------------------------------------------
//	����������д���ļ�
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
//	ȡָ����ֵ
//	���������,���� NULL
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
//	��ֵ
//----------------------------------------------------------------------------------------------------
int CCfgData::SetValue(LPCSTR sTagName,LPCSTR sTagValue)
{
    int i;

    for (i=0;i<m_Count;i++)
    if (strcmp(m_Tagnames[i],sTagName)==0)					// ��������Ѵ���
    {
//	free(m_Tagvalues[i]);							// ɾ����ֵ
	m_Tagvalues[i]=StoreString(sTagValue);					// ������ֵ
	return i;
    }
    i=m_Count;									// ���������
    m_Count++;
    m_Tagnames[i]=StoreString(sTagName);					// ����
    m_Tagvalues[i]=StoreString(sTagValue);					// ֵ��Ҫ�洢
    return i;
}

//----------------------------------------------------------------------------------------------------
//	������е���Ŀ
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
//	��һ�����ĵ�β������ 0D
//	�м�Ҫ���� 0D==>0E 02
//		   0E==>0E 01
//                 �任
//	���غ� 0D �ĳ���
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
//	�ѱ����� 0E 02==>0D
//		 0E 01==>0E
//	���ر任��ĳ���
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
    m=vsprintf(ss,Format,marker);				// д�뻺����
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
    m=vsprintf(ss,Format,marker);				// д�뻺����
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
    m=vsprintf(ss,Format,marker);				// д�뻺����
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

    va_start(marker,Format);							// �ӵ�һ��������ʼ
    m=vsprintf(ss,Format,marker);				// д�뻺����
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
