#include "pch.h"
#include "Video.h"
#include "Engine.h"
namespace hm
{
	Video::Video()
		: Object(ObjectType::Video)
	{
	}
	Video::~Video()
	{
	}
	void Video::Load(const wstring& _path)
	{
		mPath = _path;
		bool bExists = fs::exists(_path);
		AssertEx(bExists, L"Video::Load() - �������� �ʴ� ���");
	}
	void Video::Play()
	{
		HRESULT hr = VBUILDER->RenderFile(mPath.c_str(), NULL);

		if (SUCCEEDED(hr))
		{
			VWINDOW->put_Left(0);
			VWINDOW->put_Top(0);

			VWINDOW->put_FullScreenMode(OATRUE);

			hr = VCONTROL->Run();
			if (SUCCEEDED(hr))
			{
				long ev;
				VEVENT->WaitForCompletion(INFINITE, &ev);
			}
		}

		else
		{
			AssertEx(false, L"Video::Play() - ������ ������ �� ���� (��� ������ ���ɼ� ����)");
		}

	}
}