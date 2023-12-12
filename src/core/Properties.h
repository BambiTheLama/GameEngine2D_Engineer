#pragma once
#include "raylib.h"
#define textStandardSize 26
#define textStandardSize2 30
#define collidersToDraw Properties::getProperties()->getShowColliders()
/// <summary>
/// Rysuje text z domyslna czciaka uzytkownika
/// </summary>
/// <param name="text">Text do narysowania </param>
/// <param name="x">Pozycja x</param>
/// <param name="y">Pozycja y</param>
/// <param name="size">Wielkosc czciaki</param>
/// <param name="color">Kolor tekstu</param>
void drawText(const char* text, int x, int y, int size, Color color);
/// <summary>
/// Zwraca rozmiar tekstu
/// </summary>
/// <param name="text">tekst do zmierzenia</param>
/// <param name="size">wielkosc czciaki</param>
/// <param name="spacing">odleglosc miedzy znakami</param>
/// <returns>Wysokosc i szerokosc textu</returns>
Vector2 textSize(const char* text, int size, int spacing=0);
/// <summary>
/// Rysuje tekst pogrubiony z pewnym kolorem z domyslna czciaka uzytkownika
/// </summary>
/// <param name="text">Text do narysowania </param>
/// <param name="x">Pozycja x</param>
/// <param name="y">Pozycja y</param>
/// <param name="fontSize">Wielkosc chciaki</param>
/// <param name="textColor">Kolor tekstu</param>
/// <param name="outlineColor">Kolor konturu tekstu</param>
void DrawTextWithOutline(const char* text, int x, int y, int fontSize, Color textColor, Color outlineColor);
/// <summary>
/// zwraca jaki klawisz zostal klikniety
/// </summary>
/// <returns></returns>
int keyPressed();
/// <summary>
/// Zwraca czy zostal jakis przycisk klikniety
/// </summary>
/// <returns></returns>
bool isAnyKeyPressed();
/// <summary>
/// Rysuje celownik uzywany do niszczenia i stawianai obiektow
/// </summary>
/// <param name="pos">Pozycja celeownika</param>
/// <param name="c">Kolor celownika</param>
void drawViewFinder(Rectangle pos, Color c = WHITE);
class Properties
{
	static Properties* properties;
	bool showColliders = false;
	Font font;
	Texture2D viewFinder;
	Properties();
	~Properties();
public:
	static Properties* getProperties();
	/// <summary>
	/// Rysuje text z domyslna czciaka uzytkownika
	/// </summary>
	/// <param name="text">Text do narysowania </param>
	/// <param name="x">Pozycja x</param>
	/// <param name="y">Pozycja y</param>
	/// <param name="size">Wielkosc czciaki</param>
	/// <param name="color">Kolor tekstu</param>
	void drawText(const char* text, int x, int y, int size, Color color);
	/// <summary>
	/// Zwraca rozmiar tekstu
	/// </summary>
	/// <param name="text">tekst do zmierzenia</param>
	/// <param name="size">wielkosc czciaki</param>
	/// <param name="spacing">odleglosc miedzy znakami</param>
	/// <returns>Wysokosc i szerokosc textu</returns>
	Vector2 textSize(const char* text, int size, int spacing);
	/// <summary>
	/// Zwaca czy maja byc rysowane collizje obiektow
	/// </summary>
	/// <returns></returns>
	bool getShowColliders() const { return showColliders; }
	/// <summary>
	/// Rysuje celownik uzywany do niszczenia i stawianai obiektow
	/// </summary>
	/// <param name="pos">Pozycja celeownika</param>
	/// <param name="c">Kolor celownika</param>
	void drawViewFinder(Rectangle pos, Color c = WHITE);

	friend class Engine;
};

