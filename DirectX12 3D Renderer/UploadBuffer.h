#ifndef UPLOADBUFFER_H
#define UPLOADBUFFER_H
#include "d3dUtil.h"

namespace DirectX3DRenderer {
	template<class T> 
	class UploadBuffer
	{
	public:
		UploadBuffer(ID3D12Device* device, UINT elementCount, bool isConstantBuffer) : 
			mIsConstantBuffer(isConstantBuffer)
		{
			if (isConstantBuffer)
				mElementByteSize = D3DUtil::CalcConstantBufferByteSize(sizeof(T));
			else
				mElementByteSize = sizeof(T);

			ThrowIfFailed(
				device->CreateCommittedResource(
					&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
					D3D12_HEAP_FLAG_NONE,
					&CD3DX12_RESOURCE_DESC::Buffer(mElementByteSize * elementCount),
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(&mUploadBuffer))
			);
			ThrowIfFailed(mUploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mMappedData)));
		}

		UploadBuffer(const UploadBuffer& rhs) = delete;
		UploadBuffer operator=(const UploadBuffer& rhs) = delete;
		~UploadBuffer()
		{
			if (mUploadBuffer != nullptr)
				mUploadBuffer->Unmap(0, nullptr);
			mMappedData = nullptr;
		}

		ID3D12Resource* Resource()
		{
			return mUploadBuffer.Get();
		}

		void CopyData(int elementIndex, const T& data)
		{
			memcpy(&mMappedData[elementIndex * mElementByteSize], &data, sizeof(T));
		}

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> mUploadBuffer;
		BYTE* mMappedData;
		bool mIsConstantBuffer;
		UINT mElementByteSize;
	};
}
#endif // !UPLOADBUFFER_H
