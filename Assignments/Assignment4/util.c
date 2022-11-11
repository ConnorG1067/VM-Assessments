#include <stdio.h>
#include "defs.h"

char* typeToString(GhostEnumType type){
	switch(type){
		case POLTERGEIST:
			return "Poltergeist";
		case WRAITH:
			return "Wraith";
		case PHANTOM:
			return "Phantom";
		case BULLIES:
			return "Bullies";
		case OTHER:
			return "OTHER";
	}

}
