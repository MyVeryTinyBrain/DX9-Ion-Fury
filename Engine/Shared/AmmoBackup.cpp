#include "shared_stdafx.h"
#include "AmmoBackup.h"

ImplementSingletone(AmmoBackup);

void AmmoBackup::Backup()
{
	m_backupData = m_currentData;
}

AmmoBackupData* AmmoBackup::GetCurrentData()
{
	return &m_currentData;
}

const AmmoBackupData* AmmoBackup::GetBackupData() const
{
	return &m_backupData;
}
