#include "Import.h"
#include "..\PexException.h"
#include "..\PexValue.h"
#include <unordered_map>
#include <boost\algorithm\string.hpp>

using namespace std;

typedef vector<string> vecstr;

PexNamedFunction Function(string name, papyrusBase::Value::ValueType returnType, bool isGlobal, bool isNative, vector<VarType> _param, unsigned int flag, string doc);

static const unordered_map<string, string> typeNameSwap{
	// Builtin Types
	{ "bool", "bool" },
	{ "float", "float" },
	{ "int", "int" },
	{ "string", "string" },
	{ "var", "var" },

	// Special
	{ "self", "Self" },

	// General Types
	{ "action", "Action" },
	{ "activator", "Activator" },
	{ "activemagiceffect", "ActiveMagicEffect" },
	{ "actor", "Actor" },
	{ "actorbase", "ActorBase" },
	{ "actorvalue", "ActorValue" },
	{ "alias", "Alias" },
	{ "ammo", "Ammo" },
	{ "apparatus", "Apparatus" },
	{ "armor", "Armor" },
	{ "associationtype", "AssociationType" },
	{ "book", "Book" },
	{ "cell", "Cell" },
	{ "class", "Class" },
	{ "constructibleobject", "ConstructibleObject" },
	{ "container", "Container" },
	{ "debug", "Debug" },
	{ "door", "Door" },
	{ "effectshader", "EffectShader" },
	{ "enchantment", "Enchantment" },
	{ "encounterzone", "EncounterZone" },
	{ "explosion", "Explosion" },
	{ "faction", "Faction" },
	{ "flora", "Flora" },
	{ "form", "Form" },
	{ "formlist", "FormList" },
	{ "furniture", "Furniture" },
	{ "game", "Game" },
	{ "globalvariable", "GlobalVariable" },
	{ "hazard", "Hazard" },
	{ "idle", "Idle" },
	{ "imagespacemodifier", "ImageSpaceModifier" },
	{ "impactdataset", "ImpactDataSet" },
	{ "ingredient", "Ingredient" },
	{ "key", "Key" },
	{ "keyword", "Keyword" },
	{ "leveledactor", "LeveledActor" },
	{ "leveleditem", "LeveledItem" },
	{ "leveledspell", "LeveledSpell" },
	{ "light", "Light" },
	{ "location", "Location" },
	{ "locationalias", "LocationAlias" },
	{ "locationreftype", "LocationRefType" },
	{ "magiceffect", "MagicEffect" },
	{ "math", "Math" },
	{ "message", "Message" },
	{ "miscobject", "MiscObject" },
	{ "musictype", "MusicType" },
	{ "objectreference", "ObjectReference" },
	{ "outfit", "Outfit" },
	{ "package", "Package" },
	{ "perk", "Perk" },
	{ "potion", "Potion" },
	{ "projectile", "Projectile" },
	{ "quest", "Quest" },
	{ "race", "Race" },
	{ "referencealias", "ReferenceAlias" },
	{ "refcollectionalias", "RefCollectionAlias" },
	{ "scene", "Scene" },
	{ "scroll", "Scroll" },
	{ "scriptobject", "ScriptObject" },
	{ "shout", "Shout" },
	{ "soulgem", "SoulGem" },
	{ "sound", "Sound" },
	{ "soundcategory", "SoundCategory" },
	{ "spell", "Spell" },
	{ "static", "Static" },
	{ "talkingactivator", "TalkingActivator" },
	{ "topic", "Topic" },
	{ "topicinfo", "TopicInfo" },
	{ "utility", "Utility" },
	{ "visualeffect", "VisualEffect" },
	{ "voicetype", "VoiceType" },
	{ "weapon", "Weapon" },
	{ "weather", "Weather" },
	{ "wordofpower", "WordOfPower" },
	{ "worldspace", "WorldSpace" },
};

PexNamedFunction Event(string name, string returnType, bool isGlobal, bool isNative, vector<VarType> _param, unsigned int flag, string doc)
{
	if (!boost::iequals(name.substr(0, 2), "on")) throw papyrusBase::PexException("Invalid event name (Event Name: " + name + ")");

	return Function(name, StringToType(returnType), false, false, _param, flag, doc);
 }

PexNamedFunction Function(string name, papyrusBase::Value::ValueType returnType, bool isGlobal, bool isNative, vector<VarType> _param, unsigned int flag, string doc)
{
	// header
	PexNamedFunction func(name);
	PexFunction& cur = func.getFunction();
	cur.setTypeName(returnType);

	// doc string
	cur.setDocString(doc);

	// user flags
	cur.setUserFlags(flag);

	// flags
	if (isGlobal) cur.setGlobal();
	if (isNative) cur.setNative();

	// parameters
	auto& param = cur.getParameters();
	param.insert(param.end(), _param.begin(), _param.end());

	// locals
	// done automatically in function

	using namespace papyrusBase;

	// function
	cur.p_Function
	(
		Int("A") = 5,
		Int("B") = Int("A"),
		String("Test") = Int("B").asString(),
		Return(String("Test")),

		If(Int("A") == 5 && String("Test") == "hahaha"),

		ElseIf(Int("A") != 5),

		Else(),

		EndIf()
	);

	PexInstructions instrs = cur.asInstructions();

	return func;
}
