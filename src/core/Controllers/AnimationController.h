#pragma once
#include "SpriteController.h"
/// <summary>
/// Klasa od animacji obiektów
/// </summary>
class AnimationController
{
	bool toDelete = false;
	std::vector<SpriteController*> sprites;

public:
	/// <summary>
	/// konstruktor do której podajemy vektor z wszystkimi animacjami
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	AnimationController(std::vector<SpriteController*> sprites);
	/// <summary>
	/// Konstruktor do której podajemy tylko jeden obiekt do anikacji
	/// </summary>
	/// <param name="sprite">obiekt do animacji</param>
	AnimationController(SpriteController* sprite);
	/// <summary>
	/// Konstruktor do której podajemy tablice obiektów do animacji
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	/// <param name="n">iloœæ obiektów</param>
	AnimationController(SpriteController** sprites, int n);
	/// <summary>
	/// Kostruktor który kopiuje dane z podobnego obiektu
	/// </summary>
	/// <param name="animations">obiekt z którego kopiujemy dane</param>
	AnimationController(AnimationController& animations);
	/// <summary>
	/// Destruktor wszystkich obiektów z spraitami
	/// </summary>
	~AnimationController();
	/// <summary>
	/// Metoda od rysowania obiektu 
	/// </summary>
	/// <param name="pos">Pozycja w której ma byæ obiekt</param>
	/// <param name="frame">Która klatka animacji ma byæ</param>
	/// <param name="animationIndex">Który obiekt animacji ma byæ u¿yty</param>
	/// <param name="flippLeftRight">Czy rysujemy obiekt obracaj¹c do z lewa na prawo</param>
	/// <param name="flipUpDown">Czy rysujemy obiekt obracaj¹c z góry na dó³</param>
	void draw(Rectangle pos, int frame=0, int animationIndex=0, bool flipLeftRight = false, bool flipUpDown = false);

	int getMaxFrames(int animationIndex = 0);
};

