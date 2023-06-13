#pragma once
/// <summary>
/// Klasa od scen które siê bêd¹ zmieniaæ w zale¿noœci od interacji u¿ytkownika
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Metoda aktualizujaca
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Metoda rysuj¹ca
	/// </summary>
	virtual void draw() = 0;
};

