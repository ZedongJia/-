#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
typedef struct Folder
{
    string name;
    vector<Folder *> folders;
} Folder;

map<int, Folder *> loc;

int getTotalLen(Folder *folder, int prefixLen)
{
    int result = 0;
    for (Folder *subFolder : folder->folders)
    {
        int subPrefixLen = prefixLen + subFolder->name.length() + 1;
        result += subPrefixLen + getTotalLen(subFolder, subPrefixLen);
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    Folder *root = new Folder{"", {}};
    loc[0] = root;

    for (int index = 1; index <= n; index++)
    {
        int parentIndex;
        string name;
        cin >> parentIndex >> name;
        Folder *newFolder = new Folder{name, vector<Folder *>()};
        loc[index] = newFolder;
        loc[parentIndex]->folders.push_back(newFolder);
    }
    printf("%d", getTotalLen(root, 0));
}