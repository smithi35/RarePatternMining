	void TreeNode::add_transaction(array, size)
	{
		if (size > 0)
		{
			// first case: this node has no children
			if (children_number == 0)
			{
				i = new Item(array[0])
				
				child = new TreeNode(i)
				add_child(child)
			
				new_array = revise_array(array, size)
				child->add_transaction(new_array, size-1)
			}
			else
			{
				// Second, try to add the transaction to one of the children
				curr = NULL;
				
				stop = false;
				for (i = 0; i < children_number && !stop; i++)
				{
					curr = children[i];
					
					name = q->get_name();
					
					for (j = 0; j < size && !stop; j++)
					{
						if (name == array[j])
						{
							stop = true
							curr->increment_quantity()
							
							swap(0, j, array)
							int *new_array = revise_array(array, size)
							
							curr->add_transaction(new_array, size-1)
						}
					}
				}
				
				// Third, create a new group of children for this node
				if (!stop)
				{
					i = new Item(array[0])
					i->set_support(1)
					
					child = new TreeNode(i)
					add_child(child)
					
					new_array = revise_array(array, size)
					child->add_transaction(new_array, size-1)
				}
			}
		}
	}