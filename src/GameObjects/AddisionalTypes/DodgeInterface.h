#pragma once
#include "../GameObject.h"
/// <summary>
/// Interface s³u¿¹cy za komponeet który odpowiada za uniki postaci
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
	/// Konstruktor interfejsu do uników
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
	/// Metoda wykonuj¹ca unik w podan¹ pozycjê
	/// </summary>
	/// <param name="deltaMove">Pozycja do uniku</param>
	bool doDodge(Vector2 deltaMove);
};

