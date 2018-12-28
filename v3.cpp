/// include here all the headers you need (but see guidelines)

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <ctime>
#include <cstdio>

/// do not use using namespace std
 
/// do not alter the struct declaration
struct bdnode{
    std::string val; 
    bdnode* left; 
    bdnode* right; 
 
};
 
/// do not alter the typedef
typedef bdnode* bdt;
 
/// you can define and use additional structs
/// (with member data and/or member functions)
/// to use within the implementation of buildcompactbdt and/or evalcompactbdt
 
/// add here the declarations for any structs you wish to define and use
/// (including the implementation of member functions, if any) 
 
/// do not alter these two function declarations
bdt buildcompactbdt(const std::vector<std::string>& fvalues); 
std::string evalcompactbdt(bdt t, const std::string& input);
 
/// you can define and use additional functions 
/// for the implementation of buildcompactbdt and/or evalcompactbdt
 
/// add here the declarations (not the implementation)
/// for any other functions you wish to define and use
/*bdt buildzerobdt(int height);
bdt constree(std::string el, bdt l, bdt r);
bdt instree(bdt t, int height, int num);
void runtree(bdt& t, std::string string, int j);*/




///////////////////
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots, int h);
void findNodes(bdt root, bdt prevroot, int level, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots);
void compareTrees(bdt a, bdt b, bool& same);
void findSubs(std::vector<bdt>& currentroots, std::vector<bdt>& prevroots);
void deleteSubs(bdt root, bdt prevroot);
void deleteRight(bdt t);

std::string nodeName(bdt tree);
bdt rightChild(bdt tree);
bdt leftChild(bdt tree);
void printNames(bdt tree);

void makeNode(int node, bdt& tree);
void formTree(bdt& tree, int node, int i);
void insert1(bdt& tree, std::string x, int& y);
//void findAns(bdt tree, int& y, std::string input, std::string& a);
/////////////////


void printroot(bdt t);
void printtree(bdt t);

bdt buildbdt(const std::vector<std::string>& fvalues);
std::string evalbdt(bdt t, const std::string& input);
 
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
		totalduration +=  duration;
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
	 std::vector<bdt> currentroots;
	 std::vector<bdt> prevroots;
	 std::string input = fvalues[0];
	 int height = input.size();

	 
	 bdt t = buildbdt(fvalues);



//printtree(t);
	 bdt t2 = t;
	 nextLevel(t, t2, currentroots, prevroots, height);


	 std::clock_t start1;
	 double duration;
	 start1 = std::clock();	
	 findSubs(currentroots, prevroots);
	 duration = (std::clock() - start1) / (double)CLOCKS_PER_SEC;
	 std::cout << "printduration: " << duration << '\n';

	 return t;
 }
 
// std::string evalcompactbdt(bdt t, const std::string& input){
//     /// write the implementation for the function here
// }
 





/// add here the implementation for any other functions you wish to define and use
 void makeNode(int node, bdt& tree) {
	 bdt tmp = new bdnode;
	 tmp->val = "x" + std::to_string(node); //using a C++11 feature
	 tmp->left = NULL;
	 tmp->right = NULL;
	 tree = tmp;
 }


 void formTree(bdt& tree, int node, int i) {
	 node++;
	 if (node <= i + 1) {
		 makeNode(node, tree);
		 formTree(tree->left, node, i);
		 if (node == i + 1) {
			 tree->val = "0";
		 }
		 formTree(tree->right, node, i);
	 }
 }

 void insert1(bdt& tree, std::string x, int& y) {
	 if (y != x.size()) {
		 y++;
		 if (x[y - 1] == '1') {
			 insert1(tree->right, x, y);
		 }
		 else {
			 insert1(tree->left, x, y);
		 }
	 }
	 else {
		 tree->val = "1";
		 y = 0;
	 }
 }

 void findAns(bdt tree, int& y, std::string input, std::string& a) {
	 if (y != input.size()) {
		 y++;
		 if (input[y - 1] == '1') {
			 findAns(tree->right, y, input, a);
		 }
		 else {
			 findAns(tree->left, y, input, a);
		 }
	 }
	 else {
		 a = tree->val;
		 y = 0;
	 }
 }

 bdt buildbdt(const std::vector<std::string>& fvalues) {
	 bdt tree = NULL;
	 std::string ex = fvalues[0];
	 int i = ex.size();
	 int node = 0;
	 formTree(tree, node, i);
	 for (int j = 0; j < fvalues.size(); j++) {
		 int y = 0;
		 std::string x = fvalues[j];
		 insert1(tree, x, y);
	 }
	 return tree;
 }






//////////////////////////////


void printroot(bdt t){
std::cout << t->val /*<<std::endl*/ << " ";
}

void printtree(bdt t){
	if(t!=NULL){
		printtree(t->left);
		printroot(t);
		printtree(t->right);
	}
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



//std::string evalcompactbdt(bdt t, const std::string& input){
//    /// write the implementation for the function here
//    int y = 0;
//    std::string a;
//    //findAns(t,y,input,a);
//    return a;
//}

void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots, int height) {
	for (int i = 1; i <= height; i++) {
		findNodes(root, prevroot, i, currentroots, prevroots);
	}
}

/* Print nodes at a given level */
void findNodes(bdt root, bdt prevroot, int level, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots) {
	if (root != NULL) {
		if (level == 1) {
			bool same = true;
			compareTrees(root->left, root->right, same);

			if (same) {
				currentroots.push_back(root);
				prevroots.push_back(prevroot);
			}
		}
		else if (level > 1) {
			findNodes(root->left, root, level - 1, currentroots, prevroots);
			findNodes(root->right, root, level - 1, currentroots, prevroots);
		}
	}
}



void compareTrees(bdt a, bdt b, bool& same) {
	if (a != NULL && b != NULL) {
		compareTrees(a->left, b->left, same);
		if ((a->val) != (b->val)) {
			same = false;
		}
		compareTrees(a->right, b->right, same);
		if ((a->val) != (b->val)) {
			same = false;
		}
	}
}

void findSubs(std::vector<bdt>& currentroots, std::vector<bdt>& prevroots) {//could potentially delete from top of bdt to save even more operations, but exception thrown when a deleted node is accessed needs to be handled
	int j = prevroots.size() - 1;
	for (int i = currentroots.size() - 1; i > -1; i--) {
		bdt root = currentroots[i];
		bdt prevroot = prevroots[j];
		deleteSubs(root, prevroot);
		j--;
	}
}

void deleteSubs(bdt root, bdt prevroot) {
	bdt tmp;
	deleteRight(root->right);
	if (root->val == "x1") {
		tmp = root->left;
		root->val = root->left->val;
		root->right = root->left->right;
		root->left = root->left->left;
		delete tmp;

	}
	else {
		tmp = root->left;
		if (root == prevroot->left) {
			delete root;
			prevroot->left = tmp;
		}
		else {
			delete root;
			prevroot->right = tmp;
		}
	}
}

void deleteRight(bdt t) {
	if (t != NULL) {
		deleteRight(t->left);
		deleteRight(t->right);
		delete t;
	}
}

/*void findAns(bdt tree, int& y, std::string input, std::string& a){
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
}*/


void printNames(bdt tree) {
	if (tree != NULL) {
		printNames(leftChild(tree));
		std::cout << nodeName(tree) << std::endl;
		printNames(rightChild(tree));
	}
}


std::string nodeName(bdt tree) {
	return tree->val;
}
bdt rightChild(bdt tree) {
	return tree->right;
}
bdt leftChild(bdt tree) {
	return tree->left;
}
