#include <DxLib.h>
#include "Grid.h"

Grid::Grid(void)
{
}

Grid::~Grid(void)
{
}

void Grid::Init(void)
{
}

void Grid::Update(void)
{
}

void Grid::Draw(void)
{
	for (int z = -10; z < 10; z++)
	{
		VECTOR startXPos = { -500.0f, 0.0f, static_cast<float>(z * 50) };
		VECTOR endXPos = { 500.0f, 0.0f,  static_cast<float>(z * 50) };
		DrawLine3D(startXPos, endXPos, 0xff0000);
		DrawSphere3D(endXPos, 20.0f, 10, 0xff0000, 0xff0000, true);
	}
	for (int x = -10; x < 10; x++)
	{
		VECTOR startZPos = { static_cast<float>(x * 50), 0.0f, -500.0f };
		VECTOR endZPos = { static_cast<float>(x * 50), 0.0f, 500.0f };
		DrawLine3D(startZPos, endZPos, 0x0000ff);
		DrawSphere3D(endZPos, 20.0f, 10, 0x0000ff, 0x0000ff, true);
	}
}

void Grid::Release(void)
{
}