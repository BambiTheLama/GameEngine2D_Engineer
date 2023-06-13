#pragma once
#include "Scenes/Scene.h"

/// <summary>
/// G³ówna klasa która odpowiada za pêtlê gry 
/// </summary>
class Engine
{
	static Scene* scene;
public:
	/// <summary>
	/// Kretor domyœlny tworzy okno gry i ustawia podstawowe parametry
	/// </summary>
	Engine();
	/// <summary>
	/// Destruktor domyœlny usuwa wszystkie zalokowane fragmenty pamiêci
	/// </summary>
	~Engine();
	/// <summary>
	/// Metoda która startuje g³ówn¹ pêtle metoda koniczy siê po skoniczeniu pêtli gry
	/// </summary>
	void start();
	/// <summary>
	/// Metoda która aktualizuje wszsytkie obiekty
	/// </summary>
	void update();
	/// <summary>
	/// Metoda która rysuje wszystkie obiekty
	/// </summary>
	void draw();
	/// <summary>
	/// Podmienia scenê a takrze usuwa poprzedni¹
	/// </summary>
	/// <param name="scene">Nowa scena</param>
	static void setScene(Scene* scene);

};

