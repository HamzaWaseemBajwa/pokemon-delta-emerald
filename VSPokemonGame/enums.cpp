//
// Created by Hamza Waseem Bajwa on 8/16/2017.
//
#include "enums.h"

double TypeEffect(const PokemonType attack, PokemonType def1, PokemonType def2)
{
	double powerMultiplier = 1.0;
	int a = 1;
	PokemonType* currentDef = &def1; //set current defensive type as the first defensive type
	for (int i = 0; i < a; i++)  //loops for defensive type, runs one for single type, and twice for dual typed pokemon
	{
		switch (attack) //switch case for Offensive type
		{
		case Fire:
			switch (*currentDef) //switch case for defense type
			{
			case Fire:
			case Water:
			case Rock:
			case Dragon:
				powerMultiplier /= 2;
				break;
			case Grass:
			case Steel:
			case Bug:
			case Ice:
				powerMultiplier *= 2;
				break;
			default:
				break;
			}
			break;
		case Water:
			switch (*currentDef)
			{
			case Fire:
			case Rock:
			case Ground:
				powerMultiplier *= 2;
				break;
			case Grass:
			case Water:
			case Dragon:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Grass:
			switch (*currentDef)
			{
			case Rock:
			case Ground:
			case Water:
				powerMultiplier *= 2;
				break;
			case Grass:
			case Fire:
			case Bug:
			case Flying:
			case Dragon:
			case Poison:
			case Steel:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Rock:
			switch (*currentDef)
			{

			case Fighting:
			case Ground:
			case Steel:
				powerMultiplier /= 2;
				break;
			case Fire:
			case Bug:
			case Flying:
			case Ice:
				powerMultiplier *= 2;
				break;
			default:
				break;
			}
			break;
		case Steel:
			switch (*currentDef)
			{
			case Rock:
			case Ice:
				powerMultiplier *= 2;
				break;
			case Water:
			case Fire:
			case Electric:
			case Steel:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Ground:
			switch (*currentDef)
			{
			case Fire:
			case Rock:
			case Poison:
			case Electric:
			case Steel:
				powerMultiplier *= 2;
				break;
			case Grass:
			case Bug:
				powerMultiplier /= 2;
				break;
			case Flying:
				powerMultiplier *= 0;
			default:
				break;
			}
			break;
		case Electric:
			switch (*currentDef)
			{
			case Water:
			case Flying:
				powerMultiplier *= 2;
				break;
			case Grass:
			case Dragon:
			case Electric:
				powerMultiplier /= 2;
				break;
			case Ground:
				powerMultiplier *= 0;
				break;
			default:
				break;
			}
			break;
		case Ghost:
			switch (*currentDef)
			{
			case Ghost:
			case Psychic:
				powerMultiplier *= 2;
				break;
			case Dark:
			case Steel:
				powerMultiplier /= 2;
				break;
			case Normal:
				powerMultiplier *= 0;
				break;
			default:
				break;
			}

			break;
		case Dark:
			switch (*currentDef)
			{
			case Psychic:
			case Ghost:
				powerMultiplier *= 2;
				break;
			case Fighting:
			case Dark:
			case Steel:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Psychic:
			switch (*currentDef)
			{
			case Fighting:
			case Poison:
				powerMultiplier *= 2;
				break;
			case Psychic:
			case Steel:
				powerMultiplier /= 2;
				break;
			case Ground:
				powerMultiplier *= 0;
				break;
			default:
				break;
			}
			break;
		case Fighting:
			switch (*currentDef)
			{
			case Rock:
			case Ice:
			case Steel:
			case Dark:
			case Normal:
				powerMultiplier *= 2;
				break;
			case Psychic:
			case Flying:
			case Bug:
			case Poison:
				powerMultiplier /= 2;
				break;
			case Ghost:
				powerMultiplier *= 0;
				break;
			default:
				break;
			}
			break;
		case Dragon:
			switch (*currentDef)
			{
			case Dragon:
				powerMultiplier *= 2;
				break;
			case Steel:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Normal:
			switch (*currentDef)
			{
			case Steel:
			case Rock:
				powerMultiplier /= 2;
				break;
			case Ghost:
				powerMultiplier *= 0;
				break;
			default:
				break;
			}
			break;
		case Ice:
			switch (*currentDef)
			{
			case Ground:
			case Flying:
			case Dragon:
			case Grass:
				powerMultiplier *= 2;
				break;
			case Steel:
			case Fire:
			case Water:
			case Ice:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Bug:
			switch (*currentDef)
			{
			case Dark:
			case Psychic:
			case Grass:
				powerMultiplier *= 2;
				break;
			case Steel:
			case Fire:
			case Fighting:
			case Rock:
			case Flying:
			case Ghost:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		case Flying:
			switch (*currentDef)
			{
			case Bug:
			case Fighting:
			case Grass:
				powerMultiplier *= 2;
				break;
			case Steel:
			case Rock:
			case Electric:
				powerMultiplier /= 2;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if (i == 0 && def2 != None) //if pokemon has a second type
		{
			a++;
			currentDef = &def2; //set the current dfesnive type as the second type
		}
	}
	return powerMultiplier;

}

double Nature(const int stat, const PokemonNature nature)
{
	double mult = 1.0;
	switch (stat) //switch on passed stat index
	{
	case 1:
		switch (nature) //switch on passed nature
		{
		case Lonely:
		case Brave:
		case Adamant:
		case Naughty:
			mult = 1.1;
			break;
		case Bold:
		case Modest:
		case Calm:
		case Timid:
			mult = 0.9;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (nature)
		{
		case Bold:
		case Relaxed:
		case Impish:
		case Lax:
			mult = 1.1;
			break;
		case Lonely:
		case Mild:
		case Gentle:
		case Hasty:
			mult = 0.9;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (nature)
		{
		case Modest:
		case Mild:
		case Rash:
		case Quiet:
			mult = 1.1;
			break;
		case Adamant:
		case Impish:
		case Careful:
		case Jolly:
			mult = 0.9;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (nature)
		{
		case Calm:
		case Gentle:
		case Careful:
		case Sassy:
			mult = 1.1;
			break;
		case Naughty:
		case Lax:
		case Rash:
		case Naive:
			mult = 0.9;
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (nature)
		{
		case Timid:
		case Hasty:
		case Jolly:
		case Naive:
			mult = 1.1;
			break;
		case Brave:
		case Relaxed:
		case Quiet:
		case Sassy:
			mult = 0.9;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return mult;
}
std::string to_string(const Stat stat)
{
	switch (stat)
	{
	case HP:
		return "HP";
	case Attack:
		return "Attack";
	case Defense:
		return "Defense";
	case SpAttack:
		return "SpAttack";
	case SpDefense:
		return "SpDefense";
	case Speed:
		return "Speed";
	default:
		return "";
	}
}

inline std::string to_string(const PokemonNature nature) {
	switch (nature) {
	case Hardy: return "Hardy";
	case Lonely: return "Lonely";
	case Brave: return "Brave";
	case Adamant: return "Adamant";
	case Naughty: return "Naughty";
	case Bold: return "Bold";
	case Docile: return "Docile";
	case Relaxed: return "Relaxed";
	case Impish: return "Impish";
	case Lax: return "Lax";
	case Timid: return "Timid";
	case Hasty: return "Hasty";
	case Serious: return "Serious";
	case Jolly: return "Jolly";
	case Naive: return "Naive";
	case Modest: return "Modest";
	case Mild: return "Mild";
	case Quiet: return "Quiet";
	case Bashful: return "Bashful";
	case Rash: return "Rash";
	case Calm: return "Calm";
	case Gentle: return "Gentle";
	case Sassy: return "Sassy";
	case Careful: return "Careful";
	case Quirky: return "Quirky";
	default: return "";
	}
}

std::string to_string(const PokemonType type) 
{
	switch (type)
	{
	case Grass: return "Grass";
	case Fire: return "Fire";
	case Poison: return "Poison";
	case None: return "None";
	case Water: return "Water";
	case Rock:  return "Rock";
	case Normal: return "Normal";
	case Electric: return "Electric";
	case Ice: return "Ice";
	case Fighting: return "Fighting";
	case Ground: return "Ground";
	case Flying: return "Flying";
	case Psychic: return "Psychic";
	case Bug: return "Bug";
	case Ghost: return "Ghost";
	case Dragon: return "Dragon";
	case Dark: return "Dark";
	case Steel: return "Steel";
	default:return "";
	}
}

std::string to_string(const StatusEffect effect) //Status bar effect text
{
	switch (effect)
	{
	case Paralysis:
		return "PAR";
	case Poisoning:
		return "PSN";
	case Burn:
		return "BRN";
	case Sleep:
		return "SLP";
	case Freeze:
		return "FRZ";
	case Faint:
		return "FNT";
	default:
		return "None";
	}
}


std::string EffectAppliedMessage(const StatusEffect effect) //text when effect is applied
{
	switch (effect)
	{
	case Paralysis:
		return " was paralyzed!";
	case Poisoning:
		return " was poisoned!";
	case Burn:
		return " was burned!";
	case Sleep:
		return " fell asleep!";
	case Freeze:
		return " was frozen";
	case NoEffect:
		return "";
	case Faint:
		return " fainted";
	default:
		return "None";
	}
}

std::string EffectEmphasisMessage(const StatusEffect effect) //text when effect causes damage
{
	switch (effect)
	{
	case Paralysis:
		return " is paralyzed!";
	case Poisoning:
		return " was affected by the poisoning!";
	case Burn:
		return " was affected by its burn!";
	case Sleep:
		return " is asleep!";
	case Freeze:
		return " is frozen";
	case NoEffect:
		return "";
	case Faint:
		return "";
	default:
		return "None";
	}
}

std::string EffectCuringMessage(const StatusEffect effect) //text when effect is cured
{
	switch (effect)
	{
	case Paralysis:
		return " was cured of its paralysis!";
	case Poisoning:
		return " was cured of its poisoning!";
	case Burn:
		return " was cured of its burn!";
	case Sleep:
		return " awoke!";
	case Freeze:
		return " thawed out";
	case NoEffect:
		return "";
	case Faint:
		return " was revived!";
	default:
		return "None";
	}
}


std::string to_string(const MoveCategory cat) 
{
	switch (cat)
	{
	case Physical:
		return "Physical";
	case Special:
		return "Special";
	default:
		return "Status";
	}
}
