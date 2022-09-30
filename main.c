#include <stdio.h>
#include <string.h>
#define size_cells 65535

int cells[size_cells] = {0};
unsigned short functions[size_cells][1025] = {{0}};
unsigned short cell = 0;
unsigned short points[1] = {0};
unsigned short flags[4] = {0, 0, 0, 0, 0};

int *generate(char *input)
{
	int *code = malloc(strlen(input));
	for (unsigned short SymbolPos; SymbolPos < strlen(input); SymbolPos++)
	{
		switch (input[SymbolPos])
		{
		case '>':
			code[SymbolPos] = 1;
			break;

		case '<':
			code[SymbolPos] = 2;
			break;

		case '+':
			code[SymbolPos] = 3;
			break;

		case '-':
			code[SymbolPos] = 4;
			break;

		case ',':
			code[SymbolPos] = 5;
			break;

		case '[':
			code[SymbolPos] = 6;
			break;

		case ']':
			code[SymbolPos] = 7;
			break;

		case '/':
			code[SymbolPos] = 8;
			break;

		case '@':
			code[SymbolPos] = 9;
			break;

		case '!':
			code[SymbolPos] = 10;
			break;

		case '(':
			code[SymbolPos] = 11;
			break;

		case ')':
			code[SymbolPos] = 12;
			break;

		case ':':
			code[SymbolPos] = 13;
			break;

		case ';':
			code[SymbolPos] = 14;
			break;

		case '#':
			code[SymbolPos] = 15;
			break;

		case ' ':
			break;
		default:
			printf("%d:SynatxError: Instruction '%c' not found\n", SymbolPos, input[SymbolPos]);
			exit(0);
			break;
		}
	}
	return code;
}

void interpret(unsigned short instruction)
{
	switch (instruction)
	{
	// right
	case 1:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
		{
			if (cell >= size_cells)
			{
				printf("%d:CellsError: Limit of cells\n", instruction);
			}
			else
			{
				cell += 1;
			}
		}
		break;

	// left
	case 2:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
		{
			if (cell <= 0)
			{
				printf("%d:CellsError: Limit of cells\n", instruction);
			}
			else
			{
				cell -= 1;
			}
		}
		break;

	// add 1 to the current cell
	case 3:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[cell] += 1;
		break;

	// subtract 1 from the current cell
	case 4:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[cell] -= 1;
		break;

	// invert value (x, -x)
	case 5:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[cell] = cells[cell] * -1;
		break;

	// point 1 = cell
	case 6:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			points[0] = cell;
		break;

	// point 2 = cell
	case 7:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			points[1] = cell;
		break;

	// copy from point 1 to point 2
	case 8:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[points[1]] = cells[points[0]];
		break;

	// print a character from ascii a table whose value is equal to the current cell
	case 9:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			printf("%c", cells[cell]);
		break;

	// print current value of cell
	case 10:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			printf("%d\n", cells[cell]);
		break;

	// start writing an array
	case 11:
		flags[0] = 1;
		break;

	// end writing an array
	case 12:
		flags[0] = 0;
		break;

	// add point 1, point 2 and write to the cell
	case 13:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[cell] = cells[points[0]] + cells[points[1]];
		break;

	// subtract point 1, point 2 and write to the cell
	case 14:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			cells[cell] = cells[points[0]] - cells[points[1]];
		break;

	// interpret function in point 1
	case 15:
		if (flags[0])
		{
			functions[cell][functions[cell][1025]] = instruction;
			functions[cell][1025] += 1;
		}
		else
			for (unsigned short finstruction = 0; finstruction < functions[points[0]][1025]; finstruction++)
				interpret(functions[points[0]][finstruction]);
		break;
	}
}

int main()
{
	//  code
	char *code = "!+";

	// interpret
	for (unsigned short instruction = 0; instruction < strlen(code); instruction++)
	{
		interpret(generate(code)[instruction]);
	}
}
