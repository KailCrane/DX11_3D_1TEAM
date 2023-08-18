#pragma once
#include "Component.h"
namespace hm
{
	enum class TextRenderType
	{
		TextUI,
		Text2D,
		Text3D,
	};

	enum class TextAlignH
	{
		Left,
		Center,
		Right
	};

	enum class TextAlignV
	{
		Top,
		Mid,
		Bottom
	};

	class UIText :
		public Component
	{
	public:
		UIText();
		virtual ~UIText();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Initialize() override;
		virtual void Render() override;

	public:
		void SetRenderType(TextRenderType _eType);
		void SetTextCount(int _maxCount);
		void SetText(const wstring& _text);
		void AddText(const wstring& _text);

		void SetFont(const std::string& _name, const wstring& _fontName,
			int _weight, int _style, int _stretch, float _size,
			const TCHAR* _pLocalName);

		void SetFont(const string& _name);
		void SetSize(float _size);
		void SetAlignH(TextAlignH _eAlign);
		void SetAlignV(TextAlignV _eAlign);
		void Shadow(bool _bShadow);
		void SetOffset(const Vec3& _offset);
		void SetShadowOffset(const Vec3& _shadowOffset);
		void SetShadowColor(float _r, float _g, float _b, float _a);
		void SetShadowColor(unsigned char _r, unsigned char _g,
			unsigned char _b, unsigned char _a);
		void SetShadowColor(const Vec4& _color);
		void SetShadowColor(UINT32 _color);
		void AlphaBlend(bool _bAlpha);
		void ShadowAlphaBlend(bool _bAlpha);
		void SetOpacity(float _opacity);
		void SetShadowOpacity(float _opacity);
		void SetColor(float _r, float _g, float _b, float _a);
		void SetColor(unsigned char _r, unsigned char _g,
			unsigned char _b, unsigned char _a);
		void SetColor(const Vec4& _color);
		void SetColor(UINT32 _color);
		void SetRenderArea(float _l, float _t, float _r, float _b);

	private:
		void CreateTextLayout();

	private:
		IDWriteTextFormat* mpTextFormat;
		IDWriteTextLayout* mpTextLayout;

		ID2D1SolidColorBrush* mpColor;
		ID2D1SolidColorBrush* mpShadowColor; // �׸��ڿ�

		// �ؽ�Ʈ ������ (YDJ)
		Vec3 mOffset;

		// �׸��� ��뿩��
		bool	mbShadow;

		// �ؽ�Ʈ
		wstring mText;

		// �ؽ�Ʈ �� ����
		int mMaxCount;

		// ��Ʈ ��
		wstring mFont;

		// ��Ʈ ũ��
		float mSize;

		// ���� ���� ����
		TextAlignH meAlignH;
		// ���� ���� ����
		TextAlignV meAlignV;

		// ���� Ÿ��(2D, 3D, UI) 
		TextRenderType meRenderType;

		// ���� ���� ����
		bool mbAlpha;
		// �׸��� ���� ���� ����
		bool mbAlphaShadow;

		// ����
		float mOpacity;

		// �׸��� ����
		float mShadowOpacity;

		// ��Ʈ ����
		Vec4 mColor;
		// �׸��� ����
		Vec4 mShadowColor;

		// �׸��� ������
		Vec3 mShadowOffset;

		// ��Ʈ�� �׷��� ����
		D2D1_RECT_F mRenderArea;
	};
}


