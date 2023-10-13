#include "pch.h"
#include "HeadText.h"
#include "Player.h"
#include "Timer.h"
#include "UIText.h"

namespace yj
{
	HeadText::HeadText()
	{

	}
	HeadText::~HeadText()
	{
	
	}

	void HeadText::Initialize()
	{
		mWriteTextArray.push_back(L"�׾Ƹ� ����");
		mWriteTextArray.push_back(L"E ����");
		mWriteTextArray.push_back(L"E ��ȭ�ϱ�");
	}

	void HeadText::Update()
	{
		//GetTransform()->SetPosition();
		//GetTransform()->SetPosition();
		//�÷��̾� ���� ����ٴϰ� �ѹ��� ���� �Ӹ� �ٷ��� �׸��� �� �� �ϳ�
		//�� ǥ�ÿ� Ű �Է� ǥ��
		Vec3 mPlayerPos = PLAYER->GetTransform()->GetPosition();
		Vec3 mFixedPos = mPlayerPos + Vec3(0.0f, 0.5f, 0.0f);
		GetTransform()->SetPosition(mFixedPos);


		UIText* pUIText = GetUIText();
		pUIText = GetUIText();

		if (ApearAct)
		{
			while (mCurrSize < mExpandLimitSize)
			{
				mCurrSize += mIncreaseSize * DELTA_TIME;
				pUIText->SetSize(mCurrSize);
			}
			if (mCurrSize >= mExpandLimitSize)
			{
				pUIText->SetSize(mExpandLimitSize);
				mActState = StandbyAct;
			}
		}
		if (StandbyAct)
		{
			//
		}
		if (DisapearAct)
		{
			while (mCurrSize > mExpandLimitSize)
			{
				mCurrSize -= mIncreaseSize * DELTA_TIME;
				pUIText->SetSize(mCurrSize);
			}
			if (mCurrSize < 0.2f)
			{
				pUIText->SetSize(0.2f);
				Disable();
				mActState = End;
			}
		}
	}
	void HeadText::SetHeadText(int num)
	{
		SetText(mWriteTextArray[num], 25.f, true);
	}
	void HeadText::Apear()
	{
		this->GetGameObject()->Enable();
		mActState = ApearAct;
	}
	void HeadText::Disapear()
	{
		mActState = DisapearAct;
	}
}