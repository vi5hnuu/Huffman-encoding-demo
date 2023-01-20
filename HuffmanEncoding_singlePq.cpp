#include<bits/stdc++.h>
using namespace std;

/*
TestCase : FFFFAABBAAABCCCCCDDEDEAABBCAAA

output of each function is mentioned in the comments below...
*/

class Node{
  public:
    char c;
    int val;
    const Node *left;
    const Node *right;
  explicit Node(int val,char c=' ',const Node *lft=nullptr,const Node *rght=nullptr):c{c},val{val},left{lft},right{rght}{}

  Node* operator + (const Node &other) const{
    Node *tmp= new Node(val + other.val,' ',this,&other);
    return tmp;
  }
};

class NodeComparator{
  public:
    bool operator ()(const Node *f,const Node *s) const{
        return f->val > s->val;
    }
}ncp;
class PairComparator{
  public:
    bool operator ()(const pair<int,char> &left,const pair<int,char> &right) const{
        return left.first > right.first;
    }
}pcp;


void inorderTree(const Node *root){
  if(!root){
    return;
  }
  inorderTree(root->left);
  cout<<"[ "<<(root->val)<<" "<<(root->c==' ' ? '*':root->c)<<" ]"<<endl;
  inorderTree(root->right);
}

enum Direction{
  LEFT,RIGHT,STATIC
};
void printHuffmanEncoding(const Node *root,string path="",Direction parDir=Direction::STATIC){//parDir is dir of par wrt child
  if(!root){
    return;
  }
  char pathSlug=' ';
  if(parDir!=Direction::STATIC){
    if(parDir==Direction::RIGHT){
      pathSlug='0';
    }else{
      pathSlug='1';
    }
  }
  if(!root->left && !root->right){
    cout<<path<<pathSlug<<"\t"<<root->c<<endl;
    return;
  } 

  printHuffmanEncoding(root->left,path+pathSlug,Direction::RIGHT);
  printHuffmanEncoding(root->right,path+pathSlug,Direction::LEFT);
}

void encodedTextMap(const Node *root,vector<string> &paths,string path="",Direction parDir=Direction::STATIC){//parDir is dir of par wrt child
  if(!root){
    return;
  }
  char pathSlug=' ';
  if(parDir!=Direction::STATIC){
    if(parDir==Direction::RIGHT){
      pathSlug='0';
    }else{
      pathSlug='1';
    }
  }
  if(!root->left && !root->right){
    paths[root->c-'A']=path+pathSlug;
    return;
  } 

  encodedTextMap(root->left,paths,path+pathSlug,Direction::RIGHT);
  encodedTextMap(root->right,paths,path+pathSlug,Direction::LEFT);
}


void releaseMemory(const Node *root){
    if(!root){
      return;
    }
    releaseMemory(root->left);
    releaseMemory(root->right);
    cout<<"releasing memory for node with value : "<<root->val<<endl;
    delete root;
}

int main(){
  string encodeStr;
  cin >> encodeStr;
  int freqCaps[26]{};
  for(const char &c:encodeStr){
    freqCaps[c-'A']++;
  }

  priority_queue<Node*,vector<Node*>,decltype(ncp)> huffmanTree;
  for(int i=0;i<26;i++){
    if(freqCaps[i]>0){
      huffmanTree.push(new Node{freqCaps[i],static_cast<char>(i+'A')});
    }
  }

  //This will store the encoding of each different character in all caps string
 vector<string> encodedMap(huffmanTree.size(),"");


  while(huffmanTree.size()>1){
    Node *nodefmin=huffmanTree.top();
    huffmanTree.pop();
    Node *nodesmin=huffmanTree.top();
    huffmanTree.pop();
    huffmanTree.push(*nodefmin+*nodesmin);
  }

  inorderTree(huffmanTree.top());
  /*
    [ 2 E  ]
    [ 5 *  ]
    [ 3 D  ]
    [ 9 *  ]
    [ 4 F  ]
    [ 19 * ] -> *(asterisk) indicate this node is either child or root but not leaf
    [ 10 A ]
    [ 30 * ]
    [ 5 B  ]
    [ 11 * ]
    [ 6 C  ]
  */

  printHuffmanEncoding(huffmanTree.top());
  /*
  0000   E
  0001   D
  001    F
  01     A
  10     B
  11     C
  */

 encodedTextMap(huffmanTree.top(),encodedMap);
  string encodedString="";
  for(const char &c:encodeStr){
    encodedString += encodedMap[c-'A'];
  }
  cout<<"ENCODED TEXT : "<<encodedString<<endl;


  cout<<"\n-Releasing Resources-\n";
  releaseMemory(huffmanTree.top());
}