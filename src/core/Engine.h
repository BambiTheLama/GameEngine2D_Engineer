#pragma once
#include "Scenes/Scene.h"

/// <summary>
/// G��wna klasa kt�ra odpowiada za p�tl� gry 
/// </summary>
class Engine
{
	static Scene* scene;
public:
	/// <summary>
	/// Kretor domy�lny tworzy okno gry i ustawia podstawowe parametry
	/// </summary>
	Engine();
	/// <summary>
	/// Destruktor domy�lny usuwa wszystkie zalokowane fragmenty pami�ci
	/// </summary>
	~Engine();
	/// <summary>
	/// Metoda kt�ra startuje g��wn� p�tle metoda koniczy si� po skoniczeniu p�tli gry
	/// </summary>
	void start();
	/// <summary>
	/// Metoda kt�ra aktualizuje wszsytkie obiekty
	/// </summary>
	void update();
	/// <summary>
	/// Metoda kt�ra rysuje wszystkie obiekty
	/// </summary>
	void draw();
	/// <summary>
	/// Podmienia scen� a takrze usuwa poprzedni�
	/// </summary>
	/// <param name="scene">Nowa scena</param>
	static void setScene(Scene* scene);

};

