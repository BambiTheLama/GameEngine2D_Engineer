#pragma once
#include "SpriteController.h"
/// <summary>
/// Klasa od animacji obiekt�w
/// </summary>
class AnimationControler
{
	std::vector<SpriteController*> sprites;

public:
	/// <summary>
	/// konstruktor do kt�rej podajemy vektor z wszystkimi animacjami
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	AnimationControler(std::vector<SpriteController*> sprites);
	/// <summary>
	/// Konstruktor do kt�rej podajemy tylko jeden obiekt do anikacji
	/// </summary>
	/// <param name="sprite">obiekt do animacji</param>
	AnimationControler(SpriteController* sprite);
	/// <summary>
	/// Konstruktor do kt�rej podajemy tablice obiekt�w do animacji
	/// </summary>
	/// <param name="sprites">Obiekty do animowania</param>
	/// <param name="n">ilo�� obiekt�w</param>
	AnimationControler(SpriteController** sprites, int n);
	/// <summary>
	/// Destruktor wszystkich obiekt�w z spraitami
	/// </summary>
	~AnimationControler();
	/// <summary>
	/// Metoda od rysowania obiektu 
	/// </summary>
	/// <param name="pos">Pozycja w kt�rej ma by� obiekt</param>
	/// <param name="frame">Kt�ra klatka animacji ma by�</param>
	/// <param name="animationIndex">Kt�ry obiekt animacji ma by� u�yty</param>
	/// <param name="flippLeftRight">Czy rysujemy obiekt obracaj�c do z lewa na prawo</param>
	/// <param name="flipUpDown">Czy rysujemy obiekt obracaj�c z g�ry na d�</param>
	void draw(Rectangle pos, int frame=0, int animationIndex=0, bool flipLeftRight = false, bool flipUpDown = false);
};

