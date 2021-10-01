#include "stdafx.h"
#include "Releaser.h"

void Releaser::Update()
{
	if (Input::GetKeyDown(Key::Space) && !m_target.IsNull())
	{
		m_target->ReleaseUnmanaged();
	}
}
