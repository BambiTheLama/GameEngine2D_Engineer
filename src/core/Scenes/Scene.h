#pragma once
/// <summary>
/// Klasa od scen kt�re si� b�d� zmienia� w zale�no�ci od interacji u�ytkownika
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Metoda aktualizujaca
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Metoda rysuj�ca
	/// </summary>
	virtual void draw() = 0;
};

