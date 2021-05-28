#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

struct Trie
{
	char value;
	Trie *nodes[26];
	bool isEnd;
};

Trie* create(char x)
{
	struct Trie *temp_node = new Trie;
	temp_node->value=x;
	for(int i=0;i<26;i++)
	{
		temp_node->nodes[i]=NULL;
	}
	temp_node->isEnd=true;
	return temp_node;
}

void add(Trie *root, string word)
{
	Trie *temp_node = root;
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	for(int i=0;i<word.length();i++)
	{
		int temp = int(word[i]) - 97;
		if(!temp_node->nodes[temp])
		{
			temp_node->nodes[temp] = create(word[i]);
		}
		temp_node = temp_node->nodes[temp];
	}
}

//void printNode(Trie *root)
//{
//	cout<<"\n\nValue of Root => "<<root->value;
//	for(int i=0;i<26;i++)
//	{
//		cout<<"Value at "<<i<<" => "<<root->nodes[i]<<" => "<<char(i+97)<<endl;
//		if(root->nodes[i])
//		{
//			printNode(root->nodes[i]);
//		}
//	}
//}

void printWord(Trie *root, string word)
{
	int flag=1;
	word += root->value;
	for(int i=0;i<26;i++)
	{
		if(root->nodes[i])
		{
			flag=0;
			printWord(root->nodes[i], word);
		}
	}
	if(flag==1)
	{
		cout<<word<<"\t";
		word = "";
	}
}

main()
{
	Trie *head = create('.');
	fstream file;
	file.open("words.txt", ios::in);
	if(!file)
	{
		cout<<"Error occured";
	}
	else
	{
		string word;
		while(getline(file, word))
		{
			add(head, word);
		}
	}	
	cout<<"List loaded, input one character at a time"<<endl;
	
	Trie *temp = head;
	int index;
	char c;
	string str;
	string input="";
	while(c!='.')
	{
		cout<<"Type here : "<<str;
		cin>>c;
		cout<<"\n---------------------------------------------------"<<endl;
		index = int(c) - 97;
		if(temp->nodes[index])
		{
			printWord(temp->nodes[index],str);
			temp = temp->nodes[index];
		}
		else
		{
			cout<<"No suggestions available";
			exit(0);
		}
		cout<<"\n---------------------------------------------------"<<endl;
		str += char(c);
	}
}
