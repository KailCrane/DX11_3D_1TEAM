#pragma once
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include "EnginePch.h"
#include "Engine.h"
#include "ClientEnum.h"

#pragma comment(lib, "Engine.lib")
using namespace hm;
#define IDS_APP_TITLE			103
#define IDR_MAINFRAME			128
#define IDD_CLIENT_DIALOG	102
#define IDM_EXIT				105
#define IDI_CLIENT			107
#define IDI_SMALL				108
#define IDC_CLIENT			109
#define IDC_STATIC                      -1


static Vec3 ConvertDir(DirectionEvasion _dir)
{

	Vec3 forwardDir = Vec3(0, 0, 1);
	Vec3 BackwardDir = Vec3(0, 0, -1);
	Vec3 LeftwardDir = Vec3(-1, 0, 0);
	Vec3 RightwardDir = Vec3(1, 0, 0);

	Vec3 totalDir = {};

	if (_dir == DirectionEvasion::FORWARD)
	{
		totalDir = forwardDir;
	}
	if (_dir == DirectionEvasion::BACKWARD)
	{
		totalDir = BackwardDir;
	}
	if (_dir == DirectionEvasion::LEFT)
	{
		totalDir = LeftwardDir;
	}
	if (_dir == DirectionEvasion::RIGHT)
	{
		totalDir = RightwardDir;
	}
	if (_dir == DirectionEvasion::TOPLEFT)
	{
		totalDir = (forwardDir + LeftwardDir) ;
	}
	if (_dir == DirectionEvasion::TOPRIGHT) 
	{
		totalDir = (forwardDir + RightwardDir);
	}
	if (_dir == DirectionEvasion::BOTTOMLEFT)
	{
		totalDir = (BackwardDir + LeftwardDir);
	}
	if (_dir == DirectionEvasion::BOTTOMRIGHT)
	{
		totalDir = (BackwardDir + RightwardDir);
	}
	return totalDir;
}

static Vec3 ConvertRot(DirectionEvasion _dir)
{

	Vec3 totalRot = {};

	if (_dir == DirectionEvasion::FORWARD)
	{
		totalRot = Vec3(0.f, 180.f, 90.f);
	}
	if (_dir == DirectionEvasion::BACKWARD)
	{
		totalRot = Vec3(0.f, 0.f, 90.f);
	}
	if (_dir == DirectionEvasion::LEFT)
	{
		totalRot = Vec3(0.f, 90.f, 90.f);
	}
	if (_dir == DirectionEvasion::RIGHT)
	{
		totalRot = Vec3(0.f, -90.f, 90.f);
	}
	if (_dir == DirectionEvasion::TOPLEFT)
	{
		totalRot = Vec3(0.f, 135.f, 90.f);
	}
	if (_dir == DirectionEvasion::TOPRIGHT)
	{
		totalRot = Vec3(0.f, 225.f, 90.f);
	}
	if (_dir == DirectionEvasion::BOTTOMLEFT)
	{
		totalRot = Vec3(0.f, 45.f, 90.f);
	}
	if (_dir == DirectionEvasion::BOTTOMRIGHT)
	{
		totalRot = Vec3(0.f, 315.f, 90.f);
	}
	return totalRot;

}
