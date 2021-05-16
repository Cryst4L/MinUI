////////////////////////////////////////////////////////////////////////////////
// Utils.h
// -----------------------------------------------------------------------------
// Implements utility functions
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Types.h"

namespace MinUI
{

long codeFromColor(const Color color);

Color mix(Color a, Color b, float ratio = 0.5);

Vector2f add(Vector2f a, Vector2f b);
Vector2i add(Vector2i a, Vector2i b);

}
