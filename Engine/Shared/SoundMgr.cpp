#include "shared_stdafx.h"

#include <io.h>
#include <fmod.h>
#include "SoundMgr.h"
#pragma comment (lib, "fmod_vc.lib")

#include <filesystem>
namespace fs = std::filesystem;

#include <atlconv.h>

CSoundMgr* CSoundMgr::m_pInstance = nullptr;
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	FMOD_System_Create(&m_pSystem, FMOD_VERSION);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();
}
void CSoundMgr::Release()
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

void CSoundMgr::Play(const wchar_t* pSoundKey, CHANNELID eID)
{
	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, iter->second, NULL, FALSE, &m_pChannelArr[eID]);
	}
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(const wchar_t* pSoundKey)
{
	std::map<wstring, FMOD_SOUND*>::iterator iter;

	iter = std::find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
		{
			return iter.first == pSoundKey;
		});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, iter->second, NULL, FALSE, &m_pChannelArr[BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::LoadSoundFile()
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
