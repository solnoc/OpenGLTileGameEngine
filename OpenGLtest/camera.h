#pragma once

class Camera
{
public:
	Camera(int screenWidth, int screenHeight, int tileWidth, int tileHeight, int extraTilesToDrawX, int extraTilesToDrawY, int cameraX = 0, int cameraY = 0, float offsetX = 0.0f, float offsetY = 0.0f);
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;

	void setCamera(int cameraX, int cameraY, float offSetX = 0.0f, float offSetY = 0.0f);
	void moveCamera(float offSetX, float offSetY);

	void clipCamera();

	void setScreenBounds(int ScreenBoundX, int ScreenBoundY);

	int CameraX() const;
	int CameraY() const;

	float OffsetX() const;
	float OffsetY() const;

	float ExtraTilesToDrawX() const;
	float ExtraTilesToDrawY() const;

	int VisibleTilesX() const;
	int VisibleTilesY() const;

	int TileWidth() const;
	int TileHeight() const;

	int ScreenWidth() const;
	int ScreenHeight() const;


private:
	int screenWidth;
	int screenHeight;

	int screenBoundX;
	int screenBoundY;

	int tileHeight;
	int tileWidth;

	int cameraX;
	int cameraY;

	int visibleTilesX;
	int visibleTilesY;

	float offSetX;
	float offSetY;

	float extraTilesToDrawX;
	float extraTilesToDrawY;
};