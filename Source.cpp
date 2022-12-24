#include<iostream>
#include<windows.h>//to print colour text
#include<string>//to use string
using namespace std;
//Group Members:
//Muhammad Zaeem Butt 201326
//Qudsia Zainab  201286
//Ramisa Sohail Qureshi 201280

template <typename Type>
class Single_node // This class will have the key and the address of next element
{
	Type element; //Key
	Single_node<Type>* next_node; //Address of next node
public:
	Single_node(char = ' ', Single_node<Type>* = nullptr);//Constructor
	template<typename Type>
	friend class Single_list;

	template<typename Type>
	friend class STACK1;
	//This class can use all the public and private member functions and variable of Single_node class
};

template <typename Type>
Single_node<Type>::Single_node(char c, Single_node<Type>* p) : element(c), next_node(p)
{}//This will initialize element and next node address to zero

template <typename Type>
class Single_list
{
	//here we use Single_node because Single_list is a friend of Single_node
	Single_node<Type>* list_head;//This will store the head address
	Single_node<Type>* list_tail;//This will store the tail address

public:

	Single_list();//default constructor

	bool empty() const //To check if list is empty
	{
		return (list_head == nullptr);
	}

	char front() const
	{
		if (list_head == nullptr)
		{
			return 0;
		}

		return list_head->element; //This will return the value of head node
	}

	char pop_front()
	{
		int elmnt = front();
		Single_node<Type>* ptr = list_head;//Temp storing address of head
		list_head = list_head->next_node;

		delete ptr;//Deleting that temp pointer
		return elmnt;//After poping we will have new top
	}

	void push_front(char const& pushh)
	{
		list_head = new Single_node<Type>(pushh, list_head);//This will push a new node and that node will be the haed
	}

	void color(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	template<typename Type>
	friend class STACK1;//This class can use all the public and private member functions and variable of Single_list class
};

template <typename Type>
Single_list<Type>::Single_list() :list_head(nullptr), list_tail(nullptr)
{}// empty constructor

template<typename Type>
class STACK1 //This class will check the expression validity and will convert into postfix expression
{
	Single_list<Type> object_1;//Object 
	Type countt;
	//Type* postfixexp;
	string result;
public:

	STACK1()
	{
		countt = 0;
		//postfixexp = new char[countt];
	}

	bool empty() const //To check empty stack
	{
		return object_1.empty();
	}

	void color(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	void push(Type const& pussh) //To push reference to the node in stack
	{
		object_1.push_front(pussh);
	}

	Type top() const
	{
		if (empty())
		{
			//cout << "Empty: ";
		}
		return object_1.front();
	}

	Type pop()
	{
		if (empty())
		{
			color(4);
			cout << "underflow error! ";
		}
		return object_1.pop_front();
	}

	int priority(Type element) //to check the priority of operator
	{
		if (element == '^')//they have greater priority
		{
			return 3;
		}

		else if (element == '/' || element == '*')
		{
			return 2;
		}

		else if (element == '+' || element == '-')//they have less priority
		{
			return 1;
		}
		else
			return -1;
	}

	string convert(string infix) //to convert from infix to postfix
	{
		int col = 5;


		for (int i = 0; i < infix.length(); i++)//here length() function will give you the length of string expression
		{
			color(col);
			if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || isdigit(infix[i]))
			{
				countt++;
				result += infix[i];
			}
			else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[') //If it is opening parenthesis, push it on stack.
			{
				push(infix[i]);
			}
			else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
			{
				if (empty())//If stack is empty, push operator on stack.
				{
					push(infix[i]);
				}
				else if (top() == '{' || top() == '(' || top() == '[')//If the top of stack is opening parenthesis, push operator on stack
				{
					push(infix[i]);
				}
				else if (priority(infix[i]) > priority(top()))  //If it has higher priority than the top of stack, push operator on stack.
				{
					push(infix[i]);
				}
				else//Else pop the operator from the stack and output it
				{
					countt++;
					result += pop();
					i--;//repeat step 4
				}
			}
			//If it is a closing parenthesis, pop operators from stack and output them 
			// until an opening parenthesis is encountered.popand discard the opening parenthesis.
			else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
			{
				if (infix[i] == ')')
				{
					while (top() != '(')
					{
						countt++;
						result += pop();
					}
					pop(); //This will pop '('
				}
				else if (infix[i] == '}')
				{
					while (top() != '{')
					{
						countt++;
						result += pop();
					}
					pop();//This will pop '{'
				}
				else if (infix[i] == ']')
				{
					while (top() != '[')
					{
						countt++;
						result += pop();
					}
					pop();//This will pop '['
				}
			}
			col++;
		}

		while (!empty()) //If there is no more input, pop the remaining operators to output
		{
			countt++;
			result += pop();
		}
		return result;
	}

	bool check_validity(string infix) //This will check wheather the expression is valid or not before conversion
	{
		int total_operators = 0; // will use to count total operators
		int total_operands = 0; // will use to count total operands

		for (int i = 0; i < infix.length(); i++)
		{
			if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
			{
				total_operators++;
			}

			else if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || isdigit(infix[i]))//Here isdigit will check wheather the digit operand is digit or not
			{
				total_operands++;
			}
		}

		if (total_operators < total_operands)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool check_balancing(Type infix) //This will check wheather the expression is balanced or not 
	{
		if (infix == '(' || infix == '{' || infix == '[')
		{
			push(infix);
		}

		else if (infix == ')' || infix == '}' || infix == ']')
		{
			if (empty())
			{
				return false;
			}

			else
			{
				if (top() == '(' && infix == ')' || top() == '{' && infix == '}' || top() == '[' && infix == ']')
				{
					pop();
					if (!empty())//If after poping, if stack is not empty than it means it is un-balanced
					{
						return false;
					}
					return true;
				}
			}
		}
		else if (empty())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

template<typename Type>
class TreeNode {
public:
	char value;
	TreeNode<Type>* qValue;
	TreeNode<Type>* left;
	TreeNode<Type>* right;
	TreeNode<Type>* next;
	TreeNode<Type>* qnext;
public:
	TreeNode(Type c)
	{
		this->value = c;
		left = NULL;
		right = NULL;
		next = NULL;
	}
	TreeNode()
	{
		qValue = nullptr;
		left = NULL;
		right = NULL;
		qnext = NULL;
	}
	Type retrieve()
	{
		return value;
	}
	TreeNode<Type>* qretrieve()
	{
		return qValue;
	}
	template<typename Type>
	friend class Stack2;
	template<typename Type>
	friend class queue;
	template<typename Type>
	friend class expression_tree;
};

template<typename Type>
class Stack2
{
	TreeNode<Type>* head;

public:
	Stack2()
	{
		head = nullptr;
	}
	void push(TreeNode<Type>* x)
	{
		if (head == NULL)
		{
			head = x;
		}
		// We are inserting here nodes at the top of the stack [following LIFO principle]
		else
		{
			x->next = head;
			head = x;
		}
	}
	TreeNode<Type>* pop()
	{
		// Poping out the top most[ pointed with head] element
		TreeNode<Type>* p = head;
		head = head->next;
		return p;
	}
	template<typename Type>
	friend class expression_tree;
};

template<typename Type>
class queue
{
	TreeNode<Type>* front;
	TreeNode<Type>* rear;
public:
	queue()
	{
		front = nullptr;
		rear = nullptr;
	}
	void enqueue(TreeNode<Type>* value)  //pushback()
	{
		TreeNode<Type>* ptr = new TreeNode<Type>;
		ptr->qValue = value;
		ptr->qnext = nullptr;

		if (front == nullptr && rear == nullptr)
		{
			front = rear = ptr;
		}
		else
		{
			rear->qnext = ptr;  // current tail next is ptr
			rear = ptr;       // ptr is now tail;
		}
	}

	Type dequeue() //popfront()
	{
		if (empty())
		{
			cout << "Queue is empty!" << endl;
		}
		else
		{
			TreeNode<Type>* ptr = front;  //make temp ptr head
			Type deletedKey = front->retrieve();  // store data in current head
			front = ptr->qnext;  //new front is next of current head
			delete ptr;   // current head stored in ptr is deleted
			return deletedKey;  // deleted value is returned
		}
	}

	bool empty()
	{
		return(front == nullptr);
	}

	Type frontKey()
	{
		if (empty())
		{
			return NULL;
		}
		else
		{
			return front->retrieve();
		}
	}
	TreeNode<Type>* getFront()
	{
		return front;
	}
	TreeNode<Type>* getRear()
	{
		TreeNode<Type>* ptr = getFront();
		while (ptr != nullptr)
		{
			ptr = ptr->qnext;
		}
		rear = ptr;
		return rear;
	}
	template<typename Type>
	friend class expression_tree;
};

template<typename Type>
class expression_tree
{
	TreeNode<Type>* root;
	string exp;
	Type rootVal;
public:

	void BFSTdisplay(TreeNode<Type>* root)      //breadth first search traversal
	{
		if (root == nullptr)
		{
			return;
		}
		queue<Type> q;
		q.enqueue(root);

		while (!q.empty())
		{
			TreeNode<Type>* current = q.getFront();
			cout << current->qretrieve()->retrieve() << " ";
			if (current->qretrieve()->left != nullptr)
			{
				q.enqueue(current->qretrieve()->left);
			}
			if (current->qretrieve()->right != nullptr)
			{
				q.enqueue(current->qretrieve()->right);
			}
			q.dequeue();
		}
	}
	bool checkalphabet(TreeNode<Type>* root)
	{
		queue<Type> q;
		q.enqueue(root);
		bool check = false;
		while (!q.empty())
		{
			TreeNode<Type>* current = q.getFront();
			if (current->qretrieve()->retrieve() >= 'a' && current->qretrieve()->retrieve() <= 'z' || current->qretrieve()->retrieve() >= 'A' && current->qretrieve()->retrieve() <= 'Z')
			{
				check = true;
			}
			if (current->qretrieve()->left != nullptr)
			{
				q.enqueue(current->qretrieve()->left);
			}
			if (current->qretrieve()->right != nullptr)
			{
				q.enqueue(current->qretrieve()->right);
			}
			q.dequeue();
		}
		return check;
	}
	// Utility function to check if a given node is a leaf node
	bool isLeaf(TreeNode<Type>* node)
	{
		return node->left == nullptr && node->right == nullptr;
	}



	// Function to apply an operator 'op' to values 'x' and 'y' and return the result
	int processNums(char op, int x, int y)
	{
		if (op == '+') { return (x)+(y); }
		else if (op == '-') { return (x)-(y); }
		else if (op == '*') { return (x) * (y); }
		else if (op == '/') { return (x) / (y); }
		else if (op == '^') { return pow(x, y); }
		return 0;
	}
	// Recursive function to evaluate a binary expression tree
	int evaluateNums(TreeNode<Type>* root)
	{
		// base case: invalid input
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			// the leaves of a binary expression tree are operands
			if (isLeaf(root))
			{
				return (root->value - 48);
			}
			else
			{
				// recursively evaluate the left and right subtree
				int a = evaluateNums(root->left);
				int b = evaluateNums(root->right);

				// apply the operator at the root to the values obtained in the previous step
				return processNums(root->value, a, b);
			}
		}
	}

	void evaluateAlphabts(TreeNode<Type>* root)
	{
		if (root != NULL) {
			evaluateAlphabts(root->left);
			cout << root->value;
			evaluateAlphabts(root->right);
		}
	}
};

int main()
{
	//First we will take an infix expression
	STACK1<char> IN_PO; //Stack class object to convert infix into postfix

	string infix, postfix; //variables to store infix to postfix

	expression_tree<char> ETree; //Expression tree object to create, display and evaluate expression tree.

	bool balanceExp = false; //variable to tell that expression is balanced or not. True for balanced and false for unbalanced.
	IN_PO.color(2);

	//Instructions for users
	cout << "Here are some rules for INFIX to POSTFIX coversion\n\n";
	IN_PO.color(9);
	cout << "1-> Only Numbers, Arethimatic Operators and Alphabets are allowed\n";
	cout << "2-> Other values will be ignored\n";
	cout << "3-> Try writting a balanced equation\n\n\n";

	IN_PO.color(8);
	cout << "Enter an Expression for coversion: ";
	getline(cin, infix);  //stores spaces in string

	//This will check whether the infix expression is balanced or not.
	for (int i = 0; i < infix.length(); i++)
	{
		balanceExp = IN_PO.check_balancing(infix[i]);
	}

	//This will check whether the expression entered is valid or not. If expression is valid, it will be converted into postfix.
	if (balanceExp == true && IN_PO.check_validity(infix))
	{
		IN_PO.color(11);
		postfix = IN_PO.convert(infix);
		cout << "POSTFIX EXPRESSION IS: " << postfix;
	}
	else //If expression is not valid, it will not be converted into postfix.
	{
		IN_PO.color(4);
		cout << "Expression entered " << infix << " is not valid\n\n";
		return 0;
	}

	cout << "\n\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	//Display tree with BFS

	string s = postfix;
	Stack2<char> e;
	TreeNode<char>* Right, * Left, * Tree;
	Right = Left = Tree = NULL;

	int l = s.length();
	for (int i = 0; i < l; i++) {
		// if read character is operator then poping two
		// other elements from stack and making a binary
		// tree
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
		{
			Tree = new TreeNode<char>(s[i]);
			Tree->right = e.pop();
			Tree->left = e.pop();
			e.push(Tree);
		}
		else
		{
			Tree = new TreeNode<char>(s[i]);
			e.push(Tree);
		}
	}
	cout << "The Breadth First Search Traversal of Expression Tree: ";
	ETree.BFSTdisplay(Tree);
	cout << "\n\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);


	cout << "Evaluation of tree = ";//Evaluate function to evaluate tree and pass the root in evaluate function
	if (ETree.checkalphabet(Tree))
	{
		ETree.evaluateAlphabts(Tree);
	}
	else
	{
		cout << ETree.evaluateNums(Tree);
	}
	cout << "\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	return 0;
}