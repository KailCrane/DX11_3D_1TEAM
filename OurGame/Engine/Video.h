#pragma once
#include "Object.h"

namespace hm
{
	class Video :
		public Object
	{
	public:
		Video();
		virtual ~Video();
		// Resources�� ���� ȣ��Ǹ� �ܺ� �̹����� �ε��ϴ� �Լ�
		virtual void Load(const wstring& _path) override;

	public:
		void Play();
		

	private:
		wstring mPath;
	};
}


