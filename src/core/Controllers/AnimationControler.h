#pragma once
#include "SpriteController.h"
/// <summary>
/// Klasa od animacji obiektów
/// </summary>
class AnimationControler
{
	std::vector<SpriteController*> sprites;

public:
	/// <summary>
	/// konstruktor do której podajemy vektor z wszystkimi animacjami
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	AnimationControler(std::vector<SpriteController*> sprites);
	/// <summary>
	/// Konstruktor do której podajemy tylko jeden obiekt do anikacji
	/// </summary>
	/// <param name="sprite">obiekt do animacji</param>
	AnimationControler(SpriteController* sprite);
	/// <summary>
	/// Konstruktor do której podajemy tablice obiektów do animacji
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	/// <param name="n">iloœæ obiektów</param>
	AnimationControler(SpriteController** sprites, int n);
	/// <summary>
	/// Destruktor wszystkich obiektów z spraitami
	/// </summary>
	~AnimationControler();
	/// <summary>
	/// Metoda od rysowania obiektu 
	/// </summary>
	/// <param name="pos">Pozycja w której ma byæ obiekt</param>
	/// <param name="frame">Która klatka animacji ma byæ</param>
	/// <param name="animationIndex">Który obiekt animacji ma byæ u¿yty</param>
	/// <param name="flippLeftRight">Czy rysujemy obiekt obracaj¹c do z lewa na prawo</param>
	/// <param name="flipUpDown">Czy rysujemy obiekt obracaj¹c z góry na dó³</param>
	void draw(Rectangle pos, int frame=0, int animationIndex=0, bool flipLeftRight = false, bool flipUpDown = false);
};

