#pragma once

#include <Windows.h>
#include <string>

/*
* https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa
* Usage of CreateRegistryKey
* @param1: HKEY => A handle to an open registry key such as "HKEY_CLASSES_ROOT" or "HKEY_CURRENT_CONFIG" or "HKEY_CURRENT_USER"
* @param2: lpSubkey => The name of a subkey that this function opens or creates
* @param3: Reserved => This parameter cannot be NULL.
* @param4: lpClass => The user-defined class type of this key. This parameter may be ignored. This parameter can be NULL.
* @param5: dwOptions => This parameter can be one of the following values: 
*/

namespace regedit
{
	bool CreateRegistryKey(const std::wstring& wstring, HKEY hKeyParent = HKEY_CURRENT_USER);

	bool WriteInRegistry(const std::wstring& subkey, const std::wstring& valueName, DWORD data, HKEY hKeyParent = HKEY_CURRENT_USER);
}