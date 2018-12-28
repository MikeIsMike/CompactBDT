//using C++11 functions
#include <iostream>
#include <vector>
#include <ctime>




/// do not alter the struct declaration
struct bdnode{
    std::string val;
    bdnode* left;
    bdnode* right;

};

/// do not alter the typedef
typedef bdnode* bdt;


/// do not alter these two function declarations
bdt buildcompactbdt(const std::vector<std::string>& fvalues);
std::string evalcompactbdt(bdt t, const std::string& input);
bdt buildbdt(const std::vector<std::string>& fvalues);
std::string nodeName(bdt tree);
bdt rightChild(bdt tree);
bdt leftChild(bdt tree);
void printNames(bdt tree);
void makeNode(int node, bdt& tree);
void formTree(bdt& tree, int node, int i);
void insert1(bdt& tree, std::string x, int& y);
void findAns(bdt tree, int& y, std::string input, std::string& a);
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& v, int h, std::vector<bdt>& p);
void findNodes(bdt root, int level, std::vector<bdt>& v, std::vector<bdt>& p, bdt prevroot);
void compareTrees(bdt a, bdt b, int& c);
void findSubs(std::vector<bdt>& v, std::vector<bdt>& p);
void deleteSubs(bdt swap, bdt base, std::vector<bdt>& p, int k);
void deleteRight(bdt bye);




/// you can define and use additional functions
/// for the implementation of buildcompactbdt and evalcompactbdt

/// add here the declarations (not the implementation)
/// for any other functions you wish to define and use

/// before the submission you need to remove the main
/// (either delete it or comment it out)
/// otherwise it will intefere with the automated testing

int main(){
  /// write the code for the main here in order to test your functions

	std::clock_t start;
	double duration;

	start = std::clock();
	std::vector<std::string> input;
	std::string in = "00000000000000000000";
	input.push_back(in);
	//in = "101";
	//  input.push_back(in);
	bdt andbdt = buildcompactbdt(input);
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "printf: " << duration << '\n';
	printNames(andbdt);
	//std::cout<<evalcompactbdt(andbdt,"11")<<std::endl;
	//std::cout<<evalbdt(andbdt,"00")<<std::endl;
	//std::cout<<evalbdt(andbdt,"01")<<std::endl;
	//std::cout<<evalbdt(andbdt,"10")<<std::endl;
	/// write the code for the main here in order to test your functions

	return 0;

}
 
//bdt buildcompactbdt(const std::vector<std::string>& fvalues){
//    /// write the implementation for the function here
//
//}
// 
//std::string evalcompactbdt(bdt t, const std::string& input){
//    /// write the implementation for the function here
//}


bdt buildcompactbdt(const std::vector<std::string>& fvalues){
    /// write the implementation for the function here
    std::vector<bdt> v;
    std::vector<bdt> p;
    std::string ex = fvalues[0];
    int i = ex.size();

	std::clock_t start1;
	double duration;
	start1 = std::clock();
    bdt pre = buildbdt(fvalues);
	duration = (std::clock() - start1) / (double)CLOCKS_PER_SEC;
	std::cout << "printf: " << duration << '\n';

    bdt cmp = pre;
    nextLevel(pre, cmp, v, i, p);
    findSubs(v, p);
    return pre;
}

std::string evalcompactbdt(bdt t, const std::string& input){
    /// write the implementation for the function here
    int y = 0;
    std::string a;
    findAns(t,y,input,a);
    return a;
}

void printNames(bdt tree){
  if(tree != NULL){
    printNames(leftChild(tree));
    std::cout << nodeName(tree) << std::endl;
    printNames(rightChild(tree));
  }
}


std::string nodeName(bdt tree){
  return tree -> val;
}
bdt rightChild(bdt tree){
  return tree -> right;
}
bdt leftChild(bdt tree){
  return tree -> left;
}


/// add here the implementation for any other functions you wish to define and use

void makeNode(int node, bdt& tree){
  bdt tmp = new bdnode;
  tmp->val = "x" + std::to_string(node); //using a C++11 feature
  tmp->left = NULL;
  tmp->right = NULL;
  tree = tmp;
}


void formTree(bdt& tree, int node, int i){
  node++;
  if(node <= i + 1){
    makeNode(node, tree);
    formTree(tree->left, node, i);
    if(node == i + 1){
      tree->val = "0";
    }
    formTree(tree->right, node, i);
  }
}

void insert1(bdt& tree, std::string x, int& y){
  if(y != x.size()){
    y++;
    if(x[y-1] == '1'){
      insert1(tree->right, x, y);
    }
    else{
      insert1(tree->left, x, y);
    }
  }
  else{
    tree->val = "1";
    y = 0;
  }
}

void findAns(bdt tree, int& y, std::string input, std::string& a){
  if(y != input.size()){
      y++;
    if(input[y-1] == '1'){
      findAns(tree->right, y, input, a);
    }
    else{
      findAns(tree->left, y, input, a);
    }
  }
  else{
    a = tree->val;
    y = 0;
  }
}

bdt buildbdt(const std::vector<std::string>& fvalues){
  bdt tree = NULL;
  std::string ex = fvalues[0];
  int i = ex.size();
  int node = 0;
  formTree(tree, node, i);
  for(int j = 0; j < fvalues.size(); j++){
    int y = 0;
    std::string x = fvalues[j];
    insert1(tree, x, y);
  }
  return tree;
}

/* Function to line by line print level order traversal a tree*/
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& v, int h, std::vector<bdt>& p){
    for (int i=1; i<=h; i++){
        findNodes(root, i, v, p, prevroot);
    }
}

/* Print nodes at a given level */
void findNodes(bdt root, int level, std::vector<bdt>& v, std::vector<bdt>& p, bdt prevroot){
    if (root == NULL){
        return;
      }
    if (level == 1){
      int c = 1;
      compareTrees(root -> left, root -> right, c);
      if(c == 1){
        v.push_back(root);
        p.push_back(prevroot);
      }
    }
    else if (level > 1){
        findNodes(root->left, level-1, v, p, root);
        findNodes(root->right, level-1, v, p, root);
    }
}



void compareTrees(bdt a, bdt b, int& c){
  if(a != NULL &&  b!= NULL){
    compareTrees(a -> left, b -> left, c);
      if((a->val)!=(b->val)){
        c = 0;
      }
    compareTrees(a -> right, b -> right, c);
      if((a->val) != (b->val)){
        c = 0;
      }
  }
}

void findSubs(std::vector<bdt>& v, std::vector<bdt>& p){
  int j = p.size() - 1;
  for(int i = v.size() - 1; i > -1; i--){
    bdt node = v[i];
    bdt prevnode = p[j];
    deleteSubs(node, prevnode, p, i);
    j--;
    }
  }

void deleteSubs(bdt swap, bdt base, std::vector<bdt>& p, int k){
  if(base->left == swap || base->right == swap){
    bdt tmp = swap -> left;
    if(swap == base -> left){
      delete swap;
      base -> left = tmp;
    }
    else{
      delete swap;
      base -> right = tmp;
    }
      }
    }

void deleteRight(bdt bye){
  if(bye!=NULL){
    deleteRight(bye->left);
    deleteRight(bye->right);
    delete bye;
  }
}
