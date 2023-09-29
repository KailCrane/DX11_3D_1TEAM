#include "pch.h"
#include "UIText.h"
#include "GameObject.h"
#include "FontManager.h"
#include "Engine.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Camera.h"

namespace hm
{
	UIText::UIText()
		: Component(ComponentType::UI)
		, mbShadow(false)
		, mSize(20.f)
		, meAlignH(TextAlignH::Center)
		, meAlignV(TextAlignV::Top)
		, meRenderType(TextRenderType::TextUI)
		, mbAlpha(false)
		, mbAlphaShadow(false)
		, mOpacity(1.f)
		, mShadowOpacity(1.f)
	{
		mFont = L"���� ���";
		mFont.resize(64);

		mColor = Vec4(1.f, 1.f, 1.f, 1.f);
		mShadowColor = Vec4(0.f, 0.f, 0.f, 1.f);

		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat("FreshGothic");
		mpTextLayout = GET_SINGLE(FontManager)->CreateTextLayout(L"", mpTextFormat, 100.f, 100.f);

		mpColor = GET_SINGLE(FontManager)->CreateColor(mColor);
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(mShadowColor);

		mMaxCount = 256;
		mText.resize(mMaxCount);
		mText += L"Text";

		mRenderArea = {};
	}
	UIText::~UIText()
	{
		mpTextLayout->Release();
	}
	Component* UIText::Clone(GameObject* _pGameObject)
	{
		UIText* pUIText = _pGameObject->AddComponent(new UIText);
		return pUIText;
	}
	void UIText::Initialize()
	{
	}
	void UIText::Render()
	{
		// �׸��� ȣ���� BeginDraw ȣ��� EndDraw ȣ�� ���̿����� ���� �� �� �ֽ��ϴ�.
		RENDERTARGET_2D->BeginDraw();

		Vec3 pos = GetTransform()->GetPosition();

		float height = mRenderArea.bottom - mRenderArea.top;

		// UI�� �ƴ� ����ī�޶� ����޴� Ÿ���� ���
		// ���� ī�޶��� �������־�� �Ѵ�.
		if (meRenderType != TextRenderType::TextUI)
		{
			// ���� ī�޶� Transform�� ���´�.
			Transform* pCameraTr = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetTransform();

			// �ش� ������Ʈ�� ī�޶� ����ŭ ���� Ŭ���̾�Ʈ ���� ���� �����ϴ°�ó�� �����Ų��.
			pos -= pCameraTr->GetPosition();
		}

		// ��Ʈ�� �׸��ڰ� �����ϴ� ���
		if (true == mbShadow)
		{
			// �׸��ڴ� ���� ���� ��Ʈ�� ������ ����ŭ ��������
			// ��ġ �׸���ó�� ���̰Բ� �ϴ°��̹Ƿ�...
			Vec3 shadowPos = pos + mShadowOffset;

			// �׸��ڿ� ���İ��� �����ϴ� ���
			if (true == mbAlphaShadow)
			{
				// �ش� ���� ��ŭ �������ش� (0 ~ 1)
				mpShadowColor->SetOpacity(mShadowOpacity);
			}
			else
			{
				// ������
				mpShadowColor->SetOpacity(1.f);
			}

			// �׸��ڰ� ���� ��Ʈ���� ���� ������
			// �ش� ������ ������ ���� ��Ʈ���� �Ʒ��� �� ���̴�.
			shadowPos.y = RESOLUTION.y - shadowPos.y - height + RESOLUTION.y / 2.f - 20.f;
			// �׸��ڸ� �׸���.
			// 1. �׸��� ��� ��ġ
			// 2. �׸��� ���̾ƿ�
			// 3. �׸��� �÷�
			RENDERTARGET_2D->DrawTextLayout(D2D1::Point2F(shadowPos.x, shadowPos.y),
				mpTextLayout, mpShadowColor);
		}

		// ��Ʈ�� ���İ� �����ϴ� ���
		if (mbAlpha)
		{
			// ���İ� ����
			mpColor->SetOpacity(mOpacity);
		}
		else
		{
			// ������
			mpColor->SetOpacity(1.f);
		}
		pos.y = RESOLUTION.y - pos.y - height + RESOLUTION.y / 2.f - 20.f;

		// �ؽ�Ʈ�� �׸���.
		// 1. �ؽ�Ʈ ��� ��ġ
		// 2. �ؽ�Ʈ ���̾ƿ�
		// 3. �ؽ�Ʈ �÷�
		RENDERTARGET_2D->DrawTextLayout(D2D1::Point2F(pos.x, pos.y),
			mpTextLayout, mpColor);

		RENDERTARGET_2D->EndDraw();
	}
	void UIText::SetRenderType(TextRenderType _eType)
	{
		meRenderType = _eType;
	}
	void UIText::SetTextCount(int _maxCount)
	{
		if (_maxCount < mText.size())
			return;

		mText.resize(_maxCount);
	}
	void UIText::SetText(const wstring& _text)
	{
		mText = _text;
	}
	void UIText::AddText(const wstring& _text)
	{
		mText += _text;
	}
	void UIText::SetFont(const std::string& _name, const wstring& _fontName, int _weight, int _style, int _stretch, float _size, const TCHAR* _pLocalName)
	{
		mSize = _size;
		mFont = _fontName;

		GET_SINGLE(FontManager)->CreateTextFormat(_name, _fontName.c_str(), _weight, _style, _stretch, _size, _pLocalName);

		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat(_name);
		CreateTextLayout();
	}
	void UIText::SetFont(const string& _name)
	{
		mpTextFormat = GET_SINGLE(FontManager)->FindTextFormat(_name);
		CreateTextLayout();
	}
	void UIText::SetSize(float _size)
	{
		mSize = _size;
		CreateTextLayout();
	}
	void UIText::SetAlignH(TextAlignH _eAlign)
	{
		meAlignH = _eAlign;

		if (nullptr == mpTextLayout)
			CreateTextLayout();

		switch (_eAlign)
		{
		case hm::TextAlignH::Left:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			break;
		case hm::TextAlignH::Center:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			break;
		case hm::TextAlignH::Right:
			mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			break;
		}
	}
	void UIText::SetAlignV(TextAlignV _eAlign)
	{
		meAlignV = _eAlign;

		if (nullptr == mpTextLayout)
			CreateTextLayout();

		switch (_eAlign)
		{
		case hm::TextAlignV::Top:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			break;
		case hm::TextAlignV::Mid:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			break;
		case hm::TextAlignV::Bottom:
			mpTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			break;
		}
	}
	void UIText::Shadow(bool _bShadow)
	{
		mbShadow = _bShadow;
	}
	void UIText::SetOffset(const Vec3& _offset)
	{
		mOffset = _offset;
	}
	void UIText::SetShadowOffset(const Vec3& _shadowOffset)
	{
		mShadowOffset = _shadowOffset;
	}
	void UIText::SetShadowColor(float _r, float _g, float _b, float _a)
	{
		mShadowColor = Vec4(_r, _g, _b, _a);
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetShadowColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		mShadowColor = Vec4(_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f);

		// �����ͷ� ������ �׸��� �÷� ��
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetShadowColor(const Vec4& _color)
	{
		mShadowColor = _color;
		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(mShadowColor);
	}
	void UIText::SetShadowColor(UINT32 _color)
	{
		mShadowColor.z = (_color & 0x000000ff) / 255.f;
		mShadowColor.y = ((_color >> 8) & 0x000000ff) / 255.f;
		mShadowColor.x = ((_color >> 16) & 0x000000ff) / 255.f;
		mShadowColor.w = ((_color >> 24) & 0x000000ff) / 255.f;

		mpShadowColor = GET_SINGLE(FontManager)->CreateColor(_color);
	}
	void UIText::AlphaBlend(bool _bAlpha)
	{
		mbAlpha = _bAlpha;
	}
	void UIText::ShadowAlphaBlend(bool _bAlpha)
	{
		mbAlphaShadow = _bAlpha;
	}
	void UIText::SetOpacity(float _opacity)
	{
		mOpacity = _opacity;
	}
	void UIText::SetShadowOpacity(float _opacity)
	{
		mShadowOpacity = _opacity;
	}
	void UIText::SetColor(float _r, float _g, float _b, float _a)
	{
		mColor = Vec4(_r, _g, _b, _a);
		mpColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		mColor = Vec4(_r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f);
		mpColor = GET_SINGLE(FontManager)->CreateColor(_r, _g, _b, _a);
	}
	void UIText::SetColor(const Vec4& _color)
	{
		mColor = _color;
		mpColor = GET_SINGLE(FontManager)->CreateColor(mColor);
	}
	void UIText::SetColor(UINT32 _color)
	{
		mColor.z = (_color & 0x000000ff) / 255.f;
		mColor.y = ((_color >> 8) & 0x000000ff) / 255.f;
		mColor.x = ((_color >> 16) & 0x000000ff) / 255.f;
		mColor.w = ((_color >> 24) & 0x000000ff) / 255.f;

		mpColor = GET_SINGLE(FontManager)->CreateColor(_color);
	}
	void UIText::SetRenderArea(float _left, float _top, float _right, float _bottom)
	{
		mRenderArea = D2D1::RectF(_left, RESOLUTION.y - _bottom,
			_right, RESOLUTION.y - _top);

		CreateTextLayout();
	}
	void UIText::CreateTextLayout()
	{
		// ���� ������ �ؽ�Ʈ ��Ʈ�� �������� ���� ���
		if (!mpTextFormat)
		{
			return;
		}
		AssertEx(mpTextFormat, L"UIText::CreateTextLayout() - �ؽ�Ʈ ��Ʈ�� �������� ����");
		
		if (nullptr != mpTextLayout)
		{
			mpTextLayout->Release();
			mpTextLayout = nullptr;
		}

		// �ؽ�Ʈ ���̾ƿ� ����
		// 1. �ؽ�Ʈ
		// 2. �ؽ�Ʈ ����
		// 3. ���� �ʺ�
		// 4. ���� �ʺ�
		mpTextLayout = GET_SINGLE(FontManager)->CreateTextLayout(
			mText.c_str(), mpTextFormat, mRenderArea.right - mRenderArea.left,
			mRenderArea.bottom - mRenderArea.top);

		// �ؽ�Ʈ ���̿� ���� ���� (0��°���� �ش� �ؽ�Ʈ ��ü ���̱���)
		DWRITE_TEXT_RANGE	range;
		range.startPosition = 0;
		range.length = static_cast<UINT32>(mText.size());

		// ���̾ƿ��� �ؽ�Ʈ���� �� �ؽ�Ʈ ������ ����
		mpTextLayout->SetFontSize(mSize, range);
	}
}

