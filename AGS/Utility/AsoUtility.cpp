#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <DxLib.h>
#include "AsoUtility.h"

int AsoUtility::Round(float v)
{
    return 0;
}

std::vector<std::string> AsoUtility::Split(std::string& line, char delimiter)
{
    return std::vector<std::string>();
}

double AsoUtility::Rad2DegD(double rad)
{
    return 0.0;
}

float AsoUtility::Rad2DegF(float rad)
{
    return 0.0f;
}

int AsoUtility::Rad2DegI(int rad)
{
    return 0;
}

double AsoUtility::Deg2RadD(double deg)
{
    return 0.0;
}

float AsoUtility::Deg2RadF(float deg)
{
    return deg * (DX_PI_F / 180.0f);
}

int AsoUtility::Deg2RadI(int deg)
{
    return 0;
}

double AsoUtility::DegIn360(double deg)
{
    return 0.0;
}

double AsoUtility::RadIn2PI(double rad)
{
    return 0.0;
}

int AsoUtility::DirNearAroundRad(float from, float to)
{
    return 0;
}

int AsoUtility::DirNearAroundDeg(float from, float to)
{
    return 0;
}

int AsoUtility::Lerp(int start, int end, float t)
{
    return 0;
}

float AsoUtility::Lerp(float start, float end, float t)
{
    return 0.0f;
}

double AsoUtility::Lerp(double start, double end, double t)
{
    return 0.0;
}

VECTOR AsoUtility::Lerp(const VECTOR& start, const VECTOR& end, float t)
{
    return VECTOR();
}

double AsoUtility::LerpDeg(double start, double end, double t)
{
    return 0.0;
}

COLOR_F AsoUtility::Lerp(const COLOR_F& start, const COLOR_F& end, float t)
{
    return COLOR_F();
}

VECTOR AsoUtility::Bezier(const VECTOR& p1, const VECTOR& p2, const VECTOR& p3, float t)
{
    return VECTOR();
}

VECTOR AsoUtility::RotXZPos(const VECTOR& centerPos, const VECTOR& radiusPos, float rad)
{
    return VECTOR();
}

double AsoUtility::Magnitude(const VECTOR& v)
{
    return 0.0;
}

float AsoUtility::MagnitudeF(const VECTOR& v)
{
    return 0.0f;
}

float AsoUtility::SqrMagnitudeF(const VECTOR& v)
{
    return 0.0f;
}

double AsoUtility::SqrMagnitude(const VECTOR& v)
{
    return 0.0;
}

double AsoUtility::SqrMagnitude(const VECTOR& v1, const VECTOR& v2)
{
    return 0.0;
}

double AsoUtility::Distance(const VECTOR& v1, const VECTOR& v2)
{
    return 0.0;
}

bool AsoUtility::IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2)
{
    return false;
}

bool AsoUtility::IsHitSphereCapsule(const VECTOR& sphPos, float sphRadius, const VECTOR& capPos1, const VECTOR& capPos2, float capRadius)
{
    return false;
}

bool AsoUtility::Equals(const VECTOR& v1, const VECTOR& v2)
{
    if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
    {
        return true;
    }
    return false;
}

bool AsoUtility::EqualsVZero(const VECTOR& v1)
{
    const VECTOR& v2 = VECTOR_ZERO;
    if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
    {
        return true;
    }
    return false;
}

VECTOR AsoUtility::VNormalize(const VECTOR& v)
{
    return VECTOR();
}

double AsoUtility::AngleDeg(const VECTOR& from, const VECTOR& to)
{
    return 0.0;
}

void AsoUtility::DrawLineDir(const VECTOR& pos, const VECTOR& dir, int color, float len)
{
}

