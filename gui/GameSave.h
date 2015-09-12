#pragma once

#include <QString>
#include <QPixmap>

#include <array>
#include <vector>

class GameSave
{
public:
	static GameSave& instance() // Not a singleton, just the one everyone use
	{ static GameSave save; return save; }

	void loadSaveFromConfig();

	void load(QString fileName);
	bool isLoaded() const;

	QPixmap screenshot() const;

	struct Header
	{
		int saveNumber = 0, playerLevel = 0;
		QString playerName, playerLocation;
	};

	Header header() const;

	using KnownIngredients = std::vector<std::array<bool, 4>>;
	const KnownIngredients& knownIngredients() const; // Bool for each magical effect

	using InventoryItem = std::pair<int, int>; // Ingredient index in IngredientsList, number of ingredients
	using Inventory = std::vector<InventoryItem>;
	const Inventory& inventory() const;

	const std::vector<int> ingredientsCount() const; // Same as inventory, but more direct and with the 0-count ingredients

protected:
	void clear();

	bool m_isLoaded = false;
	QPixmap m_screenshot;
	Header m_header;
	KnownIngredients m_knownIngredients;
	Inventory m_inventory;
	std::vector<int> m_ingredientsCount;
};

//****************************************************************************//

inline bool GameSave::isLoaded() const
{ return m_isLoaded; }

inline QPixmap GameSave::screenshot() const
{ return m_screenshot; }

inline GameSave::Header GameSave::header() const
{ return m_header; }

inline const GameSave::KnownIngredients& GameSave::knownIngredients() const
{ return m_knownIngredients; }

inline const GameSave::Inventory& GameSave::inventory() const
{ return m_inventory; }

inline const std::vector<int> GameSave::ingredientsCount() const
{ return m_ingredientsCount; }