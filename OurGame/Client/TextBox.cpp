#include "pch.h"
#include "TextBox.h"
#include "UIText.h"
#include "Timer.h"


namespace yj
{
	TextBox::TextBox()
	{


	}
	TextBox::~TextBox()
	{
	}

	void TextBox::Initialize()
	{
		mWriteTextArray.push_back(L"�̷� �̷� �̷�...");
		mWriteTextArray.push_back(L"���� ���� ���߽ô� ����, �ڳ� �� ������ ����...");
		mWriteTextArray.push_back(L"������ ���� �Ͼ�� ����- �ƴ� �ƴ�.");
		mWriteTextArray.push_back(L"��¶��, ���� �� �����ó�... ��Ȯ����� �� ��ȥ�� �ϳ� �־�.");
		mWriteTextArray.push_back(L"�׳� ����� ��ȥ�� �ƴϾ�. ���� ��ȥ�̶��! �� �� ����غ�...");
		mWriteTextArray.push_back(L"�Ʒ��� ���� �ʾұ� �ٶ�. ���鵵 �غ��ص�. ���� ��ȥ�� ��Ȯ�ϴ� �� ���� ���� �ƴϴϱ�...");
		mWriteTextArray.push_back(L"���� ���� ��������.");
		mWriteTextArray.push_back(L"�� ���� ũ���� ��ȥ�̶�� �ð� �� �鿩�� �Ұž�...");
		mWriteTextArray.push_back(L"�׷��� �����...");
		mWriteTextArray.push_back(L"�� �� ���� ������ ��ȥ�� �������� ������ ��� �������� �ž�.");
		mWriteTextArray.push_back(L"���� �����ִ� ������ �ʸ��ڷμ� ��ư� �Ű�, ���̵� ���� �ž�. �׷��� ���θ����.");
		mWriteTextArray.push_back(L"��ȥ�� ��Ȯ�ϸ�, ���� ������ �ְ� �ǰ�, �׷��� �� ���� ��ȥ�� ��Ȯ�� �� �ְ� �ǰ�... �׷��� ��ȯ�ϴ� �ž�... ������ ������...");
		mWriteTextArray.push_back(L"�� �԰���ڰ� �ϴ� ���̾�.");
		mWriteTextArray.push_back(L"��¶��, ����. �׸��� �����ϰ�.");
		mWriteTextArray.push_back(L"�װ� ������ ó���ؾ� �� ������ �����ó�� ���� �״ϱ� ���̾�. �ð��� ���µ� ���̾�.");
	}


	void TextBox::Update()
	{
		UIText* pUIText = GetUIText();
		pUIText = GetUIText();
		
		if (ApearAct)
		{
			while(mCurrSize < mExpandLimitSize)
			{
				mCurrSize += mIncreaseSize * DELTA_TIME;
				pUIText->SetSize(mCurrSize);
			}
			if (mCurrSize >= mExpandLimitSize)
			{
				pUIText->SetSize(mExpandLimitSize);
				mActState = StandbyAct;
				SetTimerFlow();
			}
		}
		if (StandbyAct)
		{
			if (isTextWriting)
			{
				if (!GetIsWriteDone)
				{
					if (IsTimerReach())
					{
						TimerReset();
						//AddText(mSetWriteText.);
						/// ��
						/// �ȳ�
						/// 
						/// �� ó�� �ѱ��ھ� �߰��Ͽ� ��� �ϰ� ������ wstring�� �ε����� ���� �ϴ� ����� �𸣰ڴ�.
						WriteText();
					}
				}
				else
				{

				}
			}
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
	void TextBox::Apear()
	{
		this->GetGameObject()->Enable();
		mActState = ApearAct;
	}
	void TextBox::SetCurrWriteText(int _TextLineNum)
	{
		mSetWriteText = mWriteTextArray[_TextLineNum];
		mCurrTextLength = mSetWriteText.length();
	}
	void TextBox::WriteText()
	{
		SetText(mCurrWriteText, 25.f, true);
	}
	
	
	void TextBox::Disapear()
	{
		mActState = DisapearAct;
	}
}