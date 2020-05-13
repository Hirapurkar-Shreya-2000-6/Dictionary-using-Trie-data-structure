#include<iostream>
#include<string>
#include<fstream>

using namespace std;


#define SIZE (26)

#define CHAR_TO_ASCIIval(c) ((int)c - (int)'a')


struct TrieNode
{
    struct TrieNode *children[SIZE];

    bool isWordEnd;
};


struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}


void insert(struct TrieNode *root,  string key)
{
    struct TrieNode *pCrawl = root;

    for (int level = 0; level < key.length(); level++)
    {
        int index = CHAR_TO_ASCIIval(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isWordEnd = true;
}

bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i <SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

bool search(struct TrieNode *root, const string key)
{
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < key.length(); level++)
    {
        int index = CHAR_TO_ASCIIval(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isWordEnd);
}




void wordRecord(struct TrieNode* root, string currPrefix)
{

    if (root->isWordEnd)
    {
        cout << currPrefix;
        cout << endl;
    }


    if (isLastNode(root))
        return;

    for (int i = 0; i < SIZE; i++)
    {
        if (root->children[i])
        {

            currPrefix.push_back(97 + i);


            wordRecord(root->children[i], currPrefix);

            currPrefix.pop_back();
        }
    }
}


int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;

    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_ASCIIval(query[level]);


        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }
      bool isWord = (pCrawl->isWordEnd == true);


    bool isLast = isLastNode(pCrawl);


    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }

    if (!isLast)
    {
    string prefix = query;
    wordRecord(pCrawl, prefix);
    return 1;
    }
}

int main()
{
   struct TrieNode* root = getNode();
    string data;
    ifstream infile;
    infile.open("mydict.txt", ios::in);
    cout<<"Reading data from the file and creating the Trie...................."<<endl;
    int count=0;

    for(int i=0;i<=1000;i++){
            infile >> data;
            insert(root, data);
    }
        infile.close();
        cout<<endl;
   cout<<"Enter the string to find for suggestions"<<endl;;
   string query="";
   cin>>query;
   cout<<endl;
    int comp = printAutoSuggestions(root, query);

    if (comp == -1)
        cout << "No other strings found with this prefix\n";

    else if (comp == 0)
        cout << "No string found with this prefix\n";
    cout<<"working";
    return 0;
}
