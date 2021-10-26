#pragma once

struct AmmoBackupData
{
	int revolverLoadedAmmo = 0;

	int revolverTotalAmmo = 0;

	int smgLeftLoadedAmmo = 0;

	int smgRightLoadedAmmo = 0;

	int smgTotalAmmo = 0;

	int shotgunLoadedAmmo = 0;

	int shotgunTotalAmmo = 0;

	int launcherLoadedAmmo = 0;

	int launcherTotalAmmo = 0;

	int chaingunTotalAmmo = 0;

	int bowLoadedAmmo = 0;

	int bowTotalAmmo = 0;

	int weaponIndex = 0;
};

class AmmoBackup
{
	DeclareSingletone(AmmoBackup);

public:

	void Backup();

	AmmoBackupData* GetCurrentData();

	const AmmoBackupData* GetBackupData() const;

	__declspec(property(get = GetCurrentData)) AmmoBackupData* current;

	__declspec(property(get = GetBackupData)) const AmmoBackupData* backup;

private:

	AmmoBackupData m_currentData;

	AmmoBackupData m_backupData;
};

