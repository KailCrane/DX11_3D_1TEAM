#include "pch.h"
#include "TextBox.h"
#include "UIText.h"
#include "Timer.h"
#include "Input.h"


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
		mWriteTextArray.push_back(L"�Ʒ��� ���� �ʾұ� �ٶ�. ���鵵 �غ��ص�. \n ���� ��ȥ�� ��Ȯ�ϴ� �� ���� ���� �ƴϴϱ�...");
		mWriteTextArray.push_back(L"���� ���� ��������.");


		mWriteTextArray.push_back(L"�� ���� ũ���� ��ȥ�̶�� �ð� �� �鿩�� �Ұž�...");
		mWriteTextArray.push_back(L"�׷��� �����...");

		mWriteTextArray.push_back(L"�� �� ���� ������ ��ȥ�� �������� ������ ��� �������� �ž�.");
		mWriteTextArray.push_back(L"���� �����ִ� ������ �ʸ��ڷμ� ��ư� �Ű�, ���̵� ���� �ž�. \n �׷��� ���θ����.");
		
		
		mWriteTextArray.push_back(L"��ȥ�� ��Ȯ�ϸ�, ���� ������ �ְ� �ǰ�, �׷��� �� ���� ��ȥ�� \n ��Ȯ�� �� �ְ� �ǰ�... �׷��� ��ȯ�ϴ� �ž�... ������ ������...");
		mWriteTextArray.push_back(L"�� �԰���ڰ� �ϴ� ���̾�.");
		mWriteTextArray.push_back(L"��¶��, ����. �׸��� �����ϰ�.");
		mWriteTextArray.push_back(L"�װ� ������ ó���ؾ� �� ������ �����ó�� ���� �״ϱ� ���̾�. \n �ð��� ���µ� ���̾�.");
	}


	void TextBox::Update()
	{
		if (mActState == ApearAct)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			if (this->GetTransform()->GetScale().x < 400)
			{
				Vec3 mFixedScale = mScale += Vec3(4.0f * DELTA_TIME* 500.0f, 1.0f * DELTA_TIME * 500.0f, 0.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}
				
			if (mScale.x >= 400)
			{
				this->GetTransform()->SetScale(Vec3(400.0f,100.0f,0.0f));
				SetCurrWriteText(mLineStartNum);
				SetTimerFlow();
				isTextWriting = true;
				mActState = WriteTextAct;
			}
		}
		if (mActState == WriteTextAct)
		{
			if (isTextWriting)
			{
				if (!GetIsWriteDone())
				{
					if (IsTimerReach())
					{
						mAddedTextCount += 1;
						CurrWriteTextAdd(mAddedTextCount);
						WriteText();
						TimerReset();
					}
				}
				else
				{
					SetTimerStop();

					if (IS_DOWN(KeyType::E))
					{
						mAddedLineNum += 1;
						ResetTextLine();
						if (mLineStartNum + mAddedLineNum < mLineEndNum)
						{
							SetTimerFlow();
							SetCurrWriteText(mLineStartNum + mAddedLineNum);
						}
						else
						{
							Disapear();
						}
					}
				}
			}
		}
		if (mActState == DisapearAct)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			if (this->GetTransform()->GetScale().x > 10)
			{
				Vec3 mFixedScale = mScale -= Vec3(4.0f * DELTA_TIME * 500.0f, 1.0f * DELTA_TIME * 500.0f, 0.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}

			if (mScale.x <= 10)
			{
				this->GetTransform()->SetScale(Vec3(40.0f, 10.0f, 0.0f));
				this->Disable();
				mActState = End;
			}
		}

		if (isTimerFlow)
		{
			mTimer += DELTA_TIME;
		}

	}
	void TextBox::Apear()
	{
		this->GetGameObject()->Enable();
		this->GetTransform()->SetScale(Vec3(40.0f,10.0f,1.0f));
		mAddedLineNum = 0;
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

	void TextBox::CurrWriteTextAdd(int num)
	{
		wstring mAddText = wstring(1, mSetWriteText[num]);
		mCurrWriteText += mAddText;
	}
	
	
	void TextBox::Disapear()
	{
		SetText(L"", 25, false);
		mActState = DisapearAct;
	}
}