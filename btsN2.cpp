//using C++11 functions
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>



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
void printNames(bdt tree, int& h);
void makeNode(int node, bdt& tree);
void formTree(bdt& tree, int node, int i);
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& v, int h, std::vector<bdt>& p);
void findNodes(bdt root, int level, std::vector<bdt>& v, std::vector<bdt>& p, bdt prevroot);
void compareTrees(bdt a, bdt b, int& c);
void findSubs(std::vector<bdt>& v, std::vector<bdt>& p);
void deleteSubs(bdt swap, bdt base, std::vector<bdt>& p, int k);
void deleteTree(bdt bye);
void findAns(bdt tree, std::string input, std::string& a);
void traverse(bdt& tree, int& b);
void insert1(bdt& tree, std::string x, int& y);

void printLevelOrder(bdt root);
void printGivenLevel(bdt root, int level);
/// you can define and use additional functions
/// for the implementation of buildcompactbdt and evalcompactbdt

/// add here the declarations (not the implementation)
/// for any other functions you wish to define and use

/// before the submission you need to remove the main
/// (either delete it or comment it out)
/// otherwise it will intefere with the automated testing

int main(){
  std::clock_t start;
    double duration = 0, total = 0;
    int h = 0;
//  for(int i = 0; i < 10; i++){
  //  h = 0;
    start = std::clock();
  std::vector<std::string> input;
  std::string in = "0000000000000000000";
	input.push_back(in);

  bdt andbdt = buildcompactbdt(input);
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
//  printLevelOrder(andbdt);
  printNames(andbdt, h);
//  std::cout << std::endl;
  //std::cout << duration << std::endl;
  //total = total + duration;
//}
  //total = total/10;
  std::cout<<"printf: "<< duration <<'\n';
  std::cout << "Nodes: " << h << std::endl;
  //std::cout<<evalcompactbdt(andbdt,"00000000000000000000")<<std::endl;
  //std::cout<<evalcompactbdt(andbdt,"01100000000000000000")<<std::endl;
  //std::cout<<evalcompactbdt(andbdt,"11100000000000000000")<<std::endl;
  //std::cout<<evalcompactbdt(andbdt,"101")<<std::endl;
    /// write the code for the main here in order to test your functions

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
    nextLevel(pre, cmp, v, i, p);
    findSubs(v, p);
    int b = 1;
    while(b == 1){
      b = 0;
      traverse(pre,b);
    }
    return pre;
}

std::string evalcompactbdt(bdt t, const std::string& input){
    /// write the implementation for the function here
    int y = 0;
    std::string a;
    findAns(t,input,a);
    return a;
}

void printNames(bdt tree, int& h){
  if(tree != NULL){
    printNames(leftChild(tree), h);
    h++;
    printNames(rightChild(tree), h);
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

void findAns(bdt tree, std::string input, std::string& a){
  if(tree->left != NULL){
    std::stringstream index(tree->val);
    int i;
    char g;
    index >> g;
    index >> i;
      if(input[i - 1] == '1'){
        findAns(tree->right, input, a);
      }
      else{
        findAns(tree->left, input, a);
      }
    }
    else{
      a = tree->val;
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
  deleteTree(swap->right);
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

void deleteTree(bdt bye){
  if(bye!=NULL){
    deleteTree(bye->left);
    deleteTree(bye->right);
    delete bye;
  }
}

void traverse(bdt& tree, int& b){
  if(tree != NULL){
    traverse(tree->left, b);
    traverse(tree->right, b);
    if(tree -> left != NULL && tree -> right != NULL && tree -> left -> val == tree -> right -> val && b != 1){
      int j = 0;
      int c = 1;
      compareTrees(tree -> left -> left, tree -> right -> left, c);
      if(c == 1){
        j++;
        bdt tmp = tree;
        bdt tmp1 = tree -> right -> right;
        bdt tmp2 = tree -> left -> right;
        bdt tmp3 = tree -> left;
        bdt tmp4 = tree -> right;
        tree = tmp3;
        tree -> right = tmp;
        tree -> right -> right = tmp1;
        tree -> right -> left = tmp2;
        deleteTree(tmp4 -> left);
        delete tmp4;
        b = 1;
      }
      c = 2;
      if(j == 0){
        compareTrees(tree -> left -> right, tree -> right -> right, c);
        if(c == 2){
          bdt tmp = tree;
          bdt tmp1 = tree -> right -> left;
          bdt tmp2 = tree -> left -> left;
          bdt tmp3 = tree -> left;
          bdt tmp4 = tree -> right;
          tree = tmp3;
          tree -> left = tmp;
          tree -> left -> left = tmp2;
          tree -> left -> right = tmp1;
          deleteTree(tmp4 -> right);
          delete tmp4;
          b = 1;
        }
      }
    }
  }
}







/* Function to line by line print level order traversal a tree*/
void printLevelOrder(bdt root)
{
    int h = 21;
    int i;
    for (i=1; i<=h; i++)
    {
        printGivenLevel(root, i);
        printf("\n");
        std::cout << " ";
    }
}

/* Print nodes at a given level */
void printGivenLevel(bdt root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        std::cout << " " << root->val;
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}




//////////////////////////////////////////////////////////////////////
std::string evalcompactbdt(bdt t, const std::string& input){
  int parameters = input.size();
  std::vector<std::string> letter_vector;
  letter_number(letter_vector, parameters);

  bdt node = t;
  std::string parameter;

  for(int i = 0; i < input.size(); i++){
    for(int j = 0; j < input.size(); j++){
      if(letter_vector[j] == node->val){
        parameter = input[j];
        if(parameter == "1"){
          node = node->right;
        }
        else{
          node = node->left;
        }
      }
      if(node_height(node) == 0){
        return node->val;
      }
    }
  }
  return {};
}

void letter_number(std::vector<std::string>& x, int n){
  std::string letter = "x";
  std::string letterstring;
  for(int i = 0; i < n; i++){
    letterstring = letter + std::to_string(i+1);
    x.push_back(letterstring);
  }
}
