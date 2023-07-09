#pragma once
/// <summary>
/// Klasa od scen które siê bêd¹ zmieniaæ w zale¿noœci od interacji u¿ytkownika
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Destruktor wirtualny potrzbny do usuwania scen
	/// </summary>
	virtual ~Scene() {}
	/// <summary>
	/// Metoda Startuj¹ce metody start dla obiektów
	/// </summary>
	virtual void start() = 0;
	/// <summary>
	/// Metoda aktualizujaca
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Metoda rysuj¹ca
	/// </summary>
	virtual void draw() = 0;
};

