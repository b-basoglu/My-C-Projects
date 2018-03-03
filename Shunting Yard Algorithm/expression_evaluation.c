#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void shunting_yard();
char stack1[200];						//These are usedfor shunting yard					
int tos=0;								
void push1();							
char pop1();							
char infix[200],post[200];				
int precedence_check(char);				
void postfix();							


void evaluation();
double stack2[200]; 					//These are used for postfix evaluation
int top = -1; 							
void push2();							
double pop2();							


char take[200];							//input array
double result;							//output



int main(){

	scanf("%[^\n]",take);							// 	Takes expression as string
	shunting_yard();								//	This turns expression into postfix form (The Shunting Yard Algorithm )
	evaluation();									//	This evaluate postfix expression
	printf("\nThe result is %lf\n\n",result);
	return 0;
}




void shunting_yard(){
	int i=0 , j=0, length;
	length = strlen(take);

	for(i=0 ; i<length ; i++){        						//	In this example you can also use cos() sin() ln() and sqrt()
		if(take[i] == 'c'){									//	To calculate the expression easier I replace any of these functions with one character
			infix[j] = 'o';									//	cos() = c ; sin() = i ; sqrt() = q ; ln() = l	
			i = i + 2;										//	This will also helpful for us when we want to turn our expression into postfix
		}
		else if(take[i] == 's' && take[i+1] == 'i'){
			infix[j] = 'i';
			i=i+2;
		}
		else if(take[i] == 's' && take[i+1] == 'q'){
			infix[j] = 'q';
			i = i + 3;
		}
		else if(take[i] == 'l'){
			infix[j] = 'n';
			i = i + 1;
		}
		else{
			infix[j] = take[i];
		}
		j = j + 1;
	}

	postfix();							//This function convert expression to postfix

}

void postfix()
{
		int i=0,j=0,k=0,length;
		char temp;

		length = strlen(infix);

		for(i=0 ; i<length ; i++)
		{
			if(infix[i] == ' '){
				continue;
			}
			//operator check
			if(infix[i]!='+' && infix[i]!='-' && infix[i]!='*' && infix[i]!='/' && infix[i]!='^' && infix[i]!=')' && infix[i]!='('  && infix[i]!='n'  && infix[i]!='o'   && infix[i]!='q' && infix[i]!='i'&& infix[i]!='~')
			{
				post[j++] = infix[i];
			}
			else
			{
				post[j] = ' ';
				j = j + 1;
				if(tos == 0) 				//If there are no elements in the stack1, the operator is added to it
				{
					push1(infix[i]);
				}
				else 
				{       					//Operators or pushed or poped based on the order of precedence
					if( infix[i] != ')' && infix[i] != '(' )
					{
						if(    precedence_check(infix[i]) <= precedence_check(stack1[tos-1])  )
						{
							temp = pop1();
							post[j++] = temp;
							push1(infix[i]);
						}
						else
						{
							push1(infix[i]);
						}
					}
					else
					{
						if(infix[i]=='(')
						{
							push1(infix[i]);
						}
						if(infix[i]==')')
						{
							temp = pop1();
							while(temp != '(')
							{
								post[j++] = temp;
								temp = pop1();
							}
						}
					}

				}
					
			}	

		}
		while(tos!=0)
		{
			post[j++] = pop1();
		}

}
void push1(int vr)
{
	stack1[tos] = vr;
	tos++;
}
char pop1()
{
	tos--;
	return(stack1[tos]);
}
int precedence_check(char symbol)
{
	switch ( symbol ) {
        case '(':            /* with respect to their operator precedence */
            return 0;
        case ')':          
            return 0;
        case '+':         
            return 1;
        case '-':        
            return 1;
        case '*':        
            return 2;
        case '/':        
            return 2;
        case '^':        
            return 3;
        case 'i':        
            return 4;
        case 'o':        
            return 4;
        case 'q':        
            return 4;
        case 'n':        
            return 4;
        case '~':        //this is also a function, if you want to give a negative number.For instance, negative four is ~(4)
            return 4;
        default:            
            return 0;
    }
}




void evaluation()
{
        char *e;
        double n1,n2,n3, num, after_decimalpoint=1;
        double keep=0; 
        e = post; 											//e is our postfix experession 

        while(*e != '\0')
        {

                if(isdigit(*e) || *e =='.') 				//this if statement push integer and doubles to stack
                {
                        keep=0;
                        while(isdigit(*e)){
                                num = *e - 48;
                                keep = keep * 10 + num;
                                e++;
                        }
                        if (*e =='.'){ 						//when the number is double
                                e++;
                                while(isdigit(*e)){
                                        after_decimalpoint = after_decimalpoint / 10;
                                        num = *e - 48;
                                        keep = keep + num * after_decimalpoint;
                                        e++;
                                }
                        }
                        push2(keep);
                        continue;
                }
                else if( *e =='+' || *e =='/' || *e =='*' || *e =='-' || *e =='~' || *e =='q' || *e =='i' || *e =='o' || *e =='n')
                {
                        switch(*e)
                        {
                                case '+':
                                {
                                        n1 = pop2();
                                        n2 = pop2();
                                        n3 = n1 + n2;
										break;
                                }
                                case '-':
                                {
                                        n1 = pop2();
                                        n2 = pop2();
                                        n3 = n2 - n1;
                                        break;
                                }
                                case '*':
                                {
                                        n1 = pop2();
                                        n2 = pop2();
                                        n3 = n1 * n2;
                                        break;
                                }
                                case '/':
                                {
                                        n1 = pop2();
                                        n2 = pop2();
                                        n3 = n2 / n1;
                                        break;
                                }
                                case '~':
                                {
                                        n1 = pop2();
                                        n3 = - n1;
                                        break;
                                }
                                case 'o':
                                {
                                        n1 = pop2();
                                        n3 = cos(n1);
                                        break;
                                }
                                case 'n':
                                {
                                        n1 = pop2();
                                        n3 = log(n1);
                                        break;
                                }
                                case 'i':
                                {
                                        n1 = pop2();
                                        n3 = sin(n1);
                                        break;
                                }
                                case 'q':
                                {
                                        n1 = pop2();
                                        n3 = sqrt(n1);
                                        break;
                                }
                        }
                        push2(n3);
                }
                e++;
        }
        result=pop2();
        

}

void push2(double x)
{
        stack2[++top] = x;
}

double pop2()
{

        return stack2[top--];
}

