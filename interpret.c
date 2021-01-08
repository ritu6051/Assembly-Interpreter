#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ax, bx, cx, dx;
int getRegisterValue(char *registerx)
{
	if(strcmp(registerx,"ax") == 0)
	{
		return ax;
	}
	if(strcmp(registerx,"bx") == 0)
	{
		return bx;
	}
	if(strcmp(registerx,"cx") == 0)
	{
		return cx;
	}
	if(strcmp(registerx,"dx") == 0)
	{
		return dx;
	}
}

void saveInRegister(char *registerx, int value)
{
	if(strcmp(registerx,"ax") == 0)
	{
		ax = value;
	}
	if(strcmp(registerx,"bx") == 0)
	{
		bx = value;
	}
	if(strcmp(registerx,"cx") == 0)
	{
		cx = value;
	}
	if(strcmp(registerx,"dx") == 0)
	{
		dx = value;
	}
}

int main(int argc, char* argv[])
{
    FILE *ptr;
	ptr = fopen(argv[1],"r");
	char line[100][50];
    char instruction[50];
	int num1;
	int num2;
	int n = 0;
	int input;
	int i = 0;
	char arg2[50];
	char arg3[50];
	char arg4[50];
	int jump;
  
    if(ptr == NULL)
	{
		printf("Empty file");
	}

	while(fgets(line[i], 50, ptr))
	{
		line[i][strlen(line[i]) - 1] = '\0';
		i++;
	}
	
	int tot = i;

	for(i = 0; i < tot; i++)
	{
		if(strcmp(line[i],"\0") == 0)
		{
			continue;
		}
		else
		{
			sscanf(line[i],"%s", instruction);
			sscanf(line[i],"%s %s", instruction, arg2);
			sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
			sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4);
			if(strcmp(instruction,"read") == 0)
			{
				sscanf(line[i],"%s %s", instruction, arg2);
				if(strcmp(arg2,"ax") == 0)
				{
					scanf("%d", &input);
					ax = input;
					break;
				}
				if(strcmp(arg2,"bx") == 0)
				{
					scanf("%d", &input);
					bx = input;
					break;
				}
				if(strcmp(arg2,"cx") == 0)
				{
					scanf("%d", &input);
					cx = input;
					break;
				}
				if(strcmp(arg2,"dx") == 0)
				{
					scanf("%d", &input);
					dx = input;
					break;
				}
			} 	
			if(strcmp(instruction,"print") == 0)
			{ 
				sscanf(line[i],"%s %s", instruction, arg2);
				if(strcmp(arg2,"ax") == 0)
				{
					printf("%d",ax);
					break;
				}
				else if(strcmp(arg2,"bx") == 0)
				{
					printf("%d",bx);
					break;
				}
				else if(strcmp(arg2,"cx") == 0)
				{
					printf("%d",cx);
					break;
				}
				else if(strcmp(arg2,"dx") == 0)
				{
					printf("%d",dx);
					break;
				}
				else
				{
					int temp = atoi(arg2);
					printf("%d", temp);
					break;
				}
			} 
			if(strcmp(instruction,"add") == 0)
			{
				sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
				if(strcmp(arg2,"ax") == 0 || strcmp(arg2,"bx") == 0 || strcmp(arg2,"cx") == 0 || strcmp(arg2,"dx") == 0)
				{
					n = getRegisterValue(arg2) + getRegisterValue(arg3);
					saveInRegister(arg3, n);
				}
				else
				{
					num1 = atoi(arg2);
					n = getRegisterValue(arg3) + num1;
					saveInRegister(arg3, n);
				} 
				break;
			}
			if(strcmp(instruction,"sub") == 0)
			{
				sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
				if(strcmp(arg2,"ax") == 0 || strcmp(arg2,"bx") == 0 || strcmp(arg2,"cx") == 0 || strcmp(arg2,"dx") == 0)
				{
					n = getRegisterValue(arg3) - getRegisterValue(arg2);
					saveInRegister(arg3, n);
				}
				else
				{
					num1 = atoi(arg2);
					n = getRegisterValue(arg3) - num1;
					saveInRegister(arg3, n);
				}
				break;
			} 
			if(strcmp(instruction,"mul") == 0)
			{
				sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
				if(strcmp(arg2,"ax") == 0 || strcmp(arg2,"bx") == 0 || strcmp(arg2,"cx") == 0 || strcmp(arg2,"dx") == 0)
				{
					n = getRegisterValue(arg2) * getRegisterValue(arg3);
					saveInRegister(arg3, n);
				}
				else
				{
					num1 = atoi(arg2);
					n = num1 * getRegisterValue(arg3);
					saveInRegister(arg3, n);
				}
				break;
			} 
			else if(strcmp(instruction,"div") == 0)
			{
				sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
				if(strcmp(arg2,"ax") == 0 || strcmp(arg2,"bx") == 0 || strcmp(arg2,"cx") == 0 || strcmp(arg2,"dx") == 0)
				{
					n = getRegisterValue(arg2) / getRegisterValue(arg3);
					saveInRegister(arg3, n);
				}
				else
				{
					num1 = atoi(arg2);
					n = num1 / getRegisterValue(arg3);
					saveInRegister(arg3, n);
				}
				break;
			}
			else if(strcmp(instruction,"mov") == 0)
			{
				sscanf(line[i],"%s %s %s", instruction, arg2, arg3);
				if(strcmp(arg2,"ax") == 0 || strcmp(arg2,"bx") == 0 || strcmp(arg2,"cx") == 0 || strcmp(arg2,"dx") == 0)
				{
					n = getRegisterValue(arg2);
					saveInRegister(arg3, n);
				}
				else
				{
					num1 = atoi(arg2);
					saveInRegister(arg3, num1);
				}
				break; 
			}
			if(strcmp(instruction,"jmp") == 0)
			{
				sscanf(line[i],"%s %s", instruction, arg2);
				i = atoi(arg2) - 2;
				break;
			}
			if(strcmp(instruction,"je") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4); 
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) == getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) == num1)
						{
							i = atoi(arg2) - 2;
						}
					}
					
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 == getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 == num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
				break;
			} 
			if(strcmp(instruction,"jne") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4);
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) != getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) != num1)
						{
							i = atoi(arg2) - 2;
						}
					}
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 != getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 != num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
				break;
			}
			if(strcmp(instruction,"jg") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4); //arg 2=jump line, arg3=register or number, arg4=register or number
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) > getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) > num1)
						{
							i = atoi(arg2) - 2;
						}
					}
					
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 > getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 > num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
				break;
			}
			if(strcmp(instruction,"jge") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4); //arg 2=jump line, arg3=register or number, arg4=register or number
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) >= getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) >= num1)
						{
							i = atoi(arg2) - 2;
						}
					}
					
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 >= getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 >= num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
				break;
			}
			if(strcmp(instruction,"jl") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4); //arg 2=jump line, arg3=register or number, arg4=register or number
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) < getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) < num1)
						{
							i = atoi(arg2) - 2;
						}
					}
					
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 < getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 < num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
				break;
			}
			if(strcmp(instruction,"jle") == 0)
			{
				sscanf(line[i],"%s %s %s %s", instruction, arg2, arg3, arg4); //arg 2=jump line, arg3=register or number, arg4=register or number
				if(strcmp(arg3,"ax") == 0 || strcmp(arg3,"bx") == 0 || strcmp(arg3,"cx") == 0 || strcmp(arg3,"dx") == 0)
				{
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(getRegisterValue(arg3) <= getRegisterValue(arg4))
						{	
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num1 = atoi(arg4);
						if(getRegisterValue(arg3) <= num1)
						{
							i = atoi(arg2) - 2;
						}
					}
					
				}
				else
				{
					num1 = atoi(arg3);
					if(strcmp(arg4,"ax") == 0 || strcmp(arg4,"bx") == 0 || strcmp(arg4,"cx") == 0 || strcmp(arg4,"dx") == 0)
					{
						if(num1 <= getRegisterValue(arg4))
						{
							i = atoi(arg2) - 2;
						}
					}
					else
					{
						num2 = atoi(arg4);
						if(num1 <= num2)
						{
							i = atoi(arg2) - 2;
						}
					}
				} 
			}
			break;
		}
	}
	
	fclose(ptr);
	return 0;
}