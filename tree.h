



class tree
{
	//declalartion of the private methods used for all of the recursion/traversion and the 
	//delcaration of the root
	private:
	treeCell* root;
	void inorder_traversal(treeCell * t);
	void postorder_traversal(treeCell* t);
	void breadthfirst_traversal(treeCell* t);
	void bottomup_traversal(treeCell* t);
	
	public:
	
	
	//default constructor
	tree()
	{
		root=NULL;
	}
	
	/*
	~tree() 
	{
		//do nothing
	}
	*/
	
	//declaration of all of our public methods
	void insert(string newWord, treeCell * & t);
	void read(string fileName);
	treeCell* search(string s);
	void insert(string s);
	void deleteCell(string s);
	void inorder();
	void preorder();
	void postorder();
	void breadthfirst();
	void bottomup();
	void processCommands();
	void visit(treeCell* t);
	
};
