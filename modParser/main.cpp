#include <iostream>
#include <fstream>

#include "Ingredients.h"
#include "Mod.h"

#include "StringsTable.h"
#include "BSAFile.h"

using namespace std;

float round(float v, int d)
{
	float p = pow(10.0f, d);
	return round(v * p) / p;
}

std::pair<std::string, std::string> loadPaths()
{
	std::pair<std::string, string> result;
	ifstream pathsFile("data/paths.txt");

	std::getline(pathsFile, result.first);
	std::getline(pathsFile, result.second);

	return result;
}

void exportConfig(const Config& config)
{
	ofstream modsFile("data/Plugins.txt");
	for (const auto& mod : config.modsList)
		modsFile << mod << endl;

	ofstream effectsFile("data/Effects.txt");
	for (const auto& effect : config.magicalEffectsList)
	{
		effectsFile << effect.second << endl;
		effectsFile << hex << uppercase << effect.first << dec << endl;
	}

	ofstream ingredientsFile("data/Ingredients.txt");
	for (const auto& ingr : config.ingredientsList.ingredients())
	{
		ingredientsFile << ingr.name << endl << ingr.modName << endl;
		ingredientsFile << hex << uppercase << ingr.id << dec << endl;
		for (const auto& effect : ingr.effects)
		{
			ingredientsFile << hex << uppercase << effect.id << dec << " ";
			ingredientsFile << round(effect.magnitude, 6) << " ";
			ingredientsFile << effect.duration << endl;
		}
	}
}

void loadMods(Config& config, const string& modsListFile, const string& dataDir)
{
	fstream modsList(modsListFile);
	array<char, 256> modName{};
	while (modsList.getline(&modName[0], 256))
	{
		if (modName[0] == '#')
			continue;
	//	cout << modName.data() << endl;

		Mod::parse(dataDir + "/" + modName.data(), config);
	}
}

int main(int argc, char** argv)
{
	Config config;

/*	auto paths = loadPaths();
	if (paths.first.empty() || paths.second.empty())
		return 1;

	loadMods(config, paths.first, paths.second);
	exportConfig(config);
*/
	StringsTable table;
	table.load("F:/Jeux/Skyrim/Data/HearthFires.esm");
//	BSAFile bsa;
//	bsa.load("F:/Jeux/Skyrim/Data/HearthFires");

	system("Pause");
	return 0;
}

