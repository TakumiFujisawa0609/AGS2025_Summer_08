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
		VECTOR startXPos = { -500.0f, 0.0f, static_cast<float>(z * 100) };
		VECTOR endXPos = { 1500.0f, 0.0f,  static_cast<float>(z * 100) };
		DrawLine3D(startXPos, endXPos, 0xff0000);

		VECTOR startZPos = { static_cast<float>(z * 100), 0.0f, -500.0f };
		VECTOR endZPos = { static_cast<float>(z * 100), 0.0f, -1500.0f };
		DrawLine3D(startZPos, endZPos, 0xff0000);
	}
}

void Grid::Release(void)
{
}