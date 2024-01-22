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
	/// Metoda startujaca po stworzeniu sceny
	/// </summary>
	virtual void start() = 0;
	/// <summary>
	/// Metoda aktualizujaca sie cyklicznie do dany odstep czasu
	/// </summary>
	/// <param name="deltaTime">Odstep czasu od ostatniej aktualizacjai</param>
	virtual void update(float deltaTime) = 0;
	/// <summary>
	/// Metoda rysuj¹ca
	/// </summary>
	virtual void draw() = 0;
};

