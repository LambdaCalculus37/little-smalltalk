/*
	Little Smalltalk

	primitive names and numbers recognized by the parser

*/

static struct prim_names {
	char *p_name;
	int p_number;
	} prim_table[] = {

	/* Operations on all objects */
{ "Class" , 1 },
{ "SuperObject", 2 },
{ "RespondsToNew", 3 },
{ "Size", 4 },
{ "HashNumber", 5},
{ "SameTypeOfObject", 6},
{ "Equality", 7},
{ "Debug", 8},
{ "GeneralityTest", 9},
	/* Integer Arithmetic Operations */
{ "IntegerAddition" , 10 },
{ "IntegerSubtraction", 11 },
{ "IntegerLessThan", 12 },
{ "IntegerGreaterThan", 13 },
{ "IntegerLessThanOrEqual", 14 },
{ "IntegerGreaterThanOrEqual", 15 },
{ "IntegerEquality", 16 },
{ "IntegerNonEquality", 17 },
{ "IntegerMultiplication", 18 },
{ "IntegerSlash", 19 },
{ "GCD", 20 },
{ "BitAt", 21 },
{ "BitOR", 22 },
{ "BitAND", 23 },
{ "BitXOR", 24 },
{ "BitShift", 25 },
{ "RadixPrint", 26 },
{ "IntegerDivision", 28 },
{ "IntegerMod", 29 },
{ "DoPrimitive", 30 },
{ "RandomFloat", 32 },
{ "BitInverse", 33 },
{ "HighBit", 34 },
{ "Random", 35 },
{ "IntegerToCharacter", 36 },
{ "IntegerToString", 37 },
{ "Factorial", 38 },
{ "IntegerToFloat", 39 },
	/* Character Operations */
{ "CharacterLessThan", 42 },
{ "CharacterGreaterThan", 43 },
{ "CharacterLessThanOrEqual", 44 },
{ "CharacterGreaterThanOrEqual", 45 },
{ "CharacterEquality", 46 },
{ "CharacterNonEquality", 47 },
{ "DigitValue", 50 },
{ "IsVowel", 51 },
{ "IsAlpha", 52 },
{ "IsLower", 53 },
{ "IsUpper", 54 },
{ "IsSpace", 55 },
{ "IsAlnum", 56 },
{ "ChangeCase", 57 },
{ "CharacterToString", 58 },
{ "CharacterToInteger", 59 },
	/* floating point operations */
{ "FloatAddition", 60 },
{ "FloatSubtraction", 61 },
{ "FloatLessThan", 62 },
{ "FloatGreaterThan", 63 },
{ "FloatLessThanOrEqual", 64 },
{ "FloatGreaterThanOrEqual", 65 },
{ "FloatEquality", 66 },
{ "FloatNonEquality", 67 },
{ "FloatMultiplication", 68 },
{ "FloatDivision", 69 },
{ "Log", 70 },
{ "SquareRoot", 71 },
{ "Floor", 72 },
{ "Ceiling", 73 },
{ "IntegerPart", 75 },
{ "FractionalPart", 76 },
{ "Gamma", 77 },
{ "FloatToString", 78},
{ "Exponent", 79},
{ "NormalizeRadian", 80},
{ "Sin", 81},
{ "Cos", 82},
{ "ArcSin", 84},
{ "ArcCos", 85},
{ "ArcTan", 86},
{ "Power", 88},
{ "FloatRadixPrint", 89},
	/* symbol operations */
{ "SymbolCompare", 91},
{ "SymbolPrintString", 92},
{ "SymbolAsString", 93},
{ "SymbolPrint", 94},
{ "NewClass", 97 },
{ "InstallClass", 98},
{ "FindClass", 99},
	/* string operations */
{ "StringLength", 100},
{ "StringCompare", 101},
{ "StringCompareWithoutCase", 102},
{ "StringCatenation", 103},
{ "StringAt", 104},
{ "StringAtPut", 105},
{ "CopyFromLength", 106},
{ "StringCopy", 107},
{ "StringAsSymbol", 108},
{ "StringPrintString", 109},
	/* arrays and other objects */
{ "NewObject", 110},
{ "At", 111},
{ "AtPut", 112},
{ "Grow", 113},
{ "NewArray", 114},
{ "NewString", 115},
{ "NewByteArray", 116},
{ "ByteArraySize", 117},
{ "ByteArrayAt", 118},
{ "ByteArrayAtPut", 119},
	/* I/O operations */
{ "PrintNoReturn", 120},
{ "PrintWithReturn", 121},
{ "Error", 122},
{ "ErrorPrint", 123},
{ "System", 125},
{ "PrintAt", 126},
{ "BlockReturn", 127},
{ "ReferenceError", 128},
{ "DoesNotRespond", 129},
	/* operations on files */
{ "FileOpen", 130},
{ "FileRead", 131},
{ "FileWrite", 132},
{ "FileSetMode", 133},
{ "FileSize", 134},
{ "FileSetPosition", 135},
{ "FileFindPosition", 136},
	/* Process management */
{ "BlockExecute", 140},
{ "NewProcess", 141},
{ "Terminate", 142},
{ "Perform", 143},
{ "SetProcessState", 145},
{ "ReturnProcessState", 146},
{ "StartAtomic", 148},
{ "EndAtomic", 149},
	/* operations on classes */
{ "ClassEdit", 150},
{ "SuperClass", 151},
{ "ClassName", 152},
{ "ClassNew", 153},
{ "PrintMessages", 154},
{ "RespondsTo", 155},
{ "ClassView", 156},
{ "ClassList", 157},
{ "Variables", 158},
	/* misc operations */
{ "CurrentTime", 160},
{ "TimeCounter", 161},
{ "Clear", 162},
{ "GetString", 163},
{ "StringAsInteger", 164},
{ "StringAsFloat", 165},
	/* that's all */
{ 0 , 0 } };

