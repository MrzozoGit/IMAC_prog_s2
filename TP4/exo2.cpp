#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "HuffmanNode.h"

_TestMainWindow* w = nullptr;
using std::size_t;
using std::string;

void HuffmanHeap::insertHeapNode(int heapSize, unsigned char c, int frequences)
{
    /**
      * Do Like Heap::insertHeapNode (exo1) but use HuffmanNode instead of
      * int, this->get(i): HuffmanNode*  <-> this->get(i).frequences
     **/
    int i = heapSize;
}

void HuffmanNode::insertNode(HuffmanNode* node)
{
    if( this->isLeaf() )
    {
        /**
         * On crée un nouveau noeud qui copie les données de this
         * (char, frequences)
         * Selon la valeur du noeud à insérer on l'insère soit à gauche
         * soit à droite et on insère la copie de this de l'autre coté
         *
         * La feuille courante (this) devient un parent et donc sa
         * fréquence devient la somme de ses nouveaux enfants et
         * son caractère devient '\0'
        **/
        HuffmanNode* copy = new HuffmanNode(this->character, this->frequences);
        this->character = '\0';
    }
    else
    {
        /**
         * Le noeud courant est un parent donc il faut demander
         * aux enfants d'insérer (soit à gauche si 3*node->frequences < this->frequences
         * soit à droite)
         * Remarques: Si un noeud n'est pas une feuille alors ses deux enfants sont
         * non-null (grâce à la condition d'au-dessus)
        **/
    }
    /**
     * à chaque insertion on additionne au noeud courant la valeur
     * du noeud à insérer (pour faire en sorte que la valeur du parent soit
     * toujours la somme de ses deux enfants)
     **/
    this->frequences += node->frequences;
}

void HuffmanNode::processCodes(std::string baseCode)
{
    /**
      * Travel whole tree of HuffmanNode, each time you call the left
      * child, add '0' to the baseCode and each time call the right
      * child, add '1'. If the node is a leaf, it takes the baseCode.
     **/
}

void HuffmanNode::fillCharactersArray(HuffmanNode** nodes_for_chars)
{
    if (!this->left && !this->right)
        nodes_for_chars[this->character] = this;
    else {
        if (this->left)
            this->left->fillCharactersArray(nodes_for_chars);
        if (this->right)
            this->right->fillCharactersArray(nodes_for_chars);
    }
}

void charFrequences(string data, Array& frequences)
{
    /**
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/
}

void huffmanHeap(Array& frequences, HuffmanHeap& heap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
     **/
    heapSize = 0;
}

void huffmanDict(HuffmanHeap& heap, int heapSize, HuffmanNode*& dict)
{
    /**
      * For each value in heap, insert a new node in dict
     **/
    dict = new HuffmanNode(heap[0].character, heap[0].frequences);
}

string huffmanEncode(HuffmanNode** characters, string toEncode)
{
    /**
      * characters gather all leaves in the Huffman dict
      * characters[i] is the HuffmanNode representing the
      * character with the ASCII code i
     **/
    string encoded = "";
    return encoded;
}

string huffmanDecode(HuffmanNode* dict, string toDecode)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman dict. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    string decoded = "";
    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w = new _TestMainWindow();

    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    Array& frequences = w->newArray(256);
    HuffmanHeap heap(256);
    HuffmanNode* dict;
    int i;

    for (i=0; i < (int)frequences.size(); ++i)
        frequences.__set__(i, 0);

    charFrequences(data, frequences);

    for (i=0; i < (int)frequences.size(); ++i)
        if (frequences[i]>0)
            qDebug() << (char)i << ": " << frequences[i];

    int heapSize=0;

    huffmanHeap(frequences, heap, heapSize);
    huffmanDict(heap, heapSize, dict);
    dict->processCodes("");

    HuffmanNode* characters[256];
    memset(characters, 0, 256 * sizeof (HuffmanNode*));
    dict->fillCharactersArray(characters);

    string encoded = huffmanEncode(characters, data);
    string decoded = huffmanDecode(dict, encoded);

    w->addBinaryNode(dict);
    w->updateScene();
    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
    w->show();

    return a.exec();
}
