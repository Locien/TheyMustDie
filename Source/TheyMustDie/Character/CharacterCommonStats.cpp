// ©Kris and Tashhhh 2023


#include "CharacterCommonStats.h"
#include "../Debug.h"
#include "CoreMinimal.h"

CharacterCommonStats::CharacterCommonStats()
{
	HP = 100;
	MaxHP = 100;
	PhysArmor = 10;
	MagicArmor = 10;
	PhysAttack = 20;
	MagicAttack = 20;
	Player = false;
	Dead = false;
}

CharacterCommonStats::~CharacterCommonStats()
{

}

CharacterCommonStats::CharacterCommonStats(signed int hp, signed int maxhp, signed int physarmor, signed int magicarmor, signed int physattack, signed int magicattack, bool player) :
	HP(hp), MaxHP(maxhp), PhysArmor(physarmor), MagicArmor(magicarmor), PhysAttack(physattack), MagicAttack(magicattack), Player(player), Dead(false)
{

}

signed int CharacterCommonStats::GetHP()
{
	return HP;
}

void CharacterCommonStats::SetHP(signed int NewHP)
{
	if(NewHP >= 0)
		HP = NewHP;
	else
	{
		Dead = true;
		HP = 0;
	}
}

signed int CharacterCommonStats::GetMaxHP()
{
	return MaxHP;
}

void CharacterCommonStats::SetMaxHP(signed int NewMaxHP, bool HealToFull)
{
	if(NewMaxHP > 0)
	{
		MaxHP = NewMaxHP;
		if(HealToFull || HP > MaxHP)
			HP = MaxHP;
	}
	else
	{
		MaxHP = 1;
		if(HealToFull || HP > MaxHP)
			HP = MaxHP;
	}
}

signed int CharacterCommonStats::GetPhysArmor()
{
	return PhysArmor;
}

void CharacterCommonStats::SetPhysArmor(signed int NewPhysArmor)
{
	PhysArmor = NewPhysArmor;
}

signed int CharacterCommonStats::GetMagicArmor()
{
	return MagicArmor;
}

void CharacterCommonStats::SetMagicArmor(signed int NewMagicArmor)
{
	MagicArmor = NewMagicArmor;
}

signed int CharacterCommonStats::GetPhysAttack()
{
	return PhysAttack;
}

void CharacterCommonStats::SetPhysAttack(signed int NewPhysAttack)
{
	PhysAttack = NewPhysAttack;
}

signed int CharacterCommonStats::GetMagicAttack()
{
	return MagicAttack;
}

void CharacterCommonStats::SetMagicAttack(signed int NewMagicAttack)
{
	MagicAttack = NewMagicAttack;
}

unsigned int CharacterCommonStats::ApplyPhysicalDamage(unsigned int PhysDmg)
{
	if(!Dead)
	{
		signed int DamageCalc = PhysDmg - PhysArmor;
		unsigned int OutDamage = (DamageCalc >= 0) ? (unsigned int)DamageCalc : 0; //Don't let damage become negative due to too much armor.
		HP -= (signed int)OutDamage;
		if(HP <= 0)
		{
			Dead = true;
			HP = 0;
		}

		return OutDamage;
	}
	else
	{
		Debug::ErrorMessage("Attempting to apply physical damage to dead character");
		return 0;
	}
}

bool CharacterCommonStats::isPlayer()
{
	return Player;
}

bool CharacterCommonStats::isDead()
{
	return Dead;
}
