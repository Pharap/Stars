//
// Copyright (C) 2018 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

class Vector2
{
public:
	SQ7x8 x;
	SQ7x8 y;
	
public:
	constexpr Vector2() = default;
	constexpr Vector2(SQ7x8 x, SQ7x8 y) : x(x), y(y) {}
		
	Vector2 & operator +=(Vector2 other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
		
	Vector2 & operator -=(Vector2 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
};

constexpr Vector2 operator+(Vector2 left, Vector2 right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

constexpr Vector2 operator-(Vector2 left, Vector2 right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

struct Star
{
	Vector2 position;
	Vector2 velocity;
};

constexpr Vector2 centreScreen = Vector2(WIDTH / 2, HEIGHT / 2);

constexpr size_t starCount = 32;

Star stars[starCount];

// Generated with AngleGenerator.cs
const Vector2 offsets[] PROGMEM
{
	Vector2(1.0000, 0.0000),
	Vector2(0.9808, 0.1951),
	Vector2(0.9239, 0.3827),
	Vector2(0.8315, 0.5556),
	Vector2(0.7071, 0.7071),
	Vector2(0.5556, 0.8315),
	Vector2(0.3827, 0.9239),
	Vector2(0.1951, 0.9808),
	Vector2(0.0000, 1.0000),
	Vector2(-0.1951, 0.9808),
	Vector2(-0.3827, 0.9239),
	Vector2(-0.5556, 0.8315),
	Vector2(-0.7071, 0.7071),
	Vector2(-0.8315, 0.5556),
	Vector2(-0.9239, 0.3827),
	Vector2(-0.9808, 0.1951),
	Vector2(-1.0000, 0.0000),
	Vector2(-0.9808, -0.1951),
	Vector2(-0.9239, -0.3827),
	Vector2(-0.8315, -0.5556),
	Vector2(-0.7071, -0.7071),
	Vector2(-0.5556, -0.8315),
	Vector2(-0.3827, -0.9239),
	Vector2(-0.1951, -0.9808),
	Vector2(0.0000, -1.0000),
	Vector2(0.1951, -0.9808),
	Vector2(0.3827, -0.9239),
	Vector2(0.5556, -0.8315),
	Vector2(0.7071, -0.7071),
	Vector2(0.8315, -0.5556),
	Vector2(0.9239, -0.3827),
	Vector2(0.9808, -0.1951),
};
constexpr size_t offsetCount = (sizeof(offsets) / sizeof(Vector2));

Vector2 getOffset(size_t index)
{
	Vector2 result;
	memcpy_P(&result, &offsets[index % offsetCount], sizeof(Vector2));
	return result;
}

Arduboy2 arduboy;

void initialiseStars()
{
	for(size_t index = 0; index < starCount; ++index)
	{
		stars[index].position = centreScreen;
		stars[index].velocity = getOffset(rand());
	}
}

void updateStars()
{	
	for(size_t index = 0; index < starCount; ++index)
	{
		stars[index].position += stars[index].velocity;
		
		if((stars[index].position.x < 0) || (stars[index].position.y < 0))
		{
			stars[index].position = centreScreen;
			stars[index].velocity = getOffset(rand());		
		}
	}
}

void drawStars()
{
	for(size_t index = 0; index < starCount; ++index)
	{
		int8_t x = static_cast<int8_t>(stars[index].position.x);
		int8_t y = static_cast<int8_t>(stars[index].position.y);
		arduboy.drawPixel(x, y);
	}
}

void setup()
{
	arduboy.begin();
	initialiseStars();
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.pollButtons();

	updateStars();
	
	arduboy.clear();
	
	drawStars();
	
	arduboy.display();
}
