
public class ArrayList<E> implements List<E>
{

	protected int _size;
	protected int cap;
	protected Object[] obj_array;

	ArrayList()
	{
		_size=0;								//I determine the initial values of size and capacity and object.
		cap=1;
		obj_array =new Object[cap]; 
	} 

	/**
		* Adds the sent element to the list.
		*@param e 'e' is the element that should be added.
		*@return Returns true if adding element is successful.
	*/
	public boolean add(E e){

		int temp = _size;
			
		if(_size >= this.cap){
            cap++;
            Object[] newarray = new Object[cap];		//I create a new object with capacity, place all the elements in it and put the data in the last element.
            
            for(int i = 0; i < _size; i++)
            	newarray[i] = obj_array[i];              
            
            obj_array = (Object[]) newarray;
        }
        obj_array[_size]=e;
        _size++;
        if (temp < _size)
        	return true;
        return false;
        
		
	}
	/**
		*creating the object of the iterator class.
		*@return Iterator object
	*/
	public Iterator<E> iterator() {						//I am creating the object of the iterator class.
		Iterator<E> iter= new Iterator<E>(this.obj_array,0,_size);
		return iter;
	}

	/**
		*Merging data of two collections
		*@param c is a collection.
		*@return Returns true if adding element is successful.
	*/
	public boolean addAll(Collection<E> c)
	{	
		
		Iterator<E> iter = c.iterator();
	
		while(iter.hasnext()){
			this.add(iter.next());
		}

		
		return true;

	}

	/**
		*Checking the overlap of the data of the two lists.
		*@return returns false if the data does not match.
		*@param c is a collection.

	*/
	public boolean containsAll(Collection<E> c){
		int counter=0;
		
		Iterator<E> iter = c.iterator();		//Checking the overlap of the data of the two lists
		
		while(iter.hasnext()){
			if(!this.contains(iter.next())){
				return false;
			}
		}

		return true;

	}

	/**
		*Lists the intersecting elements of two lists.
		*@param c is a collection.
		*@return Returns true if retainAll operating is successful.

	*/
	public boolean retainAll(Collection<E> c){
		int counter=0;								//If the data in the list is not in the list in the parameter, I update it.
		
		Object[] newarray = new Object[_size];

		for(int i=0;i<_size;i++){
			if(c.contains((E)obj_array[i])==true){
				newarray[counter]=obj_array[i];
				counter++;
			}

		}

		_size=counter;
		obj_array=newarray;
		
	
		return true;

	}

	/**
		*If there is matching data in the list of the list and parameter, program delete it.
		*@throws Exception If program want to delete an element that is not in the list. 
		*@param c is a collection.
		*@return Returns true if removeAll operating is successful.

	*/
	public boolean removeAll(Collection<E> c)throws Exception{

		int counter=0;
		Object[] newarray = new Object[_size];

		Iterator<E> iter = c.iterator();					//If there is matching data in the list of the list and parameter, I delete it.

		for(int i=0;i<_size;i++){
			if(c.contains((E)obj_array[i])==true){
				remove((E)obj_array[i]);
				counter++;
			}

		}
		
		return true;

	}

	/**
		*Clear make the size zero, and  create a new object and synchronize it to the old object
	
	*/
	public void clear()
	{	
		cap=0;
		_size=0;
		Object[] newarray = new Object[_size];			//I make the size zero, and I create a new object and synchronize it to the old object
		obj_array=(Object[]) newarray;
		
		
	}
	
	/**
		*Contains see if the sent element is in the collection.
		*@param e  is an object to match the elements in the list.
		*@return Returns true if the match is successful.
	*/
	public boolean contains(E e) {
		for(int i=0; i<_size; i++)
			if(e.equals(obj_array[i]))				//I see if the sent element is in the collection.
				return true;
		return false;
	}

	/**
		*Checks whether there is an element in the collection.
		*@return Returns true if list is empty
	*/
	public boolean isEmpty()
	{
		if(_size==0)						
			return true;
		else
			return false;
	}


	/**
		*Removes the desired element from the list.
		*@throws Exception If program want to delete an element that is not in the list. 
		*@param e is the element to be deleted from collection.
		*@return Returns true if remove operating is successful.

	*/
	public boolean remove(E e)throws Exception {
		int del=0;
		if(!this.contains(e))
			throw new Exception("Error : There is no " + e +" so it cannot be deleted");		
			
		for(int i=0; i<_size; i++){
			if(e.equals(obj_array[i])){
				del=i;					
			}
		}
		if(del<0 || del>size())
			throw new Exception("Error : Out of range");		//Exception : if the range of the item to be deleted is out of size
		
		
        for ( int i = del; i+1!=_size; i++)						//I delete the desired element.
        	obj_array[i]=obj_array[i+1];


        _size--;

         Object[] newarray = new Object[_size];
         for(int i=0; i<_size; i++)
            	newarray[i] = obj_array[i];              
            
         obj_array=(Object[]) newarray;
         return true;
		
	}

	/**
		*@return return size
	*/
	public int size()
	{
		return _size;
	}
	
}