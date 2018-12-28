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
bdt buildzerobdt(int height);
bdt constree(std::string el, bdt l, bdt r);
bdt instree(bdt t, int height, int num);
void runtree(bdt& t, std::string string, int j);
void storeleafnodes(bdt t, std::vector<std::string>& leafnodes);
bool checkdependency(const std::vector<std::string> leafnodes, std::vector<std::vector<int> >& routes);
void routetonode(std::vector<std::vector<int> >& routes, int index, int leafnodessize, int numNodesCompared);
void prunetree(bdt t, const std::vector<std::vector<int> >& routes);
void mergesubtree(bdt& t);
void deletetree(bdt t);
void printEachLevel1(bdt root, int level, bool pr);
void printEachLevel2(bdt root, int level, bool pr);

void mergesubtree1(bdt t);
void deletetree1(bdt t);
void prunetree1(bdt t, const std::vector<std::vector<int> >& routes);
void deletetree2(bdt t);


void printroot(bdt t);
void printtree(bdt t);

bdt buildbdt(const std::vector<std::string>& fvalues);
std::string evalbdt(bdt t, const std::string& input);
 
/// before the submission you need to remove the main
/// (either delete it or comment it out)
/// otherwise it will intefere with the automated testing
 
int main(){
 
    /// write the code for the main here in order to test your functions
	std::clock_t start;
	double duration;
	start = std::clock();

	bdt tmp = NULL;
	std::vector<std::string> input;

	//std::string in = "001";
	//input.push_back(in);
	//in = "010";
	//input.push_back(in);
	//in = "100";
	//input.push_back(in);


	std::string in = "00000000000000000000";
	input.push_back(in);
	
	
	tmp = buildbdt(input);
	printtree(tmp);
	std::cout << std::endl;

	std::vector<std::string> leafnodes;
	storeleafnodes(tmp, leafnodes);
	for (int i = 0; i < leafnodes.size(); i++) {
		std::cout << leafnodes[i] << " ";
	}
	std::cout << std::endl;



	
	std::vector<std::vector<int> > routes;
	checkdependency(leafnodes, routes);
	prunetree(tmp, routes);

	//printtree(tmp);
	std::cout << std::endl;
	std::vector<std::string> leafnodes2;
	storeleafnodes(tmp, leafnodes2);
	for (int i = 0; i < leafnodes2.size(); i++) {
		std::cout << leafnodes2[i] << " ";
	}
	std::cout << std::endl;

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "printf: " << duration << '\n';



	std::cout << "what strings do you want to check? Enter '0' to exit" << std::endl;
	std::string inp;
	while (inp != "0") {
		std::cin >> inp;
		std::cout << evalbdt(tmp, inp) << std::endl;
	}
    return 0;
}
 
bdt buildcompactbdt(const std::vector<std::string>& fvalues){
    /// write the implementation for the function here

}
 
std::string evalcompactbdt(bdt t, const std::string& input){
    /// write the implementation for the function here
}
 





/// add here the implementation for any other functions you wish to define and use
bdt buildbdt(const std::vector<std::string>& fvalues) {
	/// write the implementation for the function here
	std::string firstString = fvalues[0];
	int height = firstString.size() - 1;//get the height of the tree needed from first string(assumed all strings have same length)
	bdt t = NULL;//initialise an empty tree
	t = buildzerobdt(height);//build a tree with zeros in leaf nodes
	bdt t2 = NULL;
	t2 = t;
	for (int i = 0; i<fvalues.size(); i++) {
		std::string string = fvalues[i];
		for (int j = 0; j<string.size(); j++) {
			runtree(t2, string, j);
		}
		t2->val = "1";
		t2 = t;
	}
	return t;
}

std::string evalbdt(bdt t, const std::string& input) {
	/// write the implementation for the function here
	for (int i = 0; i<input.size(); i++) {
		runtree(t, input, i);
	}
	return t->val;
}

bdt buildzerobdt(int height) {
	bdt tmp = new bdnode;
	instree(tmp, height, 0);
	return tmp;
}

bdt constree(std::string el, bdt l, bdt r) {
	bdt tmp = new bdnode;
	tmp->val = el;
	tmp->left = l;
	tmp->right = r;
	return tmp;
}

bdt instree(bdt t, int height, int num) {
	if (height<0) {
		return constree("0", NULL, NULL);
	}
	else {
		num++;
		std::stringstream nodeval;
		nodeval << "x" << num;
		t->val = nodeval.str();
		height--;
		t->left = new bdnode;
		t->left = instree(t->left, height, num);
		t->right = new bdnode;
		t->right = instree(t->right, height, num);
		return t;
	}
}



void runtree(bdt& t, std::string string, int j) {
	char value = string[j];
	if (value == '0') {
		t = t->left;
	}
	else if (value == '1') {
		t = t->right;
	}
}


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




void storeleafnodes(bdt t, std::vector<std::string>& leafnodes) {
	if (t != NULL) {
		if (t->val == "1" || t->val == "0") {
			leafnodes.push_back(t->val);
		}
		else{
			storeleafnodes(t->left, leafnodes);
			storeleafnodes(t->right, leafnodes);
		}
	}
}

bool checkdependency(const std::vector<std::string> leafnodes, std::vector<std::vector<int> >& routes) {
	int numNodesCompared = 1;
	while (numNodesCompared <= leafnodes.size()/2) {
		for (int i = 0; i < leafnodes.size(); i += numNodesCompared*2) {//going through all nodes for one number of nodes compared
			bool dependent = false;
			for (int j = 0; j < numNodesCompared && !dependent; j++) {//test one node
				int c = i + j;
				if (leafnodes[i+j] != leafnodes[i+j+numNodesCompared]) {
					dependent = true;
				}
			}
			if (!dependent) {
				routetonode(routes, i, leafnodes.size(), numNodesCompared);
			}
		}
		numNodesCompared = numNodesCompared * 2;
	}
}

void routetonode(std::vector<std::vector<int> >& routes, int index, int leafnodessize, int numNodesCompared) {
	std::vector<int> route;
	int lowerindex = 0;
	int upperindex = leafnodessize;
	int level = log2(leafnodessize) - log2(numNodesCompared*2);
	int i = 0;
	while (upperindex>lowerindex+2 && i<level) {
		if (index+1 <= (upperindex+lowerindex)/2) {
			route.push_back(0);
			upperindex = (lowerindex+upperindex)/2;
		}
		else{
			route.push_back(1);
			lowerindex = (lowerindex+upperindex)/2;
		}
		i++;
	}
	if (level == 0) {
		route.push_back(-1);
	}
	routes.push_back(route);	
}

void prunetree(bdt t, const std::vector<std::vector<int> >& routes) {
/*	int minsize = 0;
	int minindex = 0;
	bool done = false;
	std::vector<std::vector<int> > simplifiedroutes;
	if (routes[routes.size() - 1][0] == -1) {
		simplifiedroutes.push_back(routes[routes.size() - 1]);
	}
	for (int i = routes.size() - 1; i >= 0 && !done; i--) {
		
	}*/ //probably not worth it

	for (int i = 0; i < routes.size(); i++) {
		bdt tmp = t;
		std::vector<int> route = routes[i];
		bool done = false;
		for (int j = 0; j < route.size() && !done; j++) {
			/*if (tmp->right == NULL) {
				done = true;
			}*/
			
			if (route[j] == 1) {
				tmp = tmp->right;
			}
			else if (route[j] == 0) {
				tmp = tmp->left;
			}
		}
		mergesubtree(tmp);
	}
}




void mergesubtree(bdt& t) {
	bdt tmp = t->left;
	deletetree(t->right);
	t->val = tmp->val;
	t->left = tmp->left;
	t->right = tmp->right;
	delete tmp;
}

void deletetree(bdt t) {
	if (t != NULL) {
		deletetree(t->left);
		deletetree(t->right);
		delete t;
	}
}

void prunetree1(bdt t, const std::vector<std::vector<int> >& routes) {
	/*	int minsize = 0;
	int minindex = 0;
	bool done = false;
	std::vector<std::vector<int> > simplifiedroutes;
	if (routes[routes.size() - 1][0] == -1) {
	simplifiedroutes.push_back(routes[routes.size() - 1]);
	}
	for (int i = routes.size() - 1; i >= 0 && !done; i--) {

	}*/ //probably not worth it

	for (int i = routes.size()-1; i >= 0; i--) {
		bdt tmp = t;
		std::vector<int> route = routes[i];
		bool done = false;
		for (int j = 0; j < route.size() && !done; j++) {
			/*if (tmp->right == NULL) {
			done = true;
			}*/

			if (route[j] == 1) {
				tmp = tmp->right;
				if (tmp->val == "-1") {
					done = true;
				}
			}
			else if (route[j] == 0) {	
				tmp = tmp->left;
				if (tmp->val == "-1") {
					done = true;
				}
			}

		}
		if (!done) {
			mergesubtree1(tmp);
		}
		else {
			deletetree2(tmp);
		}
		
	}
}


void mergesubtree1(bdt t) {
	t->val = "-1";
	deletetree1(t->right);
}

void deletetree1(bdt t) {
	if ((t != NULL) && (t->val != "-1")) {
		deletetree1(t->left);
		deletetree1(t->right);
		t->val = "-1";
	}
}

void deletetree2(bdt t) {
	if (t != NULL) {
		deletetree1(t->left);
		deletetree1(t->right);
		if (t->val != "-1") {
			t->val = "-1";
		}
	}
}
