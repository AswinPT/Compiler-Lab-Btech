#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int pointer = 0, lbf = 0, forward = 0;
int i, j;
char token[10];

int read_sym(char buffer[]) 
{
	FILE *fsym1 = fopen("sym_tab.txt", "r");
  	int flag = 1, id;
  	char type[10], name[10];
  	while (!feof(fsym1)) 
  	{
    		fscanf(fsym1, "%d%s", &id, name);
    		if (strcmp(name, buffer) == 0)
    		{
      			flag = 0;
      			break;
    		}
  	}
  	fclose(fsym1);
  	return flag;
}
int get_id(char buffer[])
{
	FILE *fin = fopen("sym_tab.txt", "r");
	int id;
	char type[10], name[10];
	while(!feof(fin))
	{
		fscanf(fin, "%d%s", &id, name);
		if (strcmp(name, buffer) == 0)
    		{
     			break;
    		}
    	}
    	return id;
}
void write_sym(char buffer[])
{
  	FILE *fsym2 = fopen("sym_tab.txt", "a");
  	fprintf(fsym2, "%d\t%s\n", pointer, token);
  	printf("<id,%d>", pointer);
  	pointer++;
  	fclose(fsym2);
}
bool is_operator(char buffer[])
{
  	if (buffer[forward] == '+' || buffer[forward] == '*' || buffer[forward] == '-' || buffer[forward] == '='|| buffer[forward]=='<')
    		return true;
  	else
    		return false;
}
bool is_delimiter(char buffer[])
{
  	if (buffer[forward] == ',' || buffer[forward] == '{' || buffer[forward] == '}' || buffer[forward] == ' ' || buffer[forward] == ';' || buffer[forward] == '(' || buffer[forward] == ')') 
    		return true;
  	else
    		return false;
}
bool chk_delimiter(char buffer[]) 
{
  	if (buffer[forward] == ',' || buffer[forward] == '{' || buffer[forward] == '}' || buffer[forward] == ' ' || buffer[forward] == ';' || buffer[forward] == '(' || buffer[forward] == ')') 
  	{
    		if(buffer[forward] != ' ')
      			printf("<delimiter,%c>", buffer[forward]);
    		if(buffer[forward] == ';' || buffer[forward] == '{' || buffer[forward] == '}')
      			printf("\n");
    		forward++;
    		lbf++;
    		return true;
  	} 
  	else
    		return false;
}
bool chk_operator(char buffer[]) 
{
  	int state = 0, k = 0;
  	memset(&token[0], 0, sizeof(token));
  	while (1) 
  	{
    		switch (state) 
    		{
      			case 0: 
      			{
        			if (buffer[forward] == '+' || buffer[forward] == '*' || buffer[forward] == '-' || buffer[forward] == '=') 
        			{
          				token[k++] = buffer[forward++];
          				state = 2;
        			}
        			else if((buffer[forward] == '<') || (buffer[forward] == '>') || (buffer[forward] == '!'))
        			{
          				token[k++] = buffer[forward++];
          				state = 1;
        			}
        			else
          				state = 3;
        			break;
      			}
      			case 1:
      			{
        			if(buffer[forward] == '=')
        			{
          				token[k++] = buffer[forward++];
          				state = 2;
        			}
        			break;
      			}
    		}
    		if(state == 2)
    		{
      			printf("<operator,%s>", token);
      			break;
    		}
    		else if(state == 3)
      			break;
  	}
  	lbf = forward;
  	if(state == 2)
    		return true;
  	else 
    		return false;
}
bool chk_number(char buffer[]) 
{
  	forward = lbf;
  	int state = 0, k = 0;
  	memset(&token[0], 0, sizeof(token));
  	while (1) 
  	{
    		switch (state) 
    		{
      			case 0: 
      			{
        			if ((buffer[forward] >= '0' && buffer[forward] <= '9'))
          				state = 1;
        			else
          				state = 4;
        			break;
      			}
      			case 1: 
      			{
        			if ((buffer[forward] >= '0' && buffer[forward] <= '9'))
          				state = 1;
        			else if (buffer[forward] == '.')
          				state = 2;
        			else if((is_operator(buffer) == 1)|| (is_delimiter(buffer) == 1))
          				state = 3;
        			else
          				state = 4;
        			break;
      			}
      			case 2:
      			{
        			if((buffer[forward] >= '0' && buffer[forward] <= '9'))
          				state = 2;
        			else if((is_operator(buffer) == 1)|| (is_delimiter(buffer) == 1))
          				state = 3;
       			else
          				state = 4;
        			break;
      			}
    		}
    		if (state == 3)
    		{
      			printf("<number,%s>", token);
      			break;
    		} 
    		else if (state == 4)
      			break;
    		token[k++] = buffer[forward++];
  	}
  	if (state == 3)
  	{
    		lbf = forward;
    		return true;
  	}
  	else
    		return false;
}
bool chk_keyword(char buffer[]) 
{
  	forward = lbf;
  	int state = 0, flag, k, k1 = 0;
  	FILE *fsym2;
  	memset(&token[0], 0, sizeof(token));
  	while (1) 
  	{
    		switch (state) 
    		{
      			case 0: 
      			{
        			if (buffer[forward] == 'i')
          				state = 1;
        			else if (buffer[forward] == 'f')
          				state = 4;
        			else if(buffer[forward] == 'm')
        	  			state = 8;
        			else if ((buffer[forward] >= 'a' && buffer[forward] <= 'z') || (buffer[forward] >= 'A' && buffer[forward] <= 'Z'))
          				state = 11;
        			else
          				state = 13;
        			break;
      			}
      			case 1: 
      			{
        			if (buffer[forward] == 'n')
          				state = 2;
        			else
          				state = 11;
        			break;
      			}
      			case 2: 
      			{
        			i = 1;
        			j = 0;
        			if (buffer[forward] == 't')
          				state = 3;
        			else
          				state = 11;
        			break;
      			}
      			case 3: 
      			{
        			if (is_delimiter(buffer) == 1)
          				state = 14;
        			else
          				state = 11;
        			break;
      			}
      			case 4: 
      			{
        			if (buffer[forward] == 'l')
          				state = 5;
        			else
          				state = 11;
        			break;
      			}
      			case 5: 
      			{
        			if (buffer[forward] == 'o')
          				state = 6;
        			else
          				state = 11;
        			break;
      			}
      			case 6: 
      			{
        			if (buffer[forward] == 'a')
          				state = 7;
        			else
          				state = 11;
        			break;
      			}
      			case 7: 
      			{
        			j = 1;
        			i = 0;
        			if (buffer[forward] == 't')
          				state = 3;
        			else
          				state = 11;
        			break;
      			}
      			case 8:
      			{
        			if(buffer[forward] == 'a')
          				state = 9;
        			else
          				state = 11;
        			break;
      			}
      			case 9:
      			{
        			if(buffer[forward] == 'i')
          				state = 10;
        			else
          				state = 11;
        			break;
      			}
      			case 10:
      			{
        			if(buffer[forward] == 'n')
          				state = 3;
        			else
          				state = 11;
        			break;
      			}   
      			case 11: 
      			{
        			if ((buffer[forward] >= 'a' && buffer[forward] <= 'z') || (buffer[forward] >= 'A' && buffer[forward] <= 'Z') ||((buffer[forward] >= '0' && buffer[forward] <= '9')))
          				state = 11;
        			else if ((is_operator(buffer) == 1) || (is_delimiter(buffer) == 1))
          				state = 12;
        			break;
      			}   
    		}
    		if (state == 13)
      			break;
    		if (state == 12) 
    		{
      			if (i == 1) 
      			{
        			flag = read_sym(token);
        			if (flag) 
          				write_sym("int");
        			else
        			{
          				int id = get_id(token);
          				printf("<id,%d>", id);
        			}
      			} 
      			else if (j == 1) 
      			{
        			flag = read_sym(token);
        			if (flag) 
          				write_sym("float");
        			else
        			{
          				int id = get_id(token);
          				printf("<id,%d>", id);
        			}
      			}
      			break;
    		}
    		if (state == 14) 
    		{
      			printf("<keyword,%s>",token);
      			break;
    		}
    		token[k1++] = buffer[forward++];
  	}
  	lbf = forward;
  	if (state == 12 || state == 14)
    		return true;
  	else
    		return false;
}
void lex(char buffer[])
{
	while (lbf < strlen(buffer)) 
    	{
      		if (chk_delimiter(buffer) == 1)
        		continue;
      		else if (chk_operator(buffer) == 1)
      		{
        		lbf = forward;
        		continue;
      		} 
      		else if (chk_keyword(buffer) == 1)
        		continue;
      		else if (chk_number(buffer) == 1)
        		continue;
    	}
}
int main() 
{
	  FILE *f1, *f2, *f3;
	  char ch;
	  f1 = fopen("input_prg.txt", "r");
	  printf("\n\t\tINPUT PROGRAM\n");
	  printf("----------------------------------------------------------\n");
	  while (!feof(f1)) 
	  {
		    ch = fgetc(f1);
		    printf("%c", ch);
	  }
	  fclose(f1);
	  printf("\n----------------------------------------------------------\n");
	  f1 = fopen("input_prg.txt", "r");
	  f2 = fopen("temp.txt", "w");
	  f3 = fopen("sym_tab.txt", "w");
	  char buffer[100], buffer2[100];
	  int k = 0, flag = 0;
	  fclose(f3);
	  while (!feof(f1)) 
	  {
		    fgets(buffer2, sizeof(buffer2), f1);
		    k = 0;
		    flag = 0;
		    memset(&buffer[0], 0, sizeof(buffer));
		    for (i = 0; i < strlen(buffer2) - 1; i++)
			      if (buffer2[i] != '/' || buffer2[i + 1] != '/') 
			      {
					buffer[k] = buffer2[k];
					k++;
			      } 
			      else 
			      {
					flag = 1;
					break;
			      }
			      if ((flag == 1 && k != 0) || (flag == 0)) 
			      {
					buffer[strcspn(buffer, "\n")] = 0;
					fprintf(f2, "%s", buffer);
			      }
	  }
	  fclose(f2);
	  f2 = fopen("temp.txt", "r");
	  while (!feof(f2)) 
	  {
		    fgets(buffer, sizeof(buffer), f2);
		    printf("\n\t\tTOKENS\n");
		    printf("----------------------------------------------------------\n");
		    lex(buffer);
	  }
	  printf("----------------------------------------------------------\n\n");
}
