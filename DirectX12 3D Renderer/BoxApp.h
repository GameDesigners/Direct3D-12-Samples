#ifndef BOXAPP_H
#define BOXAPP_H
#include "d3dApplication.h"

namespace DirectX3DRenderer {
	class BoxApp : D3DApplication
	{
		BoxApp(HINSTANCE hInstance) : D3DApplication(hInstance) {}
		BoxApp(const BoxApp& rhs) = delete;
		BoxApp operator=(const BoxApp& rhs) = delete;
		virtual ~BoxApp() {}

		virtual bool Initialize() override;

	private:
		virtual void OnResize() override;
		virtual void Update(const GameTimer& timer) override;
		virtual void Draw(const GameTimer& timer) override;

		virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
		virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
		virtual void OnMouseMove(WPARAM btnState, int x, int y)override;


	};
}


#endif // !BOXAPP_H
