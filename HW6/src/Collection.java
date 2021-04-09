

public interface Collection<E>
{	

	/**
		*creating the object of the iterator class.
		*@return Iterator object
	*/
	public Iterator<E> iterator();

	/**
		* Adds elements to the collection.
		*@throws Exception  if an element is wanted to be added that exist in the set.
		*@param e 'e' is the element that should be added.
		*@return Returns true if adding element is successful.
	*/
	public boolean add(E e)throws IllegalArgumentException;
	/**
		*@return return size
	*/
	public int size();
	/**
		*Checks whether there is an element in the collection.
		*@return Returns true if list is empty
	*/
	public boolean isEmpty();
	/**
		*Removes the desired element from the list.
		*@throws Exception If program want to delete an element that is not in the list. 
		*@param e is the element to be deleted from collection.
		*@return Returns true if remove operating is successful.

	*/
	public boolean remove(E e)throws Exception;
	/**
		*Clear make the size zero, and  create a new object and synchronize it to the old object
	
	*/
	public void clear();

	/**
		*Contains see if the sent element is in the collection.
		*@param e  is an object to match the elements in the list.
		*@return Returns true if the match is successful.
	*/
	public boolean contains(E e);
	/**
		*Does not re-add an existing element in the list
		*@param c is a collection.
		*@return Returns true if adding element is successful.
	*/
	public boolean addAll(Collection<E> c);
	/**
		*Checking the overlap of the data of the two lists.
		*@return returns false if the data does not match.
		*@param c is a collection.

	*/
	public boolean containsAll(Collection<E> c);
	/**
		*If there is matching data in the list of the list and parameter, program delete it.
		*@throws Exception If program want to delete an element that is not in the list. 
		*@param c is a collection.
		*@return Returns true if removeAll operating is successful.

	*/
	public boolean removeAll(Collection<E> c)throws Exception;
	/**
		*Lists the intersecting elements of two lists.
		*@param c is a collection.
		*@return Returns true if retainAll operating is successful.

	*/
	public boolean retainAll(Collection<E> c);
	
}