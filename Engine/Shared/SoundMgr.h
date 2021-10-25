#pragma once
struct FMOD_SOUND;
struct FMOD_CHANNEL;
struct FMOD_SYSTEM;

enum CHANNELID
{
	BGM,

	PLAYER_FOOTSTEP,
	PLAYER_FOOTSTEP_JUMP,
	PLAYER_FOOTSTEP_LAND,
	PLAYER_WEAPON_FIRE0,
	PLAYER_WEAPON_FIRE1,
	PLAYER_WEAPON_FIRE2,
	PLAYER_WEAPON_FIRE3,
	PLAYER_WEAPON_FIRE4,
	PLAYER_WEAPON_FIRE5,
	PLAYER_WEAPON_FIRE6,
	PLAYER_WEAPON_FIRE7,
	PLAYER_WEAPON_FIRE8,
	PLAYER_WEAPON_FIRE9,
	PLAYER_WEAPON_FIRE10,
	PLAYER_WEAPON_FIRE11,
	PLAYER_WEAPON_FIRE12,
	PLAYER_WEAPON_FIRE13,
	PLAYER_WEAPON_FIRE14,
	PLAYER_WEAPON_RELOAD,
	PLAYER_WEAPON_SUBCHANNEL,
	PLAYER_PROJECTILE,
	PLAYER_EXPLOSION,

	ITEM,

	OBJECT_INPUT,
	OBJECT,

	DEACONATTACK,
	DEACONMOVE,
	DEACONHIT,
	DEACONDEAD,
	BASICMUTANTCREATE,
	BASICMUTANTHIT,
	BASICMUTANTATTACK,
	BASICMUTATNTDEAD,
	MUTANTCREATE,
	MUTANTHIT,
	MUTANTATTACK,
	MUTATNTDEAD,

	DRONE,
	DRONE_SHOOT,
	SPIDER,
	WARMECH,
	WARMECH_WALK,
	WENDIGO,

	MAXCHANNEL
};

class SoundMgr
{
public:
	static SoundMgr* Get_Instance()
	{
		if (nullptr == g_pInstance)
			g_pInstance = new SoundMgr;

		return g_pInstance;
	}
	static void Destroy_Instance()
	{
		if (g_pInstance)
		{
			delete g_pInstance;
			g_pInstance = nullptr;
		}
	}

private:
	SoundMgr();
	~SoundMgr();

public:
	void Initialize();

	void Release();
public:
	static void Play(const wchar_t* pSoundKey, CHANNELID eID, bool loop = false);
	static void PlayContinue(const wchar_t* pSoundKey, CHANNELID eID);
	static void PlayBGM(const wchar_t* pSoundKey);
	static void StopSound(CHANNELID eID);
	static void StopAll();
	static bool IsPlaying(CHANNELID eID);
	static bool IsPlaying(const wchar_t* pSoundKey, CHANNELID eID);

private:
	void LoadSoundFile();

private:
	static SoundMgr* g_pInstance;
	// ���� ���ҽ� ������ ���� ��ü 
	std::map<wstring, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;
};

