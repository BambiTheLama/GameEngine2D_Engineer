#pragma once
#include <vector>
#include <string>
#include "raylib.h"
#include <iostream>
/// <summary>
/// Klasa do trzymania textur w jednym miejscu i sprawdzaniu czy ju� zosta�a takowa wczytana
/// </summary>
class SpriteController
{
	static std::vector<SpriteController*> sprites;
	std::string path="";
	Texture2D texture;
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
	~SpriteController();
	/// <summary>
	/// Zwraca textur� kt�ra posiada obiekt
	/// </summary>
	/// <returns></returns>
	Texture2D getTexture() const { return texture; }
	/// <summary>
	/// Czy�ci wszystkie wczytane textury
	/// </summary>
	static void closeSprites();
	/// <summary>
	/// Zwraca ca�� wielko�� textury
	/// </summary>
	/// <returns>Ca�e wymiary textury</returns>
	Rectangle getTextureSize() { return { 0,0,(float)texture.width,(float)texture.height }; }
	/// <summary>
	/// Zwraca klatk� klatka jest brana na podstawie wysko�ci 
	/// </summary>
	/// <param name="frame">Kt�r� klatk� wzi��c</param>
	/// <returns>Miejsce gdzie jest dana klatka</returns>
	Rectangle getTextureFrame(int frame) { return { (float)texture.height * (frame % getHowMuchFrames()),0,(float)texture.height,(float)texture.height }; }
	/// <summary>
	/// Zwraca ile jest klatek (szeroko��/wysoko��)
	/// </summary>
	/// <returns>ilo�� klatek</returns>
	int getHowMuchFrames() { return texture.width / texture.height; }
	/// <summary>
	/// Rysuje ca�� texture w podanej pozycji
	/// </summary>
	/// <param name="pos">Pozycja do rysowania</param>
	void draw(Rectangle pos);
	/// <summary>
	/// Rysuje odpowiedni� klatk� w podanej pozycji
	/// </summary>
	/// <param name="pos">Pozycja w kt�rej rysujemy</param>
	/// <param name="frame">Klatka kt�r� ma narysowac</param>
	void draw(Rectangle pos, int frame);
	/// <summary>
	/// Sprawdza czy textura zosta�a wczytana
	/// </summary>
	/// <returns></returns>
	bool isLoaded() { return texture.id > 0; }

	std::string getPath() { return path; }

	bool comparePath(std::string p) { return p.compare(path)==0; }

};

