#include "shared_stdafx.h"

#include <io.h>
#include <fmod.h>
#include "SoundMgr.h"
#pragma comment (lib, "fmod_vc.lib")

#include <filesystem>
namespace fs = std::filesystem;

#include <atlconv.h>

SoundMgr* SoundMgr::g_pInstance = nullptr;
SoundMgr::SoundMgr()
{
	m_pSystem = nullptr;
}


SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem, FMOD_VERSION);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 64, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}
void SoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		FMOD_Sound_Release(Mypair.second);
	}

	m_mapSound.clear();

	if (m_pSystem)
	{
		FMOD_System_Release(m_pSystem);
		FMOD_System_Close(m_pSystem);
		m_pSystem = nullptr;
	}
}

void SoundMgr::Play(const wchar_t* pSoundKey, CHANNELID eID, bool loop)
{
	auto& i = *g_pInstance;

	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(i.m_mapSound.begin(), i.m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == i.m_mapSound.end())
		return;

	FMOD_Channel_Stop(i.m_pChannelArr[eID]);

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(i.m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(i.m_pSystem, iter->second, NULL, FALSE, &i.m_pChannelArr[eID]);
	}
	FMOD_Channel_SetMode(i.m_pChannelArr[eID], loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	FMOD_System_Update(i.m_pSystem);
}

void SoundMgr::PlayContinue(const wchar_t* pSoundKey, CHANNELID eID)
{
	auto& i = *g_pInstance;

	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(i.m_mapSound.begin(), i.m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == i.m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(i.m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(i.m_pSystem, iter->second, NULL, FALSE, &i.m_pChannelArr[eID]);
	}
	FMOD_System_Update(i.m_pSystem);
}

void SoundMgr::SetVolume(float volume, CHANNELID eID)
{
	auto& i = *g_pInstance;
	FMOD_Channel_SetVolume(i.m_pChannelArr[eID], volume);
	FMOD_System_Update(i.m_pSystem);
}

void SoundMgr::PlayBGM(const wchar_t* pSoundKey)
{
	auto& i = *g_pInstance;

	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(i.m_mapSound.begin(), i.m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == i.m_mapSound.end())
		return;

	FMOD_System_PlaySound(i.m_pSystem, iter->second, NULL, FALSE, &i.m_pChannelArr[BGM]);
	FMOD_Channel_SetMode(i.m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(i.m_pSystem);
}

void SoundMgr::StopSound(CHANNELID eID)
{
	auto& i = *g_pInstance;

	FMOD_Channel_Stop(i.m_pChannelArr[eID]);
	FMOD_Channel_SetMode(i.m_pChannelArr[eID], FMOD_LOOP_OFF);
	FMOD_System_Update(i.m_pSystem);
}

void SoundMgr::StopAll()
{
	auto& inst = *g_pInstance;

	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(inst.m_pChannelArr[i]);
}

bool SoundMgr::IsPlaying(CHANNELID eID)
{
	auto& i = *g_pInstance;

	FMOD_BOOL bPlay = FALSE;
	FMOD_Channel_IsPlaying(i.m_pChannelArr[eID], &bPlay);

	return bPlay;
}

bool SoundMgr::IsPlaying(const wchar_t* pSoundKey, CHANNELID eID)
{
	auto& i = *g_pInstance;

	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(i.m_mapSound.begin(), i.m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == i.m_mapSound.end())
		return false;

	FMOD_BOOL bPlay = FALSE;
	FMOD_Channel_IsPlaying(i.m_pChannelArr[eID], &bPlay);

	if (!bPlay)
	{
		return false;
	}

	FMOD_SOUND* current = nullptr;
	FMOD_Channel_GetCurrentSound(i.m_pChannelArr[eID], &current);

	if (current == iter->second)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SoundMgr::LoadSoundFile()
{
	std::vector<std::wstring> filePathes;
	fs::path begin = L"../SharedResource/Sound/";

	if (!fs::exists(begin))
	{
		return;
	}

	for (const fs::directory_entry& entry : fs::recursive_directory_iterator(begin))
	{
		const auto& path = entry.path();
		if (!fs::is_directory(path))
		{
			std::wstring wstrPath = path;
			std::replace(wstrPath.begin(), wstrPath.end(), L'\\', L'/');
			filePathes.push_back(wstrPath);
		}
	}

	auto ToString = [&](const wstring& wstr) -> string
	{
		USES_CONVERSION;
		return string(W2A(wstr.c_str()));
	};

	for (auto& wstrPath : filePathes)
	{
		string strPath = ToString(wstrPath);

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, strPath.c_str(), FMOD_CREATESAMPLE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			m_mapSound.emplace(wstrPath, pSound);
		}
	}

	FMOD_System_Update(m_pSystem);
}
