#include<iostream>
#include<regex>
#include<string.h>
using namespace std;
typedef struct symbols
{
	char key[10];
	int val;
}Symbols;
Symbols table[100];
int size = 0;
int getSymbolTableValue(char* variable)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(table[i].key, variable))
			return table[i].val;
	}
	cout << "Variable Not Defined" << endl<<endl;
	return 0;
}
void performPrint(char* eqn)
{
	char variables[10];
	sscanf(eqn, "print %[^\n]\n", variables);
	cout << getSymbolTableValue(variables)<<endl<<endl;
}
int isInteger(char* expression)
{
	int i = 0;
	while (expression[i] == ' ')
		i++;
	for (; expression[i] != '\0' && expression[i] != ' '; i++)
		if ((int)expression[i] < 48 || (int)expression[i] > 58)
			return 0;
	while (expression[i] == ' ')
		i++;
	if (expression[i] == '\0')
		return 1;
	else
		return 0;
}
int equationEval(char* eqn)
{
	if (isInteger(eqn))
	{
		int value=0;
		sscanf(eqn, "%d", &value);
		return value;
	}
	else
	{
		if (regex_match(eqn, regex("((.*)[+*-/])(.*)")))
		{
			char operand[90];
			char variable[10];
			char operation[4];
			sscanf(eqn, "%s %s %[^\n]\n", variable,operation, operand);
			if (!strcmp(operation, "+"))
				return getSymbolTableValue(variable) + equationEval(operand);
			else if (!strcmp(operation, "*"))
				return getSymbolTableValue(variable) * equationEval(operand);
			else if (!strcmp(operation, "-"))
				return getSymbolTableValue(variable) - equationEval(operand);
			else if (!strcmp(operation, "/"))
				return getSymbolTableValue(variable) / equationEval(operand);
		}
		else
			return getSymbolTableValue(eqn);
	}
}
void addToSymbolTable(char* variable, int value)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp(table[i].key, variable))
		{
			table[i].val = value;
			return;
		}
	}
	strcpy(table[size].key, variable);
	table[size++].val = value;
}
void main()
{
	addToSymbolTable("a", 5);
	addToSymbolTable("b", 10);
	while (true)
	{
		cout << "$ ";
		char eqn[100];
		fflush(stdin);
		scanf("%[^\n]s", eqn);
		if (!strcmp(eqn, "exit"))
			return;
		if (regex_match(eqn, regex("(print)(.*)")))
		{
			performPrint(eqn);
		}
		else
		{
			char variable[10];
			char operand[90];
			sscanf(eqn, "%[abcdefghijklmnopqrstuvwxyz+|012345689+]%*[ \t ]=%[^\n]\n", variable, operand);
			addToSymbolTable(variable, equationEval(operand));
		}
	}
}