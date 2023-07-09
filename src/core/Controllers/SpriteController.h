#pragma once
#include <vector>
#include <string>
#include "raylib.h"
/// <summary>
/// Klasa do trzymania textur w jednym miejscu i sprawdzaniu czy ju� zosta�a takowa wczytana
/// </summary>
class SpriteController
{
	static std::vector<SpriteController*> sprites;
	Texture2D texture;
	std::string path;	
public:
	/// <summary>
	/// Konstruktor do klasy poprzez �cie�k�
	/// </summary>
	/// <param name="path">Scie�ka</param>
	SpriteController(const char* path);
	/// <summary>
	/// Konstruktor do klasy poprzez skopiowanie
	/// </summary>
	/// <param name="controller"></param>
	SpriteController(SpriteController& controller);
	/// <summary>
	/// Zwraca textur� kt�ra posiada obiekt
	/// </summary>
	/// <returns></returns>
	Texture2D getTexture() const { return texture; }
	/// <summary>
	/// Czy�ci wszystkie wczytane textury
	/// </summary>
	static void closeSprites();

};

