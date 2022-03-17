#ifndef INITDIRECT3DAPP
#define INITDIRECT3DAPP
#include <DirectXColors.h>
#include "d3dApplication.h"
using namespace DirectX;

namespace DirectX3DRenderer
{
	class InitDirect3DApp : public D3DApplication
	{
	public:
		InitDirect3DApp(HINSTANCE hInstance) :D3DApplication(hInstance) {}
		virtual ~InitDirect3DApp() {}

		virtual bool Initialize()
		{
			return D3DApplication::Initialize();
		}

	private:
		virtual void OnResize() override { D3DApplication::OnResize(); }
		virtual void Update(const GameTimer& timer) override {}
		virtual void Draw(const GameTimer& timer) override
		{
			ThrowIfFailed(mDirectCmadListAlloc->Reset());
			ThrowIfFailed(mCommandList->Reset(mDirectCmadListAlloc.Get(), nullptr));
			mCommandList->ResourceBarrier(
				1,
				&CD3DX12_RESOURCE_BARRIER::Transition(
					CurrentBackBuffer(),
					D3D12_RESOURCE_STATE_PRESENT,
					D3D12_RESOURCE_STATE_RENDER_TARGET
				)
			);

			mCommandList->RSSetViewports(1, &mScreenViewport);
			mCommandList->RSSetScissorRects(1, &mScissorRect);
			mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::BlueViolet, 0, nullptr);
			mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
			mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

			mCommandList->ResourceBarrier(
				1,
				&CD3DX12_RESOURCE_BARRIER::Transition(
					CurrentBackBuffer(),
					D3D12_RESOURCE_STATE_RENDER_TARGET,
					D3D12_RESOURCE_STATE_PRESENT
				)
			);

			ThrowIfFailed(mCommandList->Close());
			ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
			mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
			ThrowIfFailed(mSwapChain->Present(0, 0));
			mCurrentBuffer = (mCurrentBuffer + 1) % SwapChainBufferCount;
			FlushCommandQueue();
		}
	};
}
#endif // !INITDIRECT3DAPP