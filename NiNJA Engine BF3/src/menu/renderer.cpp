#include "stdafx.h"

TextRenderer pTextRenderer;
DrawText pDrawText;
Shapes pShapes;
Renderer pRenderer;

float Shapes::ConvertPosition(float val, float screen) {
	if (val >= screen / 2.f) {
		val -= screen / 2.f;
		return val / (screen / 2.f);
	}

	return (((screen / 2.f) - val) / (screen / 2.f)) * -1.f;
}

void Shapes::Line(float x1, float y1, float x2, float y2, GColor color, float thickness) {
	if (!pGame.GetUIEngine()) return;
	if (!pGame.GetUIEngine()->pRenderer) return;
	if (!bHasTexture) return;

	float texX = 0.61f, texY = 0.17f, texW = 0.005f, texH = 0.01f;

	Vertex vertex[2];
	vertex[0].x = ConvertPosition(x1, 1280.f);
	vertex[0].y = -ConvertPosition(y1, 720.f);
	vertex[0].z = 0.f; // z
	vertex[0].texturePosition[0] = texX;
	vertex[0].texturePosition[1] = texY;
	vertex[0].color = color.GetVertexVal();

	vertex[1].x = ConvertPosition(x2, 1280.f);
	vertex[1].y = -ConvertPosition(y2, 720.f);
	vertex[1].z = 0.f; // z
	vertex[1].texturePosition[0] = texX + texW;
	vertex[1].texturePosition[1] = texY;
	vertex[1].color = color.GetVertexVal();

	DWORD vertexOffset = 0;
	DWORD vertexPtr = 0;
	if ((vertexPtr = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateVertexBuffer), pGame.GetUIEngine()->pRenderer, 0x60, &vertexOffset, vertex))) {
		short indices[6] = { 0, 1, 3, 1, 2, 3 };

		DWORD indexOffset = 0;
		DWORD indexPtr = 0;
		if ((indexPtr = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateIndexBuffer), pGame.GetUIEngine()->pRenderer, 0xC, &indexOffset, indices))) {
			DWORD command = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateRenderCommand), pGame.GetUIEngine()->pRenderer, 0);
			if (command) {
				Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingPopulateTexture), command + 0x10, szTextureBuffer);

				*(DWORD*)(command + 0x210) = 1; // primitive type
				*(short*)(command + 0x214) = 1; // primitive count
				*(BYTE*)(command + 0x21C) = 0x18; // vertex stride
				*(DWORD*)(command + 0x218) = indexOffset >> 1; // index buffer offset
				*(DWORD*)(command + 0x220) = vertexOffset; // vertex buffer offset in bytes
				*(DWORD*)(command + 0x224) = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetVertexBuffer), pGame.GetUIEngine()->pRenderer, pGame.GetUIEngine()->dwFrameIndex);
				*(DWORD*)(command + 0x228) = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetIndexBuffer), pGame.GetUIEngine()->pRenderer, pGame.GetUIEngine()->dwFrameIndex);

				Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingAddRenderCommand), pGame.GetUIEngine()->pRenderer, command, 1);
			}
		}
	}
}

void Shapes::Circle(const Vec3 &Center, float Radius, GColor color, unsigned short Sides) {
	float Angle = ((360.0f / Sides) * 3.14159265359) / 180;
	float Cos = cos(Angle);
	float Sin = sin(Angle);

	Vec3 vec(Radius, 0.f, 0.f);

	for (unsigned short i = 0; i < Sides; ++i) {
		Vec3 rot(Cos*vec.x - Sin * vec.y, Sin*vec.x + Cos * vec.y, 0.f);

		rot += Center;
		vec += Center;

		Line(vec.x, vec.y, rot.x, rot.y, color, 1);

		vec = rot - Center;
	}
}

void Shapes::Rectangle(float x, float y, float w, float h, Justification justify, GColor color) {
	float box[4];

	switch (justify) {
	case JustifyLeft:
		box[0] = x;
		box[1] = y;
		box[2] = w;
		box[3] = h;
		break;
	case JustifyCenter:
		box[0] = x - (w / 2);
		box[1] = y;
		box[2] = w;
		box[3] = h;
		break;
	case JustifyRight:
		box[0] = x - w;
		box[1] = y;
		box[2] = w;
		box[3] = h;
		break;
	}

	if (!pGame.GetUIEngine()) return;
	if (!pGame.GetUIEngine()->pRenderer) return;
	if (!bHasTexture) return;

	float texX = 0.61f, texY = 0.17f, texW = 0.005f, texH = 0.01f;

	Vertex vertex[4];
	vertex[0].x = ConvertPosition(box[0], 1280.f);
	vertex[0].y = -ConvertPosition(box[1], 720.f);
	vertex[0].z = 0.f; // z
	vertex[0].texturePosition[0] = texX;
	vertex[0].texturePosition[1] = texY;
	vertex[0].color = color.GetVertexVal();

	vertex[1].x = ConvertPosition(box[0] + box[2], 1280.f);
	vertex[1].y = -ConvertPosition(box[1], 720.f);
	vertex[1].z = 0.f; // z
	vertex[1].texturePosition[0] = texX + texW;
	vertex[1].texturePosition[1] = texY;
	vertex[1].color = color.GetVertexVal();

	vertex[2].x = ConvertPosition(box[0] + box[2], 1280.f);
	vertex[2].y = -ConvertPosition(box[1] + box[3], 720.f);
	vertex[2].z = 0.f; // z
	vertex[2].texturePosition[0] = texX + texW;
	vertex[2].texturePosition[1] = texY + texH;
	vertex[2].color = color.GetVertexVal();

	vertex[3].x = ConvertPosition(box[0], 1280.f);
	vertex[3].y = -ConvertPosition(box[1] + box[3], 720.f);
	vertex[3].z = 0.f; // z
	vertex[3].texturePosition[0] = texX;
	vertex[3].texturePosition[1] = texY + texH;
	vertex[3].color = color.GetVertexVal();

	DWORD vertexOffset = 0;
	DWORD vertexPtr = 0;
	if ((vertexPtr = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateVertexBuffer), pGame.GetUIEngine()->pRenderer, 0x60, &vertexOffset, vertex))) {
		short indices[6] = { 0, 1, 3, 1, 2, 3 };

		DWORD indexOffset = 0;
		DWORD indexPtr = 0;
		if ((indexPtr = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateIndexBuffer), pGame.GetUIEngine()->pRenderer, 0xC, &indexOffset, indices))) {
			DWORD command = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateRenderCommand), pGame.GetUIEngine()->pRenderer, 0);
			if (command) {
				Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingPopulateTexture), command + 0x10, szTextureBuffer);

				*(DWORD*)(command + 0x210) = 3; // primitive type
				*(short*)(command + 0x214) = 2; // primitive count
				*(BYTE*)(command + 0x21C) = 0x18; // vertex stride
				*(DWORD*)(command + 0x218) = indexOffset >> 1; // index buffer offset
				*(DWORD*)(command + 0x220) = vertexOffset; // vertex buffer offset in bytes
				*(DWORD*)(command + 0x224) = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetVertexBuffer), pGame.GetUIEngine()->pRenderer, pGame.GetUIEngine()->dwFrameIndex);
				*(DWORD*)(command + 0x228) = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetIndexBuffer), pGame.GetUIEngine()->pRenderer, pGame.GetUIEngine()->dwFrameIndex);

				Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingAddRenderCommand), pGame.GetUIEngine()->pRenderer, command, 1);
			}
		}
	}
}

void Shapes::RectangleOutlined(float x, float y, float w, float h, float thickness, GColor boxColor, GColor borderColor, bool sides) {
	Rectangle(x, y, w, h, JustifyLeft, boxColor);
	Rectangle(x, y - thickness, w, thickness, JustifyLeft, borderColor);
	Rectangle(x, y + h, w, thickness, JustifyLeft, borderColor);

	if (sides) {
		Rectangle(x - thickness, y - thickness, thickness, h + (thickness * 2), JustifyLeft, borderColor);
		Rectangle(x + w, y - thickness, thickness, h + (thickness * 2), JustifyLeft, borderColor);
	}
}

void Renderer::DrawTitle(const char* title) {
	pDrawText.DrawOptionTextBoldCenterAlign(title, 0, pMenu.iYPositonEditable + 360 - (fBgPosition / 2) + fPositionAnimFix - 38 + 6, 22.f, UIColors.titleText); // current sub
}

void Renderer::Render() {
	iRenderOptions = (pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions ? pMenu.iMaxOptions : pSubmenuHandler.GetTotalOptions());

	float bgPositionAnimTrans = (iRenderOptions * fOptionHeight) + 20;
	pUtils.Ease(fBgPosition, bgPositionAnimTrans, 1.5f);

	if (pSubmenuHandler.GetTotalOptions() < pMenu.iMaxOptions) {
		if (pSubmenuHandler.GetTotalOptions() % 2 == 0) {
			// if it's even
			fPositionAnimFix = fOptionHeight;
		}
	}

	int Y_coord = Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : pMenu.iCurrentOption - pMenu.iScrollOffset, 0, pMenu.iMaxOptions);
	float scrollPositionAnimTrans = pMenu.iYPositonEditable + (360 - (fBgPosition / 2) + fPositionAnimFix) + (Y_coord * fOptionHeight) + 11;
	pUtils.Ease(fScrollPosition, scrollPositionAnimTrans, 1.5f);

	RenderHeader();
	RenderBackground();
	RenderOptionHighlight();
	RenderFooter();
}

void Renderer::RenderFooter() {
	auto countNewLines = [](string s) -> int {
		int count = 0;

		for (int i = 0; i < s.size(); i++)
			if (s[i] == '\n') count++;

		return count;
	};

	float yPos = pMenu.iYPositonEditable + (360 - (fBgPosition / 2) + fPositionAnimFix) + fBgPosition;
	pUtils.Ease(fFooterYCoord, yPos, 1.5f);

	float width = 420;
	if (Tooltip.length() == 0) {
		pShapes.RectangleOutlined(640 - (width / 2), fFooterYCoord, width, 37, 1, UIColors.topBottom, UIColors.border, true); // footer
	} else {
		int count = countNewLines(Tooltip);
		pShapes.RectangleOutlined(640 - (width / 2), fFooterYCoord, width, 37 + (24.f * count), 1, UIColors.topBottom, UIColors.border, true); // footer
		pDrawText.DrawOptionTextBold(Tooltip.c_str(), 437, fFooterYCoord + 5, 20.f, UIColors.descriptionText);
	}
}

void Renderer::RenderOptionHighlight() {
	pMenu.iCurrentRenderingScroll = Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : (pMenu.iCurrentOption - pMenu.iScrollOffset) + 1, 0, pMenu.iMaxOptions);

	float width = 410;
	pShapes.Rectangle(640 - (width / 2), fScrollPosition, 410, 22, JustifyLeft, UIColors.scrollbar); // scroller
}

void Renderer::RenderBackground() {
	float trans = pMenu.iYPositonEditable + 360 - (fBgPosition / 2) + fPositionAnimFix;
	pUtils.Ease(fBgYCoord, trans, 1.5f);

	float width = 410;
	pShapes.Rectangle(640 - (width / 2), fBgYCoord, width, fBgPosition, JustifyLeft, UIColors.menuBackground);
}

void Renderer::RenderHeader() {
	float trans = pMenu.iYPositonEditable + 360 - (fBgPosition / 2) + fPositionAnimFix - 38;
	pUtils.Ease(fHeaderYCoord, trans, 1.5f);

	float width = 420;
	pShapes.RectangleOutlined(640 - (width / 2), fHeaderYCoord, width, 37, 1, UIColors.topBottom, UIColors.border, true);
}

int Renderer::Clamp(int val, int min, int max) {
	return val < min ? min : val > max ? max : val;
}

void TextRenderer::BeginText(UIRenderer* pUIRenderer, GFxDrawTextManager* pGFxDrawTextManager, bool a, bool b) {
	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingBeginText), pUIRenderer, pGFxDrawTextManager, a, b);
}

void TextRenderer::EndText(UIRenderer* pUIRenderer, GFxDrawTextManager* pGFxDrawTextManager) {
	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingEndText), pUIRenderer, pGFxDrawTextManager);
}

GFxDrawText* TextRenderer::CreateText(GFxDrawTextManager* pThis, const char* pMsg, GRect<float>* pRect, GFxDrawTextManagerTextParams* pParams) {
	return Invoke::Call<GFxDrawText*>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingCreateText), pThis, pMsg, pRect, pParams);
}

GFxDrawText* TextRenderer::CreateTextReversed(GFxDrawTextManager* pThis, const char* pMsg, GRect<float>* pRect, GFxDrawTextManagerTextParams* pParams) {
	return CreateText(pThis, pMsg, pRect, pParams);

	/*DWORD ptr = (DWORD)malloc(96);

	Invoke::Call<DWORD>(0x839FAAE8, ptr, pThis);
	
	auto pp = *(DWORD*)(ptr);

	Invoke::Call<DWORD>(*(DWORD*)(pp + 0x40), ptr, pRect);
	Invoke::Call<DWORD>(*(DWORD*)(pp + 0xC), ptr, pMsg, -1);
	
	if (!pParams) {
		pParams = (GFxDrawTextManagerTextParams*)(pThis->pManagerImpl + 0x1C0);
	}

	Invoke::Call<DWORD>(0x839FBBD8, pThis, Invoke::Call<DWORD>(*(DWORD*)(pp + 0xA8), ptr), pParams, nullptr, nullptr);

	return (GFxDrawText*)ptr;*/
}

void TextRenderer::InitTextParams(GFxDrawTextManagerTextParams* pThis) {
	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingInitTextParams), pThis);
}

void TextRenderer::InitFilterByDefaultValues(Filter* pFilter) {
	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingInitFilterByDefaultValues), pFilter);
}

void DrawText::Release(GFxDrawText* pClass, GFxDrawTextManagerTextParams* pParams) {
	Invoke::Call<DWORD>(0x839FBAB8, pClass, 1);

	auto idk = pParams->FontName.dwHeapTypeBits & 0xFFFFFFFC;
	*(int*)(idk + 4) = *(int*)(idk + 4) - 1;
	Invoke::Call<DWORD>(*(DWORD*)((*(DWORD*)pGame.GetUIEngine()->pDrawTextManager->pMemoryManager) + 0x30), pGame.GetUIEngine()->pDrawTextManager->pMemoryManager, idk);
}

void DrawText::DrawOptionText(const char* text_, float x, float y, float scale, GColor color) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);

		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_medium");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_BaseLine;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);
			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextBold(const char* text_, float x, float y, float scale, GColor color) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_bold");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_BaseLine;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);
			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextWithBox(const char* text_, float x, float y, float scale, GColor textColor, GColor boxColor, bool rightAlign) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 1, 1280, 720);
		if (rightAlign) {
			screenRect.Right = x + 400;
		}

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_medium");
		TextParams.TextColor = textColor;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_BaseLine;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);

			float width = (Invoke::Call<float>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetWidth), *(DWORD*)((DWORD)text + 0xC)) / 20.f) + 4.f;
			float height = (Invoke::Call<float>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetHeight), *(DWORD*)((DWORD)text + 0xC)) / 20.f) + 2.f;

			pShapes.Rectangle(screenRect.Left - 2.f, screenRect.Top + 2, width + 4.f, height, rightAlign ? JustifyRight : JustifyLeft, boxColor);

			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextBoldCenterAlign(const char* text_, float x, float y, float scale, GColor color) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_bold");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_Left;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);
			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextCenterAlign(const char* text_, float x, float y, float scale, GColor color) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_medium");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_Left;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);
			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextBoldRightAlign(const char* text_, float x, float y, float scale, GColor color) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);
		screenRect.Right = x + 400;

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_bold");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_Right;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);
			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}

void DrawText::DrawOptionTextBoldCenterAlignWithBox(const char* text_, float x, float boxX, float y, float scale, GColor color, GColor boxColor) {
	auto engine = pGame.GetUIEngine();
	if (ValidPtr(engine) && ValidPtr(engine->pRenderer) && ValidPtr(engine->pDrawTextManager)) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);
		GRect<float> screenRect = GRect<float>(x, y - 4, 1280, 720);

		GFxDrawTextManagerTextParams TextParams;
		Filter _Filter;

		pTextRenderer.InitTextParams(&TextParams);
		pTextRenderer.InitFilterByDefaultValues(&_Filter);
		TextParams.ConstructGString("$MENU_bold");
		TextParams.TextColor = color;
		TextParams.flFontSize = scale;
		TextParams.HAlignment = Alignment_Left;
		TextParams.VAlignment = VAlignment_None;

		auto text = pTextRenderer.CreateTextReversed(engine->pDrawTextManager, text_, &screenRect, &TextParams);
		if (text) {
			++text->iRefCount;
			text->SetRect(screenRect);
			text->SetText(text_, strlen(text_));
			text->SetFilters(&_Filter, 1);

			float width = (Invoke::Call<float>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetWidth), *(DWORD*)((DWORD)text + 0xC)) / 20.f) + 4.f;
			float height = (Invoke::Call<float>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderingGetHeight), *(DWORD*)((DWORD)text + 0xC)) / 20.f) + 2.f;

			pShapes.Rectangle(boxX - 2.f, screenRect.Top + 2, width + 4.f, height, JustifyCenter, boxColor);

			text->Display();

			Release(text, &TextParams);
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}
}