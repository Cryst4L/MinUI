////////////////////////////////////////////////////////////////////////////////
// Style.h
// -----------------------------------------------------------------------------
// Implements drawing and rendering configurations.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Types.h"

#define DEFAULT_LINE_WIDTH 2
#define DEFAULT_FONT_PATH  "Fonts/RobotoMono.bmp"

const int GRID_SIZE = 30;
const int FONT_SIZE = 15;

const int FRAME_RATE = 60;

namespace MinUI
{
typedef struct {
	Color background;
	Color foreground;
} ColorScheme;

enum ColorSchemeEnum {BASE = 0, EMPHASIS = 1, BUTTON = 2, FILL = 3, HOVER = 4};

//const int NB_COLORS  = 3;
//const int NB_SCHEMES = 3;

const Color COLOR_BASE      = {180, 180, 180};
const Color COLOR_EMPHASIS  = {200, 200, 200};
const Color COLOR_FILL      = { 50, 120, 240};  //  { 80, 120, 220};
const Color COLOR_HOVER     = {240, 240, 240};
const Color COLOR_BUTTON    = {210, 210, 210};
const Color COLOR_TEXT      = {  0,   0,   0};
const Color COLOR_INVERTED  = {255, 255, 255};
const Color COLOR_OUTLINE   = { 40,  40,  40};
const Color COLOR_SHADOW   =  {100, 100, 100};

#define NB_COLOR_SCHEMES  5

const ColorScheme COLOR_SCHEME_BASE =
{COLOR_BASE, COLOR_TEXT};

const ColorScheme COLOR_SCHEME_EMPHASIS =
{COLOR_EMPHASIS, COLOR_TEXT};

const ColorScheme COLOR_SCHEME_HOVER =
{COLOR_HOVER, COLOR_TEXT};

const ColorScheme COLOR_SCHEME_FILL =
{COLOR_FILL, COLOR_INVERTED};

const ColorScheme COLOR_SCHEME_BUTTON =
{COLOR_BUTTON, COLOR_TEXT};

const ColorScheme DEFAULT_COLOR_SCHEMES[NB_COLOR_SCHEMES] = {
	COLOR_SCHEME_BASE, COLOR_SCHEME_EMPHASIS, COLOR_SCHEME_BUTTON,
	COLOR_SCHEME_FILL, COLOR_SCHEME_HOVER
};
}
