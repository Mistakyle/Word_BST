


class treeCell
{
	
  //private members of every treeCell
  private:
  
	string data;
	int frequency;
	treeCell* left;
	treeCell* right;
  
  public:
  
  //default constructor
  treeCell()
  {
	  data = " ";
	  left = NULL;
	  right = NULL;
	  frequency = 0;
  }
  
 
  friend class tree;
  
	
	
};
