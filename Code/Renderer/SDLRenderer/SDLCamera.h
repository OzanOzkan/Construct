#pragma once

#include <System/ISystem.h>
#include <Renderer/ICamera.h>

class CSDLCamera : public ICamera
{
public:
	CSDLCamera(ISystem* systemContext);

	// ICamera
	void SetPosition(const Vector2& position) override;
	const Vector2& GetPosition() override;
	void SetZoomLevel(const float& zoomLevel) override;
	float GetZoomLevel() override;
	void SetSize(const float& width, const float& height) override;
	void GetSize(float& width, float& height) override;
	// ~ICamera

private:
	ISystem* GetSystem() { return m_pSystem; }

private:
	ISystem* m_pSystem;
	Vector2 m_position;
	float m_zoomLevel;
	float m_width;
	float m_height;
};