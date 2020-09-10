#include "Registry.h"

namespace regedit
{
	bool CreateRegistryKey(const std::wstring& wstring, HKEY hKeyParent)
	{
		DWORD dwDisposition;
		HKEY hKey;
		DWORD ret;

		ret = RegCreateKeyEx(hKeyParent, wstring.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &hKey, &dwDisposition);

		if (ret != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return false;
		}

		RegCloseKey(hKey);
		return true;
	}

	bool WriteInRegistry(const std::wstring& subkey, const std::wstring& valueName, DWORD data, HKEY hKeyParent)
	{
		DWORD ret;
		HKEY hKey;

		ret = RegOpenKeyEx(hKeyParent, subkey.c_str(), 0, KEY_WRITE, &hKey);

		if (ret == ERROR_SUCCESS)
		{
			// set the key
			if (ERROR_SUCCESS != RegSetValueEx(hKey, valueName.c_str(), 0, REG_DWORD, reinterpret_cast<BYTE*>(&data), sizeof(data)))
			{
				RegCloseKey(hKey);
				return false;
			}

			RegCloseKey(hKey);
			return true;
		}

		return false;
	}
}