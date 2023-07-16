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
	/// <summary>
	/// Zwraca ca³¹ wielkoœæ textury
	/// </summary>
	/// <returns>Ca³e wymiary textury</returns>
	Rectangle getTextureSize() { return { 0,0,(float)texture.width,(float)texture.height }; }
	/// <summary>
	/// Zwraca klatkê klatka jest brana na podstawie wyskoœci 
	/// </summary>
	/// <param name="frame">Któr¹ klatkê wzi¹œc</param>
	/// <returns>Miejsce gdzie jest dana klatka</returns>
	Rectangle getTextureFrame(int frame) { return { (float)texture.height * (frame % howMuchFrames()),0,(float)texture.height,(float)texture.height }; }
	/// <summary>
	/// Zwraca ile jest klatek (szerokoœæ/wysokoœæ)
	/// </summary>
	/// <returns>iloœæ klatek</returns>
	int howMuchFrames() { return texture.width / texture.height; }
};

