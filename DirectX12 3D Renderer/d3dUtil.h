#ifndef D3DUTIL_H
#define D3DUTIL_H

#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <comdef.h>
#include <vector>
#include <string>
#include <cassert>
#include <stdlib.h>

#include "d3dx12.h"


namespace DirectX3DRenderer {

	class DXException
	{
	public:
		DXException() = default;
		DXException(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber);
		
		std::wstring ToString() const;

		HRESULT mErrorCode = S_OK;
		std::wstring mFunctionName;
		std::wstring mFileName;
		int mLineNumber = 0;
	};








	/// <summary>
	/// 将Ansi字符串转化为wstring
	/// </summary>
	/// <param name="str">char类型字符串</param>
	/// <returns></returns>
	inline std::wstring AnsiToWString(const std::string& str)
	{
		WCHAR buffer[512];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
		return std::wstring(buffer);
	}

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)    \
{ \
    HRESULT hr__(x); \
    std::wstring wfn = AnsiToWString(__FILE__); \
    if (FAILED(hr__)) { throw DXException(hr__, L#x, wfn, __LINE__); } \
}
#endif

#ifndef ReleaseCom
#define ReleaseCom(x) {if(x) {x->Release();x=0;}}
#endif

}
#endif // D3DUTIL_H

