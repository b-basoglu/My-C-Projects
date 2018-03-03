# Dijsktra's Shunting Yard Algorithm

"Shunting Yard" algorithm converts an infix expression into a postfix expression. It uses a stack; but in this case, the stack is used to hold operators rather than numbers. The purpose of the stack is to reverse the order of the operators in the expression. It also serves as a storage structure, since no operator can be printed until both of its operands have appeared.

In this C program Shunting Yard Algorithm is implemented but it doesn't use stack data type, however it directly converts the input expression (gets as a string) to its postfix form as string and then it evaluates the expression and returns the result. 

I/O Example:

Please enter the mathematical expression (up to 200 characters)

	3+8
	Result: 11

Please enter the mathematical expression (up to 200 characters)

	3/7-2672+5222-3
	Result: 2547.43

Please enter the mathematical expression (up to 200 characters)

	sin(15)+78-cos(20)
	Result: 78.24

Please enter the mathematical expression (up to 200 characters)

	(~456)+ln(1)-15/5
	Result: -459.00
