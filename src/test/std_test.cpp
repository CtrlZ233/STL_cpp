#include<list>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
using namespace std;
#include<string>
#include<memory.h>
#include<unordered_map>
#include<queue>
#include<math.h>

vector<int> subSort(vector<int>& array) {
	int min = INT32_MAX;
	int max = INT32_MIN;
	int len = array.size();
	int first = -1;
	int last = -1;
	for(int i=0; i<len; i++){
		if(array[i]<max){
			last = i;
		}else{
			max = array[i];
		}

		if(array[len-i-1] > min){
			first = len-i-1;
		}else{
			min = array[len-i-1];
		}
	}
	vector<int> ans;
	ans.push_back(first);
	ans.push_back(last);
	return ans;
}

int main(){
    system("pause");
}