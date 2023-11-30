// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class THEYMUSTDIE_API CharacterCommonStats
{
public:
	CharacterCommonStats();
	~CharacterCommonStats();

	CharacterCommonStats(signed int HP, signed int MaxHP, signed int PhysArmor, signed int MagicArmor, signed int PhysAttack, signed int MagicAttack, bool isplayer);

	//Gets the hit points of this character.
	signed int GetHP();

	//Sets the hit points of this character.
	void SetHP(signed int NewHP);

	//Gets the max hit points of this character.
	signed int GetMaxHP();

	//Sets the max hit points of this character. If HealToFull is set to true this character will be healed to its new full max HP.
	void SetMaxHP(signed int NewMaxHP, bool HealToFull);

	//Gets the physical armor of this character.
	signed int GetPhysArmor();

	//Sets the physical armor of this character.
	void SetPhysArmor(signed int NewPhysArmor);

	//Gets the magical armor of this character.
	signed int GetMagicArmor();

	//Sets the magical armor of this character.
	void SetMagicArmor(signed int NewMagicArmor);

	//Gets the physical attack of this character.
	signed int GetPhysAttack();

	//Sets the physical attack of this character.
	void SetPhysAttack(signed int NewPhysAttack);

	//Gets the magical attack of this character.
	signed int GetMagicAttack();

	//Sets the magical attack of this character.
	void SetMagicAttack(signed int NewMagicAttack);

	//Applies physical damage according to unsigned int PhysDmg and returns the damage after calculations.
	unsigned int ApplyPhysicalDamage(unsigned int PhysDmg);

	//Returns true if this character is a player. False if it's an enemy unit.
	bool isPlayer();

	//Returns true if this character is dead. False if it's alive.
	bool isDead();

private:
	//The hit points of this character.
	signed int HP;
	//The max hit points of this character.
	signed int MaxHP;
	//The physical armor of this character.
	signed int PhysArmor;
	//The magical armor of this character.
	signed int MagicArmor;
	//The physical attack value of this character.
	signed int PhysAttack;
	//The magical attack value of this character.
	signed int MagicAttack;
	//If true this character is a player character. If false it's an enemy character.
	bool Player;
	//If true this character is dead, false if it's alive.
	bool Dead;
};
