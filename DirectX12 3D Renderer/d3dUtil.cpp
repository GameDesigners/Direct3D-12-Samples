#include "d3dUtil.h"

DirectX3DRenderer::DXException::DXException(HRESULT hr, const std::wstring& functionName, const std::wstring& fileName, int lineNumber) :
	mErrorCode(hr),
	mFunctionName(functionName),
	mFileName(fileName),
	mLineNumber(lineNumber) {}

std::wstring DirectX3DRenderer::DXException::ToString() const
{
	_com_error err(mErrorCode);
	std::wstring msg = err.ErrorMessage();
	return mFunctionName + L"failed in " + mFileName + L",line " + std::to_wstring(mLineNumber) + L", error: " + msg;
}

