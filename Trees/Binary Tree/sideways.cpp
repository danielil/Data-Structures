
//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const
{
   sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}

