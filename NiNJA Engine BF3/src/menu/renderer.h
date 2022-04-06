#pragma once

class GFxDrawText {
public:
	virtual void Destruct(int size);
	virtual void SetText1(GString& str);
	virtual void SetText2(wchar_t* pStr, DWORD dwLen);
	virtual void SetText(const char* pStr, DWORD dwLen);
	virtual GString GetText();
	virtual void SetColor(GColor color, DWORD dwStart, DWORD dwEnd);
	virtual void SetFont(const char* pFont, DWORD dwStart, DWORD dwEnd);
	virtual void SetFontSize(float flSize, DWORD dwStart, DWORD dwEnd);
	virtual void SetFontStyle(FontStyle style, DWORD dwStart, DWORD dwEnd);
	virtual void SetUnderline(bool bUnderline, DWORD dwStart, DWORD dwEnd);
	virtual void SetMultiline(bool bMultiline);
	virtual bool IsMultiline();
	virtual void SetWordWrap(bool bWordWrap);
	virtual bool IsWordWrap();
	virtual void unk1();
	virtual void unk2();
	virtual void SetRect(GRect<float>& rect);
	virtual GRect<float> GetRect();
	virtual void SetMatrix();
	virtual void GetMatrix();
	virtual void SetMatrix3D();
	virtual void GetMatrix3D();
	virtual void SetCxform();
	virtual void GetCxform();
	virtual void SetBorderColor(GColor& color);
	virtual GColor* GetBorderColor();
	virtual void SetBackgroundColor(GColor& color);
	virtual GColor* GetBackgroundColor();
	virtual void SetAlignment(Alignment a);
	virtual Alignment GetAlignment();
	virtual void SetVAlignment(VAlignment a);
	virtual VAlignment GetVAlignment();
	virtual void Display();
	virtual void SetRenderingString(GString& str);
	virtual GString* GetRendererString();
	virtual void SetRendererFloat(float flFloat);
	virtual float GetRendererFloat();
	virtual void SetRendererMatrix();
	virtual void SetAAMode();
	virtual void GetAAMode();
	virtual void SetFilters(Filter* filter, DWORD dwCount);
	virtual void ClearFilters();
	virtual DWORD GetDocView();

	int iRefCount;
};

class TextRenderer {
public:
	void BeginText(UIRenderer* pUIRenderer, GFxDrawTextManager* pGFxDrawTextManager, bool a, bool b);
	void EndText(UIRenderer* pUIRenderer, GFxDrawTextManager* pGFxDrawTextManager);

	GFxDrawText* CreateText(GFxDrawTextManager* pThis, const char* pMsg, GRect<float>* pRect, GFxDrawTextManagerTextParams* pParams = nullptr);
	GFxDrawText* CreateTextReversed(GFxDrawTextManager* pThis, const char* pMsg, GRect<float>* pRect, GFxDrawTextManagerTextParams* pParams = nullptr);

	void InitTextParams(GFxDrawTextManagerTextParams* pThis);
	void InitFilterByDefaultValues(Filter* pFilter);
};

extern TextRenderer pTextRenderer;

class DrawText {
public:
	void Release(GFxDrawText* pClass, GFxDrawTextManagerTextParams* pParams);
	void DrawOptionText(const char* text_, float x, float y, float scale, GColor color);
	void DrawOptionTextBold(const char* text_, float x, float y, float scale, GColor color);
	void DrawOptionTextCenterAlign(const char* text_, float x, float y, float scale, GColor color);
	void DrawOptionTextWithBox(const char* text_, float x, float y, float scale, GColor textColor, GColor boxColor, bool rightAlign);
	void DrawOptionTextBoldCenterAlign(const char* text_, float x, float y, float scale, GColor color);
	void DrawOptionTextBoldRightAlign(const char* text_, float x, float y, float scale, GColor color);
	void DrawOptionTextBoldCenterAlignWithBox(const char* text_, float x, float boxX, float y, float scale, GColor color, GColor boxColor);
};

extern DrawText pDrawText;

class Shapes {
public:
	struct Vertex {
		float x, y, z;
		float texturePosition[2];
		DWORD color;
	};

	char szTextureBuffer[0x200];
	bool bHasTexture;

	float ConvertPosition(float val, float screen);
	void Line(float x1, float y1, float x2, float y2, GColor color, float thickness);
	void Circle(const Vec3 &Center, float Radius, GColor color, unsigned short Sides);
	void Rectangle(float x, float y, float w, float h, Justification justify, GColor color);
	void RectangleOutlined(float x, float y, float w, float h, float thickness, GColor boxColor, GColor borderColor, bool sides = false);
};

extern Shapes pShapes;

class Renderer {
public:
	struct Colors {
		GColor menuBackground;
		GColor border;
		GColor descriptionText;
		GColor scrollbar;
		GColor selectedText;
		GColor text;
		GColor titleText;
		GColor topBottom;
		GColor slider;
	} UIColors;

	void Init() {
		DbgPrint("Initializing renderer");

		fOptionHeight = 22.f;

		UIColors.menuBackground = GColor(0, 0, 0, 226);
		UIColors.border = GColor(255, 255, 255, 255);
		UIColors.descriptionText = GColor(255, 255, 255, 255);
		UIColors.scrollbar = GColor(102, 0, 255, 102);
		UIColors.selectedText = GColor(255, 255, 255, 255);
		UIColors.text = GColor(255, 255, 255, 255);
		UIColors.titleText = GColor(255, 255, 255, 255);
		UIColors.topBottom = GColor(102, 0, 255, 226);
		UIColors.slider = GColor(255, 255, 255, 255);
	}

	void DrawTitle(const char* title);

	void Render();
	void RenderHeader();
	void RenderBackground();
	void RenderOptionHighlight();
	void RenderFooter();

	void SetTooltip(string name) {
		Tooltip = name;
	}

	int Clamp(int val, int min, int max);

	string TitleRenderText;
	string Tooltip;
	int iRenderOptions;
	float fOptionHeight;
	float fBgPosition;
	float fFooterYCoord;
	float fHeaderYCoord;
	float fPositionAnimFix;
	float fBgYCoord;
	float fScrollPosition;
	float fScrollYCoordTemp;
	float fScrollBarHeight;
	float fScrollBarYCoord;
};

extern Renderer pRenderer;