#pragma once

#include<string>
#include"Utils.h"
#include"StretchyArray.h"
#include"MergeSort.h"

using namespace std;

StretchyArray<string> uniqueStrings(StretchyArray<string>& strs) {

	StretchyArray<string>ans;

	for (int i = 0; i + 1 < strs.size(); i++)
		if (strs[i] != strs[i + 1])
			ans.push_back(strs[i]);
	ans.push_back(strs[strs.size() - 1]);

	return ans;
}

StretchyArray<string> allPossibleStrings(string s, StretchyArray<string> ans) {

	//Every string has "empty string" as a subsequence.
	ans.push_back("");

	//Base case
	if (s.size() == 0) {
		return ans;
	}

	//Helping variables
	char firstLetter = s[0];
	string restOfWord = s.substr(1, s.size());

	//Recursive call
	ans = allPossibleStrings(restOfWord, ans);

	//Concatenate 'firstLetter' with every string in 'ans'.
	int size = ans.size();
	for (int si = 0; si < size; si++) {

		string temp = ans[si];

		//Concatenate 'firstLetter' with 'ans[si]' at every position.
		for (int i = 0; i <= ans[si].size(); i++) {

			temp = ans[si];
			temp.insert(temp.begin() + i, firstLetter);
			ans.push_back(temp);
		}
	}

	return ans;
}


//this function expects sorted arrays.
StretchyArray<string>intersectionOfStrings(StretchyArray<string>& strs1, StretchyArray<string>& strs2) {

	StretchyArray<string>ans;

	int i = 0, j = 0;
	while (i < strs1.size() && j < strs2.size()) {

		if (strs1[i] < strs2[j]) {
			i++;
		}
		else if (strs2[j] < strs1[i]) {
			j++;
		}
		else {
			ans.add(strs1[i]);
			i++, j++;
		}
	}

	return ans;
}

//Returns all dictionary words formed with the given word.
StretchyArray<string> inputWordAndReturnCombos() {

	ifstream fin("dictionary.txt");

	StretchyArray<string> dictionary = loadDictionary(fin);

	string word;

	cout << "Enter a word: ";
	cin >> word;

	StretchyArray<string> allCombos;

	allCombos = allPossibleStrings(word, allCombos);
	mergeSort(allCombos);

	return intersectionOfStrings(allCombos, dictionary);
}