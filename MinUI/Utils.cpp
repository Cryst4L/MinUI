#include "Utils.h"

namespace MinUI
{
long codeFromColor(const Color color)
{
	return (color.r << 16) + (color.g << 8) + color.b;
}

Color mix(Color a, Color b, float ratio)
{
	Color c;
	c.r = (int) (a.r * ratio + b.r * (1 - ratio));
	c.g = (int) (a.g * ratio + b.g * (1 - ratio));
	c.b = (int) (a.b * ratio + b.b * (1 - ratio));
	return c;	
}

Vector2f add(Vector2f a, Vector2f b)
{
	return {a.x + b.x, a.y + b.y};
}

Vector2i add(Vector2i a, Vector2i b)
{
	return {a.x + b.x, a.y + b.y};
}

}
