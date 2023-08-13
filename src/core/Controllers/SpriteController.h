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
	std::string path;
	Texture2D texture;

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
	Rectangle getTextureFrame(int frame) { return { (float)texture.height * (frame % getHowMuchFrames()),0,(float)texture.height,(float)texture.height }; }
	/// <summary>
	/// Zwraca ile jest klatek (szerokoœæ/wysokoœæ)
	/// </summary>
	/// <returns>iloœæ klatek</returns>
	int getHowMuchFrames() { return texture.width / texture.height; }
	/// <summary>
	/// Rysuje ca³¹ texture w podanej pozycji
	/// </summary>
	/// <param name="pos">Pozycja do rysowania</param>
	void draw(Rectangle pos);
	/// <summary>
	/// Rysuje odpowiedni¹ klatkê w podanej pozycji
	/// </summary>
	/// <param name="pos">Pozycja w której rysujemy</param>
	/// <param name="frame">Klatka któr¹ ma narysowac</param>
	void draw(Rectangle pos, int frame);
};

