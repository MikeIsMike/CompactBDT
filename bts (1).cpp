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
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& v, int h, std::vector<bdt>& p);
void findNodes(bdt root, int level, std::vector<bdt>& v, std::vector<bdt>& p, bdt prevroot);
void compareTrees(bdt a, bdt b, int& c);
void findSubs(std::vector<bdt>& v, std::vector<bdt>& p);
void deleteSubs(bdt swap, bdt base, std::vector<bdt>& p, int k);
void deleteRight(bdt bye);
void findAns(bdt tree, int& y, std::string input, std::string& a);




/// you can define and use additional functions
/// for the implementation of buildcompactbdt and evalcompactbdt

/// add here the declarations (not the implementation)
/// for any other functions you wish to define and use

/// before the submission you need to remove the main
/// (either delete it or comment it out)
/// otherwise it will intefere with the automated testing

int main(){

	/// write the code for the main here in order to test your functions

	double totalduration = 0;

	bdt tmp = NULL;

	std::vector<std::string> input;

	std::string in = "00000000000000000000";
	input.push_back(in);
	//in = "011";
	//input.push_back(in);
	//in = "110";
	//input.push_back(in);
	//in = "111";
	//input.push_back(in);

	for (int i = 0; i < 10; i++) {
		std::clock_t start;
		start = std::clock();





		//	tmp = buildbdt(input);

		tmp = buildcompactbdt(input);

		// std::vector<std::string> leafnodes;
		// storeleafnodes(tmp, leafnodes);
		// for (int i = 0; i < leafnodes.size(); i++) {
		// 	std::cout << leafnodes[i] << " ";
		// }
		// std::cout << std::endl;
		double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << duration << std::endl;
		totalduration += duration;
		deleteRight(tmp);
	}

	//
	//
	//

	std::cout << "printf: " << totalduration << '\n';


	// std::vector<std::vector<int> > routes;
	// checkdependency(leafnodes, routes);
	// prunetree(tmp, routes);

	//printNames(tmp);
	//std::cout << std::endl;
	//std::vector<std::string> leafnodes2;
	////storeleafnodes(tmp, leafnodes2);
	//for (int i = 0; i < leafnodes2.size(); i++) {
	//	std::cout << leafnodes2[i] << " ";
	//}
	//std::cout << std::endl;



	/*

	std::cout << "what strings do you want to check? Enter '0' to exit" << std::endl;
	std::string inp;
	while (inp != "0") {
	std::cin >> inp;
	std::cout << evalbdt(tmp, inp) << std::endl;
	}*/
	return 0;
}

bdt buildcompactbdt(const std::vector<std::string>& fvalues){
    /// write the implementation for the function here
    std::vector<bdt> v;
    std::vector<bdt> p;
    std::string ex = fvalues[0];
    int i = ex.size();


	
    bdt pre = buildbdt(fvalues);



    bdt cmp = pre;

	std::clock_t start;
	double duration;
	start = std::clock();
    nextLevel(pre, cmp, v, i, p);
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "printf: " << duration << '\n';

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
    if (root != NULL){
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
  bdt tmp;
  deleteRight(swap->right);
  if(swap->val=="x1"){
	swap->val = swap->left->val;
	swap->right = swap->left->right;
	swap->left = swap->left->left;

  }
  else{
   tmp = swap -> left;
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
