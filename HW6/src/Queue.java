

public interface Queue<E> extends Collection<E>
{
	/**
		* Adds the sent element to the list.
		*@param e 'e' is the element that should be added.
		*@return Returns true if adding element is successful.
	*/
	public boolean add(E e);
	/**
		*Returns the last element of the queue.
		*@return Returns the last element of the queue.
	*/
	public E element();
	/**
		*adds elements if the list has capacity
		*@param e will be add if there is a space in list.
		*@return Returns true if the element was added.
	*/
	public boolean offer(E e);
	/**
		*deletes the last element of the queue.
		*@throws  Exception if set is empty
		*@return returns the data deleted.

	*/
	public E poll() throws Exception ;

}

