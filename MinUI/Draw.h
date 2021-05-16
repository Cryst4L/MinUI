////////////////////////////////////////////////////////////////////////////////
// Draw.h
// -----------------------------------------------------------------------------
// Implements reccurent drawing primitives.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Widget.h"
#include "Types.h"
#include "Utils.h"
#include "Font.h"
#include "Style.h"

#include <iomanip>

namespace MinUI
{
void drawLine(Vector2f a, Vector2f b, X11Context& context, int width = 1, Color color = COLOR_OUTLINE);

void drawBox(Vector2f position, Vector2f dimension,
             Color fill_color, X11Context& context, bool outline = true, bool shadow = true);

void drawText(std::string text, const Vector2f position,
              Font& font, X11Context& context, bool padded = 1);

void drawHeader(std::string title, Vector2f position, Font& font, X11Context& context, bool parity);

}
