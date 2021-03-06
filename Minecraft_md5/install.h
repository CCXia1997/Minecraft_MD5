#pragma once
#include "utility.h"
void inline install() {
	ofstream ofs("./output/install.mcfunction");

	ofs << "gamerule maxCommandChainLength 1000000" << endl;

	ofs << "scoreboard objectives add svars dummy" << endl;


	ofs << "kill @e[tag=md5.bit]" << endl;
	for (int i = 0; i < 32; i++) {
		ofs << R"(summon armor_stand ~)" << i <<
			R"( ~ ~ {CustomName:"{\"text\":\"bit)" << i << R"(\"}",NoGravity:1b,Invulnerable:1b,Invisible:1b,Tags:["md5.bit","md5.bit)" << i << R"("]})" <<
			endl;
	}

	for (int i = 1; i <= 32; i++) {
		for (int j = 0; j < i; j++) {
			ofs << R"(tag @e[tag=md5.bit)" << j << R"(] add L)" << i << endl;
		}
	}


	//make constants k[]
	ofs << "function md5:load_constants_k" << endl;

	//declare msg_char[]
	for (int i = 0; i < 577; i++) {
		DECLARE_INT(ofs, "msg_char" + to_string(i),  8);
	}

	//h0,h1,h2,h3
	DECLARE_INT(ofs, "h0",  32);
	DECLARE_INT(ofs, "h1",  32);
	DECLARE_INT(ofs, "h2",  32);
	DECLARE_INT(ofs, "h3",  32);

	//a,b,c,d,f,temp
	DECLARE_INT(ofs, "a",  32);
	DECLARE_INT(ofs, "b",  32);
	DECLARE_INT(ofs, "c",  32);
	DECLARE_INT(ofs, "d",  32);
	DECLARE_INT(ofs, "f",  32);
	DECLARE_INT(ofs, "temp",  32);
	DECLARE_INT(ofs, "temp1",  32);
	DECLARE_INT(ofs, "temp2",  32);
	DECLARE_INT(ofs, "temp3",  32);

	//declare w[]
	for (int i = 0; i < 16; i++) {
		DECLARE_INT(ofs, "w" + to_string(i), 32);
	}

	//make constants
	MAKE_SCONST(ofs, 1);
	MAKE_SCONST(ofs, 2);
	MAKE_SCONST(ofs, 4);
	MAKE_SCONST(ofs, 8);
	MAKE_SCONST(ofs, 16);
	MAKE_SCONST(ofs, 32);
	MAKE_SCONST(ofs, 64);

	//make result
	ofs << "scoreboard objectives add md5.result dummy" << endl;

	ofs << "scoreboard objectives add md5.login minecraft.custom:minecraft.leave_game" << endl;

	ofs << R"(summon minecraft:armor_stand ~ 0 ~ {NoGravity:1b,Invisible:1,Invulnerable:1,Tags:["md5.enabled"]})" << endl;
	ofs.close();
}

void inline install_wrapper() {
	ofstream ofs("./output/install_wrapper.mcfunction");
	ofs << "execute unless entity @e[tag=md5.enabled] run function md5:install" << endl;
}
