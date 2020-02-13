Raw Data deleted, download e.g. apple.npy from google

Node* AVL(root, node):
	# insert
	if root == null:
		return node;
	if node->val < root->val:
		root->left = AVL(root->left, node)
	else:
		root->right = AVL(root->right, node)
	# fix height
	height_diff = root->left->height - root->right->height
	if height_diff == 2:
		# right_rotate
		left = root->left # left child should be balanced or left heavy or needs double rotation, how to check if double rotation needed
		root->left = left->right
		left->right = root
		root->height = 1+max(root->right->height, root->left->height)
		root = left # new root to be returned
	else if height_diff == -2:
		# left_rotate
	root->height = 1+max(root->right->height, root->left->height) # base refresh, might be because of adding or new root(after rotation)
	return root
	
	do an AVL leetcode question
	
Node* leftRotate(root):
	left = root->left
	root->left = left->right
	left->right = root
	return left
	
Node* rightRotate(root):
	right = root->right
	root->right = right->left
	right->left = root
	return right
	
heap, avl, shell sort nlogn, avl h is changing

Node* search(root, target):
	if root->val == target:
		return delete(root)
	if target < root->val:
		root->left = search(root->left, target)
	else:
		root->right == search(root->right, target)
	update_height(root)
	return root

Node* delete(root):
if (root == null):
	return null
if left heavy || balanced:
	left = root->left
	left->left = delete(left)
	left->right = root->right
	root = left
else
	#right heavy
update_height(root)
return root