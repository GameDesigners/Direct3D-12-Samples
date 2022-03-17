#ifndef D3DUTIL_H
#define D3DUTIL_H

#include <windows.h>
#include <windowsx.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <comdef.h>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <stdlib.h>

#include "d3dx12.h"


namespace DirectX3DRenderer {

	class D3DUtil
	{
	public:
		/// <summary>
		/// 计算缓冲常量需要分配的大小
		///【涉及要求：常量缓冲分配大小必须是最小硬件的倍数（通常为256字节）】
		/// </summary>
		/// <param name="byteSize"></param>
		/// <returns></returns>
		static UINT CalcConstantBufferByteSize(UINT byteSize)
		{
			// 本函数就是为了 Floor(byteSize+255) 
			// 256 即为2^8，因此我们需要+256后掩后八位即可

			return (byteSize + 255) & (~255);
		}

		static Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const std::wstring& fileName, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);

		static Microsoft::WRL::ComPtr<ID3D12Resource> GetDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer);
	};

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

	struct SubmeshGeometry
	{
		UINT IndexCount = 0;
		UINT StartIndexLocation = 0;
		INT BaseVertexLocation = 0;
	};

	struct MeshGeometry
	{
		std::string Name;

		Microsoft::WRL::ComPtr<ID3DBlob> VertexBufferCPU = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> IndexBufferCPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;

		Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;
		Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

		UINT VertexByteStride = 0;
		UINT VertexBufferByteSize = 0;
		DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
		UINT IndexBufferByteSize = 0;

		std::unordered_map<std::string, SubmeshGeometry> DrawArgs;

		D3D12_VERTEX_BUFFER_VIEW VertexBufferView() const
		{
			D3D12_VERTEX_BUFFER_VIEW vbv;
			vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
			vbv.StrideInBytes = VertexByteStride;
			vbv.SizeInBytes = VertexBufferByteSize;
			return vbv;
		}

		D3D12_INDEX_BUFFER_VIEW IndexBufferView() const
		{
			D3D12_INDEX_BUFFER_VIEW ibv;
			ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
			ibv.Format = IndexFormat;
			ibv.SizeInBytes = IndexBufferByteSize;
			return ibv;
		}

		void DisposeUnloaders()
		{
			VertexBufferUploader = nullptr;
			IndexBufferUploader = nullptr;
		}

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

