#pragma once

namespace RF {
	struct FrameData;

	class IRenderer {
	public:
		virtual ~IRenderer() {}
		virtual void Render(const FrameData& frameData) = 0;
	};
}