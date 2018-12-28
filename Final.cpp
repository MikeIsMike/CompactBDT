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
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots, int h);
void findNodes(bdt root, bdt prevroot, int level, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots);
void compareTrees(bdt a, bdt b, bool& same);
void findSubtree(std::vector<bdt>& currentroots, std::vector<bdt>& prevroots);
void deleteSubtree(bdt root, bdt prevroot);
void deleteTree(bdt t);
void swapOrder(bdt& tree, bool& keepSwapping);
void findAnswer(bdt tree, std::string input, std::string& value);

bdt buildbdt(const std::vector<std::string>& fvalues);
bdt consubtree(int height, int num);
void instree(const std::vector<std::string>& fvalues, bdt rootnode);
 
/// add here the declarations (not the implementation)
/// for any other functions you wish to define and use
void printroot(bdt t);
void printtree(bdt t, int& count);


 
/// before the submission you need to remove the main
/// (either delete it or comment it out)
/// otherwise it will intefere with the automated testing
 
/*int main(){
 
    /// write the code for the main here in order to test your functions
	
	double totalduration = 0;
	
	bdt tmp = NULL;

	std::vector<std::string> input;

	std::string in = "00000000000000000000";
	input.push_back(in);
	in = "01100000000000000000";
	input.push_back(in);
	in = "00000000000000000110";
	input.push_back(in);
	in = "10000000000000000011";
	input.push_back(in);
	in = "10000000110000000011";
	input.push_back(in);
	in = "10000000000011000010";
	input.push_back(in);
	in = "10000100000000000011";
	input.push_back(in);
	in = "01000000000000000001";
	input.push_back(in);
	in = "10000000000001010000";
	input.push_back(in);
	in = "10000010100000000011";
	input.push_back(in);
	in = "10010101010000000001";
	input.push_back(in);
	in = "10110010100010000000";
	input.push_back(in);
	in = "10000010111111100001";
	input.push_back(in);
	in = "10110001010000001011";
	input.push_back(in);
	in = "10000010100110000000";
	input.push_back(in);

	for (int i = 0; i < 10; i++) {
		std::clock_t start;
		start = std::clock();

		tmp = buildcompactbdt(input);
		int count = 0;
		printtree(tmp, count);
		std::cout << std::endl;
		std::cout << "nodecount: " << count << std::endl;
		double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout <<"this build and compact bdt took: "<< duration << std::endl;
		totalduration +=  duration;
		//deleteTree(tmp);
		std::cout << std::endl;
		
	}

	//
	//
	//

	std::cout << "avg build and compact bdt: " << totalduration/10 << '\n';
	for (int i = 0; i < input.size(); i++) {
		std::cout << evalcompactbdt(tmp, input[i]) << std::endl;
		
	}
	in = "11111111111111111111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	in = "11111111111110001111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	in = "1111100111110001111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	in = "10000111111110001111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	in = "11010111111110001111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	in = "01010111111110001111";
	std::cout << evalcompactbdt(tmp, in) << std::endl;
	
	
	// std::vector<std::vector<int> > routes;
	// checkdependency(leafnodes, routes);
	// prunetree(tmp, routes);
	int ab = 0;
	printtree(tmp, ab);
	std::cout << std::endl;


    return 0;
}*/
 
 bdt buildcompactbdt(const std::vector<std::string>& fvalues){
     /// write the implementation for the function here
	 std::vector<bdt> currentroots;
	 std::vector<bdt> prevroots;
	 std::string input = fvalues[0];
	 int height = input.size();

	 
	 bdt t = buildbdt(fvalues);
	 bdt t2 = t;
	 nextLevel(t, t2, currentroots, prevroots, height);

	 findSubtree(currentroots, prevroots);

	 bool keepSwapping = true;
	 while (keepSwapping) {
		 keepSwapping = false;
		 swapOrder(t, keepSwapping);
	 }
	 return t;
 }
 
 std::string evalcompactbdt(bdt t, const std::string& input){
     /// write the implementation for the function here
	 std::string value;
	 findAnswer(t, input, value);
	 return value;
 }
 





/// add here the implementation for any other functions you wish to define and use
 bdt buildbdt(const std::vector<std::string>& fvalues) {
	 int height = fvalues[0].size();
	 bdt rootnode = consubtree(height, 1);
	 instree(fvalues, rootnode);
	 return rootnode;
 }


 bdt consubtree(int height, int num) {
	 if (height <= 0) {
		 bdt node = new bdnode;
		 node->val = "0";
		 node->left = NULL;
		 node->right = NULL;
		 return node;
	 }
	 bdt node = new bdnode;
	 node->val = "x" + std::to_string(num);
	 node->left = consubtree(height - 1, num+1);
	 node->right = consubtree(height - 1, num+1);

	 return node;
 }


 void instree(const std::vector<std::string>& fvalues, bdt rootnode) {
	 bdt node = rootnode;
	 int stringlength = fvalues[0].size();
	 std::string value;
	 for (int i = 0; i < fvalues.size(); i++) {
		 for (int j = 0; j < stringlength; j++) {
			 value = fvalues[i].at(j);
			 if (value == "0") {
				 node = node->left;
			 }
			 else {
				 node = node->right;
			 }
		 }
		 node->val = "1";
		 node = rootnode;
	 }
 }


////////////////////////////////////////////////////////////////////////////////
void nextLevel(bdt root, bdt prevroot, std::vector<bdt>& currentroots, std::vector<bdt>& prevroots, int height) {
	for (int i = 1; i <= height; i++) {
		findNodes(root, prevroot, i, currentroots, prevroots);
	}
}


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


void findSubtree(std::vector<bdt>& currentroots, std::vector<bdt>& prevroots) {//could potentially delete from top of bdt to save even more operations, but exception thrown when a deleted node is accessed needs to be handled
	int j = prevroots.size() - 1;
	for (int i = currentroots.size() - 1; i > -1; i--) {
		bdt root = currentroots[i];
		bdt prevroot = prevroots[j];
		deleteSubtree(root, prevroot);
		j--;
	}
}


void deleteSubtree(bdt root, bdt prevroot) {
	bdt tmp;
	deleteTree(root->right);
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


void deleteTree(bdt t) {
	if (t != NULL) {
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
	}
}


void swapOrder(bdt& t, bool& keepSwapping) {
	if (t != NULL) {
		swapOrder(t->left, keepSwapping);
		swapOrder(t->right, keepSwapping);
		if (t->left != NULL && t->right != NULL && t->left->val == t->right->val && !keepSwapping) {
			bool same = true;
			compareTrees(t->left->left, t->right->left, same);
			if (same) {
				bdt tmp = t;
				bdt tmp1 = t->right->right;
				bdt tmp2 = t->left->right;
				bdt tmp3 = t->left;
				bdt tmp4 = t->right;
				t = tmp3;
				t->right = tmp;
				t->right->right = tmp1;
				t->right->left = tmp2;
				deleteTree(tmp4->left);
				delete tmp4;
				keepSwapping = true;
			}
			
			else if(!same) {
				same = true;
				compareTrees(t->left->right, t->right->right, same);
				if (same) {
					bdt tmp = t;
					bdt tmp1 = t->right->left;
					bdt tmp2 = t->left->left;
					bdt tmp3 = t->left;
					bdt tmp4 = t->right;
					t = tmp3;
					t->left = tmp;
					t->left->left = tmp2;
					t->left->right = tmp1;
					deleteTree(tmp4->right);
					delete tmp4;
					keepSwapping = true;
				}
			}
		}
	}
}

///////////////////////////////////////////////
void findAnswer(bdt t, std::string input, std::string& value) {
	if (t->left != NULL) {
		std::stringstream index(t->val);
		int i;
		char x;
		index >> x;
		index >> i;
		if (input[i - 1] == '1') {
			findAnswer(t->right, input, value);
		}
		else {
			findAnswer(t->left, input, value);
		}
	}
	else {
		value = t->val;
	}

}






//////////////////////////////


void printroot(bdt t) {
	std::cout << t->val /*<<std::endl*/ << " ";
}

void printtree(bdt t, int& count) {
	if (t != NULL) {
		printtree(t->left, count);
		printroot(t);
		count++;
		printtree(t->right, count);
	}
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////