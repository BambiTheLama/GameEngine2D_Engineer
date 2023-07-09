#pragma once
#include <vector>
#include <string>
#include "raylib.h"
/// <summary>
/// Klasa do trzymania textur w jednym miejscu i sprawdzaniu czy ju¿ zosta³a takowa wczytana
/// </summary>
class SpriteController
{
	static std::vector<SpriteController*> sprites;
	Texture2D texture;
	std::string path;	
public:
	/// <summary>
	/// Konstruktor do klasy poprzez œcie¿kê
	/// </summary>
	/// <param name="path">Scie¿ka</param>
	SpriteController(const char* path);
	/// <summary>
	/// Konstruktor do klasy poprzez skopiowanie
	/// </summary>
	/// <param name="controller"></param>
	SpriteController(SpriteController& controller);
	/// <summary>
	/// Zwraca texturê która posiada obiekt
	/// </summary>
	/// <returns></returns>
	Texture2D getTexture() const { return texture; }
	/// <summary>
	/// Czyœci wszystkie wczytane textury
	/// </summary>
	static void closeSprites();

};

