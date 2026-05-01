#pragma once

namespace RF {
	struct FrameData;

	class IRenderer {
	public:
		virtual ~IRenderer() {}
		virtual void Init(const HWND hwnd, const uint32_t width, const uint32_t height) = 0;
		virtual void Render(const FrameData& frameData) = 0;
	};
}