#pragma once
#include "../GameObject.h"
/// <summary>
/// Interface s�u��cy za komponeet kt�ry odpowiada za uniki postaci
/// </summary>
class DodgeInterface
{
	int dodgeTime;
	int dodgeTimeMax;
	int dodgeCDR;
	int dodgeCDRMax;
	Vector2 deltaMove;
	GameObject* thisObj;
public:
	/// <summary>
	/// Konstruktor interfejsu do unik�w
	/// </summary>
	/// <param name="dodgeTime">Czas potrzebny na wykonanie uniku</param>
	/// <param name="dodgeCDR">Czas potrzebny do odnowienia uniku</param>
	DodgeInterface(int dodgeTime, int dodgeCDR);
	/// <summary>
	/// Kopiuje dane z innego obiektu
	/// </summary>
	/// <param name="dodge">Obiekt do skopiowania</param>
	DodgeInterface(DodgeInterface& dodge);
	/// <summary>
	/// Aktualizuje dane
	/// </summary>
	void update(float deltaTime);
	/// <summary>
	/// Metoda wykonuj�ca unik w podan� pozycj�
	/// </summary>
	/// <param name="deltaMove">Pozycja do uniku</param>
	bool doDodge(Vector2 deltaMove);
};

